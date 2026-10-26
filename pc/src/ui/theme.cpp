#include "acgc/ui/theme.hpp"

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
	Rml::Colourb day;
	Rml::Colourb night;
};

constexpr int kNightStartMinutes = 21 * 60;
constexpr int kDayStartMinutes   = 6 * 60;
constexpr int kGraceMinutes      = 5;
constexpr Uint64 kStallMs        = 250;
constexpr Uint64 kFinishMs       = 400;
constexpr float kSweepMs         = 15000.0f;
constexpr float kSweepEdge       = 0.5f;

const std::array kPalette = {
	Token { "--background", Rml::Colourb(0xF3, 0xE4, 0xB9), Rml::Colourb(0x13, 0x1A, 0x2A) },
	Token { "--surface", Rml::Colourb(0xFF, 0xFB, 0xE7), Rml::Colourb(0x1E, 0x27, 0x3B) },
	Token { "--surface-border", Rml::Colourb(0xF5, 0xE7, 0xBD), Rml::Colourb(0x34, 0x40, 0x5B) },
	Token { "--surface-raised", Rml::Colourb(0xF8, 0xED, 0xCF, 0xD6), Rml::Colourb(0x28, 0x33, 0x4C, 0xD6) },
	Token { "--surface-sunken", Rml::Colourb(0xFF, 0xF3, 0xD2, 0xD6), Rml::Colourb(0x18, 0x20, 0x33, 0xD6) },
	Token { "--divider", Rml::Colourb(0xEA, 0xD9, 0xAD), Rml::Colourb(0x3A, 0x47, 0x63) },
	Token { "--text", Rml::Colourb(0x65, 0x5B, 0x47), Rml::Colourb(0xEB, 0xE4, 0xD1) },
	Token { "--text-muted", Rml::Colourb(0x74, 0x68, 0x4F), Rml::Colourb(0xB9, 0xB1, 0x9F) },
	Token { "--text-faint", Rml::Colourb(0x65, 0x5B, 0x47, 0xAD), Rml::Colourb(0xEB, 0xE4, 0xD1, 0xA3) },
	Token { "--text-strong", Rml::Colourb(0x65, 0x54, 0x3C), Rml::Colourb(0x22, 0x28, 0x38) },
	Token { "--text-on-accent", Rml::Colourb(0xFF, 0xFD, 0xF3), Rml::Colourb(0xFF, 0xFD, 0xF3) },
	Token { "--heading", Rml::Colourb(0xD9, 0x78, 0x21), Rml::Colourb(0x8F, 0xA8, 0xE8) },
	Token { "--warning", Rml::Colourb(0xD9, 0x78, 0x21), Rml::Colourb(0xF2, 0xA6, 0x54) },
	Token { "--control", Rml::Colourb(0xFF, 0xFF, 0xFF, 0x85), Rml::Colourb(0xFF, 0xFF, 0xFF, 0x12) },
	Token { "--control-strong", Rml::Colourb(0xFF, 0xFF, 0xFF, 0x99), Rml::Colourb(0xFF, 0xFF, 0xFF, 0x1A) },
	Token { "--highlight", Rml::Colourb(0xFF, 0xE2, 0x7A), Rml::Colourb(0xD8, 0xDF, 0xF2) },
	Token { "--selected", Rml::Colourb(0xFF, 0xD2, 0x5A), Rml::Colourb(0xC9, 0xD3, 0xEE) },
	Token { "--pressed", Rml::Colourb(0xFF, 0xC7, 0x42), Rml::Colourb(0xB9, 0xC6, 0xE6) },
	Token { "--accent", Rml::Colourb(0xE9, 0x84, 0x24), Rml::Colourb(0x5B, 0x7F, 0xD1) },
	Token { "--accent-bright", Rml::Colourb(0xEF, 0x94, 0x2C), Rml::Colourb(0x78, 0x96, 0xDE) },
	Token { "--shadow", Rml::Colourb(0x36, 0x2D, 0x1D, 0x6B), Rml::Colourb(0x03, 0x07, 0x12, 0x99) },
	Token { "--shadow-soft", Rml::Colourb(0x36, 0x2D, 0x1D, 0x52), Rml::Colourb(0x03, 0x07, 0x12, 0x80) },
	Token { "--scroll-track", Rml::Colourb(0xD4, 0xB9, 0x7D, 0x40), Rml::Colourb(0x9F, 0xB0, 0xD5, 0x29) },
	Token { "--scroll-thumb", Rml::Colourb(0xD3, 0x8B, 0x2E, 0x8C), Rml::Colourb(0x78, 0x96, 0xDE, 0x8C) },
	Token { "--positive", Rml::Colourb(0x19, 0x8D, 0x79), Rml::Colourb(0x57, 0xC4, 0xAE) },
	Token { "--positive-soft", Rml::Colourb(0x89, 0xD2, 0xC2), Rml::Colourb(0x3F, 0x8C, 0x7F) },
	Token { "--modified", Rml::Colourb(0x00, 0x9C, 0x9B), Rml::Colourb(0x5C, 0xCF, 0xCE) },
	Token { "--status-bad", Rml::Colourb(0x9A, 0x73, 0x50), Rml::Colourb(0xC9, 0xA5, 0x82) },
	Token { "--status-info", Rml::Colourb(0x24, 0x7C, 0x9A), Rml::Colourb(0x74, 0xBF, 0xDC) },
	Token { "--modal-button", Rml::Colourb(0xFF, 0xF1, 0xA8), Rml::Colourb(0xFF, 0xFF, 0xFF, 0x14) },
	Token { "--modal-button-text", Rml::Colourb(0x4F, 0x49, 0x3D), Rml::Colourb(0xEB, 0xE4, 0xD1) },
	Token { "--modal-button-text-strong", Rml::Colourb(0x4F, 0x49, 0x3D), Rml::Colourb(0x22, 0x28, 0x38) },
	Token { "--modal-button-hover", Rml::Colourb(0xFF, 0xD6, 0x5A), Rml::Colourb(0xD8, 0xDF, 0xF2) },
	Token { "--modal-button-active", Rml::Colourb(0xFF, 0xC4, 0x29), Rml::Colourb(0xB9, 0xC6, 0xE6) },
	Token { "--pattern-tint", Rml::Colourb(0xFF, 0xFF, 0xFF), Rml::Colourb(0xA9, 0xBB, 0xEB) },
};

