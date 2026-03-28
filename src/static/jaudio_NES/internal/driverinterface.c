#include "jaudio_NES/driverinterface.h"

#include "jaudio_NES/dspinterface.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/dspdriver.h"
#include "jaudio_NES/ja_calc.h"
#include "jaudio_NES/bankdrv.h"
#include "jaudio_NES/aictrl.h"

#define CHANNEL_SIZE (0x100)

static jcs_ GLOBAL_CHANNEL;
static jc_ CHANNEL[CHANNEL_SIZE] ATTRIBUTE_ALIGN(32);

static u16 MAX_MIXERLEVEL  = 12000;
u32 JAC_SYSTEM_OUTPUT_MODE = 1;

static u32 cur_waits;
static u32 cur_top;
static u32 cur_tail;
static jc_* waitp[0x20] ATTRIBUTE_ALIGN(32);
static int waittime[0x20];

static u8 calc_sw_table[]
    = { 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 2, 0, 1, 0, 0, 2, 1, 0, 2, 2, 1, 0, 0, 1, 0, 1, 1, 0, 2, 1, 1, 0, 1, 1,
	    1, 1, 1, 2, 1, 2, 0, 1, 2, 1, 1, 2, 2, 1, 0, 0, 2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 1, 2, 2, 2, 0, 2, 2, 1, 2, 2, 2 };

// forward declarations
static void Cancel_WaitDSPChannel(jc_* jc);

/*
 * --INFO--
 * Address:	80009400
 * Size:	000024
 */
void Channel_SetMixerLevel(f32 mix)
{
	MAX_MIXERLEVEL = mix * 16384.0f;
}

/*
 * --INFO--
 * Address:	80009440
 * Size:	00000C
 */
jcs_* Get_GlobalHandle()
{
	return &GLOBAL_CHANNEL;
}

/*
 * --INFO--
 * Address:	80009460
 * Size:	000020
 */
