#include "jaudio_NES/seqsetup.h"

#include "jaudio_NES/jammain_2.h"
#include "jaudio_NES/noteon.h"
#include "jaudio_NES/fat.h"
#include "jaudio_NES/playercall.h"
#include "jaudio_NES/jamosc.h"
#include "jaudio_NES/driverinterface.h"
#include "jaudio_NES/oneshot.h"
#include "jaudio_NES/fat.h"

#include "dolphin/os/OSInterrupt.h"

#define SEQ_SIZE             (256)
#define ROOT_OUTER_SIZE      (16)
#define ROOTSEQ_SIZE         (16)
#define FREE_SEQP_QUEUE_SIZE (256)

static seqp_ seq[SEQ_SIZE];
static OuterParam_ ROOT_OUTER[ROOT_OUTER_SIZE];
static seqp_* rootseq[ROOTSEQ_SIZE];
static seqp_* FREE_SEQP_QUEUE[FREE_SEQP_QUEUE_SIZE];

static u32 BACK_P;
static u32 GET_P;
static u32 SEQ_REMAIN;

/*
 * --INFO--
 * Address:	80013DA0
 * Size:	0000A0
 */
void Jaq_Reset(void)
{
	int i;

	for (i = 0; i < SEQ_SIZE; ++i) {
		seq[i].trackState    = 0;
		seq[i].childMuteMask = 0;
		seq[i].isMuted       = 0;
		FREE_SEQP_QUEUE[i]   = &seq[i];
	}

	BACK_P     = 0;
	GET_P      = 0;
	SEQ_REMAIN = FREE_SEQP_QUEUE_SIZE;

	for (i = 0; i < ROOTSEQ_SIZE; ++i) {
		rootseq[i] = NULL;
	}

	Jam_InitRegistTrack();
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void Jaq_GetRemainFreeTracks(void)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	80013E40
 * Size:	000088
 */
static BOOL BackTrack(seqp_* track)
{
	seqp_** REF_track;

	REF_track         = &track;
	track->trackState = 0;
	if (track->_3E4 == 1) {
		if (SEQ_REMAIN == FREE_SEQP_QUEUE_SIZE) {
			return FALSE;
		}

		FREE_SEQP_QUEUE[BACK_P] = track;
		++SEQ_REMAIN;
		++BACK_P;

		if (BACK_P == FREE_SEQP_QUEUE_SIZE) {
			BACK_P = 0;
		}
		return TRUE;
	}
	return FALSE;
}

/*
 * --INFO--
 * Address:	80013EE0
 * Size:	000064
 */
static seqp_* GetNewTrack()
{
	seqp_* track;

	if (SEQ_REMAIN == 0) {
		return NULL;
	}

	track = FREE_SEQP_QUEUE[GET_P];
	--SEQ_REMAIN;
	++GET_P;

	if (GET_P == FREE_SEQP_QUEUE_SIZE) {
		GET_P = 0;
	}

	track->trackState = 2;
	track->_3E4       = 1;
	return track;
}

/*
 * --INFO--
 * Address:	80013F60
 * Size:	000048
 */
int AllocNewRoot(seqp_* track)
{
	int i;

	for (i = 0; i < ROOTSEQ_SIZE; ++i) {
		if (!rootseq[i]) {
			rootseq[i] = track;
			return i;
		}
	}
	return -1;
}

/*
 * --INFO--
 * Address:	80013FC0
 * Size:	00004C
 */
int DeAllocRoot(seqp_* track)
{
	int i;

	for (i = 0; i < ROOTSEQ_SIZE; ++i) {
		if (rootseq[i] == track) {
			rootseq[i] = NULL;
			return i;
		}
	}
	return -1;
}

/*
 * --INFO--
 * Address:	80014020
 * Size:	000018
 */
seqp_* Jaq_HandleToSeq(u32 handle)
{
	return rootseq[handle];
}

/*
 * --INFO--
 * Address:	80014040
 * Size:	000368
 */
static void Init_Track(seqp_* track, uintptr_t dataAddress, seqp_* parent)
{
	int i;

	if (!parent) {
		track->baseData         = (u8*)dataAddress;
		track->programCounter   = 0;
		track->tempo            = 120;
		track->timeBase         = AUDIO_TATUMS_PER_BEAT;
		track->timeRelationMode = 1;
		track->isPaused         = FALSE;
		track->pauseStatus      = 10;
		track->childMuteMask    = 0;
		track->isMuted          = 0;
	} else {
		track->baseData         = parent->baseData;
		track->programCounter   = dataAddress;
		track->fileHandle       = parent->fileHandle;
		track->tempo            = parent->tempo;
		track->doChangeTempo    = FALSE;
		track->tempoFactor      = parent->tempoFactor;
		track->timeBase         = parent->timeBase;
		track->timeRelationMode = parent->timeRelationMode;
		track->isPaused         = parent->isPaused;
		track->pauseStatus      = parent->pauseStatus;
		track->childMuteMask    = 0;
	}
	track->callStackDepth  = 0;
	track->_D0             = 0;
	track->waitTimer       = 0;
	track->trackState      = 1;
	track->parent          = parent;
	track->interruptEnable = 0;
	track->interruptActive = 0;
	track->timer           = 0;

	// Initialize all MoveParams with default values.
	for (i = 0; i < 18; ++i) {
		track->timedParam.move[i].duration     = 0.0f;
		track->timedParam.move[i].currentValue = 1.0f;
		track->timedParam.move[i].targetValue  = 1.0f;
	}

	track->timedParam.inner.pitch.currentValue = 0.0f;
	track->timedParam.inner.pitch.targetValue  = 0.0f;
	track->timedParam.inner.pitch.currentValue = 0.0f; // Just to be sure.
	track->timedParam.inner.pitch.targetValue  = 0.0f; // Just to be sure.
	track->timedParam.inner.pan.currentValue   = 0.5f;
	track->timedParam.inner.pan.targetValue    = 0.5f;

	track->timedParam.inner._100.currentValue = 0.5f;
	track->timedParam.inner._100.targetValue  = 0.5f;
	track->timedParam.inner._110.currentValue = 0.0f;
	track->timedParam.inner._110.targetValue  = 0.0f;

	track->timedParam.inner.fxmix.currentValue = 0.0f;
	track->timedParam.inner.fxmix.targetValue  = 0.0f;
	track->timedParam.inner.dolby.currentValue = 0.0f;
	track->timedParam.inner.dolby.targetValue  = 0.0f;

	// Initialize IIRs (skipping the first one)
	for (i = 1; i < 4; ++i) {
		track->timedParam.inner.IIRs[i].currentValue = 0.0f;
		track->timedParam.inner.IIRs[i].targetValue  = 0.0f;
	}

	track->timedParam.inner.distFilter.currentValue = 0.0f;
	track->timedParam.inner.distFilter.targetValue  = 0.0f;

	for (i = 0; i < 32; ++i) {
		track->regParam.reg[i] = 0;
	}

	if ((track->flags & 2) || !track->parent) {
		track->regParam.param.arguments[0] = 0;
		track->regParam.param.arguments[1] = 1;
		track->regParam.param.arguments[2] = 1;
		track->regParam.param.arguments[3] = 0x7fff;
		track->regParam.param.arguments[4] = 0x4000;
		for (i = 0; i < 3; ++i) {
			track->panCalcTypes[i]                  = 2;
			track->parentPanCalcTypes[i]            = 2;
			track->parentController.panCalcTypes[i] = 26;
		}
		track->regParam.param.bankNumber   = 0xf0;
		track->regParam.param.pitchScale   = 0x0c;
		track->regParam.param.basePriority = 0x40;
	} else {
		for (i = 0; i < 5; ++i) {
			track->regParam.param.arguments[i] = track->parent->regParam.param.arguments[i];
		}
		track->regParam.param.bankNumber   = track->parent->regParam.param.bankNumber;
		track->regParam.param.pitchScale   = track->parent->regParam.param.pitchScale;
		track->regParam.param.basePriority = track->parent->regParam.param.basePriority;
		for (i = 0; i < 3; ++i) {
			track->panCalcTypes[i]                  = track->parent->panCalcTypes[i];
			track->parentPanCalcTypes[i]            = track->parent->parentPanCalcTypes[i];
			track->parentController.panCalcTypes[i] = track->parent->parentController.panCalcTypes[i];
		}
	}

	for (i = 0; i < 16; ++i) {
		track->childOuterParams[i] = NULL;
		track->children[i]         = 0;
	}

	for (i = 0; i < 8; ++i) {
		track->_94[i]            = -1;
		track->channels[i]       = NULL;
		track->activeSoundIds[i] = 0;
	}
	track->_D4 = 0;
	track->_D5 = 0;
	track->_90 = 0;
	track->_D6 = FALSE;
	Osc_Init_Env(track);
	track->transpose      = 0;
	track->finalTranspose = 0;
	track->tickCounter    = -1;

	for (i = 0; i < 16; ++i) {
		track->trackPort[i].importFlag = 0;
		track->trackPort[i].exportFlag = 0;
	}

	track->isRegistered = 0;
}

/*
 * --INFO--
 * Address:	800143C0
 * Size:	0000A0
 */
BOOL Jaq_StopSeq(s32 index)
{
	seqp_* track;

	if (index == -1) {
		return FALSE;
	}
	track = rootseq[index];
	if (!track) {
		return FALSE;
	}

	switch (track->trackState) {
	case 0:
		break;
	case 2:
		BackTrack(track);
		DeAllocRoot(track);
		break;
	default:
		track->trackState = 3;
		break;
	}
	return TRUE;
}

/*
 * --INFO--
 * Address:	80014460
 * Size:	000054
 */
static void __StopSeq(seqp_* track)
{
	SeqUpdate(track, 0);
	Jaq_CloseTrack(track);
	DeAllocRoot(track);
	if (track->dataSourceMode == 1) {
		FAT_FreeMemory(track->fileHandle);
	}
}

/*
 * --INFO--
 * Address:	800144C0
 * Size:	000024
 */
s32 Jaq_SetSeqData(seqp_* param_1, u8* param_2, u32 param_3, u32 param_4)
{
	return Jaq_SetSeqData_Limit(param_1, param_2, param_3, param_4, 0);
}

/*
 * --INFO--
 * Address:	80014500
 * Size:	000170
 */
s32 Jaq_SetSeqData_Limit(seqp_* track, u8* param_2, u32 param_3, u32 param_4, u8 param_5)
{
	s32 root;
	BOOL level;
	u8* puVar2;

	if (!track) {
		level = OSDisableInterrupts();
		track = GetNewTrack();
		OSRestoreInterrupts(level);
		if (!track) {
			return -1;
		}
	} else {
		track->_3E4 = 0;
	}

	root = AllocNewRoot(track);
	if (root == -1) {
		return -1;
	}

	track->dataSourceMode = param_4;
	switch (param_4) {
	case 0:
		puVar2 = param_2;
		break;
	case 1:
		track->fileHandle = FAT_AllocateMemory(param_3);
		if (track->fileHandle == 0xffff) { // Isn't this literally impossible?
			return -1;
		}
		FAT_StoreBlock(param_2, track->fileHandle, 0, param_3);
		puVar2 = NULL;
		break;
	case 2:
		track->fileHandle = (u8)param_2;
		puVar2            = NULL;
		break;
	}
	track->trackId = root;
	track->flags   = 3;
	Init_Track(track, (uintptr_t)puVar2, (seqp_*)NULL);
	Jam_InitExtBuffer(&ROOT_OUTER[root]);
	Jam_AssignExtBuffer(track, &ROOT_OUTER[root]);
	Init_1shot(&track->parentController, param_5);
	track->tempoAccumulator = 0.0f;
	track->tempoFactor      = 1.0f;
	Jam_UpdateTrackAll(track);
	track->trackState = 2;
	return root;
}

/*
 * --INFO--
 * Address:	80014680
 * Size:	00002C
 */
BOOL Jaq_SetBankNumber(seqp_* track, u8 bankNum)
{
	u8 lo;

	// Let's get ahead of ourselves here.
	lo = track->regParam.param.bankNumber & 0xFF;
	if (!track) {
		return FALSE;
	}

	track->regParam.param.bankNumber = (bankNum << 8) | lo;
	return TRUE;
}

static s32 Jaq_RootCallback(void* track);

/*
 * --INFO--
 * Address:	800146C0
 * Size:	0000B4
 */
BOOL Jaq_StartSeq(u32 param_1)
{
	seqp_* track;
	u8* lbzu;

	if (param_1 == -1) {
		return FALSE;
	}

	track = rootseq[param_1];
	if (!track) {
		return FALSE;
	};

	// This feels like a fakematch, but oh well.
	switch (*(lbzu = &track->trackState)) {
	case 0:
		return FALSE;
	case 1:
		return FALSE;
	case 3:
		return FALSE;
	case 2:
		*lbzu = 1;
	}
	Jac_RegisterDspPlayerCallback(&Jaq_RootCallback, rootseq[param_1]);
	return TRUE;
}

/* Flags bit layout (u32):
 * -----------------------
 * Bits 0-3   : Index Selector (0 to 15)
 * Bit 5      : Direct Register Read Flag
 *               - If set, index is read from hardware register
 *               - Forces mode to 4
 * Bits 6-7   : Mode Flags (0 to 3)
 */

/*
 * --INFO--
 * Address:	80014780
 * Size:	00014C
 */
s32 Jaq_OpenTrack(seqp_* track, u32 flags, u32 source)
{

	seqp_* oldChildTrack;
	seqp_* newChildTrack;
	u8 childIndex;
	u8 trackFlags;

	childIndex = (flags & 0b00001111);
	trackFlags = (flags & 0b11000000) >> 6;
	if ((flags & 0b00100000)) {
		trackFlags = 4;
	}

	if ((u8)(flags & 0b00100000)) { // This u8 cast is a repeating pattern across JAudio... Mysterious.
		childIndex = Jam_ReadRegDirect(track, childIndex);
	}

	if (childIndex >= 16) {
		return -1;
	}

	oldChildTrack = track->children[childIndex];
	if (oldChildTrack) {
		Jaq_CloseTrack(oldChildTrack);
	}

	newChildTrack = GetNewTrack();
	if (!newChildTrack) {
		return -1;
	}

	track->children[childIndex] = newChildTrack;

    u32 trackId = track->trackId;
	newChildTrack->trackId        = ((trackId << 4 | childIndex) & 0xFFFFFFF) | ((trackId & 0xF0000000) + 0x10000000);
	newChildTrack->connectionId   = 0;
	newChildTrack->dataSourceMode = track->dataSourceMode;
	newChildTrack->flags          = trackFlags;

	Init_Track(newChildTrack, (uintptr_t)source, track);

	// Dev rolls "worst bit extraction method", asked to leave Nintendo EAD.
	newChildTrack->isMuted = newChildTrack->parent->isMuted | ((newChildTrack->parent->childMuteMask & (1 << childIndex)) >> childIndex);
	newChildTrack->outerParams = newChildTrack->parent->childOuterParams[childIndex];
	if (newChildTrack->outerParams) {
		++newChildTrack->outerParams->refCount;
	}

	Init_1shot(&newChildTrack->parentController, 0);
	Jam_UpdateTrackAll(newChildTrack);
	return 0;
}

/*
 * --INFO--
 * Address:	800148E0
 * Size:	0000B4
 */
void __AllNoteOff(seqp_* track)
{
	u32 i;

	if (!track->parent) {
		for (i = 0; i < 8; ++i) {
			NoteOFF_R(track, i, 10);
			track->_94[i]      = -1;
			track->channels[i] = NULL;
		}
	} else {
		for (i = 0; i < 8; ++i) {
			NoteOFF(track, i);
			track->_94[i]      = -1;
			track->channels[i] = NULL;
		}
	}
}

/*
 * --INFO--
 * Address:	800149A0
 * Size:	000120
 */
u32 Jaq_CloseTrack(seqp_* track)
{
	size_t i;

	// Specifically two separate conditional blocks, because why not.
	if (!track) {
		return 0;
	}
	if (track->trackState == 0) {
		return 0;
	}

	__AllNoteOff(track);
	BackTrack(track);

	for (i = 0; i < 16; ++i) {
		if (track->children[i]) {
			Jaq_CloseTrack(track->children[i]);
			track->children[i] = NULL;
		}
	}

	if (track->outerParams) {
		// This smells like refcounting.
		track->outerParams->refCount -= 1;
		track->outerParams = NULL;
	}

	for (i = 0; i < 16; ++i) {
		if (track->childOuterParams[i]) {
			track->childOuterParams[i]->isAssigned = FALSE;
			track->childOuterParams[i]             = NULL;
		}
	}
	track->isMuted       = 0;
	track->childMuteMask = 0;
	if (track->parent) {
		FixMoveChannelAll(&track->parentController, &track->parent->parentController);
	} else {
		FixReleaseChannelAll(&track->parentController);
	}
	Jam_UnRegistTrack(track);
	return 0;
}

/*
 * --INFO--
 * Address:	80014AC0
 * Size:	0000E8
 *
 * Note: While this function accepts `void*`, it really expects `seqp_*`.
 */
static s32 Jaq_RootCallback(void* VOID_track)
{
	seqp_* track;

	track = (seqp_*)VOID_track;
	if (track && track->trackState != 0) {
		if (track->trackState == 3) {
			__StopSeq(track);
			return -1;
		}

		track->tempoAccumulator += track->tempoFactor;
		if (track->tempoAccumulator < 1.0f) {
			SeqUpdate(track, 0);
		} else {
			while (track->tempoAccumulator >= 1.0f) {
				track->tempoAccumulator -= 1.0f;
				if (Jam_SeqmainNote(track, 0) == -1) {
					__StopSeq(track);
					return -1;
				}
			}

			SeqUpdate(track, 0);
		}
	} else {
		return -1;
	}

	return 0;
}
