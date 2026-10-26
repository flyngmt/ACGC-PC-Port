#pragma once

#include "nav_types.hpp"

union SDL_Event;

namespace acgc::ui::input {

void register_input_layer() noexcept;
void unregister_input_layer() noexcept;
void handle_event(const SDL_Event& event) noexcept;
void update_input() noexcept;
void reset_input_state() noexcept;
void sync_input_block() noexcept;
void release_input_block() noexcept;
bool is_dispatching_controller_key() noexcept;

} // namespace acgc::ui::input
