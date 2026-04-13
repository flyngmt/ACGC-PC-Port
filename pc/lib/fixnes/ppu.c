/*
 * Copyright (C) 2017 - 2020 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include "mapper.h"
#include "mem.h"
#include "cpu.h"
#include "ppu.h"

//certain optimizations were taken from nestopias ppu code,
//thanks to the people from there for all that

//sprite byte 2
#define PPU_SPRITE_PRIO (1<<5)
#define PPU_SPRITE_FLIP_X (1<<6)
#define PPU_SPRITE_FLIP_Y (1<<7)

//2000
#define PPU_INC_AMOUNT (1<<2)
#define PPU_SPRITE_ADDR (1<<3)
#define PPU_BACKGROUND_ADDR (1<<4)
#define PPU_SPRITE_8_16 (1<<5)
#define PPU_FLAG_NMI (1<<7)

//2001
#define PPU_GRAY (1<<0)
#define PPU_BG_8PX (1<<1)
#define PPU_SPRITE_8PX (1<<2)
#define PPU_BG_ENABLE (1<<3)
#define PPU_SPRITE_ENABLE (1<<4)

//2002
#define PPU_FLAG_OVERFLOW (1<<5)
#define PPU_FLAG_SPRITEZERO (1<<6)
#define PPU_FLAG_VBLANK (1<<7)

#define PPU_VRAM_HORIZONTAL_MASK 0x41F
#define PPU_VRAM_VERTICAL_MASK (~PPU_VRAM_HORIZONTAL_MASK)

#define PPU_DEBUG_ULTRA 0

#define PPU_DEBUG_VSYNC 0

//set or used externally
bool ppu4Screen = false;
//all for mmc5
bool ppuMapper5 = false;
bool ppu816Sprite = false;
bool ppuInFrame = false;

//from main.c
#ifdef COL_32BIT
extern uint32_t textureImage[TEX_DOTS*TEX_LINES];
#define TEXCOL_WHITE 0xFFFFFFFF
#ifdef COL_TEX_BSWAP
#define TEXCOL_BLACK 0xFF000000
#define COL_LS1 0
#define COL_LS2 8
#define COL_LS3 16
#define COL_LS4 24
#else //case COL_TEX_NORMAL
#define TEXCOL_BLACK 0x000000FF
#define COL_LS1 24
#define COL_LS2 16
#define COL_LS3 8
#define COL_LS4 0
#endif //end COL_TEX_BSWAP
#else //COL_16BIT
extern uint16_t textureImage[TEX_DOTS*TEX_LINES];
#define TEXCOL_WHITE 0xFFFF
#define TEXCOL_BLACK 0x0000
#ifdef COL_TEX_BSWAP
#define COL_LS1 0
#define COL_LS2 5
#define COL_LS3 11
#else //case COL_TEX_NORMAL
#define COL_LS1 11
#define COL_LS2 5
#define COL_LS3 0
#endif //end COL_TEX_BSWAP
#endif //end COL_32BIT
extern bool nesPause;
extern bool ppuDebugPauseFrame;
extern bool doOverscan;

static uint8_t ppuDoSprites(uint8_t color, uint16_t dot);

// BMF Final 2
static const uint8_t PPU_Pal[192] =
{
    0x52, 0x52, 0x52, 0x00, 0x00, 0x80, 0x08, 0x00, 0x8A, 0x2C, 0x00, 0x7E, 0x4A, 0x00, 0x4E, 0x50, 0x00, 0x06, 0x44, 0x00, 0x00, 0x26, 0x08, 0x00, 
    0x0A, 0x20, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x32, 0x00, 0x00, 0x26, 0x0A, 0x00, 0x1C, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xA4, 0xA4, 0xA4, 0x00, 0x38, 0xCE, 0x34, 0x16, 0xEC, 0x5E, 0x04, 0xDC, 0x8C, 0x00, 0xB0, 0x9A, 0x00, 0x4C, 0x90, 0x18, 0x00, 0x70, 0x36, 0x00, 
    0x4C, 0x54, 0x00, 0x0E, 0x6C, 0x00, 0x00, 0x74, 0x00, 0x00, 0x6C, 0x2C, 0x00, 0x5E, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xFF, 0xFF, 0xFF, 0x4C, 0x9C, 0xFF, 0x7C, 0x78, 0xFF, 0xA6, 0x64, 0xFF, 0xDA, 0x5A, 0xFF, 0xF0, 0x54, 0xC0, 0xF0, 0x6A, 0x56, 0xD6, 0x86, 0x10, 
    0xBA, 0xA4, 0x00, 0x76, 0xC0, 0x00, 0x46, 0xCC, 0x1A, 0x2E, 0xC8, 0x66, 0x34, 0xC2, 0xBE, 0x3A, 0x3A, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xFF, 0xFF, 0xFF, 0xB6, 0xDA, 0xFF, 0xC8, 0xCA, 0xFF, 0xDA, 0xC2, 0xFF, 0xF0, 0xBE, 0xFF, 0xFC, 0xBC, 0xEE, 0xFA, 0xC2, 0xC0, 0xF2, 0xCC, 0xA2, 
    0xE6, 0xDA, 0x92, 0xCC, 0xE6, 0x8E, 0xB8, 0xEE, 0xA2, 0xAE, 0xEA, 0xBE, 0xAE, 0xE8, 0xE2, 0xB0, 0xB0, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
} ;

static const uint8_t ppuOddArrNTSC[2] = { 0, 1 };
static const uint8_t ppuOddArrPAL[2] = { 0, 0 };

typedef void (*spriteEvalBFunc)(uint16_t line);

static struct
{
	const uint8_t *Pal;
	const uint8_t *OddArr;
	spriteEvalBFunc spriteEvalB;
	uint8_t SprLUT[0x100];
#ifdef COL_32BIT
	uint32_t BGRLUT[0x200];
#ifdef DISPLAY_PPUWRITES
	uint32_t highlightcolor;
#endif
#else //COL_16BIT
	uint16_t BGRLUT[0x200];
#ifdef DISPLAY_PPUWRITES
	uint16_t highlightcolor;
#endif
#endif //end COL_32BIT
	uint8_t TILELUT[0x400][4];
	uint16_t PALRAM2[0x20];
	uint16_t NameTbl[4];
	uint8_t VRAM[0x1000];
	uint8_t *VRAMBank0Ptr, *VRAMBank1Ptr,
			*VRAMBank2Ptr, *VRAMBank3Ptr;
	uint8_t OAM[0x100];
	uint8_t OAM2[0x20];
	uint8_t *OAM2Ptr;
	uint8_t PALRAM[0x20];
	uint8_t BGTiles[16];
	uint8_t Reg[8];
	uint8_t OddNum;
	uint16_t RunCycles;
	uint16_t curLine;
	uint16_t LinesTotal;
	uint16_t PreRenderLine;
	uint16_t curDot;
	uint16_t VramAddr;
	uint16_t TmpVramAddr;
	uint16_t NextAddr;
	uint16_t NextTile;
	uint8_t NextByte;
	uint8_t VramReadBuf;
	uint8_t OAMpos;
	uint8_t OAM2pos;
	uint8_t OAMcpPos;
	uint8_t OAMzSpritePos;
	uint8_t FineXScroll;
	uint8_t SpriteOAM2Pos;
	uint8_t BGRegA;
	uint8_t BGRegB;
	uint8_t BGAttribReg;
	uint8_t BGIndex;
	uint8_t lastVal;
	uint8_t CurSpriteLn;
	uint8_t CurSpriteIndex;
	uint8_t CurSpriteByte2;
	uint8_t CurSpriteByte3;
	uint8_t TmpOAMVal;
	uint8_t sprEvalNumLines;
	uint8_t sprEvalLineAnd;
	bool NextHasZSprite;
	bool FrameDone;
	bool TmpWrite;
	bool NMIallowed;
	bool NMITriggered;
	bool VBlankFlagCleared;
	bool VBlankClearCycle;
	bool CurNMIStat;
	bool OddFrame;
	bool ReadReg2;
	bool DoOverscan;
	bool BGEnable;
	bool SprEnable;
	bool DoOAMBug;
	bool reqReset;
#ifdef DISPLAY_PPUWRITES
	bool ppuwrite;
#endif
} ppu;

static void ppuSetVRAMBankPtr()
{
	ppu.VRAMBank0Ptr = ppu.VRAM+ppu.NameTbl[0];
	ppu.VRAMBank1Ptr = ppu.VRAM+ppu.NameTbl[1];
	ppu.VRAMBank2Ptr = ppu.VRAM+ppu.NameTbl[2];
	ppu.VRAMBank3Ptr = ppu.VRAM+ppu.NameTbl[3];
}

//normal drawing dot 0-340
#define PPU_OFF (DOTS*1) //drawing off dot 341-681
#define PPU_PRE (DOTS*2) //pre-render dot 682-1022
#define PPU_PRE_OFF (DOTS*3) //pre-render off dot 1023-1363
#define PPU_L241 (DOTS*4) //line 241 dot 1364-1704
#define PPU_IDLE (DOTS*5) //idle dot 1705-2045

extern bool nesEmuNSFPlayback;

static uint16_t ppuSetDotType(uint16_t dot, uint16_t line)
{
	dot %= DOTS;
	if(line < VISIBLE_LINES)
	{
		if(nesEmuNSFPlayback)
			dot += PPU_IDLE;
		else if(ppu.Reg[1] & (PPU_BG_ENABLE | PPU_SPRITE_ENABLE))
			dot += 0; //unchanged
		else
			dot += PPU_OFF;
	}
	else if(line == ppu.PreRenderLine)
	{
		if(nesEmuNSFPlayback)
			dot += PPU_PRE_OFF;
		else if(ppu.Reg[1] & (PPU_BG_ENABLE | PPU_SPRITE_ENABLE))
			dot += PPU_PRE;
		else
			dot += PPU_PRE_OFF;
	}
	else if(line == 241)
		dot += PPU_L241;
	else
		dot += PPU_IDLE;
	return dot;
}

static void ppuSetSprite816vals()
{
	if(ppu.Reg[0] & PPU_SPRITE_8_16)
	{
		ppu.sprEvalNumLines = 16;
		ppu.sprEvalLineAnd = 15;
		ppu816Sprite = true;
	}
	else
	{
		ppu.sprEvalNumLines = 8;
		ppu.sprEvalLineAnd = 7;
		ppu816Sprite = false;
	}
}

static void spriteEvalB_P1(uint16_t line);
static void spriteEvalB_P2(uint16_t line);
static void spriteEvalB_P3(uint16_t line);
static void spriteEvalB_P4(uint16_t line);
static void spriteEvalB_P5(uint16_t line);
static void spriteEvalB_P6(uint16_t line);
static void spriteEvalB_P7(uint16_t line);
static void spriteEvalB_P8(uint16_t line);
static void spriteEvalB_P9(uint16_t line);

extern bool nesPAL;

void ppuInit()
{
	memset(ppu.PALRAM2,0,0x40);
	memset(ppu.NameTbl,0,8);
	memset(ppu.VRAM,0,0x1000);
	memset(ppu.SprLUT,0,0x100);
	ppuSetVRAMBankPtr();
	memset(ppu.OAM,0,0x100);
	memset(ppu.OAM2,0xFF,0x20);
	ppu.OAM2Ptr = ppu.OAM2;
	memset(ppu.PALRAM,0,0x20);
	memset(ppu.BGTiles,0,0x10);
	memset(ppu.Reg,0,8);
	ppuSetSprite816vals();
	ppu.Pal = PPU_Pal;
	//ppuCycles = 0;
	//start out being in vblank
	ppu.Reg[2] |= PPU_FLAG_VBLANK;
	ppu.spriteEvalB = spriteEvalB_P1;
	ppu.LinesTotal = nesPAL ? LINES_PAL : LINES_NTSC;
	ppu.PreRenderLine = ppu.LinesTotal - 1;
	ppu.curLine = ppu.LinesTotal - 11;
	ppu.curDot = ppuSetDotType(0, ppu.curLine);
	ppu.VramAddr = 0;
	ppu.TmpVramAddr = 0;
	ppu.NextAddr = 0;
	ppu.NextTile = 0;
	ppu.NextByte = 0;
	ppu.VramReadBuf = 0;
	ppu.OAMpos = 0;
	ppu.OAM2pos = 0;
	ppu.OAMcpPos = 0;
	ppu.OAMzSpritePos = 0;
	ppu.FineXScroll = 0;
	ppu.BGRegA = 0;
	ppu.BGRegB = 0;
	ppu.BGAttribReg = 0;
	ppu.BGIndex = 0;
	ppu.lastVal = 0;
	ppu.CurSpriteLn = 0;
	ppu.CurSpriteIndex = 0;
	ppu.CurSpriteByte2 = 0;
	ppu.CurSpriteByte3 = 0;
	ppu.TmpOAMVal = 0xFF;
	ppu.NextHasZSprite = false;
	ppu.FrameDone = false;
	ppu.TmpWrite = false;
	ppu.NMIallowed = false;
	ppu.NMITriggered = false;
	ppu.VBlankFlagCleared = false;
	ppu.VBlankClearCycle = false;
	ppu.CurNMIStat = false;
	ppu.OddFrame = false;
	ppu.ReadReg2 = false;
	ppu.DoOverscan = false;
	ppu.BGEnable = false;
	ppu.SprEnable = false;
	ppu.reqReset = false;
#ifdef DISPLAY_PPUWRITES
	ppu.ppuwrite = false;
#endif
	//only do OAM Bug on NTSC NES games
	ppu.DoOAMBug = !nesEmuNSFPlayback && !nesPAL;
	//generate full BGR LUT
	uint8_t rtint = nesPAL ? (1<<6) : (1<<5);
	uint8_t gtint = nesPAL ? (1<<5) : (1<<6);
	uint8_t btint = (1<<7);
	int32_t i;
	for(i = 0; i < 0x200; i++)
	{
		uint8_t palpos = (i&0x3F)*3;
#ifdef COL_32BIT
		uint8_t r = ppu.Pal[palpos];
		uint8_t g = ppu.Pal[palpos+1];
		uint8_t b = ppu.Pal[palpos+2];
#else //COL_16BIT
		uint8_t r = ppu.Pal[palpos]>>3;
		uint8_t g = ppu.Pal[palpos+1]>>2;
		uint8_t b = ppu.Pal[palpos+2]>>3;
#endif
		if((i & 0xF) <= 0xD)
		{
			//reduce red
			if((i>>1) & btint) r = (uint8_t)(((float)r)*0.75f);
			if((i>>1) & gtint) r = (uint8_t)(((float)r)*0.75f);
			//reduce green
			if((i>>1) & rtint) g = (uint8_t)(((float)g)*0.75f);
			if((i>>1) & btint) g = (uint8_t)(((float)g)*0.75f);
			//reduce blue
			if((i>>1) & rtint) b = (uint8_t)(((float)b)*0.75f);
			if((i>>1) & gtint) b = (uint8_t)(((float)b)*0.75f);
		}
		//save new color into LUT
		ppu.BGRLUT[i] = 
#ifdef COL_32BIT
#ifdef COL_BGRA
			(b<<COL_LS1) //Blue
			| (g<<COL_LS2) //Green
			| (r<<COL_LS3) //Red
			| (0xFF<<COL_LS4); //Alpha
#ifdef DISPLAY_PPUWRITES
		ppu.highlightcolor = (0xFF<<COL_LS3)|(0xFF<<COL_LS4);
#endif
#else //RGBA
			(r<<COL_LS1) //Red
			| (g<<COL_LS2) //Green
			| (b<<COL_LS3) //Blue
			| (0xFF<<COL_LS4); //Alpha
#ifdef DISPLAY_PPUWRITES
		ppu.highlightcolor = (0xFF<<COL_LS1)|(0xFF<<COL_LS4);
#endif
#endif
#else //COL_16BIT
			(r<<COL_LS1) //Red
			| (g<<COL_LS2) //Green
			| (b<<COL_LS3); //Blue
#ifdef DISPLAY_PPUWRITES
		ppu.highlightcolor = (0x1F<<COL_LS1);
#endif
#endif
	}
	//tile LUT from nestopia
	for (i = 0; i < 0x400; ++i)
	{
		ppu.TILELUT[i][0] = (i & 0xC0) ? (i >> 6 & 0xC) | (i >> 6 & 0x3) : 0;
		ppu.TILELUT[i][1] = (i & 0x30) ? (i >> 6 & 0xC) | (i >> 4 & 0x3) : 0;
		ppu.TILELUT[i][2] = (i & 0x0C) ? (i >> 6 & 0xC) | (i >> 2 & 0x3) : 0;
		ppu.TILELUT[i][3] = (i & 0x03) ? (i >> 6 & 0xC) | (i >> 0 & 0x3) : 0;
	}
	ppu.RunCycles = nesPAL ? 0x46DB : 0x36DB;
	ppu.OddNum = 0;
	ppu.OddArr = nesPAL ? ppuOddArrPAL : ppuOddArrNTSC;
	ppu4Screen = false; //reg reset
	ppuInFrame = false; //we're in vsync
}

//tile load from nestopia
static void loadTiles()
{
	uint8_t* src[] =
	{
		ppu.TILELUT[ppu.BGRegA | (ppu.BGAttribReg & 3) << 8],
		ppu.TILELUT[ppu.BGRegB | (ppu.BGAttribReg & 3) << 8]
	};

	uint8_t* dst = ppu.BGTiles+ppu.BGIndex;
	ppu.BGIndex ^= 8;

	dst[0] = src[0][0];
	dst[1] = src[1][0];
	dst[2] = src[0][1];
	dst[3] = src[1][1];
	dst[4] = src[0][2];
	dst[5] = src[1][2];
	dst[6] = src[0][3];
	dst[7] = src[1][3];
}

static void setNextSpriteTileAddr(uint16_t line)
{
	uint8_t cSprLn = ppu.OAM2Ptr[0], cSprInd = ppu.OAM2Ptr[1], cSprB2 = ppu.OAM2Ptr[2];
	uint8_t cSpriteAdd = 0; //used to select which 8 by 16 tile
	uint8_t cSpriteY = (line - cSprLn)&ppu.sprEvalLineAnd;
	if(cSpriteY > 7) //8 by 16 select
	{
		cSpriteAdd = 16;
		cSpriteY &= 7;
	}
	uint16_t chrROMSpriteAdd = 0;
	if(ppu816Sprite)
	{
		chrROMSpriteAdd = ((cSprInd & 1) << 12);
		cSprInd &= ~1;
	}
	else if(ppu.Reg[0] & PPU_SPRITE_ADDR)
		chrROMSpriteAdd = 0x1000;
	if(cSprB2 & PPU_SPRITE_FLIP_Y)
	{
		cSpriteY ^= 7;
		if(ppu816Sprite)
			cSpriteAdd ^= 16; //8 by 16 select
	}
	ppu.NextTile = ((chrROMSpriteAdd+(cSprInd<<4)+cSpriteY+cSpriteAdd)&0xFFF) | chrROMSpriteAdd;
}

static void saveSprite(uint8_t p0, uint8_t p1)
{
	/* write processed values into internal draw buffer */
	if ((p0 | p1) && (ppu.OAM2Ptr[0] < VISIBLE_LINES)) //sprite contains data and is on a valid line, so process
	{
		uint8_t cSprB2 = ppu.OAM2Ptr[2];
		uint8_t cSprB3 = ppu.OAM2Ptr[3];
		//pixels
		uint8_t a = (cSprB2 & PPU_SPRITE_FLIP_X) ? 7 : 0;
		uint16_t p = (p0 >> 1 & 0x0055) | (p1 << 0 & 0x00AA) | (p0 << 8 & 0x5500) | (p1 << 9 & 0xAA00);
		uint8_t tmpCol[8];
		tmpCol[( a^=6 )] = ( p       ) & 0x3;
		tmpCol[( a^=2 )] = ( p >>= 2 ) & 0x3;
		tmpCol[( a^=6 )] = ( p >>= 2 ) & 0x3;
		tmpCol[( a^=2 )] = ( p >>= 2 ) & 0x3;
		tmpCol[( a^=7 )] = ( p >>= 2 ) & 0x3;
		tmpCol[( a^=2 )] = ( p >>= 2 ) & 0x3;
		tmpCol[( a^=6 )] = ( p >>= 2 ) & 0x3;
		tmpCol[( a^=2 )] = ( p >>= 2 );
		uint8_t tmpSpr = ((ppu.OAM2Ptr == ppu.OAM2 && ppu.NextHasZSprite) ? 0x20 : 0) | //is zero sprite
			((cSprB2 & PPU_SPRITE_PRIO) ? 0x40 : 0) | //priority
			(0x10 | (cSprB2&3)<<2); //palette
		//set to draw
		uint16_t i;
		for(i = 0; i < 8; i++)
		{
			uint16_t dstDot = cSprB3+i;
			if(dstDot > 0xFF) break;
			uint8_t col = tmpCol[i];
			if(col && !(ppu.SprLUT[dstDot]&0x80))
				ppu.SprLUT[dstDot] = 0x80 | tmpSpr | col;
		}
	}
	//move to next sprite
	ppu.OAM2Ptr += 4;
}

