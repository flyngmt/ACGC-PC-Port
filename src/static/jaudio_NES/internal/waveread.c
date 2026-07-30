#include "jaudio_NES/waveread.h"

#include "jaudio_NES/connect.h"
#include "jaudio_NES/heapctrl.h"
#include "jaudio_NES/bx.h"

#ifdef TARGET_PC
#include <stdlib.h>
#include <string.h>
#endif

#define WAVEARC_SIZE   (0x100)
#define WAVEGROUP_SIZE (0x100)

static WaveArchiveBank_* wavearc[WAVEARC_SIZE];
static CtrlGroup_* wavegroup[WAVEGROUP_SIZE];
CtrlGroup_* CGRP_ARRAY[16];

#ifdef TARGET_PC
static WaveArchiveBank_* pc_wavearc;
static u32 pc_wsys_id;

static u16 read_be16(const u8* data)
{
	return (u16)((u16)data[0] << 8 | data[1]);
}

static u32 read_be32(const u8* data)
{
	return (u32)data[0] << 24 | (u32)data[1] << 16 | (u32)data[2] << 8 | data[3];
}

static f32 read_be_f32(const u8* data)
{
	u32 bits = read_be32(data);
	f32 value;
	memcpy(&value, &bits, sizeof(value));
	return value;
}

static const u8* wsys_at(const u8* data, u32 size, u32 offset, u32 needed)
{
	if (offset == 0 || offset > size || needed > size - offset) {
		return NULL;
	}
	return data + offset;
}

static Wave_* convert_wave(const u8* data, u32 size, u32 offset)
{
	const u8* raw = wsys_at(data, size, offset, 0x28);
	if (raw == NULL) {
		return NULL;
	}

	Wave_* wave = calloc(1, sizeof(*wave));
	if (wave == NULL) {
		return NULL;
	}
	wave->_00 = raw[0];
	wave->compBlockIdx = raw[1];
	wave->key = raw[2];
	wave->_04 = read_be_f32(raw + 0x04);
	wave->srcAddress = (s32)read_be32(raw + 0x08);
	wave->length = (s32)read_be32(raw + 0x0c);
	wave->isLooping = (s32)read_be32(raw + 0x10);
	wave->loopAddress = (s32)read_be32(raw + 0x14);
	wave->loopStartPosition = (s32)read_be32(raw + 0x18);
	wave->_1C = (s32)read_be32(raw + 0x1c);
	wave->loopYN1 = (s16)read_be16(raw + 0x20);
	wave->loopYN2 = (s16)read_be16(raw + 0x22);
	wave->fileLoadStatus = NULL;
	return wave;
}

static WaveArchive_* convert_wave_archive(const u8* data, u32 size, u32 offset)
{
	const u8* raw = wsys_at(data, size, offset, 0x78);
	if (raw == NULL) {
		return NULL;
	}

	u32 count = read_be32(raw + 0x70);
	if (count > (size - offset - 0x74) / sizeof(u32)) {
		return NULL;
	}
	size_t alloc_size = sizeof(WaveArchive_);
	if (count > 1) {
		alloc_size += (count - 1) * sizeof(Wave_*);
	}
	WaveArchive_* archive = calloc(1, alloc_size);
	if (archive == NULL) {
		return NULL;
	}
	memcpy(archive->filePath, raw, sizeof(archive->filePath));
	archive->filePath[sizeof(archive->filePath) - 1] = '\0';
	Jac_InitHeap(&archive->heap);
	archive->heap.startAddress = 0;
	archive->fileLoadStatus = read_be32(raw + 0x6c);
	archive->waveCount = count;
	for (u32 i = 0; i < count; ++i) {
		archive->waves[i] = convert_wave(data, size, read_be32(raw + 0x74 + i * 4));
		if (archive->waves[i] == NULL) {
			return NULL;
		}
	}
	return archive;
}

static WaveArchiveBank_* convert_wave_bank(const u8* data, u32 size, u32 offset)
{
	const u8* raw = wsys_at(data, size, offset, 8);
	if (raw == NULL || read_be32(raw) != 'WINF') {
		return NULL;
	}
	u32 count = read_be32(raw + 4);
	if (count > (size - offset - 8) / sizeof(u32)) {
		return NULL;
	}
	size_t alloc_size = sizeof(WaveArchiveBank_);
	if (count > 1) {
		alloc_size += (count - 1) * sizeof(WaveArchive_*);
	}
	WaveArchiveBank_* bank = calloc(1, alloc_size);
	if (bank == NULL) {
		return NULL;
	}
	bank->magic = 'WINF';
	bank->count = count;
	for (u32 i = 0; i < count; ++i) {
		bank->waveGroups[i] = convert_wave_archive(data, size, read_be32(raw + 8 + i * 4));
		if (bank->waveGroups[i] == NULL) {
			return NULL;
		}
	}
	return bank;
}

static WaveID_* convert_wave_id(const u8* data, u32 size, u32 offset)
{
	const u8* raw = wsys_at(data, size, offset, 0x38);
	if (raw == NULL) {
		return NULL;
	}
	WaveID_* wave = calloc(1, sizeof(*wave));
	if (wave == NULL) {
		return NULL;
	}
	wave->id = read_be32(raw);
	Jac_InitHeap(&wave->heap);
	wave->heap.startAddress = 0;
	wave->loadStatus = read_be32(raw + 0x30);
	u32 data_offset = read_be32(raw + 0x34);
	wave->data = data_offset == UINT32_MAX ? (Wave_*)UINTPTR_MAX : NULL;
	return wave;
}

