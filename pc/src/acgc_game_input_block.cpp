#include "acgc/game_input_block.hpp"

#include <dolphin/pad.h>

#include <type_traits>

namespace acgc {
namespace {

using ReasonMask = std::underlying_type_t<InputBlockReason>;

ReasonMask sReasons = 0;
bool sBlocked = false;

} // namespace

void set_input_blocked(InputBlockReason reason, bool blocked) noexcept
{
	const ReasonMask bit = static_cast<ReasonMask>(reason);
	if (blocked) {
		sReasons |= bit;
	} else {
		sReasons &= ~bit;
	}

	const bool shouldBlock = sReasons != 0;
	if (sBlocked != shouldBlock) {
		PADBlockInput(shouldBlock);
		sBlocked = shouldBlock;
	}
}

} // namespace acgc
