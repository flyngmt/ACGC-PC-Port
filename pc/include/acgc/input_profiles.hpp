#pragma once
#include <aurora/pad.hpp>
#include <string_view>
#include <vector>

namespace acgc::input {
struct KeyboardDefault {
    std::string_view legacyKey;
    aurora::binding::ControlId control;
    SDL_Scancode key;
    float scale = 1.f;
};

const std::vector<KeyboardDefault>& keyboard_defaults();
void register_defaults();
bool save_profiles();
} // namespace acgc::input

namespace acgc::input {
std::vector<aurora::binding::Binding> editable_bindings(aurora::pad::ProfileTarget target,
                                                        aurora::binding::ControlId control, int direction);
bool replace_binding(aurora::pad::ProfileTarget target, aurora::binding::ControlId control, int direction,
                     aurora::binding::PhysicalInput physical, aurora::pad::ConflictPolicy policy);
} // namespace acgc::input
