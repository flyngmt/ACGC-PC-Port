#ifndef AC_XENON_NATIVE_BACKEND_H
#define AC_XENON_NATIVE_BACKEND_H
/* Project-owned ABI boundary. Do not include SDK or GameCube headers here.
 * unsigned long is 32 bits on this target; unsigned long long is 64 bits. */
unsigned long long ac_native_ticks(void);
int ac_native_read(const char *path, unsigned long offset, void *dst, unsigned long bytes);
void ac_native_log(const char *message);
void *ac_native_alloc(unsigned long bytes, unsigned long alignment);
void ac_native_free(void *pointer);

struct ACNativeInput {
    short left_x, left_y, right_x, right_y;
    unsigned short buttons;
    unsigned char left_trigger, right_trigger;
};
/* Returns 1 for a fresh USB packet, 0 for no new packet, -1 for invalid input.
 * The SDK does not expose connection status. Zero does NOT mean disconnected.
 * Main core only, after ac_native_input_init. */
int ac_native_input_init(void);
int ac_native_input_poll(unsigned int port, struct ACNativeInput *sample);
int ac_native_rumble(unsigned int port, unsigned char left, unsigned char right);

/* Explicit worker primitives, NOT Dolphin OSThread semantics. Start once on
 * the main core. Caller supplies a live 16-byte-aligned stack top and at least
 * 256 bytes of linkage space below it. Workers must not call unprotected libc,
 * USB, allocation, or game state. No priority, suspension or message queues. */
void ac_native_workers_init(void);
int ac_native_worker_start(unsigned int core, void *stack_top, void (*task)(void));
int ac_native_worker_busy(unsigned int core);
int ac_xenon_platform_install(void);
#endif
