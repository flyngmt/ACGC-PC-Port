#pragma once

#include <aurora/input.hpp>
#include <dolphin/types.h>

namespace acgc::controller_ports {

void initialize();
void shutdown();
void enforce_single_port();
void update();

bool auto_assign();
void select_automatic();
void select_none();
void select_controller(aurora::input::SourceId source);

} // namespace acgc::controller_ports
