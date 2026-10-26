#pragma once

#include <RmlUi/Core.h>
#include <SDL3/SDL_events.h>

#include "nav_types.hpp"

#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace acgc::ui {

class Document;

enum class DocumentScope {
    None,
    Window,
    MenuBar,
    Prelaunch,
    Overlay,
};

// Animal Crossing does not currently expose host-menu sound hooks, but the
// component layer keeps Bacopa's sound boundary intact for future wiring.
constexpr inline std::uint32_t kSoundClick = 0;
constexpr inline std::uint32_t kSoundBindingChanged = 0;
constexpr inline std::uint32_t kSoundMenuOpen = 0;
constexpr inline std::uint32_t kSoundMenuClose = 0;
constexpr inline std::uint32_t kSoundWindowOpen = 0;
constexpr inline std::uint32_t kSoundWindowClose = 0;
constexpr inline std::uint32_t kSoundTabChanged = 0;
constexpr inline std::uint32_t kSoundItemFocus = 0;
constexpr inline std::uint32_t kSoundItemChange = 0;
constexpr inline std::uint32_t kSoundItemEnable = 0;
constexpr inline std::uint32_t kSoundItemDisable = 0;
inline void play_menu_sound(std::uint32_t) noexcept {}

// Internal sentinel used for controller, touch, and menu-command dispatch.
// Physical keyboard shortcuts are translated to this key before dispatch.
constexpr inline Rml::Input::KeyIdentifier kMenuKey = Rml::Input::KI_F24;

struct Insets {
    float top = 0.0f;
    float right = 0.0f;
    float bottom = 0.0f;
    float left = 0.0f;

    bool operator==(const Insets& other) const noexcept = default;
};

bool initialize() noexcept;
bool initialized() noexcept;
void shutdown() noexcept;
void handle_event(const SDL_Event& event) noexcept;
void update() noexcept;

Document& push_document(std::unique_ptr<Document> document, bool show = true) noexcept;
void uncover_top_document() noexcept;
bool any_document_visible() noexcept;
Document* top_document() noexcept;
bool game_obscured_below(const Document& document) noexcept;
std::vector<std::unique_ptr<Document>>& get_document_stack() noexcept;

bool register_scoped_styles(DocumentScope scope, std::string id, const std::string& rcss) noexcept;
void unregister_scoped_styles(DocumentScope scope, std::string_view id) noexcept;
void apply_scoped_styles(Document& document) noexcept;

std::filesystem::path resource_path(const std::filesystem::path& filename) noexcept;
std::string escape(std::string_view value) noexcept;
Rml::Element* append(Rml::Element* parent, const Rml::String& tag) noexcept;
Rml::Element* append_text(Rml::Element* parent, const Rml::String& text) noexcept;
NavCommand map_nav_event(const Rml::Event& event) noexcept;
Insets safe_area_insets(Rml::Context* context) noexcept;

} // namespace acgc::ui
