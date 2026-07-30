#include "acgc/ui/ui.hpp"

#include "acgc/ui/document.hpp"
#include "acgc/ui/input.hpp"
#include "acgc/ui/menu_bar.hpp"

#include <aurora/rmlui.hpp>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_video.h>
#include "extern/aurora/lib/window.hpp"

#include "port/logging.h"

#include <algorithm>
#include <array>
#include <filesystem>
#include <ranges>
#include <span>
#include <unordered_set>

extern "C" {
extern int g_pc_paused;
extern int g_pc_pause_input_drain;
extern int g_pc_nes_active;
}

namespace acgc::ui {
namespace {

bool sInitialized = false;
bool sWasPausingGame = false;
std::vector<std::unique_ptr<Document>> sDocumentStack;

struct ScopedStyles {
    DocumentScope scope;
    std::string id;
    Rml::SharedPtr<Rml::StyleSheetContainer> sheet;
};
std::vector<ScopedStyles> sScopedStyles;

std::vector<const Rml::StyleSheetContainer*> scoped_sheets(DocumentScope scope)
{
    std::vector<const Rml::StyleSheetContainer*> sheets;
    for (const auto& entry : sScopedStyles) {
        if (entry.scope == scope) {
            sheets.push_back(entry.sheet.get());
        }
    }
    return sheets;
}

void restyle_scope(DocumentScope scope)
{
    const auto sheets = scoped_sheets(scope);
    for (auto& document : sDocumentStack) {
        if (document && document->scope() == scope && !document->closed()) {
            document->restyle(sheets);
        }
    }
}

bool load_host_font()
{
#if defined(_WIN32)
    constexpr std::array candidates{
        "C:/Windows/Fonts/segoeui.ttf",
        "C:/Windows/Fonts/arial.ttf",
    };
#elif defined(__APPLE__)
    constexpr std::array candidates{
        "/System/Library/Fonts/SFNSRounded.ttf",
        "/System/Library/Fonts/SFNS.ttf",
        "/System/Library/Fonts/Supplemental/Arial.ttf",
    };
#elif defined(__ANDROID__)
    constexpr std::array candidates{
        "/system/fonts/Roboto-Regular.ttf",
        "/system/fonts/NotoSans-Regular.ttf",
    };
#else
    constexpr std::array candidates{
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation2/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/freefont/FreeSans.ttf",
    };
#endif

    for (const char* path : candidates) {
        std::error_code error;
        if (!std::filesystem::is_regular_file(path, error)) {
            continue;
        }
        if (Rml::LoadFontFace(path, "ACGC UI", Rml::Style::FontStyle::Normal,
                              Rml::Style::FontWeight::Normal, true)) {
            Rml::LoadFontFace(path, "ACGC UI", Rml::Style::FontStyle::Normal,
                              Rml::Style::FontWeight::Bold, false);
            port_log_printf(LOG_INFO, "acgc::ui", "Loaded host UI font: %s", path);
            return true;
        }
    }
    port_log_printf(LOG_ERROR, "acgc::ui", "No usable host font was found");
    return false;
}

void sync_pause_state()
{
    const bool shouldPause = any_document_visible() && g_pc_nes_active == 0;
    if (sWasPausingGame != shouldPause) {
        port_log_printf(LOG_INFO, "acgc::ui", "Host menu %s; gameplay %s",
                        shouldPause ? "opened" : "closed",
                        shouldPause ? "paused" : "resumed");
    }
    if (sWasPausingGame && !shouldPause) {
        g_pc_pause_input_drain = 1;
    }
    g_pc_paused = shouldPause ? 1 : 0;
    sWasPausingGame = shouldPause;
}

} // namespace

bool initialize() noexcept
{
    if (sInitialized) {
        return true;
    }
    if (!aurora::rmlui::is_initialized() || !load_host_font()) {
        return false;
    }

    sInitialized = true;
    push_document(std::make_unique<MenuBar>(), false);
    port_log_printf(LOG_INFO, "acgc::ui", "Aurora RmlUi host menu initialized");
    return true;
}

void shutdown() noexcept
{
    sDocumentStack.clear();
    sScopedStyles.clear();
    input::reset_input_state();
    input::release_input_block();
    g_pc_paused = 0;
    sWasPausingGame = false;
    sInitialized = false;
}

void handle_event(const SDL_Event& event) noexcept
{
    if (!sInitialized || !aurora::rmlui::is_initialized()) {
        return;
    }

    // Escape is the desktop equivalent of Bacopa's menu command. Once a
    // document is open, it remains a normal Cancel event handled by RmlUi.
    if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat && event.key.key == SDLK_ESCAPE &&
        !any_document_visible()) {
        if (auto* context = aurora::rmlui::get_context()) {
            context->ProcessKeyDown(kMenuKey, 0);
            context->ProcessKeyUp(kMenuKey, 0);
        }
    }

    input::handle_event(event);
    input::sync_input_block();
    sync_pause_state();
}

void update() noexcept
{
    if (!sInitialized || !aurora::rmlui::is_initialized()) {
        return;
    }

    input::update_input();
    const std::size_t count = sDocumentStack.size();
    for (std::size_t i = 0; i < count && i < sDocumentStack.size(); ++i) {
        if (auto* document = sDocumentStack[i].get(); document && !document->closed()) {
            document->update();
        }
    }

    const auto [first, last] = std::ranges::remove_if(sDocumentStack, [](const auto& document) {
        return document->closed();
    });
    sDocumentStack.erase(first, last);

    if (auto* context = aurora::rmlui::get_context(); context &&
        (context->GetFocusElement() == nullptr || context->GetFocusElement() == context->GetRootElement())) {
        for (auto& document : std::views::reverse(sDocumentStack)) {
            if (document->active() && document->focus()) {
                break;
            }
        }
    }

    input::sync_input_block();
    sync_pause_state();
}

