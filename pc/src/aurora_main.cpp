#include <aurora/aurora.h>
#include <aurora/dvd.h>
#include <aurora/event.h>
#include <aurora/gfx.h>
#include <aurora/main.h>
#include <dolphin/gx.h>
#include <dolphin/gx/GXAurora.h>
#include <dolphin/pad.h>
#include <dolphin/vi.h>
#include <SDL3/SDL.h>
#include <tracy/Tracy.hpp>

#include "pc_assets.h"
#include "pc_platform.h"
#include "pc_typing.h"
#include "pc_mouse_input.h"
#include "aurora_debug.h"
#include "acgc/app_info.hpp"
#include "acgc/controller_ports.hpp"
#include "acgc/input_profiles.hpp"
#include "acgc/data.hpp"
#include "acgc/disc.hpp"
#include "acgc/legacy_input.hpp"
#include "acgc/settings.hpp"
#include "acgc/texture_replacements.hpp"
#include "acgc/ui/prelaunch.hpp"
#include "acgc/ui/theme.hpp"
#include "acgc/ui/ui.hpp"
#include "m_kankyo.h"
#include "borealis/aurora_log.h"
#include "borealis/cli.hpp"
#include "borealis/crash.hpp"
#include "borealis/io.hpp"
#include "borealis/log.hpp"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace {
void update_render_size();
void apply_frame_limit();
} // namespace

extern "C" {
void ac_entry();
int boot_main(int argc, const char** argv);
void pc_audio_shutdown();
void pc_audio_mq_shutdown();
void pc_emu64_tlut_frame_drained();
extern int g_pc_nes_active;
int g_pc_running = 1;
int g_pc_verbose = 0;
int g_pc_frame_limit_override = -1;
int g_pc_speedhack_enabled = 0;
int g_pc_time_override = -1;
int g_pc_min_override = -1;
int g_pc_sec_override = -1;
int g_pc_date_month = -1;
int g_pc_date_day = -1;
int g_pc_date_year = -1;
int g_pc_weather_override = -1;
int g_pc_weather_intensity_override = mEnv_WEATHER_INTENSITY_HEAVY;
int g_pc_window_w = 640;
int g_pc_window_h = 480;
int g_pc_widescreen_stretch = 0;
unsigned int pc_image_base = 0;
unsigned int pc_image_end = 0;

static bool s_frame_started = false;

static void pc_speedhack_toggle() {
    g_pc_speedhack_enabled = !g_pc_speedhack_enabled;
    if (g_pc_verbose) {
        std::printf("[PC] speedhack %s\n", g_pc_speedhack_enabled ? "5x" : "off");
    }
}

#ifdef MOUSE_INPUT
static void update_mouse_pad_buttons() {
    u32 buttons = 0;
    if (const auto bindings = aurora::pad::binding_set(0)) {
        for (const auto& binding : bindings->bindings) {
            if (const auto* mouse = binding.input.control.get_if<aurora::binding::PhysicalInput::MouseButton>();
                mouse && mouse->button > 0 && mouse->button <= 32) {
                buttons |= 1u << (mouse->button - 1);
            }
        }
    }
    pc_mouse_set_pad_buttons(buttons);
}
#endif

bool ac_aurora_begin_frame() {
    ZoneScoped;

    g_pc_widescreen_stretch = 0;
    pc_emu64_frame_cmds = 0;
    pc_emu64_frame_noop_cmds = 0;
    pc_emu64_frame_tri_cmds = 0;
    pc_emu64_frame_vtx_cmds = 0;
    pc_emu64_frame_dl_cmds = 0;
    pc_emu64_frame_cull_visible = 0;
    pc_emu64_frame_cull_rejected = 0;

    pc_mouse_set_blocked(PC_MOUSE_BLOCK_HOST_UI, borealis::ui::any_document_visible());
    pc_mouse_set_blocked(PC_MOUSE_BLOCK_IMGUI, ac_debug_imgui_wants_mouse());
    const AuroraEvent* event = aurora_update();
    pc_mouse_set_blocked(PC_MOUSE_BLOCK_HOST_UI, borealis::ui::any_document_visible());
    update_render_size();
    while (event != nullptr && event->type != AURORA_NONE) {
        if (event->type == AURORA_EXIT) {
            g_pc_running = 0;
        } else if (event->type == AURORA_SDL_EVENT) {
            if (!borealis::ui::any_document_visible()) {
                pc_typing_handle_event(&event->sdl);
            }
            if (event->sdl.type == SDL_EVENT_KEY_DOWN && !event->sdl.key.repeat && event->sdl.key.key == SDLK_F2) {
                pc_speedhack_toggle();
            }
            if (event->sdl.type == SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED) {
                acgc::apply_ui_scale();
            }
            acgc::ui::handle_event(event->sdl);
            if (borealis::ui::any_document_visible()) {
                pc_typing_cancel();
            }
            pc_mouse_handle_event(&event->sdl);
        } else if (event->type == AURORA_PAUSED || event->type == AURORA_UNPAUSED) {
            pc_mouse_cancel();
        } else if (event->type == AURORA_CONTROLLER_ADDED) {
            acgc::controller_ports::enforce_single_port();
            acgc::apply_runtime_settings(false);
        } else if (event->type == AURORA_CONTROLLER_REMOVED) {
            acgc::controller_ports::enforce_single_port();
        }
        ++event;
    }

    if (!g_pc_running) {
        return false;
    }

    acgc::controller_ports::update();
    update_render_size();
    pc_mouse_sync_system_cursor();
    s_frame_started = aurora_begin_frame();
    pc_mouse_set_blocked(PC_MOUSE_BLOCK_IMGUI, ac_debug_imgui_wants_mouse());
    pc_mouse_set_blocked(PC_MOUSE_BLOCK_PAUSED, !s_frame_started || aurora_get_timescale() == 0.0f);
#ifdef MOUSE_INPUT
    update_mouse_pad_buttons();
#endif
    pc_mouse_update();
    return s_frame_started;
}

void ac_aurora_end_frame() {
    if (s_frame_started) {
        acgc::ui::update();
        ac_debug_imgui_draw();
        pc_mouse_sync_system_cursor();
        aurora_end_frame();
        pc_emu64_tlut_frame_drained();
        s_frame_started = false;
        apply_frame_limit();
    }
}
}

