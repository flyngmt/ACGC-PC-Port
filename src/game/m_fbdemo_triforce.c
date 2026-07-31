#include "m_fbdemo_triforce.h"

#include "dataobject.h"
#include "gfxalloc.h"
#include "libultra/gu.h"
#include "libultra/libultra.h"
#include "m_rcp.h"

void fbdemo_triforce_startup(fbdemo_triforce* this) {
  this->finished = 0;

  if (this->direction != 0) {
    this->txt = 0;
  } else {
    this->txt = 0x224;
  }

  guPerspective(&this->perspmtx, &this->normal, 60.0f, 4.0f / 3.0f, 10.0f,
                12800.0f, 1.0f);
  guLookAt(&this->lookatmtx, 0.0f, 0.0f, 400.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
           0.0f);
}

fbdemo_triforce* fbdemo_triforce_init(fbdemo_triforce* this) {
  bzero(this, sizeof(fbdemo_triforce));
  return this;
}

void fbdemo_triforce_move(fbdemo_triforce* this, int updaterate) {
  static f32 triforce_accum = 0.0f;
  f32 d;
  f32 t = (1.0f - (this->txt / 548.0f));
  f32 dt = (f32)gamePT->graph->dt_num_60fps_frames;
  if ((this->textureno == 1) || (this->textureno == 2)) {
    d = 0.5f * (14.0f + (12.0f * t));
  } else {
    d = 0.5f * (16.0f + (12.0f * t));
  }

  if (this->direction != 0) {
    triforce_accum += d * dt;
    int steps = (int)triforce_accum;
    triforce_accum -= (f32)steps;
    this->txt += steps;
    if (this->txt >= 548) {
      this->txt = 548;
      this->finished = TRUE;
    }
  } else {
    triforce_accum += d * dt;
    int steps = (int)triforce_accum;
    triforce_accum -= (f32)steps;
    this->txt -= steps;
    if (this->txt <= 0) {
      this->txt = 0;
      this->finished = TRUE;
    }
  }
}

void fbdemo_triforce_draw(fbdemo_triforce* this, Gfx** gfxP) {
  Gfx* gfx = *gfxP;
  Gfx* t;
  Gfx* scroll;

  gDPPipeSync(gfx++);
  scroll = gfx_tex_scroll2(&gfx, this->txt, 0, 16, 4);
  gSPSegment(gfx++, 0x9, scroll);
#ifdef TARGET_PC
  /* Copy matrices into gfxalloc buffers so their addresses come from the DL
     buffer (above 0x10000000) instead of the heap (which can collide with
     N64 segment range 0x03-0x0F, causing seg2k0 misidentification). */
  {
    N64Mtx* persp_copy = (N64Mtx*)gfxalloc(&gfx, sizeof(N64Mtx));
    N64Mtx* lookat_copy = (N64Mtx*)gfxalloc(&gfx, sizeof(N64Mtx));
    *persp_copy = this->perspmtx;
    *lookat_copy = this->lookatmtx;
    gSPMatrix(gfx++, persp_copy, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNormalize(gfx++, this->normal);
    gSPMatrix(gfx++, lookat_copy, G_MTX_MUL | G_MTX_PROJECTION);
  }
#else
  gSPMatrix(gfx++, &this->perspmtx,
            G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
  gSPPerspNormalize(gfx++, this->normal);
  gSPMatrix(gfx++, &this->lookatmtx, G_MTX_MUL | G_MTX_PROJECTION);
#endif
  t = gfxalloc(&gfx, 0x40);
  guScale((N64Mtx*)t, 0.019f, 0.019f, 1.0f);

  gSPMatrix(gfx++, t, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

  switch (this->textureno) {
    case 0:
      gSPDisplayList(gfx++, ef_wipe1_modelT);
      break;
    case 1:
      gSPDisplayList(gfx++, ef_wipe2_modelT);
      break;
    case 2:
      gSPDisplayList(gfx++, ef_wipe3_modelT);
      break;
  }
  gDPPipeSync(gfx++);
  *gfxP = gfx;
}

s8 fbdemo_triforce_is_finish(fbdemo_triforce* this) { return this->finished; }

void fbdemo_triforce_settype(fbdemo_triforce* this, int type) {
  this->textureno = ((type & 0x80) != 0) ? 1 : ((type & 0x40) != 0 ? 2 : 0);
  this->direction = (type & 0xF) != 1;
}

void fbdemo_triforce_setcolor_rgba8888(void) {}