bool sStarted          = false;
bool sNight            = false;
bool sDebugInverted    = false;
bool sDebugArmed       = false;
Uint64 sSweepStart     = 0;
Uint64 sLastUpdate     = 0;
Uint64 sFinishedAt     = 0;
Rml::Context* sContext = nullptr;
std::vector<std::unique_ptr<DocumentSweep>> sSweeps;
std::vector<Rml::ElementDocument*> sShown;

Rml::String format(const Rml::Colourb& colour)
{
	Rml::String value;
	Rml::TypeConverter<Rml::Colourb, Rml::String>::Convert(colour, value);
	return value;
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
		element.SetProperty(token.name, format(night ? token.night : token.day));
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
	sDebugArmed        = false;
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
	const int minutes = pc_clock_minutes();
	const bool night  = night_at(minutes) != sDebugInverted;
	const bool grace  = sDebugArmed || in_grace(minutes);
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
		if (sSweepStart != 0 || sDebugArmed) {
			settle(night);
		}
		return;
	}
	if (sSweepStart == 0) {
		if (!grace || sContext == nullptr) {
			settle(night);
			return;
		}
		if (!any_document_visible()) {
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
	sContext->GetRootElement()->SetProperty("color", "var(--text)");
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

void debug_toggle() noexcept
{
	sDebugInverted = !sDebugInverted;
	sDebugArmed    = true;
}

Rml::Colourb background() noexcept
{
	if (!sStarted) {
		update();
	}
	static const Token& token = *std::ranges::find(kPalette, std::string_view { "--background" }, &Token::name);
	return sNight ? token.night : token.day;
}

} // namespace acgc::ui::theme
