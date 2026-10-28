#include "acgc/ui/settings.hpp"

#include "acgc/data.hpp"
#include "acgc/settings.hpp"
#include "acgc/texture_replacements.hpp"
#include "acgc/ui/bool_button.hpp"
#include "acgc/ui/modal.hpp"
#include "acgc/ui/number_button.hpp"
#include "acgc/ui/pane.hpp"
#include "acgc/ui/localization.hpp"

#include "borealis/io.hpp"

#include <aurora/gfx.h>
#include "extern/aurora/lib/window.hpp"

#include <SDL3/SDL_dialog.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_misc.h>
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
        right, [help = std::move(help)](Pane& pane) { pane.add_text(help); });
}

void add_bool(Pane& left, Pane& right, ConfigVar<bool>& variable, Rml::String label, Rml::String help)
{
    add_bool(left, right, variable, std::move(label), std::move(help), [](bool) {});
}

constexpr std::array kUiScales = {50, 75, 0, 125, 150, 175, 200};

constexpr std::array kThemes = {InterfaceTheme::Dynamic, InterfaceTheme::Day, InterfaceTheme::Night};

Rml::String ui_scale_label(int percent)
{
    return percent == 0 ? localization::get("settings.video.ui_scale.automatic")
                        : std::to_string(percent) + "%";
}

Rml::String theme_label(InterfaceTheme theme)
{
    switch (theme) {
    case InterfaceTheme::Day:
        return localization::get("settings.video.theme.day");
    case InterfaceTheme::Night:
        return localization::get("settings.video.theme.night");
    case InterfaceTheme::Dynamic:
        break;
    }
    return localization::get("settings.video.theme.dynamic");
}

