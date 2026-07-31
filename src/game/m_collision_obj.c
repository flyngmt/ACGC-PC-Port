#include "m_collision_obj.h"
#include "m_actor.h"
#include <dolphin/os.h>

McoWork mco_work;

void CollisionCheck_workTrisElemCenter(ClObjTrisElem_c* tri, xyz_t* vec) {
    vec->x = (tri->attribute.tri.vtx[0].x + tri->attribute.tri.vtx[1].x + tri->attribute.tri.vtx[2].x) * (1.0f / 3.0f);
    vec->y = (tri->attribute.tri.vtx[0].y + tri->attribute.tri.vtx[1].y + tri->attribute.tri.vtx[2].y) * (1.0f / 3.0f);
    vec->z = (tri->attribute.tri.vtx[0].z + tri->attribute.tri.vtx[1].z + tri->attribute.tri.vtx[2].z) * (1.0f / 3.0f);
}

int ClObj_ct(GAME* game, ClObj_c* cl) {
    static ClObj_c clobj_default = { NULL, NULL, 0, 0, 3 };

    *cl = clobj_default;

    return 1;
}

int ClObj_dt(GAME* game, ClObj_c* collision) {
    return 1;
}

int ClObj_set4(GAME* game, ClObj_c* cl, ACTOR* actor, ClObjData_c* data) {
    cl->owner_actor = actor;
    cl->collision_flags0 = data->collision_flags0;
    cl->collision_flags1 = data->collision_flags1;
    cl->collision_type = data->type;

    return 1;
}

void ClObj_OCClear(GAME* game, ClObj_c* cl) {
    cl->collision_flags0 &= ~ClObj_FLAG_COLLIDED;
    cl->collided_actor = NULL;
    cl->collision_flags1 &= ~ClObj_FLAG2_PLAYER_WAS_HIT;
}

int ClObjElem_ct(ClObjElem_c* elem) {
    elem->flags = 0;

    return 1;
}

int ClObjElem_set(ClObjElem_c* elem, ClObjElemData_c* data) {
    elem->flags = data->flags;

    return 1;
}

void ClObjElem_OCClear(GAME* game, ClObjElem_c* elem) {
    elem->flags &= ~ClObjElem_FLAG_HIT;
}

int ClObjJntSphElem_OCClear(GAME* game, ClObjJntSphElem_c* col) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjElem_OCClear(game, &col->element);

    return 1;
}

int ClObjJntSph_OCClear(GAME* game, ClObj_c* cl) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjJntSph_c* jntsph = (ClObjJntSph_c*)cl;
    ClObjJntSphElem_c* elem;

    ClObj_OCClear(game, &jntsph->collision_obj);

    for (elem = jntsph->elements; elem < &jntsph->elements[jntsph->count]; elem++) {
        ClObjJntSphElem_OCClear(game, elem);
    }

    return 1;
}

int ClObjPipeAttr_ct(GAME* game, ClObjPipeAttr_c* attribute) {
    static ClObjPipeAttr_c default_pipe_attr = { 0, 0, 0 };

    *attribute = default_pipe_attr;

    return 1;
}

int ClObjPipeAttr_dt(GAME* game, ClObjPipeAttr_c* collision) {
    return 1;
}

int ClObjPipeAttr_set(GAME* game, ClObjPipeAttr_c* dst, ClObjPipeAttr_c* src) {
    *dst = *src;

    return 1;
}

int ClObjPipe_ct(GAME* game, ClObjPipe_c* pipe) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObj_ct(game, &pipe->collision_obj);
    ClObjElem_ct(&pipe->element);
    ClObjPipeAttr_ct(game, &pipe->attribute);

    return 1;
}

int ClObjPipe_dt(GAME* game, ClObjPipe_c* pipe) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObj_dt(game, &pipe->collision_obj);
    ClObjPipeAttr_dt(game, &pipe->attribute);

    return 1;
}

int ClObjPipe_set5(GAME* game, ClObjPipe_c* pipe, ACTOR* owner, ClObjPipeData_c* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObj_set4(game, &pipe->collision_obj, owner, &data->collision_data);
    ClObjElem_set(&pipe->element, &data->element_data);
    ClObjPipeAttr_set(game, &pipe->attribute, (ClObjPipeAttr_c*)&data->attribute_data);

    return 1;
}

