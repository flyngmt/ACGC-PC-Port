/* SDK-only diagnostic, deliberately isolated from GameCube type headers.
 * Requires libxenon's runtime and an already initialized display mode.
 * Compile-checked against pinned libxenon headers; NOT console-tested.
 * Does not implement GX or claim color channel equivalence with GXColor.
 */
#ifdef AC_XENOS_CLEAR_TRACE
#include <stdio.h>
#include <console/console.h>
#include <ppc/cache.h>
#endif
#include <xenos/xe.h>
#include <xenos/edram.h>
#ifdef AC_XENOS_CLEAR_TRACE
static int trace_enabled = 1;
static void trace(const char *text) {
    if (!trace_enabled) return;
    while (*text) console_putch(*text++);
}
#else
#define trace(text) ((void)0)
#endif
static struct XenosDevice device;
static int ready;
#ifdef AC_XENOS_CLEAR_TRACE
static unsigned int sample_offsets[6], before_pixels[6], after_pixels[6];
static unsigned int cpu_expected[6], cpu_readback[6], cpu_restored[6];
/* Same BGRA8888 tiled pixel-index formula as pinned SDK console_pset32. */
static unsigned int tiled_index(unsigned int x, unsigned int y, unsigned int pitch) {
    return ((y >> 5) * 32 * pitch + ((x >> 5) << 10) + (x & 3) +
            ((y & 1) << 2) + (((x & 31) >> 2) << 3) +
            (((y & 31) >> 1) << 6)) ^ ((y & 8) << 2);
}
#endif
int ac_xenos_clear_probe_capture(int after) {
#ifdef AC_XENOS_CLEAR_TRACE
    struct XenosSurface *fb = Xe_GetFramebufferSurface(&device);
    unsigned int i, pitch = (unsigned int)fb->wpitch / 4;
    volatile unsigned int *pixels = (volatile unsigned int *)(uintptr_t)(fb->ptr | 0x80000000U);
    if (!ready || !fb->tiled || fb->bypp != 4 || fb->width < 64 || fb->height < 64)
        return -1;
    for (i = 0; i < 6; ++i) {
        unsigned int x = (unsigned int)fb->width * (1 + i % 3) / 4;
        unsigned int y = (unsigned int)fb->height * (2 + i / 3) / 4;
        unsigned int offset = tiled_index(x, y, pitch);
        sample_offsets[i] = offset * 4;
        /* Flush/invalidate clean sample lines as SDK Xe_pSyncFromDevice does.
         * Samples are below console logs; no writes occur between captures. */
        memdcbf((void *)(uintptr_t)&pixels[offset], 4);
        __asm__ volatile("sync" ::: "memory");
        if (after) after_pixels[i] = pixels[offset];
        else before_pixels[i] = pixels[offset];
    }
    return 0;
#else
    (void)after;
    return -1;
#endif
}
int ac_xenos_clear_probe_cpu_control(void) {
#ifdef AC_XENOS_CLEAR_TRACE
    struct XenosSurface *fb = Xe_GetFramebufferSurface(&device);
    volatile unsigned int *pixels = (volatile unsigned int *)(uintptr_t)(fb->ptr | 0x80000000U);
    unsigned int i;
    if (ac_xenos_clear_probe_capture(0)) return -1;
    for (i = 0; i < 6; ++i) {
        unsigned int offset = sample_offsets[i] / 4;
        void *address = (void *)(uintptr_t)&pixels[offset];
        cpu_expected[i] = 0x12345600U | (i + 1);
        pixels[offset] = cpu_expected[i];
        memdcbst(address, 4);
        __asm__ volatile("sync" ::: "memory");
        memdcbf(address, 4);
        __asm__ volatile("sync" ::: "memory");
        cpu_readback[i] = pixels[offset];
        pixels[offset] = before_pixels[i];
        memdcbst(address, 4);
        __asm__ volatile("sync" ::: "memory");
        memdcbf(address, 4);
        __asm__ volatile("sync" ::: "memory");
        cpu_restored[i] = pixels[offset];
    }
    return 0;
#else
    return -1;
#endif
}
void ac_xenos_clear_probe_readback_report(void) {
#ifdef AC_XENOS_CLEAR_TRACE
    unsigned int i, changed = 0;
    unsigned int matched = 0, restored = 0;
    printf("CPU CONTROL v4: saved results; original pixels restored\n");
    for (i = 0; i < 6; ++i) {
        matched += cpu_expected[i] == cpu_readback[i];
        restored += before_pixels[i] == cpu_restored[i];
        printf("CPU %u: wrote=%08x read=%08x restored=%08x\n",
               i, cpu_expected[i], cpu_readback[i], cpu_restored[i]);
    }
    printf("CPU matches=%u/6 restores=%u/6\n", matched, restored);
    printf("GPU READBACK v4: captured before printing these results\n");
    for (i = 0; i < 6; ++i) {
        changed += before_pixels[i] != after_pixels[i];
        printf("offset %08x: before=%08x after=%08x\n",
               sample_offsets[i], before_pixels[i], after_pixels[i]);
    }
    printf("Changed samples: %u/6; raw words, not proof of full frame\n", changed);
#endif
}
/* Diagnostic-only reads at the same register offsets used by Xe_Init and
 * console_init in the pinned SDK. No display register is changed here. */
