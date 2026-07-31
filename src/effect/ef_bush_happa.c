#include "ef_effect_control.h"
#include "sys_math.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eBushHappa_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eBushHappa_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eBushHappa_mv(eEC_Effect_c* effect, GAME* game);
static void eBushHappa_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_bush_happa = {
    // clang-format off
    &eBushHappa_init,
    &eBushHappa_ct,
    &eBushHappa_mv,
    &eBushHappa_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

extern Gfx ef_f_tree01_00_modelT[];
extern Gfx ef_s_cedar_modelT[];
extern Gfx ef_s_palm_modelT[];
extern Gfx ef_s_tree01_00_modelT[];
extern Gfx ef_s_yabu01_00_modelT[];

static void eBushHappa_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    s16 x = ABS(arg0);

    s_xz arg;

    arg.z = angle;
    arg.x = x;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_BUSH_HAPPA, pos, NULL, game, &arg, item_name, prio, arg0, arg1);
}
static void eBushHappa_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    f32 VSpeed = 2.5f + RANDOM_F(1.3f);
    xyz_t* velocity = &effect->velocity;
    f32 HzSpeed = -4.0f + RANDOM_F(8.0f);

    effect->position.x += HzSpeed;
    effect->position.z += HzSpeed;

    effect->offset.x = 0.0f;
    effect->offset.y = 0.0f;
    effect->offset.z = 0.0f;

    if (effect->arg1 & 0x8000) {
        effect->timer = 20;
        effect->arg1 &= ~0x8000;
    } else {
        effect->timer = 60;
    }

    effect->effect_specific[4] = (effect->arg1 >> 13) & 3;
    effect->arg1 &= ~0x6000;

    if (effect->arg1 & 0x1000) {
        effect->arg1 &= ~0x1000;
        effect->effect_specific[5] = 1;
    } else {
        effect->effect_specific[5] = 0;
    }

    if (effect->arg1 == 1) {
        effect->timer += 20;
        VSpeed *= 1.5f;

    } else if (effect->arg1 == 2 || effect->arg1 == 6) {
        effect->timer += 20;
        VSpeed *= 1.8f;
    } else if (effect->arg1 == 3) {
        effect->timer += 20;
        VSpeed *= 1.6f;
    } else if (effect->arg1 == 4 || effect->arg1 == 5) {
        effect->timer += 20;
    }

    if (effect->arg1 == 2 || effect->arg1 == 3) {
        eEC_CLIP->random_first_speed_proc(velocity, VSpeed, 32.0f, 32.0f);
    } else if (effect->arg1 == 4 || effect->arg1 == 6) {
        velocity->x = RANDOM2_F(2.0f);
        velocity->y = fqrand2();
        velocity->z = fqrand();
    } else if (effect->arg1 == 5 || effect->arg1 == 7) {
        eEC_CLIP->random_first_speed_proc(velocity, VSpeed, 32.0f, 32.0f);
    } else {
        eEC_CLIP->random_first_speed_proc(velocity, VSpeed, 20.0f, 20.0f);
    }

    effect->effect_specific[2] = 0;
    effect->effect_specific[3] = qrand();
    effect->effect_specific[0] = qrand();
    effect->effect_specific[1] = qrand();
    if (effect->arg1 > 3) {
        effect->scale.z = 0.010599999f;
        effect->scale.y = 0.010599999f;
        effect->scale.x = 0.010599999f;
    } else {
        effect->scale.z = 0.010199999f;
        effect->scale.y = 0.010199999f;
        effect->scale.x = 0.010199999f;
    }
    if (effect->effect_specific[5] == 1) {
        effect->scale.z = 0.0069999998f;
        effect->scale.y = 0.0069999998f;
        effect->scale.x = 0.0069999998f;
    }
    effect->acceleration.x = 0.0f;
    effect->acceleration.y = 0.5f * (0.1f * -effect->velocity.y);
    effect->acceleration.z = 0.0f;
}