int ClObjPipe_OCClear(GAME* game, ClObj_c* cl) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjPipe_c* pipe = (ClObjPipe_c*)cl;

    ClObj_OCClear(game, &pipe->collision_obj);
    ClObjElem_OCClear(game, &pipe->element);

    return 1;
}

int ClObjTrisElemAttr_ct(GAME* game, ClObjTrisElemAttr_c* tris) {
    static ClObjTrisElemAttr_c default_clobjtriselem_attr = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                                              0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

    *tris = default_clobjtriselem_attr;

    return 1;
}

int ClObjTrisElemAttr_dt(GAME* game, ClObjTrisElemAttr_c* tris) {
    return 1;
}

int ClObjTrisElemAttr_set(GAME* game, ClObjTrisElemAttr_c* tris, ClObjTrisElemAttrData_c* data) {
    xyz_t* dst;
    xyz_t* src;
    f32 nox, noy, noz, odist;

    for (dst = tris->tri.vtx, src = data->vtx; dst < &tris->tri.vtx[3]; dst++, src++) {
        *dst = *src;
    }

    Math3DPlane(&data->vtx[0], &data->vtx[1], &data->vtx[2], &nox, &noy, &noz, &odist);
    tris->tri.plane.normal.x = nox;
    tris->tri.plane.normal.y = noy;
    tris->tri.plane.normal.z = noz;
    tris->tri.plane.originDist = odist;

    return 1;
}

int ClObjTrisElem_ct(GAME* game, ClObjTrisElem_c* tris) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjElem_ct(&tris->element);
    ClObjTrisElemAttr_ct(game, &tris->attribute);

    return 1;
}

int ClObjTrisElem_dt(GAME* game, ClObjTrisElem_c* tris) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjTrisElemAttr_dt(game, &tris->attribute);

    return 1;
}

int ClObjTrisElem_set(GAME* game, ClObjTrisElem_c* tris, ClObjTrisElemData_c* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjElem_set(&tris->element, &data->element);
    ClObjTrisElemAttr_set(game, &tris->attribute, &data->data);

    return 1;
}

int ClObjTrisElem_OCClear(GAME* game, ClObjTrisElem_c* tris) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjElem_OCClear(game, &tris->element);

    return 1;
}

int ClObjTris_ct(GAME* game, ClObjTris_c* tris) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObj_ct(game, &tris->collision_obj);
    tris->count = 0;
    tris->elements = NULL;

    return 1;
}

int ClObjTris_dt_nzf(GAME* game, ClObjTris_c* tris) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjTrisElem_c* element;

    ClObj_dt(game, &tris->collision_obj);

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        ClObjTrisElem_dt(game, element);
    }
    tris->count = 0;
    tris->elements = NULL;

    return 1;
}

int ClObjTris_set5_nzm(GAME* game, ClObjTris_c* tris, ACTOR* actor, ClObjTrisData_c* data, ClObjTrisElem_c* elem) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjTrisElem_c* element;
    ClObjTrisElemData_c* elementData;

    ClObj_set4(game, &tris->collision_obj, actor, &data->data);

    tris->count = data->count;
    tris->elements = elem;

    for (element = tris->elements, elementData = data->elem_data; element < &tris->elements[tris->count];
         element++, elementData++) {
        ClObjTrisElem_ct(game, element);
        ClObjTrisElem_set(game, element, elementData);
    }

    return 1;
}

int ClObjTris_OCClear(GAME* game, ClObj_c* cl) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjTris_c* tris = (ClObjTris_c*)cl;
    ClObjTrisElem_c* element;

    ClObj_OCClear(game, &tris->collision_obj);

    for (element = tris->elements; element < &tris->elements[tris->count]; element++) {
        ClObjTrisElem_OCClear(game, element);
    }

    return 1;
}

void CollisionCheck_ct(GAME* game, CollisionCheck_c* col) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    col->flags = 0;
    CollisionCheck_clear(game, col);
}

void CollisionCheck_dt(GAME* game, CollisionCheck_c* col) {
}

