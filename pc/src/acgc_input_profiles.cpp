#include "acgc/input_profiles.hpp"
#include <borealis/log.hpp>

namespace acgc::input {

const std::vector<KeyboardDefault>& keyboard_defaults() {
    const auto& c = aurora::pad::controls();
    static const std::vector<KeyboardDefault> defaults{
        { "A", c.a, SDL_SCANCODE_SPACE },
        { "B", c.b, SDL_SCANCODE_LSHIFT },
        { "X", c.x, SDL_SCANCODE_X },
        { "Y", c.y, SDL_SCANCODE_Y },
        { "Start", c.start, SDL_SCANCODE_RETURN },
        { "Z", c.z, SDL_SCANCODE_Z },
        { "L", c.l, SDL_SCANCODE_Q },
        { "R", c.r, SDL_SCANCODE_E },
        { "DPad_Up", c.up, SDL_SCANCODE_I },
        { "DPad_Down", c.down, SDL_SCANCODE_K },
        { "DPad_Left", c.left, SDL_SCANCODE_J },
        { "DPad_Right", c.right, SDL_SCANCODE_L },
        { "Stick_Right", c.leftX, SDL_SCANCODE_D },
        { "Stick_Left", c.leftX, SDL_SCANCODE_A, -1.f },
        { "Stick_Up", c.leftY, SDL_SCANCODE_W },
        { "Stick_Down", c.leftY, SDL_SCANCODE_S, -1.f },
        { "CStick_Right", c.rightX, SDL_SCANCODE_RIGHT },
        { "CStick_Left", c.rightX, SDL_SCANCODE_LEFT, -1.f },
        { "CStick_Up", c.rightY, SDL_SCANCODE_UP },
        { "CStick_Down", c.rightY, SDL_SCANCODE_DOWN, -1.f },
        { "L", c.triggerL, SDL_SCANCODE_Q },
        { "R", c.triggerR, SDL_SCANCODE_E },
    };
    return defaults;
}

void register_defaults() {
    std::vector<aurora::binding::Binding> bindings;
    for (const auto& entry : keyboard_defaults()) {
        bindings.push_back({
            .input = { .control = aurora::binding::PhysicalInput::Key{ entry.key } },
            .target = entry.control,
            .scale = entry.scale,
        });
    }
    aurora::pad::set_default_keyboard_bindings(0, std::move(bindings));
}

bool save_profiles() {
    if (aurora::pad::save_profiles()) {
        return true;
    }
    constexpr borealis::Log Log{ "acgc::input" };
    Log.error("Could not save input profiles; changes will be lost on restart");
    return false;
}

std::vector<aurora::binding::Binding> editable_bindings(aurora::pad::ProfileTarget target,
                                                        aurora::binding::ControlId control, int direction) {
    using Axis = aurora::binding::PhysicalInput::GamepadAxis;
    auto bindings = aurora::pad::bindings_for_control(target, control);
    if (direction == 0) {
        return bindings;
    }
    std::vector<aurora::binding::Binding> result;
    for (auto binding : bindings) {
        if (auto* axis = std::get_if<Axis>(&binding.input.control.value);
            axis && axis->direction == Axis::Direction::Full) {
            axis->direction = Axis::Direction::Positive;
            result.push_back(binding);
            axis->direction = Axis::Direction::Negative;
            binding.scale = -binding.scale;
        }
        result.push_back(std::move(binding));
    }
    return result;
}

bool append_binding(aurora::pad::ProfileTarget target, aurora::binding::ControlId control, int direction,
                    aurora::binding::PhysicalInput physical, aurora::pad::ConflictPolicy policy) {
    auto bindings = editable_bindings(target, control, direction);
    physical.source = 0; // Profiles resolve source IDs at runtime.
    const float scale = direction < 0 ? -1.f : 1.f;
    for (const auto& binding : bindings) {
        if (aurora::binding::same_input(binding.input, physical) && binding.scale == scale) {
            return true;
        }
    }
    const aurora::binding::Binding binding{
        .input = physical,
        .target = control,
        .scale = scale,
    };
    if (!aurora::pad::rebind(target, control, binding, policy)) {
        return false;
    }
    bindings.push_back(binding);
    return aurora::pad::set_binding(target, control, std::move(bindings));
}

} // namespace acgc::input
