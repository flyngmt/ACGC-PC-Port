#pragma once

#include <RmlUi/Core.h>
#include <SDL3/SDL_events.h>

#include <borealis/ui/ui.hpp>

#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace acgc::ui {

inline constexpr borealis::ui::DocumentScope kScopePrelaunch = borealis::ui::kScopeUser;
inline constexpr borealis::ui::DocumentScope kScopeOverlay = borealis::ui::kScopeUser + 1;

bool initialize() noexcept;
bool initialized() noexcept;
void shutdown() noexcept;
void handle_event(const SDL_Event& event) noexcept;
void update() noexcept;
bool dispatching_controller_input() noexcept;

} // namespace acgc::ui
