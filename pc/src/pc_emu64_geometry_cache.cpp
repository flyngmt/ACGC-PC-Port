#include "pc_emu64_geometry_cache.hpp"

#include "libforest/gbi_extensions.h"

#include <xxhash.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

namespace acgc::emu64_geometry_cache {
namespace {

#ifndef ACGC_EMU64_GEOMETRY_CACHE_MAX_BYTES
#define ACGC_EMU64_GEOMETRY_CACHE_MAX_BYTES (16u * 1024u * 1024u)
#endif

constexpr size_t MaxCacheBytes = ACGC_EMU64_GEOMETRY_CACHE_MAX_BYTES;
constexpr size_t MaxCacheEntries = 32768;
constexpr u32 MaxCommandCount = 4096;
constexpr u32 FastLookupCount = 4096;
constexpr u32 Emu64VertexCount = 128;

using EntryList = std::list<Entry>;
using EntryIterator = EntryList::iterator;

EntryList s_entries;
std::unordered_multimap<u64, EntryIterator> s_entriesByHash;
size_t s_cacheBytes = 0;
Stats s_stats;
thread_local std::vector<u32> s_commandScratch;

struct FastLookup {
    const Gfx* source = nullptr;
    u32 commandCount = 0;
    Entry* entry = nullptr;
    EntryIterator iterator{};
};

std::array<FastLookup, FastLookupCount> s_fastLookups;

const std::vector<u32>& snapshot_source_commands(const Gfx* source, u32 commandCount) {
    s_commandScratch.resize(static_cast<size_t>(commandCount) * 2);
    for (u32 command = 0; command < commandCount; ++command) {
        s_commandScratch[command * 2] = source[command].words.w0;
        s_commandScratch[command * 2 + 1] = source[command].words.w1;
    }
    return s_commandScratch;
}

u64 hash_source_commands(const std::vector<u32>& commands) {
    return XXH3_64bits(commands.data(), commands.size() * sizeof(commands[0]));
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

bool commands_match_entry(const std::vector<u32>& commands, const Entry& entry) {
    return commands.size() == entry.commandWords.size() &&
           std::memcmp(commands.data(), entry.commandWords.data(), commands.size() * sizeof(commands[0])) == 0;
}

size_t entry_size(const Entry& entry) {
    return sizeof(entry) + entry.commandWords.capacity() * sizeof(entry.commandWords[0]) +
           entry.sourceVertices.capacity() * sizeof(entry.sourceVertices[0]) +
           entry.indices.capacity() * sizeof(entry.indices[0]);
}

void touch(EntryIterator entry) {
    s_entries.splice(s_entries.begin(), s_entries, entry);
}

void evict_lru() {
    const EntryIterator victim = std::prev(s_entries.end());
    Entry* victimEntry = &*victim;

    for (FastLookup& fast : s_fastLookups) {
        if (fast.entry == victimEntry) {
            fast = {};
        }
    }

    const auto range = s_entriesByHash.equal_range(victimEntry->commandHash);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == victim) {
            s_entriesByHash.erase(it);
            break;
        }
    }

