#include <dolphin/vi.h>

namespace {

u32 s_retrace_count = 0;
VIRetraceCallback s_pre_retrace_callback = nullptr;
VIRetraceCallback s_post_retrace_callback = nullptr;

} // namespace

extern "C" {

u32 pc_frame_counter = 0;

void VIWaitForRetrace()
{
    ++s_retrace_count;
    ++pc_frame_counter;

    if (s_pre_retrace_callback != nullptr) {
        s_pre_retrace_callback(s_retrace_count);
    }
    if (s_post_retrace_callback != nullptr) {
        s_post_retrace_callback(s_retrace_count);
    }
}

u32 VIGetRetraceCount()
{
    return s_retrace_count;
}

u32 VIGetNextField()
{
    return 0;
}

u32 VIGetDTVStatus()
{
    return 0;
}

void VISetBlack(BOOL black)
{
    (void)black;
}

void VISetNextFrameBuffer(void* frame_buffer)
{
    (void)frame_buffer;
}

void* VIGetCurrentFrameBuffer()
{
    return nullptr;
}

void* VIGetNextFrameBuffer()
{
    return nullptr;
}

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback callback)
{
    VIRetraceCallback previous = s_pre_retrace_callback;
    s_pre_retrace_callback = callback;
    return previous;
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback)
{
    VIRetraceCallback previous = s_post_retrace_callback;
    s_post_retrace_callback = callback;
    return previous;
}

} // extern "C"