void CollisionCheck_clear(GAME* game, CollisionCheck_c* col) {
    ClObj_c** clp;

    if (col->flags & CollisionCheck_FLAG_SKIP) {
        return;
    }

    col->collider_num = 0;

    for (clp = col->collider_table; clp < &col->collider_table[Cl_COLLIDER_NUM]; clp++) {
        *clp = NULL;
    }

    mco_work.count = 0;

    for (clp = mco_work.colliders; clp < &mco_work.colliders[10]; clp++) {
        *clp = NULL;
    }
}

CollisionClearFunction OCClearFunctionTable[ClObj_TYPE_NUM] = { ClObjJntSph_OCClear, ClObjPipe_OCClear,
                                                                ClObjTris_OCClear };

CollisionOCFunction oc_collision_function[ClObj_TYPE_NUM][ClObj_TYPE_NUM] = {
    { CollisionCheck_OC_JntSph_Vs_JntSph, CollisionCheck_OC_JntSph_Vs_Pipe, NULL },
    { CollisionCheck_OC_Pipe_Vs_JntSph, CollisionCheck_OC_Pipe_Vs_Pipe, NULL },
    { NULL, NULL, NULL }
};

CollisionOCFunction occ_collision_function[ClObj_TYPE_NUM][ClObj_TYPE_NUM] = {
    { NULL, NULL, NULL },
    { NULL, NULL, NULL },
    { (CollisionOCFunction)CollisionCheck_OCC_Tris_Vs_JntSph, (CollisionOCFunction)CollisionCheck_OCC_Tris_Vs_Pipe,
      NULL }
};

CollisionOCClear OCCClearFunctionTable[ClObj_TYPE_NUM] = { NULL, NULL, ClObjTris_OCCClear };

int CollisionCheck_setOC(GAME* game, CollisionCheck_c* col, ClObj_c* cl) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int ret;

    if (_Game_play_isPause(play) == 1) {
        return -1;
    } else {
        OCClearFunctionTable[cl->collision_type](game, cl);

        if ((cl->owner_actor != NULL) && (cl->owner_actor->mv_proc == NULL)) {
            return -1;
        }

        if (col->collider_num >= Cl_COLLIDER_NUM) {
            return -1;
        }

        if (col->flags & CollisionCheck_FLAG_SKIP) {
            return -1;
        }

        ret = col->collider_num;
        col->collider_table[col->collider_num] = cl;
        col->collider_num++;
    }

    return ret;
}

int get_type(u8 type) {
    if (type == MASSTYPE_IMMOVABLE) {
        return MASS_IMMOVABLE;
    }

    if (type == MASSTYPE_HEAVY) {
        return MASS_HEAVY;
    }

    return MASS_NORMAL;
}