static Ctrl_* convert_ctrl(const u8* data, u32 size, u32 offset)
{
	if (offset == 0) {
		return NULL;
	}
	const u8* raw = wsys_at(data, size, offset, 8);
	if (raw == NULL) {
		return NULL;
	}
	u32 count = read_be32(raw + 4);
	if (count > (size - offset - 8) / sizeof(u32)) {
		return NULL;
	}
	size_t alloc_size = sizeof(Ctrl_);
	if (count > 1) {
		alloc_size += (count - 1) * sizeof(WaveID_*);
	}
	Ctrl_* ctrl = calloc(1, alloc_size);
	if (ctrl == NULL) {
		return NULL;
	}
	ctrl->magic = read_be32(raw);
	ctrl->count = count;
	for (u32 i = 0; i < count; ++i) {
		ctrl->waveIDs[i] = convert_wave_id(data, size, read_be32(raw + 8 + i * 4));
		if (ctrl->waveIDs[i] == NULL) {
			return NULL;
		}
	}
	return ctrl;
}

static SCNE_* convert_scene(const u8* data, u32 size, u32 offset)
{
	const u8* raw = wsys_at(data, size, offset, 0x18);
	if (raw == NULL || read_be32(raw) != 'SCNE') {
		return NULL;
	}
	u32 child_count = read_be32(raw + 8);
	if (child_count > (size - offset - 0x18) / sizeof(u32)) {
		return NULL;
	}
	size_t alloc_size = sizeof(SCNE_);
	if (child_count > 1) {
		alloc_size += (child_count - 1) * sizeof(u32);
	}
	SCNE_* scene = calloc(1, alloc_size);
	if (scene == NULL) {
		return NULL;
	}
	scene->magic = 'SCNE';
	scene->_04 = read_be32(raw + 4);
	scene->_08 = child_count;
	scene->cdf = convert_ctrl(data, size, read_be32(raw + 0x0c));
	scene->cex = convert_ctrl(data, size, read_be32(raw + 0x10));
	scene->cst = convert_ctrl(data, size, read_be32(raw + 0x14));
	for (u32 i = 0; i < child_count; ++i) {
		scene->_18[i] = read_be32(raw + 0x18 + i * 4);
	}
	return scene;
}

static CtrlGroup_* convert_ctrl_group(const u8* data, u32 size, u32 offset)
{
	const u8* raw = wsys_at(data, size, offset, 0x0c);
	if (raw == NULL || read_be32(raw) != 'WBCT') {
		return NULL;
	}
	u32 count = read_be32(raw + 8);
	if (count > (size - offset - 0x0c) / sizeof(u32)) {
		return NULL;
	}
	size_t alloc_size = sizeof(CtrlGroup_);
	if (count > 1) {
		alloc_size += (count - 1) * sizeof(SCNE_*);
	}
	CtrlGroup_* group = calloc(1, alloc_size);
	if (group == NULL) {
		return NULL;
	}
	group->magic = 'WBCT';
	group->_04 = read_be32(raw + 4);
	group->count = count;
	for (u32 i = 0; i < count; ++i) {
		group->scenes[i] = convert_scene(data, size, read_be32(raw + 0x0c + i * 4));
		if (group->scenes[i] == NULL) {
			return NULL;
		}
	}
	return group;
}
#endif

/*
 * --INFO--
 * Address:	8000C200
 * Size:	000038
 */

#ifndef TARGET_PC
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
	if (read_be32(data) != 'WSYS') {
		return NULL;
	}
	u32 size = read_be32(data + 4);
	if (size < 0x18) {
		return NULL;
	}
	pc_wsys_id = read_be32(data + 8);
	pc_wavearc = convert_wave_bank(data, size, read_be32(data + 0x10));
	CtrlGroup_* group = convert_ctrl_group(data, size, read_be32(data + 0x14));
	if (pc_wavearc == NULL || group == NULL) {
		return NULL;
	}
	CGRP_ARRAY[0] = group;
	return group;
#else
    u32 base_addr = (u32)data;
	CtrlGroup_* group;
	SCNE_* scene;
	Ctrl_* cst;
	Ctrl_* cdf;
	Ctrl_* cex;
	u32 i;
    u32 j;
	WaveArchiveBank_* arcBank;
	WaveArchive_* arc;

	PTconvert((void**)&((Wsys_*)data)->waveArcBank, base_addr);
	PTconvert((void**)&((Wsys_*)data)->ctrlGroup, base_addr);
	arcBank       = *(WaveArchiveBank_**)(data + 0x10);
	group         = *(CtrlGroup_**)(data + 0x14);
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
#endif
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
#ifdef TARGET_PC
	wavegroup[id] = Wave_Test((u8*)wsysData);
	if (wavegroup[id] == NULL) {
		return FALSE;
	}
	Jac_WsConnectTableSet(pc_wsys_id, id);
	wavearc[id] = pc_wavearc;
#else
	Wsys_* wsys = (Wsys_*)wsysData;
	Jac_WsConnectTableSet(wsys->globalID, id);
	wavegroup[id] = Wave_Test((u8*)wsys);
	wavearc[id]   = wsys->waveArcBank;

	if (wavegroup[id] == NULL) {
		return FALSE;
	}
#endif
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