namespace {

struct WindowDimensions {
    int width = 1280;
    int height = 960;
};

constexpr borealis::Log MainLog{"acgc"};
constexpr borealis::Log ConfigLog{"acgc::config"};
constexpr borealis::Log VideoLog{"acgc::video"};
constexpr borealis::Log ClockLog{"acgc::clock"};
constexpr borealis::Log WeatherLog{"acgc::weather"};
constexpr borealis::Log UiLog{"acgc::ui"};
constexpr borealis::Log DvdLog{"acgc::dvd"};
constexpr borealis::Log AssetsLog{"acgc::assets"};

bool s_uber_shader_requested = false;
bool s_frame_limit_explicit = false;
bool s_window_size_explicit = false;
borealis::LogLevel s_log_level = borealis::LogLevel::Info;
std::filesystem::path s_log_directory;
std::filesystem::path s_user_directory;

struct PortLogGuard {
    ~PortLogGuard() {
        borealis::log::shutdown();
    }
};

struct SettingsGuard {
    bool saveOnExit = false;

    ~SettingsGuard() {
        if (saveOnExit) {
            acgc::save_settings();
        }
        acgc::shutdown_settings();
    }
};

bool parse_nonnegative_integer(const char* text, int* value) {
    if (text == nullptr || value == nullptr) {
        return false;
    }
    char* end = nullptr;
    const long parsed = std::strtol(text, &end, 10);
    if (end == text || *end != '\0' || parsed < 0 || parsed > 1000000) {
        return false;
    }
    *value = static_cast<int>(parsed);
    return true;
}

int parse_rain_intensity(const char* text) {
    if (text == nullptr)
        return -1;
    if (std::strcmp(text, "light") == 0)
        return mEnv_WEATHER_INTENSITY_LIGHT;
    if (std::strcmp(text, "normal") == 0)
        return mEnv_WEATHER_INTENSITY_NORMAL;
    if (std::strcmp(text, "heavy") == 0)
        return mEnv_WEATHER_INTENSITY_HEAVY;
    return -1;
}

void apply_frame_limit() {
    using clock = std::chrono::steady_clock;
    static clock::time_point next_frame{};
    constexpr int kNesFrameRate = 60;

    const int limit = g_pc_nes_active ? kNesFrameRate : g_pc_frame_limit_override;
    if (limit <= 0) {
        next_frame = {};
        return;
    }

    ZoneScopedN("Frame limiter");
    const auto interval = std::chrono::nanoseconds(1'000'000'000LL / limit);
    const auto now = clock::now();
    if (next_frame == clock::time_point{} || now > next_frame + interval * 4) {
        next_frame = now;
    }
    next_frame += interval;
    std::this_thread::sleep_until(next_frame);
}

bool parse_window_dimensions(const char* text, WindowDimensions* dimensions) {
    if (text == nullptr || dimensions == nullptr) {
        return false;
    }

    char* width_end = nullptr;
    const long width = std::strtol(text, &width_end, 10);
    if (width_end == text || (*width_end != 'x' && *width_end != 'X')) {
        return false;
    }

    char* height_end = nullptr;
    const long height = std::strtol(width_end + 1, &height_end, 10);
    if (height_end == width_end + 1 || *height_end != '\0' || width < 320 || height < 240 || width > 16384 ||
        height > 16384) {
        return false;
    }

    dimensions->width = static_cast<int>(width);
    dimensions->height = static_cast<int>(height);
    return true;
}

struct CommandLine {
    WindowDimensions window{};
    std::string discPath;
    bool discPathExplicit = false;
};

enum class ParseOutcome { Run, Exit, Failed };

ParseOutcome parse_command_line(int argc, char* argv[], CommandLine* out) {
    cxxopts::Options options{"Nookery", "PC port of Animal Crossing"};
    borealis::cli::add_standard_options(options, {.console = false});
    options.add_options()
        ("h,help", "Show this help")
        ("v,verbose", "Enable additional game diagnostics",
            cxxopts::value<bool>()->default_value("false")->implicit_value("true"))
        ("disc", "Open an RVZ, ISO, or GCM image without the prelaunch menu",
            cxxopts::value<std::string>())
        ("window-size", "Set the initial window size, WIDTHxHEIGHT (minimum 320x240)",
            cxxopts::value<std::string>())
        ("widescreen", "Start at 1280x720",
            cxxopts::value<bool>()->default_value("false")->implicit_value("true"))
        ("profile", "Show performance diagnostics (optional =N interval, ignored)",
            cxxopts::value<std::string>()->implicit_value(""))
        ("model-viewer", "Launch the model viewer, optionally at =N",
            cxxopts::value<std::string>()->implicit_value(""))
        ("framelimit", "Set a software frame limit (0 = uncapped)", cxxopts::value<std::string>())
        ("no-framelimit", "Run uncapped",
            cxxopts::value<bool>()->default_value("false")->implicit_value("true"))
        ("time", "Override the in-game clock, H[:M[:S]]", cxxopts::value<std::string>())
        ("date", "Override the in-game date, M/D[/Y]", cxxopts::value<std::string>())
        ("rain", "Force rain, optionally =light, =normal or =heavy",
            cxxopts::value<std::string>()->implicit_value("heavy"))
        ("uber-shader", "Accepted for OpenGL-backend compatibility; ignored",
            cxxopts::value<bool>()->default_value("false")->implicit_value("true"));
    options.parse_positional({"disc"});
    options.positional_help("[disc image]");
    options.allow_unrecognised_options();

    cxxopts::ParseResult parsed;
    borealis::cli::StandardOptions standard;
    try {
        parsed = options.parse(argc, argv);
        standard = borealis::cli::parse(parsed);
    } catch (const cxxopts::exceptions::exception& e) {
        std::fprintf(stderr, "%s\n", e.what());
        return ParseOutcome::Failed;
    }

    if (parsed.count("help")) {
        std::printf("%s", options.help().c_str());
        return ParseOutcome::Exit;
    }

    if (standard.level) {
        s_log_level = *standard.level;
    }
    s_log_directory = standard.logDir;
    s_user_directory = standard.userDir;

    g_pc_verbose = parsed["verbose"].as<bool>() ? 1 : 0;
    if (g_pc_verbose && !standard.level) {
        s_log_level = borealis::LogLevel::Debug;
    }

    if (parsed.count("disc")) {
        out->discPath = parsed["disc"].as<std::string>();
        out->discPathExplicit = true;
    }

    if (parsed["widescreen"].as<bool>()) {
        out->window.width = 1280;
        out->window.height = 720;
        s_window_size_explicit = true;
    }
    if (parsed.count("window-size")) {
        if (!parse_window_dimensions(parsed["window-size"].as<std::string>().c_str(),
                &out->window)) {
            std::fprintf(stderr, "--window-size expects WIDTHxHEIGHT (minimum 320x240)\n");
            return ParseOutcome::Failed;
        }
        s_window_size_explicit = true;
    }

    if (parsed["no-framelimit"].as<bool>()) {
        g_pc_frame_limit_override = 0;
        s_frame_limit_explicit = true;
    }
    if (parsed.count("framelimit")) {
        int limit = -1;
        if (!parse_nonnegative_integer(parsed["framelimit"].as<std::string>().c_str(), &limit)) {
            std::fprintf(stderr, "--framelimit expects a nonnegative integer\n");
            return ParseOutcome::Failed;
        }
        g_pc_frame_limit_override = limit;
        s_frame_limit_explicit = true;
    }

    if (parsed.count("profile")) {
        g_pc_debug_ui_visible = 1;
    }
    s_uber_shader_requested = parsed["uber-shader"].as<bool>();

    if (parsed.count("model-viewer")) {
        g_pc_model_viewer = 1;
        const auto index = parsed["model-viewer"].as<std::string>();
        int start = -1;
        if (!index.empty()) {
            if (!parse_nonnegative_integer(index.c_str(), &start)) {
                std::fprintf(stderr, "--model-viewer expects a nonnegative structure index\n");
                return ParseOutcome::Failed;
            }
            g_pc_model_viewer_start = start;
        }
    }

    if (parsed.count("time")) {
        int hour = -1;
        int minute = -1;
        int second = -1;
        std::sscanf(parsed["time"].as<std::string>().c_str(), "%d:%d:%d", &hour, &minute, &second);
        if (hour < 0 || hour > 23 || minute > 59 || second > 59) {
            std::fprintf(stderr, "--time expects H[:M[:S]] in the 24-hour clock\n");
            return ParseOutcome::Failed;
        }
        g_pc_time_override = hour;
        if (minute >= 0)
            g_pc_min_override = minute;
        if (second >= 0)
            g_pc_sec_override = second;
    }

    if (parsed.count("date")) {
        int month = -1;
        int day = -1;
        int year = -1;
        std::sscanf(parsed["date"].as<std::string>().c_str(), "%d/%d/%d", &month, &day, &year);
        if (month < 1 || month > 12 || day < 1 || day > 31 || (year >= 0 && year < 2000)) {
            std::fprintf(stderr, "--date expects M/D[/Y] with year 2000 or later\n");
            return ParseOutcome::Failed;
        }
        g_pc_date_month = month;
        g_pc_date_day = day;
        if (year >= 0)
            g_pc_date_year = year;
    }

    if (parsed.count("rain")) {
        const int intensity = parse_rain_intensity(parsed["rain"].as<std::string>().c_str());
        if (intensity < 0) {
            std::fprintf(stderr, "--rain expects light, normal or heavy\n");
            return ParseOutcome::Failed;
        }
        g_pc_weather_override = mEnv_WEATHER_RAIN;
        g_pc_weather_intensity_override = intensity;
    }

    return ParseOutcome::Run;
}

void update_render_size() {
    u32 width = 0;
    u32 height = 0;
    AuroraGetRenderSize(&width, &height);
    if (width == 0 || height == 0) {
        return;
    }

    if (g_pc_window_w != static_cast<int>(width) || g_pc_window_h != static_cast<int>(height)) {
        g_pc_window_w = static_cast<int>(width);
        g_pc_window_h = static_cast<int>(height);
        VideoLog.info("Render size {}x{} (aspect factor {:.4f})", width, height,
                      pc_widescreen_get_aspect_factor());
    }
}

bool run_prelaunch()
{
    borealis::ui::push_document(std::make_unique<acgc::ui::Prelaunch>());
    bool paused = false;
    auto& state = acgc::ui::prelaunch_state();
    while (!state.launchRequested && !state.quitRequested) {
        const AuroraEvent* event = aurora_update();
        while (event != nullptr && event->type != AURORA_NONE) {
            if (event->type == AURORA_EXIT) {
                state.quitRequested = true;
            } else if (event->type == AURORA_PAUSED) {
                paused = true;
            } else if (event->type == AURORA_UNPAUSED) {
                paused = false;
            } else if (event->type == AURORA_SDL_EVENT) {
                if (event->sdl.type == SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED) {
                    acgc::apply_ui_scale();
                }
                acgc::ui::handle_event(event->sdl);
            } else if (event->type == AURORA_CONTROLLER_ADDED) {
                acgc::controller_ports::enforce_single_port();
                acgc::apply_runtime_settings(false);
            } else if (event->type == AURORA_CONTROLLER_REMOVED) {
                acgc::controller_ports::enforce_single_port();
            }
            ++event;
        }
        acgc::controller_ports::update();
        if (state.quitRequested || paused || !aurora_begin_frame()) {
            continue;
        }
        update_render_size();
        const auto background = acgc::ui::theme::background();
        GXSetCopyClear({background.red, background.green, background.blue, background.alpha}, 0xFFFFFF);
        acgc::ui::update();
        ac_debug_imgui_draw();
        aurora_end_frame();
        apply_frame_limit();
    }
    return state.launchRequested;
}

} // namespace

int main(int argc, char* argv[]) {
    CommandLine commandLine;
    switch (parse_command_line(argc, argv, &commandLine)) {
    case ParseOutcome::Exit:
        return 0;
    case ParseOutcome::Failed:
        return 2;
    case ParseOutcome::Run:
        break;
    }
    WindowDimensions windowDimensions = commandLine.window;

    const acgc::data::Paths data_paths = acgc::data::initialize(s_user_directory);
    const auto& log_root = data_paths.cachePath;
    borealis::log::Options log_options{
        .level = s_log_level,
        .fileDirectory = log_root / "logs",
        .filePrefix = "acgc",
    };
    if (!s_log_directory.empty()) {
        log_options.fileDirectory = s_log_directory;
    }
    borealis::log::init(log_options);
    PortLogGuard log_guard;
    borealis::crash::install();
    if (const char* log_path = borealis::log::file_path()) {
        MainLog.info("Logging to {}", log_path);
    } else {
        MainLog.warn("File logging is unavailable; continuing with console logging");
    }

    const std::string user_path = borealis::io::fs_path_to_string(data_paths.userPath);
    const std::string cache_path = borealis::io::fs_path_to_string(data_paths.cachePath);

    std::vector legacy_settings{
        std::filesystem::path(user_path) / "settings.ini",
        std::filesystem::current_path() / "settings.ini",
    };
    if (const char* base_path = SDL_GetBasePath()) {
        legacy_settings.emplace_back(std::filesystem::path(base_path) / "settings.ini");
    }
    const auto settings_result = acgc::load_settings(user_path, legacy_settings);
    SettingsGuard settings_guard{
        .saveOnExit = settings_result.canonicalResult != acgc::config::LoadResult::Invalid,
    };
    if (settings_result.importedLegacy) {
        ConfigLog.info("Legacy settings migration completed");
    }

    std::vector<std::filesystem::path> legacy_input{
        std::filesystem::path(user_path) / "keybindings.ini",
        std::filesystem::current_path() / "keybindings.ini",
    };
    if (const char* base_path = SDL_GetBasePath()) {
        legacy_input.emplace_back(std::filesystem::path(base_path) / "keybindings.ini");
    }
    acgc::input::register_defaults();
    acgc::prepare_legacy_input(user_path, legacy_input);

    const auto& settings = acgc::settings();
    if (!s_window_size_explicit) {
        windowDimensions.width = settings.video.windowWidth.value();
        windowDimensions.height = settings.video.windowHeight.value();
    }
    if (!s_frame_limit_explicit) {
        g_pc_frame_limit_override = settings.video.maxFrameRate.value();
    }

    if (s_uber_shader_requested) {
        MainLog.warn("--uber-shader is an OpenGL-backend option and has no Aurora equivalent; ignoring it");
    }
    if (g_pc_frame_limit_override >= 0) {
        VideoLog.info("Software frame limit: {}{}", g_pc_frame_limit_override,
                      g_pc_frame_limit_override == 0 ? " (uncapped)" : " FPS");
    }
    if (g_pc_time_override >= 0) {
        ClockLog.info("Override: hour={} minute={} second={}", g_pc_time_override,
                      g_pc_min_override, g_pc_sec_override);
    }
    if (g_pc_date_month > 0) {
        ClockLog.info("Override: month={} day={} year={}", g_pc_date_month, g_pc_date_day,
                      g_pc_date_year);
    }
    if (g_pc_weather_override >= 0) {
        WeatherLog.info("Override: weather={} intensity={}", g_pc_weather_override,
                        g_pc_weather_intensity_override);
    }

    AuroraConfig config{};
    config.appName = acgc::AppInfo.appName.data();
    config.userPath = user_path.empty() ? nullptr : user_path.c_str();
    config.cachePath = cache_path.empty() ? nullptr : cache_path.c_str();
    config.desiredBackend = settings.video.renderer.value();
    config.windowPosX = -1;
    config.windowPosY = -1;
    config.windowWidth = windowDimensions.width;
    config.windowHeight = windowDimensions.height;
    config.startFullscreen = settings.video.windowMode.value() != 0;
    config.mem1Size = 256 * 1024 * 1024;
    config.mem2Size = ARAM_DEFAULT_SIZE;
    config.vsync = s_frame_limit_explicit ? false : settings.video.vsync.value();
    config.pauseOnFocusLost = false;
    config.logCallback = borealis::log::aurora_callback();
    config.logLevel = borealis::log::to_aurora_level(s_log_level);
    config.imGuiInitCallback = &ac_debug_imgui_init;

    const AuroraInfo aurora_info = aurora_initialize(argc, argv, &config);
    AuroraSetViewportPolicy(AURORA_VIEWPORT_STRETCH);
    g_pc_window_w = windowDimensions.width;
    g_pc_window_h = windowDimensions.height;
    update_render_size();
    PADSetSpec(PAD_SPEC_5);
    PADInit();
    acgc::controller_ports::initialize();
    acgc::apply_legacy_keyboard_input();
    acgc::apply_runtime_settings(false);
    if (!acgc::ui::initialize()) {
        UiLog.error("Could not initialize the Aurora host menu");
        aurora_shutdown();
        return 1;
    }
    std::string discPath;
    bool launch = false;
    if (commandLine.discPathExplicit) {
        acgc::disc::DiscInfo info{};
        if (acgc::disc::inspect(commandLine.discPath, info) == acgc::disc::ValidationError::Success) {
            discPath = commandLine.discPath;
            launch = true;
        } else {
            DvdLog.warn("Command-line disc is not a supported Animal Crossing image: {}; opening prelaunch menu",
                        commandLine.discPath);
        }
    }

    if (!launch) {
        acgc::ui::ensure_prelaunch_initialized();
        auto& state = acgc::ui::prelaunch_state();
        if (settings.backend.skipPrelaunch.value() && state.configuredDiscCanLaunch) {
            discPath = state.configuredDiscPath;
            launch = true;
        } else if (run_prelaunch()) {
            discPath = state.activeDiscPath;
            launch = !discPath.empty();
        }
    }

    if (!launch) {
        acgc::ui::shutdown();
        aurora_shutdown();
        return 0;
    }

    if (!aurora_dvd_open(discPath.c_str())) {
        DvdLog.error("Could not open disc image: {}", discPath);
        acgc::ui::shutdown();
        aurora_shutdown();
        return 1;
    }

    if (!pc_assets_init()) {
        AssetsLog.error("Could not load game assets from: {}", discPath);
        aurora_dvd_close();
        acgc::ui::shutdown();
        aurora_shutdown();
        return 1;
    }

    pc_typing_initialize(aurora_info.window);
    pc_mouse_initialize(aurora_info.window);
    acgc::texture_replacements::reload();
    ac_entry();
    const int result = boot_main(argc, const_cast<const char**>(argv));

    pc_audio_shutdown();
    pc_audio_mq_shutdown();
    pc_typing_shutdown();
    acgc::controller_ports::shutdown();
    pc_mouse_shutdown();
    aurora_dvd_close();
    acgc::texture_replacements::shutdown();
    acgc::ui::shutdown();
    aurora_shutdown();
    return result;
}
