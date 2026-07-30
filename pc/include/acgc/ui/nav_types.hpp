#pragma once

namespace acgc::ui {

enum class NavCommand {
	None,
	Up,
	Down,
	Left,
	Right,
	Next,     // R1
	Previous, // L1
	Confirm,  // A
	Cancel,   // B
	Menu,     // Back/Minus, or R + Start
};

} // namespace acgc::ui