FIXNES_ALWAYSINLINE inline static void updateBGTileAddress()
{
	if((ppu.VramAddr & 0x1F) == 0x1F)
		ppu.VramAddr ^= 0x41F;
	else
		ppu.VramAddr++;
}
FIXNES_ALWAYSINLINE inline static void updateBGHoriAddress()
{
	ppu.VramAddr = (ppu.VramAddr & (~PPU_VRAM_HORIZONTAL_MASK)) | (ppu.TmpVramAddr & PPU_VRAM_HORIZONTAL_MASK);
}
FIXNES_ALWAYSINLINE inline static void updateBGVertAddress()
{
	ppu.VramAddr = (ppu.VramAddr & (~PPU_VRAM_VERTICAL_MASK)) | (ppu.TmpVramAddr & PPU_VRAM_VERTICAL_MASK);
}
FIXNES_ALWAYSINLINE inline static void updateBGYAddress()
{
	/* update Y position for writes */
	if((ppu.VramAddr & 0x7000) != (7<<12))
		ppu.VramAddr += (1<<12);
	else switch(ppu.VramAddr & 0x3E0)
	{
		default:      ppu.VramAddr = (ppu.VramAddr & 0xFFF) + (1 << 5); break;
		case (29<<5): ppu.VramAddr ^= 0x800; /* Falls through. */
		case (31<<5): ppu.VramAddr &= 0xC1F; break;
	}
}

FIXNES_ALWAYSINLINE inline static void setNTAddr()
{
	ppu.NextAddr = (ppu.VramAddr & 0xFFF) | 0x2000;
}

extern void mmc5setTile(uint16_t dot);
FIXNES_ALWAYSINLINE inline static void getNTAddr(uint16_t dot)
{
	/* MMC5 Scanline/Scroll Related */
	if(ppuMapper5) mmc5setTile(dot);
	uint8_t ntByte = memPPUGet8(ppu.NextAddr);
	uint16_t chrROMBG = (ppu.Reg[0] & PPU_BACKGROUND_ADDR) ? 0x1000 : 0;
	uint8_t curTileY = (ppu.VramAddr>>12)&7;
	ppu.NextTile = chrROMBG+(ntByte<<4)+curTileY;
}

FIXNES_ALWAYSINLINE inline static void setATAddr()
{
	ppu.NextAddr = (ppu.VramAddr & 0xC00) | 0x23C0 | ((ppu.VramAddr>>4)&0x38) | ((ppu.VramAddr>>2)&7);
}

FIXNES_ALWAYSINLINE inline static void getATAddr()
{
	/* Select new BG Background Attribute */
	ppu.BGAttribReg = memPPUGet8(ppu.NextAddr) >> ((ppu.VramAddr & 0x2) | (ppu.VramAddr >> 4 & 0x4));
}

FIXNES_ALWAYSINLINE inline static void setTileAddr(uint8_t add)
{
	ppu.NextAddr = ppu.NextTile+add;
}
FIXNES_ALWAYSINLINE inline static void getBGTileAddrLow()
{
	mapperChrMode = 0;
	uint8_t tmp = memPPUGet8(ppu.NextAddr);
	ppu.BGRegB = tmp >> 0 & 0x55; ppu.BGRegA = tmp >> 1 & 0x55;
}
FIXNES_ALWAYSINLINE inline static void getBGTileAddrHigh()
{
	mapperChrMode = 0;
	uint8_t tmp = memPPUGet8(ppu.NextAddr);
	ppu.BGRegA |= tmp << 0 & 0xAA; ppu.BGRegB |= tmp << 1 & 0xAA;
}
FIXNES_ALWAYSINLINE inline static uint8_t getSpriteTileAddr()
{
	mapperChrMode = 1;
	return memPPUGet8(ppu.NextAddr);
}

FIXNES_ALWAYSINLINE inline static void spriteEvalInit()
{
	ppu.OAMzSpritePos = ppu.OAMpos;
	ppu.OAM2pos = 0;
	ppu.OAMcpPos = 0;
	ppu.spriteEvalB = spriteEvalB_P1;
}

FIXNES_ALWAYSINLINE inline static void spriteEvalA()
{
	ppu.TmpOAMVal = ppu.OAM[(ppu.OAMpos+ppu.OAMcpPos)&0xFF];
	//printf("%i %i %i %02x\n", ppu.OAMpos,  ppu.OAMcpPos, (ppu.OAMpos+ppu.OAMcpPos)&0xFF, ppu.TmpOAMVal);
}

static void spriteEvalB_P1(uint16_t line)
{
	uint8_t cSpriteLn = ppu.TmpOAMVal;
	if(cSpriteLn <= line && (cSpriteLn+ppu.sprEvalNumLines) > line)
	{
		ppu.spriteEvalB = spriteEvalB_P2; //move into sprite copy
		ppu.OAM2[ppu.OAM2pos+0] = ppu.TmpOAMVal;
		//printf("Copying sprite with line %i at line %i pos oam %i oam2 %i\n", cSpriteLn, ppu.curLine, ppu.OAMpos, ppu.OAM2pos);
		if(ppu.OAM2pos == 0 && ppu.OAMpos == ppu.OAMzSpritePos)
			ppu.NextHasZSprite = true;
		ppu.OAMcpPos++;
	}
	else //no matching sprite, increase N
	{
		ppu.OAMpos += 4;
		if(ppu.OAMpos == 0) //wrapped, end eval
		{
			ppu.OAMcpPos = 0;
			ppu.spriteEvalB = spriteEvalB_P9;
		}
	}
}

static void spriteEvalB_P2(uint16_t line)
{
	(void)line;
	ppu.OAM2[ppu.OAM2pos+1] = ppu.TmpOAMVal;
	ppu.OAMcpPos++;
	ppu.spriteEvalB = spriteEvalB_P3;
}

static void spriteEvalB_P3(uint16_t line)
{
	(void)line;
	ppu.OAM2[ppu.OAM2pos+2] = ppu.TmpOAMVal;
	ppu.OAMcpPos++;
	ppu.spriteEvalB = spriteEvalB_P4;
}

static void spriteEvalB_P4(uint16_t line)
{
	(void)line;
	ppu.OAM2[ppu.OAM2pos+3] = ppu.TmpOAMVal;
	ppu.OAMcpPos = 0;
	ppu.OAMpos += 4;
	if(ppu.OAMpos == 0) //wrapped, end eval
	{
		ppu.OAMcpPos = 0;
		ppu.spriteEvalB = spriteEvalB_P9;
	}
	else
	{
		ppu.OAM2pos += 4;
		if(ppu.OAM2pos == 0x20) //time for buggy sprite overflow
			ppu.spriteEvalB = spriteEvalB_P5;
		else //go to next sprite
			ppu.spriteEvalB = spriteEvalB_P1;
	}
}

static void spriteEvalB_P5(uint16_t line)
{
	uint8_t cSpriteLn = ppu.TmpOAMVal;
	if(cSpriteLn <= line && (cSpriteLn+ppu.sprEvalNumLines) > line)
	{
		//end byte 0 done
		ppu.spriteEvalB = spriteEvalB_P6;
		//if(!(PPU_Reg[2] & PPU_FLAG_OVERFLOW) && !ppu.SpriteOverflow)
		//	printf("Overflow with line %i at line %i pos oam %i oam2 %i\n", cSpriteLn, ppu.curLine, ppu.OAMpos, ppu.OAM2pos);
		ppu.Reg[2] |= PPU_FLAG_OVERFLOW;
		if(ppu.OAMcpPos < 3)
			ppu.OAMcpPos++;
		else
		{
			ppu.OAMcpPos = 0;
			//OAMpos increment if found
			ppu.OAMpos += 4;
		}
	}
	else //no matching sprite, increase N
	{
		ppu.OAMpos += 4;
		if(ppu.OAMpos == 0) //wrapped, end eval
		{
			ppu.OAMcpPos = 0;
			ppu.spriteEvalB = spriteEvalB_P9;
		}
		else
		{
			if(ppu.OAMcpPos < 3)
				ppu.OAMcpPos++;
			else //no OAMpos increment if not found
				ppu.OAMcpPos = 0;
		}
	}
}

static void spriteEvalB_P6(uint16_t line)
{
	(void)line;
	//end byte 1 done
	ppu.spriteEvalB = spriteEvalB_P7;
	if(ppu.OAMcpPos < 3)
		ppu.OAMcpPos++;
	else
	{
		ppu.OAMcpPos = 0;
		//OAMpos increment if found
		ppu.OAMpos += 4;
	}
}

static void spriteEvalB_P7(uint16_t line)
{
	(void)line;
	//end byte 2 done
	ppu.spriteEvalB = spriteEvalB_P8;
	if(ppu.OAMcpPos < 3)
		ppu.OAMcpPos++;
	else
	{
		ppu.OAMcpPos = 0;
		//OAMpos increment if found
		ppu.OAMpos += 4;
	}
}

static void spriteEvalB_P8(uint16_t line)
{
	(void)line;
	//end byte 3 done
	ppu.spriteEvalB = spriteEvalB_P9;
	if(ppu.OAMcpPos == 3) //OAMpos increment if found
		ppu.OAMpos += 4;
	ppu.OAMcpPos = 0;
}

