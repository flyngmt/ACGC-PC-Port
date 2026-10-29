#include "acgc/controller_ports.hpp"
#include "acgc/config.hpp"
#include "acgc/settings.hpp"
#include "acgc/input_profiles.hpp"
#include "acgc/legacy_input.hpp"
#include <SDL3/SDL_keyboard.h>
#include <borealis/log.hpp>

namespace acgc::controller_ports {
namespace {

constexpr borealis::Log Log{ "acgc::input" };
aurora::input::LayerId sLayer = aurora::input::kInvalidLayerId;
aurora::input::SourceId sController = aurora::input::kInvalidSourceId;

void assign(aurora::input::SourceId source) {
    if (!aurora::pad::set_port_controller(0, source)) {
        return;
    }
    apply_legacy_controller_input(source);
    apply_runtime_settings(false);
    input::save_profiles();
    sController = source;
}

aurora::input::EventResult on_event(const aurora::input::InputEvent& event, void*) {
    const auto* button = event.payload.get_if<aurora::input::InputEvent::ButtonChanged>();
    if (button && button->pressed && event.source.kind == aurora::input::InputSource::Kind::Controller &&
        event.source.origin == aurora::input::InputSource::Origin::Physical && auto_assign() &&
        !aurora::pad::port_controller(0)) {
        assign(event.source.id);
        Log.info("Assigned controller to player 1 after a button press");
    }
    return aurora::input::EventResult::Pass;
}

} // namespace

void initialize() {
    for (u32 port = 1; port < PAD_CHANMAX; ++port) {
        aurora::pad::clear_port(port);
        aurora::pad::clear_bindings(aurora::pad::ProfileTarget::keyboard(port));
    }
    auto& inputSettings = settings().input;
    if (!inputSettings.singlePortMigrated.value()) {
        aurora::pad::clear_port(0);
        inputSettings.singlePortMigrated.set_value(true);
        config::save();
    }
    // Aurora Auto assigns immediately. This port waits for a fresh button press.
    if (aurora::pad::port_preference(0).state == aurora::pad::PortAssignment::Auto) {
        aurora::pad::clear_port(0);
    }
    if (sLayer == aurora::input::kInvalidLayerId) {
        sLayer = aurora::input::register_layer({
            .label = "acgc.controller-claim",
            .priority = aurora::input::kRmlUiLayerPriority + 2,
            .onEvent = on_event,
        });
    }
    update();
    input::save_profiles();
}

void shutdown() {
    aurora::input::unregister_layer(sLayer);
    sLayer = aurora::input::kInvalidLayerId;
    sController = aurora::input::kInvalidSourceId;
}

void enforce_single_port() {
    for (u32 port = 1; port < PAD_CHANMAX; ++port) {
        if (aurora::pad::port_preference(port).state != aurora::pad::PortAssignment::None) {
            aurora::pad::clear_port(port);
        }
    }
}

void update() {
    enforce_single_port();
    for (const auto& source : aurora::input::sources()) {
        if (source.kind == aurora::input::InputSource::Kind::Controller) {
            apply_legacy_controller_input(source.id);
        }
    }
    const auto current = aurora::pad::port_controller(0);
    if (sController != current) {
        sController = current;
        apply_runtime_settings(false);
    }
}

bool auto_assign() {
    return settings().input.autoAssignController.value() || !SDL_HasKeyboard();
}

void select_automatic() {
    aurora::pad::clear_port(0);
    settings().input.autoAssignController.set_value(true);
    config::save();
    input::save_profiles();
}

void select_none() {
    aurora::pad::clear_port(0);
    settings().input.autoAssignController.set_value(false);
    config::save();
    input::save_profiles();
}

void select_controller(aurora::input::SourceId source) {
    assign(source);
    settings().input.autoAssignController.set_value(true);
    config::save();
}

} // namespace acgc::controller_ports
