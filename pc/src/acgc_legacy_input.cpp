#include "acgc/legacy_input.hpp"

#include <dolphin/pad.h>
#include <SDL3/SDL.h>

#include "port/logging.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace acgc {
namespace {

struct LegacyBindings {
    std::array<PADKeyButtonBinding, PAD_BUTTON_COUNT> keyboardButtons{{
        {SDL_SCANCODE_SPACE, PAD_BUTTON_A},
        {SDL_SCANCODE_LSHIFT, PAD_BUTTON_B},
        {SDL_SCANCODE_X, PAD_BUTTON_X},
        {SDL_SCANCODE_Y, PAD_BUTTON_Y},
        {SDL_SCANCODE_RETURN, PAD_BUTTON_START},
        {SDL_SCANCODE_Z, PAD_TRIGGER_Z},
        {SDL_SCANCODE_Q, PAD_TRIGGER_L},
        {SDL_SCANCODE_E, PAD_TRIGGER_R},
        {SDL_SCANCODE_I, PAD_BUTTON_UP},
        {SDL_SCANCODE_K, PAD_BUTTON_DOWN},
        {SDL_SCANCODE_J, PAD_BUTTON_LEFT},
        {SDL_SCANCODE_L, PAD_BUTTON_RIGHT},
    }};
    std::array<PADKeyAxisBinding, PAD_AXIS_COUNT> keyboardAxes{{
        {SDL_SCANCODE_D, PAD_AXIS_LEFT_X_POS, 100},
        {SDL_SCANCODE_A, PAD_AXIS_LEFT_X_NEG, 100},
        {SDL_SCANCODE_W, PAD_AXIS_LEFT_Y_POS, 100},
        {SDL_SCANCODE_S, PAD_AXIS_LEFT_Y_NEG, 100},
        {SDL_SCANCODE_RIGHT, PAD_AXIS_RIGHT_X_POS, 100},
        {SDL_SCANCODE_LEFT, PAD_AXIS_RIGHT_X_NEG, 100},
        {SDL_SCANCODE_UP, PAD_AXIS_RIGHT_Y_POS, 100},
        {SDL_SCANCODE_DOWN, PAD_AXIS_RIGHT_Y_NEG, 100},
        {SDL_SCANCODE_Q, PAD_AXIS_TRIGGER_L, 100},
        {SDL_SCANCODE_E, PAD_AXIS_TRIGGER_R, 100},
    }};
};

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

constexpr std::array<ControllerBinding, PAD_BUTTON_COUNT> kControllerBindings{{
    {"Pad_A", PAD_BUTTON_A, "a"},
    {"Pad_B", PAD_BUTTON_B, "b"},
    {"Pad_X", PAD_BUTTON_X, "x"},
    {"Pad_Y", PAD_BUTTON_Y, "y"},
    {"Pad_Start", PAD_BUTTON_START, "start"},
    {"Pad_Z", PAD_TRIGGER_Z, "rightshoulder"},
    {"Pad_L", PAD_TRIGGER_L, "lefttrigger"},
    {"Pad_R", PAD_TRIGGER_R, "righttrigger"},
    {"Pad_DPad_Up", PAD_BUTTON_UP, "dpup"},
    {"Pad_DPad_Down", PAD_BUTTON_DOWN, "dpdown"},
    {"Pad_DPad_Left", PAD_BUTTON_LEFT, "dpleft"},
    {"Pad_DPad_Right", PAD_BUTTON_RIGHT, "dpright"},
}};

std::optional<LegacyBindings> s_preparedKeyboard;

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
        if (stripped.empty() || stripped.front() == '#' || stripped.front() == ';' ||
            stripped.front() == '[') {
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

int keyboard_code(std::string_view value)
{
    const std::string lowered = lowercase(value);
    if (lowered == "mouse1") {
        return PAD_KEY_MOUSE_LEFT;
    }
    if (lowered == "mouse2") {
        return PAD_KEY_MOUSE_RIGHT;
    }
    if (lowered == "mouse3") {
        return PAD_KEY_MOUSE_MIDDLE;
    }
    return static_cast<int>(SDL_GetScancodeFromName(std::string(value).c_str()));
}

NativeInput native_input(std::string_view value)
{
    const std::string name = lowercase(value);
    if (name == "none") {
        return {NativeInputKind::None, -1};
    }

    static const std::unordered_map<std::string, SDL_GamepadButton> buttons{
        {"a", SDL_GAMEPAD_BUTTON_SOUTH},
        {"b", SDL_GAMEPAD_BUTTON_EAST},
        {"x", SDL_GAMEPAD_BUTTON_WEST},
        {"y", SDL_GAMEPAD_BUTTON_NORTH},
        {"back", SDL_GAMEPAD_BUTTON_BACK},
        {"guide", SDL_GAMEPAD_BUTTON_GUIDE},
        {"start", SDL_GAMEPAD_BUTTON_START},
        {"leftstick", SDL_GAMEPAD_BUTTON_LEFT_STICK},
        {"rightstick", SDL_GAMEPAD_BUTTON_RIGHT_STICK},
        {"leftshoulder", SDL_GAMEPAD_BUTTON_LEFT_SHOULDER},
        {"rightshoulder", SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER},
        {"dpup", SDL_GAMEPAD_BUTTON_DPAD_UP},
        {"dpdown", SDL_GAMEPAD_BUTTON_DPAD_DOWN},
        {"dpleft", SDL_GAMEPAD_BUTTON_DPAD_LEFT},
        {"dpright", SDL_GAMEPAD_BUTTON_DPAD_RIGHT},
    };
    if (const auto button = buttons.find(name); button != buttons.end()) {
        return {NativeInputKind::Button, static_cast<int>(button->second)};
    }
    if (name == "lefttrigger") {
        return {NativeInputKind::Axis, SDL_GAMEPAD_AXIS_LEFT_TRIGGER};
    }
    if (name == "righttrigger") {
        return {NativeInputKind::Axis, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER};
    }
    return {};
}

template <typename Binding, std::size_t Size>
Binding* find_pad_binding(std::array<Binding, Size>& bindings, PADButton button)
{
    const auto found = std::find_if(bindings.begin(), bindings.end(), [button](const Binding& binding) {
        return binding.padButton == button;
    });
    return found == bindings.end() ? nullptr : &*found;
}

template <typename Binding, std::size_t Size>
Binding* find_axis_binding(std::array<Binding, Size>& bindings, PADAxis axis)
{
    const auto found = std::find_if(bindings.begin(), bindings.end(), [axis](const Binding& binding) {
        return binding.padAxis == axis;
    });
    return found == bindings.end() ? nullptr : &*found;
}

bool apply_keyboard_value(LegacyBindings& bindings, const std::string& key, const std::string& value)
{
    struct KeyboardBinding {
        std::string_view key;
        bool axis;
        u16 target;
    };
    static constexpr std::array<KeyboardBinding, 22> entries{{
        {"A", false, PAD_BUTTON_A}, {"B", false, PAD_BUTTON_B},
        {"X", false, PAD_BUTTON_X}, {"Y", false, PAD_BUTTON_Y},
        {"Start", false, PAD_BUTTON_START}, {"Z", false, PAD_TRIGGER_Z},
        {"L", false, PAD_TRIGGER_L}, {"R", false, PAD_TRIGGER_R},
        {"Stick_Up", true, PAD_AXIS_LEFT_Y_POS}, {"Stick_Down", true, PAD_AXIS_LEFT_Y_NEG},
        {"Stick_Left", true, PAD_AXIS_LEFT_X_NEG}, {"Stick_Right", true, PAD_AXIS_LEFT_X_POS},
        {"CStick_Up", true, PAD_AXIS_RIGHT_Y_POS}, {"CStick_Down", true, PAD_AXIS_RIGHT_Y_NEG},
        {"CStick_Left", true, PAD_AXIS_RIGHT_X_NEG}, {"CStick_Right", true, PAD_AXIS_RIGHT_X_POS},
        {"DPad_Up", false, PAD_BUTTON_UP}, {"DPad_Down", false, PAD_BUTTON_DOWN},
        {"DPad_Left", false, PAD_BUTTON_LEFT}, {"DPad_Right", false, PAD_BUTTON_RIGHT},
        {"L", true, PAD_AXIS_TRIGGER_L}, {"R", true, PAD_AXIS_TRIGGER_R},
    }};

    const bool recognized = std::any_of(entries.begin(), entries.end(), [&key](const KeyboardBinding& entry) {
        return entry.key == key;
    });
    if (!recognized) {
        return false;
    }

    const int code = keyboard_code(value);
    if (code == SDL_SCANCODE_UNKNOWN) {
        port_log_printf(LOG_WARNING, "acgc::input", "Ignoring unknown legacy key '%s' for %s",
                        value.c_str(), key.c_str());
        return true;
    }
    for (const auto& entry : entries) {
        if (entry.key != key) {
            continue;
        }
        if (entry.axis) {
            if (auto* binding = find_axis_binding(bindings.keyboardAxes, entry.target)) {
                binding->scancode = code;
                binding->influence = 100;
            }
        } else if (auto* binding = find_pad_binding(bindings.keyboardButtons, entry.target)) {
            binding->scancode = code;
        }
    }
    return true;
}

PADDefaultMapping make_controller_mapping(const std::unordered_map<std::string, std::string>& values,
                                          bool* foundLegacyValues)
{
    PADDefaultMapping mapping{};
    const std::array<PADAxisMapping, PAD_AXIS_COUNT> axes{{
        {{SDL_GAMEPAD_AXIS_LEFTX, AXIS_SIGN_POSITIVE}, SDL_GAMEPAD_BUTTON_INVALID, PAD_AXIS_LEFT_X_POS},
        {{SDL_GAMEPAD_AXIS_LEFTX, AXIS_SIGN_NEGATIVE}, SDL_GAMEPAD_BUTTON_INVALID, PAD_AXIS_LEFT_X_NEG},
        {{SDL_GAMEPAD_AXIS_LEFTY, AXIS_SIGN_NEGATIVE}, SDL_GAMEPAD_BUTTON_INVALID, PAD_AXIS_LEFT_Y_POS},
        {{SDL_GAMEPAD_AXIS_LEFTY, AXIS_SIGN_POSITIVE}, SDL_GAMEPAD_BUTTON_INVALID, PAD_AXIS_LEFT_Y_NEG},
        {{SDL_GAMEPAD_AXIS_RIGHTX, AXIS_SIGN_POSITIVE}, SDL_GAMEPAD_BUTTON_INVALID, PAD_AXIS_RIGHT_X_POS},
        {{SDL_GAMEPAD_AXIS_RIGHTX, AXIS_SIGN_NEGATIVE}, SDL_GAMEPAD_BUTTON_INVALID, PAD_AXIS_RIGHT_X_NEG},
        {{SDL_GAMEPAD_AXIS_RIGHTY, AXIS_SIGN_NEGATIVE}, SDL_GAMEPAD_BUTTON_INVALID, PAD_AXIS_RIGHT_Y_POS},
        {{SDL_GAMEPAD_AXIS_RIGHTY, AXIS_SIGN_POSITIVE}, SDL_GAMEPAD_BUTTON_INVALID, PAD_AXIS_RIGHT_Y_NEG},
        {{SDL_GAMEPAD_AXIS_LEFT_TRIGGER, AXIS_SIGN_POSITIVE}, SDL_GAMEPAD_BUTTON_INVALID, PAD_AXIS_TRIGGER_L},
        {{SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, AXIS_SIGN_POSITIVE}, SDL_GAMEPAD_BUTTON_INVALID, PAD_AXIS_TRIGGER_R},
    }};
    std::copy(axes.begin(), axes.end(), mapping.axes);

    for (std::size_t i = 0; i < kControllerBindings.size(); ++i) {
        const auto& descriptor = kControllerBindings[i];
        const auto legacy = values.find(std::string(descriptor.key));
        if (legacy != values.end()) {
            *foundLegacyValues = true;
        }
        const std::string_view text = legacy == values.end() ? descriptor.defaultValue : legacy->second;
        NativeInput input = native_input(text);
        mapping.buttons[i] = {PAD_NATIVE_BUTTON_INVALID, descriptor.padButton};

        if (input.kind == NativeInputKind::Invalid) {
            port_log_printf(LOG_WARNING, "acgc::input", "Ignoring unknown legacy controller input '%.*s' for %.*s",
                            static_cast<int>(text.size()), text.data(),
                            static_cast<int>(descriptor.key.size()), descriptor.key.data());
            input = native_input(descriptor.defaultValue);
        }
        if (input.kind == NativeInputKind::Axis &&
            descriptor.padButton != PAD_TRIGGER_L && descriptor.padButton != PAD_TRIGGER_R) {
            port_log_printf(LOG_WARNING, "acgc::input",
                            "Aurora cannot map legacy trigger axis '%.*s' to digital input %.*s; using its default",
                            static_cast<int>(text.size()), text.data(),
                            static_cast<int>(descriptor.key.size()), descriptor.key.data());
            input = native_input(descriptor.defaultValue);
        }

        if (input.kind == NativeInputKind::Button) {
            mapping.buttons[i].nativeButton = static_cast<u32>(input.value);
        } else if (input.kind == NativeInputKind::Axis &&
                   (descriptor.padButton == PAD_TRIGGER_L || descriptor.padButton == PAD_TRIGGER_R)) {
            const PADAxis target = descriptor.padButton == PAD_TRIGGER_L ? PAD_AXIS_TRIGGER_L : PAD_AXIS_TRIGGER_R;
            mapping.axes[target].nativeAxis = {input.value, AXIS_SIGN_POSITIVE};
            mapping.axes[target].nativeButton = SDL_GAMEPAD_BUTTON_INVALID;
        }

        if ((descriptor.padButton == PAD_TRIGGER_L || descriptor.padButton == PAD_TRIGGER_R) &&
            input.kind != NativeInputKind::Axis) {
            const PADAxis target = descriptor.padButton == PAD_TRIGGER_L ? PAD_AXIS_TRIGGER_L : PAD_AXIS_TRIGGER_R;
            mapping.axes[target].nativeAxis = {SDL_GAMEPAD_AXIS_INVALID, AXIS_SIGN_POSITIVE};
            mapping.axes[target].nativeButton = SDL_GAMEPAD_BUTTON_INVALID;
        }
    }
    return mapping;
}

} // namespace

LegacyInputLoadResult prepare_legacy_input(
    const std::filesystem::path& userDirectory,
    const std::vector<std::filesystem::path>& legacyCandidates)
{
    (void)userDirectory;
    s_preparedKeyboard.reset();

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
        port_log_printf(LOG_WARNING, "acgc::input", "Legacy input file is empty: %s",
                        result.sourcePath.string().c_str());
        return result;
    }

