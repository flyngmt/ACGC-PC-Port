#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace acgc::text {

int decode(std::string_view text, size_t& consumed);
std::string_view encode(uint8_t code);

} // namespace acgc::text
