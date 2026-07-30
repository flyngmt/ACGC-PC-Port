#include "m_lights.h"

#include "m_rcp.h"
#include "libultra/libultra.h"
#include "m_play.h"
#include "sys_matrix.h"
Light_buffer light_list_buf;

extern Gfx point_light_init_model[];
extern Gfx point_light_model[];

static void Light_point_color_set(Lights* lights, u8 r, u8 g, u8 b, s16 radius);
static void Global_light_list_ct(Global_light* light);
static void Global_light_ambient_set(Global_light* light, u8 r, u8 g, u8 b);
static void Global_light_fog_set(Global_light* light, u8 r, u8 g, u8 b, s16 near, s16 far);
static LightsN* new_LightsN(GRAPH*, u8 r, u8 g, u8 b);

static void point_data_set(Lights* lights, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius, int type) {

    lights->type = type;
    lights->lights.point.x = x;
    lights->lights.point.y = y;
    lights->lights.point.z = z;
    Light_point_color_set(lights, r, g, b, radius);
}

extern void Light_point_ct(Lights* lights, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius) {

    point_data_set(lights, x, y, z, r, g, b, radius, 0);
}

static void Light_point_color_set(Lights* lights, u8 r, u8 g, u8 b, s16 radius) {

    lights->lights.point.color[0] = r;
    lights->lights.point.color[1] = g;
    lights->lights.point.color[2] = b;
    lights->lights.point.radius = radius;
}

extern void Light_diffuse_ct(Lights* lights, s8 x, s8 y, s8 z, u8 r, u8 g, u8 b) {

    lights->type = 1;
    lights->lights.diffuse.x = x;
    lights->lights.diffuse.y = y;
    lights->lights.diffuse.z = z;
    lights->lights.diffuse.color[0] = r;
    lights->lights.diffuse.color[1] = g;
    lights->lights.diffuse.color[2] = b;
}

extern void LightsN_disp_BG(LightsN* lights, GRAPH* graph) {

    Light_new* light;
    int i;

    OPEN_DISP(graph);

    gSPNumLights(NOW_BG_OPA_DISP++, lights->diffuse_count);

    light = lights->l;

    for (i = 0; i < lights->diffuse_count; i) {
        i++;
        gSPLight(NOW_BG_OPA_DISP++, light, i);
        gSPLight(NOW_BG_XLU_DISP++, light, i);
        light++;
    }

    i++;
    gSPLight(NOW_BG_OPA_DISP++, &lights->a.l, i);
    gSPLight(NOW_BG_XLU_DISP++, &lights->a.l, i);

    CLOSE_DISP(graph);
}

extern void LightsN_disp(LightsN* lights, GRAPH* graph) {

    Light_new* light;
    int i;
    Gfx* opa_gfx;
    Gfx* xlu_gfx;

    OPEN_DISP(graph);
    opa_gfx = NOW_POLY_OPA_DISP;
    xlu_gfx = NOW_POLY_XLU_DISP;

    gSPNumLights(opa_gfx++, lights->diffuse_count);
    gSPNumLights(xlu_gfx++, lights->diffuse_count);

    light = lights->l;

    for (i = 0; i < lights->diffuse_count;) {
        i++;
        gSPLight(opa_gfx++, light, i);
        gSPLight(xlu_gfx++, light, i);
        light++;
    }

    i++;
    gSPLight(opa_gfx++, &lights->a.l, i);
    gSPLight(xlu_gfx++, &lights->a.l, i);

    SET_POLY_OPA_DISP(opa_gfx);
    SET_POLY_XLU_DISP(xlu_gfx);
    CLOSE_DISP(graph);
}

static Light_new* LightsN_new_diffuse(LightsN* lights) {

    if (lights->diffuse_count >= 7) {
        return NULL;
    }

    return &lights->l[lights->diffuse_count++];
}

