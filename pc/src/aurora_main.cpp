#include <aurora/aurora.h>
#include <aurora/dvd.h>
#include <aurora/event.h>
#include <aurora/gfx.h>
#include <aurora/main.h>
#include <dolphin/gx/GXAurora.h>
#include <dolphin/pad.h>
#include <SDL3/SDL.h>

#include "pc_assets.h"
#include "pc_platform.h"
#include "aurora_debug.h"
#include "acgc/legacy_input.hpp"
#include "acgc/settings.hpp"
#include "acgc/texture_replacements.hpp"
#include "acgc/ui/ui.hpp"
#include "m_kankyo.h"
#include "port/logging.h"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
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

bool ac_aurora_begin_frame() {
    /* Display-list markers may leave this in transition/UI mode. The legacy
     * renderer reset it before every frame, before JSystem submits GX state. */
    g_pc_widescreen_stretch = 0;
    pc_emu64_frame_cmds = 0;
    pc_emu64_frame_noop_cmds = 0;
    pc_emu64_frame_tri_cmds = 0;
    pc_emu64_frame_vtx_cmds = 0;
    pc_emu64_frame_dl_cmds = 0;
    pc_emu64_frame_cull_visible = 0;
    pc_emu64_frame_cull_rejected = 0;

    const AuroraEvent* event = aurora_update();
    while (event != nullptr && event->type != AURORA_NONE) {
        if (event->type == AURORA_EXIT) {
            g_pc_running = 0;
        } else if (event->type == AURORA_SDL_EVENT) {
            acgc::ui::handle_event(event->sdl);
        } else if (event->type == AURORA_CONTROLLER_ADDED) {
            acgc::apply_runtime_settings(false);
        }
        ++event;
    }

    if (!g_pc_running) {
        return false;
    }

    update_render_size();
    s_frame_started = aurora_begin_frame();
    return s_frame_started;
}

