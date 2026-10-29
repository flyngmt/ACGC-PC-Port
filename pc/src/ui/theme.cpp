#include "acgc/ui/theme.hpp"

#include "acgc/settings.hpp"
#include "acgc/ui/theme_mirror.hpp"
#include "acgc/ui/ui.hpp"
#include "pc_platform.h"

#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/StyleTypes.h>
#include <RmlUi/Core/TypeConverter.h>
#include <SDL3/SDL_timer.h>
#include <fmt/format.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <memory>
#include <string_view>
#include <vector>

namespace acgc::ui::theme {
namespace {

struct Token {
	const char* name;
	Rml::String day;
	Rml::String night;
};

constexpr int kNightStartMinutes = 20 * 60;
constexpr int kDayStartMinutes   = 6 * 60;
constexpr int kGraceMinutes      = 5;
constexpr Uint64 kStallMs        = 250;
constexpr Uint64 kFinishMs       = 400;
constexpr float kSweepMs         = 15000.0f;
constexpr float kSweepEdge       = 0.5f;

std::array kPalette = {
	Token { "--color-background", {}, {} },
	Token { "--color-surface", {}, {} },
	Token { "--color-surface-border", {}, {} },
	Token { "--color-surface-raised", {}, {} },
	Token { "--color-surface-sunken", {}, {} },
	Token { "--color-divider", {}, {} },
	Token { "--color-text", {}, {} },
	Token { "--color-text-muted", {}, {} },
	Token { "--color-text-faint", {}, {} },
	Token { "--color-text-strong", {}, {} },
	Token { "--color-text-on-accent", {}, {} },
	Token { "--color-heading", {}, {} },
	Token { "--color-warning", {}, {} },
	Token { "--color-control", {}, {} },
	Token { "--color-control-strong", {}, {} },
	Token { "--color-highlight", {}, {} },
	Token { "--color-selected", {}, {} },
	Token { "--color-pressed", {}, {} },
	Token { "--color-accent", {}, {} },
	Token { "--color-accent-bright", {}, {} },
	Token { "--color-shadow", {}, {} },
	Token { "--color-shadow-soft", {}, {} },
	Token { "--color-scroll-track", {}, {} },
	Token { "--color-scroll-thumb", {}, {} },
	Token { "--color-positive", {}, {} },
	Token { "--color-positive-soft", {}, {} },
	Token { "--color-modified", {}, {} },
	Token { "--color-status-bad", {}, {} },
	Token { "--color-status-info", {}, {} },
	Token { "--color-modal-button", {}, {} },
	Token { "--color-modal-button-text", {}, {} },
	Token { "--color-modal-button-text-strong", {}, {} },
	Token { "--color-modal-button-hover", {}, {} },
	Token { "--color-modal-button-active", {}, {} },
	Token { "--color-pattern-tint", {}, {} },
};

bool sStarted          = false;
bool sNight            = false;
Uint64 sSweepStart     = 0;
Uint64 sLastUpdate     = 0;
Uint64 sFinishedAt     = 0;
Rml::Context* sContext = nullptr;
std::vector<std::unique_ptr<DocumentSweep>> sSweeps;
std::vector<Rml::ElementDocument*> sShown;

std::array<Rml::Colourb, 2> sBackground{};

void load_palette(Rml::Context& context)
{
    // RmlUi resolves the stylesheet so the RCSS remains the sole source of theme
    // values. This hidden probe never joins the interactive document stack.
    auto* probe = context.LoadDocumentFromMemory(R"(<rml><head>
        <link type="text/rcss" href="res/rml/theme.rcss" />
        </head><body /></rml>)");
    if (!probe) return;
    probe->SetProperty("background-color", "var(--color-background)");
    for (int night = 0; night < 2; ++night) {
        probe->SetClassNames(night ? "theme-night" : "theme-day");
        probe->UpdateDocument();
        for (auto& token : kPalette) {
            if (const auto* property = probe->GetProperty(token.name)) {
                (night ? token.night : token.day) = property->Get<Rml::String>();
            }
        }
        sBackground[night] = probe->GetProperty<Rml::Colourb>("background-color");
    }
    probe->Close();
}

bool night_at(int minutes)
{
	return minutes >= kNightStartMinutes || minutes < kDayStartMinutes;
}

bool in_grace(int minutes)
{
	const int start = night_at(minutes) ? kNightStartMinutes : kDayStartMinutes;
	return minutes >= start && minutes < start + kGraceMinutes;
}

void apply_palette(Rml::Element& element, bool night)
{
	for (const Token& token : kPalette) {
		element.SetProperty(token.name, night ? token.night : token.day);
	}
}

struct SweepMasks {
	Rml::String from;
	Rml::String to;
};

Rml::String ramp_mask(float from, float width, bool rising)
{
	const auto alpha = [from, width, rising](float position) {
		const float t = std::clamp((position - from) / width, 0.0f, 1.0f);
		return static_cast<int>(std::lround((rising ? t : 1.0f - t) * 255.0f));
	};
	const float start = std::clamp(from, 0.0f, 1.0f);
	const float end   = std::clamp(from + width, 0.0f, 1.0f);
	return fmt::format("linear-gradient(315deg, #000000{:02x} {:.2f}%, #000000{:02x} {:.2f}%)", alpha(start),
	                   start * 100.0f, alpha(end), end * 100.0f);
}

SweepMasks sweep_masks(float progress)
{
	const float eased = progress * progress * (3.0f - 2.0f * progress);
	const float front = eased * (1.0f + kSweepEdge) - kSweepEdge;
	return { ramp_mask(front, kSweepEdge, true), ramp_mask(front, kSweepEdge, false) };
}

DocumentSweep* find_sweep(const Rml::ElementDocument* source)
{
	const auto found = std::ranges::find(sSweeps, source, &DocumentSweep::source);
	return found != sSweeps.end() ? found->get() : nullptr;
}

bool is_copy(const Rml::ElementDocument* document)
{
	return std::ranges::find(sSweeps, document, &DocumentSweep::document) != sSweeps.end();
}

std::vector<Rml::ElementDocument*> live_documents()
{
	std::vector<Rml::ElementDocument*> documents;
	if (sContext != nullptr) {
		for (int i = 0; i < sContext->GetNumDocuments(); ++i) {
			if (Rml::ElementDocument* document = sContext->GetDocument(i); !is_copy(document)) {
				documents.push_back(document);
			}
		}
	}
	return documents;
}

void drop_sweeps_if(const std::vector<Rml::ElementDocument*>& live, auto&& predicate)
{
	std::erase_if(sSweeps, [&](const auto& sweep) {
		if (!predicate(*sweep)) {
			return false;
		}
		if (std::ranges::find(live, sweep->source()) == live.end()) {
			sweep->source_destroyed();
		}
		return true;
	});
}

void clear_sweeps()
{
	drop_sweeps_if(live_documents(), [](const DocumentSweep&) { return true; });
}

bool shown(Rml::ElementDocument& document)
{
	const Rml::Property* visibility = document.GetProperty(Rml::PropertyId::Visibility);
	return visibility != nullptr && visibility->Get<Rml::Style::Visibility>() == Rml::Style::Visibility::Visible;
}

std::vector<Rml::ElementDocument*> shown_documents(const std::vector<Rml::ElementDocument*>& live)
{
	std::vector<Rml::ElementDocument*> visible;
	for (Rml::ElementDocument* document : live) {
		if (shown(*document)) {
			visible.push_back(document);
		}
	}
	return visible;
}

bool copies_ordered()
{
	for (int i = 0; i < sContext->GetNumDocuments(); ++i) {
		const DocumentSweep* sweep = find_sweep(sContext->GetDocument(i));
		if (sweep != nullptr && (i + 1 >= sContext->GetNumDocuments() || sContext->GetDocument(i + 1) != sweep->document())) {
			return false;
		}
	}
	return true;
}

void order_copies(const std::vector<Rml::ElementDocument*>& live)
{
	if (copies_ordered()) {
		return;
	}
	for (Rml::ElementDocument* document : live) {
		document->PullToFront();
		if (const DocumentSweep* sweep = find_sweep(document)) {
			sweep->document()->PullToFront();
		}
	}
}

void sync_sweeps(bool night, float progress)
{
	const std::vector<Rml::ElementDocument*> live    = live_documents();
	const std::vector<Rml::ElementDocument*> visible = shown_documents(live);
	drop_sweeps_if(live, [&visible](const DocumentSweep& sweep) {
		return std::ranges::find(visible, sweep.source()) == visible.end();
	});

	const SweepMasks masks = sweep_masks(progress);
	for (Rml::ElementDocument* source : visible) {
		DocumentSweep* sweep = find_sweep(source);
		if (sweep == nullptr) {
			const bool justOpened = std::ranges::find(sShown, source) == sShown.end();
			sweep = sSweeps.emplace_back(std::make_unique<DocumentSweep>(*sContext, *source, justOpened)).get();
			if (sweep->document() == nullptr) {
				sSweeps.pop_back();
				continue;
			}
			apply_palette(*sweep->document(), night);
		}
		sweep->sync();
		sweep->set_masks(masks.from, masks.to);
	}
	order_copies(live);
}

void switch_palette(bool night)
{
	const bool changed = night != sNight;
	sSweepStart        = 0;
	sNight             = night;
	if (changed && sContext != nullptr) {
		apply_palette(*sContext->GetRootElement(), sNight);
	}
}

void settle(bool night)
{
	clear_sweeps();
	sFinishedAt = 0;
	switch_palette(night);
}

void advance()
{
	const InterfaceTheme theme = settings().video.theme.get();
	const bool dynamic         = theme == InterfaceTheme::Dynamic;
	const int minutes          = dynamic ? pc_clock_minutes() : 0;
	const bool night           = dynamic ? night_at(minutes) : theme == InterfaceTheme::Night;
	const bool grace           = dynamic && in_grace(minutes);
	if (!sStarted) {
		sStarted = true;
		settle(grace ? !night : night);
	}

	if (sFinishedAt != 0) {
		if (night == sNight && SDL_GetTicks() - sFinishedAt < kFinishMs) {
			sync_sweeps(night, 1.0f);
			return;
		}
		settle(sNight);
	}
	if (night == sNight) {
		if (sSweepStart != 0) {
			settle(night);
		}
		return;
	}
	if (sSweepStart == 0) {
		if (!grace || sContext == nullptr) {
			settle(night);
			return;
		}
		if (!borealis::ui::any_document_visible()) {
			return;
		}
		sSweepStart = SDL_GetTicks();
		sLastUpdate = sSweepStart;
	}

	const Uint64 now = SDL_GetTicks();
	if (now - sLastUpdate > kStallMs) {
		sSweepStart += now - sLastUpdate;
	}
	sLastUpdate = now;

	const float progress = static_cast<float>(now - sSweepStart) / kSweepMs;
	if (progress >= 1.0f) {
		switch_palette(night);
		sFinishedAt = now;
		sync_sweeps(night, 1.0f);
		return;
	}
	sync_sweeps(night, progress);
}

} // namespace

void attach(Rml::Context* context) noexcept
{
	if (context == nullptr || context == sContext) {
		return;
	}
	for (const auto& sweep : sSweeps) {
		sweep->context_destroyed();
	}
	sSweeps.clear();
	sContext = context;
	load_palette(*sContext);
	sContext->GetRootElement()->SetProperty("color", "var(--color-text)");
	if (!sStarted) {
		update();
	}
	apply_palette(*sContext->GetRootElement(), sNight);
}

void detach() noexcept
{
	clear_sweeps();
	sContext = nullptr;
}

void update() noexcept
{
	advance();
	sShown = shown_documents(live_documents());
}

Rml::Colourb background() noexcept
{
	if (!sStarted) {
		update();
	}
	return sBackground[sNight ? 1 : 0];
}

} // namespace acgc::ui::theme