void CollisionCheck_setOC_HitInfo(ClObj_c* col1, ClObjElem_c* colelem1, xyz_t* pos1, ClObj_c* col2,
                                  ClObjElem_c* colelem2, xyz_t* pos2, f32 diff) {
    ACTOR* actor1;
    ACTOR* actor2;
    int type1;
    int type2;

    f32 xdiff;
    f32 zdiff;
    f32 xzdist;

    f32 weight1;
    f32 weight2;
    f32 comweight;
    f32 minweight;

    f32 coldis1;
    f32 coldis2;

    actor1 = col1->owner_actor;
    actor2 = col2->owner_actor;

    col1->collided_actor = actor2;
    col1->collision_flags0 |= ClObj_FLAG_COLLIDED;
    colelem1->flags |= ClObjElem_FLAG_HIT;

    if (col2->collision_flags1 & ClObj_FLAG2_IS_PLAYER) {
        col1->collision_flags1 |= ClObj_FLAG2_PLAYER_WAS_HIT;
    }

    col2->collided_actor = actor1;
    col2->collision_flags0 |= ClObj_FLAG_COLLIDED;
    colelem2->flags |= ClObjElem_FLAG_HIT;

    if (col1->collision_flags1 & ClObj_FLAG2_IS_PLAYER) {
        col2->collision_flags1 |= ClObj_FLAG2_PLAYER_WAS_HIT;
    }

    if ((actor1 == NULL) || (actor2 == NULL)) {
        return;
    }

    if ((col1->collision_flags0 & ClObj_FLAG_DONT_UPDATE_POS) || (col2->collision_flags0 & ClObj_FLAG_DONT_UPDATE_POS)) {
        return;
    }

    type1 = get_type(actor1->status_data.weight);
    type2 = get_type(actor2->status_data.weight);

    weight1 = actor1->status_data.weight;
    weight2 = actor2->status_data.weight;

    comweight = weight1 + weight2;

    if (F32_IS_ZERO(comweight)) {
        weight1 = weight2 = 1.0f;
        comweight = 2.0f;
    }

    minweight = 1.0f / comweight;

    xdiff = pos2->x - pos1->x;
    zdiff = pos2->z - pos1->z;

    xzdist = sqrtf((xdiff * xdiff) + (zdiff * zdiff));

    if (type1 == MASS_IMMOVABLE) {
        if (type2 == MASS_IMMOVABLE) {
            return;
        }
        coldis1 = 0.0f;
        coldis2 = 1.0f;
    } else if (type1 == MASS_HEAVY) {
        if (type2 == MASS_IMMOVABLE) {
            coldis1 = 1.0f;
            coldis2 = 0.0f;
        } else if (type2 == MASS_HEAVY) {
            coldis1 = 0.5f;
            coldis2 = 0.5f;
        } else {
            coldis1 = 0.0f;
            coldis2 = 1.0f;
        }
    } else {
        if (type2 == MASS_NORMAL) {
            coldis1 = weight2 * minweight;
            coldis2 = weight1 * minweight;
        } else {
            coldis1 = 1.0f;
            coldis2 = 0.0f;
        }
    }

    if (col1->collision_flags0 & ClObj_FLAG_COLLISION_PRIORITY) {
        coldis1 = 0.0f;
        coldis2 = 1.0f;
        actor2->speed = 0.0f;
    } else if (col2->collision_flags0 & ClObj_FLAG_COLLISION_PRIORITY) {
        coldis1 = 1.0f;
        coldis2 = 0.0f;
        actor1->speed = 0.0f;
    }

    if (!(F32_IS_ZERO(xzdist))) {
        xdiff *= diff / xzdist;
        zdiff *= diff / xzdist;

        actor1->status_data.collision_vec.x += -xdiff * coldis1;
        actor1->status_data.collision_vec.z += -zdiff * coldis1;

        actor2->status_data.collision_vec.x += xdiff * coldis2;
        actor2->status_data.collision_vec.z += zdiff * coldis2;
    } else if (diff != 0) {
        actor1->status_data.collision_vec.x += -diff * coldis1;
        actor2->status_data.collision_vec.x += diff * coldis2;
    } else {
        actor1->status_data.collision_vec.x -= coldis1;
        actor2->status_data.collision_vec.x += coldis2;
    }
}

void CollisionCheck_OC_JntSph_Vs_JntSph(GAME* game, CollisionCheck_c* check, ClObj_c* col1, ClObj_c* col2) {
    ClObjJntSph_c* jntsph1 = (ClObjJntSph_c*)col1;
    ClObjJntSph_c* jntsph2 = (ClObjJntSph_c*)col2;

    ClObjJntSphElem_c* elem1;
    ClObjJntSphElem_c* elem2;

    if ((jntsph1->count <= 0) || (jntsph1->elements == NULL) || (jntsph2->count <= 0) || (jntsph2->elements == NULL)) {
        return;
    }

    for (elem1 = jntsph1->elements; elem1 < &jntsph1->elements[jntsph1->count]; elem1++) {
        if ((elem1->element.flags & ClObjElem_FLAG_CHECK)) {
            for (elem2 = jntsph2->elements; elem2 < &jntsph2->elements[jntsph2->count]; elem2++) {
                f32 in;

                if ((elem2->element.flags & ClObjElem_FLAG_CHECK)) {
                    if (Math3D_sphereCrossSphere_cl(&elem1->attribute.s2, &elem2->attribute.s2, &in) == 1) {
                        xyz_t pos1;
                        xyz_t pos2;

                        xyz_t_move_s_xyz(&pos1, &elem1->attribute.s2.center);
                        xyz_t_move_s_xyz(&pos2, &elem2->attribute.s2.center);
                        CollisionCheck_setOC_HitInfo(&jntsph1->collision_obj, &elem1->element, &pos1,
                                                     &jntsph2->collision_obj, &elem2->element, &pos2, in);
                    }
                }
            }
        }
    }
}

