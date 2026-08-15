#include "acgc/ui/settings.hpp"

#include "acgc/data.hpp"
#include "acgc/settings.hpp"
#include "acgc/texture_replacements.hpp"
#include "acgc/ui/bool_button.hpp"
#include "acgc/ui/controller_config.hpp"
#include "acgc/ui/modal.hpp"
#include "acgc/ui/number_button.hpp"
#include "acgc/ui/pane.hpp"

#include "borealis/io.hpp"

#include <aurora/gfx.h>
#include "extern/aurora/lib/window.hpp"

#include <SDL3/SDL_dialog.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>

#include <algorithm>
#include <array>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

extern "C" int g_pc_frame_limit_override;

namespace acgc::ui {
namespace {

template <typename T>
bool modified(const ConfigVar<T>& variable)
{
    return variable.value() != variable.default_value();
}

void persist(bool refreshGameplay = false)
{
    apply_runtime_settings(refreshGameplay);
    save_settings();
}

template <typename Callback>
void add_bool(Pane& left, Pane& right, ConfigVar<bool>& variable, Rml::String label,
              Rml::String help, Callback onChange)
{
    left.register_control(
        left.add_child<BoolButton>(BoolButton::Props{
            .key = std::move(label),
            .getValue = [&variable] { return variable.value(); },
            .setValue = [&variable, onChange = std::move(onChange)](bool value) {
                variable.set_value(value);
                onChange(value);
                persist();
            },
            .isModified = [&variable] { return modified(variable); },
        }),
        right, [help = std::move(help)](Pane& pane) { pane.add_rml(help); });
}

void add_bool(Pane& left, Pane& right, ConfigVar<bool>& variable, Rml::String label, Rml::String help)
{
    add_bool(left, right, variable, std::move(label), std::move(help), [](bool) {});
}

Rml::String msaa_label(int samples)
{
    return samples <= 1 ? "Off" : std::to_string(samples) + "x";
}

constexpr std::array kUiScales = {0, 50, 75, 100, 125, 150, 175, 200};

Rml::String ui_scale_label(int percent)
{
    return percent == 0 ? "Automatic" : std::to_string(percent) + "%";
}

struct ResolutionPreset {
    int width;
    int height;
    bool desktop = false;
};

constexpr std::array kResolutionPresets = {
    ResolutionPreset{640, 480},   ResolutionPreset{800, 600},   ResolutionPreset{960, 720},
    ResolutionPreset{1024, 768}, ResolutionPreset{1152, 864},  ResolutionPreset{1280, 960},
    ResolutionPreset{1400, 1050}, ResolutionPreset{1600, 1200}, ResolutionPreset{1280, 720},
    ResolutionPreset{1366, 768}, ResolutionPreset{1600, 900},  ResolutionPreset{1920, 1080},
    ResolutionPreset{2560, 1440}, ResolutionPreset{3840, 2160},
};

bool same_resolution(const ResolutionPreset& preset, int width, int height)
{
    return preset.width == width && preset.height == height;
}

std::vector<ResolutionPreset> available_resolution_presets()
{
    SDL_DisplayID display = SDL_GetDisplayForWindow(aurora::window::get_sdl_window());
    if (display == 0) {
        display = SDL_GetPrimaryDisplay();
    }
    const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(display);

    /* Presets larger than the desktop would persist an off-screen window. */
    std::vector<ResolutionPreset> presets;
    for (const ResolutionPreset& preset : kResolutionPresets) {
        if (mode == nullptr || (preset.width <= mode->w && preset.height <= mode->h)) {
            presets.push_back(preset);
        }
    }
    if (mode != nullptr) {
        const auto match = std::find_if(presets.begin(), presets.end(), [mode](const ResolutionPreset& preset) {
            return same_resolution(preset, mode->w, mode->h);
        });
        if (match != presets.end()) {
            match->desktop = true;
        } else {
            presets.push_back({mode->w, mode->h, true});
        }
    }

    std::sort(presets.begin(), presets.end(), [](const ResolutionPreset& lhs, const ResolutionPreset& rhs) {
        return lhs.width < rhs.width || (lhs.width == rhs.width && lhs.height < rhs.height);
    });
    return presets;
}

Rml::String resolution_label(const ResolutionPreset& preset)
{
    Rml::String label = std::to_string(preset.width) + " x " + std::to_string(preset.height);
    if (preset.desktop) {
        label += " (Desktop)";
    }
    return label;
}

struct ResolutionEditorState {
    int width;
    int height;
    bool custom;
};

class ResolutionDropdown final : public Component {
public:
    ResolutionDropdown(Rml::Element* parent, std::vector<ResolutionPreset> presets,
                       std::shared_ptr<ResolutionEditorState> state)
        : Component(append(parent, "select")), mPresets(std::move(presets)), mState(std::move(state))
    {
        mSelect = rmlui_dynamic_cast<Rml::ElementFormControlSelect*>(mRoot);
        if (mSelect == nullptr) {
            return;
        }
        mRoot->SetClass("dropdown", true);

        int selection = static_cast<int>(mPresets.size());
        for (int i = 0; i < static_cast<int>(mPresets.size()); ++i) {
            const ResolutionPreset& preset = mPresets[i];
            mSelect->Add(escape(resolution_label(preset)), std::to_string(i));
            if (!mState->custom && same_resolution(preset, mState->width, mState->height)) {
                selection = i;
            }
        }
        mSelect->Add("Custom", std::to_string(mPresets.size()));
        mSelect->SetSelection(selection);

        listen(mRoot, Rml::EventId::Change, [this](Rml::Event& event) {
            if (event.GetTargetElement() != mRoot) {
                return;
            }
            const int selected = mSelect->GetSelection();
            if (selected >= 0 && selected < static_cast<int>(mPresets.size())) {
                mState->width = mPresets[selected].width;
                mState->height = mPresets[selected].height;
                mState->custom = false;
            } else if (selected == static_cast<int>(mPresets.size())) {
                /* Keep width/height so Custom starts from the last selection. */
                mState->custom = true;
            }
        });
    }

private:
    std::vector<ResolutionPreset> mPresets;
    std::shared_ptr<ResolutionEditorState> mState;
    Rml::ElementFormControlSelect* mSelect = nullptr;
};

class ConditionalNumberButton final : public NumberButton {
public:
    ConditionalNumberButton(Rml::Element* parent, NumberButton::Props props, std::function<bool()> isVisible)
        : NumberButton(parent, std::move(props)), mIsVisible(std::move(isVisible))
    {
        update_visibility();
    }

