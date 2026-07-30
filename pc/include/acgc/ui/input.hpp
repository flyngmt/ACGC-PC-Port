#pragma once

#include "nav_types.hpp"

union SDL_Event;

namespace acgc::ui::input {

void handle_event(const SDL_Event& event) noexcept;
void update_input() noexcept;
void reset_input_state() noexcept;
void sync_input_block() noexcept;
void release_input_block() noexcept;

} // namespace acgc::ui::input
