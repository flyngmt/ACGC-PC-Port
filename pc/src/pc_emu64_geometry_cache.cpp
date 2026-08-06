#include "pc_emu64_geometry_cache.hpp"

#include "libforest/gbi_extensions.h"

#include <dolphin/gx.h>
#include <xxhash.h>

#include <array>
#include <cstring>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace acgc::emu64_geometry_cache {
namespace {

constexpr u32 MaxCacheEntries = 32768;
constexpr u32 MaxCommandCount = 4096;
constexpr u32 FastLookupCount = 4096;
constexpr u32 Emu64VertexCount = 128;

std::vector<std::unique_ptr<Entry>> s_entries;
std::unordered_multimap<u64, Entry*> s_entriesByHash;
thread_local std::unique_ptr<XXH3_state_t, decltype(&XXH3_freeState)>
    s_hashState{XXH3_createState(), XXH3_freeState};

struct FastLookup {
    const Gfx* source = nullptr;
    u32 commandCount = 0;
    Entry* entry = nullptr;
};

std::array<FastLookup, FastLookupCount> s_fastLookups;

u64 hash_source_commands(const Gfx* source, u32 commandCount) {
    if (!s_hashState ||
        XXH3_64bits_reset(s_hashState.get()) == XXH_ERROR) {
        return 0;
    }
    for (u32 command = 0; command < commandCount; ++command) {
        const std::array<u32, 2> words = {
            source[command].words.w0,
            source[command].words.w1,
        };
        if (XXH3_64bits_update(s_hashState.get(), words.data(),
                              sizeof(words)) == XXH_ERROR) {
            return 0;
        }
    }
    return XXH3_64bits_digest(s_hashState.get());
}

bool source_matches_entry(const Gfx* source, u32 commandCount, const Entry& entry) {
    if (entry.commandWords.size() != static_cast<size_t>(commandCount) * 2) {
        return false;
    }
    for (u32 command = 0; command < commandCount; ++command) {
        if (source[command].words.w0 != entry.commandWords[command * 2] ||
            source[command].words.w1 != entry.commandWords[command * 2 + 1]) {
            return false;
        }
    }
    return true;
}

void append_triangle(std::vector<u32>& vertices, u32 v0, u32 v1, u32 v2) {
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
}

bool collect_standard_triangles(const Gfx* source, u32 commandCount,
                                std::vector<u32>& vertices) {
    for (u32 command = 0; command < commandCount; ++command) {
        const u8 opcode = static_cast<u8>(source[command].words.w0 >> 24);
        if (opcode == G_TRI2) {
            Gtri2 triangles{};
            std::memcpy(&triangles, &source[command].words, sizeof(triangles));
            append_triangle(vertices, triangles.t0v0 / 2, triangles.t0v1 / 2,
                            triangles.t0v2 / 2);
            append_triangle(vertices, triangles.t1v0 / 2, triangles.t1v1 / 2,
                            triangles.t1v2 / 2);
        } else if (opcode == G_TRI1) {
            Gtri1 triangle{};
            std::memcpy(&triangle, &source[command].words, sizeof(triangle));
            append_triangle(vertices, triangle.v0 / 2, triangle.v1 / 2,
                            triangle.v2 / 2);
        } else {
            return false;
        }
    }
    return true;
}

bool collect_packed_triangles(const Gfx* source, u32 commandCount,
                              std::vector<u32>& vertices) {
    const u32 faceCount = ((source[0].words.w0 >> 17) & 0x7F) + 1;
    const bool sevenBit =
        (source[0].words.w1 & POLY_BITMASK) == POLY_7b;
    u32 remaining = faceCount;
    u32 consumed = 0;

    while (consumed < commandCount && remaining != 0) {
        const Gfx* command = &source[consumed];
        const bool commandSevenBit =
            (command->words.w1 & POLY_BITMASK) == POLY_7b;
        if (commandSevenBit != sevenBit) {
            return false;
        }

        if (!sevenBit) {
            const u32 packed[] = {
                POLY_GET_V0_5b(command), POLY_GET_V1_5b(command), POLY_GET_V2_5b(command),
                POLY_GET_V3_5b(command), POLY_GET_V4_5b(command), POLY_GET_V5_5b(command),
                POLY_GET_V6_5b(command), POLY_GET_V7_5b(command), POLY_GET_V8_5b(command),
                POLY_GET_V9_5b(command), POLY_GET_V10_5b(command), POLY_GET_V11_5b(command),
            };
            const u32 availableFaces = consumed == 0 ? 3 : 4;
            const u32 emittedFaces =
                remaining < availableFaces ? remaining : availableFaces;
            for (u32 face = 0; face < emittedFaces; ++face) {
                append_triangle(vertices, packed[face * 3], packed[face * 3 + 1],
                                packed[face * 3 + 2]);
            }
            remaining -= emittedFaces;
        } else {
            const u32 packed[] = {
                POLY_GET_V0_7b(command), POLY_GET_V1_7b(command), POLY_GET_V2_7b(command),
                POLY_GET_V3_7b(command), POLY_GET_V4_7b(command), POLY_GET_V5_7b(command),
                POLY_GET_V6_7b(command), POLY_GET_V7_7b(command), POLY_GET_V8_7b(command),
            };
            const u32 availableFaces = consumed == 0 ? 2 : 3;
            const u32 emittedFaces =
                remaining < availableFaces ? remaining : availableFaces;
            for (u32 face = 0; face < emittedFaces; ++face) {
                append_triangle(vertices, packed[face * 3], packed[face * 3 + 1],
                                packed[face * 3 + 2]);
            }
            remaining -= emittedFaces;
        }
        ++consumed;
    }

    return remaining == 0 && consumed == commandCount;
}

bool compile_topology(const Gfx* source, u32 commandCount, u32 vertexCount,
                      std::vector<u8>& sourceVertices,
                      std::vector<u8>& compactIndices) {
    if (source == nullptr || commandCount == 0 ||
        commandCount > MaxCommandCount || vertexCount == 0 ||
        vertexCount > 0xFFFF) {
        return false;
    }

    std::vector<u32> logicalVertices;
    logicalVertices.reserve(vertexCount);
    const u8 opcode = static_cast<u8>(source[0].words.w0 >> 24);
    bool parsed = false;
    if (opcode == G_TRI1 || opcode == G_TRI2) {
        parsed = collect_standard_triangles(source, commandCount, logicalVertices);
    } else if (opcode == G_TRIN || opcode == G_TRIN_INDEPEND) {
        parsed = collect_packed_triangles(source, commandCount, logicalVertices);
    }
    if (!parsed || logicalVertices.size() != vertexCount) {
        return false;
    }

    std::array<int, Emu64VertexCount> remap{};
    remap.fill(-1);
    sourceVertices.clear();
    compactIndices.clear();
    sourceVertices.reserve(vertexCount);
    compactIndices.reserve(vertexCount);

    for (u32 sourceVertex : logicalVertices) {
        if (sourceVertex >= Emu64VertexCount) {
            return false;
        }
        int compact = remap[sourceVertex];
        if (compact < 0) {
            compact = static_cast<int>(sourceVertices.size());
            remap[sourceVertex] = compact;
            sourceVertices.push_back(static_cast<u8>(sourceVertex));
        }
        compactIndices.push_back(static_cast<u8>(compact));
    }
    return true;
}

bool ensure_display_list(Entry& entry, u32 layout) {
    if (layout >= LayoutCount || entry.vertexCount == 0 ||
        entry.compactIndices.size() != entry.vertexCount ||
        entry.sourceVertices.empty()) {
        return false;
    }

    std::vector<u8>& list = entry.displayLists[layout];
    if (!list.empty()) {
        return true;
    }

    const bool lighting = (layout & Lighting) != 0;
    const bool textured = (layout & Textured) != 0;
    const u32 attributeCount =
        2 + (lighting ? 1 : 0) + (textured ? 1 : 0);
    list.reserve(3 + entry.compactIndices.size() * attributeCount);
    list.push_back(static_cast<u8>(GX_TRIANGLES) |
                   static_cast<u8>(GX_VTXFMT0));
    list.push_back(static_cast<u8>(entry.vertexCount >> 8));
    list.push_back(static_cast<u8>(entry.vertexCount));

    for (u8 index : entry.compactIndices) {
        list.push_back(index);
        if (lighting) {
            list.push_back(index);
        }
        list.push_back(index);
        if (textured) {
            list.push_back(index);
        }
    }
    return true;
}

std::unique_ptr<Entry> compile_entry(const Gfx* source, u32 commandCount,
                                     u32 vertexCount, u64 commandHash) {
    auto entry = std::make_unique<Entry>();
    if (!compile_topology(source, commandCount, vertexCount,
                          entry->sourceVertices, entry->compactIndices)) {
        return nullptr;
    }

    entry->commandHash = commandHash;
    entry->commandWords.reserve(static_cast<size_t>(commandCount) * 2);
    for (u32 command = 0; command < commandCount; ++command) {
        entry->commandWords.push_back(source[command].words.w0);
        entry->commandWords.push_back(source[command].words.w1);
    }
    entry->vertexCount = static_cast<u16>(vertexCount);
    return entry;
}

Entry* insert_entry(std::unique_ptr<Entry> entry) {
    Entry* result = entry.get();
    s_entries.push_back(std::move(entry));
    s_entriesByHash.emplace(result->commandHash, result);
    return result;
}

} // namespace

