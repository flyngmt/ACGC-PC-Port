/* SDL3 output for the game's existing software jaudio mixer. */
#include <SDL3/SDL.h>

#include "dolphin/ai.h"
#include "jaudio_NES/audiothread.h"

#include <stdio.h>

#define PC_AUDIO_SAMPLE_RATE 32000

static SDL_AudioStream* audio_stream;
static AIDCallback dma_callback;
static AISCallback stream_callback;
static u32 dsp_sample_rate = AI_SAMPLERATE_32KHZ;
static u32 stream_sample_rate = AI_SAMPLERATE_32KHZ;
static u32 stream_trigger;
static u32 stream_play_state;
static u32 stream_sample_count;
static u32 bytes_written;
static int master_volume = 100;

static void SDLCALL pc_audio_callback(void* userdata, SDL_AudioStream* stream,
                                      int additional_amount, int total_amount)
{
    (void)userdata;
    (void)stream;
    (void)total_amount;

    while (additional_amount > 0) {
        u32 before = bytes_written;
        pc_audio_process_frame();
        u32 produced = bytes_written - before;
        if (produced == 0) {
            break;
        }
        additional_amount -= (int)produced;
    }
}

void AIInit(u8* stack)
{
    (void)stack;
    if (audio_stream != NULL) {
        return;
    }

    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        fprintf(stderr, "[audio] SDL audio initialization failed: %s\n", SDL_GetError());
        return;
    }

    const SDL_AudioSpec spec = {
        .format = SDL_AUDIO_S16,
        .channels = 2,
        .freq = PC_AUDIO_SAMPLE_RATE,
    };
    audio_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec,
                                             pc_audio_callback, NULL);
    if (audio_stream == NULL) {
        fprintf(stderr, "[audio] Could not open output: %s\n", SDL_GetError());
    } else {
        SDL_SetAudioStreamGain(audio_stream, (float)master_volume / 100.0f);
    }
}

void pc_audio_set_master_volume(int volume)
{
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;
    master_volume = volume;
    if (audio_stream != NULL) {
        SDL_SetAudioStreamGain(audio_stream, (float)master_volume / 100.0f);
    }
}

void AIInitDMA(uintptr_t addr, u32 size)
{
    if (audio_stream == NULL || addr == 0 || size == 0) {
        return;
    }
    if (!SDL_PutAudioStreamData(audio_stream, (const void*)addr, (int)size)) {
        fprintf(stderr, "[audio] Could not queue samples: %s\n", SDL_GetError());
        return;
    }

    bytes_written += size;
    stream_sample_count += size / (sizeof(s16) * 2);
    if (dma_callback != NULL) {
        dma_callback();
    }
    if (stream_callback != NULL) {
        stream_callback(stream_sample_count);
    }
}

void AIStartDMA(void)
{
    if (audio_stream != NULL) {
        SDL_ResumeAudioStreamDevice(audio_stream);
    }
}

void AIStopDMA(void)
{
    if (audio_stream != NULL) {
        SDL_PauseAudioStreamDevice(audio_stream);
    }
}

void pc_audio_set_paused(int paused)
{
    if (paused) {
        AIStopDMA();
    } else {
        AIStartDMA();
    }
}

void pc_audio_start_producer_thread(void)
{
    /* SDL3 requests mixer output from pc_audio_callback on its audio thread. */
}

int pc_audio_get_buffer_fill(void)
{
    if (audio_stream == NULL) {
        return 0;
    }
    return SDL_GetAudioStreamAvailable(audio_stream) / (int)sizeof(s16);
}

int pc_audio_is_active(void)
{
    return audio_stream != NULL;
}

void pc_audio_shutdown(void)
{
    if (audio_stream != NULL) {
        SDL_DestroyAudioStream(audio_stream);
        audio_stream = NULL;
    }
}

AIDCallback AIRegisterDMACallback(AIDCallback callback)
{
    AIDCallback previous = dma_callback;
    dma_callback = callback;
    return previous;
}

AISCallback AIRegisterStreamCallback(AISCallback callback)
{
    AISCallback previous = stream_callback;
    stream_callback = callback;
    return previous;
}

BOOL AIGetDMAEnableFlag(void) { return audio_stream != NULL; }
u32 AIGetDMABytesLeft(void) { return 0; }
u32 AIGetDMAStartAddr(void) { return 0; }
u32 AIGetDMALength(void) { return 0; }
BOOL AICheckInit(void) { return audio_stream != NULL; }
u32 AIGetStreamSampleCount(void) { return stream_sample_count; }
void AIResetStreamSampleCount(void) { stream_sample_count = 0; }
void AISetStreamTrigger(u32 trigger) { stream_trigger = trigger; }
u32 AIGetStreamTrigger(void) { return stream_trigger; }
void AISetStreamPlayState(u32 state) { stream_play_state = state; }
u32 AIGetStreamPlayState(void) { return stream_play_state; }
void AISetDSPSampleRate(u32 rate) { dsp_sample_rate = rate; }
u32 AIGetDSPSampleRate(void) { return dsp_sample_rate; }
void AISetStreamSampleRate(u32 rate) { stream_sample_rate = rate; }
u32 AIGetStreamSampleRate(void) { return stream_sample_rate; }
void AISetStreamVolLeft(u8 volume) { (void)volume; }
u8 AIGetStreamVolLeft(void) { return 0xff; }
void AISetStreamVolRight(u8 volume) { (void)volume; }
u8 AIGetStreamVolRight(void) { return 0xff; }
void AIReset(void) { pc_audio_shutdown(); }

BOOL DSPCheckMailToDSP(void) { return FALSE; }
BOOL DSPCheckMailFromDSP(void) { return FALSE; }
u32 DSPReadMailFromDSP(void) { return 0; }
void DSPSendMailToDSP(u32 mail) { (void)mail; }
void DSPAssertInt(void) {}
void* DSPAddTask(void* task) { return task; }