Document& push_document(std::unique_ptr<Document> document, bool show) noexcept
{
    Document& result = *document;
    sDocumentStack.push_back(std::move(document));
    if (show) {
        result.show();
    }
    input::sync_input_block();
    sync_pause_state();
    return result;
}

void uncover_top_document() noexcept
{
    if (auto* document = top_document()) {
        document->uncover();
    }
    input::sync_input_block();
    sync_pause_state();
}

bool any_document_visible() noexcept
{
    return std::ranges::any_of(sDocumentStack, [](const auto& document) {
        return document && document->visible();
    });
}

Document* top_document() noexcept
{
    for (auto& document : std::views::reverse(sDocumentStack)) {
        if (document->active()) {
            return document.get();
        }
    }
    return nullptr;
}

bool game_obscured_below(const Document& document) noexcept
{
    for (const auto& entry : sDocumentStack) {
        if (entry.get() == &document) {
            break;
        }
        if (entry->active() && entry->obscures_game()) {
            return true;
        }
    }
    return false;
}

std::vector<std::unique_ptr<Document>>& get_document_stack() noexcept
{
    return sDocumentStack;
}

bool register_scoped_styles(DocumentScope scope, std::string id, const std::string& rcss) noexcept
{
    auto sheet = Rml::Factory::InstanceStyleSheetString(rcss);
    if (!sheet) {
        return false;
    }
    const auto found = std::ranges::find_if(sScopedStyles, [scope, &id](const ScopedStyles& entry) {
        return entry.scope == scope && entry.id == id;
    });
    if (found != sScopedStyles.end()) {
        found->sheet = std::move(sheet);
    } else {
        sScopedStyles.push_back({scope, std::move(id), std::move(sheet)});
    }
    restyle_scope(scope);
    return true;
}

void unregister_scoped_styles(DocumentScope scope, std::string_view id) noexcept
{
    if (std::erase_if(sScopedStyles, [scope, id](const ScopedStyles& entry) {
        return entry.scope == scope && entry.id == id;
    }) != 0) {
        restyle_scope(scope);
    }
}

void apply_scoped_styles(Document& document) noexcept
{
    document.restyle(scoped_sheets(document.scope()));
}

std::filesystem::path resource_path(const std::filesystem::path& filename) noexcept
{
    return std::filesystem::path("res") / filename;
}

std::string escape(std::string_view value) noexcept
{
    std::string result;
    result.reserve(value.size());
    for (char c : value) {
        switch (c) {
        case '&': result += "&amp;"; break;
        case '<': result += "&lt;"; break;
        case '>': result += "&gt;"; break;
        case '"': result += "&quot;"; break;
        default: result += c; break;
        }
    }
    return result;
}

Rml::Element* append(Rml::Element* parent, const Rml::String& tag) noexcept
{
    if (!parent || !parent->GetOwnerDocument()) {
        return nullptr;
    }
    return parent->AppendChild(parent->GetOwnerDocument()->CreateElement(tag));
}

Rml::Element* append_text(Rml::Element* parent, const Rml::String& text) noexcept
{
    if (!parent || !parent->GetOwnerDocument()) {
        return nullptr;
    }
    return parent->AppendChild(parent->GetOwnerDocument()->CreateTextNode(text));
}

NavCommand map_nav_event(const Rml::Event& event) noexcept
{
    const auto key = static_cast<Rml::Input::KeyIdentifier>(
        event.GetParameter<int>("key_identifier", Rml::Input::KI_UNKNOWN));
    switch (key) {
    case Rml::Input::KI_UP: return NavCommand::Up;
    case Rml::Input::KI_DOWN: return NavCommand::Down;
    case Rml::Input::KI_LEFT: return NavCommand::Left;
    case Rml::Input::KI_RIGHT: return NavCommand::Right;
    case Rml::Input::KI_ESCAPE: return NavCommand::Cancel;
    case Rml::Input::KI_RETURN:
    case Rml::Input::KI_NUMPADENTER: return NavCommand::Confirm;
    case kMenuKey: return NavCommand::Menu;
    case Rml::Input::KI_NEXT: return NavCommand::Next;
    case Rml::Input::KI_PRIOR: return NavCommand::Previous;
    default: return NavCommand::None;
    }
}

Insets safe_area_insets(Rml::Context* context) noexcept
{
    if (!context || !aurora::window::get_sdl_window()) {
        return {};
    }
    const AuroraWindowSize size = aurora::window::get_window_size();
    if (size.width == 0 || size.height == 0) {
        return {};
    }
    SDL_Rect safe{};
    if (!SDL_GetWindowSafeArea(aurora::window::get_sdl_window(), &safe)) {
        return {};
    }
    const auto dimensions = context->GetDimensions();
    const float scaleX = static_cast<float>(dimensions.x) / static_cast<float>(size.width);
    const float scaleY = static_cast<float>(dimensions.y) / static_cast<float>(size.height);
    return {
        std::max(0.0f, static_cast<float>(safe.y)) * scaleY,
        std::max(0.0f, static_cast<float>(size.width - safe.x - safe.w)) * scaleX,
        std::max(0.0f, static_cast<float>(size.height - safe.y - safe.h)) * scaleY,
        std::max(0.0f, static_cast<float>(safe.x)) * scaleX,
    };
}

} // namespace acgc::ui
