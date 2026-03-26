/* pc_main.c - PC entry point: SDL2/GL init, crash protection, boot sequence */
#ifndef _WIN32
#define _GNU_SOURCE  /* needed for dladdr */
#endif
#include "pc_platform.h"
#include "pc_gx_internal.h"
#include "pc_texture_pack.h"
#include "pc_settings.h"
#include "pc_keybindings.h"
#include "pc_assets.h"
#include "pc_disc.h"
#include "pc_typing.h"

/* prefer discrete GPU on laptops */
#ifdef _WIN32
__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
#endif

SDL_Window*   g_pc_window = NULL;
SDL_GLContext  g_pc_gl_context = NULL;
int           g_pc_running = 1;
int           g_pc_no_framelimit = 0;
int           g_pc_fast_forward = 0;
int           g_pc_verbose = 0;
int           g_pc_time_override = -1; /* -1=system clock, 0-23=override hour */
int           g_pc_min_override = -1; /* -1=system clock, 0-59=override minute */
int           g_pc_sec_override = -1; /* -1=system clock, 0-59=override second */
int           g_pc_window_w = PC_SCREEN_WIDTH;
int           g_pc_window_h = PC_SCREEN_HEIGHT;
int           g_pc_widescreen_stretch = 0;

/* exe image range -- used by seg2k0 to distinguish pointers from segment addresses */
uintptr_t pc_image_base = 0;
uintptr_t pc_image_end  = 0;

static jmp_buf* pc_active_jmpbuf = NULL;
static volatile uintptr_t pc_last_crash_addr = 0;

static volatile uintptr_t pc_last_crash_data_addr = 0;

#ifdef _WIN32
/* longjmp from VEH is technically UB, but works on x86 MinGW (no SEH to corrupt).
 * GCC doesn't have __try/__except and checking every pointer in emu64 is impractical. */
