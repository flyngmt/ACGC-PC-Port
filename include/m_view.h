#ifndef M_VIEW_H
#define M_VIEW_H

#include "types.h"
#include "libu64/u64types.h"
#include "m_olib.h"
#include "graph.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VIEW_UPDATE_NONE 0
#define VIEW_UPDATE_LOOKAT (1 << 0) // 1
#define VIEW_UPDATE_SCISSOR (1 << 1) // 2
#define VIEW_UPDATE_PERSPECTIVE (1 << 2) // 4
#define VIEW_UPDATE_ORTHOGRAPHIC (1 << 3) // 8
#define VIEW_UPDATE_ALL (VIEW_UPDATE_LOOKAT | VIEW_UPDATE_SCISSOR | VIEW_UPDATE_PERSPECTIVE | VIEW_UPDATE_ORTHOGRAPHIC) // 15

/* sizeof(struct view_s) == 0x120 */
typedef struct view_s {
  GRAPH* graph;
  
  rect screen;
  f32 fovY;
  f32 near, far;
  f32 scale;
  xyz_t eye;
  xyz_t center;
  xyz_t up;

  Vp viewport;

  N64Mtx mtx_projection;
  N64Mtx mtx_viewing;
  N64Mtx* p_projection;
  N64Mtx* p_viewing;

  struct stretch_s {
    xyz_t target_rotate;
    xyz_t target_scale;
    f32 step; /* step speed between rotate/scale -> target_rotation/target_scale */
    xyz_t rotate;
    xyz_t scale;
  } stretch;

  u16 normal;
  int flag;
  int _unused_pad0;
} View;

extern void initView(View* view, GRAPH* graph);
extern void setLookAtView(View* view, xyz_t* eye, xyz_t* center, xyz_t* up);
extern void setScaleView(View* view, f32 scale);
extern void setPerspectiveView(View* view, f32 fovY, f32 near, f32 far);
extern void setScissorView(View* view, rect* screen);
extern int stretchViewInit(View* view);
extern int showView(View* view, int flags);
extern int showPerspectiveView(View* view);
extern int showOrthoView(View* view);
extern int showView1(View* view, int flag_mask, Gfx** gfx_p);

#ifdef __cplusplus
}
#endif

#endif
