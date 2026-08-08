#pragma once

#include <cstdint>

namespace acgc {

enum class InputBlockReason : std::uint32_t {
	HostUi = 1u << 0u,
	GameTyping = 1u << 1u,
};

void set_input_blocked(InputBlockReason reason, bool blocked) noexcept;

} // namespace acgc
