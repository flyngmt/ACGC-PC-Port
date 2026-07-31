#include "m_view.h"

#include "main.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "sys_matrix.h"
#include "libultra/libultra.h"

static void set_viewport(Vp* viewport, rect* screen_rect) {
  int width = screen_rect->r - screen_rect->l;
  int height = screen_rect->bottom - screen_rect->top;

  viewport->vp.vscale[0] = width * 4;
  viewport->vp.vscale[1] = height * 4;
  viewport->vp.vscale[2] = 511;
  viewport->vp.vscale[3] = 0;

  viewport->vp.vtrans[0] = (width + screen_rect->l) * 4;
  viewport->vp.vtrans[1] = (height + screen_rect->top) * 4;
  viewport->vp.vtrans[2] = 511;
  viewport->vp.vtrans[3] = 0;
}

extern void initView(View* view, GRAPH* graph) {
  view->graph = graph;
  
  view->screen.top = 0;
  view->screen.bottom = SCREEN_HEIGHT;
  view->screen.l = 0;
  view->screen.r = SCREEN_WIDTH;

  view->fovY = 20.0f;
  view->near = 200.0f;

  if (Common_Get(field_type) != mFI_FIELDTYPE2_FG) {
    view->near = 20.0f;
  }

  view->far = 1600.0f;

  view->scale = 1.0f;
  
  view->eye.x = 0.0f;
  view->eye.y = 0.0f;
  view->eye.z = -1.0f;

  /* copy -> paste bug here */
  #ifndef BUGFIXES
  view->center.x = 0.0f;
  view->center.x = 0.0f;
  view->center.x = 0.0f;
  #else
  view->center.x = 0.0f;
  view->center.y = 0.0f;
  view->center.z = 0.0f;
  #endif

  view->up.x = 0.0f;
  view->up.y = 1.0f;
  view->up.z = 0.0f;

  view->flag = VIEW_UPDATE_LOOKAT | VIEW_UPDATE_SCISSOR | VIEW_UPDATE_PERSPECTIVE;

#ifdef TARGET_PC
  /* PC: initialize viewport immediately so submenu restore has valid data
     even before showPerspectiveView runs. On GC, memory was likely zeroed. */
  set_viewport(&view->viewport, &view->screen);
#endif

  stretchViewInit(view);
}

extern void setLookAtView(View* view, xyz_t* eye, xyz_t* center, xyz_t* up) {
  if (eye->x == center->x && eye->z == center->z) {
    eye->x += 0.1f;
  }

  view->eye = *eye;
  view->center = *center;
  view->up = *up;

  view->flag |= VIEW_UPDATE_LOOKAT;
}

extern void setScaleView(View* view, f32 scale) {
  view->scale = scale;

  view->flag |= VIEW_UPDATE_PERSPECTIVE;
}

extern void setPerspectiveView(View* view, f32 fovY, f32 near, f32 far) {
  view->fovY = fovY;
  view->near = near;
  view->far = far;

  view->flag |= VIEW_UPDATE_PERSPECTIVE;
}

extern void setScissorView(View* view, rect* screen) {
  view->screen = *screen;

  view->flag |= VIEW_UPDATE_SCISSOR;
}

static void setScissorX(Gfx** gfx_p, int left, int top, int right, int bottom) {
  Gfx* gfx = *gfx_p;

  if (left == 0 && top == 0 && right == SCREEN_WIDTH && bottom == SCREEN_HEIGHT) {
    right *=  2;
    bottom *= 2;
  }

  gDPSetScissor(gfx++, G_SC_NON_INTERLACE, left, top, right, bottom);
  *gfx_p = gfx;
}

static void setScissor(View* view) {
  GRAPH* g = view->graph;
  int left = view->screen.l;
  int top = view->screen.top;
  int right = view->screen.r;
  int bottom = view->screen.bottom;
  Gfx* gfx;

  OPEN_DISP(g);

  gfx = NOW_POLY_OPA_DISP;
  setScissorX(&gfx, left, top, right, bottom);
  SET_POLY_OPA_DISP(gfx);

  gfx = NOW_POLY_XLU_DISP;
  setScissorX(&gfx, left, top, right, bottom);
  SET_POLY_XLU_DISP(gfx);

  gfx = NOW_SHADOW_DISP;
  setScissorX(&gfx, left, top, right, bottom);
  SET_SHADOW_DISP(gfx);

  gfx = NOW_LIGHT_DISP;
  setScissorX(&gfx, left, top, right, bottom);
  SET_LIGHT_DISP(gfx);

  CLOSE_DISP(g);
}

extern int stretchViewInit(View* view) {
  view->stretch.target_rotate.x = 0.0f;
  view->stretch.target_rotate.y = 0.0f;
  view->stretch.target_rotate.z = 0.0f;

  view->stretch.target_scale.x = 1.0f;
  view->stretch.target_scale.y = 1.0f;
  view->stretch.target_scale.z = 1.0f;

  view->stretch.rotate = view->stretch.target_rotate;
  view->stretch.scale = view->stretch.target_scale;
  view->stretch.step = 0.0f;

  return 0;
}