static void eBushHappa_mv(eEC_Effect_c* effect, GAME* game) {
    float dt = (float)game->graph->dt_num_60fps_frames;

    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;

    if (effect->effect_specific[2] == 1) {
        f32 val = 2.0f * sin_s(effect->effect_specific[3]);
        float decay = powf(sqrtf(0.95f), dt);

        effect->offset.x = val;
        effect->offset.y = 0.0f;
        effect->offset.z = -val;

        effect->velocity.x *= decay;
        effect->velocity.z *= decay;

        effect->effect_specific[0] += (s16)(0x662 * dt);
        effect->effect_specific[1] += (s16)(0x662 * dt);
        effect->effect_specific[3] += (s16)(0xA00 * dt);
    } else {
        effect->effect_specific[0] += (s16)(0x280 * dt);
        effect->effect_specific[1] += (s16)(0x280 * dt);

        if (effect->velocity.y <= 0.0f) {
            effect->effect_specific[2] = 1;
            effect->acceleration.y = -0.05f;
        }
    }
}

static void eBushHappa_dw(eEC_Effect_c* effect, GAME* game) {
    mFM_field_pal_c* field_pal = mFI_GetFieldPal();
    GRAPH* graph;
    u16* cedar_pal;
    u16* golden_pal;
    u16* palm_pal;

    
    if (field_pal != NULL) {
        u8 alpha;
        cedar_pal = NULL;
        golden_pal = NULL;
        palm_pal = NULL;

        alpha = (int)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 28, 0.0f, 255.0f);

        if (effect->arg1 > 3) {
            cedar_pal = field_pal->cedar_tree_pal;
            golden_pal = field_pal->golden_tree_pal;
            palm_pal = field_pal->palm_tree_pal;
        }
        if (((cedar_pal != NULL) && (golden_pal != NULL)) || (effect->arg1 <= 3)) {
            N64Mtx* mtx = GRAPH_ALLOC_TYPE(game->graph, N64Mtx, 1);
            graph = game->graph;
            _texture_z_light_fog_prim_xlu(graph);
            suMtxMakeSRT_ZXY(mtx, effect->scale.x, effect->scale.y, effect->scale.z, effect->effect_specific[0], 0,
                             effect->effect_specific[1], effect->position.x + effect->offset.x,
                             effect->position.y + effect->offset.y, effect->position.z + effect->offset.z);
            OPEN_DISP(graph);

            gSPMatrix(NEXT_POLY_XLU_DISP, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, alpha);

            if (effect->arg1 > 3) {
                if (effect->effect_specific[4] == 3) {
                    gSPSegment(NEXT_POLY_XLU_DISP,G_MWO_SEGMENT_8, golden_pal);

                } else if (effect->effect_specific[4] == 0) {
                    gSPSegment(NEXT_POLY_XLU_DISP,G_MWO_SEGMENT_8, cedar_pal);
                } else {
                    gSPSegment(NEXT_POLY_XLU_DISP,G_MWO_SEGMENT_8, palm_pal);
                }
                if (effect->effect_specific[4] == 1) {
                    gSPDisplayList(NEXT_POLY_XLU_DISP,ef_s_palm_modelT);
                } else if (effect->effect_specific[4] == 2) {
                    gSPDisplayList(NEXT_POLY_XLU_DISP,ef_s_cedar_modelT);
                } else if (effect->arg1 > 5) {
                    gSPDisplayList(NEXT_POLY_XLU_DISP,ef_f_tree01_00_modelT);
                } else {
                    gSPDisplayList(NEXT_POLY_XLU_DISP,ef_s_tree01_00_modelT);
                }
            }
            else{
                gSPDisplayList(NEXT_POLY_XLU_DISP,ef_s_yabu01_00_modelT);
            }

            CLOSE_DISP(graph);
        }
    }
}