static LONG WINAPI pc_veh_handler(PEXCEPTION_POINTERS ep) {
    DWORD code = ep->ExceptionRecord->ExceptionCode;
    if (pc_active_jmpbuf != NULL &&
        (code == EXCEPTION_ACCESS_VIOLATION ||
         code == EXCEPTION_ILLEGAL_INSTRUCTION ||
         code == EXCEPTION_INT_DIVIDE_BY_ZERO ||
         code == EXCEPTION_PRIV_INSTRUCTION)) {
        pc_last_crash_addr = (uintptr_t)ep->ExceptionRecord->ExceptionAddress;
        if (code == EXCEPTION_ACCESS_VIOLATION)
            pc_last_crash_data_addr = (uintptr_t)ep->ExceptionRecord->ExceptionInformation[1];
        else
            pc_last_crash_data_addr = 0;
        jmp_buf* buf = pc_active_jmpbuf;
        pc_active_jmpbuf = NULL;
        longjmp(*buf, 1);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}
#else
/* POSIX equivalent of VEH — longjmp from signal handler (POSIX-defined for program faults) */
static void pc_signal_handler(int sig, siginfo_t* info, void* ucontext) {
    (void)ucontext;
    if (pc_active_jmpbuf != NULL) {
        pc_last_crash_addr = (uintptr_t)info->si_addr;
        pc_last_crash_data_addr = (sig == SIGSEGV) ?
            (uintptr_t)info->si_addr : 0;
        jmp_buf* buf = pc_active_jmpbuf;
        pc_active_jmpbuf = NULL;
        longjmp(*buf, 1);
    }
    signal(sig, SIG_DFL);
    raise(sig);
}
#endif

uintptr_t pc_crash_get_data_addr(void) {
    return pc_last_crash_data_addr;
}

void pc_crash_protection_init(void) {
    static int installed = 0;
    if (!installed) {
#ifdef _WIN32
        AddVectoredExceptionHandler(1, pc_veh_handler);
#else
        struct sigaction sa;
        memset(&sa, 0, sizeof(sa));
        sa.sa_sigaction = pc_signal_handler;
        sa.sa_flags = SA_SIGINFO;
        sigaction(SIGSEGV, &sa, NULL);
        sigaction(SIGILL, &sa, NULL);
        sigaction(SIGFPE, &sa, NULL);
#endif
        installed = 1;
    }
}

void pc_crash_set_jmpbuf(jmp_buf* buf) {
    pc_active_jmpbuf = buf;
}

uintptr_t pc_crash_get_addr(void) {
    return pc_last_crash_addr;
}

void pc_platform_init(void) {
#ifdef _WIN32
    SetProcessDPIAware();
#endif
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#ifdef __APPLE__
    /* macOS requires forward-compatible flag for Core Profile contexts */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#ifdef PC_ENHANCEMENTS
    if (g_pc_settings.msaa > 0) {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, g_pc_settings.msaa);
    }
#endif

    {
        Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
        int win_w = g_pc_settings.window_width;
        int win_h = g_pc_settings.window_height;
        if (g_pc_settings.fullscreen == 1) {
            flags |= SDL_WINDOW_FULLSCREEN;
        } else if (g_pc_settings.fullscreen == 2) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        g_pc_window = SDL_CreateWindow(
            PC_WINDOW_TITLE,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            win_w, win_h, flags
        );
    }
    if (!g_pc_window) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    g_pc_gl_context = SDL_GL_CreateContext(g_pc_window);
    if (!g_pc_gl_context) {
        fprintf(stderr, "SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(g_pc_window);
        SDL_Quit();
        exit(1);
    }

    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
        fprintf(stderr, "gladLoadGL failed\n");
        SDL_GL_DeleteContext(g_pc_gl_context);
        SDL_DestroyWindow(g_pc_window);
        SDL_Quit();
        exit(1);
    }

    if (g_pc_verbose) {
        const char* vendor = (const char*)glGetString(GL_VENDOR);
        const char* renderer = (const char*)glGetString(GL_RENDERER);
        const char* version = (const char*)glGetString(GL_VERSION);
        const char* glsl = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
        printf("[GL] Vendor: %s\n", vendor ? vendor : "Unknown");
        printf("[GL] Renderer: %s\n", renderer ? renderer : "Unknown");
        printf("[GL] Version: %s\n", version ? version : "Unknown");
        printf("[GL] GLSL: %s\n", glsl ? glsl : "Unknown");
        const char* sdl_driver = SDL_GetCurrentVideoDriver();
        printf("[SDL] Video Driver: %s\n", sdl_driver ? sdl_driver : "Unknown");
    }

#ifndef _WIN32
    {
        const char* renderer = (const char*)glGetString(GL_RENDERER);
        if (renderer && (strstr(renderer, "llvmpipe") || strstr(renderer, "softpipe"))) {
            const char* sdl_driver = SDL_GetCurrentVideoDriver();
            fprintf(stderr, "\n--- WARNING ---\n"
                            "Game is running on software renderer (llvmpipe/softpipe).\n"
                            "This likely means 32-bit graphics drivers are missing on your system.\n");
            if (sdl_driver && strcmp(sdl_driver, "wayland") == 0) {
                fprintf(stderr, "On Wayland, ensure you have lib32-egl-wayland installed.\n"
                                "Alternatively, try running with: SDL_VIDEODRIVER=x11\n");
            }
            fprintf(stderr, "----------------\n\n");
        }
    }
#endif

    SDL_GL_SetSwapInterval(g_pc_settings.vsync);

    pc_platform_update_window_size();

#ifdef PC_ENHANCEMENTS
    if (g_pc_settings.msaa > 0) {
        glEnable(GL_MULTISAMPLE);
    }
#endif

    pc_gx_init();
    pc_texture_pack_init();
#ifdef PC_ENHANCEMENTS
    if (g_pc_settings.preload_textures) {
        pc_texture_pack_preload_all();
    }
#endif
}

extern void PADCleanup(void);

void pc_platform_shutdown(void) {
    pc_audio_shutdown();
    pc_audio_mq_shutdown();
    PADCleanup();
    pc_texture_pack_shutdown();
    pc_gx_shutdown();

    if (g_pc_gl_context) {
        SDL_GL_DeleteContext(g_pc_gl_context);
        g_pc_gl_context = NULL;
    }
    if (g_pc_window) {
        SDL_DestroyWindow(g_pc_window);
        g_pc_window = NULL;
    }
    SDL_Quit();
}

void pc_platform_update_window_size(void) {
    SDL_GL_GetDrawableSize(g_pc_window, &g_pc_window_w, &g_pc_window_h);
    if (g_pc_window_w <= 0) g_pc_window_w = PC_SCREEN_WIDTH;
    if (g_pc_window_h <= 0) g_pc_window_h = PC_SCREEN_HEIGHT;
}

