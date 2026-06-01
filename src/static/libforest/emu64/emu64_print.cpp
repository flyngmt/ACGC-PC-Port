// #include "emu64.hpp"

#include "boot.h"

// __declspec(weak) void emu64_print::Vprintf(const char* fmt, std::__tag_va_List va_list) const {
//     vprintf(fmt, va_list);
// }

__declspec(weak) void emu64_print::Printf0(const char* fmt, ...) {
#ifdef TARGET_PC
    extern int g_pc_verbose;
    if (!g_pc_verbose) return;
#endif
    va_list list;

    va_start(list, fmt);
    // this->Vprintf(fmt, list);
    vprintf(fmt, list);
    va_end(list);
}

__declspec(weak) void emu64_print::Printf(const char* fmt, ...) {
    va_list list;

#ifdef TARGET_PC
    extern int g_pc_verbose;
    if (!g_pc_verbose) return;
#endif
    if ((this->print_flags & EMU64_PRINTF_ENABLED_FLAG)) {
        va_start(list, fmt);
        // this->Vprintf(fmt, list);
        vprintf(fmt, list);
        va_end(list);
    }
}

static const char* __unused__reorder_char0A(void) {
    return "\n";
}

void emu64::disp_matrix(MtxP mtx) {
    static const u8 kakko[] = {'/', '\\', '/', '\\', '|', '|', '|', '|', '|', '|', '|', '|', '\\', '/', '\\', '/'};
    int i, j;
    for (i = 0; i < 4; i++) {
        if (mtx != nullptr) {
            for (j = 0; j < 4; j++) {
                this->Printf("%10.3f", mtx[i][j]);
            }
        }

        this->Printf("\n", kakko[i * 4 + 3]);
    }
}

#pragma inline_depth(5)
#pragma inline_max_size(1100)
const char* emu64::segchk(uintptr_t segment) {
    static char str[64];
    char buf[30];
    const char str0[] = "anime_4_txt+%4u";
    const char str1[] = "anime_6_model+sizeof(Mtx)*%2u";

    uintptr_t partial_addr = seg2k0(segment);
    uintptr_t addr = convert_partial_address((u32)partial_addr);

    str[0] = '\0';
    if (segment == partial_addr) {
        if (addr == partial_addr) {
            snprintf(str, sizeof(str), "0x%08x", (u32)segment);
        } else {
            snprintf(str, sizeof(str), "0x%08x /* PADDR=0x%08x */", (u32)segment, (u32)addr);
        }
    } else {
        const char* s;
        if (SEG_EQUALS(segment, SOFTSPRITE_MTX_SEG)) {
            s = "softsprite_mtx";
        } else if (SEG_EQUALS(segment, ANIME_1_TXT_SEG)) {
            s = "anime_1_txt";
        } else if (SEG_EQUALS(segment, ANIME_2_TXT_SEG)) {
            s = "anime_2_txt";
        } else if (SEG_EQUALS(segment, ANIME_3_TXT_SEG)) {
            s = "anime_3_txt";
        } else if (SEG_EQUALS(segment, ANIME_4_TXT_SEG)) {
            s = "anime_4_txt";
        } else if (SEG_EQUALS(segment, ANIME_5_TXT_SEG)) {
            s = "anime_5_txt";
        } else if (SEG_EQUALS(segment, ANIME_6_TXT_SEG)) {
            s = "anime_6_txt";
        } else if (SEG_EQUALS(segment, ANIME_1_TXT_SEG)) {
            s = "anime_1_model";
        } else if (SEG_EQUALS(segment, ANIME_2_TXT_SEG)) {
            s = "anime_2_model";
        } else if (SEG_EQUALS(segment, ANIME_3_TXT_SEG)) {
            s = "anime_3_model";
        } else if (SEG_EQUALS(segment, ANIME_4_TXT_SEG)) {
            s = "anime_4_model";
        } else if (SEG_EQUALS(segment, ANIME_5_TXT_SEG)) {
            s = "anime_5_model";
        } else if (SEG_EQUALS(segment, ANIME_6_TXT_SEG)) {
            s = "anime_6_model";
        } else if (segment > anime_4_txt && segment < (anime_4_txt + ANIME_4_TXT_SIZE)) {
            snprintf(buf, sizeof(buf) - 1, str0, segment - anime_4_txt);
            s = buf;
        } else {
            if (segment > anime_6_model && segment < (anime_6_model + ANIME_6_MODEL_SIZE)) {
                int comb = segment - anime_6_model;
                snprintf(buf, sizeof(buf) - 1, str1, comb / (int)sizeof(Mtx));
                s = buf;
            } else {
                s = nullptr;
            }
        }

        if (addr == partial_addr) {
            if (s != nullptr) {
                snprintf(str, sizeof(str), "%s /* 0x%08x */", s, partial_addr);
            } else {
                snprintf(str, sizeof(str), "0x%08x /* ### 0x%08x */", segment, partial_addr);
            }
        } else {
            if (s != nullptr) {
                snprintf(str, sizeof(str), "%s /* 0x%08x PADDR=0x%08x */", s, partial_addr, addr);
            } else {
                snprintf(str, sizeof(str), "0x%08x /* ### 0x%08x PADDR=0x%08x */", segment, partial_addr, addr);
            }
        }
    }

    return str;
}

