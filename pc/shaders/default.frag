#version 330 core
in vec4 v_color;
in vec2 v_texcoord0;
in vec2 v_texcoord1;
in vec3 v_normal;
in float v_fog_z;

uniform int u_fog_type;
uniform float u_fog_start;
uniform float u_fog_end;
uniform vec4 u_fog_color;

/* TEV registers: PREV, REG0, REG1(=PRIM), REG2(=ENV) */
uniform vec4 u_tev_prev;
uniform vec4 u_tev_reg0;
uniform vec4 u_tev_reg1;
uniform vec4 u_tev_reg2;

/* Per-stage TEV config. All stages are identical in shape, so one loop
   over these arrays handles them; keep PC_GX_MAX_TEV_STAGES (=3) in sync. */
uniform int u_num_tev_stages;
uniform ivec4 u_tev_color_in[3];  /* x=a, y=b, z=c, w=d (GXTevColorArg) */
uniform ivec4 u_tev_alpha_in[3];
uniform int   u_tev_color_op[3];  /* 0=add, 1=sub */
uniform int   u_tev_alpha_op[3];
uniform int   u_tev_tc_src[3];    /* texcoord index (0 or 1) */
uniform ivec4 u_tev_bsc[3];       /* x=c_bias, y=c_scale, z=a_bias, w=a_scale */
uniform ivec4 u_tev_out[3];       /* x=c_clamp, y=a_clamp, z=c_out_reg, w=a_out_reg */
uniform ivec2 u_tev_swap[3];      /* x=ras swap idx, y=tex swap idx */
uniform ivec4 u_tev_ind_cfg[3];   /* x=ind_stage, y=ind_mtx, z=ind_bias, w=ind_alpha */
uniform ivec3 u_tev_ind_wrap[3];  /* x=wrap_s, y=wrap_t, z=add_prev */

/* Textures: stage N samples u_textureN. Kept as separate uniforms so the
   C-side binding code doesn't have to deal with sampler arrays; the main
   loop reads pre-sampled results from a local vec4[3]. */
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform int u_use_texture0;
uniform int u_use_texture1;
uniform int u_use_texture2;

/* Lighting / color channels */
uniform int u_lighting_enabled;
uniform vec4 u_mat_color;
uniform vec4 u_amb_color;
uniform int u_chan_mat_src;   /* 0=REG, 1=VTX */
uniform int u_chan_amb_src;
uniform int u_num_chans;
uniform int u_alpha_lighting_enabled;
uniform int u_alpha_mat_src;
uniform int u_light_mask;
uniform vec3 u_light_pos[8];
uniform vec4 u_light_color[8];

/* KONST colors and per-stage selection */
uniform vec4 u_kcolor[4];
uniform ivec3 u_tev_ksel[3];   /* x=kcolor_sel, y=kalpha_sel */

/* Swap tables (channel remapping) */
uniform ivec4 u_swap_table[4];

/* Alpha compare */
uniform int u_alpha_comp0;
uniform int u_alpha_ref0;
uniform int u_alpha_op;
uniform int u_alpha_comp1;
uniform int u_alpha_ref1;

/* Indirect textures */
uniform int u_num_ind_stages;
uniform sampler2D u_ind_tex0;
uniform sampler2D u_ind_tex1;
uniform vec2 u_ind_scale[4];
uniform vec3 u_ind_mtx_r0[3];
uniform vec3 u_ind_mtx_r1[3];

out vec4 fragColor;

/* GXTevKColorSel: 0-7 = constant fractions 8/8..1/8, 8-11 = reserved (zero),
   12-15 = K0..K3 RGB, 16+ = K0..K3 single channel (R,G,B,A). The split range
   structure doesn't benefit from a switch, so the discrete and ranged cases
   stay as ifs. */
vec3 getKonstC(int sel) {
    if (sel <= 7)  return vec3(float(8 - sel) / 8.0);
    if (sel <= 11) return vec3(0.0);
    if (sel <= 15) return u_kcolor[sel - 12].rgb;
    int ki = (sel - 16) & 3;
    int ch = (sel - 16) >> 2;
    switch (ch) {
        case 0:  return vec3(u_kcolor[ki].r);
        case 1:  return vec3(u_kcolor[ki].g);
        case 2:  return vec3(u_kcolor[ki].b);
        default: return vec3(u_kcolor[ki].a);
    }
}

float getKonstA(int sel) {
    if (sel <= 7)  return float(8 - sel) / 8.0;
    if (sel <= 15) return 0.0;
    int ki = (sel - 16) & 3;
    int ch = (sel - 16) >> 2;
    switch (ch) {
        case 0:  return u_kcolor[ki].r;
        case 1:  return u_kcolor[ki].g;
        case 2:  return u_kcolor[ki].b;
        default: return u_kcolor[ki].a;
    }
}