static void LightsN__point_proc(LightsN* lights, LightParams* lightInfo, xyz_t* point) {
    f32 xdiff;
    f32 ydiff;
    f32 zdiff;
    f32 pointd;
    f32 rad;
    Light_new* light;

    if ((point != NULL) && (lightInfo->point.radius > 0)) {
        xdiff = lightInfo->point.x - point->x;
        ydiff = lightInfo->point.y - point->y;
        zdiff = lightInfo->point.z - point->z;
        pointd = (xdiff * xdiff) + (ydiff * ydiff) + (zdiff * zdiff);

        rad = lightInfo->point.radius;

        if (pointd < (rad * rad)) {
            light = LightsN_new_diffuse(lights);

            if (light != NULL) {
                pointd = sqrtf(pointd);
                rad = pointd / rad;
                rad = 1 - (rad * rad);

                light->l.col[0] = light->l.colc[0] = lightInfo->point.color[0] * rad;
                light->l.col[1] = light->l.colc[1] = lightInfo->point.color[1] * rad;
                light->l.col[2] = light->l.colc[2] = lightInfo->point.color[2] * rad;

                rad = (pointd < 1) ? 120.0f : 120.0f / pointd;

                light->l.dir[0] = xdiff * rad;
                light->l.dir[1] = ydiff * rad;
                light->l.dir[2] = zdiff * rad;
            }
        }
    }
}

static void LightsN__P_point_proc(LightsN* lights, LightParams* lightInfo, xyz_t* pos) {

    f32 rad;
    xyz_t point;
    Light_new* light;
    f32 kq;

    if (lightInfo->point.radius > 0) {
        light = LightsN_new_diffuse(lights);

        if (light != NULL) {
            rad = lightInfo->point.radius;
            kq = 4500000.0f / (rad * rad);
            if (kq > 255.0f) {
                kq = 255.0f;
            } else if (kq < 20.0f) {
                kq = 20.0f;
            }
            light->l.col[0] = lightInfo->point.color[0];
            light->l.colc[0] = light->l.col[0];

            light->l.col[1] = lightInfo->point.color[1];
            light->l.colc[1] = light->l.col[1];

            light->l.col[2] = lightInfo->point.color[2];
            light->l.colc[2] = light->l.col[2];

            light->p.pos[0] = lightInfo->point.x;
            light->p.pos[1] = lightInfo->point.y;
            light->p.pos[2] = lightInfo->point.z;
            light->p.kc = 8;
            light->p.kl = -1;
            light->p.kq = kq;
        }
    }
}

static void LightsN__diffuse_proc(LightsN* lights, LightParams* lightInfo) {

    Light_new* light;

    light = LightsN_new_diffuse(lights);

    if (light != NULL) {
        light->l.col[0] = light->l.colc[0] = lightInfo->diffuse.color[0];
        light->l.col[1] = light->l.colc[1] = lightInfo->diffuse.color[1];
        light->l.col[2] = light->l.colc[2] = lightInfo->diffuse.color[2];
        light->l.dir[0] = lightInfo->diffuse.x;
        light->l.dir[1] = lightInfo->diffuse.y;
        light->l.dir[2] = lightInfo->diffuse.z;
    }
}

extern void LightsN_list_check(LightsN* lights, Light_list* node, xyz_t* pos) {

    const static light_point_proc poslight_type_proc[] = { LightsN__point_proc, (light_point_proc)LightsN__diffuse_proc,
                                                           LightsN__point_proc };

    const static light_P_point_proc light_type_proc[] = { LightsN__P_point_proc,
                                                          (light_P_point_proc)LightsN__diffuse_proc,
                                                          LightsN__P_point_proc };

    if (pos == NULL) {
        while (node != NULL) {
            light_type_proc[node->info->type](lights, &node->info->lights, pos);
            node = node->next;
        }
    } else {
        while (node != NULL) {
            poslight_type_proc[node->info->type](lights, &node->info->lights, pos);
            node = node->next;
        }
    }
}

static Light_list* Light_list_buf_new() {

    Light_list* light;

    if (light_list_buf.current >= 32) {
        return NULL;
    }

    light = &light_list_buf.lights[light_list_buf.idx];

    while (light->info != NULL) {
        light_list_buf.idx++;
        if (light_list_buf.idx < 32) {
            light++;
        } else {
            light_list_buf.idx = 0;
            light = &light_list_buf.lights[0];
        }
    }

    light_list_buf.current++;
    return light;
}