static int do_stretch_view(View* view, N64Mtx* mtx) {
  f32 step = view->stretch.step;

  if (step == 0.0f) {
    return FALSE;
  }
  else if (step == 1.0f) {
    view->stretch.rotate = view->stretch.target_rotate;
    view->stretch.scale = view->stretch.target_scale;
    view->stretch.step = 0.0f;
  }
  else {
    view->stretch.rotate.x += view->stretch.step * (view->stretch.target_rotate.x - view->stretch.rotate.x);
    view->stretch.rotate.y += view->stretch.step * (view->stretch.target_rotate.y - view->stretch.rotate.y);
    view->stretch.rotate.z += view->stretch.step * (view->stretch.target_rotate.z - view->stretch.rotate.z);

    view->stretch.scale.x += view->stretch.step * (view->stretch.target_scale.x - view->stretch.scale.x);
    view->stretch.scale.y += view->stretch.step * (view->stretch.target_scale.y - view->stretch.scale.y);
    view->stretch.scale.z += view->stretch.step * (view->stretch.target_scale.z - view->stretch.scale.z);
  }

  {
    s_xyz rot;
    MtxF mtx_f;

    rot.x = view->stretch.rotate.x * 10430.378f; // 57.3 degrees?
    rot.y = view->stretch.rotate.y * 10430.378f;
    rot.z = view->stretch.rotate.z * 10430.378f;

    /* push matrix to current */
    Matrix_MtxtoMtxF(mtx, &mtx_f);
    Matrix_put(&mtx_f);
    
    /* do rotation */
    Matrix_RotateX(rot.x, MTX_MULT);
    Matrix_RotateY(rot.y, MTX_MULT);
    Matrix_RotateZ(rot.z, MTX_MULT);

    /* do scaling */
    Matrix_scale(view->stretch.scale.x, view->stretch.scale.y, view->stretch.scale.z, MTX_MULT);

    /* undo rotation */
    Matrix_RotateZ(-rot.z, MTX_MULT);
    Matrix_RotateY(-rot.y, MTX_MULT);
    Matrix_RotateX(-rot.x, MTX_MULT);

    /* update matrix */
    _Matrix_to_Mtx(mtx);
  }

  return TRUE;
}

extern int showView(View* view, int flag_mask) {
  if (((flag_mask >> 4) | (flag_mask & view->flag)) & VIEW_UPDATE_ORTHOGRAPHIC) {
    return showOrthoView(view);
  }
  else {
    return showPerspectiveView(view);
  }
}

