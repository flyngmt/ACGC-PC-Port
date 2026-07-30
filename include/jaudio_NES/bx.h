#ifndef _JAUDIO_BX_H
#define _JAUDIO_BX_H

// This is an invented header containing several structs related to the file structure of pikibank.bx

#include "types.h"
#include "jaudio_NES/heapctrl.h"

#define BANK_INST_COUNT        (0xF0)
#define BANK_TEST_INST_COUNT   (0x80)
#define BANK_TEST_VOICE_OFFSET (BANK_TEST_INST_COUNT)
#define BANK_TEST_VOICE_COUNT  (0x64)
#define BANK_TEST_PERC_OFFSET  (BANK_TEST_INST_COUNT + BANK_TEST_VOICE_COUNT)
#define BANK_TEST_PERC_COUNT   (0x0C)

typedef struct Bank_ Bank_;
typedef struct Ibnk_ Ibnk_;
typedef struct Inst_ Inst_;
typedef struct Perc_ Perc_;
typedef struct Voice_ Voice_;
typedef struct Sense_ Sense_;
typedef struct Rand_ Rand_;
typedef struct Osc_ Osc_;
typedef struct Oscbuf_ Oscbuf_;

typedef struct Vmap_ Vmap_;
typedef struct InstKeymap_ InstKeymap_;
typedef struct PercKeymap_ PercKeymap_;

// these type names are confirmed:
typedef struct WaveArchiveBank_ WaveArchiveBank_;
typedef struct CtrlGroup_ CtrlGroup_;
typedef struct Ctrl_ Ctrl_;
typedef struct WaveArchive_ WaveArchive_;
typedef struct Wave_ Wave_;

// these type names are fabricated, feel free to rename if found:
typedef struct Wsys_ Wsys_;
typedef struct SCNE_ SCNE_;
typedef struct WaveID_ WaveID_;

//////////////////////////////////////////////////////////
////////////////////// BANK STRUCTS //////////////////////

struct Bank_ {
	int mMagic; // _00 | 'BANK'
	union {     // _04 | Can point to INST, VOICE, PERC.
		// There's no way this was actually an anonymous union, as this only became a feature
		// of the C programming language in C11. However, it does make the code nicer to read.
		Inst_* mInstruments[BANK_INST_COUNT];
		Voice_* mVoices[BANK_INST_COUNT];
		Perc_* mPercs[BANK_INST_COUNT];
	};
};

struct Ibnk_ {
	int magic;                            // _00 | 'IBNK'
	u32 _04;                              // _04
	u32 _08;                              // _08
	int _0C;                              // _0C
	struct WaveArchiveBank_* waveArcBank; // _10
	u8 _14[0x20 - 0x14];                  // _14
	Bank_ bank;                           // _20
};

/**
 * @brief This is an invented type of an unknown name.
 *
 * @note Size: 0x10.
 */
struct Vmap_ {
	u8 mBaseVelocity; // _00
	s16 mWsysID;      // _04
	s16 mWaveID;      // _06
	f32 mVolume;      // _08
	f32 mPitch;       // _0C
};

/**
 * @brief This is an invented type of an unknown name.
 *
 * @note Size: 0x10.
 */
struct InstKeymap_ {
	u8 mBaseKey;        // _00
	u32 mVelocityCount; // _04
#ifdef TARGET_PC
	Vmap_** mVelocities;
#else
	Vmap_* mVelocities[2]; // _08
#endif
};

/**
 * @brief This is an invented type of an unknown name.
 *
 * @note Size: 0x18.
 */
struct PercKeymap_ {
	f32 mPitch;         // _00
	f32 mVolume;        // _04
#ifdef TARGET_PC
	Rand_* _08;         // _08, first random effect
	Rand_* _0C;         // _0C, second random effect
#else
	void* _08;          // _08, pointer type unknown, but gets hit by PTconvert in Bank_Test
	void* _0C;          // _0C, pointer type unknown, but gets hit by PTconvert in Bank_Test
#endif
	int mVelocityCount; // _10
#ifdef TARGET_PC
	Vmap_** mVelocities;
#else
	Vmap_* mVelocities[2]; // _14
#endif
};

struct Sense_ {
	u8 id;        // _00
	u8 type;      // _01
	u8 threshold; // _02
	f32 min;      // _04
	f32 max;      // _08
};