void CollisionCheck_OC_JntSph_Vs_Pipe(GAME* game, CollisionCheck_c* check, ClObj_c* col1, ClObj_c* col2) {
    ClObjJntSph_c* jntsph = (ClObjJntSph_c*)col1;
    ClObjPipe_c* pipe = (ClObjPipe_c*)col2;
    ClObjJntSphElem_c* elem;
    f32 in;
    xyz_t sphpos;
    xyz_t pipepos;

    if ((jntsph->count > 0) && (jntsph->elements) != NULL) {
        if (!(jntsph->collision_obj.collision_flags0 & ClObj_FLAG_CHECK) || !(pipe->collision_obj.collision_flags0 & ClObj_FLAG_CHECK) ||
            !(pipe->element.flags & ClObjElem_FLAG_CHECK)) {
            return;
        }

        for (elem = jntsph->elements; elem < &jntsph->elements[jntsph->count]; elem++) {
            if (!(elem->element.flags & ClObjElem_FLAG_CHECK)) {
                continue;
            }

            if (Math3D_sphereVsPipe_cl(&elem->attribute.s2, &pipe->attribute.pipe, &in) == 1) {
                xyz_t_move_s_xyz(&sphpos, &elem->attribute.s2.center);
                xyz_t_move_s_xyz(&pipepos, &pipe->attribute.pipe.center);
                CollisionCheck_setOC_HitInfo(&jntsph->collision_obj, &elem->element, &sphpos, &pipe->collision_obj,
                                             &pipe->element, &pipepos, in);
            }
        }
    }
}

void CollisionCheck_OC_Pipe_Vs_JntSph(GAME* game, CollisionCheck_c* colcheck, ClObj_c* col1, ClObj_c* col2) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    CollisionCheck_OC_JntSph_Vs_Pipe(game, colcheck, col2, col1);
}

void CollisionCheck_OC_Pipe_Vs_Pipe(GAME* game, CollisionCheck_c* colcheck, ClObj_c* col1, ClObj_c* col2) {
    ClObjPipe_c* pipe1 = (ClObjPipe_c*)col1;
    ClObjPipe_c* pipe2 = (ClObjPipe_c*)col2;
    f32 in;
    xyz_t pipepos1;
    xyz_t pipepos2;

    if (!(pipe1->collision_obj.collision_flags0 & ClObj_FLAG_CHECK) || !(pipe2->collision_obj.collision_flags0 & ClObj_FLAG_CHECK) ||
        !(pipe1->element.flags & ClObjElem_FLAG_CHECK) || !(pipe2->element.flags & ClObjElem_FLAG_CHECK)) {
        return;
    }

    if (Math3D_pipeVsPipe_cl(&pipe1->attribute.pipe, &pipe2->attribute.pipe, &in) != 1) {
        return;
    }

    xyz_t_move_s_xyz(&pipepos1, &pipe1->attribute.pipe.center);
    xyz_t_move_s_xyz(&pipepos2, &pipe2->attribute.pipe.center);

    CollisionCheck_setOC_HitInfo(&pipe1->collision_obj, &pipe1->element, &pipepos1, &pipe2->collision_obj,
                                 &pipe2->element, &pipepos2, in);
}

int CollisionCheck_Check1ClObjNoOC(ClObj_c* col) {
    return col->collision_flags0 & ClObj_FLAG_CHECK ^ ClObj_FLAG_CHECK;
}

int CollisionCheck_Check2ClObjNoOC(ClObj_c* col1, ClObj_c* col2) {
    if (!(col1->collision_flags0 & col2->collision_flags1 & ClObj_GROUP_ALL) ||
        !(col1->collision_flags1 & col2->collision_flags0 & ClObj_GROUP_ALL)) {
        return 1;
    }

    if (col1->owner_actor == col2->owner_actor) {
        return 1;
    }
    return 0;
}

