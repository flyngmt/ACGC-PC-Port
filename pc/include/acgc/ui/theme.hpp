#pragma once

#include <RmlUi/Core/Types.h>

namespace Rml {
class Context;
}

namespace acgc::ui::theme {

void attach(Rml::Context* context) noexcept;
void detach() noexcept;
void update() noexcept;
void debug_toggle() noexcept;
Rml::Colourb background() noexcept;

} // namespace acgc::ui::theme