void ac_aurora_end_frame() {
    if (s_frame_started) {
        acgc::ui::update();
        ac_debug_imgui_draw();
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

bool s_show_help = false;
bool s_uber_shader_requested = false;
bool s_log_level_explicit = false;
bool s_frame_limit_explicit = false;
bool s_window_size_explicit = false;
AuroraLogLevel s_log_level = LOG_INFO;
std::string s_log_directory;
std::string s_user_directory;

struct PortLogGuard {
    ~PortLogGuard() {
        port_log_shutdown();
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

void print_usage() {
    std::printf("Usage: AnimalCrossing [options] [disc image]\n");
    std::printf("  --disc PATH          Open an RVZ, ISO, or GCM image (default: game.rvz)\n");
    std::printf("  --window-size WxH    Set the initial window size (minimum 320x240)\n");
    std::printf("  --widescreen         Start at 1280x720\n");
    std::printf("  --profile [N]        Show performance diagnostics\n");
    std::printf("  --model-viewer [N]   Launch the model viewer at optional structure N\n");
    std::printf("  --framelimit N       Set a software frame limit (0 = uncapped)\n");
    std::printf("  --no-framelimit      Run uncapped\n");
    std::printf("  --time H[:M[:S]]     Override the in-game clock\n");
    std::printf("  --date M/D[/Y]       Override the in-game date\n");
    std::printf("  --rain [intensity]   Force light, normal, or heavy rain\n");
    std::printf("  --verbose, -v        Enable additional game diagnostics\n");
    std::printf("  --log-level LEVEL    Set debug, info, warning, or error logging\n");
    std::printf("  --log-dir PATH       Override the rotating log-file directory\n");
    std::printf("  --user-dir PATH      Override configuration, saves, mappings, and logs\n");
    std::printf("  --help, -h           Show this help\n");
}

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

bool parse_log_level(const char* text, AuroraLogLevel* level) {
    if (text == nullptr || level == nullptr)
        return false;
    if (std::strcmp(text, "debug") == 0)
        *level = LOG_DEBUG;
    else if (std::strcmp(text, "info") == 0)
        *level = LOG_INFO;
    else if (std::strcmp(text, "warning") == 0 || std::strcmp(text, "warn") == 0)
        *level = LOG_WARNING;
    else if (std::strcmp(text, "error") == 0)
        *level = LOG_ERROR;
    else
        return false;
    return true;
}

bool runtime_options_from_args(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0) {
            s_show_help = true;
        } else if (std::strcmp(argv[i], "--verbose") == 0 || std::strcmp(argv[i], "-v") == 0) {
            g_pc_verbose = 1;
        } else if (std::strcmp(argv[i], "--log-level") == 0) {
            if (i + 1 >= argc || !parse_log_level(argv[++i], &s_log_level)) {
                std::fprintf(stderr, "--log-level expects debug, info, warning, or error\n");
                return false;
            }
            s_log_level_explicit = true;
        } else if (std::strcmp(argv[i], "--log-dir") == 0) {
            if (i + 1 >= argc || argv[i + 1][0] == '\0') {
                std::fprintf(stderr, "--log-dir expects a directory path\n");
                return false;
            }
            s_log_directory = argv[++i];
        } else if (std::strcmp(argv[i], "--user-dir") == 0) {
            if (i + 1 >= argc || argv[i + 1][0] == '\0') {
                std::fprintf(stderr, "--user-dir expects a directory path\n");
                return false;
            }
            s_user_directory = argv[++i];
        } else if (std::strcmp(argv[i], "--no-framelimit") == 0) {
            g_pc_frame_limit_override = 0;
            s_frame_limit_explicit = true;
        } else if (std::strcmp(argv[i], "--framelimit") == 0) {
            int limit = -1;
            if (i + 1 >= argc || !parse_nonnegative_integer(argv[++i], &limit)) {
                std::fprintf(stderr, "--framelimit expects a nonnegative integer\n");
                return false;
            }
            g_pc_frame_limit_override = limit;
            s_frame_limit_explicit = true;
        } else if (std::strcmp(argv[i], "--profile") == 0) {
            /* Aurora's live diagnostics replace the OpenGL console profiler. */
            g_pc_debug_ui_visible = 1;
            int ignored_interval = 0;
            if (i + 1 < argc && parse_nonnegative_integer(argv[i + 1], &ignored_interval)) {
                ++i;
            }
        } else if (std::strcmp(argv[i], "--uber-shader") == 0) {
            s_uber_shader_requested = true;
        } else if (std::strcmp(argv[i], "--time") == 0) {
            if (i + 1 >= argc) {
                std::fprintf(stderr, "--time expects H[:M[:S]]\n");
                return false;
            }
            int hour = -1;
            int minute = -1;
            int second = -1;
            std::sscanf(argv[++i], "%d:%d:%d", &hour, &minute, &second);
            if (hour < 0 || hour > 23 || minute > 59 || second > 59) {
                std::fprintf(stderr, "--time expects H[:M[:S]] in the 24-hour clock\n");
                return false;
            }
            g_pc_time_override = hour;
            if (minute >= 0)
                g_pc_min_override = minute;
            if (second >= 0)
                g_pc_sec_override = second;
        } else if (std::strcmp(argv[i], "--date") == 0) {
            if (i + 1 >= argc) {
                std::fprintf(stderr, "--date expects M/D[/Y]\n");
                return false;
            }
            int month = -1;
            int day = -1;
            int year = -1;
            std::sscanf(argv[++i], "%d/%d/%d", &month, &day, &year);
            if (month < 1 || month > 12 || day < 1 || day > 31 || (year >= 0 && year < 2000)) {
                std::fprintf(stderr, "--date expects M/D[/Y] with year 2000 or later\n");
                return false;
            }
            g_pc_date_month = month;
            g_pc_date_day = day;
            if (year >= 0)
                g_pc_date_year = year;
        } else if (std::strcmp(argv[i], "--rain") == 0) {
            g_pc_weather_override = mEnv_WEATHER_RAIN;
            g_pc_weather_intensity_override = mEnv_WEATHER_INTENSITY_HEAVY;
            if (i + 1 < argc) {
                const int intensity = parse_rain_intensity(argv[i + 1]);
                if (intensity >= 0) {
                    g_pc_weather_intensity_override = intensity;
                    ++i;
                }
            }
        }
    }
    if (g_pc_verbose && !s_log_level_explicit) {
        s_log_level = LOG_DEBUG;
    }
    return true;
}

void apply_frame_limit() {
    using clock = std::chrono::steady_clock;
    static clock::time_point next_frame{};

    if (g_pc_frame_limit_override <= 0) {
        next_frame = {};
        return;
    }

    const auto interval = std::chrono::nanoseconds(1'000'000'000LL / g_pc_frame_limit_override);
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

bool window_dimensions_from_args(int argc, char* argv[], WindowDimensions* dimensions) {
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--widescreen") == 0) {
            dimensions->width = 1280;
            dimensions->height = 720;
            s_window_size_explicit = true;
        } else if (std::strcmp(argv[i], "--window-size") == 0) {
            if (i + 1 >= argc || !parse_window_dimensions(argv[++i], dimensions)) {
                std::fprintf(stderr, "--window-size expects WIDTHxHEIGHT (minimum 320x240)\n");
                return false;
            }
            s_window_size_explicit = true;
        }
    }
    return true;
}

bool parse_model_viewer_index(const char* text, int* index) {
    return parse_nonnegative_integer(text, index);
}

void model_viewer_from_args(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--model-viewer") == 0) {
            g_pc_model_viewer = 1;
            int index = -1;
            if (i + 1 < argc && parse_model_viewer_index(argv[i + 1], &index)) {
                g_pc_model_viewer_start = index;
                ++i;
            }
        }
    }
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
        port_log_printf(LOG_INFO, "acgc::video", "Render size %ux%u (aspect factor %.4f)", width, height,
                        pc_widescreen_get_aspect_factor());
    }
}

