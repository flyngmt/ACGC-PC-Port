#include "acgc/legacy_input.hpp"

#include "acgc/input_profiles.hpp"
#include <map>
#include <set>
#include <SDL3/SDL.h>

#include "borealis/io.hpp"
#include "borealis/log.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

constexpr borealis::Log Log{ "acgc::input" };

namespace acgc {
namespace {

enum class NativeInputKind {
    None,
    Button,
    Axis,
    Invalid,
};

struct NativeInput {
    NativeInputKind kind = NativeInputKind::Invalid;
    int value = -1;
};

struct ControllerBinding {
    std::string_view key;
    PADButton padButton;
    std::string_view defaultValue;
};

constexpr std::array<ControllerBinding, PAD_BUTTON_COUNT> kControllerBindings{ {
    { "Pad_A", PAD_BUTTON_A, "a" },
    { "Pad_B", PAD_BUTTON_B, "b" },
    { "Pad_X", PAD_BUTTON_X, "x" },
    { "Pad_Y", PAD_BUTTON_Y, "y" },
    { "Pad_Start", PAD_BUTTON_START, "start" },
    { "Pad_Z", PAD_TRIGGER_Z, "rightshoulder" },
    { "Pad_L", PAD_TRIGGER_L, "lefttrigger" },
    { "Pad_R", PAD_TRIGGER_R, "righttrigger" },
    { "Pad_DPad_Up", PAD_BUTTON_UP, "dpup" },
    { "Pad_DPad_Down", PAD_BUTTON_DOWN, "dpdown" },
    { "Pad_DPad_Left", PAD_BUTTON_LEFT, "dpleft" },
    { "Pad_DPad_Right", PAD_BUTTON_RIGHT, "dpright" },
} };

using aurora::binding::Binding;
using aurora::binding::ControlId;
using aurora::binding::PhysicalInput;
using aurora::pad::ProfileTarget;
std::optional<std::map<ControlId, std::vector<Binding>>> s_preparedKeyboard;
std::map<ControlId, std::vector<Binding>> s_controllerFallback;
std::set<aurora::input::SourceId> s_importedControllers;

std::string trim(std::string value)
{
    const auto first = std::find_if_not(value.begin(), value.end(), [](unsigned char c) {
        return std::isspace(c) != 0;
    });
    const auto last = std::find_if_not(value.rbegin(), value.rend(), [](unsigned char c) {
        return std::isspace(c) != 0;
    }).base();
    if (first >= last) {
        return {};
    }
    return std::string(first, last);
}

std::string lowercase(std::string_view value)
{
    std::string result(value);
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    return result;
}

std::unordered_map<std::string, std::string> read_ini(const std::filesystem::path& path)
{
    std::unordered_map<std::string, std::string> result;
    std::ifstream input(path);
    std::string line;
    while (std::getline(input, line)) {
        const std::string stripped = trim(line);
        if (stripped.empty() || stripped.front() == '#' || stripped.front() == ';' || stripped.front() == '[') {
            continue;
        }
        const auto separator = stripped.find('=');
        if (separator == std::string::npos) {
            continue;
        }
        std::string key = trim(stripped.substr(0, separator));
        std::string value = trim(stripped.substr(separator + 1));
        if (!key.empty() && !value.empty()) {
            result.insert_or_assign(std::move(key), std::move(value));
        }
    }
    return result;
}

std::optional<PhysicalInput> keyboard_input(std::string_view value)
{
    const auto lowered = lowercase(value);
    if (lowered == "mouse1") {
        return PhysicalInput{ .control = PhysicalInput::MouseButton{ SDL_BUTTON_LEFT } };
    }
    if (lowered == "mouse2") {
        return PhysicalInput{ .control = PhysicalInput::MouseButton{ SDL_BUTTON_RIGHT } };
    }
    if (lowered == "mouse3") {
        return PhysicalInput{ .control = PhysicalInput::MouseButton{ SDL_BUTTON_MIDDLE } };
    }
    const auto key = SDL_GetScancodeFromName(std::string(value).c_str());
    if (key == SDL_SCANCODE_UNKNOWN) {
        return std::nullopt;
    }
    return PhysicalInput{ .control = PhysicalInput::Key{ key } };
}

NativeInput native_input(std::string_view value)
{
    const std::string name = lowercase(value);
    if (name == "none") {
        return { NativeInputKind::None, -1 };
    }

    static const std::unordered_map<std::string, SDL_GamepadButton> buttons{
        { "a", SDL_GAMEPAD_BUTTON_SOUTH },
        { "b", SDL_GAMEPAD_BUTTON_EAST },
        { "x", SDL_GAMEPAD_BUTTON_WEST },
        { "y", SDL_GAMEPAD_BUTTON_NORTH },
        { "back", SDL_GAMEPAD_BUTTON_BACK },
        { "guide", SDL_GAMEPAD_BUTTON_GUIDE },
        { "start", SDL_GAMEPAD_BUTTON_START },
        { "leftstick", SDL_GAMEPAD_BUTTON_LEFT_STICK },
        { "rightstick", SDL_GAMEPAD_BUTTON_RIGHT_STICK },
        { "leftshoulder", SDL_GAMEPAD_BUTTON_LEFT_SHOULDER },
        { "rightshoulder", SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER },
        { "dpup", SDL_GAMEPAD_BUTTON_DPAD_UP },
        { "dpdown", SDL_GAMEPAD_BUTTON_DPAD_DOWN },
        { "dpleft", SDL_GAMEPAD_BUTTON_DPAD_LEFT },
        { "dpright", SDL_GAMEPAD_BUTTON_DPAD_RIGHT },
    };
    if (const auto button = buttons.find(name); button != buttons.end()) {
        return { NativeInputKind::Button, static_cast<int>(button->second) };
    }
    if (name == "lefttrigger") {
        return { NativeInputKind::Axis, SDL_GAMEPAD_AXIS_LEFT_TRIGGER };
    }
    if (name == "righttrigger") {
        return { NativeInputKind::Axis, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER };
    }
    return {};
}

} // namespace

LegacyInputLoadResult prepare_legacy_input(
    const std::filesystem::path& userDirectory, const std::vector<std::filesystem::path>& legacyCandidates)
{
    s_preparedKeyboard.reset();
    s_controllerFallback.clear();
    s_importedControllers.clear();
    std::error_code existsError;
    // Record precedence before Aurora's loader creates input.json or removes .dat.
    const bool existingProfiles = std::filesystem::exists(userDirectory / "input.json", existsError) || existsError;
    existsError.clear();
    const bool existingKeyboard = existingProfiles ||
                                  std::filesystem::exists(userDirectory / "keyboard_bindings.dat", existsError) ||
                                  existsError;

    LegacyInputLoadResult result;
    std::error_code error;
    for (const auto& candidate : legacyCandidates) {
        if (!candidate.empty() && std::filesystem::is_regular_file(candidate, error)) {
            result.sourcePath = candidate;
            break;
        }
        error.clear();
    }
    if (result.sourcePath.empty()) {
        return result;
    }

    const auto values = read_ini(result.sourcePath);
    if (values.empty()) {
        Log.warn("Legacy input file is empty: {}", borealis::io::fs_path_to_string(result.sourcePath).c_str());
        return result;
    }

    if (!existingKeyboard) {
        std::map<ControlId, std::vector<Binding>> keyboard;
        bool found = false;
        for (const auto& entry : input::keyboard_defaults()) {
            auto& list = keyboard[entry.control];
            const auto value = values.find(std::string(entry.legacyKey));
            std::optional<PhysicalInput> physical = PhysicalInput{ .control = PhysicalInput::Key{ entry.key } };
            if (value != values.end()) {
                found = true;
                if (lowercase(value->second) == "none") {
                    physical.reset();
                } else if (auto parsed = keyboard_input(value->second)) {
                    physical = parsed;
                } else {
                    Log.warn("Ignoring unknown legacy key '{}' for {}", value->second, entry.legacyKey);
                }
            }
            if (physical) {
                list.push_back({ .input = *physical, .target = entry.control, .scale = entry.scale });
            }
        }
        if (found) {
            s_preparedKeyboard = std::move(keyboard);
            result.keyboardPending = true;
        }
    }

    // Keep INI controller entries as fallbacks. Explicit profile entries, including
    // empty lists, always win. Keep the INI so a controller connected later can
    // inherit its legacy mapping too.
    for (const auto& entry : kControllerBindings) {
        const auto found = values.find(std::string(entry.key));
        if (found == values.end()) {
            continue;
        }
        const auto physical = native_input(found->second);
        if (physical.kind == NativeInputKind::Invalid) {
            Log.warn("Ignoring unknown legacy controller input '{}' for {}", found->second, entry.key);
            continue;
        }
        const auto control = aurora::pad::control_for_button(entry.padButton);
        auto& list = s_controllerFallback[control];
        if (physical.kind == NativeInputKind::Button) {
            list.push_back({ .input = { .control = PhysicalInput::GamepadButton{ static_cast<SDL_GamepadButton>(
                                            physical.value) } },
                .target = control });
        } else if (physical.kind == NativeInputKind::Axis) {
            list.push_back(
                { .input = { .control = PhysicalInput::GamepadAxis{ static_cast<SDL_GamepadAxis>(physical.value),
                                 PhysicalInput::GamepadAxis::Direction::Positive } },
                    .target = control });
        }
        if (entry.padButton == PAD_TRIGGER_L || entry.padButton == PAD_TRIGGER_R) {
            const auto axis =
                entry.padButton == PAD_TRIGGER_L ? aurora::pad::controls().triggerL : aurora::pad::controls().triggerR;
            auto analog = list;
            for (auto& binding : analog) {
                binding.target = axis;
            }
            s_controllerFallback[axis] = std::move(analog);
        }
    }
    result.controllerDefaultsApplied = !s_controllerFallback.empty();

    result.loaded = result.keyboardPending || result.controllerDefaultsApplied;
    if (result.loaded) {
        Log.info("Loaded legacy input mappings from {}", borealis::io::fs_path_to_string(result.sourcePath).c_str());
    }
    return result;
}

bool apply_legacy_keyboard_input()
{
    if (!s_preparedKeyboard) {
        return false;
    }

    bool applied = true;
    for (auto& [control, bindings] : *s_preparedKeyboard) {
        applied = aurora::pad::set_binding(ProfileTarget::keyboard(0), control, bindings) && applied;
    }
    if (!applied || !input::save_profiles()) {
        return false;
    }
    s_preparedKeyboard.reset();
    Log.info("Migrated legacy keyboard bindings to Aurora profiles");
    return true;
}

void apply_legacy_controller_input(aurora::input::SourceId source)
{
    if (!source || s_importedControllers.contains(source)) {
        return;
    }
    const auto target = ProfileTarget::controller(source);
    const auto* profile = aurora::pad::profile(target);
    if (!profile) {
        return;
    }
    bool changed = false;
    for (const auto& [control, bindings] : s_controllerFallback) {
        const auto* descriptor = aurora::binding::describe_control(control);
        if (descriptor && !profile->bindings.contains(descriptor->name)) {
            changed = aurora::pad::set_binding(target, control, bindings) || changed;
        }
    }
    if (!changed || input::save_profiles()) {
        s_importedControllers.insert(source);
    }
}

} // namespace acgc