struct Osc_ {
	u8 mode;               // _00
	f32 rate;              // _04
	s16* attackVecOffset;  // _08
	s16* releaseVecOffset; // _0C
	f32 width;             // _10
	f32 vertex;            // _14
};

/**
 * @note Size: 0x18.
 */
struct Oscbuf_ {
	u8 state;         // _00
	u8 curveType;     // _01
	u16 tableIndex;   // _02
	f32 timeCounter;  // _04
	f32 value;        // _08
	f32 targetValue;  // _0C
	f32 deltaRate;    // _10
	u16 releaseParam; // _14
};

/**
 * @note Size: 0x40.
 */
struct Inst_ {
	int mMagic;                  // _00 | 'INST'
	u32 mFlag;                   // _04
	f32 mFreqMultiplier;         // _08
	f32 mGainMultiplier;         // _0C
	Osc_* mOscillators[2];       // _10
	Rand_* mEffects[2];          // _18
	Sense_* mSensors[2];         // _20
	int mKeyRegionCount; // _28
#ifdef TARGET_PC
	InstKeymap_** mKeyRegions;
#else
	InstKeymap_* mKeyRegions[5]; // _2C
#endif
};

struct Voice_ {
	u8 _00[0x8]; // _00, unknown
	int size;    // _08, count of whatever's at 0xC
#ifdef TARGET_PC
	void** _0C;
#else
	void* _0C[1]; // _0C, unsure of length of array or type
#endif
};

struct Perc_ {
	int mMagic;                    // _00 | 'PER2' (or 'PERC'?)
	u8 _04[0x84];                  // _04, unknown
	PercKeymap_* mKeyRegions[128]; // _88
	s8 _288[128];                  // _288
	u16 _308[128];                 // _308
};

struct Rand_ {
	u8 id;               // _00
	f32 value;           // _04
	f32 range;           // _08
	u8 _0C[0x10 - 0x0C]; // _0C
};

struct Pmap_ {
	Rand_* _00; // _00
	int _04;    // _04
};

//////////////////////////////////////////////////////////
////////////////////// WAVE STRUCTS //////////////////////

// Name fabricated, but makes sense in line with Ibnk_
struct Wsys_ {
	int magic;                     // _00, 'WSYS'
	int size;                      // _04
	int globalID;                  // _08
	int _0C;                       // _0C, unused?
	WaveArchiveBank_* waveArcBank; // _10
	CtrlGroup_* ctrlGroup;         // _14
};

struct WaveArchiveBank_ {
	int magic;                   // _00, 'WINF'
	int count;                   // _04, same count as CtrlGroup_
	WaveArchive_* waveGroups[1]; // _08, array size variable
};

struct CtrlGroup_ {
	int magic;        // _00, 'WBCT'
	u32 _04;          // _04, unknown
	int count;        // _08, same count as WaveArchiveBank_
	SCNE_* scenes[1]; // _0C, array size variable
};

// Name fabricated based on magic ID.
struct SCNE_ {
	int magic;  // _00, 'SCNE'
	u32 _04;    // _04
	u32 _08;    // _08
	Ctrl_* cdf; // _0C
	Ctrl_* cex; // _10
	Ctrl_* cst; // _14
	int _18[1]; // _18, variable size?
};

struct Ctrl_ {
	int magic;           // _00, 'C-DF', 'C-EX' or 'C-ST'
	int count;           // _04
	WaveID_* waveIDs[1]; // _08, array size variable
};

// Name fabricated from Xayr's tools.
struct WaveID_ {
	u32 id;         // _00, split into sound id and ws id
	jaheap_ heap;   // _04
	u32 loadStatus; // _30
	Wave_* data;    // _34
};

struct WaveArchive_ {
	char filePath[0x40]; // _00, might be smaller, unsure
	jaheap_ heap;        // _40
	u32 fileLoadStatus;  // _6C
	int waveCount;       // _70
	Wave_* waves[1];     // _74, array size variable
};

/**
 * @brief File data, size unknown
 */
struct Wave_ {
	u8 _00;                // _00
	u8 compBlockIdx;       // _01
	u8 key;                // _02
	f32 _04;               // _04
	int srcAddress;        // _08
	int length;            // _0C
	s32 isLooping;         // _10
	s32 loopAddress;       // _14
	s32 loopStartPosition; // _18
	s32 _1C;               // _1C
	s16 loopYN1;           // _20
	s16 loopYN2;           // _22
	u32* fileLoadStatus;   // _24, set to dolphin/dvd.h 'DVD_RESULT_*' defines
};

#endif