    s_cacheBytes -= entry_size(*victim);
    s_entries.erase(victim);
    ++s_stats.evictions;
}

bool make_room(size_t bytes) {
    if (bytes > MaxCacheBytes) {
        return false;
    }
    while (!s_entries.empty() && (s_entries.size() >= MaxCacheEntries || bytes > MaxCacheBytes - s_cacheBytes)) {
        evict_lru();
    }
    return s_entries.size() < MaxCacheEntries && bytes <= MaxCacheBytes - s_cacheBytes;
}

void append_triangle(std::vector<u32>& vertices, u32 v0, u32 v1, u32 v2) {
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
}

bool collect_standard_triangles(const Gfx* source, u32 commandCount, std::vector<u32>& vertices) {
    for (u32 command = 0; command < commandCount; ++command) {
        const u8 opcode = static_cast<u8>(source[command].words.w0 >> 24);
        if (opcode == G_TRI2) {
            Gtri2 triangles{};
            std::memcpy(&triangles, &source[command].words, sizeof(triangles));
            append_triangle(vertices, triangles.t0v0 / 2, triangles.t0v1 / 2, triangles.t0v2 / 2);
            append_triangle(vertices, triangles.t1v0 / 2, triangles.t1v1 / 2, triangles.t1v2 / 2);
        } else if (opcode == G_TRI1) {
            Gtri1 triangle{};
            std::memcpy(&triangle, &source[command].words, sizeof(triangle));
            append_triangle(vertices, triangle.v0 / 2, triangle.v1 / 2, triangle.v2 / 2);
        } else {
            return false;
        }
    }
    return true;
}

bool collect_packed_triangles(const Gfx* source, u32 commandCount, std::vector<u32>& vertices) {
    const u32 faceCount = ((source[0].words.w0 >> 17) & 0x7F) + 1;
    const bool sevenBit = (source[0].words.w1 & POLY_BITMASK) == POLY_7b;
    u32 remaining = faceCount;
    u32 consumed = 0;

    while (consumed < commandCount && remaining != 0) {
        const Gfx* command = &source[consumed];
        const bool commandSevenBit = (command->words.w1 & POLY_BITMASK) == POLY_7b;
        if (commandSevenBit != sevenBit) {
            return false;
        }

        if (!sevenBit) {
            const u32 packed[] = {
                POLY_GET_V0_5b(command), POLY_GET_V1_5b(command), POLY_GET_V2_5b(command),  POLY_GET_V3_5b(command),
                POLY_GET_V4_5b(command), POLY_GET_V5_5b(command), POLY_GET_V6_5b(command),  POLY_GET_V7_5b(command),
                POLY_GET_V8_5b(command), POLY_GET_V9_5b(command), POLY_GET_V10_5b(command), POLY_GET_V11_5b(command),
            };
            const u32 availableFaces = consumed == 0 ? 3 : 4;
            const u32 emittedFaces = remaining < availableFaces ? remaining : availableFaces;
            for (u32 face = 0; face < emittedFaces; ++face) {
                append_triangle(vertices, packed[face * 3], packed[face * 3 + 1], packed[face * 3 + 2]);
            }
            remaining -= emittedFaces;
        } else {
            const u32 packed[] = {
                POLY_GET_V0_7b(command), POLY_GET_V1_7b(command), POLY_GET_V2_7b(command),
                POLY_GET_V3_7b(command), POLY_GET_V4_7b(command), POLY_GET_V5_7b(command),
                POLY_GET_V6_7b(command), POLY_GET_V7_7b(command), POLY_GET_V8_7b(command),
            };
            const u32 availableFaces = consumed == 0 ? 2 : 3;
            const u32 emittedFaces = remaining < availableFaces ? remaining : availableFaces;
            for (u32 face = 0; face < emittedFaces; ++face) {
                append_triangle(vertices, packed[face * 3], packed[face * 3 + 1], packed[face * 3 + 2]);
            }
            remaining -= emittedFaces;
        }
        ++consumed;
    }

    return remaining == 0 && consumed == commandCount;
}

bool compile_topology(const Gfx* source, u32 commandCount, u32 vertexCount, std::vector<u8>& sourceVertices,
                      std::vector<u16>& indices) {
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
    sourceVertices.reserve(vertexCount);
    indices.reserve(vertexCount);

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
        indices.push_back(static_cast<u16>(compact));
    }
    return true;
}

std::optional<Entry> compile_entry(const Gfx* source, u32 commandCount, u32 vertexCount, u64 commandHash,
                                   const std::vector<u32>& commandWords) {
    Entry entry;
    if (!compile_topology(source, commandCount, vertexCount, entry.sourceVertices, entry.indices)) {
        return std::nullopt;
    }

    entry.commandHash = commandHash;
    entry.commandWords = commandWords;
    return entry;
}

std::optional<EntryIterator> insert_entry(Entry entry) {
    const size_t bytes = entry_size(entry);
    if (!make_room(bytes)) {
        return std::nullopt;
    }

    s_entries.push_front(std::move(entry));
    const EntryIterator inserted = s_entries.begin();
    s_entriesByHash.emplace(inserted->commandHash, inserted);
    s_cacheBytes += bytes;
    return inserted;
}

} // namespace

const Entry* find_or_compile(const Gfx* source, u32 commandCount, u32 vertexCount) {
    if (source == nullptr || commandCount == 0 || commandCount > MaxCommandCount || vertexCount == 0 ||
        vertexCount > 0xFFFF) {
        return nullptr;
    }

    const u32 fastSlot = static_cast<u32>(reinterpret_cast<uintptr_t>(source) >> 3) & (FastLookupCount - 1);
    FastLookup& fast = s_fastLookups[fastSlot];
    if (fast.source == source && fast.commandCount == commandCount && fast.entry != nullptr &&
        fast.entry->indices.size() == vertexCount && source_matches_entry(source, commandCount, *fast.entry)) {
        ++s_stats.fastHits;
        touch(fast.iterator);
        return fast.entry;
    }

    const std::vector<u32>& commands = snapshot_source_commands(source, commandCount);
    const u64 hash = hash_source_commands(commands);
    const auto range = s_entriesByHash.equal_range(hash);
    for (auto it = range.first; it != range.second; ++it) {
        const EntryIterator entry = it->second;
        if (entry->indices.size() == vertexCount && commands_match_entry(commands, *entry)) {
            ++s_stats.contentHits;
            fast = { source, commandCount, &*entry, entry };
            touch(entry);
            return fast.entry;
        }
    }

    ++s_stats.misses;
    std::optional<Entry> compiled = compile_entry(source, commandCount, vertexCount, hash, commands);
    if (!compiled) {
        return nullptr;
    }
    const std::optional<EntryIterator> inserted = insert_entry(std::move(*compiled));
    if (!inserted) {
        return nullptr;
    }

    fast = { source, commandCount, &**inserted, *inserted };
    return fast.entry;
}

Stats stats() {
    Stats result = s_stats;
    result.entryCount = s_entries.size();
    result.byteSize = s_cacheBytes;
    return result;
}

void clear() {
    s_entries.clear();
    s_entriesByHash.clear();
    s_fastLookups.fill({});
    s_cacheBytes = 0;
    s_stats = {};
}

} // namespace acgc::emu64_geometry_cache
