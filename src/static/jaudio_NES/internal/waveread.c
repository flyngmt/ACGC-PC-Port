#include "jaudio_NES/waveread.h"

#include "jaudio_NES/connect.h"
#include "jaudio_NES/heapctrl.h"
#include "jaudio_NES/bx.h"

#define WAVEARC_SIZE   (0x100)
#define WAVEGROUP_SIZE (0x100)

static WaveArchiveBank_* wavearc[WAVEARC_SIZE];
static CtrlGroup_* wavegroup[WAVEGROUP_SIZE];
CtrlGroup_* CGRP_ARRAY[16];

/*
 * --INFO--
 * Address:	8000C200
 * Size:	000038
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
		/* Already an absolute address (or larger than base) — leave as-is
		 * but widen to pointer */
		*pointer = (void*)(uintptr_t)offset;
		return;
	}
	*pointer = (void*)(base_address + offset);
}
#else
static void PTconvert(void** pointer, u32 base_address)
{
	if (*pointer == NULL) {
		*pointer = NULL;
		return;
	}
	if (*pointer >= (void*)base_address || *pointer == NULL) {
		return;
	}
	*pointer = *(char**)pointer + base_address;
}
#endif

/*
 * --INFO--
 * Address:	8000C240
 * Size:	0002A0
 */
CtrlGroup_* Wave_Test(u8* data)
{
#ifdef TARGET_PC
    uintptr_t base_addr = (uintptr_t)data;
#else
    u32 base_addr = (u32)data;
#endif
	CtrlGroup_* group;
	SCNE_* scene;
	Ctrl_* cst;
	Ctrl_* cdf;
	Ctrl_* cex;
	u32 i;
    u32 j;
	WaveArchiveBank_* arcBank;
	WaveArchive_* arc;

#ifdef TARGET_PC
	/* ROM data has 32-bit pointer fields at fixed offsets regardless of
	 * native pointer size. Read as u32 offsets and relocate manually. */
	{
		u32 arcBank_off = *(u32*)(data + 0x10);
		u32 group_off   = *(u32*)(data + 0x14);
		arcBank = arcBank_off ? (WaveArchiveBank_*)(base_addr + arcBank_off) : NULL;
		group   = group_off   ? (CtrlGroup_*)(base_addr + group_off)         : NULL;
		/* Write back relocated pointers for later use via struct fields */
		((Wsys_*)data)->waveArcBank = arcBank;
		((Wsys_*)data)->ctrlGroup   = group;
	}
#else
	PTconvert((void**)&((Wsys_*)data)->waveArcBank, base_addr);
	PTconvert((void**)&((Wsys_*)data)->ctrlGroup, base_addr);
	arcBank       = *(WaveArchiveBank_**)(data + 0x10);
	group         = *(CtrlGroup_**)(data + 0x14);
#endif
	CGRP_ARRAY[0] = group;

	if (arcBank->magic != 'WINF') {
		return NULL;
	}
	if (group->magic != 'WBCT') {
		return NULL;
	}

	for (i = 0; i < arcBank->count; i++) {
		PTconvert((void**)&arcBank->waveGroups[i], base_addr);
		arc     = arcBank->waveGroups[i];
		Jac_InitHeap(&arc->heap);
		arc->heap.startAddress = 0;

		for (j = 0; j < arc->waveCount; j++) {
			PTconvert((void**)&arc->waves[j], base_addr);
		}
	}

	for (i = 0; i < group->count; i++) {
		PTconvert((void**)&group->scenes[i], base_addr);
		scene = group->scenes[i];
		PTconvert((void**)&scene->cdf, base_addr);
		PTconvert((void**)&scene->cex, base_addr);
		PTconvert((void**)&scene->cst, base_addr);

		cdf = scene->cdf;
		if (cdf && cdf->magic == 'C-DF') {
			for (j = 0; j < cdf->count; j++) {
				PTconvert((void**)&cdf->waveIDs[j], base_addr);
				Jac_InitHeap(&cdf->waveIDs[j]->heap);
				cdf->waveIDs[j]->heap.startAddress = 0;
			}
		}

		cex = scene->cex;
		if (cex && cex->magic == 'C-EX') {
			for (j = 0; j < cex->count; j++) {
				PTconvert((void**)&cex->waveIDs[j], base_addr);
				Jac_InitHeap(&cex->waveIDs[j]->heap);
				cex->waveIDs[j]->heap.startAddress = 0;
			}
		}

		cst = scene->cst;
		if (cst && cst->magic == 'C-ST') {
			for (j = 0; j < cst->count; j++) {
				PTconvert((void**)&cst->waveIDs[j], base_addr);
				Jac_InitHeap(&cst->waveIDs[j]->heap);
				cst->waveIDs[j]->heap.startAddress = 0;
			}
		}
	}
	return CGRP_ARRAY[0];
}