static void spriteEvalB_P9(uint16_t line)
{
	(void)line;
	ppu.OAMpos += 4;
}

FIXNES_ALWAYSINLINE inline static void initSpriteTileFetch()
{
	ppu.OAM2Ptr = ppu.OAM2;
}

FIXNES_ALWAYSINLINE inline static void resetOAMPos()
{
	ppu.OAMpos = 0;
}

FIXNES_ALWAYSINLINE inline static void ClearOAM2Byte()
{
	ppu.OAM2[ppu.OAM2pos++] = 0xFF;
}

static uint16_t ppuLastDot(uint16_t line)
{
	line++;
	if(line == 241) /* done drawing this frame */
	{
		ppu.FrameDone = true;
		/* For MMC5 Scanline Detect */
		ppuInFrame = false;
	}
	else if(line == ppu.PreRenderLine) /* OAM Bug in 2C02 */
	{
		if((ppu.OAMpos & 0xF8) && ppu.DoOAMBug && (ppu.Reg[1] & (PPU_BG_ENABLE | PPU_SPRITE_ENABLE)))
			memcpy(ppu.OAM,ppu.OAM + (ppu.OAMpos & 0xF8), 8);
	}
	else if(line == ppu.LinesTotal) /* Wrap back down after pre-render line */
		line = 0;
	ppu.curLine = line;
	ppu.DoOverscan = (doOverscan && (line < 8 || line >= 232));
	ppu.NextHasZSprite = false; //reset
	ppu.OAMzSpritePos = 0; // reset
	//important for ClearOAM2Byte
	ppu.OAM2pos = 0; //reset
	ppu.TmpOAMVal = 0xFF;
	//printf("Line done\n");
	return line;
}
#ifdef DO_4_3_ASPECT //4x horizontal and vertical scaling for interpolation
#define TEX_AT_POS 	textureImage[drawPos]=textureImage[drawPos+1]= \
					textureImage[drawPos+2]=textureImage[drawPos+3]= \
					textureImage[drawPos+TEX_DOTS]=textureImage[drawPos+TEX_DOTS+1]= \
					textureImage[drawPos+TEX_DOTS+2]=textureImage[drawPos+TEX_DOTS+3]= \
					textureImage[drawPos+(TEX_DOTS*2)]=textureImage[drawPos+(TEX_DOTS*2)+1]= \
					textureImage[drawPos+(TEX_DOTS*2)+2]=textureImage[drawPos+(TEX_DOTS*2)+3]= \
					textureImage[drawPos+(TEX_DOTS*3)]=textureImage[drawPos+(TEX_DOTS*3)+1]= \
					textureImage[drawPos+(TEX_DOTS*3)+2]=textureImage[drawPos+(TEX_DOTS*3)+3]
