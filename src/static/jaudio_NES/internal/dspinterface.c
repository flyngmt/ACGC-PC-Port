#include "jaudio_NES/dspinterface.h"

#include "dolphin/os.h"
#include "jaudio_NES/sample.h"
#include "jaudio_NES/dspproc.h"
#include "jaudio_NES/dspdriver.h"
#include "jaudio_NES/driverinterface.h"
#include "jaudio_NES/fxinterface.h"

#include "limits.h"

#define CH_BUF_LENGTH (64)
#define FX_BUF_LENGTH (4)

static DSPchannel_ CH_BUF[CH_BUF_LENGTH];
static FXBuffer FX_BUF[FX_BUF_LENGTH];

/*
 * --INFO--
 * Address:	8000B560
 * Size:	000018
 */
DSPchannel_* GetDspHandle(u8 idx)
{
	return &CH_BUF[idx];
}

/*
 * --INFO--
 * Address:	........
 * Size:	000034
 */
DSPchannel_* GetDspHandleNc(u8)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000B580
 * Size:	000014
 */
FXBuffer* GetFxHandle(u8 idx)
{
	return &FX_BUF[idx];
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
FXBuffer* GetFxHandleNc(u8 idx)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000B5A0
 * Size:	00002C
 */
void DSP_SetPitch(u8 idx, u16 pitch)
{
	DSPchannel_* buf = &CH_BUF[idx];
	if (pitch >= SHRT_MAX)
		pitch = SHRT_MAX;
	buf->resamplingRatio = pitch;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000050
 */
void DSP_SetPitch_Indirect(u8 idx, f32, f32)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000B5E0
 * Size:	000020
 */
void DSP_SetMixerInitDelayMax(u8 idx, u8 initDelayMax)
{
	DSPchannel_* buf        = &CH_BUF[idx];
	buf->samplesToKeepCount = initDelayMax;
}

/*
 * --INFO--
 * Address:	8000B600
 * Size:	00004C
 */
void DSP_SetMixerInitVolume(u8 idx, u8 mixer, s16 volume, u8 level)
{
	u8* REF_idx;
	u8* REF_mixer;

	DSPchannel_* buf;
	DSPMixerChannel* mixChan;

	REF_idx   = &idx;
	REF_mixer = &mixer;

	buf     = &CH_BUF[idx];
	mixChan = &buf->mixChannels[mixer];

	mixChan->currentVolume = volume;
	mixChan->targetVolume  = volume;
	mixChan->level         = (level << 8) | (level);
}

/*
 * --INFO--
 * Address:	8000B660
 * Size:	000044
 */
void DSP_SetMixerVolume(u8 idx, u8 mixer, s16 volume, u8 param_4)
{
	DSPchannel_* buf         = &CH_BUF[idx];
	DSPMixerChannel* mixChan = &buf->mixChannels[mixer];
	if (buf->endRequested)
		return;
	mixChan->targetVolume = volume;
	mixChan->level        = (param_4 << 8) | (mixChan->level & 0xff);
}

/*
 * --INFO--
 * Address:	8000B6C0
 * Size:	00002C
 */
void DSP_SetOscInfo(u8 idx, u32 samplesSourceType)
{
	DSPchannel_* buf                = &CH_BUF[idx];
	buf->baseAddress                = 0;
	buf->afcRemainingDecodedSamples = 16;
	buf->samplesSourceType          = samplesSourceType;
}

/*
 * --INFO--
 * Address:	8000B700
 * Size:	000020
 */
void DSP_SetPauseFlag(u8 idx, u8 pauseFlag)
{
	DSPchannel_* buf       = &CH_BUF[idx];
	buf->useConstantSample = pauseFlag;
}

/*
 * --INFO--
 * Address:	8000B720
 * Size:	0000B0
 */
void DSP_SetWaveInfo(u8 idx, Wave_* wave, u32 baseAddress)
{
	static u8 COMP_BLOCKSAMPLES[] = {
		0x10, 0x10, 0x01, 0x01, 0x01, 0x10, 0x10, 0x01,
	};
	static u8 COMP_BLOCKBYTES[] = {
		0x09, 0x05, 0x08, 0x10, 0x01, 0x01, 0x01, 0x01,
	};

	DSPchannel_* buf = &CH_BUF[idx];

	buf->baseAddress                = baseAddress;
	buf->afcRemainingDecodedSamples = COMP_BLOCKSAMPLES[wave->compBlockIdx];
	buf->samplesSourceType          = COMP_BLOCKBYTES[wave->compBlockIdx];
	if (buf->samplesSourceType < 4)
		return;
	buf->_11C      = wave->_1C;
	buf->isLooping = wave->isLooping;
	if (buf->isLooping) {
		buf->loopAddress       = wave->loopAddress;
		buf->loopStartPosition = wave->loopStartPosition;
		buf->loopYN1           = wave->loopYN1;
		buf->loopYN2           = wave->loopYN2;
	} else {
		buf->loopStartPosition = buf->_11C;
	}
	for (int i = 0; i < 16; ++i) {
		buf->afcRemainingSamples[i] = 0;
	}
}

/*
 * --INFO--
 * Address:	8000B7E0
 * Size:	000038
 */
void DSP_SetBusConnect(u8 idx, u8 mixer, u8 busConnect)
{
	static u16 connect_table[] = {
		0x0000, 0x0D00, 0x0D60, 0x0DC0, 0x0E20, 0x0E80, 0x0EE0, 0x0CA0, 0x0F40, 0x0FA0, 0x0B00, 0x09A0,
	};

	DSPchannel_* buf         = &CH_BUF[idx];
	DSPMixerChannel* mixChan = &buf->mixChannels[mixer];
	mixChan->id              = connect_table[busConnect];
}

/*
 * --INFO--
 * Address:	8000B820
 * Size:	000020
 */
void DSP_PlayStop(u8 idx)
{
	DSPchannel_* buf = &CH_BUF[idx];
	buf->enabled     = DSP_FALSE;
}

/*
 * --INFO--
 * Address:	8000B840
 * Size:	000060
 */
void DSP_AllocInit(u8 idx)
{
	DSPchannel_* buf       = &CH_BUF[idx];
	buf->useConstantSample = DSP_FALSE;
	buf->done              = DSP_FALSE;
	buf->endRequested      = DSP_FALSE;
	buf->enabled           = DSP_FALSE;
	// DSP_InitFilter(idx);
	DSP_FlushChannel(idx);
}

/*
 * --INFO--
 * Address:	8000B8A0
 * Size:	00007C
 */
void DSP_PlayStart(u8 idx)
{
	u32 i;

	DSPchannel_* buf     = &CH_BUF[idx];
	buf->_10C            = 0;
	buf->currentPosition = 0;
	buf->currentPosFrac  = 0;
	buf->resetVpb        = DSP_TRUE;
	buf->constantSample  = 0;
	for (i = 0; i < 4; ++i) {
		buf->resampleBuffer[i] = 0;
		buf->biquadHistory[i]  = 0;
	}
	for (i = 0; i < 20; ++i) {
		buf->variableFirHistory[i] = 0;
	}
	buf->enabled = DSP_TRUE;
}

/*
 * --INFO--
 * Address:	8000B920
 * Size:	00001C
 */
void DSP_SetDistFilter(u8 idx, s16 distFilter)
{
	DSPchannel_* buf  = &CH_BUF[idx];
	buf->lowPassCoeff = distFilter;
}

/*
 * --INFO--
 * Address:	8000B940
 * Size:	000024
 */
void DSP_SetFilterTable(s16* dst, s16* src, u32 len)
{
	for (int i = 0; i < len; ++i) {
		*dst++ = *src++;
	}
}

/*
 * --INFO--
 * Address:	8000B980
 * Size:	00003C
 */
void DSP_SetIIRFilterParam(u8 idx, s16* param_2)
{
	DSPchannel_* buf = &CH_BUF[idx];
	DSP_SetFilterTable(buf->biquadFilterCoeffs, param_2, 4);
}

/*
 * --INFO--
 * Address:	8000B9C0
 * Size:	00003C
 */
void DSP_SetFIR8FilterParam(u8 idx, s16* param_2)
{
	DSPchannel_* buf = &CH_BUF[idx];
	DSP_SetFilterTable(buf->variableFirCoeffs, param_2, 8);
}

/*
 * --INFO--
 * Address:	8000BA00
 * Size:	000054
 */
void DSP_SetFilterMode(u8 idx, u16 filterMode)
{
	DSPchannel_* buf = &CH_BUF[idx];

	u8 enableBiquadFilter    = filterMode & 0b100000;
	u8 variableFirFilterSize = filterMode & 0b011111;
	if (enableBiquadFilter) {
		if (variableFirFilterSize > 20) {
			variableFirFilterSize = 20;
		}
	} else {
		if (variableFirFilterSize > 24) {
			variableFirFilterSize = 24;
		}
	}
	buf->filterMode = enableBiquadFilter + variableFirFilterSize;
}

/*
 * --INFO--
 * Address:	8000BA60
 * Size:	000070
 */
void DSP_InitFilter(u8 idx)
{
	int i;
	DSPchannel_* buf = &CH_BUF[idx];

	for (i = 0; i < 8; ++i) {
		buf->variableFirCoeffs[i] = 0;
	}
	buf->variableFirCoeffs[0] = SHRT_MAX;

	for (i = 0; i < 4; ++i) {
		buf->biquadFilterCoeffs[i] = 0;
	}
	buf->biquadFilterCoeffs[0] = SHRT_MAX;

	buf->lowPassCoeff = 0;
}

/*
 * --INFO--
 * Address:	8000BAE0
 * Size:	00003C
 */
void DSP_FlushBuffer()
{
	DCFlushRange(CH_BUF, sizeof(CH_BUF));
	DCFlushRange(FX_BUF, sizeof(FX_BUF));
}

/*
 * --INFO--
 * Address:	8000BB20
 * Size:	000038
 */
void DSP_FlushChannel(u8 idx)
{
	DCFlushRangeNoSync(&CH_BUF[idx], sizeof(DSPchannel_));
}

/*
 * --INFO--
 * Address:	........
 * Size:	000038
 */
void DSP_CacheChannel(u8 idx)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
void DSP_FlushChannelAll()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
void DSP_CacheChannelAll()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000BB60
 * Size:	00002C
 */
void DSP_InvalChannelAll()
{
	DCInvalidateRange(CH_BUF, sizeof(CH_BUF));
}

/*
 * --INFO--
 * Address:	8000BBA0
 * Size:	000050
 */
void DSP_ClearBuffer()
{
	for (int i = 0; i < CH_BUF_LENGTH; ++i) {
		Jac_bzero(&CH_BUF[i], sizeof(DSPchannel_));
	}
}

static u32 DSPADPCM_FILTER[] ATTRIBUTE_ALIGN(32) = {
	0x00000000, 0x08000000, 0x00000800, 0x04000400, 0x1000f800, 0x0e00fa00, 0x0c00fc00, 0x1200f600,
	0x1068f738, 0x12c0f704, 0x1400f400, 0x0800f800, 0x0400fc00, 0xfc000400, 0xfc000000, 0xf8000000,
};

static u32 DSPRES_FILTER[] ATTRIBUTE_ALIGN(32) = {
	0x0c3966ad, 0x0d46ffdf, 0x0b396696, 0x0e5fffd8, 0x0a446669, 0x0f83ffd0, 0x095a6626, 0x10b4ffc8, 0x087d65cd, 0x11f0ffbf, 0x07ab655e,
	0x1338ffb6, 0x06e464d9, 0x148cffac, 0x0628643f, 0x15ebffa1, 0x0577638f, 0x1756ff96, 0x04d162cb, 0x18cbff8a, 0x043561f3, 0x1a4cff7e,
	0x03a46106, 0x1bd7ff71, 0x031c6007, 0x1d6cff64, 0x029f5ef5, 0x1f0bff56, 0x022a5dd0, 0x20b3ff48, 0x01be5c9a, 0x2264ff3a, 0x015b5b53,
	0x241eff2c, 0x010159fc, 0x25e0ff1e, 0x00ae5896, 0x27a9ff10, 0x00635720, 0x297aff02, 0x001f559d, 0x2b50fef4, 0xffe2540d, 0x2d2cfee8,
	0xffac5270, 0x2f0dfedb, 0xff7c50c7, 0x30f3fed0, 0xff534f14, 0x32dcfec6, 0xff2e4d57, 0x34c8febd, 0xff0f4b91, 0x36b6feb6, 0xfef549c2,
	0x38a5feb0, 0xfedf47ed, 0x3a95feac, 0xfece4611, 0x3c85feab, 0xfec04430, 0x3e74feac, 0xfeb6424a, 0x4060feaf, 0xfeaf4060, 0x424afeb6,
	0xfeac3e74, 0x4430fec0, 0xfeab3c85, 0x4611fece, 0xfeac3a95, 0x47edfedf, 0xfeb038a5, 0x49c2fef5, 0xfeb636b6, 0x4b91ff0f, 0xfebd34c8,
	0x4d57ff2e, 0xfec632dc, 0x4f14ff53, 0xfed030f3, 0x50c7ff7c, 0xfedb2f0d, 0x5270ffac, 0xfee82d2c, 0x540dffe2, 0xfef42b50, 0x559d001f,
	0xff02297a, 0x57200063, 0xff1027a9, 0x589600ae, 0xff1e25e0, 0x59fc0101, 0xff2c241e, 0x5b53015b, 0xff3a2264, 0x5c9a01be, 0xff4820b3,
	0x5dd0022a, 0xff561f0b, 0x5ef5029f, 0xff641d6c, 0x6007031c, 0xff711bd7, 0x610603a4, 0xff7e1a4c, 0x61f30435, 0xff8a18cb, 0x62cb04d1,
	0xff961756, 0x638f0577, 0xffa115eb, 0x643f0628, 0xffac148c, 0x64d906e4, 0xffb61338, 0x655e07ab, 0xffbf11f0, 0x65cd087d, 0xffc810b4,
	0x6626095a, 0xffd00f83, 0x66690a44, 0xffd80e5f, 0x66960b39, 0xffdf0d46, 0x66ad0c39, 0x00000c8b, 0x18f82527, 0x30fb3c56, 0x471c5133,
	0x5a8262f1, 0x6a6d70e2, 0x76417a7c, 0x7d897f61, 0x7fff7f61, 0x7d897a7c, 0x764170e2, 0x6a6d62f1, 0x5a825133, 0x471c3c56, 0x30fb2527,
	0x18f80c8b, 0x0000f375, 0xe708dad9, 0xcf05c3aa, 0xb8e4aecd, 0xa57e9d0f, 0x95938f1e, 0x89bf8584, 0x8277809f, 0x8001809f, 0x82778584,
	0x89bf8f1e, 0x95939d0f, 0xa57eaecd, 0xb8e4c3aa, 0xcf05dad9, 0xe708f375, 0x000007ff, 0x0fff17ff, 0x1fff27ff, 0x2fff37ff, 0x3fff47ff,
	0x4fff57ff, 0x5fff67ff, 0x6fff77ff, 0x7fff7800, 0x70006800, 0x60005800, 0x50004800, 0x40003800, 0x30002800, 0x20001800, 0x10000800,
	0x0000f801, 0xf001e801, 0xe001d801, 0xd001c801, 0xc001b801, 0xb001a801, 0xa0019801, 0x90018801, 0x80018800, 0x90009800, 0xa000a800,
	0xb000b800, 0xc000c800, 0xd000d800, 0xe000e800, 0xf000f800, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x1fff3fff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x1fffc001,
};

/*
 * --INFO--
 * Address:	8000BC00
 * Size:	000044
 */
void DSP_SetupBuffer()
{
	DsetupTable((uintptr_t)CH_BUF_LENGTH, (uintptr_t)CH_BUF, (uintptr_t)DSPRES_FILTER, (uintptr_t)DSPADPCM_FILTER, (uintptr_t)FX_BUF);
}

/*
 * --INFO--
 * Address:	8000BC60
 * Size:	000058
 */
void DSP_InitBuffer()
{
	for (int i = 0; i < 4; ++i)
		DFX_SetFxLine(i, NULL, NULL);
	DSP_ClearBuffer();
	DSP_SetupBuffer();
	InitDSPchannel();
	InitGlobalChannel();
	DSP_FlushBuffer();
}
