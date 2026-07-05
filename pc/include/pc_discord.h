/* pc_discord.h - Discord Rich Presence (local IPC, best-effort) */
#ifndef PC_DISCORD_H
#define PC_DISCORD_H

#ifdef __cplusplus
extern "C" {
#endif

/* No-ops if settings.ini has no discord_client_id configured. */
void pc_discord_init(void);

/* Cheap to call every frame; internally throttled. */
void pc_discord_update(void);

void pc_discord_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif /* PC_DISCORD_H */
