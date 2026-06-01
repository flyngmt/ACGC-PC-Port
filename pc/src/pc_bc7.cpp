#include "pc_bc7.h"
#include "../lib/bc7decomp.h"

extern "C" void pc_bc7_decomp_block(const unsigned char* block_bytes, unsigned char* rgba_4x4) {
    bc7decomp::color_rgba pixels[16];
    bc7decomp::unpack_bc7(block_bytes, pixels);
    for (int i = 0; i < 16; i++) {
        rgba_4x4[i*4+0] = pixels[i].r;
        rgba_4x4[i*4+1] = pixels[i].g;
        rgba_4x4[i*4+2] = pixels[i].b;
        rgba_4x4[i*4+3] = pixels[i].a;
    }
}