Rml::String renderer_label(AuroraBackend renderer)
{
    switch (renderer) {
    case BACKEND_AUTO:
        return localization::get("settings.video.renderer.automatic");
    case BACKEND_D3D11:
        return "Direct3D 11";
    case BACKEND_D3D12:
        return "Direct3D 12";
    case BACKEND_METAL:
        return "Metal";
    case BACKEND_VULKAN:
        return "Vulkan";
    case BACKEND_OPENGL:
        return "OpenGL";
    case BACKEND_OPENGLES:
        return "OpenGL ES";
    case BACKEND_WEBGPU:
        return "WebGPU";
    case BACKEND_NULL:
        break;
    }
    return localization::get("settings.video.renderer.automatic");
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
        label += localization::get("settings.video.resolution.desktop_suffix");
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
        mSelect->Add(escape(localization::get("settings.video.resolution.custom")),
                     std::to_string(mPresets.size()));
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
        listen(mRoot, Rml::EventId::Keydown, [this](Rml::Event& event) {
            if (map_nav_event(event) == NavCommand::Cancel && mSelect->IsSelectBoxVisible()) {
                mSelect->CancelSelectBox();
                event.StopPropagation();
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

Rml::String data_folder_error_message(const borealis::data::Status& status)
{
    using enum borealis::data::ErrorCode;
    Rml::String message;
    switch (status.code) {
    case NotInitialized: message = localization::get("settings.data.error.not_initialized"); break;
    case PreferencePathUnavailable:
        message = localization::get("settings.data.error.system_path_unavailable");
        break;
    case EmptyPath: message = localization::get("settings.data.error.empty_path"); break;
    case CreateDirectoryFailed: message = localization::get("settings.data.error.create_failed"); break;
    case NotDirectory: message = localization::get("settings.data.error.not_directory"); break;
    case WriteProbeFailed: message = localization::get("settings.data.error.not_writable"); break;
    case WriteProbeCleanupFailed:
        message = localization::get("settings.data.error.validation_failed");
        break;
    case DescriptorWriteFailed: message = localization::get("settings.data.error.save_failed"); break;
    case MigrationIncomplete:
        message = localization::get("settings.data.error.migration_incomplete");
        break;
    case OverrideActive: message = localization::get("settings.data.error.override_active"); break;
    case Unsupported: message = localization::get("settings.data.error.unsupported"); break;
    case OpenFolderFailed: message = localization::get("settings.data.error.open_failed"); break;
    case None: message = localization::get("settings.data.error_fallback"); break;
    }

    if (!status.path.empty()) {
        message = localization::format("settings.data.error.with_path", message,
                                       borealis::io::fs_path_to_string(status.path));
    }
    if (status.systemError) {
        message = localization::format("settings.data.error.with_system_error", message,
                                       status.systemError.message());
    }
    return message;
}

/* Live view of the configured data folder plus the pending-restart notice. */
class DataFolderPathText : public Component {
public:
    explicit DataFolderPathText(Rml::Element* parent) : Component(append(parent, "div")) {}

    void update() override
    {
        Rml::String rml = escape(localization::get("settings.data.current_folder")) + "<br/>" +
                          escape(data::abbreviated_path_string(data::configured_data_path()));
        if (data::is_data_path_restart_pending()) {
            rml += "<br/><br/>" + escape(localization::get("settings.data.restart_pending"));
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
        .title = escape(localization::get("settings.data.error_title")),
        .bodyRml = escape(message),
        .actions = {
            ModalAction{
                .label = localization::get("common.ok"),
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

constexpr const char* kTexturePackUrl = "https://forums.dolphin-emu.org/Thread-animal-crossing-hd-texture-pack-version-25-october-11th-2026";

void show_open_url_modal(const char* url)
{
    auto dismiss = [](Modal& modal) { modal.pop(); };
    push_document(std::make_unique<Modal>(Modal::Props{
        .title = escape(localization::get("settings.open_url.title")),
        .bodyRml = escape(localization::get("settings.open_url.body")) + "<div class=\"modal-url\">" +
                   escape(url) + "</div>",
        .actions = {
            ModalAction{
                .label = localization::get("common.cancel"),
                .onPressed = dismiss,
            },
            ModalAction{
                .label = localization::get("settings.open_url.open"),
                .onPressed = [url](Modal& modal) {
                    modal.pop();
                    SDL_OpenURL(url);
                },
            },
        },
        .onDismiss = dismiss,
        .variant = "light",
    }));
    if (auto* doc = top_document()) {
        doc->focus();
    }
}

void apply_data_folder_selection(void* userdata)
{
    std::unique_ptr<std::string> selection(static_cast<std::string*>(userdata));

    const auto status = data::set_custom_data_path(
        borealis::io::fs_path_from_utf8(*selection));
    if (status) {
        return;
    }
    show_data_folder_error_modal(data_folder_error_message(status));
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
    add_tab(localization::get("settings.tabs.general"), [this](Rml::Element* content) {
        auto& current = settings();
        auto& left = add_child<Pane>(content, Pane::Type::Controlled);
        auto& right = add_child<Pane>(content, Pane::Type::Uncontrolled);

#if ACGC_CAN_CHANGE_DATA_FOLDER
        left.add_section(localization::get("settings.data.section"));
        left.register_control(
            left.add_select_button({
                .key = localization::get("settings.data.folder"),
                .getValue = [] {
                    return Rml::String(data::abbreviated_path_string(data::configured_data_path()));
                },
                .isModified = [] { return data::is_data_path_restart_pending(); },
            }),
            right, [](Pane& pane) {
                pane.add_text(localization::get("settings.data.help"));
                pane.add_child<DataFolderPathText>();
#if ACGC_CAN_OPEN_DATA_FOLDER
                pane.add_button(localization::get("settings.data.open")).on_pressed([] {
                    data::open_data_path();
                });
#endif
                pane.add_button(localization::get("settings.data.change")).on_pressed([] {
                    const std::string current = borealis::io::fs_path_to_string(data::configured_data_path());
                    SDL_ShowOpenFolderDialog(&data_folder_dialog_callback, nullptr,
                                             aurora::window::get_sdl_window(),
                                             current.empty() ? nullptr : current.c_str(), false);
                });
                pane.add_button(ControlledButton::Props{
                    .text = localization::get("settings.data.reset"),
                    .isDisabled = [] { return data::is_default_data_path(); },
                }).on_pressed([] {
                    data::reset_data_path();
                });
                pane.add_text(localization::get("settings.data.change_help"));
            });
#endif

        left.add_section(localization::get("settings.startup.section"));
        add_bool(left, right, current.backend.skipPrelaunch,
                 localization::get("settings.startup.skip_prelaunch"),
                 localization::get("settings.startup.skip_prelaunch_help"));
        add_bool(left, right, current.backend.checkForUpdates,
                 localization::get("settings.startup.check_updates"),
                 localization::get("settings.startup.check_updates_help"));
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
    const auto rendererBackends = available_renderer_backends();

    add_tab(localization::get("settings.tabs.video"),
            [this, resolutionPresets, resolutionState, rendererBackends](Rml::Element* content) {
        auto& current = settings();
        auto& left = add_child<Pane>(content, Pane::Type::Controlled);
        auto& right = add_child<Pane>(content, Pane::Type::Uncontrolled);

        left.add_section(localization::get("settings.video.display_section"));
        left.register_control(
            left.add_select_button({
                .key = localization::get("settings.video.renderer"),
                .getValue = [&current] { return renderer_label(current.video.renderer.value()); },
                .isModified = [&current] { return modified(current.video.renderer); },
            }),
            right, [&current, rendererBackends](Pane& pane) {
                for (const AuroraBackend renderer : rendererBackends) {
                    pane.add_button(ControlledButton::Props{
                        .text = renderer_label(renderer),
                        .isSelected = [&current, renderer] {
                            return current.video.renderer.value() == renderer;
                        },
                    }).on_pressed([&current, renderer] {
                        current.video.renderer.set_value(renderer);
                        save_settings();
                    });
                }
                pane.add_text(localization::get("settings.video.renderer_help"));
            });

        left.register_control(
            left.add_child<BoolButton>(BoolButton::Props{
                .key = localization::get("settings.video.fullscreen"),
                .getValue = [&current] { return current.video.windowMode.value() != 0; },
                .setValue = [&current](bool value) {
                    current.video.windowMode.set_value(value ? 1 : 0);
                    aurora::window::set_fullscreen(value);
                    persist();
                },
                .isModified = [&current] { return modified(current.video.windowMode); },
            }),
            right, [](Pane& pane) {
                pane.add_text(localization::get("settings.video.fullscreen_help"));
            });

        add_bool(left, right, current.video.vsync, localization::get("settings.video.vsync"),
                 localization::get("settings.video.vsync_help"),
                 [](bool value) { aurora_enable_vsync(value); });

        left.register_control(
            left.add_select_button({
                .key = localization::get("settings.video.window_size"),
                .getValue = [&current, resolutionState] {
                    Rml::String value = std::to_string(resolutionState->width) + " x " +
                                        std::to_string(resolutionState->height);
                    if (resolutionState->width != current.video.windowWidth.value() ||
                        resolutionState->height != current.video.windowHeight.value()) {
                        value += localization::get("settings.video.resolution.pending_suffix");
                    }
                    return value;
                },
                .isDisabled = [&current] { return current.video.windowMode.value() != 0; },
                .isModified = [&current] {
                    return modified(current.video.windowWidth) || modified(current.video.windowHeight);
                },
            }),
            right, [&current, resolutionPresets, resolutionState](Pane& pane) {
                pane.add_section(localization::get("settings.video.resolution.section"));
                pane.add_child<ResolutionDropdown>(resolutionPresets, resolutionState);
                auto& widthField = pane.add_child<ConditionalNumberButton>(NumberButton::Props{
                    .key = localization::get("settings.video.resolution.width"),
                    .getValue = [resolutionState] { return resolutionState->width; },
                    .setValue = [resolutionState](int value) { resolutionState->width = value; },
                    .isDisabled = [resolutionState] { return !resolutionState->custom; },
                    .isModified = [&current, resolutionState] {
                        return resolutionState->custom &&
                               resolutionState->width != current.video.windowWidth.value();
                    },
                    .min = 320, .max = 7680, .step = 16,
                    .suffix = " px",
                }, [resolutionState] { return resolutionState->custom; });
                auto& heightField = pane.add_child<ConditionalNumberButton>(NumberButton::Props{
                    .key = localization::get("settings.video.resolution.height"),
                    .getValue = [resolutionState] { return resolutionState->height; },
                    .setValue = [resolutionState](int value) { resolutionState->height = value; },
                    .isDisabled = [resolutionState] { return !resolutionState->custom; },
                    .isModified = [&current, resolutionState] {
                        return resolutionState->custom &&
                               resolutionState->height != current.video.windowHeight.value();
                    },
                    .min = 240, .max = 4320, .step = 16,
                    .suffix = " px",
                }, [resolutionState] { return resolutionState->custom; });
                pane.add_button(localization::get("common.apply")).on_pressed(
                    [&current, resolutionState, &widthField, &heightField] {
                        widthField.commit_pending_edit();
                        heightField.commit_pending_edit();
                        current.video.windowWidth.set_value(resolutionState->width);
                        current.video.windowHeight.set_value(resolutionState->height);
                        aurora::window::set_window_size(resolutionState->width, resolutionState->height);
                        persist();
                    });
                pane.add_text(localization::get("settings.video.resolution.help"));
            });

        left.register_control(
            left.add_select_button({
                .key = localization::get("settings.video.ui_scale.label"),
                .getValue = [&current] { return ui_scale_label(current.video.uiScale.value()); },
                .isModified = [&current] { return modified(current.video.uiScale); },
            }),
            right, [&current](Pane& pane) {
                pane.add_text(localization::get("settings.video.ui_scale.help"));
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

        left.register_control(
            left.add_select_button({
                .key = localization::get("settings.video.theme.label"),
                .getValue = [&current] { return theme_label(current.video.theme.value()); },
                .isModified = [&current] { return modified(current.video.theme); },
            }),
            right, [&current](Pane& pane) {
                pane.add_text(localization::get("settings.video.theme.help"));
                for (const InterfaceTheme theme : kThemes) {
                    pane.add_button(ControlledButton::Props{
                        .text = theme_label(theme),
                        .isSelected = [&current, theme] { return current.video.theme.value() == theme; },
                    }).on_pressed([&current, theme] {
                        current.video.theme.set_value(theme);
                        save_settings();
                    });
                }
            });

        left.add_section(localization::get("settings.video.performance_section"));
        left.register_control(
            left.add_child<NumberButton>(NumberButton::Props{
                .key = localization::get("settings.video.frame_limit"),
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
            right, [](Pane& pane) { pane.add_text(localization::get("settings.video.frame_limit_help")); });

        left.add_section(localization::get("settings.video.textures_section"));
        left.register_control(
            left.add_select_button({
                .key = localization::get("settings.video.texture_pack"),
                .getValue = [] {
                    return localization::format("settings.video.texture_pack_loaded",
                                           texture_replacements::registration_count());
                },
            }),
            right, [](Pane& pane) {
                pane.add_button(localization::get("settings.video.texture_pack_reload")).on_pressed([] {
                    texture_replacements::reload();
                });
                pane.add_text(localization::format(
                    "settings.video.texture_pack_help",
                    borealis::io::fs_path_to_string(texture_replacements::directory())));
                pane.add_button(localization::get("settings.video.texture_pack_get")).on_pressed([] {
                    show_open_url_modal(kTexturePackUrl);
                });
            });
    });

    add_tab(localization::get("settings.tabs.audio"), [this](Rml::Element* content) {
        auto& current = settings();
        auto& left = add_child<Pane>(content, Pane::Type::Controlled);
        auto& right = add_child<Pane>(content, Pane::Type::Uncontrolled);
        left.add_section(localization::get("settings.audio.volume_section"));
        left.register_control(
            left.add_child<NumberButton>(NumberButton::Props{
                .key = localization::get("settings.audio.master_volume"),
                .getValue = [&current] { return current.audio.masterVolume.value(); },
                .setValue = [&current](int value) {
                    current.audio.masterVolume.set_value(value);
                    persist();
                },
                .isModified = [&current] { return modified(current.audio.masterVolume); },
                .min = 0, .max = 100, .step = 5,
                .suffix = "%",
            }),
            right, [](Pane& pane) { pane.add_text(localization::get("settings.audio.master_volume_help")); });
    });

    add_tab(localization::get("settings.tabs.gameplay"), [this](Rml::Element* content) {
        auto& current = settings();
        auto& left = add_child<Pane>(content, Pane::Type::Controlled);
        auto& right = add_child<Pane>(content, Pane::Type::Uncontrolled);

        left.add_section(localization::get("settings.gameplay.original_section"));
        left.register_control(
            left.add_child<BoolButton>(BoolButton::Props{
                .key = localization::get("settings.gameplay.resetti"),
                .getValue = [&current] { return !current.enhancements.disableResetti.value(); },
                .setValue = [&current](bool value) {
                    current.enhancements.disableResetti.set_value(!value);
                    persist(true);
                },
                .isModified = [&current] { return modified(current.enhancements.disableResetti); },
            }),
            right, [](Pane& pane) { pane.add_text(localization::get("settings.gameplay.resetti_help")); });

        left.add_section(localization::get("settings.gameplay.qol_section"));
        left.register_control(
            left.add_child<BoolButton>(BoolButton::Props{
                .key = localization::get("settings.gameplay.single_player_shop"),
                .getValue = [&current] { return current.enhancements.disableShopVisitorRequirement.value(); },
                .setValue = [&current](bool value) {
                    current.enhancements.disableShopVisitorRequirement.set_value(value);
                    persist(true);
                },
                .isModified = [&current] { return modified(current.enhancements.disableShopVisitorRequirement); },
            }),
            right, [](Pane& pane) { pane.add_text(localization::get("settings.gameplay.single_player_shop_help")); });

        add_bool(left, right, current.enhancements.reduceTravelMoveOut,
                 localization::get("settings.gameplay.reduce_travel_move_out"),
                 localization::get("settings.gameplay.reduce_travel_move_out_help"));

        add_bool(left, right, current.enhancements.borderlessAcres,
                 localization::get("settings.gameplay.borderless_acres"),
                 localization::get("settings.gameplay.borderless_acres_help"),
                 [](bool) { apply_runtime_settings(true); });
        add_bool(left, right, current.enhancements.fastText,
                 localization::get("settings.gameplay.fast_text"),
                 localization::get("settings.gameplay.fast_text_help"));
        add_bool(left, right, current.enhancements.pillarboxNes,
                 localization::get("settings.gameplay.nes_aspect"),
                 localization::get("settings.gameplay.nes_aspect_help"));
    });
}

void SettingsWindow::hide(bool close)
{
    save_settings();
    Window::hide(close);
}

} // namespace acgc::ui