const char* emu64::combine_name(u32 param, u32 type) {
    const char* ret;
    switch (param) {
        case 0:
            ret = "COMBINED";
            break;
        case 1:
            ret = "TEXEL0";
            break;
        case 2:
            ret = "TEXEL1";
            break;
        case 3:
            ret = "PRIMITIVE";
            break;
        case 4:
            ret = "SHADE";
            break;
        case 5:
            ret = "ENVIRONMENT";
            break;
        case 6:
            ret = (type == COMBINER_PARAM_B) ? "CENTER" : ((type == COMBINER_PARAM_C) ? "SCALE" : "1");
            break;
        case 7:
            ret = (type == COMBINER_PARAM_A)
                      ? "NOISE"
                      : ((type == COMBINER_PARAM_B) ? "K4" : ((type == COMBINER_PARAM_C) ? "COMBINED_ALPHA" : "0"));
            break;
        default:
            if (type == COMBINER_PARAM_C) {
                switch (param) {
                    case 8:
                        ret = "TEXEL0_ALPHA";
                        break;
                    case 9:
                        ret = "TEXEL1_ALPHA";
                        break;
                    case 10:
                        ret = "PRIMITIVE_ALPHA";
                        break;
                    case 11:
                        ret = "SHADE_ALPHA";
                        break;
                    case 12:
                        ret = "ENV_ALPHA";
                        break;
                    case 13:
                        ret = "LOD_FRACTION";
                        break;
                    case 14:
                        ret = "PRIM_LOD_FRAC";
                        break;
                    case 15:
                        ret = "K5";
                        break;
                    default:
                        ret = "0";
                        break;
                }
            } else {
                ret = "0";
            }
            break;
    }
    return ret;
}

const char* emu64::combine_alpha(int param, int type) {
    const char* ret;

    switch (param) {
        case 0:
            ret = (type == COMBINER_PARAM_C) ? "LOD_FRACTION" : "COMBINED";
            break;
        case 1:
            ret = "TEXEL0";
            break;
        case 2:
            ret = "TEXEL1";
            break;
        case 3:
            ret = "PRIMITIVE";
            break;
        case 4:
            ret = "SHADE";
            break;
        case 5:
            ret = "ENVIRONMENT";
            break;
        case 6:
            ret = (type == COMBINER_PARAM_C) ? "PRIM_LOD_FRAC" : "1";
            break;
        case 7:
            ret = "0";
            break;
            /* There should be a default case here, but they forgot it. */
            /* It returns a pointer to the emu64 class instead. */
#ifdef EMU64_FIX_COMBINE_NAME_RETURN_VALUES
        default:
            ret = "0";
            break;
#endif
    }

    return ret;
}