const char* disc_path_from_args(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--disc") == 0 && i + 1 < argc) {
            return argv[i + 1];
        }
        if (std::strcmp(argv[i], "--window-size") == 0 && i + 1 < argc) {
            ++i;
            continue;
        }
        if (std::strcmp(argv[i], "--widescreen") == 0) {
            continue;
        }
        if (std::strcmp(argv[i], "--model-viewer") == 0) {
            int index = -1;
            if (i + 1 < argc && parse_model_viewer_index(argv[i + 1], &index)) {
                ++i;
            }
            continue;
        }
        if (std::strcmp(argv[i], "--framelimit") == 0 || std::strcmp(argv[i], "--time") == 0 ||
            std::strcmp(argv[i], "--date") == 0 || std::strcmp(argv[i], "--log-level") == 0 ||
            std::strcmp(argv[i], "--log-dir") == 0 || std::strcmp(argv[i], "--user-dir") == 0) {
            if (i + 1 < argc)
                ++i;
            continue;
        }
        if (std::strcmp(argv[i], "--rain") == 0) {
            if (i + 1 < argc && parse_rain_intensity(argv[i + 1]) >= 0)
                ++i;
            continue;
        }
        if (std::strcmp(argv[i], "--profile") == 0) {
            int ignored_interval = 0;
            if (i + 1 < argc && parse_nonnegative_integer(argv[i + 1], &ignored_interval))
                ++i;
            continue;
        }
        if (std::strcmp(argv[i], "--no-framelimit") == 0 || std::strcmp(argv[i], "--uber-shader") == 0 ||
            std::strcmp(argv[i], "--verbose") == 0 ||
            std::strcmp(argv[i], "-v") == 0 || std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0) {
            continue;
        }
        if (argv[i][0] != '-') {
            return argv[i];
        }
    }
    return "game.rvz";
}

