#include "acgc/ui/ui.hpp"

#include "acgc/ui/document.hpp"
#include "acgc/ui/input.hpp"
#include "acgc/ui/menu_bar.hpp"
#include "acgc/ui/overlay.hpp"

#include <aurora/rmlui.hpp>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_video.h>
#include "extern/aurora/lib/window.hpp"

#include "borealis/io.hpp"
#include "borealis/log.hpp"

#include <algorithm>
#include <filesystem>
#include <ranges>
#include <span>
#include <unordered_set>

constexpr borealis::Log Log{"acgc::ui"};

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
std::vector<std::unique_ptr<Document>> sPassiveDocuments;

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
    const auto restyle_documents = [&sheets, scope](auto& documents) {
        for (auto& document : documents) {
            if (document && document->scope() == scope && !document->closed()) {
                document->restyle(sheets);
            }
        }
    };
    restyle_documents(sDocumentStack);
    restyle_documents(sPassiveDocuments);
}

bool load_ui_fonts()
{
    const std::string bodyPath = borealis::io::fs_path_to_string(
        resource_path("fonts/FOT-SeuratPro-B.otf"));
    const std::string headingPath = borealis::io::fs_path_to_string(
        resource_path("fonts/FOT-RodinBokutohPro-EB.otf"));
    const std::string symbolsPath = borealis::io::fs_path_to_string(
        resource_path("fonts/MaterialSymbolsRounded-Regular.ttf"));

    const bool bodyLoaded = Rml::LoadFontFace(
        bodyPath, "ACGC Body", Rml::Style::FontStyle::Normal,
        Rml::Style::FontWeight::Normal, true);
    const bool bodyBoldLoaded = Rml::LoadFontFace(
        bodyPath, "ACGC Body", Rml::Style::FontStyle::Normal,
        Rml::Style::FontWeight::Bold, false);
    const bool headingLoaded = Rml::LoadFontFace(
        headingPath, "ACGC Heading", Rml::Style::FontStyle::Normal,
        Rml::Style::FontWeight::Bold, false);
    const bool symbolsLoaded = Rml::LoadFontFace(
        symbolsPath, "Material Symbols Rounded", Rml::Style::FontStyle::Normal,
        Rml::Style::FontWeight::Normal, false);
    if (!bodyLoaded || !bodyBoldLoaded || !headingLoaded || !symbolsLoaded) {
        Log.error("Could not load the bundled Animal Crossing UI fonts");
        return false;
    }

    Log.info("Loaded bundled Animal Crossing UI fonts");
    return true;
}

void sync_pause_state()
{
    const bool shouldPause = any_document_visible() && g_pc_nes_active == 0;
    if (sWasPausingGame != shouldPause) {
        Log.info("Host menu {}; gameplay {}",
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
    if (!aurora::rmlui::is_initialized() || !load_ui_fonts()) {
        return false;
    }

    sInitialized = true;
    push_document(std::make_unique<MenuBar>(), false);
    push_document(std::make_unique<Overlay>());
    Log.info("Aurora RmlUi host menu initialized");
    return true;
}

void shutdown() noexcept
{
    sDocumentStack.clear();
    sPassiveDocuments.clear();
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

    if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat && event.key.key == SDLK_F1 &&
        !any_document_visible() && !sWasPausingGame) {
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
    const auto updateDocuments = [](auto& documents) {
        const std::size_t count = documents.size();
        for (std::size_t i = 0; i < count && i < documents.size(); ++i) {
            if (auto* document = documents[i].get(); document && !document->closed()) {
                document->update();
            }
        }
    };
    updateDocuments(sDocumentStack);
    updateDocuments(sPassiveDocuments);

    const auto [first, last] = std::ranges::remove_if(sDocumentStack, [](const auto& document) {
        return document->closed();
    });
    sDocumentStack.erase(first, last);
    const auto [passiveFirst, passiveLast] =
        std::ranges::remove_if(sPassiveDocuments, [](const auto& document) {
            return document->closed();
        });
    sPassiveDocuments.erase(passiveFirst, passiveLast);

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
    if (result.passive()) {
        sPassiveDocuments.push_back(std::move(document));
    } else {
        sDocumentStack.push_back(std::move(document));
    }
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
