#include "jaudio_NES/bankread.h"

#include "jaudio_NES/connect.h"
#include "jaudio_NES/bx.h"

#ifdef TARGET_PC
#include "dolphin/os.h"

#include <stdlib.h>
#include <string.h>
#endif

#define BANKP_SIZE (0x100)
static Bank_* bankp[BANKP_SIZE];

#ifdef TARGET_PC
typedef struct PcBankAllocation {
	void* data;
	struct PcBankAllocation* next;
} PcBankAllocation;

typedef struct PcBankParse {
	const u8* data;
	u32 size;
	PcBankAllocation* allocations;
	const char* error;
	u32 instrument_count;
	u32 voice_count;
	u32 percussion_count;
	u32 keymap_count;
	u32 velocity_map_count;
} PcBankParse;

static PcBankAllocation* pc_bank_allocations;
static const char* pc_bank_last_error;
static u32 pc_bank_last_instrument_count;
static u32 pc_bank_last_voice_count;
static u32 pc_bank_last_percussion_count;
static u32 pc_bank_last_keymap_count;
static u32 pc_bank_last_velocity_map_count;

static u16 pc_bank_read_be16(const u8* data)
{
	return (u16)((u16)data[0] << 8 | data[1]);
}

static u32 pc_bank_read_be32(const u8* data)
{
	return (u32)data[0] << 24 | (u32)data[1] << 16 | (u32)data[2] << 8 | data[3];
}

static f32 pc_bank_read_be_f32(const u8* data)
{
	u32 bits = pc_bank_read_be32(data);
	f32 value;
	memcpy(&value, &bits, sizeof(value));
	return value;
}

static void pc_bank_fail(PcBankParse* parse, const char* error)
{
	if (parse->error == NULL) {
		parse->error = error;
	}
}

static const u8* pc_bank_at(PcBankParse* parse, u32 offset, size_t size)
{
	if (offset == 0) {
		return NULL;
	}
	if (offset > parse->size || size > (size_t)(parse->size - offset)) {
		pc_bank_fail(parse, "offset outside IBNK");
		return NULL;
	}
	return parse->data + offset;
}

static void* pc_bank_alloc(PcBankParse* parse, size_t count, size_t size)
{
	if (count != 0 && size > SIZE_MAX / count) {
		pc_bank_fail(parse, "native allocation overflow");
		return NULL;
	}
	void* data = calloc(count, size);
	if (data == NULL) {
		pc_bank_fail(parse, "native allocation failed");
		return NULL;
	}
	PcBankAllocation* allocation = malloc(sizeof(*allocation));
	if (allocation == NULL) {
		free(data);
		pc_bank_fail(parse, "allocation tracking failed");
		return NULL;
	}
	allocation->data = data;
	allocation->next = parse->allocations;
	parse->allocations = allocation;
	return data;
}

static void pc_bank_free_allocations(PcBankAllocation* allocation)
{
	while (allocation != NULL) {
		PcBankAllocation* next = allocation->next;
		free(allocation->data);
		free(allocation);
		allocation = next;
	}
}

static void pc_bank_commit_allocations(PcBankParse* parse)
{
	if (parse->allocations == NULL) {
		return;
	}
	PcBankAllocation* tail = parse->allocations;
	while (tail->next != NULL) {
		tail = tail->next;
	}
	tail->next = pc_bank_allocations;
	pc_bank_allocations = parse->allocations;
	parse->allocations = NULL;
}