static void Light_list_buf_delete(Light_list* light) {
    if (light != NULL) {
        light_list_buf.current--;
        light->info = NULL;
        light_list_buf.idx = (int)(light - light_list_buf.lights);
    }
}

extern void Global_light_ct(Global_light* glight) {

    Global_light_list_ct(glight);
    Global_light_ambient_set(glight, 80, 80, 80);
    Global_light_fog_set(glight, 0, 0, 0, 996, 1600);
    bzero(&light_list_buf, sizeof(Light_buffer));
}

static void Global_light_ambient_set(Global_light* glight, u8 r, u8 g, u8 b) {

    glight->ambientColor[0] = r;
    glight->ambientColor[1] = g;
    glight->ambientColor[2] = b;
}

static void Global_light_fog_set(Global_light* glight, u8 r, u8 g, u8 b, s16 near, s16 far) {

    glight->fogColor[0] = r;
    glight->fogColor[1] = g;
    glight->fogColor[2] = b;
    glight->fogNear = near;
    glight->fogFar = far;
}

extern LightsN* Global_light_read(Global_light* glight, GRAPH* graph) {
    return new_LightsN(graph, glight->ambientColor[0], glight->ambientColor[1], glight->ambientColor[2]);
}

static void Global_light_list_ct(Global_light* glight) {

    glight->list = NULL;
}

extern Light_list* Global_light_list_new(GAME* game, Global_light* glight, Lights* light) {

    Light_list* clight;

    clight = Light_list_buf_new();

    if (clight != NULL) {
        clight->info = light;
        clight->prev = NULL;
        clight->next = glight->list;

        if (glight->list != NULL) {
            glight->list->prev = clight;
        }

        glight->list = clight;
    }

    return clight;
}

extern void Global_light_list_delete(Global_light* glight, Light_list* light) {

    if (light != NULL) {
        if (light->prev != NULL) {
            light->prev->next = light->next;
        } else {
            glight->list = light->next;
        }

        if (light->next != NULL) {
            light->next->prev = light->prev;
        }
        Light_list_buf_delete(light);
    }
}

static LightsN* new_LightsN(GRAPH* graph, u8 r, u8 g, u8 b) {

    LightsN* light;

    light = GRAPH_ALLOC(graph, sizeof(LightsN));

    light->a.l.col[0] = light->a.l.colc[0] = r;
    light->a.l.col[1] = light->a.l.colc[1] = g;
    light->a.l.col[2] = light->a.l.colc[2] = b;

    light->diffuse_count = 0;

    return light;
}

extern void Light_list_point_draw(GAME_PLAY* play) {
    LightPoint* lightInfo;
    Light_list* light;
    GRAPH* g = play->game.graph;
    f32 rad;
    Gfx* dl;

    light = play->global_light.list;

    OPEN_DISP(g);
    dl = gfx_softsprite_prim_xlu(NOW_POLY_XLU_DISP);

    gDPSetAlphaDither(dl++, G_AD_NOISE);
    gDPSetColorDither(dl++, G_CD_MAGICSQ);
    gSPDisplayList(dl++, point_light_init_model);

    while (light != NULL) {
        if (light->info->type == 2) {
            lightInfo = &light->info->lights.point;
            if (lightInfo->drawGlow) {
                rad = (lightInfo->radius * lightInfo->radius) * 2.60000001617e-06f;
                gDPSetPrimColor(dl++, 0, 0, lightInfo->color[0], lightInfo->color[1], lightInfo->color[2], 50);

                Matrix_translate(lightInfo->x, lightInfo->y, lightInfo->z, MTX_LOAD);
                Matrix_scale(rad, rad, rad, MTX_MULT);

                gSPMatrix(dl++, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                gSPDisplayList(dl++, point_light_model);
            }
        }
        light = light->next;
    }

    SET_POLY_XLU_DISP(dl);
    CLOSE_DISP(g);
}