#else //1x horizontal and vertical scaling for pure integer scale display
#define TEX_AT_POS 	textureImage[drawPos]
#endif
FIXNES_ALWAYSINLINE void ppuCycle()
{
	uint16_t dot = ppu.curDot, line = ppu.curLine;
#if defined(DISPLAY_PPUWRITES) || defined(DO_4_3_ASPECT)
	uint32_t drawPos;
#else
	uint16_t drawPos;
#endif
	uint8_t curCol;
	//these 2 stats are set by cpu, no need to have them in loop
	ppu.CurNMIStat = !!(ppu.Reg[0] & PPU_FLAG_NMI);
	ppu.VBlankClearCycle = false;
	//get value of how often ppu has to run
	uint16_t rc = ppu.RunCycles;
	uint8_t ppuLoop = rc&7;
	ppu.RunCycles = (rc>>3)|(ppuLoop<<12);
	while(ppuLoop--)
	{
		switch(dot)
		{
			//line 0-239 render on
			/*case 0: case 8:*/ case 16: case 24:
			case 32: case 40: case 48: case 56:
				setNTAddr();
				loadTiles();
			do_render_pixel:
				/* Grab color to render from BG and Sprites */
				curCol = ppu.BGEnable ? ppu.BGTiles[(dot + ppu.FineXScroll) & 15] : 0;
				if(ppu.SprEnable) curCol = ppuDoSprites(curCol, dot);
				ppu.SprLUT[dot] = 0; //always clear for next sprite eval
				/* Draw current dot on screen */
				#ifdef DISPLAY_PPUWRITES
				drawPos = (dot)+(line*TEX_DOTS);
				#elif defined(DO_4_3_ASPECT)
				drawPos = (dot<<2)+(line<<12);
				#else
				drawPos = (dot)+(line<<8);
				#endif
				if(ppu.DoOverscan) /* Draw clipped area as black */
					TEX_AT_POS = TEXCOL_BLACK;
				else
				{
					//use color from bg or sprite input
					TEX_AT_POS = ppu.BGRLUT[ppu.PALRAM2[curCol&0x1F]];
				}
				goto add_dot;
			case 0:
				setNTAddr();
				loadTiles();
				ppu.BGEnable = (ppu.Reg[1] & PPU_BG_8PX) && (ppu.Reg[1] & PPU_BG_ENABLE);
				ppu.SprEnable = (ppu.Reg[1] & PPU_SPRITE_8PX) && (ppu.Reg[1] & PPU_SPRITE_ENABLE);
				goto do_render_pixel;
			case 8:
				setNTAddr();
				loadTiles();
				ppu.BGEnable = (ppu.Reg[1] & PPU_BG_ENABLE);
				ppu.SprEnable = (ppu.Reg[1] & PPU_SPRITE_ENABLE);
				goto do_render_pixel;
			case 1: case 9: case 17: case 25:
			case 33: case 41: case 49: case 57:
				getNTAddr(dot);
				ClearOAM2Byte();
				goto do_render_pixel;
			case 2: case 10: case 18: case 26:
			case 34: case 42: case 50: case 58:
				setATAddr();
				goto do_render_pixel;
			case 3: case 11: case 19: case 27:
			case 35: case 43: case 51: case 59:
				getATAddr();
				updateBGTileAddress();
				ClearOAM2Byte();
				goto do_render_pixel;
			case 4: case 12: case 20: case 28:
			case 36: case 44: case 52: case 60:
				setTileAddr(0);
				goto do_render_pixel;
			case 5: case 13: case 21: case 29:
			case 37: case 45: case 53: case 61:
				getBGTileAddrLow();
				ClearOAM2Byte();
				goto do_render_pixel;
			case 6: case 14: case 22: case 30:
			case 38: case 46: case 54: case 62:
				setTileAddr(8);
				goto do_render_pixel;
			case 7: case 15: case 23: case 31:
			case 39: case 47: case 55: case 63:
				getBGTileAddrHigh();
				ClearOAM2Byte();
				goto do_render_pixel;
			/*case 64:*/ case 72: case 80: case 88:
			case 96: case 104: case 112: case 120:
			case 128: case 136: case 144: case 152:
			case 160: case 168: case 176: case 184:
			case 192: case 200: case 208: case 216:
			case 224: case 232: case 240: case 248:
				setNTAddr();
				loadTiles();
				goto do_sprite_eval_a;
			case 64: //special case
				setNTAddr();
				loadTiles();
				spriteEvalInit();
				goto do_sprite_eval_a;
			case 65: case 73: case 81: case 89:
			case 97: case 105: case 113: case 121:
			case 129: case 137: case 145: case 153:
			case 161: case 169: case 177: case 185:
			case 193: case 201: case 209: case 217:
			case 225: case 233: case 241: case 249:
				getNTAddr(dot);
			do_sprite_eval_b:
				ppu.spriteEvalB(line);
				goto do_render_pixel;
			case 66: case 74: case 82: case 90:
			case 98: case 106: case 114: case 122:
			case 130: case 138: case 146: case 154:
			case 162: case 170: case 178: case 186:
			case 194: case 202: case 210: case 218:
			case 226: case 234: case 242: case 250:
				setATAddr();
			do_sprite_eval_a:
				spriteEvalA();
				goto do_render_pixel;
			case 67: case 75: case 83: case 91:
			case 99: case 107: case 115: case 123:
			case 131: case 139: case 147: case 155:
			case 163: case 171: case 179: case 187:
			case 195: case 203: case 211: case 219:
			case 227: case 235: case 243: /*case 251:*/
				getATAddr();
				updateBGTileAddress();
				goto do_sprite_eval_b;
			case 251: //special case
				getATAddr();
				updateBGTileAddress();
				updateBGYAddress();
				goto do_sprite_eval_b;
			case 68: case 76: case 84: case 92:
			case 100: case 108: case 116: case 124:
			case 132: case 140: case 148: case 156:
			case 164: case 172: case 180: case 188:
			case 196: case 204: case 212: case 220:
			case 228: case 236: case 244: case 252:
				setTileAddr(0);
				goto do_sprite_eval_a;
			case 69: case 77: case 85: case 93:
			case 101: case 109: case 117: case 125:
			case 133: case 141: case 149: case 157:
			case 165: case 173: case 181: case 189:
			case 197: case 205: case 213: case 221:
			case 229: case 237: case 245: case 253:
				getBGTileAddrLow();
				goto do_sprite_eval_b;
			case 70: case 78: case 86: case 94:
			case 102: case 110: case 118: case 126:
			case 134: case 142: case 150: case 158:
			case 166: case 174: case 182: case 190:
			case 198: case 206: case 214: case 222:
			case 230: case 238: case 246: case 254:
				setTileAddr(8);
				goto do_sprite_eval_a;
			case 71: case 79: case 87: case 95:
			case 103: case 111: case 119: case 127:
			case 135: case 143: case 151: case 159:
			case 167: case 175: case 183: case 191:
			case 199: case 207: case 215: case 223:
			case 231: case 239: case 247: case 255:
				getBGTileAddrHigh();
				goto do_sprite_eval_b;
			case 256:
				updateBGHoriAddress();
				ppu.TmpOAMVal = 0xFF;
				initSpriteTileFetch();
				goto do_reset_oam_pos;
			case 257: case 258: case 259:
			case 280: case 281: case 282: case 283:
			case 288: case 289: case 290: case 291:
			case 296: case 297: case 298: case 299:
			case 304: case 305: case 306: case 307:
			case 312: case 313: case 314: case 315:
			do_reset_oam_pos:
				resetOAMPos();
				goto add_dot;
			case 260: case 268: case 276: case 284:
			case 292: case 300: case 308: case 316:
				setNextSpriteTileAddr(line);
				setTileAddr(0);
				goto do_reset_oam_pos;
			case 261: case 269: case 277: case 285:
			case 293: case 301: case 309: case 317:
				ppu.NextByte = getSpriteTileAddr();
				goto do_reset_oam_pos;
			case 262: case 270: case 278: case 286:
			case 294: case 302: case 310: case 318:
				setTileAddr(8);
				goto do_reset_oam_pos;
			case 263: case 271: case 279: case 287:
			case 295: case 303: case 311: case 319:
				saveSprite(ppu.NextByte, getSpriteTileAddr());
				goto do_reset_oam_pos;
			case 264: case 265: case 266: case 267:
			case 272: case 273: case 274: case 275:
				//garbage table fetches, not here yet
				goto add_dot;
			case 320:
				setNTAddr();
				ppu.TmpOAMVal = ppu.OAM2[0];
				goto add_dot;
			case 328:
				setNTAddr();
				ppu.BGIndex = 0;
				loadTiles();
				goto add_dot;
			case 336: case 338:
				setNTAddr();
				goto add_dot;
			case 321: case 329: case 337: case 339:
				getNTAddr(dot);
				goto add_dot;
			case 322: case 330:
				setATAddr();
				goto add_dot;
			case 323: case 331:
				getATAddr();
				updateBGTileAddress();
				goto add_dot;
			case 324: case 332:
				setTileAddr(0);
				goto add_dot;
			case 325: case 333:
				getBGTileAddrLow();
				goto add_dot;
			case 326: case 334:
				setTileAddr(8);
				goto add_dot;
			case 327: case 335:
				getBGTileAddrHigh();
				goto add_dot;
			//line 0-239 rendering off
			case PPU_OFF+0: case PPU_OFF+2: case PPU_OFF+4: case PPU_OFF+6:
			case PPU_OFF+8: case PPU_OFF+10: case PPU_OFF+12: case PPU_OFF+14:
			case PPU_OFF+16: case PPU_OFF+18: case PPU_OFF+20: case PPU_OFF+22:
			case PPU_OFF+24: case PPU_OFF+26: case PPU_OFF+28: case PPU_OFF+30:
			case PPU_OFF+32: case PPU_OFF+34: case PPU_OFF+36: case PPU_OFF+38:
			case PPU_OFF+40: case PPU_OFF+42: case PPU_OFF+44: case PPU_OFF+46:
			case PPU_OFF+48: case PPU_OFF+50: case PPU_OFF+52: case PPU_OFF+54:
			case PPU_OFF+56: case PPU_OFF+58: case PPU_OFF+60: case PPU_OFF+62:
			/*case PPU_OFF+64:*/ case PPU_OFF+65: case PPU_OFF+66: case PPU_OFF+67:
			case PPU_OFF+68: case PPU_OFF+69: case PPU_OFF+70: case PPU_OFF+71:
			case PPU_OFF+72: case PPU_OFF+73: case PPU_OFF+74: case PPU_OFF+75:
			case PPU_OFF+76: case PPU_OFF+77: case PPU_OFF+78: case PPU_OFF+79:
			case PPU_OFF+80: case PPU_OFF+81: case PPU_OFF+82: case PPU_OFF+83:
			case PPU_OFF+84: case PPU_OFF+85: case PPU_OFF+86: case PPU_OFF+87:
			case PPU_OFF+88: case PPU_OFF+89: case PPU_OFF+90: case PPU_OFF+91:
			case PPU_OFF+92: case PPU_OFF+93: case PPU_OFF+94: case PPU_OFF+95:
			case PPU_OFF+96: case PPU_OFF+97: case PPU_OFF+98: case PPU_OFF+99:
			case PPU_OFF+100: case PPU_OFF+101: case PPU_OFF+102: case PPU_OFF+103:
			case PPU_OFF+104: case PPU_OFF+105: case PPU_OFF+106: case PPU_OFF+107:
			case PPU_OFF+108: case PPU_OFF+109: case PPU_OFF+110: case PPU_OFF+111:
			case PPU_OFF+112: case PPU_OFF+113: case PPU_OFF+114: case PPU_OFF+115:
			case PPU_OFF+116: case PPU_OFF+117: case PPU_OFF+118: case PPU_OFF+119:
			case PPU_OFF+120: case PPU_OFF+121: case PPU_OFF+122: case PPU_OFF+123:
			case PPU_OFF+124: case PPU_OFF+125: case PPU_OFF+126: case PPU_OFF+127:
			case PPU_OFF+128: case PPU_OFF+129: case PPU_OFF+130: case PPU_OFF+131:
			case PPU_OFF+132: case PPU_OFF+133: case PPU_OFF+134: case PPU_OFF+135:
			case PPU_OFF+136: case PPU_OFF+137: case PPU_OFF+138: case PPU_OFF+139:
			case PPU_OFF+140: case PPU_OFF+141: case PPU_OFF+142: case PPU_OFF+143:
			case PPU_OFF+144: case PPU_OFF+145: case PPU_OFF+146: case PPU_OFF+147:
			case PPU_OFF+148: case PPU_OFF+149: case PPU_OFF+150: case PPU_OFF+151:
			case PPU_OFF+152: case PPU_OFF+153: case PPU_OFF+154: case PPU_OFF+155:
			case PPU_OFF+156: case PPU_OFF+157: case PPU_OFF+158: case PPU_OFF+159:
			case PPU_OFF+160: case PPU_OFF+161: case PPU_OFF+162: case PPU_OFF+163:
			case PPU_OFF+164: case PPU_OFF+165: case PPU_OFF+166: case PPU_OFF+167:
			case PPU_OFF+168: case PPU_OFF+169: case PPU_OFF+170: case PPU_OFF+171:
			case PPU_OFF+172: case PPU_OFF+173: case PPU_OFF+174: case PPU_OFF+175:
			case PPU_OFF+176: case PPU_OFF+177: case PPU_OFF+178: case PPU_OFF+179:
			case PPU_OFF+180: case PPU_OFF+181: case PPU_OFF+182: case PPU_OFF+183:
			case PPU_OFF+184: case PPU_OFF+185: case PPU_OFF+186: case PPU_OFF+187:
			case PPU_OFF+188: case PPU_OFF+189: case PPU_OFF+190: case PPU_OFF+191:
			case PPU_OFF+192: case PPU_OFF+193: case PPU_OFF+194: case PPU_OFF+195:
			case PPU_OFF+196: case PPU_OFF+197: case PPU_OFF+198: case PPU_OFF+199:
			case PPU_OFF+200: case PPU_OFF+201: case PPU_OFF+202: case PPU_OFF+203:
			case PPU_OFF+204: case PPU_OFF+205: case PPU_OFF+206: case PPU_OFF+207:
			case PPU_OFF+208: case PPU_OFF+209: case PPU_OFF+210: case PPU_OFF+211:
			case PPU_OFF+212: case PPU_OFF+213: case PPU_OFF+214: case PPU_OFF+215:
			case PPU_OFF+216: case PPU_OFF+217: case PPU_OFF+218: case PPU_OFF+219:
			case PPU_OFF+220: case PPU_OFF+221: case PPU_OFF+222: case PPU_OFF+223:
			case PPU_OFF+224: case PPU_OFF+225: case PPU_OFF+226: case PPU_OFF+227:
			case PPU_OFF+228: case PPU_OFF+229: case PPU_OFF+230: case PPU_OFF+231:
			case PPU_OFF+232: case PPU_OFF+233: case PPU_OFF+234: case PPU_OFF+235:
			case PPU_OFF+236: case PPU_OFF+237: case PPU_OFF+238: case PPU_OFF+239:
			case PPU_OFF+240: case PPU_OFF+241: case PPU_OFF+242: case PPU_OFF+243:
			case PPU_OFF+244: case PPU_OFF+245: case PPU_OFF+246: case PPU_OFF+247:
			case PPU_OFF+248: case PPU_OFF+249: case PPU_OFF+250: case PPU_OFF+251:
			case PPU_OFF+252: case PPU_OFF+253: case PPU_OFF+254: case PPU_OFF+255:
			do_render_pixel_off:
				ppu.SprLUT[dot-PPU_OFF] = 0; //always clear for next sprite eval
				/* Draw current dot on screen */
				#ifdef DISPLAY_PPUWRITES
				drawPos = (dot-PPU_OFF)+(line*TEX_DOTS);
				#elif defined(DO_4_3_ASPECT)
				drawPos = ((dot-PPU_OFF)<<2)+(line<<12);
				#else
				drawPos = (dot-PPU_OFF)+(line<<8);
				#endif
				if(ppu.DoOverscan) /* Draw clipped area as black */
					TEX_AT_POS = TEXCOL_BLACK;
				else
				{
					if((ppu.VramAddr & 0x3F00) == 0x3F00) //bg and sprite disabled but address within PALRAM
						TEX_AT_POS = ppu.BGRLUT[ppu.PALRAM2[ppu.VramAddr&0x1F]];
					else //bg and sprite disabled and address not within PALRAM
						TEX_AT_POS = ppu.BGRLUT[ppu.PALRAM2[0]];
				}
				goto add_dot;
			case PPU_OFF+1: case PPU_OFF+3: case PPU_OFF+5: case PPU_OFF+7:
			case PPU_OFF+9: case PPU_OFF+11: case PPU_OFF+13: case PPU_OFF+15:
			case PPU_OFF+17: case PPU_OFF+19: case PPU_OFF+21: case PPU_OFF+23:
			case PPU_OFF+25: case PPU_OFF+27: case PPU_OFF+29: case PPU_OFF+31:
			case PPU_OFF+33: case PPU_OFF+35: case PPU_OFF+37: case PPU_OFF+39:
			case PPU_OFF+41: case PPU_OFF+43: case PPU_OFF+45: case PPU_OFF+47:
			case PPU_OFF+49: case PPU_OFF+51: case PPU_OFF+53: case PPU_OFF+55:
			case PPU_OFF+57: case PPU_OFF+59: case PPU_OFF+61: case PPU_OFF+63:
				ClearOAM2Byte();
				goto do_render_pixel_off;
			case PPU_OFF+64: //safety pointer reset
				spriteEvalInit();
				goto do_render_pixel_off;
			case PPU_OFF+256: //safety pointer reset
				initSpriteTileFetch();
				goto add_dot;
			case PPU_OFF+257: case PPU_OFF+258: case PPU_OFF+259: case PPU_OFF+260:
			case PPU_OFF+261: case PPU_OFF+262: case PPU_OFF+263: case PPU_OFF+264:
			case PPU_OFF+265: case PPU_OFF+266: case PPU_OFF+267: case PPU_OFF+268:
			case PPU_OFF+269: case PPU_OFF+270: case PPU_OFF+271: case PPU_OFF+272:
			case PPU_OFF+273: case PPU_OFF+274: case PPU_OFF+275: case PPU_OFF+276:
			case PPU_OFF+277: case PPU_OFF+278: case PPU_OFF+279: case PPU_OFF+280:
			case PPU_OFF+281: case PPU_OFF+282: case PPU_OFF+283: case PPU_OFF+284:
			case PPU_OFF+285: case PPU_OFF+286: case PPU_OFF+287: case PPU_OFF+288:
			case PPU_OFF+289: case PPU_OFF+290: case PPU_OFF+291: case PPU_OFF+292:
			case PPU_OFF+293: case PPU_OFF+294: case PPU_OFF+295: case PPU_OFF+296:
			case PPU_OFF+297: case PPU_OFF+298: case PPU_OFF+299: case PPU_OFF+300:
			case PPU_OFF+301: case PPU_OFF+302: case PPU_OFF+303: case PPU_OFF+304:
			case PPU_OFF+305: case PPU_OFF+306: case PPU_OFF+307: case PPU_OFF+308:
			case PPU_OFF+309: case PPU_OFF+310: case PPU_OFF+311: case PPU_OFF+312:
			case PPU_OFF+313: case PPU_OFF+314: case PPU_OFF+315: case PPU_OFF+316:
			case PPU_OFF+317: case PPU_OFF+318: case PPU_OFF+319: case PPU_OFF+320:
			case PPU_OFF+321: case PPU_OFF+322: case PPU_OFF+323: case PPU_OFF+324:
			case PPU_OFF+325: case PPU_OFF+326: case PPU_OFF+327: case PPU_OFF+328:
			case PPU_OFF+329: case PPU_OFF+330: case PPU_OFF+331: case PPU_OFF+332:
			case PPU_OFF+333: case PPU_OFF+334: case PPU_OFF+335: case PPU_OFF+336:
			case PPU_OFF+337: case PPU_OFF+338: case PPU_OFF+339:
				goto add_dot;
			//pre-render line render on
			/*case PPU_PRE+0: */case PPU_PRE+8: case PPU_PRE+16: case PPU_PRE+24:
			case PPU_PRE+32: case PPU_PRE+40: case PPU_PRE+48: case PPU_PRE+56:
			case PPU_PRE+64: case PPU_PRE+72: case PPU_PRE+80: case PPU_PRE+88:
			case PPU_PRE+96: case PPU_PRE+104: case PPU_PRE+112: case PPU_PRE+120:
			case PPU_PRE+128: case PPU_PRE+136: case PPU_PRE+144: case PPU_PRE+152:
			case PPU_PRE+160: case PPU_PRE+168: case PPU_PRE+176: case PPU_PRE+184:
			case PPU_PRE+192: case PPU_PRE+200: case PPU_PRE+208: case PPU_PRE+216:
			case PPU_PRE+224: case PPU_PRE+232: case PPU_PRE+240: case PPU_PRE+248:
				setNTAddr();
				loadTiles();
				goto add_dot;
			case PPU_PRE+0: /* VBlank ends at first dot of the pre-render line */
				setNTAddr();
				loadTiles();
				ppu.Reg[2] &= ~(PPU_FLAG_SPRITEZERO | PPU_FLAG_OVERFLOW);
				goto add_dot;
			case PPU_PRE+1: case PPU_PRE+9: case PPU_PRE+17: case PPU_PRE+25:
			case PPU_PRE+33: case PPU_PRE+41: case PPU_PRE+49: case PPU_PRE+57:
			case PPU_PRE+65: case PPU_PRE+73: case PPU_PRE+81: case PPU_PRE+89:
			case PPU_PRE+97: case PPU_PRE+105: case PPU_PRE+113: case PPU_PRE+121:
			case PPU_PRE+129: case PPU_PRE+137: case PPU_PRE+145: case PPU_PRE+153:
			case PPU_PRE+161: case PPU_PRE+169: case PPU_PRE+177: case PPU_PRE+185:
			case PPU_PRE+193: case PPU_PRE+201: case PPU_PRE+209: case PPU_PRE+217:
			case PPU_PRE+225: case PPU_PRE+233: case PPU_PRE+241: case PPU_PRE+249:
				getNTAddr(dot-PPU_PRE);
				goto add_dot;
			/*case PPU_PRE+2:*/ case PPU_PRE+10: case PPU_PRE+18: case PPU_PRE+26:
			case PPU_PRE+34: case PPU_PRE+42: case PPU_PRE+50: case PPU_PRE+58:
			case PPU_PRE+66: case PPU_PRE+74: case PPU_PRE+82: case PPU_PRE+90:
			case PPU_PRE+98: case PPU_PRE+106: case PPU_PRE+114: case PPU_PRE+122:
			case PPU_PRE+130: case PPU_PRE+138: case PPU_PRE+146: case PPU_PRE+154:
			case PPU_PRE+162: case PPU_PRE+170: case PPU_PRE+178: case PPU_PRE+186:
			case PPU_PRE+194: case PPU_PRE+202: case PPU_PRE+210: case PPU_PRE+218:
			case PPU_PRE+226: case PPU_PRE+234: case PPU_PRE+242: case PPU_PRE+250:
				setATAddr();
				goto add_dot;
			case PPU_PRE+2: /* Though results are better when clearing it a bit later */
				setATAddr();
				#if PPU_DEBUG_VSYNC
				printf("PPU End VBlank\n");
				#endif
				ppu.Reg[2] &= ~(PPU_FLAG_VBLANK);
				goto add_dot;
			case PPU_PRE+3: case PPU_PRE+11: case PPU_PRE+19: case PPU_PRE+27:
			case PPU_PRE+35: case PPU_PRE+43: case PPU_PRE+51: case PPU_PRE+59:
			case PPU_PRE+67: case PPU_PRE+75: case PPU_PRE+83: case PPU_PRE+91:
			case PPU_PRE+99: case PPU_PRE+107: case PPU_PRE+115: case PPU_PRE+123:
			case PPU_PRE+131: case PPU_PRE+139: case PPU_PRE+147: case PPU_PRE+155:
			case PPU_PRE+163: case PPU_PRE+171: case PPU_PRE+179: case PPU_PRE+187:
			case PPU_PRE+195: case PPU_PRE+203: case PPU_PRE+211: case PPU_PRE+219:
			case PPU_PRE+227: case PPU_PRE+235: case PPU_PRE+243: /*case PPU_PRE+251:*/
				getATAddr();
				updateBGTileAddress();
				goto add_dot;
			case PPU_PRE+251: //special case
				getATAddr();
				updateBGTileAddress();
				updateBGYAddress();
				goto add_dot;
			case PPU_PRE+4: case PPU_PRE+12: case PPU_PRE+20: case PPU_PRE+28:
			case PPU_PRE+36: case PPU_PRE+44: case PPU_PRE+52: case PPU_PRE+60:
			case PPU_PRE+68: case PPU_PRE+76: case PPU_PRE+84: case PPU_PRE+92:
			case PPU_PRE+100: case PPU_PRE+108: case PPU_PRE+116: case PPU_PRE+124:
			case PPU_PRE+132: case PPU_PRE+140: case PPU_PRE+148: case PPU_PRE+156:
			case PPU_PRE+164: case PPU_PRE+172: case PPU_PRE+180: case PPU_PRE+188:
			case PPU_PRE+196: case PPU_PRE+204: case PPU_PRE+212: case PPU_PRE+220:
			case PPU_PRE+228: case PPU_PRE+236: case PPU_PRE+244: case PPU_PRE+252:
				setTileAddr(0);
				goto add_dot;
			case PPU_PRE+5: case PPU_PRE+13: case PPU_PRE+21: case PPU_PRE+29:
			case PPU_PRE+37: case PPU_PRE+45: case PPU_PRE+53: case PPU_PRE+61:
			case PPU_PRE+69: case PPU_PRE+77: case PPU_PRE+85: case PPU_PRE+93:
			case PPU_PRE+101: case PPU_PRE+109: case PPU_PRE+117: case PPU_PRE+125:
			case PPU_PRE+133: case PPU_PRE+141: case PPU_PRE+149: case PPU_PRE+157:
			case PPU_PRE+165: case PPU_PRE+173: case PPU_PRE+181: case PPU_PRE+189:
			case PPU_PRE+197: case PPU_PRE+205: case PPU_PRE+213: case PPU_PRE+221:
			case PPU_PRE+229: case PPU_PRE+237: case PPU_PRE+245: case PPU_PRE+253:
				getBGTileAddrLow();
				goto add_dot;
			case PPU_PRE+6: case PPU_PRE+14: case PPU_PRE+22: case PPU_PRE+30:
			case PPU_PRE+38: case PPU_PRE+46: case PPU_PRE+54: case PPU_PRE+62:
			case PPU_PRE+70: case PPU_PRE+78: case PPU_PRE+86: case PPU_PRE+94:
			case PPU_PRE+102: case PPU_PRE+110: case PPU_PRE+118: case PPU_PRE+126:
			case PPU_PRE+134: case PPU_PRE+142: case PPU_PRE+150: case PPU_PRE+158:
			case PPU_PRE+166: case PPU_PRE+174: case PPU_PRE+182: case PPU_PRE+190:
			case PPU_PRE+198: case PPU_PRE+206: case PPU_PRE+214: case PPU_PRE+222:
			case PPU_PRE+230: case PPU_PRE+238: case PPU_PRE+246: case PPU_PRE+254:
				setTileAddr(8);
				goto add_dot;
			/*case PPU_PRE+7:*/ case PPU_PRE+15: case PPU_PRE+23: case PPU_PRE+31:
			case PPU_PRE+39: case PPU_PRE+47: case PPU_PRE+55: case PPU_PRE+63:
			case PPU_PRE+71: case PPU_PRE+79: case PPU_PRE+87: case PPU_PRE+95:
			case PPU_PRE+103: case PPU_PRE+111: case PPU_PRE+119: case PPU_PRE+127:
			case PPU_PRE+135: case PPU_PRE+143: case PPU_PRE+151: case PPU_PRE+159:
			case PPU_PRE+167: case PPU_PRE+175: case PPU_PRE+183: case PPU_PRE+191:
			case PPU_PRE+199: case PPU_PRE+207: case PPU_PRE+215: case PPU_PRE+223:
			case PPU_PRE+231: case PPU_PRE+239: case PPU_PRE+247: case PPU_PRE+255:
				getBGTileAddrHigh();
				goto add_dot;
			case PPU_PRE+7: //special case
				getBGTileAddrHigh();
				ppu.NMIallowed = false;
				goto add_dot;
			case PPU_PRE+256:
				updateBGHoriAddress();
				ppu.TmpOAMVal = 0xFF;
				initSpriteTileFetch();
				goto do_reset_oam_pos;
			case PPU_PRE+257: case PPU_PRE+258: case PPU_PRE+259:
				goto do_reset_oam_pos;
			case PPU_PRE+260: case PPU_PRE+268: case PPU_PRE+276: case PPU_PRE+308:
			case PPU_PRE+316:
				setNextSpriteTileAddr(line);
				setTileAddr(0);
				goto do_reset_oam_pos;
			case PPU_PRE+261: case PPU_PRE+269: case PPU_PRE+277: case PPU_PRE+309:
			case PPU_PRE+317:
				ppu.NextByte = getSpriteTileAddr();
				goto do_reset_oam_pos;
			case PPU_PRE+262: case PPU_PRE+270: case PPU_PRE+278: case PPU_PRE+310:
			case PPU_PRE+318:
				setTileAddr(8);
				goto do_reset_oam_pos;
			case PPU_PRE+263: case PPU_PRE+271: case PPU_PRE+311: case PPU_PRE+319:
				saveSprite(ppu.NextByte, getSpriteTileAddr());
				goto do_reset_oam_pos;
			case PPU_PRE+264: case PPU_PRE+265: case PPU_PRE+266: case PPU_PRE+267:
			case PPU_PRE+272: case PPU_PRE+273: case PPU_PRE+274: case PPU_PRE+275:
				//garbage table fetches, not here yet
				goto add_dot;
			case PPU_PRE+284: case PPU_PRE+292: case PPU_PRE+300:
				updateBGVertAddress();
				setNextSpriteTileAddr(line);
				setTileAddr(0);
				goto do_reset_oam_pos;
			case PPU_PRE+285: case PPU_PRE+293: case PPU_PRE+301:
				updateBGVertAddress();
				ppu.NextByte = getSpriteTileAddr();
				goto do_reset_oam_pos;
			case PPU_PRE+286: case PPU_PRE+294: case PPU_PRE+302:
				updateBGVertAddress();
				setTileAddr(8);
				goto do_reset_oam_pos;
			case PPU_PRE+279: case PPU_PRE+287:	case PPU_PRE+295: case PPU_PRE+303:
				updateBGVertAddress();
				saveSprite(ppu.NextByte, getSpriteTileAddr());
				goto do_reset_oam_pos;
			case PPU_PRE+280: case PPU_PRE+281: case PPU_PRE+282: case PPU_PRE+283:
			case PPU_PRE+288: case PPU_PRE+289: case PPU_PRE+290: case PPU_PRE+291:
			case PPU_PRE+296: case PPU_PRE+297: case PPU_PRE+298: case PPU_PRE+299:
				updateBGVertAddress();
				goto do_reset_oam_pos;
			case PPU_PRE+304: case PPU_PRE+305: case PPU_PRE+306: case PPU_PRE+307:
			case PPU_PRE+312: case PPU_PRE+313: case PPU_PRE+314: case PPU_PRE+315:
				goto do_reset_oam_pos;
			case PPU_PRE+320:
				setNTAddr();
				ppu.TmpOAMVal = ppu.OAM2[0];
				goto add_dot;
			case PPU_PRE+328:
				setNTAddr();
				ppu.BGIndex = 0;
				loadTiles();
				goto add_dot;
			case PPU_PRE+336: case PPU_PRE+338:
				setNTAddr();
				goto add_dot;
			case PPU_PRE+321: case PPU_PRE+329: case PPU_PRE+337:
				getNTAddr(dot-PPU_PRE);
				goto add_dot;
			case PPU_PRE+322: case PPU_PRE+330:
				setATAddr();
				goto add_dot;
			case PPU_PRE+323: case PPU_PRE+331:
				getATAddr();
				updateBGTileAddress();
				goto add_dot;
			case PPU_PRE+324: case PPU_PRE+332:
				setTileAddr(0);
				goto add_dot;
			case PPU_PRE+325: case PPU_PRE+333:
				getBGTileAddrLow();
				goto add_dot;
			case PPU_PRE+326: case PPU_PRE+334:
				setTileAddr(8);
				goto add_dot;
			case PPU_PRE+327: case PPU_PRE+335:
				getBGTileAddrHigh();
				goto add_dot;
			case PPU_PRE+339:
				getNTAddr(dot-PPU_PRE);
				ppu.OddFrame = ppu.OddArr[ppu.OddNum^=1];
				if(ppu.OddFrame && (ppu.Reg[1] & PPU_BG_ENABLE))
					goto last_dot;
				goto add_dot;
			//pre-render line render off
			/*case PPU_PRE_OFF+0:*/ case PPU_PRE_OFF+1: /*case PPU_PRE_OFF+2:*/ case PPU_PRE_OFF+3:
			case PPU_PRE_OFF+4: case PPU_PRE_OFF+5: case PPU_PRE_OFF+6: /*case PPU_PRE_OFF+7:*/
			case PPU_PRE_OFF+8: case PPU_PRE_OFF+9: case PPU_PRE_OFF+10: case PPU_PRE_OFF+11:
			case PPU_PRE_OFF+12: case PPU_PRE_OFF+13: case PPU_PRE_OFF+14: case PPU_PRE_OFF+15:
			case PPU_PRE_OFF+16: case PPU_PRE_OFF+17: case PPU_PRE_OFF+18: case PPU_PRE_OFF+19:
			case PPU_PRE_OFF+20: case PPU_PRE_OFF+21: case PPU_PRE_OFF+22: case PPU_PRE_OFF+23:
			case PPU_PRE_OFF+24: case PPU_PRE_OFF+25: case PPU_PRE_OFF+26: case PPU_PRE_OFF+27:
			case PPU_PRE_OFF+28: case PPU_PRE_OFF+29: case PPU_PRE_OFF+30: case PPU_PRE_OFF+31:
			case PPU_PRE_OFF+32: case PPU_PRE_OFF+33: case PPU_PRE_OFF+34: case PPU_PRE_OFF+35:
			case PPU_PRE_OFF+36: case PPU_PRE_OFF+37: case PPU_PRE_OFF+38: case PPU_PRE_OFF+39:
			case PPU_PRE_OFF+40: case PPU_PRE_OFF+41: case PPU_PRE_OFF+42: case PPU_PRE_OFF+43:
			case PPU_PRE_OFF+44: case PPU_PRE_OFF+45: case PPU_PRE_OFF+46: case PPU_PRE_OFF+47:
			case PPU_PRE_OFF+48: case PPU_PRE_OFF+49: case PPU_PRE_OFF+50: case PPU_PRE_OFF+51:
			case PPU_PRE_OFF+52: case PPU_PRE_OFF+53: case PPU_PRE_OFF+54: case PPU_PRE_OFF+55:
			case PPU_PRE_OFF+56: case PPU_PRE_OFF+57: case PPU_PRE_OFF+58: case PPU_PRE_OFF+59:
			case PPU_PRE_OFF+60: case PPU_PRE_OFF+61: case PPU_PRE_OFF+62: case PPU_PRE_OFF+63:
			case PPU_PRE_OFF+64: case PPU_PRE_OFF+65: case PPU_PRE_OFF+66: case PPU_PRE_OFF+67:
			case PPU_PRE_OFF+68: case PPU_PRE_OFF+69: case PPU_PRE_OFF+70: case PPU_PRE_OFF+71:
			case PPU_PRE_OFF+72: case PPU_PRE_OFF+73: case PPU_PRE_OFF+74: case PPU_PRE_OFF+75:
			case PPU_PRE_OFF+76: case PPU_PRE_OFF+77: case PPU_PRE_OFF+78: case PPU_PRE_OFF+79:
			case PPU_PRE_OFF+80: case PPU_PRE_OFF+81: case PPU_PRE_OFF+82: case PPU_PRE_OFF+83:
			case PPU_PRE_OFF+84: case PPU_PRE_OFF+85: case PPU_PRE_OFF+86: case PPU_PRE_OFF+87:
			case PPU_PRE_OFF+88: case PPU_PRE_OFF+89: case PPU_PRE_OFF+90: case PPU_PRE_OFF+91:
			case PPU_PRE_OFF+92: case PPU_PRE_OFF+93: case PPU_PRE_OFF+94: case PPU_PRE_OFF+95:
			case PPU_PRE_OFF+96: case PPU_PRE_OFF+97: case PPU_PRE_OFF+98: case PPU_PRE_OFF+99:
			case PPU_PRE_OFF+100: case PPU_PRE_OFF+101: case PPU_PRE_OFF+102: case PPU_PRE_OFF+103:
			case PPU_PRE_OFF+104: case PPU_PRE_OFF+105: case PPU_PRE_OFF+106: case PPU_PRE_OFF+107:
			case PPU_PRE_OFF+108: case PPU_PRE_OFF+109: case PPU_PRE_OFF+110: case PPU_PRE_OFF+111:
			case PPU_PRE_OFF+112: case PPU_PRE_OFF+113: case PPU_PRE_OFF+114: case PPU_PRE_OFF+115:
			case PPU_PRE_OFF+116: case PPU_PRE_OFF+117: case PPU_PRE_OFF+118: case PPU_PRE_OFF+119:
			case PPU_PRE_OFF+120: case PPU_PRE_OFF+121: case PPU_PRE_OFF+122: case PPU_PRE_OFF+123:
			case PPU_PRE_OFF+124: case PPU_PRE_OFF+125: case PPU_PRE_OFF+126: case PPU_PRE_OFF+127:
			case PPU_PRE_OFF+128: case PPU_PRE_OFF+129: case PPU_PRE_OFF+130: case PPU_PRE_OFF+131:
			case PPU_PRE_OFF+132: case PPU_PRE_OFF+133: case PPU_PRE_OFF+134: case PPU_PRE_OFF+135:
			case PPU_PRE_OFF+136: case PPU_PRE_OFF+137: case PPU_PRE_OFF+138: case PPU_PRE_OFF+139:
			case PPU_PRE_OFF+140: case PPU_PRE_OFF+141: case PPU_PRE_OFF+142: case PPU_PRE_OFF+143:
			case PPU_PRE_OFF+144: case PPU_PRE_OFF+145: case PPU_PRE_OFF+146: case PPU_PRE_OFF+147:
			case PPU_PRE_OFF+148: case PPU_PRE_OFF+149: case PPU_PRE_OFF+150: case PPU_PRE_OFF+151:
			case PPU_PRE_OFF+152: case PPU_PRE_OFF+153: case PPU_PRE_OFF+154: case PPU_PRE_OFF+155:
			case PPU_PRE_OFF+156: case PPU_PRE_OFF+157: case PPU_PRE_OFF+158: case PPU_PRE_OFF+159:
			case PPU_PRE_OFF+160: case PPU_PRE_OFF+161: case PPU_PRE_OFF+162: case PPU_PRE_OFF+163:
			case PPU_PRE_OFF+164: case PPU_PRE_OFF+165: case PPU_PRE_OFF+166: case PPU_PRE_OFF+167:
			case PPU_PRE_OFF+168: case PPU_PRE_OFF+169: case PPU_PRE_OFF+170: case PPU_PRE_OFF+171:
			case PPU_PRE_OFF+172: case PPU_PRE_OFF+173: case PPU_PRE_OFF+174: case PPU_PRE_OFF+175:
			case PPU_PRE_OFF+176: case PPU_PRE_OFF+177: case PPU_PRE_OFF+178: case PPU_PRE_OFF+179:
			case PPU_PRE_OFF+180: case PPU_PRE_OFF+181: case PPU_PRE_OFF+182: case PPU_PRE_OFF+183:
			case PPU_PRE_OFF+184: case PPU_PRE_OFF+185: case PPU_PRE_OFF+186: case PPU_PRE_OFF+187:
			case PPU_PRE_OFF+188: case PPU_PRE_OFF+189: case PPU_PRE_OFF+190: case PPU_PRE_OFF+191:
			case PPU_PRE_OFF+192: case PPU_PRE_OFF+193: case PPU_PRE_OFF+194: case PPU_PRE_OFF+195:
			case PPU_PRE_OFF+196: case PPU_PRE_OFF+197: case PPU_PRE_OFF+198: case PPU_PRE_OFF+199:
			case PPU_PRE_OFF+200: case PPU_PRE_OFF+201: case PPU_PRE_OFF+202: case PPU_PRE_OFF+203:
			case PPU_PRE_OFF+204: case PPU_PRE_OFF+205: case PPU_PRE_OFF+206: case PPU_PRE_OFF+207:
			case PPU_PRE_OFF+208: case PPU_PRE_OFF+209: case PPU_PRE_OFF+210: case PPU_PRE_OFF+211:
			case PPU_PRE_OFF+212: case PPU_PRE_OFF+213: case PPU_PRE_OFF+214: case PPU_PRE_OFF+215:
			case PPU_PRE_OFF+216: case PPU_PRE_OFF+217: case PPU_PRE_OFF+218: case PPU_PRE_OFF+219:
			case PPU_PRE_OFF+220: case PPU_PRE_OFF+221: case PPU_PRE_OFF+222: case PPU_PRE_OFF+223:
			case PPU_PRE_OFF+224: case PPU_PRE_OFF+225: case PPU_PRE_OFF+226: case PPU_PRE_OFF+227:
			case PPU_PRE_OFF+228: case PPU_PRE_OFF+229: case PPU_PRE_OFF+230: case PPU_PRE_OFF+231:
			case PPU_PRE_OFF+232: case PPU_PRE_OFF+233: case PPU_PRE_OFF+234: case PPU_PRE_OFF+235:
			case PPU_PRE_OFF+236: case PPU_PRE_OFF+237: case PPU_PRE_OFF+238: case PPU_PRE_OFF+239:
			case PPU_PRE_OFF+240: case PPU_PRE_OFF+241: case PPU_PRE_OFF+242: case PPU_PRE_OFF+243:
			case PPU_PRE_OFF+244: case PPU_PRE_OFF+245: case PPU_PRE_OFF+246: case PPU_PRE_OFF+247:
			case PPU_PRE_OFF+248: case PPU_PRE_OFF+249: case PPU_PRE_OFF+250: case PPU_PRE_OFF+251:
			case PPU_PRE_OFF+252: case PPU_PRE_OFF+253: case PPU_PRE_OFF+254: case PPU_PRE_OFF+255:
			/*case PPU_PRE_OFF+256:*/ case PPU_PRE_OFF+257: case PPU_PRE_OFF+258: case PPU_PRE_OFF+259:
			case PPU_PRE_OFF+260: case PPU_PRE_OFF+261: case PPU_PRE_OFF+262: case PPU_PRE_OFF+263:
			case PPU_PRE_OFF+264: case PPU_PRE_OFF+265: case PPU_PRE_OFF+266: case PPU_PRE_OFF+267:
			case PPU_PRE_OFF+268: case PPU_PRE_OFF+269: case PPU_PRE_OFF+270: case PPU_PRE_OFF+271:
			case PPU_PRE_OFF+272: case PPU_PRE_OFF+273: case PPU_PRE_OFF+274: case PPU_PRE_OFF+275:
			case PPU_PRE_OFF+276: case PPU_PRE_OFF+277: case PPU_PRE_OFF+278: case PPU_PRE_OFF+279:
			case PPU_PRE_OFF+280: case PPU_PRE_OFF+281: case PPU_PRE_OFF+282: case PPU_PRE_OFF+283:
			case PPU_PRE_OFF+284: case PPU_PRE_OFF+285: case PPU_PRE_OFF+286: case PPU_PRE_OFF+287:
			case PPU_PRE_OFF+288: case PPU_PRE_OFF+289: case PPU_PRE_OFF+290: case PPU_PRE_OFF+291:
			case PPU_PRE_OFF+292: case PPU_PRE_OFF+293: case PPU_PRE_OFF+294: case PPU_PRE_OFF+295:
			case PPU_PRE_OFF+296: case PPU_PRE_OFF+297: case PPU_PRE_OFF+298: case PPU_PRE_OFF+299:
			case PPU_PRE_OFF+300: case PPU_PRE_OFF+301: case PPU_PRE_OFF+302: case PPU_PRE_OFF+303:
			case PPU_PRE_OFF+304: case PPU_PRE_OFF+305: case PPU_PRE_OFF+306: case PPU_PRE_OFF+307:
			case PPU_PRE_OFF+308: case PPU_PRE_OFF+309: case PPU_PRE_OFF+310: case PPU_PRE_OFF+311:
			case PPU_PRE_OFF+312: case PPU_PRE_OFF+313: case PPU_PRE_OFF+314: case PPU_PRE_OFF+315:
			case PPU_PRE_OFF+316: case PPU_PRE_OFF+317: case PPU_PRE_OFF+318: case PPU_PRE_OFF+319:
			case PPU_PRE_OFF+320: case PPU_PRE_OFF+321: case PPU_PRE_OFF+322: case PPU_PRE_OFF+323:
			case PPU_PRE_OFF+324: case PPU_PRE_OFF+325: case PPU_PRE_OFF+326: case PPU_PRE_OFF+327:
			case PPU_PRE_OFF+328: case PPU_PRE_OFF+329: case PPU_PRE_OFF+330: case PPU_PRE_OFF+331:
			case PPU_PRE_OFF+332: case PPU_PRE_OFF+333: case PPU_PRE_OFF+334: case PPU_PRE_OFF+335:
			case PPU_PRE_OFF+336: case PPU_PRE_OFF+337: case PPU_PRE_OFF+338: /*case PPU_PRE_OFF+339:*/
				goto add_dot;
			case PPU_PRE_OFF+0: /* VBlank ends at first dot of the pre-render line */
				ppu.Reg[2] &= ~(PPU_FLAG_SPRITEZERO | PPU_FLAG_OVERFLOW);
				goto add_dot;
			case PPU_PRE_OFF+2: /* Though results are better when clearing it a bit later */
				#if PPU_DEBUG_VSYNC
				printf("PPU End VBlank\n");
				#endif
				ppu.Reg[2] &= ~(PPU_FLAG_VBLANK);
				goto add_dot;
			case PPU_PRE_OFF+7: //special case
				ppu.NMIallowed = false;
				goto add_dot;
			case PPU_PRE_OFF+256:
				initSpriteTileFetch();
				goto add_dot;
			case PPU_PRE_OFF+339:
				ppu.OddFrame = ppu.OddArr[ppu.OddNum^=1];
				goto add_dot;
			//line 241
			/*case PPU_L241+0: case PPU_L241+1: case PPU_L241+2: case PPU_L241+3:
			case PPU_L241+4:*/ case PPU_L241+5: case PPU_L241+6: case PPU_L241+7:
			case PPU_L241+8: case PPU_L241+9: case PPU_L241+10: case PPU_L241+11:
			case PPU_L241+12: case PPU_L241+13: case PPU_L241+14: case PPU_L241+15:
			case PPU_L241+16: case PPU_L241+17: case PPU_L241+18: case PPU_L241+19:
			case PPU_L241+20: case PPU_L241+21: case PPU_L241+22: case PPU_L241+23:
			case PPU_L241+24: case PPU_L241+25: case PPU_L241+26: case PPU_L241+27:
			case PPU_L241+28: case PPU_L241+29: case PPU_L241+30: case PPU_L241+31:
			case PPU_L241+32: case PPU_L241+33: case PPU_L241+34: case PPU_L241+35:
			case PPU_L241+36: case PPU_L241+37: case PPU_L241+38: case PPU_L241+39:
			case PPU_L241+40: case PPU_L241+41: case PPU_L241+42: case PPU_L241+43:
			case PPU_L241+44: case PPU_L241+45: case PPU_L241+46: case PPU_L241+47:
			case PPU_L241+48: case PPU_L241+49: case PPU_L241+50: case PPU_L241+51:
			case PPU_L241+52: case PPU_L241+53: case PPU_L241+54: case PPU_L241+55:
			case PPU_L241+56: case PPU_L241+57: case PPU_L241+58: case PPU_L241+59:
			case PPU_L241+60: case PPU_L241+61: case PPU_L241+62: case PPU_L241+63:
			case PPU_L241+64: case PPU_L241+65: case PPU_L241+66: case PPU_L241+67:
			case PPU_L241+68: case PPU_L241+69: case PPU_L241+70: case PPU_L241+71:
			case PPU_L241+72: case PPU_L241+73: case PPU_L241+74: case PPU_L241+75:
			case PPU_L241+76: case PPU_L241+77: case PPU_L241+78: case PPU_L241+79:
			case PPU_L241+80: case PPU_L241+81: case PPU_L241+82: case PPU_L241+83:
			case PPU_L241+84: case PPU_L241+85: case PPU_L241+86: case PPU_L241+87:
			case PPU_L241+88: case PPU_L241+89: case PPU_L241+90: case PPU_L241+91:
			case PPU_L241+92: case PPU_L241+93: case PPU_L241+94: case PPU_L241+95:
			case PPU_L241+96: case PPU_L241+97: case PPU_L241+98: case PPU_L241+99:
			case PPU_L241+100: case PPU_L241+101: case PPU_L241+102: case PPU_L241+103:
			case PPU_L241+104: case PPU_L241+105: case PPU_L241+106: case PPU_L241+107:
			case PPU_L241+108: case PPU_L241+109: case PPU_L241+110: case PPU_L241+111:
			case PPU_L241+112: case PPU_L241+113: case PPU_L241+114: case PPU_L241+115:
			case PPU_L241+116: case PPU_L241+117: case PPU_L241+118: case PPU_L241+119:
			case PPU_L241+120: case PPU_L241+121: case PPU_L241+122: case PPU_L241+123:
			case PPU_L241+124: case PPU_L241+125: case PPU_L241+126: case PPU_L241+127:
			case PPU_L241+128: case PPU_L241+129: case PPU_L241+130: case PPU_L241+131:
			case PPU_L241+132: case PPU_L241+133: case PPU_L241+134: case PPU_L241+135:
			case PPU_L241+136: case PPU_L241+137: case PPU_L241+138: case PPU_L241+139:
			case PPU_L241+140: case PPU_L241+141: case PPU_L241+142: case PPU_L241+143:
			case PPU_L241+144: case PPU_L241+145: case PPU_L241+146: case PPU_L241+147:
			case PPU_L241+148: case PPU_L241+149: case PPU_L241+150: case PPU_L241+151:
			case PPU_L241+152: case PPU_L241+153: case PPU_L241+154: case PPU_L241+155:
			case PPU_L241+156: case PPU_L241+157: case PPU_L241+158: case PPU_L241+159:
			case PPU_L241+160: case PPU_L241+161: case PPU_L241+162: case PPU_L241+163:
			case PPU_L241+164: case PPU_L241+165: case PPU_L241+166: case PPU_L241+167:
			case PPU_L241+168: case PPU_L241+169: case PPU_L241+170: case PPU_L241+171:
			case PPU_L241+172: case PPU_L241+173: case PPU_L241+174: case PPU_L241+175:
			case PPU_L241+176: case PPU_L241+177: case PPU_L241+178: case PPU_L241+179:
			case PPU_L241+180: case PPU_L241+181: case PPU_L241+182: case PPU_L241+183:
			case PPU_L241+184: case PPU_L241+185: case PPU_L241+186: case PPU_L241+187:
			case PPU_L241+188: case PPU_L241+189: case PPU_L241+190: case PPU_L241+191:
			case PPU_L241+192: case PPU_L241+193: case PPU_L241+194: case PPU_L241+195:
			case PPU_L241+196: case PPU_L241+197: case PPU_L241+198: case PPU_L241+199:
			case PPU_L241+200: case PPU_L241+201: case PPU_L241+202: case PPU_L241+203:
			case PPU_L241+204: case PPU_L241+205: case PPU_L241+206: case PPU_L241+207:
			case PPU_L241+208: case PPU_L241+209: case PPU_L241+210: case PPU_L241+211:
			case PPU_L241+212: case PPU_L241+213: case PPU_L241+214: case PPU_L241+215:
			case PPU_L241+216: case PPU_L241+217: case PPU_L241+218: case PPU_L241+219:
			case PPU_L241+220: case PPU_L241+221: case PPU_L241+222: case PPU_L241+223:
			case PPU_L241+224: case PPU_L241+225: case PPU_L241+226: case PPU_L241+227:
			case PPU_L241+228: case PPU_L241+229: case PPU_L241+230: case PPU_L241+231:
			case PPU_L241+232: case PPU_L241+233: case PPU_L241+234: case PPU_L241+235:
			case PPU_L241+236: case PPU_L241+237: case PPU_L241+238: case PPU_L241+239:
			case PPU_L241+240: case PPU_L241+241: case PPU_L241+242: case PPU_L241+243:
			case PPU_L241+244: case PPU_L241+245: case PPU_L241+246: case PPU_L241+247:
			case PPU_L241+248: case PPU_L241+249: case PPU_L241+250: case PPU_L241+251:
			case PPU_L241+252: case PPU_L241+253: case PPU_L241+254: case PPU_L241+255:
			case PPU_L241+256: case PPU_L241+257: case PPU_L241+258: case PPU_L241+259:
			case PPU_L241+260: case PPU_L241+261: case PPU_L241+262: case PPU_L241+263:
			case PPU_L241+264: case PPU_L241+265: case PPU_L241+266: case PPU_L241+267:
			case PPU_L241+268: case PPU_L241+269: case PPU_L241+270: case PPU_L241+271:
			case PPU_L241+272: case PPU_L241+273: case PPU_L241+274: case PPU_L241+275:
			case PPU_L241+276: case PPU_L241+277: case PPU_L241+278: case PPU_L241+279:
			case PPU_L241+280: case PPU_L241+281: case PPU_L241+282: case PPU_L241+283:
			case PPU_L241+284: case PPU_L241+285: case PPU_L241+286: case PPU_L241+287:
			case PPU_L241+288: case PPU_L241+289: case PPU_L241+290: case PPU_L241+291:
			case PPU_L241+292: case PPU_L241+293: case PPU_L241+294: case PPU_L241+295:
			case PPU_L241+296: case PPU_L241+297: case PPU_L241+298: case PPU_L241+299:
			case PPU_L241+300: case PPU_L241+301: case PPU_L241+302: case PPU_L241+303:
			case PPU_L241+304: case PPU_L241+305: case PPU_L241+306: case PPU_L241+307:
			case PPU_L241+308: case PPU_L241+309: case PPU_L241+310: case PPU_L241+311:
			case PPU_L241+312: case PPU_L241+313: case PPU_L241+314: case PPU_L241+315:
			case PPU_L241+316: case PPU_L241+317: case PPU_L241+318: case PPU_L241+319:
			case PPU_L241+320: case PPU_L241+321: case PPU_L241+322: case PPU_L241+323:
			case PPU_L241+324: case PPU_L241+325: case PPU_L241+326: case PPU_L241+327:
			case PPU_L241+328: case PPU_L241+329: case PPU_L241+330: case PPU_L241+331:
			case PPU_L241+332: case PPU_L241+333: case PPU_L241+334: case PPU_L241+335:
			case PPU_L241+336: case PPU_L241+337: case PPU_L241+338: /*case PPU_L241+339:*/
				goto add_dot;
			case PPU_L241+0:
				ppu.ReadReg2 = false;
				goto add_dot;
			case PPU_L241+1:
				ppu.ReadReg2 = false;
				goto add_dot;
			case PPU_L241+2:
				ppu.NMITriggered = false;
				if(!ppu.ReadReg2)
					ppu.Reg[2] |= PPU_FLAG_VBLANK;
				#if PPU_DEBUG_VSYNC
				printf("PPU Start VBlank\n");
				#endif
				ppu.ReadReg2 = false;
				goto add_dot;
			case PPU_L241+3:
				ppu.ReadReg2 = false;
				goto add_dot;
			case PPU_L241+4:
				if(ppu.Reg[2] & PPU_FLAG_VBLANK)
					ppu.NMIallowed = true;
				ppu.ReadReg2 = false;
				goto add_dot;
			case PPU_L241+339: //ready for idle cycles, request reset now
				if(ppu.reqReset)
				{
					ppu.reqReset = false;
					cpuSoftReset();
				}
				goto add_dot;
			//idle
			case PPU_IDLE+0: case PPU_IDLE+1: case PPU_IDLE+2: case PPU_IDLE+3:
			case PPU_IDLE+4: case PPU_IDLE+5: case PPU_IDLE+6: case PPU_IDLE+7:
			case PPU_IDLE+8: case PPU_IDLE+9: case PPU_IDLE+10: case PPU_IDLE+11:
			case PPU_IDLE+12: case PPU_IDLE+13: case PPU_IDLE+14: case PPU_IDLE+15:
			case PPU_IDLE+16: case PPU_IDLE+17: case PPU_IDLE+18: case PPU_IDLE+19:
			case PPU_IDLE+20: case PPU_IDLE+21: case PPU_IDLE+22: case PPU_IDLE+23:
			case PPU_IDLE+24: case PPU_IDLE+25: case PPU_IDLE+26: case PPU_IDLE+27:
			case PPU_IDLE+28: case PPU_IDLE+29: case PPU_IDLE+30: case PPU_IDLE+31:
			case PPU_IDLE+32: case PPU_IDLE+33: case PPU_IDLE+34: case PPU_IDLE+35:
			case PPU_IDLE+36: case PPU_IDLE+37: case PPU_IDLE+38: case PPU_IDLE+39:
			case PPU_IDLE+40: case PPU_IDLE+41: case PPU_IDLE+42: case PPU_IDLE+43:
			case PPU_IDLE+44: case PPU_IDLE+45: case PPU_IDLE+46: case PPU_IDLE+47:
			case PPU_IDLE+48: case PPU_IDLE+49: case PPU_IDLE+50: case PPU_IDLE+51:
			case PPU_IDLE+52: case PPU_IDLE+53: case PPU_IDLE+54: case PPU_IDLE+55:
			case PPU_IDLE+56: case PPU_IDLE+57: case PPU_IDLE+58: case PPU_IDLE+59:
			case PPU_IDLE+60: case PPU_IDLE+61: case PPU_IDLE+62: case PPU_IDLE+63:
			case PPU_IDLE+64: case PPU_IDLE+65: case PPU_IDLE+66: case PPU_IDLE+67:
			case PPU_IDLE+68: case PPU_IDLE+69: case PPU_IDLE+70: case PPU_IDLE+71:
			case PPU_IDLE+72: case PPU_IDLE+73: case PPU_IDLE+74: case PPU_IDLE+75:
			case PPU_IDLE+76: case PPU_IDLE+77: case PPU_IDLE+78: case PPU_IDLE+79:
			case PPU_IDLE+80: case PPU_IDLE+81: case PPU_IDLE+82: case PPU_IDLE+83:
			case PPU_IDLE+84: case PPU_IDLE+85: case PPU_IDLE+86: case PPU_IDLE+87:
			case PPU_IDLE+88: case PPU_IDLE+89: case PPU_IDLE+90: case PPU_IDLE+91:
			case PPU_IDLE+92: case PPU_IDLE+93: case PPU_IDLE+94: case PPU_IDLE+95:
			case PPU_IDLE+96: case PPU_IDLE+97: case PPU_IDLE+98: case PPU_IDLE+99:
			case PPU_IDLE+100: case PPU_IDLE+101: case PPU_IDLE+102: case PPU_IDLE+103:
			case PPU_IDLE+104: case PPU_IDLE+105: case PPU_IDLE+106: case PPU_IDLE+107:
			case PPU_IDLE+108: case PPU_IDLE+109: case PPU_IDLE+110: case PPU_IDLE+111:
			case PPU_IDLE+112: case PPU_IDLE+113: case PPU_IDLE+114: case PPU_IDLE+115:
			case PPU_IDLE+116: case PPU_IDLE+117: case PPU_IDLE+118: case PPU_IDLE+119:
			case PPU_IDLE+120: case PPU_IDLE+121: case PPU_IDLE+122: case PPU_IDLE+123:
			case PPU_IDLE+124: case PPU_IDLE+125: case PPU_IDLE+126: case PPU_IDLE+127:
			case PPU_IDLE+128: case PPU_IDLE+129: case PPU_IDLE+130: case PPU_IDLE+131:
			case PPU_IDLE+132: case PPU_IDLE+133: case PPU_IDLE+134: case PPU_IDLE+135:
			case PPU_IDLE+136: case PPU_IDLE+137: case PPU_IDLE+138: case PPU_IDLE+139:
			case PPU_IDLE+140: case PPU_IDLE+141: case PPU_IDLE+142: case PPU_IDLE+143:
			case PPU_IDLE+144: case PPU_IDLE+145: case PPU_IDLE+146: case PPU_IDLE+147:
			case PPU_IDLE+148: case PPU_IDLE+149: case PPU_IDLE+150: case PPU_IDLE+151:
			case PPU_IDLE+152: case PPU_IDLE+153: case PPU_IDLE+154: case PPU_IDLE+155:
			case PPU_IDLE+156: case PPU_IDLE+157: case PPU_IDLE+158: case PPU_IDLE+159:
			case PPU_IDLE+160: case PPU_IDLE+161: case PPU_IDLE+162: case PPU_IDLE+163:
			case PPU_IDLE+164: case PPU_IDLE+165: case PPU_IDLE+166: case PPU_IDLE+167:
			case PPU_IDLE+168: case PPU_IDLE+169: case PPU_IDLE+170: case PPU_IDLE+171:
			case PPU_IDLE+172: case PPU_IDLE+173: case PPU_IDLE+174: case PPU_IDLE+175:
			case PPU_IDLE+176: case PPU_IDLE+177: case PPU_IDLE+178: case PPU_IDLE+179:
			case PPU_IDLE+180: case PPU_IDLE+181: case PPU_IDLE+182: case PPU_IDLE+183:
			case PPU_IDLE+184: case PPU_IDLE+185: case PPU_IDLE+186: case PPU_IDLE+187:
			case PPU_IDLE+188: case PPU_IDLE+189: case PPU_IDLE+190: case PPU_IDLE+191:
			case PPU_IDLE+192: case PPU_IDLE+193: case PPU_IDLE+194: case PPU_IDLE+195:
			case PPU_IDLE+196: case PPU_IDLE+197: case PPU_IDLE+198: case PPU_IDLE+199:
			case PPU_IDLE+200: case PPU_IDLE+201: case PPU_IDLE+202: case PPU_IDLE+203:
			case PPU_IDLE+204: case PPU_IDLE+205: case PPU_IDLE+206: case PPU_IDLE+207:
			case PPU_IDLE+208: case PPU_IDLE+209: case PPU_IDLE+210: case PPU_IDLE+211:
			case PPU_IDLE+212: case PPU_IDLE+213: case PPU_IDLE+214: case PPU_IDLE+215:
			case PPU_IDLE+216: case PPU_IDLE+217: case PPU_IDLE+218: case PPU_IDLE+219:
			case PPU_IDLE+220: case PPU_IDLE+221: case PPU_IDLE+222: case PPU_IDLE+223:
			case PPU_IDLE+224: case PPU_IDLE+225: case PPU_IDLE+226: case PPU_IDLE+227:
			case PPU_IDLE+228: case PPU_IDLE+229: case PPU_IDLE+230: case PPU_IDLE+231:
			case PPU_IDLE+232: case PPU_IDLE+233: case PPU_IDLE+234: case PPU_IDLE+235:
			case PPU_IDLE+236: case PPU_IDLE+237: case PPU_IDLE+238: case PPU_IDLE+239:
			case PPU_IDLE+240: case PPU_IDLE+241: case PPU_IDLE+242: case PPU_IDLE+243:
			case PPU_IDLE+244: case PPU_IDLE+245: case PPU_IDLE+246: case PPU_IDLE+247:
			case PPU_IDLE+248: case PPU_IDLE+249: case PPU_IDLE+250: case PPU_IDLE+251:
			case PPU_IDLE+252: case PPU_IDLE+253: case PPU_IDLE+254: case PPU_IDLE+255:
			case PPU_IDLE+256: case PPU_IDLE+257: case PPU_IDLE+258: case PPU_IDLE+259:
			case PPU_IDLE+260: case PPU_IDLE+261: case PPU_IDLE+262: case PPU_IDLE+263:
			case PPU_IDLE+264: case PPU_IDLE+265: case PPU_IDLE+266: case PPU_IDLE+267:
			case PPU_IDLE+268: case PPU_IDLE+269: case PPU_IDLE+270: case PPU_IDLE+271:
			case PPU_IDLE+272: case PPU_IDLE+273: case PPU_IDLE+274: case PPU_IDLE+275:
			case PPU_IDLE+276: case PPU_IDLE+277: case PPU_IDLE+278: case PPU_IDLE+279:
			case PPU_IDLE+280: case PPU_IDLE+281: case PPU_IDLE+282: case PPU_IDLE+283:
			case PPU_IDLE+284: case PPU_IDLE+285: case PPU_IDLE+286: case PPU_IDLE+287:
			case PPU_IDLE+288: case PPU_IDLE+289: case PPU_IDLE+290: case PPU_IDLE+291:
			case PPU_IDLE+292: case PPU_IDLE+293: case PPU_IDLE+294: case PPU_IDLE+295:
			case PPU_IDLE+296: case PPU_IDLE+297: case PPU_IDLE+298: case PPU_IDLE+299:
			case PPU_IDLE+300: case PPU_IDLE+301: case PPU_IDLE+302: case PPU_IDLE+303:
			case PPU_IDLE+304: case PPU_IDLE+305: case PPU_IDLE+306: case PPU_IDLE+307:
			case PPU_IDLE+308: case PPU_IDLE+309: case PPU_IDLE+310: case PPU_IDLE+311:
			case PPU_IDLE+312: case PPU_IDLE+313: case PPU_IDLE+314: case PPU_IDLE+315:
			case PPU_IDLE+316: case PPU_IDLE+317: case PPU_IDLE+318: case PPU_IDLE+319:
			case PPU_IDLE+320: case PPU_IDLE+321: case PPU_IDLE+322: case PPU_IDLE+323:
			case PPU_IDLE+324: case PPU_IDLE+325: case PPU_IDLE+326: case PPU_IDLE+327:
			case PPU_IDLE+328: case PPU_IDLE+329: case PPU_IDLE+330: case PPU_IDLE+331:
			case PPU_IDLE+332: case PPU_IDLE+333: case PPU_IDLE+334: case PPU_IDLE+335:
			case PPU_IDLE+336: case PPU_IDLE+337: case PPU_IDLE+338: case PPU_IDLE+339:
				goto add_dot;
			//common functions
			case 340:
			case PPU_OFF+340:
			case PPU_PRE+340:
			case PPU_PRE_OFF+340:
			case PPU_L241+340:
			case PPU_IDLE+340:
			last_dot:
				line = ppuLastDot(line);
				dot = ppuSetDotType(0,line);
				break;
			add_dot:
				#ifdef DISPLAY_PPUWRITES
				if(ppu.ppuwrite)
					textureImage[(dot%DOTS)+(line*DOTS)] = ppu.highlightcolor;
				ppu.ppuwrite = false;
				#endif
				dot++;
				break;
			default:
				printf("PPU: Unhandled dot %i!\n", dot);
				break;
		}
	}
	ppu.curDot = dot;
}