const char* emu64::combine_tev_color_name(u32 color_param) {
    const char* ret;

    switch (color_param) {
        case 0:
            ret = "COMBINED";
            break;
        case 1:
            ret = "COMBINED_ALPHA";
            break;
        case 2:
            ret = "(FILL)";
            break;
        case 3:
            ret = "PRIM_LOD_FRAC";
            break;
        case 4:
            ret = "PRIMITIVE";
            break;
        case 5:
            ret = "PRIMITIVE_ALPHA";
            break;
        case 6:
            ret = "ENVIRONMENT";
            break;
        case 7:
            ret = "ENV_ALPHA";
            break;
        case 8:
            ret = "TEXEL0";
            break;
        case 9:
            ret = "TEXEL0_ALPHA";
            break;
        case 10:
            ret = "SHADE";
            break;
        case 11:
            ret = "SHADE_ALPHA";
            break;
        case 12:
            ret = "1";
            break;
        case 13:
            ret = "(HALF)";
            break;
        case 14:
            ret = "(KONST)";
            break;
        case 15:
            ret = "0";
            break;
            /* There should be a default case here, but they forgot it. */
            /* It returns a pointer to the emu64 class instead. */
#ifdef EMU64_FIX_COMBINE_NAME_RETURN_VALUES
        default:
            ret = "0";
            break;
#endif
    }
    return ret;
}

const char* emu64::combine_tev_alpha_name(u32 alpha_param) {
    const char* ret;

    switch (alpha_param) {
        case 0:
            ret = "COMBINED";
            break;
        case 1:
            ret = "PRIM_LOD_FRAC";
            break;
        case 2:
            ret = "PRIMITIVE";
            break;
        case 3:
            ret = "ENVIRONMENT";
            break;
        case 4:
            ret = "TEXEL0";
            break;
        case 5:
            ret = "SHADE";
            break;
        case 6:
            ret = "1";
            break;
        case 7:
            ret = "0";
            break;
            /* There should be a default case here, but they forgot it. */
            /* It returns a pointer to the emu64 class instead. */
#ifdef EMU64_FIX_COMBINE_NAME_RETURN_VALUES
        default:
            ret = "0";
            break;
#endif
    }

    return ret;
}

void emu64::print_geomflags(u32 flags) {
    u32 i;
    int empty = TRUE;

    for (i = 0; i < NUM_GEOMETRYMODE_FLAGS; i++) {
        if ((flags & geomtbl[i].mask) == geomtbl[i].value) {
            if (empty) {
                empty = FALSE;
            } else {
                this->Printf("|");
            }

            this->Printf("%s", geomtbl[i].name);
        }
    }

    if (empty) {
        this->Printf("0");
    }
}

typedef struct {
    const char* name;
    u32 value;
    u32 mask;
} RendermodeInfo;

