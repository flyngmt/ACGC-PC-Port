#if DEBUG

#include <dolphin/gx.h>

#include "gx/__gx.h"

static struct __GXVerifyData __gxVerifData;
struct __GXVerifyData * __gxVerif = &__gxVerifData;

char *__gxvWarnings[115] = {
    "Invalid Vertex Format. Normal count must be set to %s.",
    "Texture size %ld not initialized.",
    "Left edge of scissor rectangle is less than %d.",
    "Top edge of scissor rectangle is less than %d.",
    "Right edge of scissor rectangle is greater than %d in %s mode.",
    "Bottom edge of scissor rectangle is greater than %d in %s mode.",
    "%s value for subsample %d in pixel %ld is not 6 when single-sampling.",
    "Indirect texture command for stage %ld is not set.",
    "Invalid indirect texture request in TEV stage %ld.",
    "Indirect matrix %ld requested in stage %d not set.",
    "Requested indirect textures never initialized.",
    "Indirect texture coordinate scales %d and %d not set.",
    "Invalid texture coordinate specified for indirect stage %d.",
    "Indirect texture feedback accumulation is on in TEV stage 0.",
    "Indirect bump alpha is enabled in TEV stage 0.",
    "Indirect vs. direct mask byte never set.",
    "Texture reference never written for TEV stage %ld.",
    "Invalid texture coordinate specified for TEV stage %ld.",
    "Texture %ld is used as both indirect and direct.",
    "Texture %ld not configured.",
    "Base pointer for cached texture %ld is not specified.",
    "TLUT for indexed texture %ld was never set up.",
    "%s is not a power of 2 for mipmapped texture %ld.",
    "%s is not GX_CLAMP for non-power-of-2 width in texture %ld.",
    "Minification filter for texture %ld is not compatible with color index texture format.",
    "Minimum LOD is greater than maximum LOD in texture %ld.",
    "Maximum LOD is greater than image's maximum LOD for texture %ld.",
    "LOD bias clamp shold be used with edge LOD for texture %ld.",
    "Texture %ld does not meet requirements for anisotropic mipmapping.",
    "Filters are not linear for field prediction in texture %ld.",
    "Incomplete rounding mode configuration for texture %ld.",
    "Rounding color indexed texture %ld.",
    "Environment for TEV stage %ld not fully set up.",
    "Invalid color channel selected in TEV stage %ld.",
    "Argument %s selects null texture in TEV color stage %ld.",
    "Argument %s selects null texture in TEV alpha stage %ld.",
    "Color arg %s in TEV stage %ld accesses register %s, which may be dirty.",
    "Alpha arg %s in TEV stage %ld accesses register %s, which may be dirty.",
    "Color arg %s in TEV stage %ld accesses register %s, which was last unclamped. Possible wrap-around effect.",
    "Alpha arg %s in TEV stage %ld accesses register %s, which was last unclamped. Possible wrap-around effect.",
    "Z texturing enabled, but no Z offset specified.",
    "Z texturing enabled, but no texture specified for final TEV stage.",
    "Final TEV stage doesn't write color to register GX_TEVPREV.",
    "Final TEV stage doesn't write alpha to register GX_TEVPREV.",
    "Final TEV color stage has no clamping. Possible color wrap-around effect.",
    "Final TEV alpha stage has no clamping. Possible alpha wrap-around effect.",
    "Z buffering is before texture, but alpha compare operation is active.",
    "PE blend and logicop are both on.",
    "Selected pixel format does not support dithering.",
    "Multisample enabled but pixel type is not RGB565.",
    "Pixel type is RGB565 but multisample is not enabled.",
    "Multisample locations for pixel %ld are not ordered correctly for antialias filter.",
    "Invalid texgen_type %d for texture %d.",
    "Register address 0x%04x uninitialized (%s).",
    "Register address 0x%04x modified (%s), probably should not be.",
    "Invalid combination of %d output color channels and %d color texgen textures.",
    "Invalid number of output colors, %d.",
    "Vertex packet does not contain position values.",
    "XF is not expecting host colors but cp is sending some.",
    "XF is expecting a host color but cp is not sending one.",
    "XF is expecting a single host color but cp is sending two.",
    "XF is expecting two host colors but cp is not sending first color.",
    "XF is expecting two host colors but cp is not sending second color.",
    "Invalid value (%d) for INVERTEXSPEC_REG.host_colors.",
    "XF is not expecting host normals but cp is sending them.",
    "XF is not expecting host normals, binormals and tangents but cp is sending them.",
    "XF is expecting host normals but cp is not sending them.",
    "XF is expecting host normals but cp is sending normals, binormals, and tangents.",
    "XF is expecting host normals, binormals and tangents but cp is only sending normals.",
    "XF is expecting host normals, binormals and tangents but cp is not sending them.",
    "Invalid value (%d) for INVERTEXSPEC_REG.host_normal.",
    "XF expecting %d host textures but CP is only sending %d.",
    "GX_TEXCOORD%d specifies source row of position, but this is not getting sent.",
    "GX_TEXCOORD%d specifies source row of normal, but this is not getting sent.",
    "GX_TEXCOORD%d specifies source row of color0, but color0 is not getting sent.",
    "GX_TEXCOORD%d specifies source row of color1, but color1 is not getting sent.",
    "GX_TEXCOORD%d specifies source row of binormal or tangent, but this is not getting sent.",
    "GX_TEXCOORD%d specifies source row of input texture coordinate %d, but this is not getting sent.",
    "GX_TEXCOORD%d is specifying an invalid source row of %d.",
    "TexCoordGen types are out of order. GX_TG_MTX2x4/3x4 should come first (if any), followed by GX_TG_BUMP (if any), then GX_TG_SRTG (if any).",
    "Bumpmap texgen is defined, which requires that binormals and tangents be transformed by a normal matrix, but current matrix index is set to an invalid value (%d) for normal transform.",
    "GX_TEXCOORD%d (texgen type bumpmap) is referencing texture %d as a source texture, which is not of texgen type regular.",
    "GX_TEXCOORD%d (texgen type bumpmap) using light source %d, but light's %c position is not defined.",
    "GX_TEXCOORD%d is defined as texgen type bumpmap, but binormals and tangents are not getting sent.",
    "Invalid regular texture number (%d)",
    "Regular texture %d specifying a source row of %d which only has 2 elements, but an input form of ABC1.",
    "Output XF colors or color textures enabled, but register address 0x%04x uninitialized (%s).",
    "Output XF colors or color textures enabled, COLOR%dCNTRL_REG.material_src == REGISTER, but Material %d register (0x%04x) is not initialized.",
    "Output XF colors or color textures enabled, COLOR%dCNTRL_REG.ambient_src == REGISTER, but Ambient %d register (0x%04x) is not initialized.",
    "Channel %s uses specular function (GX_AF_SPEC), but diffuse function is not GX_DF_NONE.",
    "Channel %d performs lighting which requires a normal, but this is not getting sent.",
    "Channel %d performs lighting which requires the normal to be transformed by a normal matrix, but current matrix index is (%d), which may be invalid.",
    "%s has a value of %sinfinity (%08x), which is probably not intended.",
    "%s has a value of NaN (%08x), which is probably not intended.",
    "%s has a value of (%f 0x%08x), which might be unintentionally small.",
    "%s has a value of (%f 0x%08x), which might be unintentionally large.",
    "%d regular textures active, but MatrixIndex1 register (0x%04x) uninitialized.",
    "gen_mode register not initialized.",
    "Number of XF output textures does not match what downstream units are expecting.",
    "Number of XF output colors does not match what downstream units are expecting.",
    "Number of all texgens (%d) > max allowed %d.",
    "Number of regular(2x4/3x4) type texgens (%d) > max allowed %d.",
    "Number of bumpmap type texgens (%d) > max allowed %d.",
    "Number of color texgens (%d) > max allowed %d.",
    "First color texgen is not referencing COLOR0.",
    "Color texgen from COLOR%d is used more than once.",
    "Bumpmap texgen is defined, which requires the normal matrix values pointed by current matrix index (%d) to be loaded, however it may not be loaded yet.",
    "GX_TEXCOORD%d requires the matrix values pointed by current texture matrix index %d (%d), however it may not be loaded yet.",
    "GX_LIGHT%d is being referenced, however it may not be loaded yet.",
    "Channel %d performs lighting which requires the normal matrix values pointed to by the current matrix index (%d), however these values may not be loaded yet.",
    "Position matrix values pointed to by the current matrix index must be loaded, however they may not be loaded yet.",
    "Address 0x%04x is uninitialized.",
    "Register (0x%04x) (%s) is not initialized.",
    "Display list contains invalid command.",
    "Nested display list.",
};

