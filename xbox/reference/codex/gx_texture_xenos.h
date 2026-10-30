#ifndef AC_GX_TEXTURE_XENOS_H
#define AC_GX_TEXTURE_XENOS_H
#include "gx_texture_binding.h"
#include "material_program.h"
struct XenosDevice;
/* GPU calls/draws using these textures must stay inside the managed frame.
 * Initializes real SDK fence; cache owns <=32 native surfaces, no raw asset refs.
 * Collect only outside a frame; it unbinds/destroys completed surfaces. */
int ac_gx_xenos_setup(struct XenosDevice *);
int ac_gx_xenos_apply(unsigned int stage,unsigned char *workspace,size_t,const ACMaterialProgram *);
int ac_gx_xenos_collect(void);
int ac_gx_xenos_shutdown(void);
#endif