/*
 * --INFO--
 * Address:	........
 * Size:	000030
 */
void GetSound_Test(u32 id)
{
	// UNUSED FUNCTION
}

/*
 * --INFO--
 * Address:	8000C4E0
 * Size:	000084
 */
BOOL Wavegroup_Regist(void* wsysData, u32 id)
{
	Wsys_* wsys = (Wsys_*)wsysData;
	Jac_WsConnectTableSet(wsys->globalID, id);
	wavegroup[id] = Wave_Test((u8*)wsys);
	wavearc[id]   = wsys->waveArcBank;

	if (wavegroup[id] == NULL) {
		return FALSE;
	}
	wavegroup[id]->_04 = 0;
	return TRUE;
}

/*
 * --INFO--
 * Address:	8000C580
 * Size:	00002C
 */
void Wavegroup_Init()
{
	for (int i = 0; i < WAVEGROUP_SIZE; ++i) {
		wavegroup[i] = NULL;
	}
}

/*
 * --INFO--
 * Address:	8000C5C0
 * Size:	000064
 */
CtrlGroup_* WaveidToWavegroup(u32 param_1, u32 param_2)
{
	u16 virtID = param_1 >> 16;
	u16 index;
	u16* REF_virtID = &virtID;

	if (virtID == 0xFFFF) {
		index = param_2;
	} else {
		index = Jac_WsVirtualToPhysical(virtID);
	}

	return index >= WAVEGROUP_SIZE ? NULL : wavegroup[index];
}

/*
 * --INFO--
 * Address:	8000C640
 * Size:	00008C
 */
static BOOL __WaveScene_Set(u32 waveIndex, u32 ctrlIndex, BOOL doSet)
{
	u32* REF_param_1;
	u32* REF_param_2;

	CtrlGroup_* group;

	REF_param_1 = &waveIndex;
	if (waveIndex >= WAVEGROUP_SIZE) {
		return FALSE;
	}
	if (!(group = wavegroup[waveIndex])) {
		return FALSE;
	}
	REF_param_2 = &ctrlIndex;
	if (ctrlIndex >= group->count) {
		return FALSE;
	}
	return Jac_SceneSet(wavearc[waveIndex], group, ctrlIndex, doSet);
}

/*
 * --INFO--
 * Address:	8000C6E0
 * Size:	000024
 */
BOOL WaveScene_Set(u32 waveIndex, u32 ctrlIndex)
{
	return __WaveScene_Set(waveIndex, ctrlIndex, TRUE);
}

/*
 * --INFO--
 * Address:	8000C720
 * Size:	000024
 */
BOOL WaveScene_Load(u32 waveIndex, u32 ctrlIndex)
{
	return __WaveScene_Set(waveIndex, ctrlIndex, FALSE);
}

/*
 * --INFO--
 * Address:	8000C760
 * Size:	000074
 */
static void __WaveScene_Close(u32 waveIndex, u32 ctrlIndex, BOOL param_3)
{
	u32* REF_param_1;
	u32* REF_param_2;

	CtrlGroup_* group;

	REF_param_1 = &waveIndex;
	if (waveIndex >= WAVEGROUP_SIZE) {
		return;
	}
	if (group = wavegroup[waveIndex]) {
		REF_param_2 = &ctrlIndex;
		if (ctrlIndex < group->count) {
			Jac_SceneClose(wavearc[waveIndex], group, ctrlIndex, param_3);
		}
	}
}

/*
 * --INFO--
 * Address:	8000C7E0
 * Size:	000024
 */
void WaveScene_Close(u32 waveIndex, u32 ctrlIndex)
{
	__WaveScene_Close(waveIndex, ctrlIndex, TRUE);
}

/*
 * --INFO--
 * Address:	8000C820
 * Size:	000024
 */
void WaveScene_Erase(u32 waveIndex, u32 ctrlIndex)
{
	__WaveScene_Close(waveIndex, ctrlIndex, FALSE);
}