void ac_xenos_clear_probe_report(void) {
#ifdef AC_XENOS_CLEAR_TRACE
    volatile unsigned int *regs = (volatile unsigned int *)device.regs;
    struct XenosSurface *fb = Xe_GetFramebufferSurface(&device);
    printf("ADDR TEST v2: GPU fb=%08x base=%p rt=%08x\n",
           fb->ptr, fb->base, device.rt->ptr);
    printf("SCANOUT base=%08x pitch=%u width=%u height=%u\n",
           regs[0x6110/4], regs[0x6120/4], regs[0x6134/4], regs[0x6138/4]);
    printf("SURFACE width=%d height=%d byte_pitch=%d tiled=%d format=%08x\n",
           fb->width, fb->height, fb->wpitch, fb->tiled, (unsigned)fb->format);
    printf("CONSOLE CPU alias=%08x (SDK scanout base OR 80000000)\n",
           regs[0x6110/4] | 0x80000000U);
#endif
}
void ac_xenos_clear_probe_quiet(void) {
#ifdef AC_XENOS_CLEAR_TRACE
    trace_enabled = 0;
#endif
}
int ac_xenos_clear_probe_init(void) {
    if (ready) return -1;
    Xe_Init(&device);
    struct XenosSurface* framebuffer = Xe_GetFramebufferSurface(&device);
    if (!framebuffer || framebuffer->width <= 0 || framebuffer->height <= 0)
        return -1;
    Xe_SetRenderTarget(&device, framebuffer);
    /* Required by the pinned SDK cube example before its first frame. */
    trace("GPU INIT v5: calling edram_init before first frame\n");
    edram_init(&device);
    trace("GPU INIT v5: edram_init returned\n");
    ready = 1;
    return 0;
}
int ac_xenos_clear_probe_frame(unsigned int sdk_color) {
    if (!ready) return -1;
    trace("GPU A: setting clear color\n");
    Xe_SetClearColor(&device, sdk_color);
    trace("GPU B: entering Xe_Clear\n");
    Xe_Clear(&device, XE_CLEAR_COLOR | XE_CLEAR_DS);
    trace("GPU C: clear queued; entering Xe_Resolve\n");
    Xe_Resolve(&device);
    trace("GPU D: resolve queued; entering Xe_Sync\n");
    /* Xe_Sync submits through Xe_pDebugSync -> Xe_Execute itself. */
    Xe_Sync(&device);
    trace("GPU E: synchronization returned\n");
    return 0;
}
