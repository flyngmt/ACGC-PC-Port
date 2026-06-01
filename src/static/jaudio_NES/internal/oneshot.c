#include "jaudio_NES/oneshot.h"
#include "jaudio_NES/bankdrv.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/driverinterface.h"
#include "jaudio_NES/tables.h"
#include "jaudio_NES/bankread.h"
#include "jaudio_NES/waveread.h"
#include "jaudio_NES/connect.h"
#include "jaudio_NES/dspdriver.h"
#include "jaudio_NES/rate.h"
#include "jaudio_NES/bx.h"

static int Jesus1Shot_Update(jc_*, JCSTATUS);

static s16 OSC_REL[] = { 1, 10, 0, 15 };

Osc_ PERC_ENV    = { 0, 1.0f, 0, 0, 1.0f, 0 };
Osc_ OSC_ENV     = { 0, 1.0f, 0, OSC_REL, 1.0f, 0 };
u8 polys_table[] = { 0, 1, 2, 3, 4, 5, 6, 8, 10, 12, 14, 16, 20, 24, 28, 32 };

/*
 * --INFO--
 * Address:	80015140
 * Size:	000034
 */
static u8 __GetTrigger(jc_* jc, u8 n)
{
	switch (n) {
	case 1:
		return jc->velocity;
	case 2:
		return jc->note;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	80015180
 * Size:	000028
 */
static f32 __Clamp01(f32 val)
{
	if (val < 0.0f) {
		return 0.0f;
	}
	if (val > 1.0f) {
		return 1.0f;
	}
	return val;
}

/*
 * --INFO--
 * Address:	800151C0
 * Size:	000054
 */
static void __Clamp01InitPan(jc_* jc)
{
	for (u32 i = 1; i < 3; i++) {
		jc->panMatrices[i].values[0] = __Clamp01(jc->panMatrices[i].values[0]);
	}
}

/*
 * --INFO--
 * Address:	80015220
 * Size:	000068
 */
static void __DoEffect(jc_* jc, u8 id, f32 val)
{
	switch (id) {
	case 1:
		jc->currentPitch *= val;
		break;
	case 0:
		jc->currentVolume *= val;
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
 * Address:	800152A0
 * Size:	000138
 */
static void EffecterInit(jc_* jc, Inst_* inst)
{
	jc->pitchModifier            = 1.0f;
	jc->volumeModifier           = 1.0f;
	jc->panMatrices[1].values[1] = 0.5f;
	jc->panMatrices[2].values[1] = 0.0f;
	jc->panMatrices[3].values[1] = 0.0f;
	for (u32 i = 0; i < 2; i++) {
		if (inst->mSensors[i]) {
			u8 trigger     = __GetTrigger(jc, inst->mSensors[i]->type);
			f32 sense      = Bank_SenseToOfs(inst->mSensors[i], trigger);
			f32* REF_sense = &sense;
			__DoEffect(jc, inst->mSensors[i]->id, sense);
		}

		if (inst->mEffects[i]) {
			f32 r = Bank_RandToOfs(inst->mEffects[i]);
			__DoEffect(jc, inst->mEffects[i]->id, r);
		}

		if (inst->mOscillators[i]) {
			jc->mOscBuffers[i].state = 1;
			jc->mOscillators[i]      = inst->mOscillators[i];
			f32 ofs                  = Bank_OscToOfs(jc->mOscillators[i], &jc->mOscBuffers[i]);
			DoEffectOsc(jc, jc->mOscillators[i]->mode, ofs);
		} else {
			jc->mOscillators[i] = NULL;
		}
	}
	__Clamp01InitPan(jc);
}

/*
 * --INFO--
 * Address:	800153E0
 * Size:	0000D0
 */
static void EffecterInit_Perc(jc_* jc, Pmap_* pmap, u16 id)
{
	jc->pitchModifier            = 1.0f;
	jc->volumeModifier           = 1.0f;
	jc->panMatrices[1].values[1] = 0.5f;
	jc->panMatrices[2].values[1] = 0.0f;
	jc->panMatrices[3].values[1] = 0.0f;

	// PERC instruments only have rand and not osc
    Pmap_* map;
	for (u32 i = 0; i < 2; i++) {
		 map = (Pmap_*)((int*)pmap + i + 2);
		if (map->_00) {
			f32 r      = Bank_RandToOfs(map->_00);
			f32* REF_r = &r;
			__DoEffect(jc, map->_00->id, r);
		}

		jc->mOscillators[i] = NULL;
	}
	jc->mOscillators[0]      = &PERC_ENV;
	jc->mOscBuffers[0].state = TRUE;
	Bank_OscToOfs(jc->mOscillators[0], &jc->mOscBuffers[0]);
	jc->mOscBuffers[0].releaseParam = id;
	__Clamp01InitPan(jc);
}

/*
 * --INFO--
 * Address:	800154C0
 * Size:	00007C
 */
static void EffecterInit_Osc(jc_* jc)
{
	jc->pitchModifier            = 1.0f;
	jc->volumeModifier           = 1.0f;
	jc->panMatrices[1].values[1] = 0.5f;
	jc->panMatrices[2].values[1] = 0.0f;
	jc->panMatrices[3].values[1] = 0.0f;

	for (u32 i = 0; i < 2; i++) {
		jc->mOscillators[i] = NULL;
	}

	jc->mOscillators[0]      = &OSC_ENV;
	jc->mOscBuffers[0].state = TRUE;
	Bank_OscToOfs(jc->mOscillators[0], &jc->mOscBuffers[0]);
}

/*
 * --INFO--
 * Address:	80015540
 * Size:	00006C
 */
void Effecter_Overwrite_1ShotD(jc_* jc, Osc_* osc, u32 id)
{
	if (id < 4) {
		jc->mOscBuffers[id].state = TRUE;
		jc->mOscillators[id]      = osc;
		DoEffectOsc(jc, jc->mOscillators[id]->mode, Bank_OscToOfs(jc->mOscillators[id], &jc->mOscBuffers[id]));
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	000060
 */
void Effecter_Overwrite_1Shot(jc_* jc, Osc_* osc1, Osc_* osc2)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800155C0
 * Size:	00010C
 */
static jc_* __Oneshot_Play_Start(jcs_* jcs, jc_* jc, u32 id)
{
	BOOL play;

	if (id == 0) {
		id = -1;
	}
	jc->playId         = id;
	jc->savedPlayId    = jc->playId;
	jc->updateCallback = Jesus1Shot_Update;
	jc->dspChannel     = AllocDSPchannel(0, (uintptr_t)jc);

	if (jc->dspChannel == NULL) {
		play = CheckLogicalChannel(jc);
	} else {
		play = PlayLogicalChannel(jc);
	}

	if (jc->dspChannel == NULL && play == TRUE) {
		if (Add_WaitDSPChannel(jc) == TRUE) {
			List_AddChannelTail(&jcs->waitingChannels, jc);
			return jc;
		} else {
			List_AddChannelTail(&jcs->freeChannels, jc);
			return NULL;
		}
	} else if (play == FALSE) {
		DeAllocDSPchannel(jc->dspChannel, (uintptr_t)jc);
		jc->dspChannel = NULL;
		List_AddChannelTail(&jcs->freeChannels, jc);
		return NULL;
	} else {
		List_AddChannelTail(&jcs->activeChannels, jc);
	}
	return jc;
}

/*
 * --INFO--
 * Address:	800156E0
 * Size:	000154
 */
static jc_* __Oneshot_GetLogicalChannel(jcs_* jcs, CtrlWave_* wave)
{
	if (wave && wave->_0C == NULL) {
		return FALSE;
	}

	jc_* chan = List_GetChannel(&jcs->freeChannels);
	jc_* chan2;
	jc_** REF_chan2 = &chan2;
	if (chan == NULL) {

		if (FixAllocChannel(jcs, 1) == FALSE) {
			return 0;
		}
		jcs->chanAllocCount++;
		chan = List_GetChannel(&jcs->freeChannels);
		if (chan == NULL) {
			return 0;
		}

		if (jcs->voiceStealingMode == 1) {
			chan2 = List_GetChannel(&jcs->releasingChannels);
			if (chan2 == NULL) {
				chan2 = List_GetChannel(&jcs->activeChannels);
				if (chan2) {
					List_CountChannel(&jcs->waitingChannels);
				}
			}

			if (chan2) {
				chan2->mOscBuffers[0].state = 6;
				List_AddChannel(&jcs->waitingChannels, chan2);
				if (chan2->dspChannel) {
					ForceStopDSPchannel(chan2->dspChannel);
				}
			}
		}
	}
	Channel_Init(chan);
	if (wave) {
		chan->waveData        = (Wave_*)wave->_34;
		chan->_14             = wave->_0C;
		chan->logicalChanType = 0;
	}
	chan->_18 = 0;
	UpdatePanPower_1Shot(chan, 1.0f, 1.0f, 1.0f, 1.0f);
	return chan;
}

/*
 * --INFO--
 * Address:	80015840
 * Size:	000044
 */
Perc_* PercRead(u32 a1, u32 a2)
{
	Bank_* bank = Bank_Get(a1);
	if (bank == NULL) {
		return NULL;
	}

	return Bank_PercChange(bank, a2);
}

/*
 * --INFO--
 * Address:	800158A0
 * Size:	000044
 */
Inst_* InstRead(u32 a1, u32 a2)
{

	Bank_* bank = Bank_Get(a1);
	if (bank == NULL) {
		return NULL;
	}

	return Bank_InstChange(bank, a2);
}

/*
 * --INFO--
 * Address:	80015900
 * Size:	00002C
 */
Vmap_* VmapRead(Inst_* inst, u8 a1, u8 a2)
{
	Vmap_* map = (Vmap_*)Bank_GetInstVmap(inst, a1, a2);
	return !map ? NULL : map;
}

/*
 * --INFO--
 * Address:	80015940
 * Size:	000010
 */
static void __Oneshot_WavePause(jc_* jc, u8 a)
{
	jc->pauseFlag = a;
	jc->toFlush   = 1;
}

/*
 * --INFO--
 * Address:	80015960
 * Size:	00014C
 */
static BOOL __Oneshot_StartMonoPolyCheck(jc_* jc, u32 id)
{
	jcs_* mgr = jc->mMgr;
	jc_* chan = mgr->activeChannels;
	u32 index = 0;
	u8 flag   = id >> 0x18;
	u8 poly   = polys_table[flag & 0xf];


	if (poly == 0) {
		return TRUE;
	}

	while (TRUE) {
		if (chan == NULL) {
			break;
		}

		if (chan->soundId == id) {
			if (flag & 0x20) {
				index++;
			} else {
				chan->polyphonyCounter++;
				if (chan->polyphonyCounter == poly) {
					if (flag & 0x10) {
						ForceStopLogicalChannel(chan);
					} else {
						__Oneshot_WavePause(chan, 1);
					}
				}
			}
		}
		chan = (jc_*)chan->mNext;
	}

	chan = mgr->releasingChannels;
	while (TRUE) {
		if (chan == NULL) {
			break;
		}

		if (chan->soundId == id) {
			if (flag & 0x20) {
				index++;
			} else {
				chan->polyphonyCounter++;
				if (chan->polyphonyCounter == poly) {
					ForceStopLogicalChannel(chan);
				}
			}
		}

		chan = (jc_*)chan->mNext;
	}

	if (flag & 0x20) {
		jc->polyphonyCounter = index;
		if (index < poly) {
			return TRUE;
		}
		return FALSE;
	}

	jc->polyphonyCounter = 0;
	return TRUE;
}

/*
 * --INFO--
 * Address:	80015AC0
 * Size:	0000E8
 */
static void __Oneshot_StopMonoPolyCheck(jc_* jc, u32 id)
{
	jc_* chan;
	u8 poly;

	chan = jc->mMgr->activeChannels;
	poly = polys_table[id >> 0x18 & 0xf];

	if (id && poly) {

		while (TRUE) {
			if (chan == NULL) {
				break;
			}

			int flag = id >> 0x18 & 0x20;
			if (chan->soundId == id) {
				if (flag) {
					if (chan->polyphonyCounter > jc->polyphonyCounter) {
						chan->polyphonyCounter--;
						if (chan->polyphonyCounter == poly - 1) {
							__Oneshot_WavePause(chan, 0);
						}
					}
				} else {
					if (chan->polyphonyCounter > jc->polyphonyCounter) {
						chan->polyphonyCounter--;
						if (chan->polyphonyCounter < poly) {
							__Oneshot_WavePause(chan, 0);
						}
					}
				}
			}

			chan = (jc_*)chan->mNext;
		}
	}
}

/*
 * --INFO--
 * Address:	80015BC0
 * Size:	000070
 */
void Init_1shot(jcs_* jcs, u32 id)
{
	if (jcs->chanCount != 0) {
		FixReleaseChannelAll(jcs);
	}
	InitJcs(jcs);
	FixAllocChannel(jcs, id);
	if (id == 0) {
		jcs->voiceStealingMode = 0;
	} else {
		jcs->voiceStealingMode = 1;
	}
}

/*
 * --INFO--
 * Address:	80015C40
 * Size:	00003C
 */
void Stop_1Shot(jc_* jc)
{
	if (jc->dspChannel == 0) {
		Jesus1Shot_Update(jc, JCSTAT_Unk6);
	} else {
		Jesus1Shot_Update(jc, JCSTAT_Unk0);
	}
}

/*
 * --INFO--
 * Address:	80015C80
 * Size:	000040
 */
void Stop_1Shot_R(jc_* jc, u16 id)
{
	if (jc->dspChannel == 0) {
		Jesus1Shot_Update(jc, JCSTAT_Unk6);
	} else {
		jc->mOscBuffers[0].releaseParam = id;
		Jesus1Shot_Update(jc, JCSTAT_Unk0);
	}
}

/*
 * --INFO--
 * Address:	80015CC0
 * Size:	00006C
 */
void AllStop_1Shot(jcs_* jcs)
{
	List_CountChannel(&jcs->freeChannels);
	List_CountChannel(&jcs->activeChannels);
	List_CountChannel(&jcs->releasingChannels);
	List_CountChannel(&jcs->waitingChannels);

	jc_* jc = jcs->activeChannels;
	jc_* next;
	jc_** REF_jc = &jc;
	while (jc) {
		next = (jc_*)jc->mNext;
		Stop_1Shot(jc);
		jc = next;
	}
}

/*
 * --INFO--
 * Address:	80015D40
 * Size:	00006C
 * Note: Equivalent to `JASChannel::sweepProc` in later JAudio.
 */
static BOOL Extra_Update(jc_* jc, JCSTATUS status)
{
	if (jc->pitchSweepSteps != 0) {
		f32 pitch = jc->targetPitch;
		pitch -= jc->currentPitch;
		pitch /= jc->pitchSweepSteps;
		jc->currentPitch += pitch;
		jc->pitchSweepSteps--;

		if (jc->pitchSweepSteps == 0) {
			jc->pitchSweepUpdater = NULL;
		}
	}
	return FALSE;
}

/*
 * --INFO--
 * Address:	80015DC0
 * Size:	000030
 */
void SetPitchTarget_1Shot(jc_* jc, f32 pitch, u32 steps)
{
	if (steps == 0) {
		jc->currentPitch      = pitch;
		jc->pitchSweepUpdater = NULL;
		return;
	}

	jc->targetPitch       = pitch;
	jc->pitchSweepSteps   = steps;
	jc->pitchSweepUpdater = Extra_Update;
}

/*
 * --INFO--
 * Address:	80015E00
 * Size:	000090
 * Note: (Roughly) Equivalent to `JASChannel::setKeySweepTarget` in later JAudio.
 */
void SetKeyTarget_1Shot(jc_* jc, u8 key, u32 steps)
{
	int pitchKey;
	if (jc == 0) {
		return;
	}

	if (jc->logicalChanType == 2 || jc->waveData == NULL) {
		pitchKey = key;
	} else {
		pitchKey = key + 60 - jc->waveData->key;
	}

	if (pitchKey < 0) {
		pitchKey = 0;
	}
	if (pitchKey > 0x7f) {
		pitchKey = 0x7f;
	}

	f32 pitch = C5BASE_PITCHTABLE[pitchKey];
    pitch = jc->basePitch * pitch;
	SetPitchTarget_1Shot(jc, pitch, steps);
}

/*
 * --INFO--
 * Address:	80015EA0
 * Size:	0000C8
 */
void Gate_1Shot(jc_* jc, u8 key, u8 a2, s32 a3)
{
	if (jc->playId == -1) {
		jc->playId      = a3;
		jc->savedPlayId = jc->playId;
		int pitchKey;
		if (jc->logicalChanType == 2) {
			pitchKey = key;
		} else {
			pitchKey = key + 60 - jc->waveData->key;
		}
		if (pitchKey < 0) {
			pitchKey = 0;
		}
		if (pitchKey > 0x7f) {
			pitchKey = 0x7f;
		}

		f32 pitch         = C5BASE_PITCHTABLE[pitchKey];
		jc->velocity      = a2;
		jc->note          = key;
		jc->currentPitch  = jc->basePitch * pitch;
		jc->currentVolume = jc->velocity / 127.0f;
		jc->currentVolume = jc->currentVolume * jc->currentVolume * jc->baseVolume;
	}
}

/*
 * --INFO--
 * Address:	80015F80
 * Size:	000008
 */
void UpdatePause_1Shot(jc_* jc, u8 a1)
{
	jc->pauseFlag = a1;
}

/*
 * --INFO--
 * Address:	80015FA0
 * Size:	000030
 */
void UpdatePanPower_1Shot(jc_* channel, f32 leftPower, f32 rightPower, f32 centerPower, f32 v4)
{
	f32 val = leftPower + rightPower + centerPower;
	if (val == 0.0f) {
		return;
	}

	channel->panMatrices[0].values[0] = leftPower / val;
	channel->panMatrices[0].values[1] = rightPower / val;
	channel->panMatrices[0].values[2] = centerPower / val;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000068
 */
void CountChan(jc_* jc)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000068
 */
void CountChanD(jc_* jc)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000080
 */
void CheckChan(jc_* jc)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000AC
 */
void PrintChan(char* str, jc_* jc, u32 id)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80015FE0
 * Size:	0000B0
 */
void FlushRelease_1Shot(jcs_* jcs)
{
	int count = List_CountChannel(&jcs->releasingChannels);

	for (u32 i = 0; i < count; i++) {
		jc_* chan = List_GetChannel(&jcs->releasingChannels);
		if (chan == NULL) {
			break;
		}

		for (int j = 0; j < 2; j++) {
			if (chan->mOscillators[j]) {
				if (chan->mOscBuffers[j].state != 6 && chan->mOscBuffers[j].state != 7) {
					chan->mOscBuffers[j].state = 6;
				}
			}
		}

		List_AddChannelTail(&jcs->releasingChannels, chan);
	}
}

/*
 * --INFO--
 * Address:	800160A0
 * Size:	0001C4
 */
static BOOL Jesus1Shot_Update(jc_* jc, JCSTATUS jstatus)
{
    Oscbuf_* buf;
	u32 test    = FALSE;
	jc_** jcptr = &jc;
	s32 status  = jstatus;

	if (status == 0) {
		for (u32 i = 0; i < 2; i++) {
			if (jc->mOscillators[i]) {
				buf = &jc->mOscBuffers[i];
				if (buf->state != 6 && buf->state != 7) {
					buf->state = 4;
					test       = TRUE;
				}
			}
		}

		if (test && List_CutChannel(jc) != -1) {
			List_AddChannelTail(&jc->mMgr->releasingChannels, jc);
			if (jc->dspChannel) {
				u8 flag   = jc->channelPriority >> 8;
				u32 test2 = flag;
				if ((flag & 0xff) == 0) {
					test2 = 1;
				}
				jc->dspChannel->_03 = test2;
			}
		}
		jc->playId = -1;
		return FALSE;
	} else if (status == 1 || status == 2 || status == 6) {
		if (jc->mMgr->chanAllocCount) {
			if (List_CutChannel(jc) != -1) {
				jc->mMgr->chanAllocCount--;
				int id      = jc->soundId;
				jc->soundId = 0;
				__Oneshot_StopMonoPolyCheck(jc, id);
				FixReleaseChannel(jc);
			}
		} else {
			if (List_CutChannel(jc) != -1) {
				int id      = jc->soundId;
				jc->soundId = 0;
				__Oneshot_StopMonoPolyCheck(jc, id);
				List_AddChannel(&jc->mMgr->freeChannels, jc);
			}
		}
		if (status != 6) {
			StopLogicalChannel(jc);
		} else {
			Del_WaitDSPChannel(jc);
		}
		jc->note           = -1;
		jc->playId         = -1;
		jc->updateCallback = NULL;
	}
	return FALSE;
}

/*
 * --INFO--
 * Address:	80016280
 * Size:	000098
 */
u32 One_CheckInstWave(SOUNDID_ sound)
{
	Inst_* inst = InstRead(sound.bytes[0], sound.bytes[1]);
	if (inst == NULL) {
		return 1;
	}

	// TODO: fix this conversion to something wave-related once we've sorted that out
	int* map = (int*)VmapRead(inst, sound.bytes[2], sound.bytes[3]);
	if (map == NULL) {
		return 2;
	}

	// clearly need something better than map[1]
	CtrlGroup_* group = WaveidToWavegroup(map[1], sound.bytes[0]);
	if (group == NULL) {
		return 3;
	}

	WaveID_* handle = GetSoundHandle(group, map[1]);
	if (handle == 0) {
		return 4;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000090
 */
void Get_CtrlWave(SOUNDID_ sound)
{
	// UNUSED FUNCTION
}

typedef struct testPercMap {
	int _00; // this clearly should one of the existing structs, but Vmap doesnt work so I have no idea
	int _04;
	f32 _08;
	f32 _0C;
} testPercMap;

/*
 * --INFO--
 * Address:	80016320
 * Size:	00027C
 */
jc_* Play_1shot(jcs_* jcs, SOUNDID_ sound, u32 id)
{
	jc_* chan;
	Inst_* inst;
	WaveID_* wave;
	BOOL test = FALSE;

	inst = InstRead(sound.bytes[0], sound.bytes[1]);
	if (inst == NULL) {
		return NULL;
	}

	testPercMap* map = (testPercMap*)VmapRead(inst, sound.bytes[2], sound.bytes[3]);
	if (map == NULL) {
		return NULL;
	}

	CtrlGroup_* group = WaveidToWavegroup(map->_04, sound.bytes[0]);
	if (group == NULL) {
		return NULL;
	}

	wave = GetSoundHandle(group, map->_04);
	if (wave == NULL) {
		return NULL;
	}

	chan = __Oneshot_GetLogicalChannel(jcs, (CtrlWave_*)wave);
	if (chan == NULL) {
		return NULL;
	}

	int val = sound.bytes[2] + 60 - wave->data->key;
	if (val < 0) {
		val = 0;
	}
	if (val > 127) {
		val = 127;
	}
	f32 pitch                      = C5BASE_PITCHTABLE[val];
	chan->velocity                 = sound.bytes[3];
	chan->note                     = sound.bytes[2];
	chan->basePitch                = map->_0C * (wave->data->_04 / JAC_DAC_RATE) * inst->mGainMultiplier;
	chan->currentPitch             = chan->basePitch * pitch;
	chan->baseVolume               = map->_08 * inst->mFreqMultiplier;
	chan->currentVolume            = chan->velocity / 127.0f;
	chan->currentVolume            = chan->currentVolume * chan->currentVolume * chan->baseVolume;
	chan->panMatrices[1].values[0] = 0.5f;
	chan->panMatrices[2].values[0] = 0.0f;
	chan->panMatrices[3].values[0] = 0.0f;
	EffecterInit(chan, inst);

	int flag = inst->mFlag << 0x18 | sound.value >> 0x10;
	switch (inst->mFlag & 0xc0) {
	case 0xc0:
		flag |= 0xffffff;
		break;
	case 0x80:
		flag |= 0xff;
		break;
	case 0x40:
		flag |= Bank_GetInstKeymap(inst, sound.bytes[2]) << 0x10;
		break;
	}

	chan->soundId = 0;
	if (__Oneshot_StartMonoPolyCheck(chan, flag) == FALSE) {
		if (inst->mFlag & 0x10) {
			List_AddChannelTail(&jcs->freeChannels, chan);
			return FALSE;
		}
		test = TRUE;
	}
	chan->soundId = flag;

	jc_* newjc = __Oneshot_Play_Start(jcs, chan, id);
	if (test) {
		__Oneshot_WavePause(newjc, 1);
	}
	return newjc;
}

/*
 * --INFO--
 * Address:	800165A0
 * Size:	00020C
 */
jc_* Play_1shot_Perc(jcs_* jcs, SOUNDID_ sound, u32 id)
{
	jc_* chan;
	Perc_* perc;
	u32* idp = &id;

	perc = PercRead(sound.bytes[0], sound.bytes[1]);
	if (perc == NULL) {
		return NULL;
	}

	testPercMap* map   = (testPercMap*)Bank_GetPercVmap(perc, sound.bytes[2], sound.bytes[3]);
	testPercMap** mapp = &map;
	if (map == NULL) {
		return NULL;
	}

	u32 x;

	CtrlGroup_* group = WaveidToWavegroup(map->_04, sound.bytes[0]);
	if (group == NULL) {
		return NULL;
	}

	WaveID_* wave = GetSoundHandle(group, map->_04);
	if (wave == NULL) {
		return NULL;
	}

	chan = __Oneshot_GetLogicalChannel(jcs, (CtrlWave_*)wave);
	if (chan == NULL) {
		return NULL;
	}

	chan->velocity = sound.bytes[3];
	chan->note     = sound.bytes[2];

	chan->basePitch    = (wave->data->_04 / JAC_DAC_RATE) * map->_0C * perc->mKeyRegions[sound.bytes[2]]->mVolume;
	chan->currentPitch = chan->basePitch;

	chan->baseVolume    = map->_08 * perc->mKeyRegions[sound.bytes[2]]->mPitch;
	chan->currentVolume = chan->velocity / 127.0f;
	chan->currentVolume = chan->currentVolume * chan->currentVolume * chan->baseVolume;

	u16 flag;
	if (perc->mMagic == 'PER2') {
		chan->panMatrices[1].values[0] = perc->_288[sound.bytes[2]] / 127.0f;
		flag                           = perc->_308[sound.bytes[2]];
	} else {
		flag                           = 1000;
		chan->panMatrices[1].values[0] = 0.5f;
	}
	chan->panMatrices[2].values[0] = 0.0f;
	chan->panMatrices[3].values[0] = 0.0f;
	EffecterInit_Perc(chan, (Pmap_*)perc->mKeyRegions[sound.bytes[2]], flag);
	chan->soundId = 0;

	return __Oneshot_Play_Start(jcs, chan, id);
}

/*
 * --INFO--
 * Address:	800167C0
 * Size:	000128
 */
jc_* Play_1shot_Osc(jcs_* jcs, SOUNDID_ sound, u32 id)
{
	jc_* chan;
	u32 ids = id;
	int pit;
	jcs_* mgr = jcs;

	chan = __Oneshot_GetLogicalChannel(mgr, NULL);
	if (chan == NULL) {
		return NULL;
	}

	chan->_14             = sound.bytes[1] - 0xf0;
	chan->logicalChanType = 2;

	pit = sound.bytes[2];
	if (pit < 0) {
		pit = 0;
	}
	if (pit > 127) {
		pit = 127;
	}
	f32 pitch                      = C5BASE_PITCHTABLE[pit];
	chan->velocity                 = sound.bytes[3];
	chan->note                     = sound.bytes[2];
	chan->basePitch                = 16736.016f / JAC_DAC_RATE;
	chan->currentPitch             = chan->basePitch * pitch;
	chan->baseVolume               = 1.0f;
	chan->currentVolume            = chan->velocity / 127.0f;
	chan->currentVolume            = chan->currentVolume * chan->currentVolume;
	chan->panMatrices[1].values[0] = 0.5f;
	chan->panMatrices[2].values[0] = 0.0f;
	chan->panMatrices[3].values[0] = 0.0f;
	EffecterInit_Osc(chan);
	chan->soundId = 0;
	return __Oneshot_Play_Start(mgr, chan, ids);
}