#define GX_WARN_4 4 // not in GX_WARN_*

GXWarningLevel __gxvWarnLev[115] = {
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_4,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_ALL,
    GX_WARN_ALL,
    GX_WARN_4,
    GX_WARN_SEVERE,
    GX_WARN_MEDIUM,
    GX_WARN_MEDIUM,
    GX_WARN_ALL,
    GX_WARN_ALL,
    GX_WARN_MEDIUM,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_ALL,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_4,
    GX_WARN_SEVERE,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_4,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_MEDIUM,
    GX_WARN_MEDIUM,
    GX_WARN_MEDIUM,
    GX_WARN_ALL,
    GX_WARN_ALL,
    GX_WARN_SEVERE,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_4,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
    GX_WARN_MEDIUM,
    GX_WARN_MEDIUM,
    GX_WARN_MEDIUM,
    GX_WARN_MEDIUM,
    GX_WARN_MEDIUM,
    GX_WARN_MEDIUM,
    GX_WARN_MEDIUM,
    GX_WARN_SEVERE,
    GX_WARN_SEVERE,
};

char __gxvDummyStr[256];

static void __GXVerifyGlobal(void)
{
}

static void __GXVerifyCP(GXVtxFmt fmt)
{
    u32 nrmCnt = GET_REG_FIELD(gx->vatA[fmt], 1, 9);
    
    if (__gxVerif->verifyLevel >= GX_WARN_SEVERE) {
        if (gx->hasNrms && nrmCnt != 0) {
            if (__gxVerif->verifyLevel >= __gxvWarnLev[0]) {
                sprintf(__gxvDummyStr, __gxvWarnings[0], "GX_NRM_XYZ");
                __gxVerif->cb(__gxvWarnLev[0], 0, __gxvDummyStr);
            }
        }
        else if (gx->hasBiNrms && nrmCnt != 1) {
            if (__gxVerif->verifyLevel >= __gxvWarnLev[0]) {
                sprintf(__gxvDummyStr, __gxvWarnings[0], "GX_NRM_NBT or GX_NRM_NBT3");
                __gxVerif->cb(__gxvWarnLev[0], 0, __gxvDummyStr);
            }
        }
    }
}

void __GXVerifyState(GXVtxFmt vtxfmt)
{
    if (__gxVerif->verifyLevel != GX_WARN_NONE) {
        __GXVerifyGlobal();
        __GXVerifyCP(vtxfmt);
        __GXVerifyXF();
        __GXVerifySU();
        __GXVerifyBUMP();
        __GXVerifyTEX();
        __GXVerifyTEV();
        __GXVerifyPE();
    }
}

void GXSetVerifyLevel(GXWarningLevel level)
{
    __gxVerif->verifyLevel = level;
}

GXVerifyCallback GXSetVerifyCallback(GXVerifyCallback cb)
{
    GXVerifyCallback old_cb = __gxVerif->cb;
    
    __gxVerif->cb = cb;
    return old_cb;
}

#endif  // DEBUG