const Entry* find_or_compile(const Gfx* source, u32 commandCount,
                             u32 vertexCount, u32 layout) {
    if (source == nullptr || commandCount == 0 ||
        commandCount > MaxCommandCount || vertexCount == 0 ||
        vertexCount > 0xFFFF || layout >= LayoutCount) {
        return nullptr;
    }

    const u32 fastSlot =
        static_cast<u32>(reinterpret_cast<uintptr_t>(source) >> 3) &
        (FastLookupCount - 1);
    FastLookup& fast = s_fastLookups[fastSlot];
    if (fast.source == source && fast.commandCount == commandCount &&
        fast.entry != nullptr && fast.entry->vertexCount == vertexCount &&
        source_matches_entry(source, commandCount, *fast.entry)) {
        return ensure_display_list(*fast.entry, layout) ? fast.entry : nullptr;
    }

    const u64 hash = hash_source_commands(source, commandCount);
    const auto range = s_entriesByHash.equal_range(hash);
    for (auto it = range.first; it != range.second; ++it) {
        Entry* entry = it->second;
        if (entry->vertexCount == vertexCount &&
            source_matches_entry(source, commandCount, *entry)) {
            if (!ensure_display_list(*entry, layout)) {
                return nullptr;
            }
            fast = {source, commandCount, entry};
            return entry;
        }
    }

    if (s_entries.size() >= MaxCacheEntries) {
        return nullptr;
    }
    std::unique_ptr<Entry> compiled =
        compile_entry(source, commandCount, vertexCount, hash);
    if (!compiled) {
        return nullptr;
    }
    if (!ensure_display_list(*compiled, layout)) {
        return nullptr;
    }
    Entry* entry = insert_entry(std::move(compiled));
    fast = {source, commandCount, entry};
    return entry;
}

} // namespace acgc::emu64_geometry_cache