void pc_platform_swap_buffers(void) {
    /* One-time pixel color diagnostic */
    {
        static int diag_frame = 0;
        if (diag_frame >= 180 && diag_frame < 185) {
            u8 px[4];
            int cx = g_pc_window_w / 2, cy = g_pc_window_h / 2;
            /* Sample center, and 5 points around the character area */
            struct { int x, y; const char* label; } pts[] = {
                {cx, cy, "center"},
                {cx, cy + 50, "char_body"},
                {cx - 30, cy + 30, "char_left"},
                {cx + 30, cy + 30, "char_right"},
                {cx, cy - 80, "above"},
                {50, 50, "top_left"},
            };
            fprintf(stderr, "[PIXEL] frame=%d:", diag_frame);
            for (int i = 0; i < 6; i++) {
                glReadPixels(pts[i].x, g_pc_window_h - pts[i].y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);
                fprintf(stderr, " %s=(%d,%d,%d,%d)", pts[i].label, px[0], px[1], px[2], px[3]);
            }
            fprintf(stderr, "\n");
        }
        diag_frame++;
    }
    SDL_GL_SwapWindow(g_pc_window);
}

static int pc_confirm_quit(void) {
    const SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancel" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Quit" },
    };
    const SDL_MessageBoxData data = {
        SDL_MESSAGEBOX_INFORMATION, g_pc_window,
        "Animal Crossing", "Are you sure you want to quit?",
        2, buttons, NULL
    };
    int button = 0;
    if (SDL_ShowMessageBox(&data, &button) < 0)
        return 1; /* on error, just quit */
    return button == 1;
}

int pc_platform_poll_events(void) {
    SDL_Event event;

    pc_typing_update();

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                if (pc_confirm_quit()) {
                    g_pc_running = 0;
                    return 0;
                }
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    pc_platform_update_window_size();
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    if (pc_confirm_quit()) {
                        g_pc_running = 0;
                        return 0;
                    }
                }
                if (event.key.keysym.sym == SDLK_F3 && !event.key.repeat) {
                    g_pc_no_framelimit ^= 1;
                    printf("[PC] Frame limiter %s\n", g_pc_no_framelimit ? "OFF" : "ON");
                }
                if (event.key.keysym.sym == SDLK_F4 && !event.key.repeat) {
                    g_pc_fast_forward ^= 1;
                    printf("[PC] Fast forward %s (2x)\n", g_pc_fast_forward ? "ON" : "OFF");
                }
                pc_typing_handle_event(&event);
                break;
            case SDL_TEXTINPUT:
                pc_typing_handle_event(&event);
                break;
        }
    }
    return 1;
}

/* game's main() renamed to ac_entry via -Dmain=ac_entry, boot.c's to boot_main */
extern void ac_entry(void);
extern int boot_main(int argc, const char** argv);

int main(int argc, char* argv[]) {
#ifndef _WIN32
    /* prefer discrete GPU on Linux (NVIDIA PRIME and AMD) while respecting user overrides */
    setenv("__NV_PRIME_RENDER_OFFLOAD", "1", 0);
    setenv("__GLX_VENDOR_LIBRARY_NAME", "nvidia", 0);
    setenv("__VK_LAYER_NV_optimus", "NVIDIA_only", 0);
    setenv("DRI_PRIME", "1", 0);

    const char* wayland_display = getenv("WAYLAND_DISPLAY");
    const char* x11_display = getenv("DISPLAY");

#if UINTPTR_MAX <= 0xFFFFFFFFu
    /* On 32-bit Linux, Wayland/EGL often fails to load discrete drivers (lib32-nvidia-utils).
     * We default to X11 (XWayland) for stability, but allow user override via SDL_VIDEODRIVER. */
    if (wayland_display != NULL && x11_display != NULL) {
        setenv("SDL_VIDEODRIVER", "x11", 0);
    }
#endif

    const char* sdl_vid_drv = getenv("SDL_VIDEODRIVER");
    if (sdl_vid_drv != NULL && strcmp(sdl_vid_drv, "x11") == 0) {
        /* prefer GLX on X11 to prevent EGL fallback issues on some discrete drivers */
        setenv("SDL_VIDEO_GL_DRIVER", "libGL.so.1", 0);
    } else if (sdl_vid_drv == NULL && x11_display != NULL && wayland_display == NULL) {
        /* No driver set, and only X11 is available - safe to prefer GLX */
        setenv("SDL_VIDEO_GL_DRIVER", "libGL.so.1", 0);
    }
#endif

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            printf("Usage: AnimalCrossing [options]\n");
            printf("  --verbose, -v       Enable diagnostic output\n");
            printf("  --no-framelimit     Disable frame limiter\n");
            printf("  --model-viewer [N]  Launch model viewer (optional start index)\n");
            printf("  --time H[:M[:S]]    Override in-game time (e.g. 5, 17:30, 5:55:00)\n");
            printf("  --help, -h          Show this help message\n");
            return 0;
        } else if (strcmp(argv[i], "--no-framelimit") == 0) {
            g_pc_no_framelimit = 1;
        } else if (strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0) {
            g_pc_verbose = 1;
        } else if (strcmp(argv[i], "--model-viewer") == 0) {
            g_pc_model_viewer = 1;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                g_pc_model_viewer_start = atoi(argv[i + 1]);
                i++;
            }
        } else if (strcmp(argv[i], "--time") == 0 && i + 1 < argc) {
            int h = -1, m = -1, s = -1;
            sscanf(argv[i + 1], "%d:%d:%d", &h, &m, &s);
            if (h >= 0 && h <= 23) g_pc_time_override = h;
            if (m >= 0 && m <= 59) g_pc_min_override = m;
            if (s >= 0 && s <= 59) g_pc_sec_override = s;
            i++;
        }
    }

    /* Redirect stdout/stderr to NUL unless verbose — unbuffered terminal writes
     * are extremely slow on Windows and tank FPS. */
    if (!g_pc_verbose) {
#ifdef _WIN32
        freopen("NUL", "w", stdout);
        freopen("NUL", "w", stderr);
#else
        freopen("/dev/null", "w", stdout);
        freopen("/dev/null", "w", stderr);
#endif
    } else {
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);
    }

    /* exe image range for seg2k0 — BSS can overlap N64 segment addresses */