void ppuPrintCurLineDot()
{
	printf("%i %i %02x\n", ppu.curLine, ppu.curDot, ppu.OAMpos);
}

static uint8_t ppuDoSprites(uint8_t color, uint16_t dot)
{
	uint8_t sprVal = ppu.SprLUT[dot];
	if((sprVal&0x80))
	{
		if(color && (sprVal&0x20) && dot < 255)
		{
			ppu.Reg[2] |= PPU_FLAG_SPRITEZERO;
			#if PPU_DEBUG_ULTRA
			printf("Zero sprite hit at x %i y %i cSpriteDot %i "
						"table %04x color %02x sprCol %02x\n", dot, ppu.curLine, cSpriteDot, ppuGetVramTbl((ppu.Reg[0]&3)<<10), color, sprCol);
			#endif
			//if(ppu.curLine < 224)
			//	ppuDebugPauseFrame = true;
		}
		if(!(color && (sprVal&0x40)))
			color = sprVal&0x1F;
	}
	return color;
}

FIXNES_ALWAYSINLINE bool ppuDrawDone()
{
	if(ppu.FrameDone)
	{
		//printf("%i\n",ppuCycles);
		//ppuCycles = 0;
		ppu.FrameDone = false;
		return true;
	}
	return false;
}

void ppuSet8(uint16_t addr, uint8_t val)
{
	ppu.lastVal = val;
#ifdef DISPLAY_PPUWRITES
	ppu.ppuwrite = true;
#endif
	switch(addr&7)
	{
		case 0:
			ppu.Reg[0] = val;
			ppu.TmpVramAddr &= ~0xC00;
			ppu.TmpVramAddr |= ((val&3)<<10);
			ppuSetSprite816vals();
			//printf("%d %d %d\n", (PPU_Reg[0] & PPU_BACKGROUND_ADDR) != 0, (PPU_Reg[0] & PPU_SPRITE_ADDR) != 0, (PPU_Reg[0] & PPU_SPRITE_8_16) != 0);
			break;
		case 1:
			if((ppu.Reg[1]^val)&(PPU_GRAY|0xE0))
			{
				uint8_t i;
				for(i = 0; i < 0x20; i++)
					ppu.PALRAM2[i] = (ppu.PALRAM[i]&((val&PPU_GRAY)?0x30:0x3F))|((val&0xE0)<<1);
			}
			if((val & (PPU_BG_ENABLE | PPU_SPRITE_ENABLE)) == 0) //disabled rendering
			{
				/* For MMC5 Scanline Detect */
				ppuInFrame = false;
			}
			ppu.Reg[1] = val;
			//possibly updated
			ppu.curDot = ppuSetDotType(ppu.curDot,ppu.curLine);
			if(ppu.curDot < DOTS)
			{
				if(ppu.curDot < 8)
				{
					ppu.BGEnable = (val & PPU_BG_8PX) && (val & PPU_BG_ENABLE);
					ppu.SprEnable = (val & PPU_SPRITE_8PX) && (val & PPU_SPRITE_ENABLE);
				}
				else
				{
					ppu.BGEnable = (val & PPU_BG_ENABLE);
					ppu.SprEnable = (val & PPU_SPRITE_ENABLE);
				}
			}
			break;
		case 3:
			#if PPU_DEBUG_ULTRA
			printf("ppu.OAMpos at line %i dot %i was %02x set to %02x\n", ppu.curLine, ppu.curDot, ppu.OAMpos, val);
			#endif
			ppu.OAMpos = val;
			break;
		case 4:
			#if PPU_DEBUG_ULTRA
			printf("Setting OAM at line %i dot %i addr %02x to %02x\n", ppu.curLine, ppu.curDot, ppu.OAMpos, val);
			#endif
			if((ppu.OAMpos&3) == 2) val &= 0xE3;
			ppu.OAM[ppu.OAMpos++] = val;
			break;
		case 5:
			#if PPU_DEBUG_ULTRA
			printf("ppuScrollWrite (%d) %02x pc %04x\n", ppu.TmpWrite, val, cpuGetPc());
			#endif
			if(!ppu.TmpWrite)
			{
				ppu.TmpWrite = true;
				ppu.FineXScroll = val&7;
				ppu.TmpVramAddr &= ~0x1F;
				ppu.TmpVramAddr |= ((val>>3)&0x1F);
			}
			else
			{
				ppu.TmpWrite = false;
				ppu.TmpVramAddr &= ~0x73E0;
				ppu.TmpVramAddr |= ((val&7)<<12) | ((val>>3)<<5);
			}
			break;
		case 6:
			#if PPU_DEBUG_ULTRA
			printf("ppu.VramAddrWrite (%d) %02x pc %04x\n", ppu.TmpWrite, val, cpuGetPc());
			#endif
			if(!ppu.TmpWrite)
			{
				ppu.TmpWrite = true;
				ppu.TmpVramAddr &= 0xFF;
				ppu.TmpVramAddr |= ((val&0x3F)<<8);
			}
			else
			{
				ppu.TmpWrite = false;
				ppu.TmpVramAddr &= ~0xFF;
				ppu.TmpVramAddr |= val;
				ppu.VramAddr = ppu.TmpVramAddr;
				//For MMC3 IRQ (Shadow Read)
				if((ppu.VramAddr&0x3FFF) < 0x2000)
					memPPUGet8(ppu.VramAddr&0x3FFF);
			}
			break;
		case 7:
			memPPUSet8(ppu.VramAddr&0x3FFF, val);
			ppu.VramAddr += (ppu.Reg[0] & PPU_INC_AMOUNT) ? 32 : 1;
			//For MMC3 IRQ (Shadow Read)
			if((ppu.VramAddr&0x3FFF) < 0x2000)
				memPPUGet8(ppu.VramAddr&0x3FFF);
			break;
		default: //case 2
			break;
	}
}

