#pragma once

#include <dolphin/types.h>

namespace acgc::controller_ports {

void initialize();
void enforce_single_port();
void update();

bool auto_assign();
void select_automatic();
void select_none();
void select_controller(u32 index);

} // namespace acgc::controller_ports