/* GXTevColorArg enum (0-15) */
vec3 getTevC(int id, vec4 prev, vec4 tex, vec4 ras,
             vec4 r0, vec4 r1, vec4 r2, vec3 konst) {
    switch (id) {
        case 0:  return prev.rgb;      /* CPREV */
        case 1:  return vec3(prev.a);  /* APREV */
        case 2:  return r0.rgb;        /* C0 */
        case 3:  return vec3(r0.a);    /* A0 */
        case 4:  return r1.rgb;        /* C1 */
        case 5:  return vec3(r1.a);    /* A1 */
        case 6:  return r2.rgb;        /* C2 */
        case 7:  return vec3(r2.a);    /* A2 */
        case 8:  return tex.rgb;       /* TEXC */
        case 9:  return vec3(tex.a);   /* TEXA */
        case 10: return ras.rgb;       /* RASC */
        case 11: return vec3(ras.a);   /* RASA */
        case 12: return vec3(1.0);     /* ONE */
        case 13: return vec3(0.5);     /* HALF */
        case 14: return konst;         /* KONST */
        default: return vec3(0.0);     /* ZERO */
    }
}

/* GXTevAlphaArg enum (0-7) */
float getTevA(int id, float prev, float tex, float ras,
              float r0, float r1, float r2, float konst) {
    switch (id) {
        case 0:  return prev;   /* APREV */
        case 1:  return r0;     /* A0 */
        case 2:  return r1;     /* A1 */
        case 3:  return r2;     /* A2 */
        case 4:  return tex;    /* TEXA */
        case 5:  return ras;    /* RASA */
        case 6:  return konst;  /* KONST */
        default: return 0.0;    /* ZERO */
    }
}

vec4 applySwap(vec4 v, ivec4 sw) {
    return vec4(v[sw.x], v[sw.y], v[sw.z], v[sw.w]);
}

/* TEV formula: d OP ((1-c)*a + c*b) */
vec4 tevStage(ivec4 cin, int cop, ivec4 ain, int aop,
              vec4 prev, vec4 tex, vec4 ras,
              vec4 r0, vec4 r1, vec4 r2,
              vec3 konstC, float konstA) {
    vec3 ca = getTevC(cin.x, prev, tex, ras, r0, r1, r2, konstC);
    vec3 cb = getTevC(cin.y, prev, tex, ras, r0, r1, r2, konstC);
    vec3 cc = getTevC(cin.z, prev, tex, ras, r0, r1, r2, konstC);
    vec3 cd = getTevC(cin.w, prev, tex, ras, r0, r1, r2, konstC);
    vec3 blend = mix(ca, cb, cc);
    vec3 cResult = (cop == 1) ? (cd - blend) : (cd + blend);

    float aa = getTevA(ain.x, prev.a, tex.a, ras.a, r0.a, r1.a, r2.a, konstA);
    float ab = getTevA(ain.y, prev.a, tex.a, ras.a, r0.a, r1.a, r2.a, konstA);
    float ac = getTevA(ain.z, prev.a, tex.a, ras.a, r0.a, r1.a, r2.a, konstA);
    float ad = getTevA(ain.w, prev.a, tex.a, ras.a, r0.a, r1.a, r2.a, konstA);
    float aBlend = mix(aa, ab, ac);
    float aResult = (aop == 1) ? (ad - aBlend) : (ad + aBlend);

    return vec4(cResult, aResult);
}

/* bias: 0=none, 1=+0.5, 2=-0.5; scale: 0=x1, 1=x2, 2=x4, 3=x0.5 */
vec4 applyBSC(vec4 v, ivec4 bsc) {
    switch (bsc.x) {
        case 1: v.rgb += 0.5; break;
        case 2: v.rgb -= 0.5; break;
    }
    switch (bsc.y) {
        case 1: v.rgb *= 2.0; break;
        case 2: v.rgb *= 4.0; break;
        case 3: v.rgb *= 0.5; break;
    }
    switch (bsc.z) {
        case 1: v.a += 0.5; break;
        case 2: v.a -= 0.5; break;
    }
    switch (bsc.w) {
        case 1: v.a *= 2.0; break;
        case 2: v.a *= 4.0; break;
        case 3: v.a *= 0.5; break;
    }
    return v;
}

