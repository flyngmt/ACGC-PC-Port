#pragma once

#include "types.h"

#include <PR/gbi.h>

#include <cstddef>
#include <vector>

namespace acgc::emu64_geometry_cache {

struct Entry {
    u64 commandHash = 0;
    std::vector<u32> commandWords;
    std::vector<u8> sourceVertices;
    std::vector<u16> indices;
};

struct Stats {
    u64 fastHits = 0;
    u64 contentHits = 0;
    u64 misses = 0;
    u64 evictions = 0;
    size_t entryCount = 0;
    size_t byteSize = 0;
};

const Entry* find_or_compile(const Gfx* source, u32 commandCount, u32 vertexCount);
Stats stats();
void clear();

} // namespace acgc::emu64_geometry_cache
