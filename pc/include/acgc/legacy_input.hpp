#pragma once

#include <filesystem>
#include <vector>

namespace acgc {

struct LegacyInputLoadResult {
    bool loaded = false;
    bool keyboardPending = false;
    bool controllerDefaultsApplied = false;
    std::filesystem::path sourcePath;
};

// Reads the pre-Aurora keybindings.ini format. Controller mappings become
// Aurora defaults before PADInit; per-device Aurora mappings still take
// precedence when a controller has already been configured.
LegacyInputLoadResult prepare_legacy_input(
    const std::filesystem::path& userDirectory,
    const std::vector<std::filesystem::path>& legacyCandidates);

// Must be called after PADInit. Existing Aurora keyboard bindings win; when
// none exist, the prepared legacy mapping is installed and serialized once.
bool apply_legacy_keyboard_input();

} // namespace acgc
