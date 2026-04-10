#include "jaudio_NES/bankread.h"

#include "jaudio_NES/connect.h"
#include "jaudio_NES/bx.h"

#define BANKP_SIZE (0x100)
static Bank_* bankp[BANKP_SIZE];

/*
 * --INFO--
 * Address:	8000BE00
 * Size:	000024
 */
#ifdef TARGET_PC
static void PTconvert(void** pointer, uintptr_t base_address)
{
	/* ROM data stores 32-bit offsets. On 64-bit, void* is 8 bytes but the
	 * serialized data has 4-byte values. Read as u32 offset, relocate. */
	u32 offset = *(u32*)pointer;
	if (offset == 0) {
		*pointer = NULL;
		return;
	}
	if (offset >= (u32)base_address) {
		*pointer = (void*)(uintptr_t)offset;
		return;
	}
	*pointer = (void*)(base_address + offset);
}
#else
static void PTconvert(void** pointer, u32 base_address)
{
	if (*pointer >= (void*)base_address || *pointer == NULL) {
		return;
	}
	*pointer = *(char**)pointer + base_address;
}
#endif

/*
 * --INFO--
 * Address:	8000BE40
 * Size:	000270
 */
Bank_* Bank_Test(u8* ibnk_address)
{
	u32 i, j, k;
#ifdef TARGET_PC
	uintptr_t base_addr = (uintptr_t)ibnk_address;
#else
	u32 base_addr    = (u32)ibnk_address;
#endif
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

/*
 * --INFO--
 * Address:	8000C0C0
 * Size:	000068
 */
static BOOL __Bank_Regist_Inner(u8* ibnk, u32 param_2, u32 param_3)
{
	Jac_BnkConnectTableSet(param_3, param_2);
	bankp[param_2] = Bank_Test(ibnk);
	if (!bankp[param_2])
		return FALSE;
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000C140
 * Size:	000024
 */
BOOL Bank_Regist(void* ibnk, u32 param_2)
{
	return __Bank_Regist_Inner((u8*)ibnk, param_2, ((Ibnk_*)ibnk)->_08);
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