    LegacyBindings keyboard;
    bool foundKeyboardValues = false;
    for (const auto& [key, value] : values) {
        if (key.rfind("Pad_", 0) == 0) {
            continue;
        }
        foundKeyboardValues = apply_keyboard_value(keyboard, key, value) || foundKeyboardValues;
    }
    if (foundKeyboardValues) {
        s_preparedKeyboard = keyboard;
        result.keyboardPending = true;
    }

    bool foundControllerValues = false;
    const PADDefaultMapping controller = make_controller_mapping(values, &foundControllerValues);
    if (foundControllerValues) {
        constexpr std::array<PADControllerType, 10> genericControllerTypes{{
            PAD_TYPE_STANDARD, PAD_TYPE_XBOX360, PAD_TYPE_XBOXONE, PAD_TYPE_PS3, PAD_TYPE_PS4,
            PAD_TYPE_PS5, PAD_TYPE_SWITCH_PROCON, PAD_TYPE_JOYCON_LEFT, PAD_TYPE_JOYCON_RIGHT,
            PAD_TYPE_JOYCON_PAIR,
        }};
        for (const PADControllerType type : genericControllerTypes) {
            PADSetDefaultMapping(&controller, type);
        }
        result.controllerDefaultsApplied = true;
    }

    result.loaded = result.keyboardPending || result.controllerDefaultsApplied;
    if (result.loaded) {
        port_log_printf(LOG_INFO, "acgc::input", "Loaded legacy input mappings from %s",
                        result.sourcePath.string().c_str());
    }
    return result;
}

bool apply_legacy_keyboard_input()
{
    if (!s_preparedKeyboard) {
        return false;
    }

    u32 existingCount = 0;
    if (PADGetKeyButtonBindings(0, &existingCount) != nullptr) {
        port_log_printf(LOG_INFO, "acgc::input", "Keeping existing Aurora keyboard bindings");
        s_preparedKeyboard.reset();
        return false;
    }

    auto buttons = s_preparedKeyboard->keyboardButtons;
    auto axes = s_preparedKeyboard->keyboardAxes;
    PADSetKeyButtonBindings(0, buttons.data());
    PADSetKeyAxisBindings(0, axes.data());
    PADSetKeyboardActive(0, TRUE);
    PADSerializeMappings();
    s_preparedKeyboard.reset();
    port_log_printf(LOG_INFO, "acgc::input", "Migrated legacy keyboard bindings to Aurora");
    return true;
}

} // namespace acgc
