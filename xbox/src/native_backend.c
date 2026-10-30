/* SDK/newlib translation unit: compile WITHOUT legacy include directories. */
#include "native_backend.h"
#include "time_scale.h"
#include <stdint.h>
#include <input/input.h>
#include <usb/usbmain.h>
#include <ppc/timebase.h>
#include <xenon_uart/xenon_uart.h>
#include <xenon_soc/xenon_power.h>
_Static_assert(PPC_TIMEBASE_FREQ == AC_XENON_TIMEBASE_HZ, "SDK timebase frequency changed");
_Static_assert(sizeof(unsigned long) == 4 && sizeof(unsigned long long) == 8,
               "Project backend requires the PPC32 ABI");

unsigned long long ac_native_ticks(void) {
    uint32_t upper, lower, verify;
    uint64_t native;
    do {
        __asm__ volatile("mftbu %0" : "=r"(upper));
        __asm__ volatile("mftbl %0" : "=r"(lower));
        __asm__ volatile("mftbu %0" : "=r"(verify));
    } while (upper != verify);
    native = ((uint64_t)upper << 32) | lower;
    /* GC bus 162 MHz / 4. Monotonic ticks, not a calendar epoch. Split the
     * product so a long uptime cannot overflow the intermediate numerator. */
    return ac_scale_timebase(native);
}

void ac_native_log(const char *message) {
    if (message) while (*message) putch((unsigned char)*message++);
}

static int input_ready, workers_ready;
int ac_native_input_init(void) {
    int result;
    if (input_ready) return 0;
    result = usb_init();
    if (result) return result;
    input_ready = 1;
    return 0;
}
int ac_native_input_poll(unsigned int port, struct ACNativeInput *sample) {
    struct controller_data_s d;
    unsigned short buttons;
    if (!input_ready || port >= 4 || !sample) return -1;
    usb_do_poll();
    if (!get_controller_data(&d, (int)port)) return 0;
    buttons = (d.left ? 1 : 0) | (d.right ? 2 : 0) | (d.down ? 4 : 0) | (d.up ? 8 : 0) |
              (d.lb ? 16 : 0) | (d.rb || d.rt >= 128 ? 32 : 0) | (d.lt >= 128 ? 64 : 0) |
              (d.a ? 256 : 0) | (d.b ? 512 : 0) | (d.x ? 1024 : 0) |
              (d.y ? 2048 : 0) | (d.start ? 4096 : 0);
    sample->left_x = d.s1_x; sample->left_y = d.s1_y;
    sample->right_x = d.s2_x; sample->right_y = d.s2_y;
    sample->buttons = buttons;
    sample->left_trigger = d.lt; sample->right_trigger = d.rt;
    return 1;
}
int ac_native_rumble(unsigned int port, unsigned char left, unsigned char right) {
    if (!input_ready || port >= 4) return -1;
    set_controller_rumble((int)port, left, right);
    return 0; /* Request accepted by SDK; not device delivery confirmation. */
}
void ac_native_workers_init(void) {
    if (!workers_ready) { xenon_thread_startup(); workers_ready = 1; }
}
int ac_native_worker_start(unsigned int core, void *stack_top, void (*task)(void)) {
    if (!workers_ready || core < 1 || core > 5 || !stack_top || !task ||
        ((uintptr_t)stack_top & 15)) return -1;
    return xenon_run_thread_task((int)core, stack_top, (void *)task);
}
int ac_native_worker_busy(unsigned int core) {
    if (!workers_ready || core < 1 || core > 5) return -1;
    return xenon_is_thread_task_running((int)core) != 0;
}