void CollisionCheck_OC(GAME* game, CollisionCheck_c* colcheck) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObj_c** col1p;
    ClObj_c** col2p;
    CollisionOCFunction current;

    for (col1p = colcheck->collider_table; col1p < &colcheck->collider_table[colcheck->collider_num]; col1p++) {
        if (((*col1p) == NULL) || (CollisionCheck_Check1ClObjNoOC(*col1p) == 1)) {
            continue;
        }

        for (col2p = col1p + 1; col2p < &colcheck->collider_table[colcheck->collider_num]; col2p++) {
            if ((*col2p == NULL) || (CollisionCheck_Check1ClObjNoOC(*col2p) == 1) ||
                (CollisionCheck_Check2ClObjNoOC(*col1p, *col2p) == 1)) {
                continue;
            }
            current = oc_collision_function[(*col1p)->collision_type][(*col2p)->collision_type];

            if (current == NULL) {
                continue;
            }

            current(game, colcheck, *col1p, *col2p);
        }
    }

    CollisionCheck_OCC(game, colcheck);
}

void CollisionCheck_setOCC_HitInfo(GAME* game, ClObj_c* col1, ClObjTrisElem_c* elem1, xyz_t* pos1, ClObj_c* col2,
                                   ClObjElem_c* elem2, xyz_t* pos2, xyz_t* pos3) {
    col1->collided_actor = col2->owner_actor;
    col1->collision_flags1 |= ClObj_FLAG2_TRIS_HIT;

    elem1->attribute.t.x = pos3->x;
    elem1->attribute.t.y = pos3->y;
    elem1->attribute.t.z = pos3->z;
}

void CollisionCheck_OCC_Tris_Vs_JntSph(GAME* game, CollisionCheck_c* colcheck, ClObjTris_c* tris,
                                       ClObjJntSph_c* jntsph) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjTrisElem_c* triselem;
    ClObjJntSphElem_c* jntsphelem;
    xyz_t pos;
    xyz_t sphpos;
    xyz_t trispos;

    if ((tris->count <= 0) || (tris->elements == NULL) || (jntsph->count <= 0) || (jntsph->elements == NULL)) {
        return;
    }

    for (jntsphelem = jntsph->elements; jntsphelem < &jntsph->elements[jntsph->count]; jntsphelem++) {
        if ((jntsphelem->element.flags & ClObjElem_FLAG_CHECK)) {
            for (triselem = tris->elements; triselem < &tris->elements[tris->count]; triselem++) {
                if (Math3D_sphereCrossTriangle3_cp(&jntsphelem->attribute.s2, &triselem->attribute.tri, &pos) != 0) {
                    xyz_t_move_s_xyz(&sphpos, &jntsphelem->attribute.s2.center);
                    CollisionCheck_workTrisElemCenter(triselem, &trispos);
                    CollisionCheck_setOCC_HitInfo(game, &tris->collision_obj, triselem, &trispos,
                                                  &jntsph->collision_obj, &jntsphelem->element, &sphpos, &pos);
                }
            }
        }
    }
}

void CollisionCheck_OCC_Tris_Vs_Pipe(GAME* game, CollisionCheck_c* colcheck, ClObjTris_c* tris, ClObjPipe_c* pipe) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    ClObjTrisElem_c* triselem;
    xyz_t pos;
    xyz_t pipepos;
    xyz_t trispos;

    if ((pipe->attribute.pipe.radius > 0) && (pipe->attribute.pipe.height > 0) && (pipe->element.flags & ClObjElem_FLAG_CHECK)) {
        if ((tris->count <= 0) || (tris->elements == NULL)) {
            return;
        }

        for (triselem = tris->elements; triselem < &tris->elements[tris->count]; triselem++) {
            if (Math3D_pipeCrossTriangle_cp(&pipe->attribute.pipe, &triselem->attribute.tri, &pos) != 0) {
                CollisionCheck_workTrisElemCenter(triselem, &trispos);
                xyz_t_move_s_xyz(&pipepos, &pipe->attribute.pipe.center);
                CollisionCheck_setOCC_HitInfo(game, &tris->collision_obj, triselem, &trispos, &pipe->collision_obj,
                                              &pipe->element, &pipepos, &pos);
                break;
            }
        }
    }
}