uint8_t ppuGet8(uint16_t addr)
{
	uint8_t ret;
	switch(addr&7)
	{
		case 2:
			ret = ppu.Reg[2];
			ppu.Reg[2] &= ~PPU_FLAG_VBLANK;
			if(ret & PPU_FLAG_VBLANK)
			{
				ppu.VBlankFlagCleared = true;
				ppu.VBlankClearCycle = true;
			}
			ppu.TmpWrite = false;
			ppu.ReadReg2 = true;
			break;
		case 4:
			if(ppu.Reg[2] & PPU_FLAG_VBLANK || (ppu.Reg[1] & (PPU_BG_ENABLE | PPU_SPRITE_ENABLE)) == 0)
				ret = ppu.OAM[ppu.OAMpos];
			else
				ret = ppu.TmpOAMVal;
			//printf("Cycle %i line %i val %02x\n", ppu.curDot, ppu.curLine, ret);
			break;
		case 7:
			if((ppu.VramAddr&0x3FFF) >= 0x3F00) //very special case
			{
				//dont use existing read buf, get palette directly
				ret = memPPUGet8(ppu.VramAddr&0x3FFF);
				//read vram as if its in the 2FXX region
				ppu.VramReadBuf = memPPUGet8(ppu.VramAddr&0x2FFF);
			}
			else //normal ppu read
			{
				mapperChrMode = 2;
				ret = ppu.VramReadBuf;
				ppu.VramReadBuf = memPPUGet8(ppu.VramAddr&0x3FFF);
			}
			ppu.VramAddr += (ppu.Reg[0] & PPU_INC_AMOUNT) ? 32 : 1;
			//For MMC3 IRQ (Shadow Read)
			if((ppu.VramAddr&0x3FFF) < 0x2000)
				memPPUGet8(ppu.VramAddr&0x3FFF);
			break;
		default:
			ret = ppu.lastVal;
			break;
	}
	//if(ret & PPU_FLAG_VBLANK)
	//printf("ppuGet8 %04x:%02x\n",reg,ret);
	ppu.lastVal = ret;
	return ret;
}