    void update() override
    {
        update_visibility();
        NumberButton::update();
    }

    void commit_pending_edit() { update(); }

private:
    void update_visibility()
    {
        const bool visible = !mIsVisible || mIsVisible();
        if (visible == mVisible) {
            return;
        }
        mVisible = visible;
        if (visible) {
            mRoot->RemoveProperty(Rml::PropertyId::Display);
        } else {
            mRoot->SetProperty(Rml::PropertyId::Display, Rml::Style::Display::None);
        }
    }

    std::function<bool()> mIsVisible;
    bool mVisible = true;
};

#if ACGC_CAN_CHANGE_DATA_FOLDER

/* Live view of the configured data folder plus the pending-restart notice. */
class DataFolderPathText : public Component {
public:
    explicit DataFolderPathText(Rml::Element* parent) : Component(append(parent, "div")) {}

    void update() override
    {
        Rml::String rml = "Current data folder:<br/>" +
                          escape(data::abbreviated_path_string(data::configured_data_path()));
        if (data::is_data_path_restart_pending()) {
            rml += "<br/><br/>Restart the game to move data to the new folder.";
        }
        if (rml != mCurrentRml) {
            mRoot->SetInnerRML(rml);
            mCurrentRml = rml;
        }
        Component::update();
    }

private:
    Rml::String mCurrentRml;
};

void show_data_folder_error_modal(std::string_view message)
{
    auto dismiss = [](Modal& modal) { modal.pop(); };
    push_document(std::make_unique<Modal>(Modal::Props{
        .title = "Data Folder Not Changed",
        .bodyRml = escape(message),
        .actions = {
            ModalAction{
                .label = "OK",
                .onPressed = dismiss,
            },
        },
        .onDismiss = dismiss,
        .icon = "warning",
    }));
    if (auto* doc = top_document()) {
        doc->focus();
    }
}

void apply_data_folder_selection(void* userdata)
{
    std::unique_ptr<std::string> selection(static_cast<std::string*>(userdata));

    std::string dataPathError;
    if (data::set_custom_data_path(selection->c_str(), &dataPathError)) {
        return;
    }
    if (dataPathError.empty()) {
        dataPathError = "The selected folder could not be used as the data folder.";
    }
    show_data_folder_error_modal(dataPathError);
}

/* SDL may invoke dialog callbacks off the main thread; the UI (and the
 * descriptor write it triggers) must run on it. */
void data_folder_dialog_callback(void*, const char* const* filelist, int)
{
    if (filelist == nullptr || filelist[0] == nullptr) {
        return; /* Canceled or failed; nothing to apply. */
    }

    auto selection = std::make_unique<std::string>(filelist[0]);
    if (SDL_RunOnMainThread(&apply_data_folder_selection, selection.get(), false)) {
        selection.release();
    }
}

#endif // ACGC_CAN_CHANGE_DATA_FOLDER

} // namespace

SettingsWindow::SettingsWindow()
{
    add_tab("Animal Crossing", [this](Rml::Element* content) {
        auto& current = settings();
        auto& left = add_child<Pane>(content, Pane::Type::Controlled);
        auto& right = add_child<Pane>(content, Pane::Type::Uncontrolled);

#if ACGC_CAN_CHANGE_DATA_FOLDER
        left.add_section("Data");
        left.register_control(
            left.add_select_button({
                .key = "Data Folder",
                .getValue = [] {
                    return Rml::String(data::abbreviated_path_string(data::configured_data_path()));
                },
                .isModified = [] { return data::is_data_path_restart_pending(); },
            }),
            right, [](Pane& pane) {
                pane.add_text("The data folder is where the game stores saves, settings, "
                              "input mappings, texture packs, and NES ROMs.");
                pane.add_child<DataFolderPathText>();
#if ACGC_CAN_OPEN_DATA_FOLDER
                pane.add_button("Open Data Folder").on_pressed([] {
                    data::open_data_path();
                });
#endif
                pane.add_button("Change Data Folder").on_pressed([] {
                    const std::string current = borealis::io::fs_path_to_string(data::configured_data_path());
                    SDL_ShowOpenFolderDialog(&data_folder_dialog_callback, nullptr,
                                             aurora::window::get_sdl_window(),
                                             current.empty() ? nullptr : current.c_str(), false);
                });
                pane.add_button(ControlledButton::Props{
                    .text = "Reset to Default",
                    .isDisabled = [] { return data::is_default_data_path(); },
                }).on_pressed([] {
                    data::reset_data_path();
                });
                pane.add_text("Changes take effect after restarting the game; recognized data "
                              "moves to the new folder on the next launch.");
            });
#endif

        left.add_section("Startup");
        add_bool(left, right, current.backend.skipPrelaunch, "Skip Prelaunch Menu",
                 "Launch the last verified disc image immediately on future starts.");
        add_bool(left, right, current.backend.checkForUpdates, "Check for Updates",
                 "Check GitHub releases when the prelaunch menu opens. No personal data is collected.");
    });

    /* Created once per window, outside the tab builder, so rebuilding the tab
     * on activation does not discard staged, un-applied resolution edits. */
    const auto resolutionPresets = available_resolution_presets();
    auto& video = settings().video;
    const bool currentIsPreset = std::any_of(
        resolutionPresets.begin(), resolutionPresets.end(), [&video](const ResolutionPreset& preset) {
            return same_resolution(preset, video.windowWidth.value(), video.windowHeight.value());
        });
    auto resolutionState = std::make_shared<ResolutionEditorState>(ResolutionEditorState{
        .width = video.windowWidth.value(),
        .height = video.windowHeight.value(),
        .custom = !currentIsPreset,
    });

    add_tab("Video", [this, resolutionPresets, resolutionState](Rml::Element* content) {
        auto& current = settings();
        auto& left = add_child<Pane>(content, Pane::Type::Controlled);
        auto& right = add_child<Pane>(content, Pane::Type::Uncontrolled);

        left.add_section("Display");
        left.register_control(
            left.add_child<BoolButton>(BoolButton::Props{
                .key = "Fullscreen",
                .getValue = [&current] { return current.video.windowMode.value() != 0; },
                .setValue = [&current](bool value) {
                    current.video.windowMode.set_value(value ? 1 : 0);
                    aurora::window::set_fullscreen(value);
                    persist();
                },
                .isModified = [&current] { return modified(current.video.windowMode); },
            }),
            right, [](Pane& pane) {
                pane.add_text("Display the game in Aurora's borderless fullscreen mode.");
            });

        add_bool(left, right, current.video.vsync, "Vertical Sync",
                 "Synchronize presentation with the display refresh rate.",
                 [](bool value) { aurora_enable_vsync(value); });

        left.register_control(
            left.add_select_button({
                .key = "Window Size",
                .getValue = [&current, resolutionState] {
                    Rml::String value = std::to_string(resolutionState->width) + " x " +
                                        std::to_string(resolutionState->height);
                    if (resolutionState->width != current.video.windowWidth.value() ||
                        resolutionState->height != current.video.windowHeight.value()) {
                        value += " (pending)";
                    }
                    return value;
                },
                .isDisabled = [&current] { return current.video.windowMode.value() != 0; },
                .isModified = [&current] {
                    return modified(current.video.windowWidth) || modified(current.video.windowHeight);
                },
            }),
            right, [&current, resolutionPresets, resolutionState](Pane& pane) {
                pane.add_section("Resolution");
                pane.add_child<ResolutionDropdown>(resolutionPresets, resolutionState);
                auto& widthField = pane.add_child<ConditionalNumberButton>(NumberButton::Props{
                    .key = "Width",
                    .getValue = [resolutionState] { return resolutionState->width; },
                    .setValue = [resolutionState](int value) { resolutionState->width = value; },
                    .isDisabled = [resolutionState] { return !resolutionState->custom; },
                    .isModified = [&current, resolutionState] {
                        return resolutionState->custom &&
                               resolutionState->width != current.video.windowWidth.value();
                    },
                    .min = 320, .max = 7680, .step = 16, .suffix = " px",
                }, [resolutionState] { return resolutionState->custom; });
                auto& heightField = pane.add_child<ConditionalNumberButton>(NumberButton::Props{
                    .key = "Height",
                    .getValue = [resolutionState] { return resolutionState->height; },
                    .setValue = [resolutionState](int value) { resolutionState->height = value; },
                    .isDisabled = [resolutionState] { return !resolutionState->custom; },
                    .isModified = [&current, resolutionState] {
                        return resolutionState->custom &&
                               resolutionState->height != current.video.windowHeight.value();
                    },
                    .min = 240, .max = 4320, .step = 16, .suffix = " px",
                }, [resolutionState] { return resolutionState->custom; });
                pane.add_button("Apply").on_pressed(
                    [&current, resolutionState, &widthField, &heightField] {
                        widthField.commit_pending_edit();
                        heightField.commit_pending_edit();
                        current.video.windowWidth.set_value(resolutionState->width);
                        current.video.windowHeight.set_value(resolutionState->height);
                        aurora::window::set_window_size(resolutionState->width, resolutionState->height);
                        persist();
                    });
                pane.add_text("Choose a preset or Custom, then select Apply.");
            });

        left.register_control(
            left.add_select_button({
                .key = "UI Scale",
                .getValue = [&current] { return ui_scale_label(current.video.uiScale.value()); },
                .isModified = [&current] { return modified(current.video.uiScale); },
            }),
            right, [&current](Pane& pane) {
                pane.add_text("Scale the interface relative to the display's DPI scale. "
                              "Automatic and 100% match the DPI scale exactly.");
                for (const int percent : kUiScales) {
                    pane.add_button(ControlledButton::Props{
                        .text = ui_scale_label(percent),
                        .isSelected = [&current, percent] {
                            return current.video.uiScale.value() == percent;
                        },
                    }).on_pressed([&current, percent] {
                        current.video.uiScale.set_value(percent);
                        persist();
                    });
                }
            });

        left.add_section("Performance");
        left.register_control(
            left.add_child<NumberButton>(NumberButton::Props{
                .key = "Frame Limit",
                .getValue = [&current] { return current.video.maxFrameRate.value(); },
                .setValue = [&current](int value) {
                    current.video.maxFrameRate.set_value(value);
                    g_pc_frame_limit_override = value;
                    persist();
                },
                .isModified = [&current] { return modified(current.video.maxFrameRate); },
                .min = 0,
                .max = 480,
                .step = 5,
                .suffix = " FPS",
            }),
            right, [](Pane& pane) { pane.add_text("Set to 0 for uncapped presentation."); });

        left.register_control(
            left.add_select_button({
                .key = "Multisample Antialiasing",
                .getValue = [&current] { return msaa_label(current.video.msaa.value()); },
                .isModified = [&current] { return modified(current.video.msaa); },
            }),
            right, [&current](Pane& pane) {
                for (int samples : std::array{1, 2, 4, 8}) {
                    pane.add_button(ControlledButton::Props{
                        .text = msaa_label(samples),
                        .isSelected = [&current, samples] { return current.video.msaa.value() == samples; },
                    }).on_pressed([&current, samples] {
                        current.video.msaa.set_value(samples);
                        save_settings();
                    });
                }
                pane.add_text("MSAA changes take effect after restarting the game.");
            });

        left.add_section("Textures");
        left.register_control(
            left.add_select_button({
                .key = "Texture Pack",
                .getValue = [] {
                    return std::to_string(texture_replacements::registration_count()) + " loaded";
                },
            }),
            right, [](Pane& pane) {
                pane.add_button("Reload Texture Pack").on_pressed([] {
                    texture_replacements::reload();
                });
                pane.add_text("Loads Dolphin-format DDS and PNG replacements recursively from " +
                              borealis::io::fs_path_to_string(texture_replacements::directory()) +
                              ". Aurora indexes filenames at startup and loads image data on demand. "
                              "Legacy preload/cache values remain accepted in config for compatibility.");
            });
    });

    add_tab("Audio", [this](Rml::Element* content) {
        auto& current = settings();
        auto& left = add_child<Pane>(content, Pane::Type::Controlled);
        auto& right = add_child<Pane>(content, Pane::Type::Uncontrolled);
        left.add_section("Volume");
        left.register_control(
            left.add_child<NumberButton>(NumberButton::Props{
                .key = "Master Volume",
                .getValue = [&current] { return current.audio.masterVolume.value(); },
                .setValue = [&current](int value) {
                    current.audio.masterVolume.set_value(value);
                    persist();
                },
                .isModified = [&current] { return modified(current.audio.masterVolume); },
                .min = 0, .max = 100, .step = 5, .suffix = "%",
            }),
            right, [](Pane& pane) { pane.add_text("Adjust the host audio stream gain immediately."); });
    });

    add_tab("Gameplay", [this](Rml::Element* content) {
        auto& current = settings();
        auto& left = add_child<Pane>(content, Pane::Type::Controlled);
        auto& right = add_child<Pane>(content, Pane::Type::Uncontrolled);

        left.add_section("Original Experience");
        left.register_control(
            left.add_child<BoolButton>(BoolButton::Props{
                .key = "Resetti",
                .getValue = [&current] { return !current.enhancements.disableResetti.value(); },
                .setValue = [&current](bool value) {
                    current.enhancements.disableResetti.set_value(!value);
                    persist(true);
                },
                .isModified = [&current] { return modified(current.enhancements.disableResetti); },
            }),
            right, [](Pane& pane) { pane.add_text("Enable the normal Resetti consequence after quitting without saving."); });

        left.add_section("Quality of Life");
        left.register_control(
            left.add_child<BoolButton>(BoolButton::Props{
                .key = "Single-Player Shop Upgrades",
                .getValue = [&current] { return current.enhancements.disableShopVisitorRequirement.value(); },
                .setValue = [&current](bool value) {
                    current.enhancements.disableShopVisitorRequirement.set_value(value);
                    persist(true);
                },
                .isModified = [&current] { return modified(current.enhancements.disableShopVisitorRequirement); },
            }),
            right, [](Pane& pane) { pane.add_text("Remove the visiting-player requirement from the final Nook shop upgrade."); });

        add_bool(left, right, current.enhancements.borderlessAcres, "Borderless Acres",
                 "Remove acre-boundary movement restrictions. Enabling it refreshes nearby collision state.",
                 [](bool) { apply_runtime_settings(true); });
        add_bool(left, right, current.enhancements.pillarboxNes, "NES 4:3 Aspect",
                 "Keep embedded NES games at their original 4:3 aspect ratio.");
    });

    add_tab("Controller", [this](Rml::Element* content) {
        auto& current = settings();
        auto& left = add_child<Pane>(content, Pane::Type::Controlled);
        auto& right = add_child<Pane>(content, Pane::Type::Uncontrolled);

        left.add_section("Configuration");
        left.register_control(
            left.add_button("Configure Controllers").on_pressed([this] {
                push(std::make_unique<ControllerConfigWindow>());
            }),
            right, [](Pane& pane) {
                pane.add_text("Choose devices and configure keyboard and controller buttons, "
                              "sticks, triggers, dead zones, and rumble for all four ports.");
            });

        left.add_section("Dead Zones");
        left.register_control(
            left.add_child<NumberButton>(NumberButton::Props{
                .key = "Control Stick Deadzone",
                .getValue = [&current] { return current.input.stickDeadzone.value(); },
                .setValue = [&current](int value) {
                    current.input.stickDeadzone.set_value(value);
                    persist();
                },
                .isModified = [&current] { return modified(current.input.stickDeadzone); },
                .min = 0, .max = 40, .step = 2, .suffix = "%",
            }),
            right, [](Pane& pane) { pane.add_text("Global left-stick deadzone for newly connected and active controllers."); });
        left.register_control(
            left.add_child<NumberButton>(NumberButton::Props{
                .key = "C-Stick Deadzone",
                .getValue = [&current] { return current.input.cstickDeadzone.value(); },
                .setValue = [&current](int value) {
                    current.input.cstickDeadzone.set_value(value);
                    persist();
                },
                .isModified = [&current] { return modified(current.input.cstickDeadzone); },
                .min = 0, .max = 40, .step = 2, .suffix = "%",
            }),
            right, [](Pane& pane) { pane.add_text("Global C-stick deadzone for newly connected and active controllers."); });
    });
}

void SettingsWindow::hide(bool close)
{
    save_settings();
    Window::hide(close);
}

} // namespace acgc::ui
