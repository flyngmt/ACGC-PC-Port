#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eCoin_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eCoin_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eCoin_mv(eEC_Effect_c* effect, GAME* game);
static void eCoin_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_coin = {
    // clang-format off
    &eCoin_init,
    &eCoin_ct,
    &eCoin_mv,
    &eCoin_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eCoin_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_COIN, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static f32 eCoin_GetFountainHeight(void) {
    int bx;
    int bz;

    if (mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_SHRINE)) {
        return 40.0f + mFI_BkNum2BaseHeight(bx, bz);
    } else {
        return 150.0f;
    }
}

static void eCoin_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 rng = RANDOM(10) & 1;
    f32 dir;
    s16 angle;

    if (rng == 1) {
        dir = RANDOM_F(768.0f);
    } else {
        dir = -fqrand() * 1024.0f;
    }

    angle = (int)dir + DEG2SHORT_ANGLE(192.65625f);

    effect->position.x += 9.0f;
    effect->position.y += 11.0f;
    effect->position.z -= 15.0f;

    effect->timer = 100;

    effect->effect_specific[0] = FALSE;
    effect->effect_specific[1] = F32_TO_S16(RANDOM_F(65535));
    effect->effect_specific[2] = F32_TO_S16(RANDOM_F(65535));
    effect->effect_specific[3] = F32_TO_S16(RANDOM_F(65535));
    effect->effect_specific[4] = 0;

    effect->velocity.x = sin_s(angle) * 0.77f;
    effect->velocity.y = 5.5f;
    effect->velocity.z = cos_s(angle) * 0.77f;

    effect->acceleration.x = 0.0f;
    effect->acceleration.y = -0.2f;
    effect->acceleration.z = 0.0f;

    effect->offset.x = 14.0f + eCoin_GetFountainHeight() - 3.0f;
    effect->offset.y = effect->offset.x - 4.5f;

    sAdo_OngenTrgStart(0x466, &effect->position);

    effect->effect_specific[5] = RANDOM(100) & 1; // 0 = gold coin, 1 = silver coin
}

static void eCoin_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;

    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;

    if (effect->effect_specific[0] == FALSE) {

        eEC_CLIP->set_continious_env_proc(effect, 100, 100);
        effect->effect_specific[1] += F32_TO_S16(DEG2SHORT_ANGLE(21.093750f) * dt);
        effect->effect_specific[2] += F32_TO_S16(DEG2SHORT_ANGLE(18.281250f) * dt);
        effect->effect_specific[3] += F32_TO_S16(DEG2SHORT_ANGLE(19.687500f) * dt);

        if (effect->position.y <= effect->offset.x) {
            xyz_t pos = effect->position;

            pos.y = effect->offset.x;
            effect->position.y = effect->offset.x;

            sAdo_OngenTrgStart(0x467, &effect->position);
            effect->effect_specific[0] = TRUE;
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_MIZU, pos, effect->prio, 0, game, (u16)effect->item_name, 0, 0);

            effect->effect_specific[1] = 0;
            effect->effect_specific[2] = 0;
            effect->effect_specific[3] = 0;

            effect->acceleration.x = 0.0f;
            effect->acceleration.y = 0.0f;
            effect->acceleration.z = 0.0f;

            effect->velocity.x = 0.0f;
            effect->velocity.y = -0.14f;
            effect->velocity.z = 0.0f;

            effect->timer = 300;
            effect->lifetime = 300.0f;
        }
    } else if (effect->position.y <= effect->offset.y) {
        effect->position.y = effect->offset.y;

        effect->velocity.x = 0.0f;
        effect->velocity.y = 0.0f;
        effect->velocity.z = 0.0f;

        effect->effect_specific[1] = 0;
        effect->effect_specific[2] = 0;
        effect->effect_specific[3] = 0;

    } else {
        effect->effect_specific[4] += F32_TO_S16(DEG2SHORT_ANGLE(7.031250f) * dt);
        effect->effect_specific[1] = sin_s(effect->effect_specific[4]) * 2048.0f;
        effect->effect_specific[3] = cos_s(effect->effect_specific[4]) * 2048.0f;
        effect->effect_specific[2] = 0;
    }
}

#ifdef TARGET_PC
static u16 ef_coin_gold_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
static u16 ef_coin_gold_pal[16] ATTRIBUTE_ALIGN(32) = {
#include "assets/ef_coin_gold_pal.inc"
};
#endif

#ifdef TARGET_PC
static u16 ef_coin_silver_pal[0x20 / sizeof(u16)] ATTRIBUTE_ALIGN(32);
#else
static u16 ef_coin_silver_pal[16] ATTRIBUTE_ALIGN(32) = {
#include "assets/ef_coin_silver_pal.inc"
};
#endif

static u16* eCoin_pal_table[2] = { ef_coin_gold_pal, ef_coin_silver_pal };

extern Gfx ef_coin_model[];
extern Gfx ef_coin_modelT[];

static void eCoin_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (effect->effect_specific[0] == FALSE) {
        _texture_z_light_fog_prim(game->graph);
        Setpos_HiliteReflect_init(&effect->position, play);

        OPEN_DISP(game->graph);

        Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
        Matrix_RotateX(effect->effect_specific[1], MTX_MULT);
        Matrix_RotateY(effect->effect_specific[2], MTX_MULT);
        Matrix_RotateZ(effect->effect_specific[3], MTX_MULT);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, eCoin_pal_table[effect->effect_specific[5] & 1]);
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, ef_coin_model);

        CLOSE_DISP(game->graph);
    } else {
        f32 t = 300.0f - effect->lifetime;
        u8 alpha = (int)eEL_CalcAdjust_F(t, 0.0f, 300.0f, 180.0f, 0.0f);

        _texture_z_light_fog_prim_xlu(game->graph);
        Setpos_HiliteReflect_xlu_init(&effect->position, play);

        OPEN_DISP(game->graph);

        Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
        Matrix_RotateX(effect->effect_specific[1], MTX_MULT);
        Matrix_RotateY(effect->effect_specific[2], MTX_MULT);
        Matrix_RotateZ(effect->effect_specific[3], MTX_MULT);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, 255, 255, alpha);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, eCoin_pal_table[effect->effect_specific[5] & 1]);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_coin_modelT);

        CLOSE_DISP(game->graph);
    }
}

#ifdef TARGET_PC
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_src_effect_ef_coin_c(void) {
    pc_load_asset("assets/ef_coin_gold_pal.bin", ef_coin_gold_pal, 0x20, 0x361F20, 0, 1);
    pc_load_asset("assets/ef_coin_silver_pal.bin", ef_coin_silver_pal, 0x20, 0x361F40, 0, 1);
}
#endif