void emu64::show_render(u32 data) {
    static const RendermodeInfo flags[] = {
        { "AA_EN", AA_EN, AA_EN },
        { "Z_CMP", Z_CMP, Z_CMP },
        { "Z_UPD", Z_UPD, Z_UPD },
        { "IM_RD", IM_RD, IM_RD },
        { "CLR_ON_CVG", CLR_ON_CVG, CLR_ON_CVG },
        { "CVG_DST_CLAMP", CVG_DST_CLAMP, CVG_DST_SAVE },
        { "CVG_DST_WRAP", CVG_DST_WRAP, CVG_DST_SAVE },
        { "CVG_DST_FULL", CVG_DST_FULL, CVG_DST_SAVE },
        { "CVG_DST_SAVE", CVG_DST_SAVE, CVG_DST_SAVE },
        { "ZMODE_OPA", ZMODE_OPA, ZMODE_DEC },
        { "ZMODE_INTER", ZMODE_INTER, ZMODE_DEC },
        { "ZMODE_XLU", ZMODE_XLU, ZMODE_DEC },
        { "ZMODE_DEC", ZMODE_DEC, ZMODE_DEC },
        { "CVG_X_ALPHA", CVG_X_ALPHA, CVG_X_ALPHA },
        { "ALPHA_CVG_SEL", ALPHA_CVG_SEL, ALPHA_CVG_SEL },
        { "FORCE_BL", FORCE_BL, FORCE_BL },
    };

    static const char* const m[4][4] = {
        { "G_BL_CLR_IN", "G_BL_CLR_MEM", "G_BL_CLR_BL", "G_BL_CLR_FOG" },
        { "G_BL_A_IN", "G_BL_A_FOG", "G_BL_A_SHADE", "G_BL_0" },
        { "G_BL_CLR_IN", "G_BL_CLR_MEM", "G_BL_CLR_BL", "G_BL_CLR_FOG" },
        { "G_BL_1MA", "G_BL_A_MEM", "G_BL_1", "G_BL_0" },
    };

    EMU64_LOG("\ngsDPSetRenderBlender(\n");

    u32 c1 = (data >> 18) & 0x3333;
    u32 c2 = (data >> 16) & 0x3333;

    for (u32 i = 0; i < ARRAY_COUNT(flags); i++) {
        if ((data & flags[i].mask) == flags[i].value) {
            this->Printf("%s|", flags[i].name);
        }
    }

    this->Printf("\nGBL_c1(%s, %s, %s, %s)|", m[0][(c1 >> 12) & 3], m[1][(c1 >> 8) & 3], m[2][(c1 >> 4) & 3],
                 m[3][c1 & 3]);

    this->Printf("\nGBL_c2(%s, %s, %s, %s)", m[0][(c2 >> 12) & 3], m[1][(c2 >> 8) & 3], m[2][(c2 >> 4) & 3],
                 m[3][c2 & 3]);

    EMU64_LOG("\n),");
}

void emu64::show_vtx(Vtx* vtx, int count, int begin) {
    for (int i = 0; i < count; i++, vtx++) {
        if ((this->geometry_mode & G_LIGHTING) != 0) {
            Vtx_tn* p_vtx = &vtx->n;

            // clang-format off
            this->Printf(
                "\n{{%6d, %6d, %6d, %d, %6d, %6d, %4d, %4d, %4d, %3d}}, /* vc%02d */",
                p_vtx->ob[0], p_vtx->ob[1], p_vtx->ob[2], /* Position */
                p_vtx->flag, /* Flag */
                p_vtx->tc[0], p_vtx->tc[1], /* Texture Coordinates */
                p_vtx->n[0], p_vtx->n[1], p_vtx->n[2], /* Normal */
                p_vtx->a, /* Alpha */
                begin + i /* Vertex # */
            );
            // clang-format on
        } else {
            Vtx_t* p_vtx = &vtx->v;

            // clang-format off
            this->Printf(
                "\n{{%6d, %6d, %6d, %d, %6d, %6d, %4d, %4d, %4d, %3d}}, /* vn%02d */",
                p_vtx->ob[0], p_vtx->ob[1], p_vtx->ob[2], /* Position */
                p_vtx->flag, /* Flag */
                p_vtx->tc[0], p_vtx->tc[1], /* Texture Coordinates */
                p_vtx->cn[0], p_vtx->cn[1], p_vtx->cn[2], p_vtx->cn[3], /* Color */
                begin + i /* Vertex # */
            );
            // clang-format on
        }
    }
}

