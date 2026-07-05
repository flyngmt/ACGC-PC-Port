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
#include "m_land.h"
#include "m_scene_table.h"

#ifdef _WIN32

#define DISCORD_OP_HANDSHAKE 0
#define DISCORD_OP_FRAME 1

/* ~5s at 60fps: enough to feel live without spamming the pipe. */
#define DISCORD_UPDATE_INTERVAL_FRAMES 300
#define DISCORD_RECONNECT_DELAY_MS 5000

typedef struct {
    char details[128];
    char state[128];
    int has_state;
    int version; /* bumped whenever details/state change */
} pc_discord_presence_t;

static SDL_Thread* s_thread = NULL;
static SDL_atomic_t s_running;
static SDL_mutex* s_mutex = NULL;
static pc_discord_presence_t s_desired;
static int s_sent_version = -1;
static char s_client_id[32];
static long long s_start_time = 0;
static HANDLE s_pipe = INVALID_HANDLE_VALUE;

static int pc_discord_connect(void) {
    s_pipe = CreateFileA("\\\\.\\pipe\\discord-ipc-0", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    return s_pipe != INVALID_HANDLE_VALUE;
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

static int pc_discord_send_activity(const char* details, const char* state, int has_state) {
    char json[512];
    size_t pos;

    pos = (size_t)snprintf(json, sizeof(json), "{\"cmd\":\"SET_ACTIVITY\",\"args\":{\"pid\":%lu,\"activity\":{\"details\":\"",
                            (unsigned long)GetCurrentProcessId());
    json_escape_append(json, sizeof(json), &pos, details);

    if (has_state) {
        pos += (size_t)snprintf(json + pos, sizeof(json) - pos, "\",\"state\":\"");
        json_escape_append(json, sizeof(json), &pos, state);
    }

    /* "game_icon" only renders if the Discord Application has a Rich Presence
     * art asset uploaded under that exact key (Developer Portal > Rich
     * Presence > Art Assets); otherwise Discord just drops it silently. */
    pos += (size_t)snprintf(
        json + pos, sizeof(json) - pos,
        "\",\"timestamps\":{\"start\":%lld},\"assets\":{\"large_image\":\"game_icon\",\"large_text\":\"Animal Crossing\"}}},\"nonce\":\"1\"}",
        s_start_time);

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
            if (now >= next_connect_attempt) {
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
                if (!pc_discord_send_activity(local.details, local.state, local.has_state)) {
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
    snprintf(s_desired.details, sizeof(s_desired.details), "Playing Animal Crossing");

    SDL_AtomicSet(&s_running, 1);
    s_thread = SDL_CreateThread(pc_discord_worker, "DiscordRPC", NULL);
    if (!s_thread) {
        printf("[Discord] Failed to create worker thread: %s\n", SDL_GetError());
        SDL_AtomicSet(&s_running, 0);
    }
}

/* Town names use the game's own font character codes, which only line up
 * with ASCII across these two ranges (checked against m_font.h); everything
 * else (accented letters, symbols) is dropped rather than shown wrong. */
static int pc_discord_char_is_ascii(u8 c) {
    return (c >= 32 && c <= 90) || (c >= 97 && c <= 122);
}

static void pc_discord_get_town_name(char* out, size_t out_size) {
    u8* raw = mLd_GetLandName();
    size_t len = 0;
    int i;

    for (i = 0; i < LAND_NAME_SIZE && len + 1 < out_size; i++) {
        if (pc_discord_char_is_ascii(raw[i])) {
            out[len++] = (char)raw[i];
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
    static u32 frame = 0;
    char details[128];
    char state[128];
    int has_state = 0;

    if (!s_mutex) return; /* not initialized (no client ID configured) */

    frame++;
    if (frame % DISCORD_UPDATE_INTERVAL_FRAMES != 0) return;

    if (!pc_save_loaded) {
        snprintf(details, sizeof(details), "Playing Animal Crossing");
    } else {
        char town[32];
        pc_discord_get_town_name(town, sizeof(town));

        if (town[0] == '\0') {
            snprintf(details, sizeof(details), "Playing Animal Crossing");
        } else {
            const char* loc;

            snprintf(details, sizeof(details), "In the town of %s", town);

            loc = pc_discord_location_for_scene(Save_Get(scene_no));
            if (loc) {
                snprintf(state, sizeof(state), "%s", loc);
                has_state = 1;
            }
        }
    }

    SDL_LockMutex(s_mutex);
    if (strcmp(s_desired.details, details) != 0 || s_desired.has_state != has_state ||
        (has_state && strcmp(s_desired.state, state) != 0)) {
        snprintf(s_desired.details, sizeof(s_desired.details), "%s", details);
        s_desired.has_state = has_state;
        if (has_state) snprintf(s_desired.state, sizeof(s_desired.state), "%s", state);
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
