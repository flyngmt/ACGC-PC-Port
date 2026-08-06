#pragma once

#include "types.h"

#include <PR/gbi.h>

#include <array>
#include <vector>

namespace acgc::emu64_geometry_cache {

enum Layout : u32 {
    Lighting = 1,
    Textured = 2,
    LayoutCount = 4,
};

struct Entry {
    u64 commandHash = 0;
    std::vector<u32> commandWords;
    std::vector<u8> sourceVertices;
    std::vector<u8> compactIndices;
    u16 vertexCount = 0;
    std::array<std::vector<u8>, LayoutCount> displayLists;
};

const Entry* find_or_compile(const Gfx* source, u32 commandCount,
                             u32 vertexCount, u32 layout);

} // namespace acgc::emu64_geometry_cache
