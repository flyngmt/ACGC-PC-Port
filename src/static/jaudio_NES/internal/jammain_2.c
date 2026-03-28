#include "jaudio_NES/jammain_2.h"

#include "jaudio_NES/oneshot.h"
#include "jaudio_NES/jamosc.h"
#include "jaudio_NES/seqsetup.h"
#include "jaudio_NES/fat.h"
#include "jaudio_NES/noteon.h"
#include "jaudio_NES/rate.h"
#include "jaudio_NES/random.h"
#include "jaudio_NES/centcalc.h"
#include "jaudio_NES/bankdrv.h"
#include "jaudio_NES/driverinterface.h"

#include "dolphin/os/OSError.h"
#include <dolphin/os/OSFastCast.h>
#include <dolphin/os.h>

// TODO IN THIS FILE: What do the return values for the `Cmd_` functions signify?
// 0 is probably success / "no error".  Return values 1 and 2 have been observed.
// This just breaking: Cmd_LoopE returns 0x80.

#define TRACK_LIST_SIZE (32)

typedef struct TrackListPair TrackListPair;
typedef struct Arghead_ Arghead_;

/**
 * @brief This is an invented pair-like struct, needed for `TRACK_LIST`.
 *
 * @note Size: 8.
 */
struct TrackListPair {
	seqp_* track; // _00
	u32 id;       // _04
};

/**
 * @brief This is an invented pair-like struct, needed for `Arglist`.
 *
 * @note Size: 4.
 */
struct Arghead_ {
	u16 argCount;
	u16 argTypes; // This is a bitfield array of eight 2-bit values
};

static TrackCallback JAM_CALLBACK_FUNC = NULL;

static size_t T_LISTS;
static TrackListPair TRACK_LIST[TRACK_LIST_SIZE];

static seqp_* SEQ_P;
static u8 SEQ_CMD;
static u32 SEQ_ARG[8];

// predeclare this so Jam_UpdateTrackAll can use this stupid function.
#ifndef TARGET_PC
extern "C" static void OSf32tos8(f32* in, s8* out);
#endif

/*
 * --INFO--
 * Address:	8000F400
 * Size:	000054
 */
void* Jam_OfsToAddr(seqp_* track, u32 ofs)
{
	// TODO: What do 0, 1, and 2 mean?
	switch (track->dataSourceMode) {
	case 0:
		return track->baseData + ofs;
	case 1:
	case 2:
		return FAT_GetPointer(track->fileHandle, ofs);
	}
	return 0;
}

/*
 * --INFO--
 * Address:	8000F460
 * Size:	000054
 */
static u8 __ByteReadOfs(seqp_* track, u32 ofs)
{
	// TODO: What do 0, 1, and 2 mean?
	switch (track->dataSourceMode) {
	case 0:
		return track->baseData[ofs];
	case 1:
	case 2:
		return FAT_ReadByte(track->fileHandle, ofs);
	}
	return 0;
}

/*
 * --INFO--
 * Address:	8000F4C0
 * Size:	000050
 */
static u16 __WordReadOfs(seqp_* track, u32 ofs)
{
	u16 result = __ByteReadOfs(track, ofs + 0) << 8;
	result |= __ByteReadOfs(track, ofs + 1);
	return result;
}

/*
 * --INFO--
 * Address:	8000F520
 * Size:	000068
 */
static u32 __24ReadOfs(seqp_* track, u32 ofs)
{
	u32 result;
	result = __ByteReadOfs(track, ofs + 0) << 16;
	result |= __ByteReadOfs(track, ofs + 1) << 8;
	result |= __ByteReadOfs(track, ofs + 2);
	return result;
}

/*
 * --INFO--
 * Address:	8000F5A0
 * Size:	000050
 */
static u32 __LongReadOfs(seqp_* track, u32 ofs)
{
	u32 result;
	result = __WordReadOfs(track, ofs + 0) << 16;
	result |= __WordReadOfs(track, ofs + 2);
	return result;
}

/*
 * --INFO--
 * Address:	8000F600
 * Size:	000070
 */
static u8 __ByteRead(seqp_* track)
{
	// TODO: What do 0, 1, and 2 mean?
	switch (track->dataSourceMode) {
	case 0:
		return track->baseData[track->programCounter++];
	case 1:
	case 2:
		return FAT_ReadByte(track->fileHandle, track->programCounter++);
	}
	return 0;
}

/*
 * --INFO--
 * Address:	8000F680
 * Size:	000048
 */
static u16 __WordRead(seqp_* track)
{
	u16 result;
	result = __ByteRead(track) << 8;
	result |= __ByteRead(track);
	return result;
}

/*
 * --INFO--
 * Address:	8000F6E0
 * Size:	00005C
 */
