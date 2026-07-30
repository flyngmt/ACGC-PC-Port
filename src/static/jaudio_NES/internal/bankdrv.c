#include "jaudio_NES/bankdrv.h"

#include "jaudio_NES/random.h"
#include "jaudio_NES/rate.h"
#include "jaudio_NES/bx.h"
#include "jaudio_NES/ja_calc.h"

static u32 FORCE_RELEASE_TABLE[3] = { 5, 15, 0 };

/*
 * --INFO--
 * Address:	8000CFC0
 * Size:	000030
 */
Inst_* Bank_InstChange(Bank_* bank, u32 index)
{
    Inst_* ret;

	if (bank == NULL) {
		ret = NULL;
	} else {
	    ret = bank->mInstruments[index];
    }

    return ret;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
Voice_* Bank_VoiceChange(Bank_* bank, u32 index)
{
    Voice_* ret;

	if (bank == NULL) {
		ret = NULL;
	} else {
	    ret = bank->mVoices[index];
    }

    return ret;
}

/*
 * --INFO--
 * Address:	8000D000
 * Size:	000030
 */
Perc_* Bank_PercChange(Bank_* bank, u32 index)
{
    Perc_* ret;

	if (bank == NULL) {
        ret = NULL;
	} else {
		ret = bank->mPercs[index];
    }

	return ret;
}

/*
 * --INFO--
 * Address:	8000D040
 * Size:	00005C
 */
int Bank_GetInstKeymap(Inst_* inst, u8 param_2)
{
	if (!inst) {
		return 0;
	}

	for (u32 i = 0; i < inst->mKeyRegionCount; i++) {
		if (param_2 <= inst->mKeyRegions[i]->mBaseKey) {
			return i; // Return the index of the keymap
		}
	}

	return -1;
}

/*
 * --INFO--
 * Address:	8000D0A0
 * Size:	000090
 */
Vmap_* Bank_GetInstVmap(Inst_* inst, u8 param_2, u8 param_3)
{

	if (!inst) {
		return NULL;
	}

	int instIndex = Bank_GetInstKeymap(inst, param_2);
	if (instIndex != -1) {
		u8* REF_p3       = &param_3;
		InstKeymap_* key = inst->mKeyRegions[instIndex];
		for (u32 i = 0; i < key->mVelocityCount; i++) {
			Vmap_* vmap = key->mVelocities[i];
			if (param_3 <= vmap->mBaseVelocity) {
				return vmap;
			}
		}

		return NULL;
	}

	return NULL;
}

/*
 * --INFO--
 * Address:	8000D140
 * Size:	000068
 */
Vmap_* Bank_GetPercVmap(Perc_* perc, u8 keyIdx, u8 vel)
{
	if (!perc) {
		return 0;
	}

	PercKeymap_* keymap = perc->mKeyRegions[keyIdx];
	if (!keymap) {
		return 0;
	}
	for (u32 i = 0; i < keymap->mVelocityCount; i++) {
		Vmap_* vmap = keymap->mVelocities[i];
		if (vel <= vmap->mBaseVelocity) {
			return vmap;
		}
	}
	return 0;
}

/*
 * --INFO--
 * Address:	........
 * Size:	000010
 */
int Bank_GetVoiceMap(Voice_* voice, u16 id)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000D1C0
 * Size:	000104
 */
f32 Bank_SenseToOfs(Sense_* sensor, u8 p2)
{
    f32 t;
    f32 s;

	if (!sensor) {
		return 1.0f;
	} else if (sensor->threshold == 127 || sensor->threshold == 0) {
		return sensor->min + p2 * (sensor->max - sensor->min) / 127.0f;
	} else if (p2 < sensor->threshold) {
        t = p2;
        s = sensor->threshold;
		return sensor->min + (1.0f - sensor->min) * (t / s);
	} else {
        int thresh = sensor->threshold;

        t = p2 - thresh;
        s = 127 - thresh;
        return 1.0f + (sensor->max - 1.0f) * ((t) / (s));
    }
}

/*
 * --INFO--
 * Address:	8000D2E0
 * Size:	000048
 */
f32 Bank_RandToOfs(Rand_* rand)
{
	f32 value;

	if (!rand) {
		return 1.0f;
	}
	value = GetRandom_sf32();
	value *= rand->range;
	value += rand->value;
	return value;
}

/*
 * --INFO--
 * Address:	8000D340
 * Size:	0003F8
 */
f32 Bank_OscToOfs(Osc_* osc, Oscbuf_* buf)
{
	f32 sub;
	int offset;
    s16 val1;
    s16 val2;
	s16 val0;
	f32 calc;
	s16* table;
    f32 v;

	if (osc == NULL) {
		buf->value = 1.0f;
		return 1.0f;
	}

	if (buf->state == 4) {
		if (osc->attackVecOffset != osc->releaseVecOffset) {
			buf->tableIndex  = 0;
			buf->timeCounter = 0.0f;
			buf->targetValue = buf->value;
		}
		if (osc->releaseVecOffset == 0 && buf->releaseParam == 0) {
			buf->releaseParam = 0x10;
		}

		if (buf->releaseParam) {
			buf->state     = 8;
			buf->curveType = buf->releaseParam >> 14 & 3;
			f32 x          = buf->releaseParam & 0x3fff;
			x *= (JAC_DAC_RATE / 80.0f) / 600.0f;
			buf->timeCounter = x;
			if (buf->timeCounter < 1.0f) {
				buf->timeCounter = 1.0f;
			}
			buf->targetValue = 0.0f;
			buf->deltaRate   = (buf->targetValue - buf->value) / buf->timeCounter;
		} else {
			buf->state = 5;
		}
	}
	if (buf->state == 6) {
		buf->tableIndex  = 0;
		buf->timeCounter = 0.0f;
		buf->targetValue = buf->value;
		buf->state       = 7;
	}

	if (buf->state == 5) {
		table = osc->releaseVecOffset;
	} else if (buf->state == 7) {
		table = (s16*)FORCE_RELEASE_TABLE;
	} else {
		table = osc->attackVecOffset;
	}

	if (table == NULL && buf->state != 8) {
		buf->value = 1.0f;
		return 1.0f;
	}
	if (buf->state == 0) {
		return 1.0f;
	}
	if (buf->state == 3) {
		return buf->value * osc->width + osc->vertex;
	}

	if (buf->state == 1) {
		buf->state        = 2;
		buf->tableIndex   = 0;
		buf->timeCounter  = 0.0f;
		buf->targetValue  = 0.0f;
		buf->releaseParam = 0;
		sub               = osc->rate;
	} else {
		sub = osc->rate;
	}
	if (buf->state == 7) {
		sub = 1.0f;
	}
	buf->timeCounter -= sub;

	while (buf->timeCounter <= 0.0f) {
		offset     = (buf->tableIndex * 3);
		buf->value = buf->targetValue;
		if (buf->state == 8) {
			buf->state = 0;
			break;
		}

		val0 = table[offset + 0];
		val1 = table[offset + 1];
		val2 = table[offset + 2];
		if (val0 == 0xd) {
			buf->tableIndex = val2;
			continue;
		} else if (val0 == 0xf) {
			buf->state = 0;
			break;
		} else if (val0 == 0xe) {
			buf->state = 3;
			return buf->value * osc->width + osc->vertex;
		}
		buf->curveType = val0;

		if (val1 == 0) {
			buf->targetValue = val2 / 32768.0f;
			buf->tableIndex++;
		} else {
            // issue here
            v = (u16)(int)val1;
            v = v * ((JAC_DAC_RATE / 80.0f) / 600.0f);
			buf->timeCounter = v;
			buf->targetValue = (int)val2 / 32768.0f;
			buf->deltaRate   = (buf->targetValue - buf->value) / buf->timeCounter;
			buf->tableIndex++;
		}
	}

	calc       = -(buf->deltaRate * buf->timeCounter - buf->targetValue);
	buf->value = calc;

	switch (buf->curveType) {
	case 0:
		break;
	case 1:
		if (calc > 0.0f) {
			calc = calc * calc;
		} else {
			calc = -calc * calc;
		}
		break;

	case 2:
		if (calc > 0.0f) {
			calc = sqrtf2(calc);
		} else {
			calc = -sqrtf2(-calc);
		}
		break;
	}
	return calc * osc->width + osc->vertex;
}
