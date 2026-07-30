#ifndef OSFONT_H
#define OSFONT_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_FONT_ROM_SIZE_ANSI 0x03000
#define OS_FONT_ROM_SIZE_SJIS 0x4D000

typedef struct OSFontHeader {
  u16 fontType;      // _00
  u16 firstChar;     // _02, first char code defined in font.
  u16 lastChar;      // _04, last char code defined in font.
  u16 invalChar;     // _06, code to sub for invalid chars.
  u16 ascent;        // _08
  u16 descent;       // _0A
  u16 width;         // _0C, max width.
  u16 leading;       // _0E
  u16 cellWidth;     // _10
  u16 cellHeight;    // _12
  u32 sheetSize;     // _14
  u16 sheetFormat;   // _18, see GX_TF_* part of GXTexFmt enum
  u16 sheetColumn;   // _1A
  u16 sheetRow;      // _1C
  u16 sheetWidth;    // _1E
  u16 sheetHeight;   // _20
  u16 widthTable;    // _22
  u32 sheetImage;    // _24
  u32 sheetFullSize; // _28
  u8 c0;             // _2C, font color components?
  u8 c1;             // _2D
  u8 c2;             // _2E
  u8 c3;             // _2F
} OSFontHeader;

#define OS_FONT_ENCODE_NULL -1
#define OS_FONT_ENCODE_ANSI 0u
#define OS_FONT_ENCODE_SJIS 1u
#define OS_FONT_ENCODE_UTF8 3u  // UTF-8 [RFC 3629]
#define OS_FONT_ENCODE_UTF16 4u // UTF-16BE [RFC 2781]
#define OS_FONT_ENCODE_UTF32 5u // UTF-32
#define OS_FONT_ENCODE_MAX 5u
#define OS_FONT_ENCODE_VOID 0xffffu

#define OS_FONT_PROPORTIONAL FALSE
#define OS_FONT_FIXED TRUE

u16 OSGetFontEncode(void);
u16 OSSetFontEncode(u16 encode);

#ifdef __cplusplus
}
#endif

#endif