void configure_default_keyboard_input() {
    u32 binding_count = 0;
    if (PADGetKeyButtonBindings(0, &binding_count) != nullptr) {
        return;
    }

    PADKeyButtonBinding buttons[PAD_BUTTON_COUNT] = {
        { SDL_SCANCODE_SPACE, PAD_BUTTON_A },      { SDL_SCANCODE_LSHIFT, PAD_BUTTON_B },
        { SDL_SCANCODE_X, PAD_BUTTON_X },          { SDL_SCANCODE_Y, PAD_BUTTON_Y },
        { SDL_SCANCODE_RETURN, PAD_BUTTON_START }, { SDL_SCANCODE_Z, PAD_TRIGGER_Z },
        { SDL_SCANCODE_Q, PAD_TRIGGER_L },         { SDL_SCANCODE_E, PAD_TRIGGER_R },
        { SDL_SCANCODE_I, PAD_BUTTON_UP },         { SDL_SCANCODE_K, PAD_BUTTON_DOWN },
        { SDL_SCANCODE_J, PAD_BUTTON_LEFT },       { SDL_SCANCODE_L, PAD_BUTTON_RIGHT },
    };
    PADKeyAxisBinding axes[PAD_AXIS_COUNT] = {
        { SDL_SCANCODE_D, PAD_AXIS_LEFT_X_POS, 100 },      { SDL_SCANCODE_A, PAD_AXIS_LEFT_X_NEG, 100 },
        { SDL_SCANCODE_W, PAD_AXIS_LEFT_Y_POS, 100 },      { SDL_SCANCODE_S, PAD_AXIS_LEFT_Y_NEG, 100 },
        { SDL_SCANCODE_RIGHT, PAD_AXIS_RIGHT_X_POS, 100 }, { SDL_SCANCODE_LEFT, PAD_AXIS_RIGHT_X_NEG, 100 },
        { SDL_SCANCODE_UP, PAD_AXIS_RIGHT_Y_POS, 100 },    { SDL_SCANCODE_DOWN, PAD_AXIS_RIGHT_Y_NEG, 100 },
        { SDL_SCANCODE_Q, PAD_AXIS_TRIGGER_L, 100 },       { SDL_SCANCODE_E, PAD_AXIS_TRIGGER_R, 100 },
    };

    PADSetKeyButtonBindings(0, buttons);
    PADSetKeyAxisBindings(0, axes);
    PADSetKeyboardActive(0, TRUE);
}

} // namespace