extern int showPerspectiveView(View* view) {
  GRAPH* g = view->graph;
  Vp* vp;
  N64Mtx* mtx;

  OPEN_DISP(g);

  /* update viewport */
  vp = GRAPH_ALLOC_TYPE(g, Vp, 1);
  set_viewport(vp, &view->screen);
  view->viewport = *vp;

  /* update scissor */
  setScissor(view);

  /* push viewport */
  gSPViewport(NOW_POLY_OPA_DISP++, vp);
  gSPViewport(NOW_POLY_XLU_DISP++, vp);
  gSPViewport(NOW_SHADOW_DISP++, vp);
  gSPViewport(NOW_LIGHT_DISP++, vp);
  gSPViewport(NOW_BG_OPA_DISP++, vp);
  gSPViewport(NOW_BG_XLU_DISP++, vp);

  /* update perspective matrix */
  mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);
  view->p_projection = mtx;
  guPerspective(
    mtx,
    &view->normal,
    view->fovY,
    (f32)(view->screen.r - view->screen.l) / (f32)(view->screen.bottom - view->screen.top),
    view->near, view->far,
    view->scale
  );

  view->mtx_projection = *mtx;

  do_stretch_view(view, mtx);

  gSPPerspNormalize(NOW_POLY_OPA_DISP++, view->normal);
  gSPMatrix(NOW_POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  gSPPerspNormalize(NOW_POLY_XLU_DISP++, view->normal);
  gSPMatrix(NOW_POLY_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  gSPPerspNormalize(NOW_SHADOW_DISP++, view->normal);
  gSPMatrix(NOW_SHADOW_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  gSPPerspNormalize(NOW_LIGHT_DISP++, view->normal);
  gSPMatrix(NOW_LIGHT_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  gSPPerspNormalize(NOW_BG_OPA_DISP++, view->normal);
  gSPMatrix(NOW_BG_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  gSPPerspNormalize(NOW_BG_XLU_DISP++, view->normal);
  gSPMatrix(NOW_BG_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  /* update look-at (viewing) matrix */
  mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);
  view->p_viewing = mtx;
  guLookAt(
    mtx,
    view->eye.x, view->eye.y, view->eye.z,
    view->center.x, view->center.y, view->center.z,
    view->up.x, view->up.y, view->up.z
  );
  view->mtx_viewing = *mtx;

  gSPMatrix(NOW_POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

  gSPMatrix(NOW_POLY_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

  gSPMatrix(NOW_SHADOW_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

  gSPMatrix(NOW_LIGHT_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

  gSPMatrix(NOW_BG_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

  gSPMatrix(NOW_BG_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

  CLOSE_DISP(g);

  return TRUE;
}

extern int showOrthoView(View* view) {
  GRAPH* g = view->graph;
  Vp* vp;
  N64Mtx* mtx;

  OPEN_DISP(g);

  /* update viewport */
  vp = GRAPH_ALLOC_TYPE(g, Vp, 1);
  set_viewport(vp, &view->screen);
  view->viewport = *vp;

  /* update scissor */
  setScissor(view);

  /* push viewport */
  gSPViewport(NOW_POLY_OPA_DISP++, vp);
  gSPViewport(NOW_POLY_XLU_DISP++, vp);
  gSPViewport(NOW_SHADOW_DISP++, vp);
  gSPViewport(NOW_LIGHT_DISP++, vp);
  gSPViewport(NOW_OVERLAY_DISP++, vp);
  gSPViewport(NOW_BG_OPA_DISP++, vp);
  gSPViewport(NOW_BG_XLU_DISP++, vp);

  /* update orthographic proj matrix */
  mtx = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);
  view->p_projection = mtx;

  guOrtho(
    mtx,
    -(f32)ScreenWidth / 2.0f, (f32)ScreenWidth / 2.0f,
    -(f32)ScreenHeight / 2.0f, (f32)ScreenHeight / 2.0f,
    view->near,
    view->far,
    view->scale
  );

  view->mtx_projection = *mtx;

  gSPMatrix(NOW_POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  gSPMatrix(NOW_POLY_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  gSPMatrix(NOW_SHADOW_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  gSPMatrix(NOW_LIGHT_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  gSPMatrix(NOW_BG_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  gSPMatrix(NOW_BG_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

  CLOSE_DISP(g);

  return TRUE;
}

extern int showView1(View* view, int flag_mask, Gfx** gfx_p) {
  Gfx* gfx;
  GRAPH* g;
  int flags;

  gfx = *gfx_p;
  flag_mask = (flag_mask >> 4) | (flag_mask & view->flag);
  g = view->graph;
    
  OPEN_DISP(g);

  if (flag_mask & VIEW_UPDATE_SCISSOR) {
    Gfx* gfx_save;
    Vp* vp = GRAPH_ALLOC_TYPE(g, Vp, 1);
    set_viewport(vp, &view->screen);
    view->viewport = *vp;
    
    gDPPipeSync(gfx++);
    gfx_save = gfx;
    setScissorX(&gfx_save, view->screen.l, view->screen.top, view->screen.r, view->screen.bottom);
    gfx = gfx_save;
    gSPViewport(gfx++, vp);
  }
  
  if (flag_mask & VIEW_UPDATE_ORTHOGRAPHIC) {
    N64Mtx* m = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);

    view->p_projection = m;
    guOrtho(
      m,
      -(f32)ScreenWidth / 2.0f, (f32)ScreenWidth / 2.0f,
      -(f32)ScreenHeight / 2.0f, (f32)ScreenHeight / 2.0f,
      view->near,
      view->far,
      view->scale
    );

    view->mtx_projection = *m;
    gSPMatrix(gfx++, m, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
  }
  else if (flag_mask & (VIEW_UPDATE_SCISSOR | VIEW_UPDATE_PERSPECTIVE)) {
    N64Mtx* m = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);

    view->p_projection = m;
    guPerspective(
      m,
      &view->normal,
      view->fovY,
      (f32)(view->screen.r - view->screen.l) / (f32)(view->screen.bottom - view->screen.top),
      view->near, view->far,
      view->scale
    );

    view->mtx_projection = *m;
    gSPPerspNormalize(gfx++, view->normal);
    gSPMatrix(gfx++, m, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
  }

  if (flag_mask & VIEW_UPDATE_LOOKAT) {
    N64Mtx* m = GRAPH_ALLOC_TYPE(g, N64Mtx, 1);

    view->p_viewing = m;
    guLookAt(
      m,
      view->eye.x, view->eye.y, view->eye.z,
      view->center.x, view->center.y, view->center.z,
      view->up.x, view->up.y, view->up.z
    );
    
    view->mtx_viewing = *m;
    gSPMatrix(gfx++, m, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
  }

  CLOSE_DISP(g);

  view->flag = VIEW_UPDATE_NONE;
  *gfx_p = gfx;

  return TRUE;
}