uint8_t ppuNMI()
{
	if(ppu.VBlankFlagCleared && !ppu.VBlankClearCycle)
	{
		ppu.VBlankFlagCleared = false;
		ppu.NMIallowed = false;
	}
	if(ppu.CurNMIStat && ppu.NMIallowed)
	{
		if(ppu.NMITriggered == false)
		{
			ppu.NMITriggered = true;
			return PPU_NMI;
		}
		else
			return 0;
	}
	ppu.NMITriggered = false;
	return 0;
}

void ppuDumpMem()
{
	FILE *f = fopen("PPU_VRAM.bin","wb");
	if(f)
	{
		fwrite(ppu.VRAM,1,0x1000,f);
		fclose(f);
	}
	f = fopen("PPU_OAM.bin","wb");
	if(f)
	{
		fwrite(ppu.OAM,1,0x100,f);
		fclose(f);
	}
	f = fopen("PPU_Sprites.bin","wb");
	if(f)
	{
		fwrite(ppu.SprLUT,1,0x100,f);
		fclose(f);
	}
}

uint16_t ppuGetCurVramAddr()
{
	return ppu.VramAddr;
}

void ppuSetNameTblSingleLower()
{
	ppu.NameTbl[0] = 0; ppu.NameTbl[1] = 0; ppu.NameTbl[2] = 0; ppu.NameTbl[3] = 0;
	ppuSetVRAMBankPtr();
}