/* out_cfg.zw selects target register: 0=PREV, 1=REG0, 2=REG1, 3=REG2 */
void writeToReg(vec4 val, ivec4 out_cfg,
                inout vec4 prev, inout vec4 r0, inout vec4 r1, inout vec4 r2) {
    vec3 rgb = (out_cfg.x != 0) ? clamp(val.rgb, 0.0, 1.0) : val.rgb;
    float a  = (out_cfg.y != 0) ? clamp(val.a,   0.0, 1.0) : val.a;
    switch (out_cfg.z) {
        case 0:  prev.rgb = rgb; break;
        case 1:  r0.rgb   = rgb; break;
        case 2:  r1.rgb   = rgb; break;
        default: r2.rgb   = rgb; break;
    }
    switch (out_cfg.w) {
        case 0:  prev.a = a; break;
        case 1:  r0.a   = a; break;
        case 2:  r1.a   = a; break;
        default: r2.a   = a; break;
    }
}

vec3 sampleIndTex(int ind_stage, vec2 tc0, vec2 tc1) {
    vec2 tc = (ind_stage == 0) ? tc0 : tc1;
    vec4 s = (ind_stage == 0) ? texture(u_ind_tex0, tc) : texture(u_ind_tex1, tc);
    return s.rgb;
}

vec2 applyIndirect(ivec4 ind_cfg, ivec3 ind_wrap, vec2 coord,
                   vec2 prev_offset, vec2 tc0, vec2 tc1) {
    int ind_mtx_id = ind_cfg.y;
    if (ind_mtx_id == 0) return coord;  /* GX_ITM_OFF */

    vec3 indSample = sampleIndTex(ind_cfg.x, tc0, tc1);

    /* Bias: shift [0,1] to [-0.5,0.5] per axis (GX_ITB bitmask: S=1, T=2, U=4) */
    int bias = ind_cfg.z;
    vec3 biased = indSample;
    if ((bias & 1) != 0) biased.x -= 0.5;
    if ((bias & 2) != 0) biased.y -= 0.5;
    if ((bias & 4) != 0) biased.z -= 0.5;

    /* GX_ITM 1-3=full 2D, 5-7=S-only, 9-11=T-only. Ranged ids rather than
       discrete cases, so keep as ifs. */
    vec2 offset = vec2(0.0);
    int idx;
    if (ind_mtx_id >= 1 && ind_mtx_id <= 3) {
        idx = ind_mtx_id - 1;
        offset.x = dot(u_ind_mtx_r0[idx], biased);
        offset.y = dot(u_ind_mtx_r1[idx], biased);
    } else if (ind_mtx_id >= 5 && ind_mtx_id <= 7) {
        idx = ind_mtx_id - 5;
        offset.x = dot(u_ind_mtx_r0[idx], biased);
        offset.y = 0.0;
    } else if (ind_mtx_id >= 9 && ind_mtx_id <= 11) {
        idx = ind_mtx_id - 9;
        offset.x = 0.0;
        offset.y = dot(u_ind_mtx_r1[idx], biased);
    }

    if (ind_wrap.z != 0) offset += prev_offset;

    /* Wrap base texcoord: 0=off, 1-5=256..16 texels, 6=zero.
       Uses floor-based wrap instead of mod() to handle negative inputs. */
    vec2 wrappedCoord = coord;
    if (ind_wrap.x == 6) wrappedCoord.x = 0.0;
    else if (ind_wrap.x >= 1 && ind_wrap.x <= 5) {
        float wrapSize = float(1 << (9 - ind_wrap.x));  /* 256,128,64,32,16 */
        float w = coord.x * 256.0;
        wrappedCoord.x = (w - wrapSize * floor(w / wrapSize)) / 256.0;
    }
    if (ind_wrap.y == 6) wrappedCoord.y = 0.0;
    else if (ind_wrap.y >= 1 && ind_wrap.y <= 5) {
        float wrapSize = float(1 << (9 - ind_wrap.y));
        float w = coord.y * 256.0;
        wrappedCoord.y = (w - wrapSize * floor(w / wrapSize)) / 256.0;
    }

    return wrappedCoord + offset;
}

/* EQUAL/NEQUAL use epsilon for float precision after interpolation */
bool alphaTest(int comp, float val, float ref) {
    const float EPS = 0.5 / 255.0;
    switch (comp) {
        case 0:  return false;                  /* NEVER */
        case 1:  return val < ref;              /* LESS */
        case 2:  return abs(val - ref) < EPS;   /* EQUAL */
        case 3:  return val <= ref;             /* LEQUAL */
        case 4:  return val > ref;              /* GREATER */
        case 5:  return abs(val - ref) >= EPS;  /* NEQUAL */
        case 6:  return val >= ref;             /* GEQUAL */
        default: return true;                   /* ALWAYS */
    }
}

