/* pc_discord.c - Discord Rich Presence over the local IPC named pipe.
 *
 * Implements just enough of Discord's documented RPC protocol (handshake +
 * SET_ACTIVITY) to show what town/location the player is in. No official
 * SDK or third-party library needed - it's a small JSON-over-named-pipe
 * protocol: https://discord.com/developers/docs/topics/rpc
 *
 * All pipe I/O happens on a dedicated thread so a slow/absent Discord client
 * can never stall the game's frame loop. The game thread only ever touches
 * a small mutex-guarded "desired presence" struct.
 *
 * No-ops entirely if settings.ini has no discord_client_id (feature is
 * opt-in; there's nothing to connect to without an Application ID from
 * https://discord.com/developers/applications).
 */
#include "pc_platform.h"
#include "pc_discord.h"
#include "pc_settings.h"
#include "m_common_data.h"
#include "m_font.h"
#include "m_land.h"
#include "m_scene_table.h"

#ifdef _WIN32

#define DISCORD_OP_HANDSHAKE 0
#define DISCORD_OP_FRAME 1

/* Enough to feel live without spamming the pipe (Discord rate-limits
 * presence updates to roughly one per 15s anyway). */
#define DISCORD_UPDATE_INTERVAL_MS 5000
#define DISCORD_RECONNECT_DELAY_MS 5000

/* Default when no save is loaded or the town has no printable name. */
static const char DEFAULT_DETAILS[] = "Playing Animal Crossing";

typedef struct {
    char details[128];
    char state[128]; /* "" = no state line */
    int version;     /* bumped whenever details/state change */
} pc_discord_presence_t;

static SDL_Thread* s_thread = NULL;
static SDL_atomic_t s_running;
static SDL_mutex* s_mutex = NULL;
static pc_discord_presence_t s_desired;
static int s_sent_version = -1;
static char s_client_id[32];
static long long s_start_time = 0;
static HANDLE s_pipe = INVALID_HANDLE_VALUE;

/* Discord (or another RPC app) may hold any of discord-ipc-0..9; with
 * multiple clients running (e.g. stable + Canary) the active one is often
 * not on -0, so probe all ten. */