void ppuSetNameTblSingleUpper()
{
	ppu.NameTbl[0] = 0x400; ppu.NameTbl[1] = 0x400; ppu.NameTbl[2] = 0x400; ppu.NameTbl[3] = 0x400;
	ppuSetVRAMBankPtr();
}

void ppuSetNameTblVertical()
{
	ppu.NameTbl[0] = 0; ppu.NameTbl[1] = 0x400; ppu.NameTbl[2] = 0; ppu.NameTbl[3] = 0x400;
	ppuSetVRAMBankPtr();
}

void ppuSetNameTblHorizontal()
{
	ppu.NameTbl[0] = 0; ppu.NameTbl[1] = 0; ppu.NameTbl[2] = 0x400; ppu.NameTbl[3] = 0x400;
	ppuSetVRAMBankPtr();
}

void ppuSetNameTbl4Screen()
{
	ppu4Screen = true;
	ppu.NameTbl[0] = 0; ppu.NameTbl[1] = 0x400; ppu.NameTbl[2] = 0x800; ppu.NameTbl[3] = 0xC00;
	ppuSetVRAMBankPtr();
}

void ppuSetNameTblCustom(uint16_t addrA, uint16_t addrB, uint16_t addrC, uint16_t addrD)
{
	//printf("%04x %04x %04x %04x\n", addrA, addrB, addrC, addrD);
	//ppuPrintppu.curLineDot();
	ppu.NameTbl[0] = addrA; ppu.NameTbl[1] = addrB; ppu.NameTbl[2] = addrC; ppu.NameTbl[3] = addrD;
	ppuSetVRAMBankPtr();
}

uint8_t ppuGetVRAM0(uint16_t addr)
{
	return ppu.VRAMBank0Ptr[addr&0x3FF];
}
uint8_t ppuGetVRAM1(uint16_t addr)
{
	return ppu.VRAMBank1Ptr[addr&0x3FF];
}
uint8_t ppuGetVRAM2(uint16_t addr)
{
	return ppu.VRAMBank2Ptr[addr&0x3FF];
}
uint8_t ppuGetVRAM3(uint16_t addr)
{
	return ppu.VRAMBank3Ptr[addr&0x3FF];
}

void ppuSetVRAM0(uint16_t addr, uint8_t val)
{
	ppu.VRAMBank0Ptr[addr&0x3FF] = val;
}
void ppuSetVRAM1(uint16_t addr, uint8_t val)
{
	ppu.VRAMBank1Ptr[addr&0x3FF] = val;
}
void ppuSetVRAM2(uint16_t addr, uint8_t val)
{
	ppu.VRAMBank2Ptr[addr&0x3FF] = val;
}
void ppuSetVRAM3(uint16_t addr, uint8_t val)
{
	ppu.VRAMBank3Ptr[addr&0x3FF] = val;
}

uint8_t ppuGetPALRAM(uint16_t addr)
{
	return ppu.PALRAM[addr&0x1F]&((ppu.Reg[1]&PPU_GRAY)?0x30:0x3F);
}

void ppuSetPALRAM(uint16_t addr, uint8_t val)
{
	addr&=0x1F;
	ppu.PALRAM[addr] = val;
	ppu.PALRAM2[addr] = (val&((ppu.Reg[1]&PPU_GRAY)?0x30:0x3F))|((ppu.Reg[1]&0xE0)<<1);
}

void ppuSetPALRAMMirror(uint16_t addr, uint8_t val)
{
	addr&=0xF; //used for 00,04,08 and 0C
	ppu.PALRAM[0x10|addr] = ppu.PALRAM[addr] = val;
	ppu.PALRAM2[0x10|addr] = ppu.PALRAM2[addr] = (val&((ppu.Reg[1]&PPU_GRAY)?0x30:0x3F))|((ppu.Reg[1]&0xE0)<<1);
}

//64x12 1BPP "Track"
static const uint8_t ppuNSFTextTrack[96] =
{
	0x0C, 0x1C, 0x03, 0xD8, 0x7C, 0x71, 0xC0, 0x00, 0x0C, 0x1C, 0x07, 0xF8, 0xFE, 0x73, 0x80, 0x00, 
	0x0C, 0x1C, 0x06, 0x39, 0xE2, 0x77, 0x00, 0x00, 0x0C, 0x1C, 0x07, 0x39, 0xC0, 0x7E, 0x00, 0x00, 
	0x0C, 0x1C, 0x07, 0xF9, 0xC0, 0x7C, 0x00, 0x00, 0x0C, 0x1C, 0x01, 0xF9, 0xC0, 0x7C, 0x00, 0x00, 
	0x0C, 0x1E, 0x60, 0x38, 0xE2, 0x7E, 0x00, 0x00, 0x0C, 0x1F, 0xE3, 0xF8, 0xFE, 0x77, 0x00, 0x00, 
	0x0C, 0x1D, 0xC3, 0xF0, 0x3C, 0x73, 0xC0, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 
	0xFF, 0xC0, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 
};

//128x12 1BPP "0123456789/"
static const uint8_t ppuNsfTextRest[192] =
{
	0x0E, 0x1F, 0xF7, 0xF8, 0xF8, 0x03, 0x9F, 0x01, 0xF0, 0x60, 0x1F, 0x0F, 0x83, 0x00, 0x00, 0x00, 
	0x3F, 0x9F, 0xF7, 0xF9, 0xFC, 0x03, 0x9F, 0xC3, 0xF8, 0x70, 0x3F, 0x8F, 0xC3, 0x00, 0x00, 0x00, 
	0x3B, 0x83, 0x83, 0x80, 0x0E, 0x7F, 0xC1, 0xE7, 0x1C, 0x70, 0x71, 0xC0, 0xE1, 0x80, 0x00, 0x00, 
	0x71, 0xC3, 0x81, 0xC0, 0x0E, 0x7F, 0xC0, 0xE7, 0x1C, 0x30, 0x71, 0xC0, 0x71, 0x80, 0x00, 0x00, 
	0x79, 0xC3, 0x80, 0xE0, 0x0E, 0x63, 0x80, 0xE7, 0x1C, 0x38, 0x71, 0xC7, 0x70, 0xC0, 0x00, 0x00, 
	0x7D, 0xC3, 0x80, 0x70, 0x7E, 0x33, 0x81, 0xE7, 0x1C, 0x18, 0x3F, 0x8F, 0xF0, 0xC0, 0x00, 0x00, 
	0x77, 0xC3, 0x80, 0x70, 0x7C, 0x13, 0x9F, 0xC7, 0xF8, 0x1C, 0x1F, 0x1C, 0x70, 0x60, 0x00, 0x00, 
	0x73, 0xC3, 0x80, 0x38, 0x0E, 0x1B, 0x9F, 0x87, 0x70, 0x1C, 0x31, 0x9C, 0x70, 0x60, 0x00, 0x00, 
	0x71, 0xC3, 0x80, 0x38, 0x0E, 0x0B, 0x9C, 0x07, 0x00, 0x0C, 0x71, 0xDC, 0x70, 0x30, 0x00, 0x00, 
	0x3B, 0x9F, 0x80, 0x38, 0x0E, 0x0F, 0x9C, 0x03, 0x80, 0x0E, 0x71, 0xDC, 0x70, 0x30, 0x00, 0x00, 
	0x3F, 0x8F, 0x83, 0xF1, 0xFC, 0x07, 0x9F, 0xC1, 0xF9, 0xFE, 0x3F, 0x8F, 0xE0, 0x18, 0x00, 0x00, 
	0x0E, 0x03, 0x81, 0xE0, 0xF8, 0x03, 0x9F, 0xC0, 0xF9, 0xFE, 0x1F, 0x07, 0xC0, 0x18, 0x00, 0x00, 
};

static void ppuDrawRest(uint8_t curX, uint8_t sym)
{
	uint8_t i, j;
	for(i = 0; i < 12; i++)
	{
		for(j = 0; j < 10; j++)
		{
			#ifdef DO_4_3_ASPECT
			size_t drawPos = ((j+curX)<<2)+(((i+9)*TEX_DOTS)<<2);
			#else
			size_t drawPos = (j+curX)+((i+9)*TEX_DOTS);
			#endif
			uint8_t xSel = (j+(sym*10));
			if(ppuNsfTextRest[((11-i)<<4)+(xSel>>3)]&(0x80>>(xSel&7)))
				TEX_AT_POS = TEXCOL_WHITE; //White
			else
				TEX_AT_POS = TEXCOL_BLACK; //Black
		}
	}
}

#ifdef COL_32BIT
#define NSF_TEX_CLEAR TEX_LINES*TEX_DOTS*4
#else //COL_16BIT
#define NSF_TEX_CLEAR TEX_LINES*TEX_DOTS*2
#endif

void ppuDrawNSFTrackNum(uint8_t cTrack, uint8_t trackTotal)
{
	memset(textureImage,0,NSF_TEX_CLEAR);
	uint8_t curX = 4;
	//draw "Track"
	uint8_t i, j;
	for(i = 0; i < 12; i++)
	{
		for(j = 0; j < 50; j++)
		{
			#ifdef DO_4_3_ASPECT
			size_t drawPos = ((j+curX)<<2)+(((i+9)*TEX_DOTS)<<2);
			#else
			size_t drawPos = (j+curX)+((i+9)*TEX_DOTS);
			#endif
			if(ppuNSFTextTrack[((11-i)<<3)+(j>>3)]&(0x80>>(j&7)))
				TEX_AT_POS = TEXCOL_WHITE; //White
			else
				TEX_AT_POS = TEXCOL_BLACK; //Black
		}
	}
	//"Track" len+space
	curX+=60;
	//draw current num
	if(cTrack > 99)
	{
		ppuDrawRest(curX, (cTrack/100)%10);
		curX+=10;
	}
	if(cTrack > 9)
	{
		ppuDrawRest(curX, (cTrack/10)%10);
		curX+=10;
	}
	ppuDrawRest(curX, cTrack%10);
	curX+=10;
	//draw the "/"
	ppuDrawRest(curX, 10);
	curX+=10;
	//draw total num
	if(trackTotal > 99)
	{
		ppuDrawRest(curX, (trackTotal/100)%10);
		curX+=10;
	}
	if(trackTotal > 9)
	{
		ppuDrawRest(curX, (trackTotal/10)%10);
		curX+=10;
	}
	ppuDrawRest(curX, trackTotal%10);
	curX+=10;
}

void ppuSoftReset()
{
	//will be dealt with at the end of a frame
	ppu.reqReset = true;
}

void ppuReset()
{
	//reset those regs
	ppuSet8(0,0);
	ppuSet8(1,0);
	ppu.TmpWrite = false;
	ppu.FineXScroll = 0;
	ppu.VramReadBuf = 0;
	ppu.OddFrame = false;
	ppu.OddNum = 0;
}