void main() {
    vec2 tc[2];
    tc[0] = v_texcoord0;
    tc[1] = v_texcoord1;

    /* Pre-pass: compute per-stage texcoord (with indirect offset). The
       indirect chain has a serial dependency via ind_prev_offset, so this
       runs as its own loop before the main TEV loop. */
    vec2 stc[3];
    {
        vec2 ind_prev_offset = vec2(0.0);
        for (int s = 0; s < u_num_tev_stages; s++) {
            vec2 base = tc[u_tev_tc_src[s]];
            stc[s] = base;
            if (u_num_ind_stages > 0 && u_tev_ind_cfg[s].y != 0) {
                stc[s] = applyIndirect(u_tev_ind_cfg[s], u_tev_ind_wrap[s],
                                       stc[s], ind_prev_offset, tc[0], tc[1]);
                ind_prev_offset = stc[s] - base;
            }
        }
    }

    /* Texture samples. Kept as an explicit 3-way dispatch rather than a
       sampler array so the C side doesn't need to change. */
    vec4 texColor[3];
    texColor[0] = (u_use_texture0 != 0) ? texture(u_texture0, stc[0]) : vec4(1.0);
    texColor[1] = (u_use_texture1 != 0) ? texture(u_texture1, stc[1]) : vec4(1.0);
    texColor[2] = (u_use_texture2 != 0) ? texture(u_texture2, stc[2]) : vec4(1.0);

    /* Rasterized color: GX lighting model */
    vec4 rasColor;
    if (u_num_chans == 0) {
        rasColor = vec4(1.0);
    } else {
        vec3 matC = (u_chan_mat_src != 0) ? v_color.rgb : u_mat_color.rgb;
        vec3 ambC = (u_chan_amb_src != 0) ? v_color.rgb : u_amb_color.rgb;
        if (u_lighting_enabled != 0) {
            vec3 lightAccum = ambC;
            for (int i = 0; i < 8; i++) {
                if ((u_light_mask & (1 << i)) != 0) {
                    vec3 L = normalize(u_light_pos[i]);
                    float diff = clamp(dot(v_normal, L), 0.0, 1.0);
                    lightAccum += diff * u_light_color[i].rgb;
                }
            }
            rasColor.rgb = matC * clamp(lightAccum, 0.0, 1.0);
        } else {
            rasColor.rgb = matC;
        }
        float matA = (u_alpha_mat_src != 0) ? v_color.a : u_mat_color.a;
        rasColor.a = (u_alpha_lighting_enabled != 0) ? matA * u_amb_color.a : matA;
    }

    vec4 prev = u_tev_prev;
    vec4 r0 = u_tev_reg0;
    vec4 r1 = u_tev_reg1;
    vec4 r2 = u_tev_reg2;

    /* Main TEV loop (Stage 0, 1, 2) */
    for (int s = 0; s < u_num_tev_stages; s++) {
        ivec2 swap = u_tev_swap[s];
        vec4 sTex = applySwap(texColor[s], u_swap_table[swap.y]);
        vec4 sRas = applySwap(rasColor,    u_swap_table[swap.x]);
        vec3 kc = getKonstC(u_tev_ksel[s].x);
        float ka = getKonstA(u_tev_ksel[s].y);
        vec4 result = tevStage(u_tev_color_in[s], u_tev_color_op[s],
                               u_tev_alpha_in[s], u_tev_alpha_op[s],
                               prev, sTex, sRas, r0, r1, r2, kc, ka);
        result = applyBSC(result, u_tev_bsc[s]);
        writeToReg(result, u_tev_out[s], prev, r0, r1, r2);
    }

    /* Alpha compare */
    if (u_alpha_comp0 != 7 || u_alpha_comp1 != 7) {
        float ref0 = float(u_alpha_ref0) / 255.0;
        float ref1 = float(u_alpha_ref1) / 255.0;
        bool pass0 = alphaTest(u_alpha_comp0, prev.a, ref0);
        bool pass1 = alphaTest(u_alpha_comp1, prev.a, ref1);
        bool pass;
        switch (u_alpha_op) {
            case 0:  pass = pass0 && pass1; break;
            case 1:  pass = pass0 || pass1; break;
            case 2:  pass = pass0 != pass1; break;
            default: pass = pass0 == pass1; break;
        }
        if (!pass) discard;
    }

    fragColor = prev;

    /* Fog */
    if (u_fog_type != 0) {
        float fog_denom = max(u_fog_end - u_fog_start, 1e-6);
        float fog_factor = clamp((v_fog_z - u_fog_start) / fog_denom, 0.0, 1.0);
        fragColor.rgb = mix(fragColor.rgb, u_fog_color.rgb, fog_factor);
    }
}