static Rand_* pc_bank_parse_random(PcBankParse* parse, u32 offset)
{
	const u8* raw = pc_bank_at(parse, offset, 0x10);
	if (raw == NULL) {
		return NULL;
	}
	Rand_* result = pc_bank_alloc(parse, 1, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	result->id = raw[0];
	result->value = pc_bank_read_be_f32(raw + 4);
	result->range = pc_bank_read_be_f32(raw + 8);
	memcpy(result->_0C, raw + 0x0c, sizeof(result->_0C));
	return result;
}

static Sense_* pc_bank_parse_sense(PcBankParse* parse, u32 offset)
{
	const u8* raw = pc_bank_at(parse, offset, 0x0c);
	if (raw == NULL) {
		return NULL;
	}
	Sense_* result = pc_bank_alloc(parse, 1, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	result->id = raw[0];
	result->type = raw[1];
	result->threshold = raw[2];
	result->min = pc_bank_read_be_f32(raw + 4);
	result->max = pc_bank_read_be_f32(raw + 8);
	return result;
}

static s16* pc_bank_parse_envelope(PcBankParse* parse, u32 offset)
{
	if (offset == 0) {
		return NULL;
	}
	size_t point_count = 0;
	for (;;) {
		if (point_count >= 0x10000) {
			pc_bank_fail(parse, "unterminated oscillator envelope");
			return NULL;
		}
		u32 point_offset = offset + (u32)(point_count * 6);
		if (point_offset < offset) {
			pc_bank_fail(parse, "oscillator envelope offset overflow");
			return NULL;
		}
		const u8* raw = pc_bank_at(parse, point_offset, 6);
		if (raw == NULL) {
			return NULL;
		}
		point_count++;
		if ((s16)pc_bank_read_be16(raw) > 10) {
			break;
		}
	}

	s16* result = pc_bank_alloc(parse, point_count * 3, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	for (size_t i = 0; i < point_count * 3; ++i) {
		result[i] = (s16)pc_bank_read_be16(parse->data + offset + i * 2);
	}
	return result;
}

static Osc_* pc_bank_parse_oscillator(PcBankParse* parse, u32 offset)
{
	const u8* raw = pc_bank_at(parse, offset, 0x18);
	if (raw == NULL) {
		return NULL;
	}
	Osc_* result = pc_bank_alloc(parse, 1, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	result->mode = raw[0];
	result->rate = pc_bank_read_be_f32(raw + 4);
	u32 attack_offset = pc_bank_read_be32(raw + 8);
	u32 release_offset = pc_bank_read_be32(raw + 0x0c);
	result->attackVecOffset = pc_bank_parse_envelope(parse, attack_offset);
	if (attack_offset != 0 && result->attackVecOffset == NULL) {
		return NULL;
	}
	if (release_offset == attack_offset) {
		result->releaseVecOffset = result->attackVecOffset;
	} else {
		result->releaseVecOffset = pc_bank_parse_envelope(parse, release_offset);
		if (release_offset != 0 && result->releaseVecOffset == NULL) {
			return NULL;
		}
	}
	result->width = pc_bank_read_be_f32(raw + 0x10);
	result->vertex = pc_bank_read_be_f32(raw + 0x14);
	return result;
}

static Vmap_* pc_bank_parse_velocity_map(PcBankParse* parse, u32 offset)
{
	const u8* raw = pc_bank_at(parse, offset, 0x10);
	if (raw == NULL) {
		return NULL;
	}
	Vmap_* result = pc_bank_alloc(parse, 1, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	result->mBaseVelocity = raw[0];
	result->mWsysID = (s16)pc_bank_read_be16(raw + 4);
	result->mWaveID = (s16)pc_bank_read_be16(raw + 6);
	result->mVolume = pc_bank_read_be_f32(raw + 8);
	result->mPitch = pc_bank_read_be_f32(raw + 0x0c);
	parse->velocity_map_count++;
	return result;
}

static InstKeymap_* pc_bank_parse_instrument_keymap(PcBankParse* parse, u32 offset)
{
	const u8* raw = pc_bank_at(parse, offset, 8);
	if (raw == NULL) {
		return NULL;
	}
	u32 count = pc_bank_read_be32(raw + 4);
	if (count > 0x100 || pc_bank_at(parse, offset + 8, (size_t)count * 4) == NULL) {
		pc_bank_fail(parse, "invalid instrument velocity-map count");
		return NULL;
	}
	InstKeymap_* result = pc_bank_alloc(parse, 1, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	result->mBaseKey = raw[0];
	result->mVelocityCount = count;
	if (count != 0) {
		result->mVelocities = pc_bank_alloc(parse, count, sizeof(*result->mVelocities));
		if (result->mVelocities == NULL) {
			return NULL;
		}
	}
	for (u32 i = 0; i < count; ++i) {
		u32 velocity_offset = pc_bank_read_be32(parse->data + offset + 8 + i * 4);
		result->mVelocities[i] = pc_bank_parse_velocity_map(parse, velocity_offset);
		if (result->mVelocities[i] == NULL) {
			pc_bank_fail(parse, "missing instrument velocity map");
			return NULL;
		}
	}
	parse->keymap_count++;
	return result;
}

static Inst_* pc_bank_parse_instrument(PcBankParse* parse, u32 offset)
{
	const u8* raw = pc_bank_at(parse, offset, 0x2c);
	if (raw == NULL) {
		return NULL;
	}
	if (pc_bank_read_be32(raw) != 'INST') {
		pc_bank_fail(parse, "invalid instrument magic");
		return NULL;
	}
	u32 key_count = pc_bank_read_be32(raw + 0x28);
	if (key_count > 0x100 || pc_bank_at(parse, offset + 0x2c, (size_t)key_count * 4) == NULL) {
		pc_bank_fail(parse, "invalid instrument key-map count");
		return NULL;
	}
	Inst_* result = pc_bank_alloc(parse, 1, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	result->mMagic = 'INST';
	result->mFlag = pc_bank_read_be32(raw + 4);
	result->mFreqMultiplier = pc_bank_read_be_f32(raw + 8);
	result->mGainMultiplier = pc_bank_read_be_f32(raw + 0x0c);
	for (u32 i = 0; i < 2; ++i) {
		u32 osc_offset = pc_bank_read_be32(raw + 0x10 + i * 4);
		u32 random_offset = pc_bank_read_be32(raw + 0x18 + i * 4);
		u32 sense_offset = pc_bank_read_be32(raw + 0x20 + i * 4);
		result->mOscillators[i] = pc_bank_parse_oscillator(parse, osc_offset);
		result->mEffects[i] = pc_bank_parse_random(parse, random_offset);
		result->mSensors[i] = pc_bank_parse_sense(parse, sense_offset);
		if ((osc_offset != 0 && result->mOscillators[i] == NULL) ||
		    (random_offset != 0 && result->mEffects[i] == NULL) ||
		    (sense_offset != 0 && result->mSensors[i] == NULL)) {
			return NULL;
		}
	}
	result->mKeyRegionCount = (int)key_count;
	if (key_count != 0) {
		result->mKeyRegions = pc_bank_alloc(parse, key_count, sizeof(*result->mKeyRegions));
		if (result->mKeyRegions == NULL) {
			return NULL;
		}
	}
	for (u32 i = 0; i < key_count; ++i) {
		u32 key_offset = pc_bank_read_be32(parse->data + offset + 0x2c + i * 4);
		result->mKeyRegions[i] = pc_bank_parse_instrument_keymap(parse, key_offset);
		if (result->mKeyRegions[i] == NULL) {
			pc_bank_fail(parse, "missing instrument key map");
			return NULL;
		}
	}
	parse->instrument_count++;
	return result;
}

static Voice_* pc_bank_parse_voice(PcBankParse* parse, u32 offset)
{
	const u8* raw = pc_bank_at(parse, offset, 0x0c);
	if (raw == NULL) {
		return NULL;
	}
	u32 count = pc_bank_read_be32(raw + 8);
	if (count > 0x1000 || pc_bank_at(parse, offset + 0x0c, (size_t)count * 4) == NULL) {
		pc_bank_fail(parse, "invalid voice-map count");
		return NULL;
	}
	Voice_* result = pc_bank_alloc(parse, 1, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	memcpy(result->_00, raw, sizeof(result->_00));
	result->size = (int)count;
	if (count != 0) {
		result->_0C = pc_bank_alloc(parse, count, sizeof(*result->_0C));
		if (result->_0C == NULL) {
			return NULL;
		}
	}
	for (u32 i = 0; i < count; ++i) {
		u32 data_offset = pc_bank_read_be32(parse->data + offset + 0x0c + i * 4);
		if (data_offset != 0) {
			result->_0C[i] = (void*)pc_bank_at(parse, data_offset, 1);
			if (result->_0C[i] == NULL) {
				return NULL;
			}
		}
	}
	parse->voice_count++;
	return result;
}

static PercKeymap_* pc_bank_parse_percussion_keymap(PcBankParse* parse, u32 offset)
{
	const u8* raw = pc_bank_at(parse, offset, 0x14);
	if (raw == NULL) {
		return NULL;
	}
	u32 count = pc_bank_read_be32(raw + 0x10);
	if (count > 0x100 || pc_bank_at(parse, offset + 0x14, (size_t)count * 4) == NULL) {
		pc_bank_fail(parse, "invalid percussion velocity-map count");
		return NULL;
	}
	PercKeymap_* result = pc_bank_alloc(parse, 1, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	result->mPitch = pc_bank_read_be_f32(raw);
	result->mVolume = pc_bank_read_be_f32(raw + 4);
	u32 random0_offset = pc_bank_read_be32(raw + 8);
	u32 random1_offset = pc_bank_read_be32(raw + 0x0c);
	result->_08 = pc_bank_parse_random(parse, random0_offset);
	result->_0C = pc_bank_parse_random(parse, random1_offset);
	if ((random0_offset != 0 && result->_08 == NULL) || (random1_offset != 0 && result->_0C == NULL)) {
		return NULL;
	}
	result->mVelocityCount = (int)count;
	if (count != 0) {
		result->mVelocities = pc_bank_alloc(parse, count, sizeof(*result->mVelocities));
		if (result->mVelocities == NULL) {
			return NULL;
		}
	}
	for (u32 i = 0; i < count; ++i) {
		u32 velocity_offset = pc_bank_read_be32(parse->data + offset + 0x14 + i * 4);
		result->mVelocities[i] = pc_bank_parse_velocity_map(parse, velocity_offset);
		if (result->mVelocities[i] == NULL) {
			pc_bank_fail(parse, "missing percussion velocity map");
			return NULL;
		}
	}
	parse->keymap_count++;
	return result;
}

static Perc_* pc_bank_parse_percussion(PcBankParse* parse, u32 offset)
{
	const u8* raw = pc_bank_at(parse, offset, 0x408);
	if (raw == NULL) {
		return NULL;
	}
	u32 magic = pc_bank_read_be32(raw);
	if (magic != 'PERC' && magic != 'PER2') {
		pc_bank_fail(parse, "invalid percussion magic");
		return NULL;
	}
	Perc_* result = pc_bank_alloc(parse, 1, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	result->mMagic = (int)magic;
	memcpy(result->_04, raw + 4, sizeof(result->_04));
	for (u32 i = 0; i < 128; ++i) {
		u32 key_offset = pc_bank_read_be32(raw + 0x88 + i * 4);
		if (key_offset != 0) {
			result->mKeyRegions[i] = pc_bank_parse_percussion_keymap(parse, key_offset);
			if (result->mKeyRegions[i] == NULL) {
				return NULL;
			}
		}
		result->_288[i] = (s8)raw[0x288 + i];
		result->_308[i] = pc_bank_read_be16(raw + 0x308 + i * 2);
	}
	parse->percussion_count++;
	return result;
}

static Bank_* pc_bank_convert(const u8* ibnk_address, PcBankParse* parse)
{
	memset(parse, 0, sizeof(*parse));
	parse->data = ibnk_address;
	if (ibnk_address == NULL) {
		pc_bank_fail(parse, "null IBNK address");
		return NULL;
	}
	if (pc_bank_read_be32(ibnk_address) != 'IBNK') {
		pc_bank_fail(parse, "invalid IBNK magic");
		return NULL;
	}
	parse->size = pc_bank_read_be32(ibnk_address + 4);
	if (parse->size < 0x3e4 || parse->size > 0x10000000) {
		pc_bank_fail(parse, "invalid IBNK size");
		return NULL;
	}
	if (pc_bank_read_be32(ibnk_address + 0x0c) != 0) {
		pc_bank_fail(parse, "unsupported IBNK version");
		return NULL;
	}
	if (pc_bank_read_be32(ibnk_address + 0x20) != 'BANK') {
		pc_bank_fail(parse, "invalid BANK magic");
		return NULL;
	}

	Bank_* result = pc_bank_alloc(parse, 1, sizeof(*result));
	if (result == NULL) {
		return NULL;
	}
	result->mMagic = 'BANK';
	for (u32 i = 0; i < BANK_INST_COUNT; ++i) {
		u32 offset = pc_bank_read_be32(ibnk_address + 0x24 + i * 4);
		if (offset == 0) {
			continue;
		}
		if (i < BANK_TEST_INST_COUNT) {
			result->mInstruments[i] = pc_bank_parse_instrument(parse, offset);
			if (result->mInstruments[i] == NULL) {
				return NULL;
			}
		} else if (i < BANK_TEST_PERC_OFFSET) {
			result->mVoices[i] = pc_bank_parse_voice(parse, offset);
			if (result->mVoices[i] == NULL) {
				return NULL;
			}
		} else {
			result->mPercs[i] = pc_bank_parse_percussion(parse, offset);
			if (result->mPercs[i] == NULL) {
				return NULL;
			}
		}
	}
	return result;
}

/* PC banks remain serialized big-endian data; this builds a separate native pointer graph. */
Bank_* Bank_Test(u8* ibnk_address)
{
	PcBankParse parse;
	Bank_* result = pc_bank_convert(ibnk_address, &parse);
	pc_bank_last_error = parse.error;
	pc_bank_last_instrument_count = parse.instrument_count;
	pc_bank_last_voice_count = parse.voice_count;
	pc_bank_last_percussion_count = parse.percussion_count;
	pc_bank_last_keymap_count = parse.keymap_count;
	pc_bank_last_velocity_map_count = parse.velocity_map_count;
	if (result == NULL) {
		pc_bank_free_allocations(parse.allocations);
		return NULL;
	}
	pc_bank_commit_allocations(&parse);
	return result;
}
#else
/*
 * --INFO--
 * Address:	8000BE00
 * Size:	000024
 */
static void PTconvert(void** pointer, u32 base_address)
{
	if (*pointer >= (void*)base_address || *pointer == NULL) {
		return;
	}
	*pointer = *(char**)pointer + base_address;
}

/*
 * --INFO--
 * Address:	8000BE40
 * Size:	000270
 */
Bank_* Bank_Test(u8* ibnk_address)
{
	u32 i, j, k;
	u32 base_addr    = (u32)ibnk_address;
	Bank_* startBank = (Bank_*)(ibnk_address + 0x20);
	if (startBank->mMagic != 'BANK') {
		return NULL;
	}

	for (i = 0; i < BANK_TEST_INST_COUNT; ++i) {
		PTconvert((void**)&startBank->mInstruments[i], base_addr);

		Inst_* inst = (Inst_*)startBank->mInstruments[i];
		if (!inst) {
			continue;
		}

		// each instrument has two oscillators, effects, and sensors
		for (j = 0; j < 2; j++) {
			PTconvert((void**)&inst->mOscillators[j], base_addr);
			PTconvert((void**)&inst->mEffects[j], base_addr);
			PTconvert((void**)&inst->mSensors[j], base_addr);

			if (inst->mOscillators[j]) {
				PTconvert((void**)&inst->mOscillators[j]->attackVecOffset, base_addr);
				PTconvert((void**)&inst->mOscillators[j]->releaseVecOffset, base_addr);
			}
		}

		// each instrument also has a certain number of key regions
		for (j = 0; j < inst->mKeyRegionCount; j++) {
			PTconvert((void**)&inst->mKeyRegions[j], base_addr);

			for (k = 0; k < inst->mKeyRegions[j]->mVelocityCount; k++) {
				PTconvert((void**)&inst->mKeyRegions[j]->mVelocities[k], base_addr);
			}
		}
	}

	// treat the next block of 100 as voices (for some reason)
	for (i = 0; i < BANK_TEST_VOICE_COUNT; i++) {
		PTconvert((void**)&(startBank->mInstruments + BANK_TEST_VOICE_OFFSET)[i], base_addr);

		Voice_* voice = (Voice_*)(startBank->mInstruments + BANK_TEST_VOICE_OFFSET)[i];
		if (!voice) {
			continue;
		}

		for (j = 0; j < voice->size; j++) {
			PTconvert(&voice->_0C[j], base_addr);
		}
	}

	// treat the next block of 12 as percussion (for some reason)
	for (i = 0; i < BANK_TEST_PERC_COUNT; i++) {
		PTconvert((void**)&(startBank->mInstruments + BANK_TEST_PERC_OFFSET)[i], base_addr);

		Perc_* perc = (Perc_*)(startBank->mInstruments + BANK_TEST_PERC_OFFSET)[i];
		if (!perc) {
			continue;
		}

		for (j = 0; j < 128; j++) {
			PTconvert((void**)&perc->mKeyRegions[j], base_addr);

			PercKeymap_* key = perc->mKeyRegions[j];
			if (!key) {
				continue;
			}

			PTconvert(&key->_08, base_addr);
			PTconvert(&key->_0C, base_addr);

			for (k = 0; k < key->mVelocityCount; k++) {
				PTconvert((void**)&key->mVelocities[k], base_addr);
			}
		}
	}

	return startBank;
}
#endif

/*
 * --INFO--
 * Address:	8000C0C0
 * Size:	000068
 */
static BOOL __Bank_Regist_Inner(u8* ibnk, u32 param_2, u32 param_3)
{
#ifdef TARGET_PC
	if (param_2 >= BANKP_SIZE) {
		OSReport("[PC] IBNK registration index %u is out of range\n", param_2);
		return FALSE;
	}
#endif
	Jac_BnkConnectTableSet(param_3, param_2);
	bankp[param_2] = Bank_Test(ibnk);
	if (!bankp[param_2]) {
#ifdef TARGET_PC
		OSReport("[PC] IBNK bank %u conversion failed: %s\n", param_2,
		         pc_bank_last_error != NULL ? pc_bank_last_error : "unknown error");
#endif
		return FALSE;
	}
#ifdef TARGET_PC
	OSReport("[PC] IBNK bank %u converted: %u instruments, %u voices, %u percussion sets, %u key maps, %u velocity maps\n",
	         param_2, pc_bank_last_instrument_count, pc_bank_last_voice_count,
	         pc_bank_last_percussion_count, pc_bank_last_keymap_count, pc_bank_last_velocity_map_count);
#endif
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000C140
 * Size:	000024
 */
BOOL Bank_Regist(void* ibnk, u32 param_2)
{
#ifdef TARGET_PC
	if (ibnk == NULL) {
		return FALSE;
	}
	return __Bank_Regist_Inner((u8*)ibnk, param_2, pc_bank_read_be32((const u8*)ibnk + 8));
#else
	return __Bank_Regist_Inner((u8*)ibnk, param_2, ((Ibnk_*)ibnk)->_08);
#endif
}

/*
 * --INFO--
 * Address:	........
 * Size:	000020
 */
BOOL Bank_Regist_Direct(void* ibnk, u32 param_2, u32 param_3)
{
	return __Bank_Regist_Inner((u8*)ibnk, param_2, param_3);
}

/*
 * --INFO--
 * Address:	8000C180
 * Size:	00002C
 */
void Bank_Init()
{
#ifdef TARGET_PC
	pc_bank_free_allocations(pc_bank_allocations);
	pc_bank_allocations = NULL;
#endif
	for (int i = 0; i < BANKP_SIZE; ++i) {
		bankp[i] = NULL;
	}
}

/*
 * --INFO--
 * Address:	8000C1C0
 * Size:	000028
 */
Bank_* Bank_Get(u32 index)
{
	if (index >= BANKP_SIZE) {
		return NULL;
	}
	return bankp[index];
}
