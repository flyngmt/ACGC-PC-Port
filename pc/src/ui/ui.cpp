#include "acgc/ui/ui.hpp"
#include "acgc/ui/menu_bar.hpp"
#include "acgc/ui/overlay.hpp"
#include "acgc/ui/localization.hpp"
#include "acgc/ui/theme.hpp"
#include "acgc/ui/touch_controls.hpp"
#include <borealis/ui/input.hpp>
#include <borealis/io.hpp>
#include <borealis/log.hpp>
#include <aurora/aurora.h>
#include <aurora/input.hpp>
#include <aurora/rmlui.hpp>

constexpr borealis::Log Log{ "acgc::ui" };
extern "C" {
extern int g_pc_paused;
extern int g_pc_pause_input_drain;
extern int g_pc_nes_active;
}

namespace acgc::ui {
using namespace borealis::ui;

namespace {
bool sInitialized = false;
bool sWasPausingGame = false;
float sDisplayScale = 0.0f;
bool sControllerInput = false;
aurora::input::LayerId sMenuLayer = aurora::input::kInvalidLayerId;

bool load_ui_fonts() {
    const std::string bodyPath = borealis::io::fs_path_to_string(resource_path("fonts/OpenSans-SemiBold.ttf"));
    const std::string bodyBoldPath = borealis::io::fs_path_to_string(resource_path("fonts/OpenSans-Bold.ttf"));
    const std::string headingPath = bodyBoldPath;
    const std::string symbolsPath =
        borealis::io::fs_path_to_string(resource_path("fonts/MaterialSymbolsRounded-Regular.ttf"));

    const bool bodyLoaded =
        Rml::LoadFontFace(bodyPath, "ACGC Body", Rml::Style::FontStyle::Normal, Rml::Style::FontWeight::Normal, true);
    const bool bodyBoldLoaded = Rml::LoadFontFace(bodyBoldPath, "ACGC Body", Rml::Style::FontStyle::Normal,
                                                  Rml::Style::FontWeight::Bold, false);
    const bool headingLoaded = Rml::LoadFontFace(headingPath, "ACGC Heading", Rml::Style::FontStyle::Normal,
                                                 Rml::Style::FontWeight::Bold, false);
    const bool symbolsLoaded = Rml::LoadFontFace(symbolsPath, "Material Symbols Rounded", Rml::Style::FontStyle::Normal,
                                                 Rml::Style::FontWeight::Normal, false);
    if (!bodyLoaded || !bodyBoldLoaded || !headingLoaded || !symbolsLoaded) {
        Log.error("Could not load the bundled Animal Crossing UI fonts");
        return false;
    }

    Log.info("Loaded bundled Animal Crossing UI fonts");
    return true;
}

void sync_pause_state() {
    const bool shouldPause = any_document_visible() && g_pc_nes_active == 0;
    if (sWasPausingGame != shouldPause) {
        Log.info("Host menu {}; gameplay {}", shouldPause ? "opened" : "closed", shouldPause ? "paused" : "resumed");
    }
    if (sWasPausingGame && !shouldPause) {
        g_pc_pause_input_drain = 1;
    }
    g_pc_paused = shouldPause ? 1 : 0;
    sWasPausingGame = shouldPause;
}

aurora::input::EventResult menu_event(const aurora::input::InputEvent& event, void*) {
    sControllerInput = event.source.kind == aurora::input::InputSource::Kind::Controller;
    const auto* key = event.payload.get_if<aurora::input::InputEvent::KeyChanged>();
    if (key && key->scancode == SDL_SCANCODE_ESCAPE && key->pressed && !key->repeat && !any_document_visible() &&
        !sWasPausingGame) {
        if (auto* document = top_document()) {
            document->element()->DispatchEvent(kNavCommandEvent,
                                               { { "command", Rml::Variant{ static_cast<int>(NavCommand::Menu) } } });
            return aurora::input::EventResult::Consume;
        }
    }
    return aurora::input::EventResult::Pass;
}
} // namespace

bool initialize() noexcept {
    if (sInitialized) {
        return true;
    }
    if (!aurora::rmlui::is_initialized() || !load_ui_fonts()) {
        return false;
    }
    localization::load();
    if (!borealis::ui::initialize()) {
        return false;
    }
    input::apply_settings({ .menuChord = true, .menuTap = true });
    theme::attach(aurora::rmlui::get_context());
    sMenuLayer = aurora::input::register_layer(
        { .label = "acgc.menu", .priority = aurora::input::kRmlUiLayerPriority + 1, .onEvent = menu_event });
    sInitialized = true;
    push_document(std::make_unique<MenuBar>(), false);
    push_document(std::make_unique<Overlay>(), true, true);
    push_document(std::make_unique<TouchControls>(), false, true);
    return true;
}

bool initialized() noexcept {
    return sInitialized && aurora::rmlui::is_initialized() && aurora::rmlui::get_context();
}

void shutdown() noexcept {
    theme::detach();
    aurora::input::unregister_layer(sMenuLayer);
    sMenuLayer = aurora::input::kInvalidLayerId;
    borealis::ui::shutdown();
    localization::shutdown();
    g_pc_paused = 0;
    sWasPausingGame = false;
    sDisplayScale = 0.0f;
    sInitialized = false;
}

void handle_event(const SDL_Event& event) noexcept {
    if (!initialized()) {
        return;
    }
    borealis::ui::handle_event(event);
    sync_pause_state();
}

void update() noexcept {
    if (!initialized()) {
        return;
    }
    const float displayScale = aurora_get_window_size().scale;
    if (displayScale != sDisplayScale) {
        sDisplayScale = displayScale;
        borealis::ui::apply_scale();
    }
    borealis::ui::update();
    theme::update();
    sync_pause_state();
}

bool dispatching_controller_input() noexcept {
    return sControllerInput;
}
} // namespace acgc::ui
