#ifndef _DOLPHIN_GXCOMMANDLIST
#define _DOLPHIN_GXCOMMANDLIST

#ifdef __cplusplus
extern "C" {
#endif

#define GX_NOP 0x00
#define GX_DRAW_QUADS 0x80
#define GX_DRAW_TRIANGLES 0x90
#define GX_DRAW_TRIANGLE_STRIP 0x98
#define GX_DRAW_TRIANGLE_FAN 0xA0
#define GX_DRAW_LINES 0xA8
#define GX_DRAW_LINE_STRIP 0xB0
#define GX_DRAW_POINTS 0xB8

#define GX_LOAD_BP_REG 0x61
#define GX_LOAD_CP_REG 0x08
#define GX_LOAD_XF_REG 0x10
#define GX_LOAD_INDX_A 0x20
#define GX_LOAD_INDX_B 0x28
#define GX_LOAD_INDX_C 0x30
#define GX_LOAD_INDX_D 0x38

#define GX_CMD_CALL_DL 0x40
#define GX_CMD_INVL_VC 0x48

#define GX_OPCODE_MASK 0xF8
#define GX_VAT_MASK 0x07

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXCOMMANDLIST
