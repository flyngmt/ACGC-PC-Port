#pragma once

#include <filesystem>
#include <aurora/input.hpp>
#include <vector>

namespace acgc {

struct LegacyInputLoadResult {
    bool loaded = false;
    bool keyboardPending = false;
    bool controllerDefaultsApplied = false;
    std::filesystem::path sourcePath;
};

// Reads keybindings.ini before Aurora loads profiles. Existing input.json and
// legacy keyboard .dat mappings win over INI keyboard defaults.
LegacyInputLoadResult prepare_legacy_input(
    const std::filesystem::path& userDirectory, const std::vector<std::filesystem::path>& legacyCandidates);

// Must be called after PADInit. Existing Aurora keyboard bindings win; when
// none exist, the prepared legacy mapping is installed and serialized once.
bool apply_legacy_keyboard_input();
// Applies only missing controller controls, preserving explicit unbinds.
void apply_legacy_controller_input(aurora::input::SourceId source);

} // namespace acgc