int List_CountChannel(jc_** jc)
{
	jc_* chan = *jc;
	int num   = 0;

	while (TRUE) {
		if (chan == NULL) {
			break;
		}
		chan = (jc_*)chan->mNext;
		num++;
	}

	return num;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000044
 */
void Check_GlobalActiveChannel()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
void Check_GlobalRelease(jc_** jc)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00006C
 */
void List_GlobalChannel()
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80009480
 * Size:	000070
 */
int List_CutChannel(jc_* jc)
{
    jc_* orig = jc;
	jc_* chan = *jc->chanListHead;
    int num   = 0;
    int ret;

	if (chan == jc) {
		*jc->chanListHead = (jc_*)jc->mNext;
		jc->chanListHead  = NULL;
        return 0;
	}
    
    while (TRUE) {
        num++;
        if (chan == NULL) {
            return -1;
        }

        jc = (jc_*)chan->mNext;
        if (jc == orig) {
            break;
        }

        chan = (jc_*)chan->mNext;
    }

    chan->mNext      = orig->mNext;
    orig->chanListHead = NULL;
	return num;
}

/*
 * --INFO--
 * Address:	80009500
 * Size:	000030
 */
jc_* List_GetChannel(jc_** jc)
{
	jc_* chan = *jc;

	if (chan == NULL) {
		return NULL;
	}

	*jc                = (jc_*)chan->mNext;
	chan->chanListHead = NULL;
	return chan;
}

/*
 * --INFO--
 * Address:	80009540
 * Size:	000048
 */
void List_AddChannelTail(jc_** jc, jc_* in)
{
	jc_* chan        = *jc;
	in->chanListHead = jc;

	if (chan == NULL) {
		*jc       = in;
		in->mNext = NULL;
		return;
	}

	jc_* next;
	while (TRUE) {
		next = (jc_*)chan->mNext;
		if (next == NULL) {
			chan->mNext = in;
			in->mNext   = NULL;
			return;
		}
		chan = next;
	}
}

/*
 * --INFO--
 * Address:	800095A0
 * Size:	000014
 */
void List_AddChannel(jc_** jc, jc_* in)
{
	jc_* chan        = *jc;
	in->chanListHead = jc;
	*jc              = in;
	in->mNext        = chan;
}

/*
 * --INFO--
 * Address:	800095C0
 * Size:	00009C
 */
int FixAllocChannel(jcs_* sys, u32 size)
{
	jcs_** REF_sys = &sys;
	u32* REF_size  = &size;
	int num        = 0;
	while (num < size) {
		jc_* chan = List_GetChannel(&GLOBAL_CHANNEL.freeChannels);
		if (chan == NULL) {
			break;
		}

		List_AddChannel(&sys->freeChannels, chan);
		chan->mMgr = sys;
		Channel_Init(chan);
		num++;
	}

	sys->chanCount += num;
	GLOBAL_CHANNEL.chanCount -= num;
	return num;
}

/*
 * --INFO--
 * Address:	80009660
 * Size:	000060
 */
int FixReleaseChannel(jc_* chan)
{
	List_AddChannel(&GLOBAL_CHANNEL.freeChannels, chan);
	chan->mMgr->chanCount--;
	GLOBAL_CHANNEL.chanCount++;
	chan->mMgr = &GLOBAL_CHANNEL;
	return 0;
}

/*
 * --INFO--
 * Address:	800096C0
 * Size:	0000F0
 */
int FixReleaseChannelAll(jcs_* sys)
{
	jc_* chan;

	while (TRUE) {
		chan = List_GetChannel(&sys->freeChannels);
		if (chan == NULL) {
			break;
		}
		List_AddChannel(&GLOBAL_CHANNEL.freeChannels, chan);
		chan->mMgr = &GLOBAL_CHANNEL;
	}

	while (TRUE) {
		chan = List_GetChannel(&sys->activeChannels);
		if (chan == NULL) {
			break;
		}
		List_AddChannel(&GLOBAL_CHANNEL.activeChannels, chan);
		chan->mMgr = &GLOBAL_CHANNEL;
	}

	while (TRUE) {
		chan = List_GetChannel(&sys->releasingChannels);
		if (chan == NULL) {
			break;
		}
		List_AddChannel(&GLOBAL_CHANNEL.releasingChannels, chan);
		chan->mMgr = &GLOBAL_CHANNEL;
	}

	while (TRUE) {
		chan = List_GetChannel(&sys->waitingChannels);
		if (chan == NULL) {
			break;
		}
		Cancel_WaitDSPChannel(chan);
		List_AddChannel(&GLOBAL_CHANNEL.freeChannels, chan);
		chan->mMgr = &GLOBAL_CHANNEL;
	}

	GLOBAL_CHANNEL.chanCount += sys->chanCount;
	sys->chanCount = 0;
	return 0;
}

/*
 * --INFO--
 * Address:	800097C0
 * Size:	0000EC
 */
int FixMoveChannelAll(jcs_* sys, jcs_* sys2)
{
	jc_* chan;

	while (TRUE) {
		chan = List_GetChannel(&sys->freeChannels);
		if (chan == NULL) {
			break;
		}
		List_AddChannel(&sys2->freeChannels, chan);
		chan->mMgr = sys2;
	}

	while (TRUE) {
		chan = List_GetChannel(&sys->activeChannels);
		if (chan == NULL) {
			break;
		}
		List_AddChannel(&sys2->activeChannels, chan);
		chan->mMgr = sys2;
	}

	while (TRUE) {
		chan = List_GetChannel(&sys->releasingChannels);
		if (chan == NULL) {
			break;
		}
		List_AddChannel(&sys2->releasingChannels, chan);
		chan->mMgr = sys2;
	}

	while (TRUE) {
		chan = List_GetChannel(&sys->waitingChannels);
		if (chan == NULL) {
			break;
		}
		List_AddChannel(&sys2->waitingChannels, chan);
		chan->mMgr = sys2;
	}

	sys2->chanCount += sys->chanCount;
	sys->chanCount = 0;
	sys2->chanAllocCount += sys->chanAllocCount;
	sys->chanAllocCount = 0;
	return 0;
}

/*
 * --INFO--
 * Address:	800098C0
 * Size:	000070
 */
static f32 PanCalc(const PanMatrix_* mtx1, const PanMatrix_* mtx2, u8 a)
{
	f32 calc = 0.0f;

	u8* vals = calc_sw_table + (a * 3);

	for (int i = 0; i < 3; i++) {
		switch (vals[i]) {
		case 0:
			break;
		case 1:
			calc += mtx1->values[i];
			break;
		case 2:
			calc += (mtx1->values[i] * mtx2->values[i]);
			break;
		}
	}
	return calc;
}

/*
 * --INFO--
 * Address:	80009940
 * Size:	000104
 */
void InitJcs(jcs_* sys)
{
	sys->freeChannels      = NULL;
	sys->activeChannels    = NULL;
	sys->releasingChannels = NULL;
	sys->waitingChannels   = NULL;
	sys->chanAllocCount    = 0;
	sys->chanCount         = 0;
	sys->voiceStealingMode = 1;
	sys->volume            = 1.0f;
	sys->pitch             = 1.0f;
	sys->pan               = 0.5f;
	sys->fxmix             = 0.0f;
	sys->dolby             = 0.0f;

	int i;

	for (i = 0; i < 8; i++) {
		sys->firCoefficients[i] = 0;
	}

	sys->firCoefficients[0] = 0x7fff;
	sys->distFilter         = 0;

	for (i = 0; i < 4; i++) {
		sys->iirCoefficients[i] = 0;
		sys->masterLevels[i]    = 0;
	}

	sys->maxDelay           = 0;
	sys->iirCoefficients[0] = 0x7fff;
	sys->filterMode         = 0;
	sys->busConnect[0]      = 0x150;
	sys->busConnect[1]      = 0x210;
	sys->busConnect[2]      = 0x352;
	sys->busConnect[3]      = 0x412;
	sys->busConnect[4]      = 0;
	sys->busConnect[5]      = 0;
	sys->channelPriority    = 0x20103;
	sys->releaseTime        = 600;
	sys->panCalcTypes[0]    = 26;
	sys->panCalcTypes[1]    = 1;
	sys->panCalcTypes[2]    = 1;
}

/*
 * --INFO--
 * Address:	80009A60
 * Size:	000138
 */
void Channel_Init(jc_* jc)
{
	jc->updateCallback    = NULL;
	jc->pitchSweepUpdater = NULL;
	jc->playId            = 0;
	jc->savedPlayId       = 0;
	jc->waveData          = NULL;
	jc->logicalChanType   = 0;
	jc->_14               = 0;
	jc->_18               = 0;
	jc->_1C               = 0;

	if (jc->mMgr == NULL) {
		jc->busRouting[0].whole = 0x150;
		jc->busRouting[1].whole = 0x210;
		jc->busRouting[2].whole = 0x352;
		jc->busRouting[3].whole = 0x412;
		jc->busRouting[4].whole = 0;
		jc->busRouting[5].whole = 0;
		jc->channelPriority     = 0x10101;
		jc->releaseTime         = 0x258;
		jc->panCalcTypes[0]     = 0x1A;
		jc->panCalcTypes[1]     = 1;
		jc->panCalcTypes[2]     = 1;
	} else {
		for (int i = 0; i < 6; i++) {
			jc->busRouting[i].whole = jc->mMgr->busConnect[i];
		}

		jc->channelPriority = jc->mMgr->channelPriority;
		jc->releaseTime     = jc->mMgr->releaseTime;

		for (int i = 0; i < 3; i++) {
			jc->panCalcTypes[i] = jc->mMgr->panCalcTypes[i];
		}
	}

	for (int i = 0; i < 4; i++) {
		jc->mOscillators[i] = NULL;
	}

	jc->pauseFlag = 0;
	jc->channelId++;
	if ((int)jc->channelId == 0) {
		jc->channelId = 1;
	}
}

/*
 * --INFO--
 * Address:	80009BA0
 * Size:	000030
 */
static void Channel_FirstInit(jc_* jc)
{
	jc->dspChannel = NULL;
	jc->mNext      = NULL;
	jc->mMgr       = NULL;
	Channel_Init(jc);
}

/*
 * --INFO--
 * Address:	80009BE0
 * Size:	00007C
 */
void InitGlobalChannel()
{
	jcs_* global_channel;
	int i;

	global_channel = &GLOBAL_CHANNEL;
	InitJcs(global_channel);

	for (i = 0; i < CHANNEL_SIZE; i++) {
		Channel_FirstInit(&CHANNEL[i]);
		List_AddChannel(&global_channel->freeChannels, &CHANNEL[i]);
		CHANNEL[i].mMgr = global_channel;
	}

	global_channel->chanCount = CHANNEL_SIZE;
}

/*
 * --INFO--
 * Address:	80009C60
 * Size:	0000D8
 */
static void __UpdateJcToDSPInit(jc_* jc)
{
	int buf = jc->dspChannel->buffer_idx;
	DSP_SetMixerInitDelayMax(buf, jc->mMgr->maxDelay);

	for (u32 i = 0; i < 6; i++) {
		DSP_SetMixerInitVolume(buf, i, jc->mixerLevels[i], jc->mMgr->masterLevels[i]);
	}

	DSP_SetPitch(buf, jc->finalPitch);

	if (jc->mMgr->filterMode & 0x20) {
		DSP_SetIIRFilterParam(buf, jc->mMgr->iirCoefficients);
	}

	if (jc->mMgr->filterMode & 0x1f) {
		DSP_SetFIR8FilterParam(buf, jc->mMgr->firCoefficients);
	}

	DSP_SetFilterMode(buf, jc->mMgr->filterMode);
	DSP_SetPauseFlag(buf, jc->pauseFlag);
}

/*
 * --INFO--
 * Address:	80009D40
 * Size:	0000D8
 */
static void __UpdateJcToDSP(jc_* jc)
{
	u8 uVar1;

	uVar1 = jc->dspChannel->buffer_idx;
	for (u32 i = 0; i < 6; ++i) {
		DSP_SetMixerVolume(uVar1, i, jc->mixerLevels[i], jc->mMgr->masterLevels[i]);
	}

	DSP_SetPitch(uVar1, jc->finalPitch);

	if ((jc->mMgr->filterMode & 0x20) != 0) {
		DSP_SetIIRFilterParam(uVar1, jc->mMgr->iirCoefficients);
	}

	if ((jc->mMgr->filterMode & 0x1f) != 0) {
		DSP_SetFIR8FilterParam(uVar1, jc->mMgr->firCoefficients);
	}

	DSP_SetFilterMode(uVar1, jc->mMgr->filterMode);
	DSP_SetDistFilter(uVar1, jc->mMgr->distFilter);
	DSP_SetPauseFlag(uVar1, jc->pauseFlag);
}

/*
 * --INFO--
 * Address:	80009E20
 * Size:	000038
 */
void UpdateJcToDSP(jc_* jc)
{
	__UpdateJcToDSP(jc);
	DSP_FlushChannel(jc->dspChannel->buffer_idx);
}

/*
 * --INFO--
 * Address:	80009E60
 * Size:	000348
 */
void UpdateEffecterParam(jc_* jc)
{
	f32 pan;
	f32 volume;
	f32 fxmix;
	f32 dolby = 0.0f;
	f32 angle;

	f32 tmp;
	if (jc->lastManager == jc->mMgr) {
		jc->managerPitch             = jc->mMgr->pitch;
		jc->managerVolume            = jc->mMgr->volume;
		jc->panMatrices[1].values[2] = jc->mMgr->pan;
		jc->panMatrices[2].values[2] = jc->mMgr->fxmix;
		jc->panMatrices[3].values[2] = jc->mMgr->dolby;

		for (u32 i = 0; i < 3; i++) {
			jc->panCalcTypes[i] = jc->mMgr->panCalcTypes[i];
		}
	}

	switch (JAC_SYSTEM_OUTPUT_MODE) {
	case 0:
		pan   = 0.5f;
		dolby = 0.0f;
		fxmix = PanCalc(&jc->panMatrices[2], &jc->panMatrices[0], jc->panCalcTypes[1]);
		break;

	case 1:
		if (jc->panCalcTypes[0] == 0) {
			pan = 0.5f;
		} else {
			pan = PanCalc(&jc->panMatrices[1], &jc->panMatrices[0], jc->panCalcTypes[0]);
		}
		fxmix = PanCalc(&jc->panMatrices[2], &jc->panMatrices[0], jc->panCalcTypes[1]);
		dolby = PanCalc(&jc->panMatrices[3], &jc->panMatrices[0], jc->panCalcTypes[2]);
		break;
	}

	volume = jc->currentVolume * jc->volumeModifier * jc->managerVolume;

	if (pan < 0.0f) {
		pan = 0.0f;
	} else if (pan > 1.0f) {
		pan = 1.0f;
	}

	if (fxmix < 0.0f) {
		fxmix = 0.0f;
	} else if (fxmix > 1.0f) {
		fxmix = 1.0f;
	}

	if (dolby < 0.0f) {
		dolby = 0.0f;
	} else if (dolby > 1.0f) {
		dolby = 1.0f;
	}

	jc->finalPitch = jc->currentPitch * jc->pitchModifier * jc->managerPitch * 4096.0f;

	for (u32 i = 0; i < 6; i++) {
		f32 tmp          = volume;
		MixConfig config = jc->busRouting[i];

		if (config.parts.upper == 0) {
			jc->mixerLevels[i] = 0;
			continue;
		}

		f32 angle;
		if (config.parts.lower0) {
			switch (config.parts.lower0) {
			case 1:
				angle = pan;
				break;
			case 2:
				angle = fxmix;
				break;
			case 3:
				angle = dolby;
				break;
			case 5:
				angle = 1.0f - pan;
				break;
			case 6:
				angle = 1.0f - fxmix;
				break;
			case 7:
				angle = 1.0f - dolby;
				break;
			}
			tmp *= sinf3(angle);
		}

		if (config.parts.lower1) {
			switch (config.parts.lower1) {
			case 1:
				angle = pan;
				break;
			case 2:
				angle = fxmix;
				break;
			case 3:
				angle = dolby;
				break;
			case 5:
				angle = 1.0f - pan;
				break;
			case 6:
				angle = 1.0f - fxmix;
				break;
			case 7:
				angle = 1.0f - dolby;
				break;
			}
			tmp *= sinf3(angle);
		}

		if (tmp < 0.0f) {
			tmp = 0.0f;
		} else if (tmp > 1.0f) {
			tmp = 1.0f;
		}
		jc->mixerLevels[i] = tmp * (f32)MAX_MIXERLEVEL;
	}
}

/*
 * --INFO--
 * Address:	8000A1C0
 * Size:	000068
 */
void DoEffectOsc(jc_* jc, u8 id, f32 val)
{
	switch (id) {
	case 1:
		jc->pitchModifier *= val;
		break;
	case 0:
		jc->volumeModifier *= val;
		break;
	case 2:
		jc->panMatrices[1].values[1] = val;
		break;
	case 3:
		jc->panMatrices[2].values[1] = val;
		break;
	case 4:
		jc->panMatrices[3].values[1] = val;
		break;
	}
}

/*
 * --INFO--
 * Address:	8000A240
 * Size:	000084
 */
static void KillBrokenLogicalChannels(dspch_* ch)
{
	size_t i;
	jc_* chan;

	for (i = 0; i < CHANNEL_SIZE; i++) {
		chan = &CHANNEL[i];
		if (chan->dspChannel == ch) {
			StopLogicalChannel(chan);
			if (List_CutChannel(chan) != -1) {
				List_AddChannel(&chan->mMgr->freeChannels, chan);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	8000A2E0
 * Size:	000384
 */
static int CommonCallbackLogicalChannel(dspch_* ch, u32 a)
{
    jc_* jc = ch->_08;
	u32 i;
	u32 b   = 0;
	dspch_** REF_ch = &ch;
	jc_** REF_jc    = &jc;
	if (jc == NULL) {
		ch->_0C = NULL;
		ch->_03 = 0;
		KillBrokenLogicalChannels(ch);
		return FALSE;
	}

	if (jc->dspChannel != ch) {
		if (jc->dspChannel && jc->dspChannel->_08 == jc) {
			KillBrokenLogicalChannels(ch);
		} else {
			StopLogicalChannel(jc);
			if (List_CutChannel(jc) != -1) {
				List_AddChannel(&jc->mMgr->freeChannels, jc);
			}
		}
		ch->_08 = 0;
		ch->_03 = 0;
		ch->_0C = nullptr;
		return FALSE;
	}

	if (a == 2) {
		if (jc->updateCallback) {
			jc->updateCallback(jc, JCSTAT_Unk1);
		} else {
			StopLogicalChannel(jc);
			if (List_CutChannel(jc) != -1) {
				List_AddChannel(&jc->mMgr->freeChannels, jc);
			}
		}
		return FALSE;
	}

	if (jc->waveData && !*jc->waveData->fileLoadStatus) {
		ForceStopDSPchannel(jc->dspChannel);
		return -1;
	}

	if (a == 4) {
		u8 prio = jc->channelPriority >> 16;
		if (jc->dspChannel && prio < jc->dspChannel->_03) {
			jc->dspChannel->_03 = prio;
		}
		return FALSE;
	}

	if (a == 3) {
		jc->mOscBuffers[0].state = 6;
		if (List_CutChannel(jc) == -1) {
			return TRUE;
		}
		List_AddChannel(&jc->mMgr->waitingChannels, jc);
		a = 0;
	}

	if (a == 0) {
		jc->pitchModifier            = 1.0f;
		jc->volumeModifier           = 1.0f;
		jc->panMatrices[1].values[1] = 0.5f;
		jc->panMatrices[2].values[1] = 0.0f;
		jc->panMatrices[3].values[1] = 0.0f;

		for (i = 0; i < 4; i++) {
			u32* REF_i = &i;
			if (jc->mOscillators[i]) {
				DoEffectOsc(jc, jc->mOscillators[i]->mode, Bank_OscToOfs(jc->mOscillators[i], &jc->mOscBuffers[i]));
				if (jc->mOscBuffers[i].state == 0) {
					if (jc->updateCallback == NULL) {
						if (StopLogicalChannel(jc) == FALSE) {
							DSP_PlayStop(ch->buffer_idx);
							DSP_FlushChannel(ch->buffer_idx);
						}
						if (List_CutChannel(jc) != -1) {
							List_AddChannel(&jc->mMgr->freeChannels, jc);
						}
						return FALSE;
					} else {
						jc->updateCallback(jc, JCSTAT_Unk2);
						return FALSE;
					}
				}
				b++;
			}
		}

		if (b) {
			UpdateEffecterParam(jc);
			jc->toFlush = 1;
		}

		if (jc->pitchSweepUpdater && (uintptr_t)jc->pitchSweepUpdater(jc, JCSTAT_Unk0) == TRUE) {
			jc->toFlush++;
		}

		if (jc->updateCallback == NULL) {
			return TRUE;
		}

		if (jc->savedPlayId > 0) {
			jc->savedPlayId--;
		}
	}

	if (jc->savedPlayId == 0) {
		jc->updateCallback(jc, JCSTAT_Unk0);
		jc->savedPlayId = jc->playId;
	}

	if (jc->toFlush) {
		UpdateJcToDSP(jc);
		jc->toFlush = 0;
	}

	return TRUE;
}

/*
 * --INFO--
 * Address:	8000A680
 * Size:	000078
 */
BOOL StopLogicalChannel(jc_* jc)
{
	dspch_* ch = jc->dspChannel;
	if (ch == NULL) {
		return FALSE;
	}

	ch->_0C             = NULL;
	jc->dspChannel->_06 = 0;
	DSP_PlayStop(jc->dspChannel->buffer_idx);
	DSP_FlushChannel(jc->dspChannel->buffer_idx);
	DeAllocDSPchannel(jc->dspChannel, (uintptr_t)jc);
	jc->dspChannel = NULL;
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000A700
 * Size:	000028
 */
BOOL CheckLogicalChannel(jc_* jc)
{
	if (jc->waveData == NULL && jc->logicalChanType == 0) {
		return FALSE;
	}
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000A740
 * Size:	000180
 */
BOOL PlayLogicalChannel(jc_* jc)
{
	if (jc->dspChannel == NULL) {
		return FALSE;
	}
	if (CheckLogicalChannel(jc) == FALSE) {
		return FALSE;
	}

	jc->dspChannel->_0C = CommonCallbackLogicalChannel;
	jc->dspChannel->_06 = 1;

	switch (jc->logicalChanType) {
	case 0:
		DSP_SetWaveInfo(jc->dspChannel->buffer_idx, jc->waveData, jc->_14);
		break;
	case 1:
		break;
	case 2:
		DSP_SetOscInfo(jc->dspChannel->buffer_idx, jc->_14);
		break;
	}

	for (u32 i = 0; i < 6; i++) {
		MixConfig bus = jc->busRouting[i];
		// if (JAC_SYSTEM_OUTPUT_MODE == 0) {
		// 	switch (bus.parts.upper) {
		// 	case 8:
		// 		bus.parts.upper = 11;
		// 		break;
		// 	case 9:
		// 		bus.parts.upper = 2;
		// 		break;
		// 	}
		// }
		DSP_SetBusConnect(jc->dspChannel->buffer_idx, i, bus.parts.upper);
	}

	jc->lastManager = jc->mMgr;
	UpdateEffecterParam(jc);
	__UpdateJcToDSPInit(jc);
	jc->dspChannel->_03 = jc->channelPriority;
	jc->dspChannel->_04 = jc->releaseTime;
	DSP_PlayStart(jc->dspChannel->buffer_idx);
	DSP_FlushChannel(jc->dspChannel->buffer_idx);
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000A8C0
 * Size:	000074
 */
BOOL ResetInitialVolume(jc_* jc)
{
	if (jc->dspChannel == NULL) {
		return FALSE;
	}

	if (CheckLogicalChannel(jc) == FALSE) {
		return FALSE;
	}

	UpdateEffecterParam(jc);
	__UpdateJcToDSPInit(jc);
	DSP_FlushChannel(jc->dspChannel->buffer_idx);
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000A940
 * Size:	0000B0
 */
BOOL Add_WaitDSPChannel(jc_* jc)
{
	if (cur_waits == 32) {
		return FALSE;
	}

	if (BreakLowerDSPchannel(jc->channelPriority) == FALSE) {
		return FALSE;
	}

	waittime[cur_tail] = 0;
	waitp[cur_tail]    = jc;
	cur_tail++;
	cur_waits++;

	if (cur_tail == 32) {
		cur_tail = 0;
	}
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000AA00
 * Size:	000064
 */
BOOL Del_WaitDSPChannel(jc_* jc)
{
	for (u32 i = 0; i < cur_waits; i++) {
		if (waitp[(cur_top + i) & 0x1F] == jc) {
			waitp[(cur_top + i) & 0x1F] = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

/*
 * --INFO--
 * Address:	8000AA80
 * Size:	0000FC
 */
void __Entry_WaitChannel(u8 a)
{
	jc_* jc;
	dspch_* ch;

	while (cur_waits != 0) {
		jc = waitp[cur_top];
		if (jc) {
			ch = AllocDSPchannel(0, (uintptr_t)jc);
			if (ch == NULL) {
				break;
			}
			jc->dspChannel = ch;
			PlayLogicalChannel(jc);
			if (List_CutChannel(jc) != -1) {
				List_AddChannelTail(&jc->mMgr->activeChannels, jc);
			}
			cur_top++;
			if (cur_top == 0x20) {
				cur_top = 0;
			}
			cur_waits--;
			if (a == 1) {
				break;
			}
		} else {
			cur_top++;
			if (cur_top == 0x20) {
				cur_top = 0;
			}
			cur_waits--;
		}
	}
}

/*
 * --INFO--
 * Address:	8000AB80
 * Size:	0000C4
 */
void EntryCheck_WaitDSPChannel()
{
	__Entry_WaitChannel(0);

	for (u32 i = 0; i < cur_waits; i++) {
		jc_* jc = waitp[(cur_top + i) & 0x1f];
		if (jc) {
			waittime[(cur_top + i) & 0x1f]++;
			if (jc->playId > 0) {
				jc->playId--;
			}
			if (jc->playId == 0) {
				jc->updateCallback(jc, JCSTAT_Unk6);
				waitp[(cur_top + i) & 0x1f] = NULL;
			}
		}
	}
}

/*
 * --INFO--
 * Address:	8000AC60
 * Size:	00004C
 */
static void Cancel_WaitDSPChannel(jc_* jc)
{
	for (u32 i = 0; i < cur_waits; i++) {
		if (waitp[(cur_top + i) & 0x1F] == jc) {
			waitp[(cur_top + i) & 0x1F] = NULL;
		}
	}
}

/*
 * --INFO--
 * Address:	8000ACC0
 * Size:	000038
 */
BOOL ForceStopLogicalChannel(jc_* jc)
{
	if (jc->dspChannel == NULL) {
		return FALSE;
	}

	ForceStopDSPchannel(jc->dspChannel);
	return TRUE;
}