int CollisionCheck_Check1ClObjNoOCC(ClObj_c* col) {
    return (col->collision_flags1 & ClObj_FLAG2_OCC_CHECK) >> 1 ^ 1;
}

void CollisionCheck_OCC(GAME* game, CollisionCheck_c* colcheck) {
    ClObj_c** col1p;
    ClObj_c** col2p;
    CollisionOCFunction current;

    if (mco_work.count == 0) {
        return;
    }

    for (col1p = mco_work.colliders; col1p < &mco_work.colliders[mco_work.count]; col1p++) {
        if (((*col1p) == NULL) || (CollisionCheck_Check1ClObjNoOCC(*col1p) == 1)) {
            continue;
        }

        for (col2p = colcheck->collider_table; col2p < &colcheck->collider_table[colcheck->collider_num]; col2p++) {
            if ((*col2p) == NULL) {
                continue;
            }

            if ((*col1p)->owner_actor == (*col2p)->owner_actor) {
                continue;
            }

            current = occ_collision_function[(*col1p)->collision_type][(*col2p)->collision_type];

            if (current == NULL) {
                continue;
            }

            current(game, colcheck, *col1p, *col2p);
        }
    }
}

int ClObjTrisElem_OCCClear(GAME* game, ClObjTrisElem_c* triselem) {
    triselem->attribute.t.x = 0.0f;
    triselem->attribute.t.y = 0.0f;
    triselem->attribute.t.z = 0.0f;
    return 1;
}

int ClObj_OCCClear(GAME* game, ClObj_c* col) {
    col->collided_actor = NULL;
    col->collision_flags1 &= ~ClObj_FLAG_DONT_UPDATE_POS;
}

int ClObjTris_OCCClear(GAME* game, ClObj_c* col) {
    ClObjTris_c* tris = (ClObjTris_c*)col;
    ClObjTrisElem_c* triselem;

    ClObj_OCCClear(game, &tris->collision_obj);

    for (triselem = tris->elements; triselem < &tris->elements[tris->count]; triselem++) {
        ClObjTrisElem_OCCClear(game, triselem);
    }

    return 1;
}

int CollisionCheck_setOCC(GAME* game, CollisionCheck_c* colcheck, ClObj_c* col) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int ret;

    if (_Game_play_isPause(play) == 1) {
        return -1;
    }

    if ((col->collision_type == ClObj_TYPE_JNT_SPH) || (col->collision_type == ClObj_TYPE_PIPE)) {
        return -1;
    }

    OCCClearFunctionTable[col->collision_type](game, col);

    if ((col->owner_actor != NULL) && (col->owner_actor->mv_proc == NULL)) {
        return -1;
    }

    if (mco_work.count >= 10) {
        return -1;
    }

    if (colcheck->flags & CollisionCheck_FLAG_SKIP) {
        return -1;
    }

    ret = mco_work.count;
    mco_work.colliders[mco_work.count] = col;
    mco_work.count++;

    return ret;
}

void CollisionCheck_Status_ct(Status_c* status) {
    static Status_c status_org = { { 0.0f, 0.0f, 0.0f }, 10, 10, 0, 50, 8, 0, 0, 0 };

    *status = status_org;
}

void CollisionCheck_Status_Clear(Status_c* status) {
    status->damage = 0;
    status->damage_effect = 0;
    status->at_hit_effect = 0;
    status->ac_hit_effect = 0;
    status->collision_vec.z = 0.0f;
    status->collision_vec.y = 0.0f;
    status->collision_vec.x = 0.0f;
}

void CollisionCheck_Status_set3(Status_c* status, StatusData_c* data) {
    status->hp = data->health;
    status->radius = data->radius;
    status->height = data->height;
    status->offset = data->offset;
    status->weight = data->weight;
}

int CollisionCheck_Uty_ActorWorldPosSetPipeC(ACTOR* actor, ClObjPipe_c* pipe) {
    pipe->attribute.pipe.center.x = actor->world.position.x;
    pipe->attribute.pipe.center.y = actor->world.position.y;
    pipe->attribute.pipe.center.z = actor->world.position.z;
}
