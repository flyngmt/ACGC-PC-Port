#include <dolphin.h>
#include <dolphin/pad.h>
#include <dolphin/os/OSSerial.h>

typedef struct PADClampRegion {
	u8 minTrigger;
	u8 maxTrigger;
	s8 minStick;
	s8 maxStick;
	s8 xyStick;
	s8 minSubstick;
	s8 maxSubstick;
	s8 xySubstick;
} PADClampRegion;

static PADClampRegion ClampRegion = {
	// Triggers
	30,
	180,

#ifdef TARGET_PC
	// Stick deadzone comes from the configurable setting in pc_pad.c
	// Left stick
	0,
	72,
	40,

	// Right stick
	0,
	59,
	31,
#else
	// Left stick
	15,
	72,
	40,

	// Right stick
	15,
	59,
	31,
#endif
};

// functions
static void ClampStick(s8* px, s8* py, s8 max, s8 xy, s8 min);
static void ClampTrigger(u8* trigger);

static void ClampStick(s8* px, s8* py, s8 max, s8 xy, s8 min) {
	int x = *px;
	int y = *py;
	int signX;
	int signY;
	int d;

	if (0 <= x) {
		signX = 1;
	} else {
		signX = -1;
		x     = -x;
	}

	if (0 <= y) {
		signY = 1;
	} else {
		signY = -1;
		y     = -y;
	}

	if (x <= min) {
		x = 0;
	} else {
		x -= min;
	}
	if (y <= min) {
		y = 0;
	} else {
		y -= min;
	}

	if (x == 0 && y == 0) {
		*px = *py = 0;
		return;
	}

	if (xy * y <= xy * x) {
		d = xy * x + (max - xy) * y;
		if (xy * max < d) {
			x = (s8)(xy * max * x / d);
			y = (s8)(xy * max * y / d);
		}
	} else {
		d = xy * y + (max - xy) * x;
		if (xy * max < d) {
			x = (s8)(xy * max * x / d);
			y = (s8)(xy * max * y / d);
		}
	}

	*px = (s8)(signX * x);
	*py = (s8)(signY * y);
}

static void ClampTrigger(u8* trigger) {
	if (*trigger <= ClampRegion.minTrigger) {
		*trigger = 0;
	} else {
		if (ClampRegion.maxTrigger < *trigger) {
			*trigger = ClampRegion.maxTrigger;
		}
		*trigger -= ClampRegion.minTrigger;
	}
}


void PADClamp(PADStatus* status) {
	int i;
	for (i = 0; i < SI_MAX_CHAN; i++, status++) {
		if (status->err != PAD_ERR_NONE) {
			continue;
		}

		ClampStick(&status->stickX, &status->stickY, ClampRegion.maxStick, ClampRegion.xyStick, ClampRegion.minStick);
		ClampStick(&status->substickX, &status->substickY, ClampRegion.maxSubstick, ClampRegion.xySubstick, ClampRegion.minSubstick);
		ClampTrigger(&status->triggerLeft);
		ClampTrigger(&status->triggerRight);
	}
}
