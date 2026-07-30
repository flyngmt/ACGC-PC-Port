#include "jaudio_NES/dspdriver.h"

#include <stdbool.h>
#include "jaudio_NES/dspinterface.h"
#include "jaudio_NES/audiothread.h"
#include "jaudio_NES/driverinterface.h"
#include "jaudio_NES/rate.h"
#include <dolphin/PPCArch.h>

#define DSPCH_LENGTH (64)
static dspch_ DSPCH[DSPCH_LENGTH] ATTRIBUTE_ALIGN(32);

static int old_time;
static u32 history[10] = { 0xF4240 };

/*
 * --INFO--
 * Address:	........
 * Size:	000014
 */
dspch_* GetDSPchannelHandle(u32 idx)
{
	return &DSPCH[idx];
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000AD00
 * Size:	000060
 */
void InitDSPchannel()
{
	dspch_* chan;
	int i;

	for (i = 0; i < DSPCH_LENGTH; ++i) {
		chan = &DSPCH[i];

		chan->buffer_idx = i;
		chan->_01        = 0;
		chan->_08        = 0;
		chan->_06        = 0;
		chan->_0C        = NULL;
		chan->_03        = 0;
		chan->_04        = 0;
	}
}

typedef enum DSPChannelAllocState {
	DSPCHAN_Free          = 0, // Channel is available for allocation
	DSPCHAN_MonoAllocated = 1, // Channel allocated for mono playback
	DSPCHAN_StereoLeft    = 2, // Left channel of stereo pair
	DSPCHAN_StereoRight   = 3, // Right channel of stereo pair
	DSPCHAN_Stopping      = 4  // Channel is being force stopped
} DSPChannelAllocState;

/*
 * --INFO--
 * Address:	8000AD60
 * Size:	000114
 */
dspch_* AllocDSPchannel(u32 param_1, JacDspOwner param_2)
{
    jc_* jc = (jc_*)(uintptr_t)param_2;
	s32 i;
	
	if (param_1 == 0) {
		for (i = 0; i < DSPCH_LENGTH; ++i) {
            dspch_* ch = &DSPCH[i];
			if (!ch->_01) {
                // what the hell is this LOL, whatever it matches
                ch = (dspch_*)&((volatile dspch_*)DSPCH)[i];
				ch->_01 = true;
				ch->_08 = jc;
				ch->_03 = 1;
				DSP_AllocInit(i);
				return &DSPCH[i];
			}
		}
		return NULL;
	}

	for (i = 1; i < DSPCH_LENGTH; i += 2) {

		if (DSPCH[i]._01 || DSPCH[i - 1]._01)
			continue;

		DSPCH[i]._01     = 3;
		DSPCH[i - 1]._01 = 2;
		DSPCH[i]._08     = jc;
		DSPCH[i - 1]._08 = jc;
		DSP_AllocInit(i);
		DSP_AllocInit(i - 1);
		return &DSPCH[i - 1];
	}
	return NULL;
}

/*
 * --INFO--
 * Address:	8000AE80
 * Size:	0000DC
 */
int DeAllocDSPchannel(dspch_* chan, JacDspOwner id)
{
	if (chan == NULL) {
		return -1;
	}
	if (chan->_08 != (jc_*)(uintptr_t)id) {
		return -2;
	}

	switch (chan->_01) {
	case 1:
	case 4:
		chan->_01 = 0;
		break;
	case 2:
		chan->_01 = 0;
		DeAllocDSPchannel(&DSPCH[chan->buffer_idx + 1], id);
		break;
	case 3:
		chan->_01 = 0;
		DeAllocDSPchannel(&DSPCH[chan->buffer_idx - 1], id);
		break;
	}
	chan->_03 = 0;
	chan->_0C = nullptr;
	chan->_08 = 0;
	return 0;
}

/*
 * --INFO--
 * Address:	8000AF60
 * Size:	000104
 */
dspch_* GetLowerDSPchannel()
{
	u8 max      = 255;
	u32 id      = 0;
	u32 x       = 0;
	u32 i       = 0;
	u8* REF_max = &max;
	u32* REF_id = &id;
	u32* REF_x  = &x;
	u32* REF_i  = &i;

	for (i; i < DSPCH_LENGTH; i++) {
		if (DSPCH[i]._01 != 4) {
			if (DSPCH[i]._01 == 0) {
				DSPCH[i]._03 = 0;
				id           = i;
				break;
			}

			if (DSPCH[i]._0C) {
				GetDspHandle(DSPCH[i].buffer_idx);
				if (DSPCH[i]._03 <= max) {
					DSPchannel_* buf = GetDspHandle(DSPCH[i].buffer_idx);
					if (max != DSPCH[i]._03 || (x && (buf->_10C >= x || buf->_10C == 0))) {
						x   = buf->_10C;
						id  = i;
						max = DSPCH[i]._03;
					}
				}
			}
		}
	}

	return &DSPCH[id];
}

/*
 * --INFO--
 * Address:	8000B080
 * Size:	0000D8
 */
dspch_* GetLowerActiveDSPchannel()
{
	u8 a      = 0xFF;
	u32 index = 0;
	u32 c     = 0;
	u32 i;
	DSPchannel_* buf;

	u8* REF_a      = &a;
	u32* REF_index = &index;
	u32* REF_c     = &c;

	for (i = 0; i < DSPCH_LENGTH; ++i) {
		if (DSPCH[i]._01 == 4 || DSPCH[i]._01 == 0)
			continue;

		if (DSPCH[i]._03 > a)
			continue;

		buf = GetDspHandle(DSPCH[i].buffer_idx);
		if (a == DSPCH[i]._03) {

			if (c == 0)
				continue;
			if (buf->_10C < c && buf->_10C != 0)
				continue;
		}
		c     = buf->_10C;
		index = i;
		a     = DSPCH[i]._03;
	}

	return &DSPCH[index];
}

/*
 * --INFO--
 * Address:	8000B160
 * Size:	00007C
 */
BOOL ForceStopDSPchannel(dspch_* chan)
{
	dspch_** REF_chan;

	DSPchannel_* buf;

	REF_chan = &chan;
	if (chan->_01 == 4)
		return FALSE;
	buf = GetDspHandle(chan->buffer_idx);
	if (!buf->enabled)
		return FALSE;
	buf->endRequested = DSP_TRUE;
	chan->_01         = 4;
	DSP_FlushChannel(chan->buffer_idx);
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000B1E0
 * Size:	0000AC
 */
BOOL BreakLowerDSPchannel(u8 param_1)
{
	u8* REF_param_1;

	dspch_* chan;
	DSPchannel_* buf;

	chan        = GetLowerDSPchannel();
	REF_param_1 = &param_1;
	if (chan->_03 > param_1)
		return FALSE;
	if (chan->_03 == param_1) {
		buf = GetDspHandle(chan->buffer_idx); // UNUSED??
	}
	if (chan->_01) {
		if (chan->_0C) {
			chan->_06 = chan->_0C(chan, 3);
			ForceStopDSPchannel(chan);
			chan->_01 = 4;
		}
		ForceStopDSPchannel(chan);
	} else {
		return FALSE;
	}
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000B2A0
 * Size:	0000AC
 */
BOOL BreakLowerActiveDSPchannel(u8 id)
{
	u8* id_ptr   = &id;
	dspch_* chan = GetLowerActiveDSPchannel();

	if (chan->_03 > id) {
		return FALSE;
	}

	if (chan->_03 == id) {
		GetDspHandle(chan->buffer_idx);
	}

	if (chan->_01) {
		if (chan->_0C) {
			chan->_06 = chan->_0C(chan, 3);
			ForceStopDSPchannel(chan);
			chan->_01 = 4;
		}
		ForceStopDSPchannel(chan);
	} else {
		return FALSE;
	}

	return TRUE;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000008
 */
void UpdateDSPchannel(dspch_* chan)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000B360
 * Size:	0001F4
 */
void UpdateDSPchannelAll()
{
	int tick    = OSGetTick();
	u32 old     = tick - old_time;
	old_time    = tick;
	int id      = JAC_SUBFRAMES - DspSyncCountCheck();
	history[id] = old;

	if (id != 0 && (f32)history[0] / (f32)old < 1.1f) {
		BreakLowerActiveDSPchannel(0x7e);
	}

    dspch_* chan;
	for (u32 i = 0; i < DSPCH_LENGTH; i++) {
		chan     = &DSPCH[i];
		if (chan->_01 == FALSE) {
			continue;
		}

		DSPchannel_* buf = GetDspHandle(chan->buffer_idx);
		if (buf->done) {
			if (chan->_0C) {
				chan->_06 = chan->_0C(chan, 2);
			}
			buf->done    = FALSE;
			buf->enabled = FALSE;
			DSP_FlushChannel(chan->buffer_idx);
			if (chan->_01 == FALSE) {
				continue;
			}
		}

		if (!buf->endRequested) {
			buf->_10C++;
			if (buf->_10C == chan->_04 && chan->_0C) {
				chan->_06 = chan->_0C(chan, 4);
			}
		}

		if (chan->_0C) {
			if (chan->_06) {
				chan->_06--;
			}

			if (chan->_06 == 0) {
				chan->_06 = chan->_0C(chan, 0);
				if (chan->_06 == 0) {
					buf->done    = FALSE;
					buf->enabled = FALSE;
					__Entry_WaitChannel(1);
					DSP_FlushChannel(chan->buffer_idx);
				}
			}
		}
	}
	EntryCheck_WaitDSPChannel();
	PPCSync();
}