static u32 __24Read(seqp_* track)
{
	u32 result;
	result = __ByteRead(track) << 16;
	result |= __ByteRead(track) << 8;
	result |= __ByteRead(track);
	return result;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000048
 */
static u32 __32Read(seqp_* track)
{
	// Despite being unused, it's obvious this function is similar to `__LongReadOfs`.
	u32 result;
	result = __WordRead(track) << 16;
	result |= __WordRead(track);
	return result;
}

/*
 * --INFO--
 * Address:	8000F740
 * Size:	0000D0
 */
static BOOL __ConditionCheck(seqp_* track, u8 param_2)
{
	BOOL result;
	u16 uVar1;

	uVar1  = Jam_ReadRegDirect(track, 3);
	result = FALSE;

	switch (param_2 & 0x0f) {
	case 0:
		result = TRUE;
		break;
	case 1:
		if (uVar1 == 0) {
			result = TRUE;
		}
		break;
	case 2:
		if (uVar1 != 0) {
			result = TRUE;
		}
		break;
	case 3:
		if (uVar1 == 1) {
			result = TRUE;
		}
		break;
	case 4:
		if (uVar1 >= 0x8000) {
			result = TRUE;
		}
		break;
	case 5:
		if (uVar1 < 0x8000) {
			result = TRUE;
		}
		break;
	}
	return result;
}

/*
 * --INFO--
 * Address:	8000F820
 * Size:	000090
 * Note: Equivalent to `JASTrack::seqTimeToDspTime` in later JAudio
 */
int Jam_SEQtimeToDSPtime(seqp_* track, s32 param_2, u8 param_3)
{
	f32 dspTime;

	dspTime = (f32)param_2 * (f32)param_3 / 100.0f;

	if (track->timeRelationMode == 1) {
		dspTime = dspTime / track->tempoFactor;
	} else {
		dspTime = dspTime * 120.0f / track->timeBase;
	}

	return dspTime;
}

/*
 * --INFO--
 * Address:	8000F8C0
 * Size:	000020
 */
u16 Extend8to16(u8 value)
{
	if (value & 0x80) {
		return value + 0xFF00;
	}
	return value;
}

/*
 * --INFO--
 * Address:	8000F8E0
 * Size:	0001A8
 */
void Jam_WriteTimeParam(seqp_* track, u8 controlByte)
{

	s32 duration;
	u8 paramIndex;
	s16 targetValue;
	MoveParam_* param;

	duration   = 0;
	paramIndex = __ByteRead(track);

	// Extract target value based on controlByte[3:2]
	switch (controlByte & 0x0C) {
	case 0x00: // Use register value
		targetValue = track->regParam.reg[__ByteRead(track)];
		break;
	case 0x04: // 8-bit immediate value
		targetValue = __ByteRead(track);
		break;
	case 0x08: // 8-bit value shifted to high byte
		targetValue = __ByteRead(track) << 8;
		break;
	case 0x0C: // 16-bit immediate value
		targetValue = __WordRead(track);
		break;
	}

	// Determine time over which to interpolate the parameter
	switch (controlByte & 0x03) {
	case 0: // Immediate (no interpolation)
		duration = -1;
		break;
	case 1: // Time from register
		duration = track->regParam.reg[__ByteRead(track)];
		break;
	case 2: // 8-bit immediate duration
		duration = __ByteRead(track);
		break;
	case 3: // 16-bit immediate duration
		duration = __WordRead(track);
		break;
	}

	param              = &track->timedParam.move[paramIndex];
	param->targetValue = targetValue / 32768.0f;

	if (duration >= 0) {
		param->duration = duration;
	}

	if (param->duration <= 0.0f) {
		param->currentValue = param->targetValue;
		param->stepSize     = 0.0f;
		param->duration     = 1.0f;
	} else {
		param->stepSize = (param->targetValue - param->currentValue) / param->duration;
	}
}

/*
 * --INFO--
 * Address:	8000FAA0
 * Size:	0000AC
 */
void Jam_WriteRegDirect(seqp_* track, u8 index, u16 value)
{

	u16 uVar1;

	switch (index) {
	case 0:
	case 1:
	case 2:
		value = value & 0xff;
		uVar1 = Extend8to16(value);
		break;
	case 32:
	case 33:
		return;
	case 34:
		Jam_WriteRegDirect(track, 0, value >> 8);
		uVar1 = value;
		value = value & 0xff;
		index = 1;
		break;
	default:
		uVar1 = value;
		break;
	}

	track->regParam.reg[index]  = value;
	track->regParam.param.value = uVar1;
}

/*
 * --INFO--
 * Address:	8000FB60
 * Size:	000098
 */
static u32 LoadTbl(seqp_* track, u32 ofs, u32 idx, u32 param_4)
{
	u32 result;

	switch (param_4) {
	case 4:
		result = __ByteReadOfs(track, ofs + idx);
		break;
	case 5:
		idx    = idx * 2;
		result = __WordReadOfs(track, ofs + idx);
		break;
	case 6:
		idx    = idx * 2 + idx; // Roundabout way to multiply by 3.
		result = __24ReadOfs(track, ofs + idx);
		break;
	case 7:
		idx = idx * 4;
	case 8:
		result = __LongReadOfs(track, ofs + idx);
		break;
	}
	return result;
}

/*
 * --INFO--
 * Address:	8000FC00
 * Size:	000484
 */
void Jam_WriteRegParam(seqp_* track, u8 param_2)
{

	s16 r30_newRegValue; // r30
	u8 r29_regIdx;       // r29
	u16 r28;             // r28
	u32 unaff_r27;       // r27
	u32 r26;             // r26
	u32 r25;             // r25
	u32 unaff_r24;       // r24
	s16 r23_oldRegValue; // r23

	r26 = param_2 & 0xc;
	r25 = param_2 & 3;
	if ((param_2 & 0x0F) == 0x0B) {
		r26 = 0;
		r25 = 0xb;
	}
	if ((param_2 & 0x0F) == 0x0A) {
		param_2   = __ByteRead(track);
		r26       = param_2 & 0x0C;
		r25       = 0xa;
		unaff_r24 = (u8)(param_2 >> 4) + 4;
	}
	if ((param_2 & 0x0F) == 0x09) {
		param_2 = __ByteRead(track);
		r26     = param_2 & 0x0c;
		r25     = param_2 & 0xf0;
		if (r26 == 8) {
			r26 = 0x10;
		}
	}
	r29_regIdx = __ByteRead(track);
	if (r25 == 0x0A) {
		unaff_r27 = Jam_ReadReg32(track, __ByteRead(track));
	}
	switch (r26) {
	case 0:
		r30_newRegValue = Jam_ReadRegDirect(track, __ByteRead(track));
		break;
	case 4:
		r30_newRegValue = __ByteRead(track);
		break;
	case 8:
		r30_newRegValue = __ByteRead(track) << 8;
		break;
	case 12:
		r30_newRegValue = __WordRead(track);
		break;
	case 16:
		r30_newRegValue = -1;
	}

	r23_oldRegValue = Jam_ReadRegDirect(track, r29_regIdx);
	switch (r25) {
	case 0x00:
		break;
	case 0x01:
		if (r26 == 4) {
			r30_newRegValue = Extend8to16(r30_newRegValue);
		}
		r30_newRegValue = r23_oldRegValue + r30_newRegValue;
		break;
	case 0x02:
		unaff_r27 = r23_oldRegValue * r30_newRegValue;
		Jam_WriteRegXY(track, unaff_r27);
		return;
	case 0x03:
		track->regParam.param.value = r23_oldRegValue - r30_newRegValue;
		return;
	case 0x0B:
		r30_newRegValue = r23_oldRegValue - r30_newRegValue;
		break;
	case 0x10:
		if (r26 == 4) {
			r30_newRegValue = Extend8to16(r30_newRegValue);
		}
		if (r30_newRegValue < 0) {
			r30_newRegValue = (u16)r23_oldRegValue >> -r30_newRegValue;
		} else {
			r30_newRegValue = (u16)r23_oldRegValue << r30_newRegValue;
		}
		break;
	case 0x20:
		if (r26 == 4) {
			r30_newRegValue = Extend8to16(r30_newRegValue);
		}
		if (r30_newRegValue < 0) {
			r30_newRegValue = r23_oldRegValue >> -r30_newRegValue;
		} else {
			r30_newRegValue = r23_oldRegValue << r30_newRegValue;
		}
		break;
	case 0x30:
		r30_newRegValue = r23_oldRegValue & r30_newRegValue;
		break;
	case 0x40:
		r30_newRegValue = r23_oldRegValue | r30_newRegValue;
		break;
	case 0x50:
		r30_newRegValue = r23_oldRegValue ^ r30_newRegValue;
		break;
	case 0x60:
		r30_newRegValue = -r23_oldRegValue;
		break;
	case 0x90:
		unaff_r27       = GetRandom_s32();
		r30_newRegValue = unaff_r27 % (u16)r30_newRegValue;
		break;
	case 0xA:
		unaff_r27       = LoadTbl(track, unaff_r27, r30_newRegValue, unaff_r24);
		r30_newRegValue = (u16)unaff_r27;
		break;
	}

	switch (r29_regIdx) {
	case 0:
	case 1:
	case 2:
		r30_newRegValue = r30_newRegValue & 0xff;
		r28             = Extend8to16(r30_newRegValue);
		break;
	case 0x21:
		r29_regIdx      = 6;
		r30_newRegValue = track->regParam.param.bankNumber & 0xff00 | r30_newRegValue & 0x00ff;
		break;
	case 0x20:
		r29_regIdx      = 6;
		r30_newRegValue = track->regParam.param.bankNumber & 0x00ff | r30_newRegValue << 8;
		break;
	case 0x2E:
		r29_regIdx      = 0xd;
		r30_newRegValue = track->regParam.param.basePriority & 0xff00 | r30_newRegValue & 0x00ff;
		break;
	case 0x2F:
		r29_regIdx      = 0xd;
		r30_newRegValue = track->regParam.param.basePriority & 0x00ff | r30_newRegValue << 8;
		break;
	case 0x22:
		Jam_WriteRegDirect(track, 0, r30_newRegValue >> 8);
		r30_newRegValue = r30_newRegValue & 0xff;
		r28             = r30_newRegValue;
		r29_regIdx      = 1;
		break;
	case 0x28:
	case 0x29:
	case 0x2A:
	case 0x2B:
		track->regParam.param._20[r29_regIdx - 0x28] = unaff_r27;
		return;
	default:
		r28 = r30_newRegValue;
		break;
	}

	track->regParam.reg[r29_regIdx] = r30_newRegValue;
	track->regParam.param.value     = r28;

	if (r29_regIdx == 6) {
		Osc_Clear_Overwrite(track);
	}
	if (r29_regIdx == 7) {
		track->updateFlags |= OuterParamFlag_Pitch;
	}
	if (r29_regIdx == 0xd) {
		track->parentController.channelPriority = track->regParam.param.basePriority | 0x10000;
		track->parentController.releaseTime     = 0;
	}
}

/*
 * --INFO--
 * Address:	800100A0
 * Size:	00016C
 */
u16 Jam_ReadRegDirect(seqp_* track, u8 regIdx)
{
	s16 result;
	u16 regDirectLo;
	u16 regDirectHi;
	int i;

	switch (regIdx) {
	case 0x20:
	case 0x21:
		result = track->regParam.param.bankNumber;
		break;
	case 0x22:
		regDirectLo = Jam_ReadRegDirect(track, 1);
		regDirectHi = Jam_ReadRegDirect(track, 0);
		result      = regDirectHi << 8 | regDirectLo;
		break;
	case 0x2C:
		result = 0;
		for (i = 15; i >= 0; --i) {
			result = result << 1; // For some reason, `<<=` prevents `srawi`.
			if (track->children[i] && track->children[i]->trackState) {
				result |= 1;
			}
		}
		break;
	case 0x2D:
		result = 0;
		for (i = 7; i >= 0; --i) {
			result = result << 1; // For some reason, `<<=` prevents `srawi`.
			result |= (u8)CheckNoteStop(track, i);
		}
		break;
	case 0x30:
		if (track->callStackDepth == 0) {
			result = 0;
		} else {
			result = track->loopCounters[track->callStackDepth - 1];
		}
		break;
	default:
		result = track->regParam.reg[regIdx];
		break;
	}
	switch (regIdx) {
	case 0x00:
	case 0x01:
	case 0x02:
	case 0x21:
		result = result & 0xff;
		break;
	case 0x20:
		result = result >> 8;
		break;
	}
	return result;
}

/*
 * --INFO--
 * Address:	80010220
 * Size:	000048
 */
u32 Jam_ReadRegXY(seqp_* track)
{
	return (Jam_ReadRegDirect(track, 4) << 16) | Jam_ReadRegDirect(track, 5);
}

/*
 * --INFO--
 * Address:	80010280
 * Size:	00005C
 */
u32 Jam_ReadReg32(seqp_* track, u8 index)
{
	switch (index) {
	case 40:
	case 41:
	case 42:
	case 43:
		return track->regParam.param._20[index - 40];
	case 35:
		return Jam_ReadRegXY(track);
	}
	return Jam_ReadRegDirect(track, index);
}

/*
 * --INFO--
 * Address:	800102E0
 * Size:	000048
 */
void Jam_WriteRegXY(seqp_* track, u32 param_2)
{
    u16 v = param_2 >> 16;
	Jam_WriteRegDirect(track, 4, (u16)v);
    u16 v2 = param_2;
	Jam_WriteRegDirect(track, 5, (u16)v2);
}

/*
 * --INFO--
 * Address:	80010340
 * Size:	00003C
 * Note: Equivalent to `JASTrack::exchangeRegisterValue` in later JAudio.
 */
u32 __ExchangeRegisterValue(seqp_* track, u8 param_2)
{
	if (param_2 < 64) {
		return Jam_ReadReg32(track, param_2);
	}
	return track->trackPort[param_2 - 64].value;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00004C
 */
void Jam_WritePortApp(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00004C
 */
void Jam_ReadPortApp(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000048
 */
void Jam_CheckExportApp(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000048
 */
void Jam_CheckImportApp(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A0
 */
void Jam_WritePortIndirect(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000058
 */
void Jam_ReadPortIndirect(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000A4
 */
void Jam_CheckPortIndirect(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80010380
 * Size:	000078
 */
BOOL Jam_WritePortAppDirect(seqp_* track, u32 param_2, u16 param_3)
{
	if (!track) {
		return FALSE;
	}
	track->trackPort[param_2].value      = param_3;
	track->trackPort[param_2].importFlag = 1;
	if (param_2 == 0) {
		Jam_SetInterrupt(track, 3);
	}
	if (param_2 == 1) {
		Jam_SetInterrupt(track, 4);
	}
	return TRUE;
}

/*
 * --INFO--
 * Address:	80010400
 * Size:	000030
 */
BOOL Jam_ReadPortAppDirect(seqp_* track, u32 param_2, u16* param_3)
{
	if (!track) {
		return FALSE;
	}
	*param_3                             = track->trackPort[param_2].value;
	track->trackPort[param_2].exportFlag = 0;
	return TRUE;
}

/*
 * --INFO--
 * Address:	80010440
 * Size:	00006C
 */
BOOL Jam_CheckPortAppDirect(seqp_* track, u32 param_2, u16 param_3)
{
	// Again with the cast to u8... what is it?
	switch ((u8)param_3) {
	case FALSE:
		if (track->trackPort[param_2].exportFlag == FALSE) {
			return FALSE;
		}
		return TRUE;
	case TRUE:
		if (track->trackPort[param_2].importFlag == TRUE) {
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000018
 */
void Jam_WritePort(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000018
 */
void Jam_ReadPort(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000034
 */
void Jam_WritePortChild(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	000038
 */
void Jam_WritePortBros(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800104C0
 * Size:	000030
 */
void Jam_InitRegistTrack(void)
{
	int i;

	T_LISTS = 0;
	for (i = 0; i < TRACK_LIST_SIZE; ++i) {
		TRACK_LIST[i].track = NULL;
	}
}

/*
 * --INFO--
 * Address:	80010500
 * Size:	0000A8
 */
void Jam_RegistTrack(seqp_* track, u32 param_2)
{
	u32* REF_param_2;
	size_t i;

	for (i = 0; i < T_LISTS; ++i) {
		if (param_2 == TRACK_LIST[i].id) {
			return;
		}
	}
	if (T_LISTS == TRACK_LIST_SIZE) {
		for (i = 0; i < TRACK_LIST_SIZE; ++i) {
			if (!TRACK_LIST[i].track) {
				break;
			}
		}
		if (i == TRACK_LIST_SIZE) {
			return;
		}
	} else {
		i = T_LISTS;
		++T_LISTS;
	}
	REF_param_2         = &param_2;
	TRACK_LIST[i].id    = param_2;
	TRACK_LIST[i].track = track;
	track->isRegistered = 1;
}

/*
 * --INFO--
 * Address:	800105C0
 * Size:	00008C
 */
void Jam_UnRegistTrack(seqp_* track)
{
	size_t i;

	if (!track->isRegistered) {
		return;
	}
	for (i = 0; i < T_LISTS; ++i) {
		if (track == TRACK_LIST[i].track) {
			TRACK_LIST[i].track = NULL;
		}
	}
	track->isRegistered = FALSE;
	for (; T_LISTS != 0; --T_LISTS) {
		if (TRACK_LIST[T_LISTS - 1].track) {
			break;
		}
	}
}

/*
 * --INFO--
 * Address:	80010660
 * Size:	000050
 */
seqp_* Jam_GetTrackHandle(u32 param_1)
{
	size_t i;

	for (i = 0; i < T_LISTS; ++i) {
		if (param_1 == TRACK_LIST[i].id && TRACK_LIST[i].track) {
			return TRACK_LIST[i].track;
		}
	}
	return NULL;
}

/*
 * --INFO--
 * Address:	800106C0
 * Size:	000018
 */
void Jam_InitExtBuffer(OuterParam_* ext)
{
	ext->flags       = 0;
	ext->updateFlags = 0;
	ext->isAssigned  = FALSE;
	ext->refCount    = 0;
}

/*
 * --INFO--
 * Address:	800106E0
 * Size:	000038
 */
BOOL Jam_AssignExtBuffer(seqp_* track, OuterParam_* ext)
{
	if (!track) {
		return FALSE;
	}
	if (!ext) {
		return FALSE;
	}
	track->outerParams = ext;
	++ext->refCount;
	return TRUE;
}

/*
 * --INFO--
 * Address:	80010720
 * Size:	000060
 */
BOOL Jam_AssignExtBufferP(seqp_* track, u8 index, OuterParam_* ext)
{
	if (!track) {
		return FALSE;
	}
	if (!ext) {
		return FALSE;
	}
	track->childOuterParams[index] = ext;
	ext->isAssigned                = TRUE;
	Jam_AssignExtBuffer(track->children[index], ext);
	return TRUE;
}

/*
 * --INFO--
 * Address:	80010780
 * Size:	000044
 */
void Jam_SetExtFirFilterD(OuterParam_* ext, s16* param_2)
{
	int i;

	if (!ext) {
		return;
	}
	ext->updateFlags |= OuterParamFlag_FIR8Filter;
	ext->flags |= OuterParamFlag_FIR8Filter;
	for (i = 0; i < 8; ++i) {
		ext->firCoefficients[i] = param_2[i];
	}
}

/*
 * --INFO--
 * Address:	800107E0
 * Size:	0000A4
 */
void Jam_SetExtParamD(f32 value, OuterParam_* ext, u8 updateFlags)
{
	f32* member;

	if (!ext) {
		return;
	}

	switch (updateFlags) {
	case OuterParamFlag_Volume:
		member = &ext->volume;
		break;
	case OuterParamFlag_Pitch:
		member = &ext->pitch;
		break;
	case OuterParamFlag_Fxmix:
		member = &ext->fxMix;
		break;
	case OuterParamFlag_Dolby:
		member = &ext->dolby;
		break;
	case OuterParamFlag_Pan:
		member = &ext->pan;
		break;
	case OuterParamFlag_Tempo:
		member = &ext->tempo;
		break;
	default:
		return;
	}

	*member = value;
	ext->updateFlags |= updateFlags;
}

/*
 * --INFO--
 * Address:	800108A0
 * Size:	000024
 */
void Jam_OnExtSwitchD(OuterParam_* ext, u16 param_2)
{
	if (!ext) {
		return;
	}
	ext->flags |= param_2;
	ext->updateFlags |= param_2;
}

/*
 * --INFO--
 * Address:	800108E0
 * Size:	000028
 */
void Jam_OffExtSwitchD(OuterParam_* ext, u16 param_2)
{
	if (!ext) {
		return;
	}
	ext->flags ^= ext->flags & param_2;
	ext->updateFlags |= param_2;
}

/*
 * --INFO--
 * Address:	........
 * Size:	00001C
 */
void Jam_SetExtSwitchDirectD(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
void Jam_SetExtFirFilter(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80010920
 * Size:	00002C
 */
void Jam_SetExtParam(f32 param_1, seqp_* track, u8 param_3)
{
	if (!track) {
		return;
	}
	Jam_SetExtParamD(param_1, track->outerParams, param_3);
}

/*
 * --INFO--
 * Address:	80010960
 * Size:	00002C
 */
void Jam_OnExtSwitch(seqp_* track, u16 param_2)
{
	if (!track) {
		return;
	}
	Jam_OnExtSwitchD(track->outerParams, param_2);
}

/*
 * --INFO--
 * Address:	800109A0
 * Size:	00002C
 */
void Jam_OffExtSwitch(seqp_* track, u16 param_2)
{
	if (!track) {
		return;
	}
	Jam_OffExtSwitchD(track->outerParams, param_2);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
void Jam_SetExtSwitchDirect(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void Jam_SetExtFirFilterP(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800109E0
 * Size:	000038
 */
void Jam_SetExtParamP(f32 param_1, seqp_* track, u8 index, u8 param_4)
{
	if (!track) {
		return;
	}
	Jam_SetExtParamD(param_1, track->childOuterParams[index], param_4);
}

/*
 * --INFO--
 * Address:	80010A20
 * Size:	00003C
 */
void Jam_OnExtSwitchP(seqp_* track, u8 index, u16 param_3)
{
	if (!track) {
		return;
	}
	Jam_OnExtSwitchD(track->childOuterParams[index], param_3);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void Jam_OffExtSwitchP(seqp_* track, u8 index, u16 param_3)
{
	if (!track) {
		return;
	}
	Jam_OffExtSwitchD(track->childOuterParams[index], param_3);
}

/*
 * --INFO--
 * Address:	........
 * Size:	00003C
 */
void Jam_SetExtSwitchDirectP(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	........
 * Size:	00002C
 */
void Jam_CheckRunningCounter(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80010A60
 * Size:	00000C
 */
BOOL Jam_RegisterTrackCallback(TrackCallback callback)
{
	JAM_CALLBACK_FUNC = callback;
	return TRUE;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000038
 */
void Jam_SetTrackExtPanPower(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80010A80
 * Size:	00004C
 */
static f32 __PanCalc(f32 param_1, f32 param_2, f32 param_3, u8 param_4)
{
	f32 result;

	switch (param_4) {
	case 0:
		return param_1;
	case 1:
		return param_2;
	case 2:
		result = param_1 * (1.0f - param_3) + (param_2 * param_3);
	}
	return result;
}

/*
 * --INFO--
 * Address:	80010AE0
 * Size:	000320
 */
void Jam_UpdateTrackAll(seqp_* track)
{
	f32 volumeValue;
	f32 pitchCents;
	f32 panValue;
	f32 fxMixValue;
	f32 dolbyValue;
	f32 distance;
	f32 parentDistance;

	f32 panScaled;
	s8 pan8bit;
	s8 panDelayLeft;

	size_t i;

	distance = track->regParam.param.arguments[3] / 32767.0f;
	if (track->flags != 4) {
		track->parentController.channelPriority = track->regParam.param.basePriority | 0x10000;
		track->parentController.releaseTime     = 0;

		panDelayLeft = 0;
		panScaled    = track->timedParam.inner._110.currentValue * 128.0f;

		OSf32tos8(&panScaled, &pan8bit);
		if (pan8bit < 0) {
			panDelayLeft = -pan8bit;
			pan8bit      = 0;
		}

		track->parentController.maxDelay        = 0x10;
		track->parentController.masterLevels[0] = panDelayLeft;
		track->parentController.masterLevels[1] = pan8bit;

		// Read base volume; if muted, force to zero
		volumeValue = track->timedParam.inner.volume.currentValue;
		if (track->isMuted > 0) {
			volumeValue = 0.0f;
		}

		// Convert pitch to cents, read pan/fxmix/dolby from timed parameters
		pitchCents = Jam_PitchToCent(track->timedParam.inner.pitch.currentValue, track->regParam.param.pitchScale);
		panValue   = track->timedParam.inner.pan.currentValue;
		fxMixValue = track->timedParam.inner.fxmix.currentValue;
		dolbyValue = track->timedParam.inner.dolby.currentValue;

		if (track->outerParams) {
			if (track->outerParams->flags & OuterParamFlag_Volume) {
				volumeValue = volumeValue * track->outerParams->volume;
			}

			if (track->outerParams->flags & OuterParamFlag_Pitch) {
				pitchCents = pitchCents * track->outerParams->pitch;
			}

			if (track->outerParams->flags & OuterParamFlag_Fxmix) {
				fxMixValue = __PanCalc(fxMixValue, track->outerParams->fxMix, distance, track->panCalcTypes[1]);
			}

			if (track->outerParams->flags & OuterParamFlag_Dolby) {
				dolbyValue = __PanCalc(dolbyValue, track->outerParams->dolby, distance, track->panCalcTypes[2]);
			}

			if (track->outerParams->flags & OuterParamFlag_Pan) {
				panValue = __PanCalc(panValue, track->outerParams->pan, distance, track->panCalcTypes[0]);
			}
		}

		// If there is no parent or this track overrides its parent (trackFlags & 1),
		// write the final values directly into the channel state
		if (!track->parent || (track->flags & 1)) {
			track->parentController.volume = volumeValue;
			track->parentController.pitch  = pitchCents;
			track->parentController.pan    = panValue;
			track->parentController.fxmix  = fxMixValue;
			track->parentController.dolby  = dolbyValue;
		} else {
			// Otherwise, combine with parent’s values using a second attenuation factor
			parentDistance = track->regParam.param.arguments[4] / 32767.0f;

			track->parentController.volume = track->parent->parentController.volume * volumeValue;
			track->parentController.pitch  = track->parent->parentController.pitch * pitchCents;
			track->parentController.pan
			    = __PanCalc(panValue, track->parent->parentController.pan, parentDistance, track->parentPanCalcTypes[0]);
			track->parentController.fxmix
			    = __PanCalc(fxMixValue, track->parent->parentController.fxmix, parentDistance, track->parentPanCalcTypes[1]);
			track->parentController.dolby
			    = __PanCalc(dolbyValue, track->parent->parentController.dolby, parentDistance, track->parentPanCalcTypes[2]);

			// If outerParams specify a custom FIR filter, copy those coefficients
			if (track->outerParams && (track->outerParams->flags & OuterParamFlag_FIR8Filter)) {
				for (i = 0; i < 8; ++i) {
					track->parentController.firCoefficients[i] = track->outerParams->firCoefficients[i];
				}

				track->parentController.filterMode = 8;
			}

			// Read inner IIR coefficients (normalized floats) and convert to 16-bit
			for (i = 0; i < 4; ++i) {
				track->parentController.iirCoefficients[i] = track->timedParam.inner.IIRs[i].currentValue * 32767.0f;
			}

			track->parentController.filterMode |= 0x20;
			track->parentController.distFilter = track->timedParam.inner.distFilter.currentValue * 32767.0f;
		}
	}
}

#define OS_FASTCAST_S8 (4)

/*
 * --INFO--
 * Address:	80010E00
 * Size:	00000C
 */
static void OSf32tos8(register f32* in, volatile register s8* out)
{
    *out = __OSf32tos8(*in);
}

/*
 * --INFO--
 * Address:	80010E20
 * Size:	0004A8
 */
void Jam_UpdateTrack(seqp_* track, u32 updateFlags)
{
	// A bizarre way the devs attempted to re-use some repeated AND operations in this function,
	// which the compiler can already see and optimize in its own way, causes regalloc inflation.
	u32 updateVolumeFlag;
	u32 updatePitchFlag;
	u32 updatePanFlag;
	u32 updateFxMixFlag;
	u32 updateDolbyFlag;

	f32 computedVolume; // f31
	f32 unaff_f30;      // f30
	f32 unaff_f29;      // f29
	f32 unaff_f28;      // f28
	f32 unaff_f27;      // f27
	f32 regionAttenuation;
	f32 offset;
	f32 dVar15_3;

	size_t i;

	// Used for `OSf32tos8`
	f32 masterLevelF32;
	s8 masterRight;
	s8 masterLeft;

	regionAttenuation = track->regParam.param.arguments[3] / 32767.0f;

	if (track->flags != 0x04) {

		// Update master pan delay levels if requested
		if (updateFlags & SEQTRACK_FLAG_MASTER_LEVEL) {
			masterLeft     = 0;
			masterLevelF32 = track->timedParam.inner._110.currentValue * 128.0f;
			OSf32tos8(&masterLevelF32, &masterRight);
			if (masterRight < 0) {
				masterLeft  = -masterRight;
				masterRight = 0;
			}
			track->parentController.masterLevels[0] = masterLeft;
			track->parentController.masterLevels[1] = masterRight;
		}

		// Tempo update (only if top-level track)
		if (updateFlags & OuterParamFlag_Tempo && !track->parent) {
			Jam_UpdateTempo(track);
		}

		updateVolumeFlag = updateFlags & OuterParamFlag_Volume;
		if (updateVolumeFlag) {
			computedVolume = track->timedParam.inner.volume.currentValue;
			if (track->isMuted != 0) {
				computedVolume = 0.0f;
			}

			if (track->outerParams && (track->outerParams->flags & OuterParamFlag_Volume)) {
				computedVolume *= track->outerParams->volume;
			}

			if (track->isPaused && (track->pauseStatus & 1)) {
				computedVolume *= track->timedParam.inner._100.currentValue;
			}
		}

		updatePitchFlag = updateFlags & OuterParamFlag_Pitch;
		if (updatePitchFlag) {
			unaff_f30 = Jam_PitchToCent((track->timedParam).inner.pitch.currentValue, track->regParam.param.pitchScale);
			if (track->outerParams && ((track->outerParams->flags & OuterParamFlag_Pitch) != 0)) {
				unaff_f30 = (unaff_f30 * track->outerParams->pitch);
			}
		}

		updatePanFlag = updateFlags & OuterParamFlag_Pan;
		if (updatePanFlag) {
			unaff_f29 = (track->timedParam).inner.pan.currentValue;
			if (track->outerParams && ((track->outerParams->flags & OuterParamFlag_Pan) != 0)) {
				unaff_f29 = __PanCalc(unaff_f29, track->outerParams->pan, regionAttenuation, track->panCalcTypes[0]);
			}
		}

		updateFxMixFlag = updateFlags & OuterParamFlag_Fxmix;
		if (updateFxMixFlag) {
			unaff_f28 = (track->timedParam).inner.fxmix.currentValue;
			if (track->outerParams && ((track->outerParams->flags & OuterParamFlag_Fxmix) != 0)) {
				unaff_f28 = __PanCalc(unaff_f28, track->outerParams->fxMix, regionAttenuation, track->panCalcTypes[1]);
			}
		}

		updateDolbyFlag = updateFlags & OuterParamFlag_Dolby;
		if (updateDolbyFlag) {
			unaff_f27 = (track->timedParam).inner.dolby.currentValue;
			if (track->outerParams && ((track->outerParams->flags & OuterParamFlag_Dolby) != 0)) {
				unaff_f27 = __PanCalc(unaff_f27, track->outerParams->dolby, regionAttenuation, track->panCalcTypes[2]);
			}
		}

		// IIR flag is set
		if (updateFlags & OuterParamFlag_IIRFilter) {
			for (i = 0; i < 4; ++i) {
				track->parentController.iirCoefficients[i] = track->timedParam.inner.IIRs[i].currentValue * 32767.0f;
			}

			track->parentController.filterMode |= 0x20;
		}

		if (track->outerParams) {
			if (updateFlags & OuterParamFlag_FIR8Filter && (track->outerParams->flags & OuterParamFlag_FIR8Filter)) {
				for (i = 0; i < 8; ++i) {
					track->parentController.firCoefficients[i] = track->outerParams->firCoefficients[i];
				}

				track->parentController.filterMode = (track->parentController.filterMode & 0x20) + 8;
			}
		}

		if (updateFlags & OuterParamFlag_DistFilt) {
			track->parentController.distFilter = track->timedParam.inner.distFilter.currentValue * 32767.0f;
		}

		for (i = 0; i < 2; ++i) {
			if (track->oscillatorRouting[i] == 0x0E) {
				offset = Bank_OscToOfs(&track->oscillators[i], &track->oscillatorParams[i]);
				switch (track->oscillators[i].mode) {
				case 1:
					unaff_f30 = unaff_f30 * offset;
					break;
				case 0:
					computedVolume = computedVolume * offset;
					break;
				case 2:
					unaff_f29 = unaff_f29 * offset;
					break;
				case 3:
					unaff_f28 = unaff_f28 * offset;
					break;
				case 4:
					unaff_f27 = unaff_f27 * offset;
					break;
				}
			}
		}
		if (!track->parent || ((track->flags & 1) != 0)) {
			if (updateVolumeFlag) {
				track->parentController.volume = computedVolume;
			}
			if (updatePitchFlag) {
				track->parentController.pitch = unaff_f30;
			}
			if (updatePanFlag) {
				track->parentController.pan = unaff_f29;
			}
			if (updateFxMixFlag) {
				track->parentController.fxmix = unaff_f28;
			}
			if (updateDolbyFlag != 0) {
				track->parentController.dolby = unaff_f27;
			}
		} else {
			dVar15_3 = track->regParam.param.arguments[4] / 32767.0f;
			if (updateVolumeFlag) {
				track->parentController.volume = track->parent->parentController.volume * computedVolume;
			}
			if (updatePitchFlag) {
				track->parentController.pitch = track->parent->parentController.pitch * unaff_f30;
			}
			if (updatePanFlag) {
				track->parentController.pan
				    = __PanCalc(unaff_f29, track->parent->parentController.pan, dVar15_3, track->parentPanCalcTypes[0]);
			}
			if (updateFxMixFlag) {
				track->parentController.fxmix
				    = __PanCalc(unaff_f28, track->parent->parentController.fxmix, dVar15_3, track->parentPanCalcTypes[1]);
			}
			if (updateDolbyFlag) {
				track->parentController.dolby
				    = __PanCalc(unaff_f27, track->parent->parentController.dolby, dVar15_3, track->parentPanCalcTypes[2]);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	800112E0
 * Size:	000104
 */
void Jam_UpdateTempo(seqp_* track)
{
	size_t i;

	size_t* REF_i;

	if (!track->parent) {
		track->tempoFactor = (float)track->timeBase * (float)track->tempo / (JAC_DAC_RATE * 60.0f / 80.0f);
		if ((track->outerParams->flags & OuterParamFlag_Tempo) != 0) {
			track->tempoFactor = track->tempoFactor * track->outerParams->tempo;
		}
	} else {
		track->tempoFactor = track->parent->tempoFactor;
		track->timeBase    = track->parent->timeBase;
	}
	for (i = 0; i < 16; ++i) {
		REF_i = &i;
		if (track->children[i] && track->children[i]->trackState) {
			Jam_UpdateTempo(track->children[i]);
		}
	}
}

/*
 * --INFO--
 * Address:	80011400
 * Size:	0000CC
 */
void Jam_MuteTrack(seqp_* track, u8 param_2)
{
	u32 i;
	u16 mask;

	if (track->parent) {
		track->isMuted = track->parent->isMuted | param_2;
		mask           = 1 << (track->trackId & 0xf);
		if (!param_2) {
			track->parent->childMuteMask &= ~mask;
		} else {
			track->parent->childMuteMask |= mask;
		}
	} else {
		track->isMuted = param_2;
	}
	track->updateFlags |= OuterParamFlag_Volume;
	if (track->isMuted && (track->pauseStatus & 0x20)) {
		for (i = 0; i < 8; ++i) {
			NoteOFF_R(track, (u8)i, 10);
		};
	}
}

/*
 * --INFO--
 * Address:	........
 * Size:	0000B4
 */
void Jam_MuteChildTracks(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	800114E0
 * Size:	00013C
 */
void Jam_PauseTrack(seqp_* track, u8 param_2)
{
	size_t i;
	jc_* pjVar1;

	size_t* REF_i;

	track->isPaused = TRUE;
	if (track->pauseStatus & 0x01) {
		track->updateFlags |= OuterParamFlag_Volume;
	}
	if (track->pauseStatus & 0x04) {
		for (i = 0; i < 8; ++i) {
			REF_i = &i;
			NoteOFF_R(track, i, 10);
		}
	}
	if (track->pauseStatus & 0x08) {
		for (i = 0; i < 8; ++i) {
			pjVar1 = track->channels[i];
			if (pjVar1 && track->activeSoundIds[i] == pjVar1->channelId) {
				UpdatePause_1Shot(pjVar1, 1);
			}
		}
	}
	Jam_SetInterrupt(track, 0);
	if (param_2 == TRUE) {
		for (i = 0; i < 16; ++i) {
			if (track->children[i] && track->children[i]->trackState) {
				Jam_PauseTrack(track->children[i], 1);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	80011620
 * Size:	0000EC
 */
void Jam_UnPauseTrack(seqp_* track, u8 param_2)
{
	size_t i;
	jc_* pjVar1;

	size_t* REF_i;

	track->isPaused = FALSE;
	track->updateFlags |= OuterParamFlag_Volume;
	for (i = 0; i < 8; ++i) {
		REF_i  = &i;
		pjVar1 = track->channels[i];
		if (pjVar1 && track->activeSoundIds[i] == pjVar1->channelId) {
			UpdatePause_1Shot(pjVar1, 0);
		}
	}
	Jam_SetInterrupt(track, 1);
	if (param_2 == TRUE) {
		for (i = 0; i < 16; ++i) {
			if (track->children[i] && track->children[i]->trackState) {
				Jam_UnPauseTrack(track->children[i], 1);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	80011720
 * Size:	000028
 * Note: Equivalent to `JASIntrMgr::request` in later JAudio.
 */
void Jam_SetInterrupt(seqp_* track, u16 interrupt)
{
	if (track->interruptEnable & (1 << interrupt)) {
		track->interruptPending |= (1 << interrupt);
	}
}

/*
 * --INFO--
 * Address:	80011760
 * Size:	000090
 */
BOOL Jam_TryInterrupt(seqp_* track)
{
	u32 mask;
	int i;

	if (track->interruptActive) {
		return FALSE;
	}
	for (i = 0; i < 8; ++i) {
		mask = 1 << i;
		if ((track->interruptEnable & mask) && (track->interruptPending & mask)) {
			track->savedProgramCounter = track->programCounter;
			track->programCounter      = track->interruptAddresses[i];
			track->interruptActive     = mask;
			track->_3CC                = track->waitTimer;
			track->waitTimer           = 0;
			track->interruptPending ^= mask;
			return TRUE;
		}
	}
	return FALSE;
}

/*
 * --INFO--
 * Address:	80011800
 * Size:	000038
 */
static u32 Cmd_OpenTrack()
{
	Jaq_OpenTrack(SEQ_P, SEQ_ARG[0], SEQ_ARG[1]);
	return 0;
}

/*
 * --INFO--
 * Address:	80011840
 * Size:	000050
 */
static u32 Cmd_OpenTrackBros()
{
	if (SEQ_P->parent) {
		Jaq_OpenTrack(SEQ_P->parent, SEQ_ARG[0], SEQ_ARG[1]);
	} else {
		return 0x40;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	800118A0
 * Size:	00003C
 */
static u32 Cmd_Call()
{
	SEQ_P->callStack[SEQ_P->callStackDepth++] = SEQ_P->programCounter;
	SEQ_P->programCounter                     = SEQ_ARG[0];
	return 0;
}

/*
 * --INFO--
 * Address:	800118E0
 * Size:	000100
 */
static u32 Cmd_CallF()
{
	u8 bVar1;
	u32 uVar2;
	u32 uVar3;
	u8 uVar4;

	bVar1 = __ByteRead(SEQ_P);
	if (bVar1 & 0x80) {
		uVar4 = __ByteRead(SEQ_P);
		uVar2 = Jam_ReadRegDirect(SEQ_P, uVar4);
		if (bVar1 & 0x40) {
			if (bVar1 & 0x20) {
				uVar4 = __ByteRead(SEQ_P);
				uVar3 = Jam_ReadRegDirect(SEQ_P, uVar4);
			} else {
				uVar3 = __24Read(SEQ_P);
			}
			uVar2 = __24ReadOfs(SEQ_P, uVar3 + uVar2 * 3);
		}
	} else {
		uVar2 = __24Read(SEQ_P);
	}
	if ((u8)__ConditionCheck(SEQ_P, bVar1 & 0x0f) == TRUE) {
		if (SEQ_CMD == (0xC0 + CMD_CALL_F)) {
			SEQ_P->callStack[SEQ_P->callStackDepth++] = SEQ_P->programCounter;
		}
		SEQ_P->programCounter = uVar2;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	800119E0
 * Size:	000028
 */
static u32 Cmd_Ret()
{
	SEQ_P->programCounter = SEQ_P->callStack[--SEQ_P->callStackDepth];
	return 0;
}

/*
 * --INFO--
 * Address:	80011A20
 * Size:	000060
 */
static u32 Cmd_RetF()
{
	// But why cast it...?  And why check if it explicitly equals TRUE...?
	if ((u8)__ConditionCheck(SEQ_P, SEQ_ARG[0] & 0x0f) == TRUE) {
		SEQ_P->programCounter = SEQ_P->callStack[--SEQ_P->callStackDepth];
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80011A80
 * Size:	00001C
 */
static u32 Cmd_Jmp()
{
	SEQ_P->programCounter = SEQ_ARG[1];
	return 0;
}

/*
 * --INFO--
 * Address:	80011AA0
 * Size:	000020
 */
static u32 Cmd_JmpF()
{
	Cmd_CallF();
}

/*
 * --INFO--
 * Address:	80011AC0
 * Size:	000048
 */
static u32 Cmd_LoopS()
{
	SEQ_P->callStack[SEQ_P->callStackDepth]      = SEQ_P->programCounter;
	SEQ_P->loopCounters[SEQ_P->callStackDepth++] = SEQ_ARG[0];
	return 0;
}

/*
 * --INFO--
 * Address:	80011B20
 * Size:	000078
 */
static u32 Cmd_LoopE()
{
	u16 uVar1;

	if (SEQ_P->callStackDepth == 0) {
		return 0x80;
	}

	uVar1 = SEQ_P->loopCounters[SEQ_P->callStackDepth - 1];
	if (uVar1 != 0) {
		uVar1 = (u16)(uVar1 - 1);
	}
    
	if (uVar1 == 0) {
		SEQ_P->callStackDepth -= 1;
		return 0;
	}

	SEQ_P->loopCounters[SEQ_P->callStackDepth - 1] = uVar1;
	SEQ_P->programCounter                          = SEQ_P->callStack[SEQ_P->callStackDepth - 1];
	return 0;
}

/*
 * --INFO--
 * Address:	80011BA0
 * Size:	000054
 */
static u32 Cmd_ReadPort()
{
	u16 temp;

	temp                                    = SEQ_P->trackPort[SEQ_ARG[0]].value;
	SEQ_P->trackPort[SEQ_ARG[0]].importFlag = 0;
	Jam_WriteRegDirect(SEQ_P, SEQ_ARG[1], temp);
	return 0;
}

/*
 * --INFO--
 * Address:	80011C00
 * Size:	000040
 */
static u32 Cmd_WritePort()
{
	SEQ_P->trackPort[SEQ_ARG[0]].value      = SEQ_ARG[1];
	SEQ_P->trackPort[SEQ_ARG[0]].exportFlag = 1;
	return 0;
}

/*
 * --INFO--
 * Address:	80011C40
 * Size:	000044
 */
static u32 Cmd_CheckPortImport()
{
	Jam_WriteRegDirect(SEQ_P, 3, SEQ_P->trackPort[SEQ_ARG[0]].importFlag);
	return 0;
}

/*
 * --INFO--
 * Address:	80011CA0
 * Size:	000044
 */
static u32 Cmd_CheckPortExport()
{
	Jam_WriteRegDirect(SEQ_P, 3, SEQ_P->trackPort[SEQ_ARG[0]].exportFlag);
	return 0;
}

/*
 * --INFO--
 * Address:	80011D00
 * Size:	00002C
 */
static u32 Cmd_WaitReg()
{
	SEQ_P->waitTimer = SEQ_ARG[0];
	return SEQ_ARG[0] ? 1 : 0;
}

/*
 * --INFO--
 * Address:	80011D40
 * Size:	000028
 */
static u32 Cmd_ConnectName()
{
	SEQ_P->connectionId = SEQ_ARG[0] << 16 | SEQ_ARG[1];
	return 0;
}

/*
 * --INFO--
 * Address:	80011D80
 * Size:	000040
 */
static u32 Cmd_ParentWritePort()
{
	Jam_WritePortAppDirect(SEQ_P->parent, SEQ_ARG[0] & 0x0f, SEQ_ARG[1]);
	return 0;
}

/*
 * --INFO--
 * Address:	80011DC0
 * Size:	000048
 */
static u32 Cmd_ChildWritePort()
{
	Jam_WritePortAppDirect(SEQ_P->children[(SEQ_ARG[0] >> 4)], SEQ_ARG[0] & 0x0f, SEQ_ARG[1]);
	return 0;
}

/*
 * --INFO--
 * Address:	80011E20
 * Size:	000030
 */
static u32 Cmd_SetLastNote()
{
	SEQ_P->_D5 = SEQ_ARG[0];
	SEQ_P->_D5 += SEQ_P->finalTranspose;
	return 0;
}

/*
 * --INFO--
 * Address:	80011E60
 * Size:	00001C
 */
static u32 Cmd_TimeRelate()
{
	SEQ_P->timeRelationMode = SEQ_ARG[0];
	return 0;
}

/*
 * --INFO--
 * Address:	80011E80
 * Size:	000034
 */
static u32 Cmd_SimpleOsc()
{
	Osc_Setup_Simple(SEQ_P, SEQ_ARG[0]);
	return 0;
}

/*
 * --INFO--
 * Address:	80011EC0
 * Size:	000038
 */
static u32 Cmd_SimpleEnv()
{
	Osc_Setup_SimpleEnv(SEQ_P, SEQ_ARG[0], SEQ_ARG[1]);
	return 0;
}

/*
 * --INFO--
 * Address:	80011F00
 * Size:	000064
 */
static u32 Cmd_SimpleADSR()
{
	int i;
	s16 local_10[5];

	for (i = 0; i < 5; ++i) {
		local_10[i] = SEQ_ARG[i];
	}
	Osc_Setup_ADSR(SEQ_P, local_10);
	return 0;
}

/*
 * --INFO--
 * Address:	80011F80
 * Size:	000048
 */
static u32 Cmd_Transpose()
{
	SEQ_P->transpose = SEQ_ARG[0];
	if (SEQ_P->parent) {
		SEQ_P->finalTranspose = SEQ_P->parent->transpose + SEQ_P->transpose;
	} else {
		SEQ_P->finalTranspose = SEQ_P->transpose;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80011FE0
 * Size:	000068
 */
static u32 Cmd_CloseTrack()
{
	u8 index = SEQ_ARG[0];
	if (index >= (u32)ARRAY_COUNT(SEQ_P->children)) {
		return 0x80;
	}
	Jaq_CloseTrack(SEQ_P->children[index]);
	SEQ_P->children[index] = NULL;
	return 0;
}

/*
 * --INFO--
 * Address:	80012060
 * Size:	000038
 */
static u32 Cmd_OutSwitch()
{
	if (SEQ_P->outerParams) {
		SEQ_P->outerParams->flags       = SEQ_ARG[0];
		SEQ_P->outerParams->updateFlags = -1;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	800120A0
 * Size:	000034
 */
static u32 Cmd_UpdateSync()
{
	Jam_UpdateTrack(SEQ_P, SEQ_ARG[0]);
	return 0;
}

/*
 * --INFO--
 * Address:	800120E0
 * Size:	00002C
 */
static u32 Cmd_BusConnect()
{
	if (SEQ_ARG[0] < 6) {
		SEQ_P->parentController.busConnect[SEQ_ARG[0]] = SEQ_ARG[1];
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80012120
 * Size:	00001C
 */
static u32 Cmd_PauseStatus()
{
	SEQ_P->pauseStatus = SEQ_ARG[0];
	return 0;
}

/*
 * --INFO--
 * Address:	80012140
 * Size:	000044
 */
static u32 Cmd_SetInterrupt()
{
	SEQ_P->interruptEnable |= (1 << SEQ_ARG[0]);
	SEQ_P->interruptAddresses[SEQ_ARG[0]] = SEQ_ARG[1];
	return 0;
}

/*
 * --INFO--
 * Address:	800121A0
 * Size:	000030
 */
static u32 Cmd_DisInterrupt()
{
	u8 arg;
	arg = SEQ_ARG[0];
	arg = 1 << arg;
    arg = ~arg;
	SEQ_P->interruptEnable &= arg;
	return 0;
}

/*
 * --INFO--
 * Address:	800121E0
 * Size:	000014
 */
static u32 Cmd_ClrI()
{
	SEQ_P->interruptActive = 0;
	return 0;
}

/*
 * --INFO--
 * Address:	80012200
 * Size:	000014
 */
static u32 Cmd_SetI()
{
	SEQ_P->interruptActive = 1;
	return 0;
}

/*
 * --INFO--
 * Address:	80012220
 * Size:	00002C
 */
static u32 Cmd_RetI()
{
	SEQ_P->waitTimer       = SEQ_P->_3CC;
	SEQ_P->interruptActive = 0;
	SEQ_P->programCounter  = SEQ_P->savedProgramCounter;
	return 2;
}

/*
 * --INFO--
 * Address:	80012260
 * Size:	000034
 */
static u32 Cmd_IntTimer()
{
	SEQ_P->timerCount = SEQ_ARG[0];
	SEQ_P->timer      = SEQ_ARG[1];
	SEQ_P->maxTime    = SEQ_ARG[1];
	return 0;
}

/*
 * --INFO--
 * Address:	800122A0
 * Size:	00002C
 */
static u32 Cmd_ConnectOpen()
{
	Jam_RegistTrack(SEQ_P, SEQ_P->connectionId);
	return 0;
}

/*
 * --INFO--
 * Address:	800122E0
 * Size:	000028
 */
static u32 Cmd_ConnectClose()
{
	Jam_UnRegistTrack(SEQ_P);
	return 0;
}

/*
 * --INFO--
 * Address:	80012320
 * Size:	000060
 */
static u32 Cmd_SyncCPU()
{
	u16 seq_arg;
	u16 param_3;

	seq_arg = SEQ_ARG[0];
	if (JAM_CALLBACK_FUNC) {
		param_3 = JAM_CALLBACK_FUNC(SEQ_P, seq_arg);
	} else {
		param_3 = 0xffff;
	}
	Jam_WriteRegDirect(SEQ_P, 3, param_3);
	return 0;
}

/*
 * --INFO--
 * Address:	80012380
 * Size:	000038
 */
static u32 Cmd_FlushAll()
{
	AllStop_1Shot(&SEQ_P->parentController);
	FlushRelease_1Shot(&SEQ_P->parentController);
	return 0;
}

/*
 * --INFO--
 * Address:	800123C0
 * Size:	00002C
 */
static u32 Cmd_FlushRelease()
{
	FlushRelease_1Shot(&SEQ_P->parentController);
	return 0;
}

/*
 * --INFO--
 * Address:	80012400
 * Size:	00002C
 */
static u32 Cmd_Wait3()
{
	SEQ_P->waitTimer = SEQ_ARG[0];
	return SEQ_ARG[0] ? 1 : 0;
}

/*
 * --INFO--
 * Address:	80012440
 * Size:	000044
 */
static u32 Cmd_TimeBase()
{
	SEQ_P->timeBase = SEQ_ARG[0];
	if (!SEQ_P->parent) {
		Jam_UpdateTempo(SEQ_P);
	}
	return 0;
}

/*
 * --INFO--
 * Address:	800124A0
 * Size:	000050
 */
static u32 Cmd_Tempo()
{
	SEQ_P->tempo = SEQ_ARG[0];
	if (!SEQ_P->parent) {
		Jam_UpdateTempo(SEQ_P);
	} else {
		SEQ_P->doChangeTempo = TRUE;
	}
	return 0;
}

/*
 * --INFO--
 * Address:	80012500
 * Size:	0000CC
 */
static u32 Cmd_Finish()
{
	size_t i;
	u32 updateFlags;
	MoveParam_* temp;

	updateFlags = 0;
	for (i = 0; i < 18; ++i) {
		temp = &SEQ_P->timedParam.move[i];
		if (temp->duration > 0.0f) {
			temp->currentValue += temp->stepSize;
			temp->duration -= 1.0f;
			if (i <= 5 || i >= 11) {
				updateFlags |= 1 << i;
			} else {
				Osc_Update_Param(SEQ_P, i, temp->currentValue);
			}
		}
	}
	SeqUpdate(SEQ_P, updateFlags);

	return 3;
}

/*
 * --INFO--
 * Address:	800125E0
 * Size:	000008
 */
static u32 Cmd_Nop()
{
	return 0;
}

/*
 * --INFO--
 * Address:	80012600
 * Size:	0000AC
 */
static u32 Cmd_PanPowSet()
{
	size_t i;

	for (i = 0; i < 3; ++i) {
		SEQ_P->regParam.param.arguments[i] = SEQ_ARG[i];
	}
	for (i = 3; i < 5; ++i) {
		SEQ_P->regParam.param.arguments[i] = SEQ_ARG[i] * 327.67f;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	800126C0
 * Size:	000094
 */
static u32 Cmd_IIRSet()
{

	size_t i;
	MoveParam_* iir;

	for (i = 0; i < 4; ++i) {
		iir               = &SEQ_P->timedParam.move[i + 12]; // IIRs 0 - 4 are at 12-15
		iir->targetValue  = (s16)SEQ_ARG[i] / 32768.0f;
		iir->currentValue = iir->targetValue;
		iir->stepSize     = 0.0f;
		iir->duration     = 1.0f;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	80012760
 * Size:	000044
 */
static u32 Cmd_FIRSet()
{
	Jam_SetExtFirFilterD(SEQ_P->outerParams, (s16*)Jam_OfsToAddr(SEQ_P, SEQ_ARG[0]));
	return 0;
}

/*
 * --INFO--
 * Address:	800127C0
 * Size:	000050
 */
static u32 Cmd_EXTSet()
{
	OuterParam_* ext;

	ext = (OuterParam_*)Jam_OfsToAddr(SEQ_P, SEQ_ARG[0]);
	Jam_InitExtBuffer(ext);
	Jam_AssignExtBuffer(SEQ_P, ext);
	return 0;
}

/*
 * --INFO--
 * Address:	80012820
 * Size:	0000C4
 */
static u32 Cmd_PanSwSet()
{
	size_t i;

	// Ah yes, let's just construct this on the stack real quick.
	u8 calcTypes[]       = { 0, 0, 0, 1, 1, 2, 2 };
	u8 parentCalcTypes[] = { 0, 1, 2, 0, 2, 0, 2 };

	for (i = 0; i < 3; ++i) {
		SEQ_P->panCalcTypes[i]                  = calcTypes[SEQ_ARG[i] >> 5];
		SEQ_P->parentPanCalcTypes[i]            = parentCalcTypes[SEQ_ARG[i] >> 5];
		SEQ_P->parentController.panCalcTypes[i] = SEQ_ARG[i] & 0x1f;
		SEQ_P->updateFlags |= OuterParamFlag_Pan;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	80012900
 * Size:	000040
 */
static u32 Cmd_OscRoute()
{
	u8 uVar2;
	u8 oscRoute;

	uVar2    = SEQ_ARG[0] >> 4 & 0xf;
	oscRoute = SEQ_ARG[0] & 0xf;

	SEQ_P->oscillatorRouting[uVar2] = oscRoute;
	if (oscRoute == 14) {
		SEQ_P->oscillatorParams[uVar2].state = 1;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	80012940
 * Size:	0000A0
 */
static u32 Cmd_IIRCutOff()
{
	u8 index;
	size_t i;
	MoveParam_* iir;

	index = SEQ_ARG[0];
	for (i = 0; i < 4; ++i) {
		iir               = &SEQ_P->timedParam.move[i + 12]; // IIRs 0 - 4 are at 12-15
		iir->targetValue  = CUTOFF_TO_IIR_TABLE[index][i] / 32767.0f;
		iir->currentValue = iir->targetValue;
		iir->stepSize     = 0.0f;
		iir->duration     = 1.0f;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	800129E0
 * Size:	000040
 */
static u32 Cmd_OscFull()
{
	Osc_Setup_Full(SEQ_P, SEQ_ARG[0], SEQ_ARG[1], SEQ_ARG[2]);
	return 0;
}

/*
 * --INFO--
 * Address:	80012A20
 * Size:	000068
 */
static u32 Cmd_CheckWave()
{
	SOUNDID_ soundID;
	u32 uVar2;

	soundID.value = SEQ_ARG[0] | (Jam_ReadRegDirect(SEQ_P, 6) << 16);
	uVar2         = One_CheckInstWave(soundID);
	Jam_WriteRegDirect(SEQ_P, 3, (u8)uVar2);
	return 0;
}

/*
 * --INFO--
 * Address:	80012AA0
 * Size:	000204
 */
static u32 Cmd_Printf()
{
	char fmtStr[0x80];
	u8 fmtFlags[4];
	u32 fmtParms[4];
	size_t fmtCount;
	size_t i;

	fmtCount = 0;
	for (i = 0; i < (u32)ARRAY_COUNT(fmtStr); ++i) {
		fmtStr[i] = __ByteRead(SEQ_P);
		if (fmtStr[i] == '\0') {
			// Handle end of string
			break;
		}
		if (fmtStr[i] == '\\') {
			// Handle escape sequences (just the one)
			fmtStr[i] = __ByteRead(SEQ_P);

			if (fmtStr[i] == '\0') {
				// Unexpected end of string!
				break;
			}
			switch (fmtStr[i]) {
			case 'n':
				// Convert newlines to... carriage returns?
				fmtStr[i] = '\r';
				break;
			}
			continue;
		}
		if (fmtStr[i] == '%') {
			// Handle conversion specifiers (plus a few custom ones!)
			++i;
			fmtStr[i] = __ByteRead(SEQ_P);

			if (fmtStr[i] == '\0') {
				// Unexpected end of string!
				break;
			}
			switch (fmtStr[i]) {
			case 'd': // Decimal
				fmtFlags[fmtCount] = 0;
				break;
			case 'x': // Hexadecimal
				fmtFlags[fmtCount] = 1;
				break;
			case 's': // String
				fmtFlags[fmtCount] = 2;
				break;
			case 'r': // ?
				fmtFlags[fmtCount] = 3;
				fmtStr[i]          = 'd';
				break;
            case 'R':
				fmtFlags[fmtCount] = 4;
				fmtStr[i]          = 'x';
				break;
			}
			++fmtCount;
			continue;
		}
	}
	for (i = 0; i < fmtCount; ++i) {
		fmtParms[i] = __ByteRead(SEQ_P);
		if (fmtFlags[i] == 2) {
			fmtParms[i] = (uintptr_t)Jam_OfsToAddr(SEQ_P, fmtParms[i]);
		// } else if (fmtFlags[i] == 5) {
		// 	fmtParms[i] = SEQ_P->trackId;
		}
        
        if (fmtFlags[i] >= 3) {
			fmtParms[i] = __ExchangeRegisterValue(SEQ_P, fmtParms[i]);
		}
	}
	// A restoration of this command's functionality can be enabled below:
	OSReport(fmtStr, fmtParms[0], fmtParms[1], fmtParms[2], fmtParms[3]);
	return 0;
}

static Arghead_ Arglist[CMD_COUNT] = {
	{ 0, 0x0000 }, //
	{ 2, 0x0008 }, // OpenTrack
	{ 2, 0x0008 }, // OpenTrackBros
	{ 1, 0x0002 }, // Call
	{ 0, 0x0000 }, // CallF
	{ 0, 0x0000 }, // Ret
	{ 1, 0x0000 }, // RetF
	{ 1, 0x0002 }, // Jmp
	{ 0, 0x0000 }, // JmpF
	{ 1, 0x0001 }, // LoopS
	{ 0, 0x0000 }, // LoopE
	{ 2, 0x0000 }, // ReadPort
	{ 2, 0x000c }, // WritePort
	{ 1, 0x0000 }, // CheckPortImport
	{ 1, 0x0000 }, // CheckPortExport
	{ 1, 0x0003 }, // WaitReg
	{ 2, 0x0005 }, // ConnectName
	{ 2, 0x000c }, // ParentWritePort
	{ 2, 0x000c }, // ChildWritePort
	{ 2, 0x000f }, //
	{ 1, 0x0000 }, // SetLastNote
	{ 1, 0x0000 }, // TimeRelate
	{ 1, 0x0000 }, // SimpleOsc
	{ 2, 0x0008 }, // SimpleEnv
	{ 5, 0x0155 }, // SimpleADSR
	{ 1, 0x0000 }, // Transpose
	{ 1, 0x0000 }, // CloseTrack
	{ 1, 0x0000 }, // OutSwitch
	{ 1, 0x0001 }, // UpdateSync
	{ 2, 0x0004 }, // BusConnect
	{ 1, 0x0000 }, // PauseStatus
	{ 2, 0x0008 }, // SetInterrupt
	{ 1, 0x0000 }, // DisInterrupt
	{ 0, 0x0000 }, // ClrI
	{ 0, 0x0000 }, // SetI
	{ 0, 0x0000 }, // RetI
	{ 2, 0x0004 }, // IntTimer
	{ 0, 0x0000 }, // ConnectOpen
	{ 0, 0x0000 }, // ConnectClose
	{ 1, 0x0001 }, // SyncCPU
	{ 0, 0x0000 }, // FlushAll
	{ 0, 0x0000 }, // FlushRelease
	{ 1, 0x0002 }, // Wait3
	{ 5, 0x0000 }, // PanPowSet
	{ 4, 0x0055 }, // IIRSet
	{ 1, 0x0002 }, // FIRSet
	{ 1, 0x0002 }, // EXTSet
	{ 3, 0x0000 }, // PanSwSet
	{ 1, 0x0000 }, // OscRoute
	{ 1, 0x0000 }, // IIRCutOff
	{ 3, 0x0028 }, // OscFull
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 0, 0x0000 }, //
	{ 1, 0x0001 }, // CheckWave
	{ 0, 0x0000 }, // Printf
	{ 0, 0x0000 }, // Nop
	{ 1, 0x0001 }, // Tempo
	{ 1, 0x0001 }, // TimeBase
	{ 0, 0x0000 }, // Finish

};

static CmdFunction CMDP_LIST[CMD_COUNT] = {
	NULL,
	Cmd_OpenTrack,
	Cmd_OpenTrackBros,
	Cmd_Call,
	Cmd_CallF,
	Cmd_Ret,
	Cmd_RetF,
	Cmd_Jmp,
	Cmd_JmpF,
	Cmd_LoopS,
	Cmd_LoopE,
	Cmd_ReadPort,
	Cmd_WritePort,
	Cmd_CheckPortImport,
	Cmd_CheckPortExport,
	Cmd_WaitReg,
	Cmd_ConnectName,
	Cmd_ParentWritePort,
	Cmd_ChildWritePort,
	NULL,
	Cmd_SetLastNote,
	Cmd_TimeRelate,
	Cmd_SimpleOsc,
	Cmd_SimpleEnv,
	Cmd_SimpleADSR,
	Cmd_Transpose,
	Cmd_CloseTrack,
	Cmd_OutSwitch,
	Cmd_UpdateSync,
	Cmd_BusConnect,
	Cmd_PauseStatus,
	Cmd_SetInterrupt,
	Cmd_DisInterrupt,
	Cmd_ClrI,
	Cmd_SetI,
	Cmd_RetI,
	Cmd_IntTimer,
	Cmd_ConnectOpen,
	Cmd_ConnectClose,
	Cmd_SyncCPU,
	Cmd_FlushAll,
	Cmd_FlushRelease,
	Cmd_Wait3,
	Cmd_PanPowSet,
	Cmd_IIRSet,
	Cmd_FIRSet,
	Cmd_EXTSet,
	Cmd_PanSwSet,
	Cmd_OscRoute,
	Cmd_IIRCutOff,
	Cmd_OscFull,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	Cmd_CheckWave,
	Cmd_Printf,
	Cmd_Nop,
	Cmd_Tempo,
	Cmd_TimeBase,
	Cmd_Finish,
};

/*
 * --INFO--
 * Address:	80012CC0
 * Size:	000130
 */
u32 Cmd_Process(seqp_* track, u8 cmd, u16 param_3)
{
	Arghead_ argpair;
	u16 argTypes;
	size_t i;
	u32 arg;
	CmdFunction function;
	seqp_** REF_track;
	u8* REF_cmd;

	REF_track = &track;
	REF_cmd   = &cmd;

	argpair  = Arglist[cmd - 0xC0];
	argTypes = argpair.argTypes | param_3;
	for (i = 0; i < argpair.argCount; ++i) {
		switch (argTypes & 0x03) {
		case 0: // 8-bit immediate value
			arg = __ByteRead(track);
			break;
		case 1: // 16-bit immediate value
			arg = __WordRead(track);
			break;
		case 2: // 24-bit immediate value
			arg = __24Read(track);
			break;
		case 3: // Register value
			arg = __ExchangeRegisterValue(track, __ByteRead(track));
			break;
		}

		argTypes   = argTypes >> 2;
		SEQ_ARG[i] = arg;
	}

	// Me when I have to introduce global state because I'm bored.
	SEQ_CMD = cmd;
	SEQ_P   = track;

	function = CMDP_LIST[cmd - 0xC0];
	if (!function) {
        OSReport("Error: NULL Command Pointer (cmd. %x ) \n", cmd);
        OSReport("SEQP %x  Access Offset %d\n", track, track->programCounter);
		return 0;
	}
	return function();
}

/*
 * --INFO--
 * Address:	80012E00
 * Size:	0000A8
 */
u32 RegCmd_Process(seqp_* track, BOOL param_2, u32 param_3)
{
	size_t i;
	u8 uVar4;
	u8 uVar3;
	u16 uVar5;
	u16 uVar6; // Uninitialized!  Naughty!

	uVar4 = __ByteRead(track);
	if (param_2 == TRUE) {
		uVar4 = __ExchangeRegisterValue(track, uVar4);
	}
	if (param_2 != TRUE || param_3 != 0) {
		uVar3 = __ByteRead(track);
		uVar5 = 0b11;
		for (i = 0; i < param_3 + 1; ++i) {
			if (uVar3 & 0b10000000) {
				uVar6 |= uVar5;
			}
			uVar3 = uVar3 << 1;
			uVar5 = uVar5 << 2;
		}
	}
	return Cmd_Process(track, uVar4, uVar6);
}

// TODO: These five values appear all over this file. They mean something.
static u8 osc_table[] = { 0x01, 0x02, 0x08, 0x04, 0x10 };

/*
 * --INFO--
 * Address:	80012EC0
 * Size:	0008C0
 * Note: (Roughly) Equivalent to `JASTrack::mainProc` in later JAudio.
 */
s32 Jam_SeqmainNote(seqp_* track, u8 isMuted)
{
	BOOL var_r26;
	u8 bVar9;
	u8 velocity;
	u32 uVar2;
	s32 uVar5;
	u8 bVar10_2;
	f32 tempoProportion;
	u8 opcode;
	u8 uVar6;
	u8 keyTarget;
	u8 pitch;
	u8 bVar10;
	int local_64;
	int iVar11;
	int iVar11_2;
	int iVar12;
	u32 seqRes;
	int duration;
	jc_* pjVar3;
	int iVar11_3;
	u8 voice;

	seqRes = 0;
	if (track->parent && track->doChangeTempo == TRUE) {
		tempoProportion = (float)track->tempo / (float)track->parent->tempo;
		if (tempoProportion > 1.0f) {
			tempoProportion = 1.0f;
		}
		track->tempoAccumulator += tempoProportion;
		if (track->tempoAccumulator < 1.0f) {
			return 0;
		}
		track->tempoAccumulator -= 1.0f;
	}

	{ // This whole part is not present(?) in later JAudio.
		if (track->parent) {
			track->isMuted = isMuted;
		}
		if (track->parent && track->parentController.chanCount != 0) {
			pjVar3 = List_GetChannel(&track->parentController.freeChannels);
			if (pjVar3) {
				List_AddChannel(&track->parent->parentController.freeChannels, pjVar3);
				pjVar3->mMgr = &track->parent->parentController;
				track->parentController.chanCount--;
				track->parent->parentController.chanCount++;
			}
		}
		// This resembles `JASTrack::getTranspose` of later JAudio.
		if (track->parent) {
			track->finalTranspose = track->transpose + track->parent->finalTranspose;
		} else {
			track->finalTranspose = track->transpose;
		}
	}

	Jam_SetInterrupt(track, 7);
	{ // This resembles `JASIntrMgr::timerProcess` of later JAudio.
		if (track->timer != 0) {
			if (--track->timer == 0) {
				Jam_SetInterrupt(track, 6);
				if (track->timerCount != 0) {
					if (--track->timerCount != 0) {
						track->timer = track->maxTime;
					}
				} else {
					track->timer = track->maxTime;
				}
			}
		}
	}

try_interrupt:
	Jam_TryInterrupt(track);
	if (track->isPaused && (track->pauseStatus & 2)) {
		goto LAB_800136e0;
	}
	track->tickCounter++;
	if (track->waitTimer == -1) {
		if ((u8)CheckNoteStop(track, 0)) { // TODO: CheckNoteStop should return u8 or C++ bool
			track->waitTimer = 0;
		} else {
			goto timed;
		}
	}

	if (track->waitTimer > 0) {
		--track->waitTimer;
		if (track->waitTimer != 0) {
			goto timed;
		}
		if (track->_D0 != -1 && track->_D4 == 0) {
			for (local_64 = 0; local_64 < (int)track->_90; local_64++) {
				track->_94[local_64]      = -1;
				track->channels[local_64] = NULL;
			}
		}
	}

	while (TRUE) {
		opcode = __ByteRead(track);
		if (!(opcode & 0x80)) {
			// MIDI pitch (0-127)
			pitch = opcode;
			pitch += track->finalTranspose;

			if ((bVar10 = __ByteRead(track)) & 0x80) {
				pitch = __ExchangeRegisterValue(track, pitch);
				pitch += track->finalTranspose;
			}

			if (pitch >= 128) {
                OSReport("♪Jam/Seq :: Error Note %d\n", pitch);
            }

			if (bVar10 >> 5 & 2) {
				keyTarget = pitch;
				pitch     = track->_D5;
			}

			velocity = __ByteRead(track);
			if (velocity >= 0x80) {
				velocity = __ExchangeRegisterValue(track, velocity - 0x80);
			}

			u32 lowBits = bVar10;
			lowBits &= 7;
			if (lowBits == 0) {
				voice = 0;
				bVar9 = __ByteRead(track);
				if (bVar9 >= 0x80) {
					bVar9 = __ExchangeRegisterValue(track, bVar9 - 0x80);
				}
				uVar2 = 0;
				for (iVar11 = 0; iVar11 < (bVar10 >> 3 & 3); iVar11++) {
					uVar2 = uVar2 << 8 | __ByteRead(track);
				}
				if ((bVar10 >> 3 & 3) == 1 && uVar2 >= 0x80) {
					uVar2 = __ExchangeRegisterValue(track, uVar2 - 0x80);
				}
			} else {
				voice = lowBits;
				// fake volatile for matching
				if (*(volatile u8*)&bVar10 >> 3 & 3) {
					voice = __ExchangeRegisterValue(track, voice - 1);
					if (voice >= 8) {
						break;
					}
				}
				uVar2 = -1;
				bVar9 = 100;
			}

			track->_D4 = bVar10 >> 5 & 3;

			BOOL cond = track->_D6 ? TRUE : FALSE;
			var_r26   = FALSE;

			for (int j = 0; j < 1; j++) {
                // u8* track_p = track->_94;
				int unused = j * 2;

				if (cond) {
					duration = uVar2;
					if (track->_D4 & 1) {
						duration = -1;
					}
					if (duration != -1) {
						duration = Jam_SEQtimeToDSPtime(track, duration, bVar9);
					}
					if (track->isPaused && (track->pauseStatus & 0x10)) {
						iVar11_2 = -1;
					} else {
						iVar11_2 = GateON(track, voice, pitch, velocity, duration);
					}
				} else {
					if ((duration = uVar2) != -1) {
						duration = Jam_SEQtimeToDSPtime(track, duration, bVar9);
					}
					if (track->_D4 & 1) {
						duration = -1;
					}
					if (track->isPaused && (track->pauseStatus & 0x10)) {
						iVar11_2 = -1;
					} else {
						iVar11_2 = NoteON(track, voice, (u8)pitch, velocity, duration);
					}
				}

				if (iVar11_2 != -1) {
					track->_94[voice] = pitch;
					var_r26           = TRUE;
				}
				!unused;
			}

			track->_90 = var_r26;
			track->_CC = bVar9;
			track->_CD = velocity;
			track->_D0 = uVar2;

			if (track->_D4 & 1) {
				track->_D6 = TRUE;
			} else {
				track->_D6 = FALSE;
			}

			if (track->_D4 & 2) {
				s32 steps = duration;
				if (duration == -1) {
					steps = Jam_SEQtimeToDSPtime(track, uVar2, track->_CC);
				}
				SetKeyTarget_1Shot(track->channels[0], keyTarget + track->finalTranspose, steps);
				pitch = (u8)keyTarget;
			}

			track->_D5 = pitch;

			if (uVar2 != -1) {
				track->waitTimer = uVar2;
				if (uVar2 == 0) {
					track->waitTimer = -1;
				}
				break;
			}
		} else if ((opcode & 0xf0) == 0x80 || opcode == 0xf9) {
			iVar11_3 = 1;
			uVar5    = 0;
			if (opcode == 0xf9) {
				bVar10_2 = __ByteRead(track);
				uVar6    = __ExchangeRegisterValue(track, bVar10_2 & 7);
				if (uVar6 > 7 || uVar6 == 0) {
                    OSReport("♪Jam/main :: r-noteoff error\n");
					if ((bVar10_2 & 0x80) != 0) {
						__ByteRead(track);
					}
					continue;
				}
				opcode = uVar6 + 0x80;
				if (bVar10_2 & 0x80) {
					opcode += 8;
				}
			}
			uVar6 = opcode & 0x0f;
			if (uVar6 == 8) {
				iVar11_3 = 2;
				uVar6 -= 8;
			}
			if (uVar6 > 8) {
				uVar6 -= 8;
				uVar5 = __ByteRead(track);
				if (uVar5 > 100) {
					uVar5 = (uVar5 - 98) * 20;
				}
			}
			if (uVar6 == 0) {
				// This for loop init feels fake... but idk.  Check this again later.
				for (track->waitTimer = iVar12 = 0; iVar12 < iVar11_3; iVar12++) {
					track->waitTimer = track->waitTimer << 8 | __ByteRead(track);
				}
				if (track->waitTimer == 0) {
					continue;
				}
				break;
			}
			if (uVar5 == 0) {
				NoteOFF(track, uVar6);
			} else {
				NoteOFF_R(track, uVar6, uVar5);
			}
		} else {
			// This portion is equivalent to `JASSeqParser::parseSeq` in later JAudio.
			u32 cmdResult = 0;
			if ((opcode & 0xf0) == 0x90) {
				Jam_WriteTimeParam(track, opcode & 0x0f);
			} else if ((opcode & 0xf0) == 0xa0) {
				Jam_WriteRegParam(track, opcode & 0x0f);
			} else if ((opcode & 0xf0) == 0xb0) {
				u32 param_3 = opcode & 7;
				cmdResult   = RegCmd_Process(track, (opcode & 8) ? TRUE : FALSE, param_3);
			} else {
				cmdResult = Cmd_Process(track, opcode, 0);
			}

			if (cmdResult == 0) {
				continue;
			} else if (cmdResult == 1) {
				break;
			} else if (cmdResult == 2) {
				goto try_interrupt;
			} else if (cmdResult == 3) {
				return -1;
			} else if (cmdResult == 0x80) {
                OSReport("\x1b[4%dm", cmdResult);
                OSReport("♪Jam/seq :: Sequence Error occerd... I try to continue\n");
                OSReport("\x1b[m");
            }
		}
	}

timed:
	// This portion is equivalent to `JASTrack::updateTimedParam` in later JAudio.
	for (int i = 0; i < 18; i++) {
		MoveParam_* move = &track->timedParam.move[i];
		if (move->duration > 0.0f) {
			move->currentValue += move->stepSize;
			move->duration -= 1.0f;
			if (i <= 5 || i >= 11) {
				seqRes |= (1 << i);
			} else {
				Osc_Update_Param(track, i, move->currentValue);
			}
		}
	}

	if (track->oscillatorRouting[0] == 0x0E) {
		seqRes |= osc_table[track->oscillators[0].mode];
	}
	if (track->oscillatorRouting[1] == 0x0E) {
		seqRes |= osc_table[track->oscillators[1].mode];
	}

LAB_800136e0:
	track->updateFlags |= seqRes;

	for (int i = 0; i < 16; i++) {
		if (track->children[i] && track->children[i]->trackState != 0) {
            if (track != track->children[i]->parent) {
                OSReport("##########Error:: Track %d の共有違反です\n", i);
            }
			// Return of the worst bit extract extraction method known to man.
			BOOL childIsMuted = track->isMuted | ((track->childMuteMask & (1 << i)) >> i);
			if (Jam_SeqmainNote(track->children[i], childIsMuted) == -1) {
				Jaq_CloseTrack(track->children[i]);
				track->children[i] = NULL;
			}
		}
	}

	return 0;
}

/*
 * --INFO--
 * Address:	80013780
 * Size:	0000A8
 */
void SeqUpdate(seqp_* track, u32 updateFlags)
{
	u32 finalFlags;
	size_t i;

	finalFlags = updateFlags | track->updateFlags;
	if (track->outerParams) {
		finalFlags |= track->outerParams->updateFlags;
		track->outerParams->updateFlags = 0;
	}

	track->updateFlags = OuterParamFlag_None;
	if (finalFlags) {
		Jam_UpdateTrack(track, finalFlags);
	}

	for (i = 0; i < 16; ++i) {
		if (track->children[i] && track->children[i]->trackState) {
			SeqUpdate(track->children[i], finalFlags);
		}
	}
}