static int pc_discord_connect(void) {
    char pipe_name[32];
    int i;

    for (i = 0; i <= 9; i++) {
        snprintf(pipe_name, sizeof(pipe_name), "\\\\.\\pipe\\discord-ipc-%d", i);
        s_pipe = CreateFileA(pipe_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (s_pipe != INVALID_HANDLE_VALUE) {
            return 1;
        }
    }
    return 0;
}

static void pc_discord_disconnect(void) {
    if (s_pipe != INVALID_HANDLE_VALUE) {
        CloseHandle(s_pipe);
        s_pipe = INVALID_HANDLE_VALUE;
    }
}

/* The pipe may be message-mode, where each WriteFile call is a distinct
 * message. Header and payload must go in a single write or Discord's
 * parser desyncs silently (writes still "succeed", nothing shows up). */
static int pc_discord_send_frame(int opcode, const char* json, int len) {
    char buf[8 + 512];
    DWORD written;

    if ((size_t)len > sizeof(buf) - 8) return 0;

    ((int*)buf)[0] = opcode;
    ((int*)buf)[1] = len;
    memcpy(buf + 8, json, (size_t)len);

    if (!WriteFile(s_pipe, buf, (DWORD)(8 + len), &written, NULL) || written != (DWORD)(8 + len)) {
        return 0;
    }
    return 1;
}

/* Appends src to out[*pos..], backslash-escaping " and \. */
static void json_escape_append(char* out, size_t out_size, size_t* pos, const char* src) {
    for (; *src != '\0' && *pos + 2 < out_size; src++) {
        if (*src == '"' || *src == '\\') {
            out[(*pos)++] = '\\';
        }
        out[(*pos)++] = *src;
    }
}

/* snprintf returns the would-be length when it truncates; clamp so pos
 * stays a valid offset and sizeof(json) - pos can't underflow. */
static size_t clamp_pos(size_t pos, size_t size) {
    return pos < size ? pos : size - 1;
}

/* state may be "" to omit the state line entirely. */
static int pc_discord_send_activity(const char* details, const char* state) {
    char json[512];
    size_t pos;

    pos = (size_t)snprintf(json, sizeof(json),
                           "{\"cmd\":\"SET_ACTIVITY\",\"args\":{\"pid\":%lu,\"activity\":{\"details\":\"",
                           (unsigned long)GetCurrentProcessId());
    pos = clamp_pos(pos, sizeof(json));
    json_escape_append(json, sizeof(json), &pos, details);

    if (state[0] != '\0') {
        pos += (size_t)snprintf(json + pos, sizeof(json) - pos, "\",\"state\":\"");
        pos = clamp_pos(pos, sizeof(json));
        json_escape_append(json, sizeof(json), &pos, state);
    }

    /* "game_icon" only renders if the Discord Application has a Rich Presence
     * art asset uploaded under that exact key (Developer Portal > Rich
     * Presence > Art Assets); otherwise Discord just drops it silently. */
    pos += (size_t)snprintf(json + pos, sizeof(json) - pos,
                            "\",\"timestamps\":{\"start\":%lld},"
                            "\"assets\":{\"large_image\":\"game_icon\",\"large_text\":\"Animal Crossing\"}}},"
                            "\"nonce\":\"1\"}",
                            s_start_time);
    pos = clamp_pos(pos, sizeof(json));

    return pc_discord_send_frame(DISCORD_OP_FRAME, json, (int)pos);
}

static int pc_discord_handshake(void) {
    char json[128];
    int len = snprintf(json, sizeof(json), "{\"v\":1,\"client_id\":\"%s\"}", s_client_id);
    return pc_discord_send_frame(DISCORD_OP_HANDSHAKE, json, len);
}

static int pc_discord_worker(void* data) {
    int connected = 0;
    Uint32 next_connect_attempt = 0;
    (void)data;

    while (SDL_AtomicGet(&s_running)) {
        if (!connected) {
            Uint32 now = SDL_GetTicks();
            /* signed diff is safe across the Uint32 tick wraparound */
            if ((Sint32)(now - next_connect_attempt) >= 0) {
                if (pc_discord_connect() && pc_discord_handshake()) {
                    connected = 1;
                    s_sent_version = -1; /* force a resend now that we're connected */
                    if (g_pc_verbose) printf("[Discord] Connected to Discord IPC\n");
                } else {
                    pc_discord_disconnect();
                    next_connect_attempt = now + DISCORD_RECONNECT_DELAY_MS;
                }
            }
        }

        if (connected) {
            pc_discord_presence_t local;
            SDL_LockMutex(s_mutex);
            local = s_desired;
            SDL_UnlockMutex(s_mutex);

            if (local.version != s_sent_version) {
                if (!pc_discord_send_activity(local.details, local.state)) {
                    if (g_pc_verbose) printf("[Discord] Lost connection to Discord\n");
                    pc_discord_disconnect();
                    connected = 0;
                    next_connect_attempt = SDL_GetTicks() + DISCORD_RECONNECT_DELAY_MS;
                } else {
                    s_sent_version = local.version;
                }
            }
        }

        SDL_Delay(250);
    }

    pc_discord_disconnect();
    return 0;
}

void pc_discord_init(void) {
    strncpy(s_client_id, g_pc_settings.discord_client_id, sizeof(s_client_id) - 1);
    s_client_id[sizeof(s_client_id) - 1] = '\0';

    if (s_client_id[0] == '\0') {
        return; /* feature disabled: no client ID configured in settings.ini */
    }

    s_start_time = (long long)time(NULL);
    s_mutex = SDL_CreateMutex();
    if (!s_mutex) {
        printf("[Discord] Failed to create mutex: %s\n", SDL_GetError());
        return;
    }

    memset(&s_desired, 0, sizeof(s_desired));
    snprintf(s_desired.details, sizeof(s_desired.details), "%s", DEFAULT_DETAILS);

    SDL_AtomicSet(&s_running, 1);
    s_thread = SDL_CreateThread(pc_discord_worker, "DiscordRPC", NULL);
    if (!s_thread) {
        printf("[Discord] Failed to create worker thread: %s\n", SDL_GetError());
        SDL_AtomicSet(&s_running, 0);
    }
}

/* Town names use the game's own font character codes. The 32..122 block
 * mostly coincides with ASCII, but a handful of codes in it are game
 * symbols or accented letters (see m_font.h): those map to a base letter
 * where one exists and are dropped ('\0') otherwise. */
static char pc_discord_font_to_ascii(u8 c) {
    switch (c) {
        case CHAR_ACUTE_a:
        case CHAR_CIRCUMFLEX_a:
        case CHAR_TILDE_a:
        case CHAR_DIARESIS_a:
        case CHAR_ANGSTROM_a:
            return 'a';
        case CHAR_TILDE:
            return '~';
        case CHAR_SYMBOL_HEART:
        case CHAR_SYMBOL_MUSIC_NOTE:
        case CHAR_SYMBOL_DROPLET:
        case CHAR_SYMBOL_ANNOYED:
            return '\0';
        default:
            if ((c >= CHAR_SPACE && c <= CHAR_UNDERSCORE) || (c >= CHAR_a && c <= CHAR_z)) {
                return (char)c; /* these font codes coincide with ASCII */
            }
            return '\0';
    }
}

static void pc_discord_get_town_name(char* out, size_t out_size) {
    u8* raw = mLd_GetLandName();
    size_t len = 0;
    int i;

    for (i = 0; i < LAND_NAME_SIZE && len + 1 < out_size; i++) {
        char c = pc_discord_font_to_ascii(raw[i]);
        if (c != '\0') {
            out[len++] = c;
        }
    }
    while (len > 0 && out[len - 1] == ' ') len--;
    out[len] = '\0';
}

static const char* pc_discord_location_for_scene(int scene_no) {
    switch (scene_no) {
        case SCENE_FG: return "Outside";
        case SCENE_SHOP0: return "Inside Nook's Cranny";
        case SCENE_BROKER_SHOP: return "Inside Crazy Redd's tent";
        case SCENE_POST_OFFICE: return "Inside the Post Office";
        case SCENE_POLICE_BOX: return "Inside the Police Station";
        case SCENE_CONVENI: return "Inside Nook 'n' Go";
        case SCENE_SUPER: return "Inside Nookway";
        case SCENE_DEPART:
        case SCENE_DEPART_2: return "Inside Nookington's";
        case SCENE_NEEDLEWORK: return "Inside Able Sisters";
        case SCENE_NPC_HOUSE:
        case SCENE_COTTAGE_NPC: return "Visiting a neighbor's house";
        case SCENE_MY_ROOM_S:
        case SCENE_MY_ROOM_M:
        case SCENE_MY_ROOM_L:
        case SCENE_MY_ROOM_LL1:
        case SCENE_MY_ROOM_LL2:
        case SCENE_MY_ROOM_BASEMENT_S:
        case SCENE_MY_ROOM_BASEMENT_M:
        case SCENE_MY_ROOM_BASEMENT_L:
        case SCENE_MY_ROOM_BASEMENT_LL1:
        case SCENE_COTTAGE_MY: return "At home";
        default:
            if (mSc_IS_SCENE_MUSEUM_ROOM(scene_no)) return "At the Museum";
            return NULL; /* menus, demos, and scenes we're not confident labeling */
    }
}

void pc_discord_update(void) {
    static Uint32 next_update = 0;
    char details[128];
    char state[128] = "";
    Uint32 now;

    if (!s_mutex) return; /* not initialized (no client ID configured) */

    /* Wall-clock throttle (frame counting would scale with the FPS cap).
     * next_update == 0 fires immediately on the first call; the signed
     * diff is safe across the Uint32 tick wraparound. */
    now = SDL_GetTicks();
    if (next_update != 0 && (Sint32)(now - next_update) < 0) return;
    next_update = now + DISCORD_UPDATE_INTERVAL_MS;

    snprintf(details, sizeof(details), "%s", DEFAULT_DETAILS);
    if (pc_save_loaded) {
        char town[32];
        pc_discord_get_town_name(town, sizeof(town));

        if (town[0] != '\0') {
            const char* loc = pc_discord_location_for_scene(Save_Get(scene_no));

            snprintf(details, sizeof(details), "In the town of %s", town);
            if (loc) {
                snprintf(state, sizeof(state), "%s", loc);
            }
        }
    }

    SDL_LockMutex(s_mutex);
    if (strcmp(s_desired.details, details) != 0 || strcmp(s_desired.state, state) != 0) {
        snprintf(s_desired.details, sizeof(s_desired.details), "%s", details);
        snprintf(s_desired.state, sizeof(s_desired.state), "%s", state);
        s_desired.version++;
    }
    SDL_UnlockMutex(s_mutex);
}

void pc_discord_shutdown(void) {
    if (!s_mutex) return;

    SDL_AtomicSet(&s_running, 0);
    if (s_thread) {
        SDL_WaitThread(s_thread, NULL);
        s_thread = NULL;
    }
    SDL_DestroyMutex(s_mutex);
    s_mutex = NULL;
}

#else /* !_WIN32 */

void pc_discord_init(void) {}
void pc_discord_update(void) {}
void pc_discord_shutdown(void) {}

#endif
