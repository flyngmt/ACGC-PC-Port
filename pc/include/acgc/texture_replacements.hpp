#pragma once

#include <cstddef>
#include <filesystem>

namespace acgc::texture_replacements {

const std::filesystem::path& directory();
std::size_t registration_count();
void reload();
void shutdown();

} // namespace acgc::texture_replacements