#ifdef _WIN32
    {
        HMODULE exe = GetModuleHandle(NULL);
        IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)exe;
        IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)((char*)exe + dos->e_lfanew);
        pc_image_base = (uintptr_t)exe;
        pc_image_end = pc_image_base + nt->OptionalHeader.SizeOfImage;
    }
#elif defined(__APPLE__)
    {
        /* macOS: use dladdr — no ELF headers available */
        Dl_info dl;
        if (dladdr((void*)main, &dl) && dl.dli_fbase) {
            pc_image_base = (uintptr_t)dl.dli_fbase;
            /* Estimate image end — on 64-bit, seg2k0 uses threshold check
             * instead of image range, so this is defense-in-depth only. */
            pc_image_end = pc_image_base + 0x10000000;
        }
    }
#else
    {
        Dl_info dl;
        if (dladdr((void*)main, &dl) && dl.dli_fbase) {
            pc_image_base = (uintptr_t)dl.dli_fbase;
#if UINTPTR_MAX > 0xFFFFFFFFu
            /* 64-bit ELF */
            Elf64_Ehdr* ehdr = (Elf64_Ehdr*)dl.dli_fbase;
            Elf64_Phdr* phdr = (Elf64_Phdr*)((char*)dl.dli_fbase + ehdr->e_phoff);
            uintptr_t max_end = 0;
            for (int i = 0; i < ehdr->e_phnum; i++) {
                if (phdr[i].p_type == PT_LOAD) {
                    uintptr_t seg_end = phdr[i].p_vaddr + phdr[i].p_memsz;
                    if (seg_end > max_end) max_end = seg_end;
                }
            }
#else
            /* 32-bit ELF */
            Elf32_Ehdr* ehdr = (Elf32_Ehdr*)dl.dli_fbase;
            Elf32_Phdr* phdr = (Elf32_Phdr*)((char*)dl.dli_fbase + ehdr->e_phoff);
            uintptr_t max_end = 0;
            for (int i = 0; i < ehdr->e_phnum; i++) {
                if (phdr[i].p_type == PT_LOAD) {
                    uintptr_t seg_end = phdr[i].p_vaddr + phdr[i].p_memsz;
                    if (seg_end > max_end) max_end = seg_end;
                }
            }
#endif
            /* ET_EXEC: p_vaddr is absolute. ET_DYN (PIE): relative to load address. */
            if (ehdr->e_type == ET_DYN) {
                pc_image_end = pc_image_base + max_end;
            } else {
                pc_image_end = max_end;
            }
        }
    }
#endif

    SDL_SetMainReady();
    pc_settings_load();
    pc_keybindings_load();
    pc_platform_init();
    pc_disc_init();
    pc_assets_init();

    ac_entry();                         /* sets HotStartEntry = &entry */
    boot_main(argc, (const char**)argv); /* full init → HotStartEntry → game loop */

    pc_disc_shutdown();
    pc_platform_shutdown();
    return 0;
}