void emu64::print_combine(u64 cmd) {
    Gsetcombine_new* combine = (Gsetcombine_new*)&cmd;
    this->Printf0(
        "gsDPSetCombineLERP(%s,%s,%s,%s, %s,%s,%s,%s, %s,%s,%s,%s, %s,%s,%s,%s),",
        this->combine_name(combine->a0, COMBINER_PARAM_A), this->combine_name(combine->b0, COMBINER_PARAM_B),
        this->combine_name(combine->c0, COMBINER_PARAM_C), this->combine_name(combine->d0, COMBINER_PARAM_D),
        this->combine_alpha(combine->Aa0, COMBINER_PARAM_A), this->combine_alpha(combine->Ab0, COMBINER_PARAM_B),
        this->combine_alpha(combine->Ac0, COMBINER_PARAM_C), this->combine_alpha(combine->Ad0, COMBINER_PARAM_D),
        this->combine_name(combine->a1, COMBINER_PARAM_A), this->combine_name(combine->b1, COMBINER_PARAM_B),
        this->combine_name(combine->c1, COMBINER_PARAM_C), this->combine_name(combine->d1, COMBINER_PARAM_D),
        this->combine_alpha(combine->Aa1, COMBINER_PARAM_A), this->combine_alpha(combine->Ab1, COMBINER_PARAM_B),
        this->combine_alpha(combine->Ac1, COMBINER_PARAM_C), this->combine_alpha(combine->Ad1, COMBINER_PARAM_D));
}

void emu64::print_combine_tev(u64 combine_tev) {
    Gsetcombine_tev* c_tev = (Gsetcombine_tev*)&combine_tev;

    this->Printf0("gsDPSetCombineTev(%s,%s,%s,%s, %s,%s,%s,%s, %s,%s,%s,%s, %s,%s,%s,%s),",
                  this->combine_tev_color_name(c_tev->a0), this->combine_tev_color_name(c_tev->b0),
                  this->combine_tev_color_name(c_tev->c0), this->combine_tev_color_name(c_tev->d0),
                  this->combine_tev_alpha_name(c_tev->Aa0), this->combine_tev_alpha_name(c_tev->Ab0),
                  this->combine_tev_alpha_name(c_tev->Ac0), this->combine_tev_alpha_name(c_tev->Ad0),
                  this->combine_tev_color_name(c_tev->a1), this->combine_tev_color_name(c_tev->b1),
                  this->combine_tev_color_name(c_tev->c1), this->combine_tev_color_name(c_tev->d1),
                  this->combine_tev_alpha_name(c_tev->Aa1), this->combine_tev_alpha_name(c_tev->Ab1),
                  this->combine_tev_alpha_name(c_tev->Ac1), this->combine_tev_alpha_name(c_tev->Ad1));
}

void emu64::print_guMtxXFM1F_dol2(MtxP mtx, GXProjectionType type, float x, float y, float z) {
    if (type == GX_PERSPECTIVE) {
        float s = -1.0f / z;

        float x0 = mtx[0][0] * x * s - mtx[0][2];
        float y0 = mtx[1][1] * y * s - mtx[1][2];
        float z0 = mtx[2][3] * s - mtx[2][2];

        EMU64_LOGF("%8.3f * %8.3f * %8.3f - %8.3f = %8.3f\n", mtx[0][0], x, s, mtx[0][2], x0);
        EMU64_LOGF("%8.3f * %8.3f * %8.3f - %8.3f = %8.3f\n", mtx[1][1], y, s, mtx[1][2], y0);
        EMU64_LOGF("%8.3f            * %8.3f - %8.3f = %8.3f\n", mtx[2][3], s, mtx[2][2], z0);
    } else {
        float x0 = mtx[0][0] * x + mtx[0][3];
        float y0 = mtx[1][1] * y + mtx[1][3];
        float z0 = mtx[2][2] * z + mtx[2][3];

        EMU64_LOGF("%8.3f * %8.3f + %8.3f = %8.3f\n", mtx[0][0], x, mtx[0][3], x0);
        EMU64_LOGF("%8.3f * %8.3f + %8.3f = %8.3f\n", mtx[1][1], x, mtx[1][3], y0);
        EMU64_LOGF("%8.3f * %8.3f + %8.3f = %8.3f\n", mtx[2][2], x, mtx[2][3], z0);
    }
}