int main(int argc, char* argv[]) {
    WindowDimensions windowDimensions;
    if (!runtime_options_from_args(argc, argv) || !window_dimensions_from_args(argc, argv, &windowDimensions)) {
        return 2;
    }
    if (s_show_help) {
        print_usage();
        return 0;
    }
    model_viewer_from_args(argc, argv);

    std::string user_path = s_user_directory;
    if (user_path.empty()) {
        if (char* path = SDL_GetPrefPath(nullptr, "Animal Crossing")) {
            user_path = path;
            SDL_free(path);
        }
    }
    if (user_path.empty()) {
        std::error_code error;
        user_path = std::filesystem::current_path(error).string();
    }
    std::string log_directory = s_log_directory;
    if (log_directory.empty() && !user_path.empty()) {
        log_directory = (std::filesystem::path(user_path) / "logs").string();
    }
    PortLogConfig log_config{};
    log_config.log_directory = log_directory.c_str();
    log_config.filename_prefix = "animal-crossing";
    log_config.minimum_level = s_log_level;
    log_config.max_retained_files = 10;
    log_config.max_retained_bytes = 100ull * 1024ull * 1024ull;
    log_config.write_console = true;
    port_log_initialize(&log_config);
    PortLogGuard log_guard;
    if (const char* log_path = port_log_file_path()) {
        port_log_printf(LOG_INFO, "acgc", "Logging to %s", log_path);
    } else {
        port_log_printf(LOG_WARNING, "acgc", "File logging is unavailable; continuing with console logging");
    }

    std::vector<std::filesystem::path> legacy_settings{
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
        port_log_printf(LOG_INFO, "acgc::config", "Legacy settings migration completed");
    }

    std::vector<std::filesystem::path> legacy_input{
        std::filesystem::path(user_path) / "keybindings.ini",
        std::filesystem::current_path() / "keybindings.ini",
    };
    if (const char* base_path = SDL_GetBasePath()) {
        legacy_input.emplace_back(std::filesystem::path(base_path) / "keybindings.ini");
    }
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
        port_log_printf(LOG_WARNING, "acgc",
                        "--uber-shader is an OpenGL-backend option and has no Aurora equivalent; ignoring it");
    }
    if (g_pc_frame_limit_override >= 0) {
        port_log_printf(LOG_INFO, "acgc::video", "Software frame limit: %d%s", g_pc_frame_limit_override,
                        g_pc_frame_limit_override == 0 ? " (uncapped)" : " FPS");
    }
    if (g_pc_time_override >= 0) {
        port_log_printf(LOG_INFO, "acgc::clock", "Override: hour=%d minute=%d second=%d", g_pc_time_override,
                        g_pc_min_override, g_pc_sec_override);
    }
    if (g_pc_date_month > 0) {
        port_log_printf(LOG_INFO, "acgc::clock", "Override: month=%d day=%d year=%d", g_pc_date_month, g_pc_date_day,
                        g_pc_date_year);
    }
    if (g_pc_weather_override >= 0) {
        port_log_printf(LOG_INFO, "acgc::weather", "Override: weather=%d intensity=%d", g_pc_weather_override,
                        g_pc_weather_intensity_override);
    }

    AuroraConfig config{};
    config.appName = "Animal Crossing";
    config.userPath = user_path.empty() ? nullptr : user_path.c_str();
    config.windowPosX = -1;
    config.windowPosY = -1;
    config.windowWidth = windowDimensions.width;
    config.windowHeight = windowDimensions.height;
    config.startFullscreen = settings.video.windowMode.value() != 0;
    config.msaa = static_cast<uint32_t>(settings.video.msaa.value());
    // Match Dusklight's 64-bit JSystem host policy. Native pointers enlarge
    // heap metadata and many decompiled runtime objects beyond GC-era sizes.
    config.mem1Size = 256 * 1024 * 1024;
    config.mem2Size = ARAM_DEFAULT_SIZE;
    /* An explicit limit uses the software limiter so arbitrary rates and the
     * legacy uncapped mode do not depend on the monitor's refresh rate. */
    config.vsync = s_frame_limit_explicit ? false : settings.video.vsync.value();
    config.pauseOnFocusLost = false;
    config.logCallback = &port_log_callback;
    config.logLevel = s_log_level;
    config.imGuiInitCallback = &ac_debug_imgui_init;

    aurora_initialize(argc, argv, &config);
    /* Match Dusklight's unlocked-aspect path: Aurora owns a framebuffer with
     * the window's aspect, while game-side GX wrappers preserve 4:3 content. */
    AuroraSetViewportPolicy(AURORA_VIEWPORT_STRETCH);
    g_pc_window_w = windowDimensions.width;
    g_pc_window_h = windowDimensions.height;
    update_render_size();
    PADSetSpec(PAD_SPEC_5);
    PADInit();
    acgc::apply_legacy_keyboard_input();
    configure_default_keyboard_input();
    acgc::apply_runtime_settings(false);
    if (!acgc::ui::initialize()) {
        port_log_printf(LOG_ERROR, "acgc::ui", "Could not initialize the Aurora host menu");
        aurora_shutdown();
        return 1;
    }
    const char* disc_path = disc_path_from_args(argc, argv);
    if (!aurora_dvd_open(disc_path)) {
        port_log_printf(LOG_ERROR, "acgc::dvd", "Could not open disc image: %s", disc_path);
        acgc::ui::shutdown();
        aurora_shutdown();
        return 1;
    }

    if (!pc_assets_init()) {
        port_log_printf(LOG_ERROR, "acgc::assets", "Could not load game assets from: %s", disc_path);
        aurora_dvd_close();
        acgc::ui::shutdown();
        aurora_shutdown();
        return 1;
    }

    acgc::texture_replacements::reload();
    ac_entry();
    const int result = boot_main(argc, const_cast<const char**>(argv));

    pc_audio_shutdown();
    pc_audio_mq_shutdown();
    aurora_dvd_close();
    acgc::texture_replacements::shutdown();
    acgc::ui::shutdown();
    aurora_shutdown();
    return result;
}
