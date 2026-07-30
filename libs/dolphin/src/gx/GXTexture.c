#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "gx/__gx.h"

// GXTexObj internal data
typedef struct __GXTexObjInt_struct {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void *userData;
    GXTexFmt fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} __GXTexObjInt;

// GXTexRegion internal data
typedef struct __GXTexRegionInt_struct {
    u32 image1;
    u32 image2;
    u16 sizeEven;
    u16 sizeOdd;
    u8 is32bMipmap;
    u8 isCached;
} __GXTexRegionInt;

// GXTlutObj internal data
typedef struct __GXTlutObjInt_struct {
    u32 tlut;
    u32 loadTlut0;
    u16 numEntries;
} __GXTlutObjInt;

// GXTlutRegion internal data
typedef struct __GXTlutRegionInt_struct {
    u32 loadTlut1;
    __GXTlutObjInt tlutObj;
} __GXTlutRegionInt;

u8 GXTexMode0Ids[8] = { 0x80, 0x81, 0x82, 0x83, 0xA0, 0xA1, 0xA2, 0xA3 };
u8 GXTexMode1Ids[8] = { 0x84, 0x85, 0x86, 0x87, 0xA4, 0xA5, 0xA6, 0xA7 };
u8 GXTexImage0Ids[8] = { 0x88, 0x89, 0x8A, 0x8B, 0xA8, 0xA9, 0xAA, 0xAB };
u8 GXTexImage1Ids[8] = { 0x8C, 0x8D, 0x8E, 0x8F, 0xAC, 0xAD, 0xAE, 0xAF };
u8 GXTexImage2Ids[8] = { 0x90, 0x91, 0x92, 0x93, 0xB0, 0xB1, 0xB2, 0xB3 };
u8 GXTexImage3Ids[8] = { 0x94, 0x95, 0x96, 0x97, 0xB4, 0xB5, 0xB6, 0xB7 };
u8 GXTexTlutIds[8] = { 0x98, 0x99, 0x9A, 0x9B, 0xB8, 0xB9, 0xBA, 0xBB };
static u8 GX2HWFiltConv[6] = { 0x00, 0x04, 0x01, 0x05, 0x02, 0x06 };
static u8 HW2GXFiltConv[8] = { 0x00, 0x02, 0x04, 0x00, 0x01, 0x03, 0x05, 0x00 };

static void __GXGetTexTileShift(GXTexFmt fmt, u32 *rowTileS, u32 *colTileS)
{
    switch (fmt) {
    case GX_TF_I4:
    case 0x8:
    case GX_TF_CMPR:
    case GX_CTF_R4:
    case GX_CTF_Z4:
        *rowTileS = 3;
        *colTileS = 3;
        break;
    case GX_TF_I8:
    case GX_TF_IA4:
    case 0x9:
    case GX_TF_Z8:
    case GX_CTF_RA4:
    case GX_TF_A8:
    case GX_CTF_R8:
    case GX_CTF_G8:
    case GX_CTF_B8:
    case GX_CTF_Z8M:
    case GX_CTF_Z8L:
        *rowTileS = 3;
        *colTileS = 2;
        break;
    case GX_TF_IA8:
    case GX_TF_RGB565:
    case GX_TF_RGB5A3:
    case GX_TF_RGBA8:
    case 0xA:
    case GX_TF_Z16:
    case GX_TF_Z24X8:
    case GX_CTF_RA8:
    case GX_CTF_RG8:
    case GX_CTF_GB8:
    case GX_CTF_Z16L:
        *rowTileS = 2;
        *colTileS = 2;
        break;
    default:
        *rowTileS = *colTileS = 0;
        ASSERTMSGLINEV(0x19B, 0, "%s: invalid texture format", "GX");
        break;
    }
}

u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod)
{
    u32 tileShiftX;
    u32 tileShiftY;
    u32 tileBytes;
    u32 bufferSize;
    u32 nx;
    u32 ny;
    u32 level;

    ASSERTMSGLINEV(0x1AB, width <= 1024, "%s: width too large", "GXGetTexBufferSize");
    ASSERTMSGLINEV(0x1AC, height <= 1024, "%s: height too large", "GXGetTexBufferSize");

    __GXGetTexTileShift(format, &tileShiftX, &tileShiftY);
    if (format == GX_TF_RGBA8 || format == GX_TF_Z24X8) {
        tileBytes = 64;
    } else {
        tileBytes = 32;
    }
    if (mipmap == 1) {
        nx = 1 << (31 - __cntlzw(width));
        ASSERTMSGLINEV(0x1BE, width == nx, "%s: width must be a power of 2", "GXGetTexBufferSize");
        ny = 1 << (31 - __cntlzw(height));
        ASSERTMSGLINEV(0x1C1, height == ny, "%s: height must be a power of 2", "GXGetTexBufferSize");

        bufferSize = 0;
        for (level = 0; level < max_lod; level++) {
            nx = (width + (1 << tileShiftX) - 1) >> tileShiftX;
            ny = (height + (1 << tileShiftY) - 1) >> tileShiftY;
            bufferSize += tileBytes * (nx * ny);
            if (width == 1 && height == 1) {
                break;
            }
            width = (width > 1) ? width >> 1 : 1;
            height = (height > 1) ? height >> 1 : 1;
        }
    } else {
        nx = (width + (1 << tileShiftX) - 1) >> tileShiftX;
        ny = (height + (1 << tileShiftY) - 1) >> tileShiftY;
        bufferSize = nx * ny * tileBytes;
    }
    return bufferSize;
}

void __GetImageTileCount(enum _GXTexFmt fmt, u16 wd, u16 ht, u32 *rowTiles, u32 *colTiles, u32 *cmpTiles)
{
    u32 texRowShift;
    u32 texColShift;

    __GXGetTexTileShift(fmt, &texRowShift, &texColShift);
    if (wd == 0) {
        wd = 1;
    }
    if (ht == 0) {
        ht = 1;
    }
    *rowTiles = (wd + (1 << texRowShift) - 1) >> texRowShift;
    *colTiles = (ht + (1 << texColShift) - 1) >> texColShift;
    *cmpTiles = (fmt == GX_TF_RGBA8 || fmt == GX_TF_Z24X8) ? 2 : 1;
}

void GXInitTexObj(GXTexObj *obj, void *image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap)
{
    u32 imageBase;
    u32 maxLOD;
    u16 rowT;
    u16 colT;
    u32 rowC;
    u32 colC;
    __GXTexObjInt *t = (__GXTexObjInt *)obj;

    ASSERTMSGLINE(0x214, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x216, "GXInitTexObj");
    ASSERTMSGLINEV(0x217, width <= 1024, "%s: width too large", "GXInitTexObj");
    ASSERTMSGLINEV(0x218, height <= 1024, "%s: height too large", "GXInitTexObj");
    ASSERTMSGLINEV(0x21A, !(format & 0x20), "%s: invalid texture format", "GXInitTexObj");
#if DEBUG
    if (wrap_s != GX_CLAMP || mipmap != 0) {
        u32 mask = 1 << (31 - __cntlzw(width));
        ASSERTMSGLINEV(0x224, width == mask, "%s: width must be a power of 2", "GXInitTexObj");
    }
    if (wrap_t != GX_CLAMP || mipmap != 0) {
        u32 mask = 1 << (31 - __cntlzw(height));
        ASSERTMSGLINEV(0x229, height == mask, "%s: height must be a power of 2", "GXInitTexObj");
    }
#endif
    memset(t, 0, 0x20);
    SET_REG_FIELD(0x237, t->mode0, 2, 0, wrap_s);
    SET_REG_FIELD(0x238, t->mode0, 2, 2, wrap_t);
    SET_REG_FIELD(0x239, t->mode0, 1, 4, 1);
    if (mipmap != 0) {
        u8 lmax;
        t->flags |= 1;
        if (format == 8 || format == 9 || format == 10) {
            t->mode0 = (t->mode0 & 0xFFFFFF1F) | 0xA0;
        } else {
            t->mode0 = (t->mode0 & 0xFFFFFF1F) | 0xC0;
        }

        if (width > height) {
            maxLOD = 31 - __cntlzw(width);
        } else {
            maxLOD = 31 - __cntlzw(height);
        }

        lmax = 16.0f * maxLOD;
        SET_REG_FIELD(0x257, t->mode1, 8, 8, lmax);
    } else {
        t->mode0 = (t->mode0 & 0xFFFFFF1F) | 0x80;
    }
    t->fmt = format;
    SET_REG_FIELD(0x265, t->image0, 10, 0, width - 1);
    SET_REG_FIELD(0x266, t->image0, 10, 10, height - 1);
    SET_REG_FIELD(0x267, t->image0, 4, 20, format & 0xF);
    ASSERTMSGLINEV(0x26D, ((u32)image_ptr & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexObj", "image");
    imageBase = (u32)((u32)image_ptr >> 5) & 0x01FFFFFF;
    SET_REG_FIELD(0x26F, t->image3, 21, 0, imageBase);
    switch (format & 0xF) {
    case 0:
    case 8:
        t->loadFmt = 1;
        rowT = 3;
        colT = 3;
        break;
    case 1:
    case 2:
    case 9:
        t->loadFmt = 2;
        rowT = 3;
        colT = 2;
        break;
    case 3:
    case 4:
    case 5:
    case 10:
        t->loadFmt = 2;
        rowT = 2;
        colT = 2;
        break;
    case 6:
        t->loadFmt = 3;
        rowT = 2;
        colT = 2;
        break;
    case 14:
        t->loadFmt = 0;
        rowT = 3;
        colT = 3;
        break;
    default:
        ASSERTMSGLINEV(0x29A, 0, "%s: invalid texture format", "GXPreLoadEntireTexture");
        t->loadFmt = 2;
        rowT = 2;
        colT = 2;
        break;
    }
    rowC = (width + (1 << rowT) - 1) >> rowT;
    colC = (height + (1 << colT) - 1) >> colT;
    t->loadCnt = (rowC * colC) & 0x7FFF;
    t->flags |= 2;
}

void GXInitTexObjCI(GXTexObj *obj, void *image_ptr, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap, u32 tlut_name)
{
    __GXTexObjInt *t = (__GXTexObjInt *)obj;

    ASSERTMSGLINE(0x2C0, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x2C2, "GXInitTexObjCI");
    GXInitTexObj(obj, image_ptr, width, height, format, wrap_s, wrap_t, mipmap);
    t->flags &= 0xFFFFFFFD;
    t->tlutName = tlut_name;
}

void GXInitTexObjLOD(GXTexObj *obj, GXTexFilter min_filt, GXTexFilter mag_filt, f32 min_lod, f32 max_lod, f32 lod_bias, u8 bias_clamp, u8 do_edge_lod, GXAnisotropy max_aniso)
{
    u8 lbias;
    u8 lmin;
    u8 lmax;
    __GXTexObjInt *t = (__GXTexObjInt *)obj;

    ASSERTMSGLINE(0x2E7, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x2E9, "GXInitTexObjLOD");

    if (lod_bias < -4.0f) {
        lod_bias = -4.0f;
    } else if (lod_bias >= 4.0f) {
        lod_bias = 3.99f;
    }
    lbias = 32.0f * lod_bias;
    SET_REG_FIELD(0x2F3, t->mode0, 8, 9, lbias);
    SET_REG_FIELD(0x2F4, t->mode0, 1, 4, (mag_filt == GX_LINEAR) ? 1 : 0);
    ASSERTMSGLINE(0x2F6, (u32)min_filt <= 5, "GXInitTexObjLOD: invalid min_filt value");
    SET_REG_FIELD(0x2F7, t->mode0, 3, 5, GX2HWFiltConv[min_filt]);
    SET_REG_FIELD(0x2F8, t->mode0, 1, 8, do_edge_lod ? 0 : 1);
    t->mode0 &= 0xFFFDFFFF;
    t->mode0 &= 0xFFFBFFFF;
    SET_REG_FIELD(0x2FB, t->mode0, 2, 19, max_aniso);
    SET_REG_FIELD(0x2FC, t->mode0, 1, 21, bias_clamp);
    if (min_lod < 0.0f) {
        min_lod = 0.0f;
    } else if (min_lod > 10.0f) {
        min_lod = 10.0f;
    }
    lmin = 16.0f * min_lod;
    if (max_lod < 0.0f) {
        max_lod = 0.0f;
    } else if (max_lod > 10.0f) {
        max_lod = 10.0f;
    }
    lmax = 16.0f * max_lod;
    SET_REG_FIELD(0x30A, t->mode1, 8, 0, lmin);
    SET_REG_FIELD(0x30B, t->mode1, 8, 8, lmax);
}

void GXInitTexObjData(GXTexObj *obj, void *image_ptr)
{
    u32 imageBase;
    __GXTexObjInt *t = (__GXTexObjInt *)obj;

    ASSERTMSGLINE(0x31E, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x320, "GXInitTexObjData");
    ASSERTMSGLINEV(0x323, ((u32)image_ptr & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexObjData", "image");
    imageBase = ((u32)image_ptr >> 5) & 0x01FFFFFF;
    SET_REG_FIELD(0x326, t->image3, 21, 0, imageBase);
}

void GXInitTexObjWrapMode(GXTexObj *obj, GXTexWrapMode sm, GXTexWrapMode tm)
{
    __GXTexObjInt *t = (__GXTexObjInt *)obj;

    ASSERTMSGLINE(0x338, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x33A, "GXInitTexObjWrapMode");
    SET_REG_FIELD(0x33C, t->mode0, 2, 0, sm);
    SET_REG_FIELD(0x33D, t->mode0, 2, 2, tm);
}

void GXInitTexObjTlut(GXTexObj *obj, u32 tlut_name)
{
    __GXTexObjInt *t = (__GXTexObjInt *)obj;

    ASSERTMSGLINE(0x34E, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x350, "GXInitTexObjTlut");
    t->tlutName = tlut_name;
}

void GXInitTexObjUserData(GXTexObj *obj, void *user_data)
{
    __GXTexObjInt *t = (__GXTexObjInt *)obj;

    ASSERTMSGLINE(0x363, obj, "Texture Object Pointer is null");
    CHECK_GXBEGIN(0x364, "GXInitTexObjUserData");
    t->userData = user_data;
}

void *GXGetTexObjUserData(const GXTexObj *obj)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)obj;

    ASSERTMSGLINE(0x36A, obj, "Texture Object Pointer is null");
    return t->userData;
}

void GXGetTexObjAll(const GXTexObj *obj, void **image_ptr, u16 *width, u16 *height, GXTexFmt *format, GXTexWrapMode *wrap_s, GXTexWrapMode *wrap_t, u8 *mipmap)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)obj;

    ASSERTMSGLINE(0x37E, obj, "Texture Object Pointer is null");
    *image_ptr = (void *)(GET_REG_FIELD(t->image3, 21, 0) << 5);
    *width = (u32)GET_REG_FIELD(t->image0, 10, 0) + 1;
    *height = (u32)GET_REG_FIELD(t->image0, 10, 10) + 1;
    *format = t->fmt;
    *wrap_s = GET_REG_FIELD(t->mode0, 2, 0);
    *wrap_t = GET_REG_FIELD(t->mode0, 2, 2);
    *mipmap = (t->flags & 1) == 1;
}

void *GXGetTexObjData(const GXTexObj *to)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)to;

    ASSERTMSGLINE(0x38B, to, "Texture Object Pointer is null");
    return (void *)(GET_REG_FIELD(t->image3, 21, 0) << 5);
}

u16 GXGetTexObjWidth(const GXTexObj *to)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)to;

    ASSERTMSGLINE(0x391, to, "Texture Object Pointer is null");
    return (u32)GET_REG_FIELD(t->image0, 10, 0) + 1;
}

u16 GXGetTexObjHeight(const GXTexObj *to)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)to;

    ASSERTMSGLINE(0x397, to, "Texture Object Pointer is null");
    return (u32)GET_REG_FIELD(t->image0, 10, 10) + 1;
}

GXTexFmt GXGetTexObjFmt(const GXTexObj *to)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)to;

    ASSERTMSGLINE(0x39D, to, "Texture Object Pointer is null");
    return t->fmt;
}

GXTexWrapMode GXGetTexObjWrapS(const GXTexObj *to)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)to;

    ASSERTMSGLINE(0x3A3, to, "Texture Object Pointer is null");
    return GET_REG_FIELD(t->mode0, 2, 0);
}

GXTexWrapMode GXGetTexObjWrapT(const GXTexObj *to)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)to;

    ASSERTMSGLINE(0x3A9, to, "Texture Object Pointer is null");
    return GET_REG_FIELD(t->mode0, 2, 2);
}

GXBool GXGetTexObjMipMap(const GXTexObj *to)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)to;

    ASSERTMSGLINE(0x3AF, to, "Texture Object Pointer is null");
    return (t->flags & 1) == 1;
}

void GXGetTexObjLODAll(const GXTexObj *tex_obj, GXTexFilter *min_filt, GXTexFilter *mag_filt, f32 *min_lod, f32 *max_lod, f32 *lod_bias, u8 *bias_clamp, u8 *do_edge_lod, GXAnisotropy *max_aniso)
{
    s16 tmp;
    const __GXTexObjInt *t = (const __GXTexObjInt *)tex_obj;

    ASSERTMSGLINE(0x3C5, tex_obj, "Texture Object Pointer is null");
    *min_filt = HW2GXFiltConv[GET_REG_FIELD(t->mode0, 3, 5)];
    *mag_filt = GET_REG_FIELD(t->mode0, 1, 4);
    *min_lod = (u8)t->mode1 / 16.0f;
    *max_lod = (u32)GET_REG_FIELD(t->mode1, 8, 8) / 16.0f;
    tmp = (s32)GET_REG_FIELD(t->mode0, 8, 9);
    if (tmp & 0x80) {
        tmp = -(tmp & 0x7F);
    }
    *lod_bias = 32.0f * tmp;
    *bias_clamp = (u32)GET_REG_FIELD(t->mode0, 1, 21);
    *do_edge_lod = !GET_REG_FIELD(t->mode0, 1, 8);
    *max_aniso = GET_REG_FIELD(t->mode0, 2, 19);
}

GXTexFilter GXGetTexObjMinFilt(const GXTexObj *tex_obj)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)tex_obj;

    ASSERTMSGLINE(0x3D7, tex_obj, "Texture Object Pointer is null");
    return HW2GXFiltConv[GET_REG_FIELD(t->mode0, 3, 5)];
}

GXTexFilter GXGetTexObjMagFilt(const GXTexObj *tex_obj)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)tex_obj;

    ASSERTMSGLINE(0x3DE, tex_obj, "Texture Object Pointer is null");
    return GET_REG_FIELD(t->mode0, 1, 4);
}

f32 GXGetTexObjMinLOD(const GXTexObj *tex_obj)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)tex_obj;

    ASSERTMSGLINE(0x3E4, tex_obj, "Texture Object Pointer is null");
    return (u32)GET_REG_FIELD(t->mode1, 8, 0) / 16.0f;
}

f32 GXGetTexObjMaxLOD(const GXTexObj *tex_obj)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)tex_obj;

    ASSERTMSGLINE(0x3EA, tex_obj, "Texture Object Pointer is null");
    return (u32)GET_REG_FIELD(t->mode1, 8, 8) / 16.0f;
}

f32 GXGetTexObjLODBias(const GXTexObj *tex_obj)
{
    s16 tmp;
    const __GXTexObjInt *t = (const __GXTexObjInt *)tex_obj;

    ASSERTMSGLINE(0x3F1, tex_obj, "Texture Object Pointer is null");
    tmp = (s32)GET_REG_FIELD(t->mode0, 8, 9);
    if (tmp & 0x80) {
        tmp = -(tmp & 0x7F);
    }
    return 32.0f * tmp;
}

GXBool GXGetTexObjBiasClamp(const GXTexObj *tex_obj)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)tex_obj;

    ASSERTMSGLINE(0x3FA, tex_obj, "Texture Object Pointer is null");
    return (u32)GET_REG_FIELD(t->mode0, 1, 21);
}

GXBool GXGetTexObjEdgeLOD(const GXTexObj *tex_obj)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)tex_obj;

    ASSERTMSGLINE(0x400, tex_obj, "Texture Object Pointer is null");
    return !GET_REG_FIELD(t->mode0, 1, 8);
}

GXAnisotropy GXGetTexObjMaxAniso(const GXTexObj *tex_obj)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)tex_obj;

    ASSERTMSGLINE(0x406, tex_obj, "Texture Object Pointer is null");
    return GET_REG_FIELD(t->mode0, 2, 19);
}

u32 GXGetTexObjTlut(const GXTexObj *tex_obj)
{
    const __GXTexObjInt *t = (const __GXTexObjInt *)tex_obj;

    ASSERTMSGLINE(0x40C, tex_obj, "Texture Object Pointer is null");
    return t->tlutName;
}

void GXLoadTexObjPreLoaded(GXTexObj *obj, GXTexRegion *region, GXTexMapID id)
{
    __GXTlutRegionInt *tlr;
    __GXTexObjInt *t = (__GXTexObjInt *)obj;
    __GXTexRegionInt *r = (__GXTexRegionInt *)region;

    ASSERTMSGLINE(0x423, obj, "Texture Object Pointer is null");
    ASSERTMSGLINE(0x423, region, "TexRegion Object Pointer is null");
    CHECK_GXBEGIN(0x425, "GXLoadTexObjPreLoaded");
    ASSERTMSGLINEV(0x426, id < 8, "%s: invalid texture map ID", "GXLoadTexObj");

    SET_REG_FIELD(0x428, t->mode0, 8, 24, GXTexMode0Ids[id]);
    SET_REG_FIELD(0x429, t->mode1, 8, 24, GXTexMode1Ids[id]);
    SET_REG_FIELD(0x42A, t->image0, 8, 24, GXTexImage0Ids[id]);
    SET_REG_FIELD(0x42B, r->image1, 8, 24, GXTexImage1Ids[id]);
    SET_REG_FIELD(0x42C, r->image2, 8, 24, GXTexImage2Ids[id]);
    SET_REG_FIELD(0x42D, t->image3, 8, 24, GXTexImage3Ids[id]);

    GX_WRITE_RAS_REG(t->mode0);
    GX_WRITE_RAS_REG(t->mode1);
    GX_WRITE_RAS_REG(t->image0);
    GX_WRITE_RAS_REG(r->image1);
    GX_WRITE_RAS_REG(r->image2);
    GX_WRITE_RAS_REG(t->image3);

    if (!(t->flags & 2)) {
        ASSERTMSGLINEV(0x438, gx->tlutRegionCallback, "%s: Tex/Tlut Region Callback not set", "GXLoadTexObj/PreLoaded");
        tlr = (__GXTlutRegionInt *)gx->tlutRegionCallback(t->tlutName);
        ASSERTMSGLINEV(0x43A, tlr, "%s: Tex/Tlut Region Callback returns NULL", "GXLoadTexObj/PreLoaded");

        SET_REG_FIELD(0x43C, tlr->tlutObj.tlut, 8, 24, GXTexTlutIds[id]);
        GX_WRITE_RAS_REG(tlr->tlutObj.tlut);
    }
    gx->tImage0[id] = t->image0;
    gx->tMode0[id] = t->mode0;
    gx->dirtyState |= 1;
    gx->bpSentNot = GX_FALSE;
}

void GXLoadTexObj(GXTexObj *obj, GXTexMapID id)
{
    GXTexRegion *r;

    CHECK_GXBEGIN(0x457, "GXLoadTexObj");
    ASSERTMSGLINEV(0x458, id < 8, "%s: invalid texture map ID", "GXLoadTexObj");
    ASSERTMSGLINEV(0x45D, gx->texRegionCallback, "%s: Tex/Tlut Region Callback not set", "GXLoadTexObj");
    r = gx->texRegionCallback(obj, id);
    ASSERTMSGLINEV(0x45F, r, "%s: Tex/Tlut Region Callback returns NULL", "GXLoadTexObj");
    GXLoadTexObjPreLoaded(obj, r, id);
}

void GXInitTlutObj(GXTlutObj *tlut_obj, void *lut, GXTlutFmt fmt, u16 n_entries)
{
    __GXTlutObjInt *t = (__GXTlutObjInt *)tlut_obj;

    ASSERTMSGLINE(0x477, tlut_obj, "TLut Object Pointer is null");
    CHECK_GXBEGIN(0x478, "GXInitTlutObj");
    ASSERTMSGLINEV(0x47B, n_entries <= 0x4000, "%s: number of entries exceeds maximum", "GXInitTlutObj");
    ASSERTMSGLINEV(0x47D, ((u32)lut & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTlutObj", "Tlut");
    t->tlut = 0;
    SET_REG_FIELD(0x480, t->tlut, 2, 10, fmt);
    SET_REG_FIELD(0x481, t->loadTlut0, 21, 0, ((u32)lut & 0x3FFFFFFF) >> 5);
    SET_REG_FIELD(0x482, t->loadTlut0, 8, 24, 0x64);
    t->numEntries = n_entries;
}

void GXGetTlutObjAll(const GXTlutObj *tlut_obj, void **data, GXTlutFmt *format, u16 *numEntries)
{
    const __GXTlutObjInt *t = (const __GXTlutObjInt *)tlut_obj;

    ASSERTMSGLINE(0x497, tlut_obj, "TLut Object Pointer is null");
    *data = (void *)(GET_REG_FIELD(t->loadTlut0, 21, 0) << 5);
    *format = GET_REG_FIELD(t->tlut, 2, 10);
    *numEntries = t->numEntries;
}

void *GXGetTlutObjData(const GXTlutObj *tlut_obj)
{
    const __GXTlutObjInt *t = (const __GXTlutObjInt *)tlut_obj;

    ASSERTMSGLINE(0x4A0, tlut_obj, "TLut Object Pointer is null");
    return (void *)(GET_REG_FIELD(t->loadTlut0, 21, 0) << 5);
}

GXTlutFmt GXGetTlutObjFmt(const GXTlutObj *tlut_obj)
{
    const __GXTlutObjInt *t = (const __GXTlutObjInt *)tlut_obj;

    ASSERTMSGLINE(0x4A7, tlut_obj, "TLut Object Pointer is null");
    return GET_REG_FIELD(t->tlut, 2, 10);
}

u16 GXGetTlutObjNumEntries(const GXTlutObj *tlut_obj)
{
    const __GXTlutObjInt *t = (const __GXTlutObjInt *)tlut_obj;

    ASSERTMSGLINE(0x4AE, tlut_obj, "TLut Object Pointer is null");
    return t->numEntries;
}

void GXLoadTlut(GXTlutObj *tlut_obj, u32 tlut_name)
{
    __GXTlutRegionInt *r;
    u32 tlut_offset;
    __GXTlutObjInt *t = (__GXTlutObjInt *)tlut_obj;

    ASSERTMSGLINE(0x4C9, tlut_obj, "TLut Object Pointer is null");
    CHECK_GXBEGIN(0x4CB, "GXLoadTlut");
    ASSERTMSGLINEV(0x4CC, gx->tlutRegionCallback, "%s: Tex/Tlut Region Callback not set", "GXLoadTlut");
    r = (__GXTlutRegionInt *)gx->tlutRegionCallback(tlut_name);
    ASSERTMSGLINEV(0x4CE, r, "%s: Tex/Tlut Region Callback returns NULL", "GXLoadTlut");
    __GXFlushTextureState();
    GX_WRITE_RAS_REG(t->loadTlut0);
    GX_WRITE_RAS_REG(r->loadTlut1);
    __GXFlushTextureState();
    tlut_offset = r->loadTlut1 & 0x3FF;
    SET_REG_FIELD(0x4DE, t->tlut, 10, 0, tlut_offset);
    r->tlutObj = *t;
}

void GXInitTexCacheRegion(GXTexRegion *region, u8 is_32b_mipmap, u32 tmem_even, GXTexCacheSize size_even, u32 tmem_odd, GXTexCacheSize size_odd)
{
    u32 WidthExp2;
    __GXTexRegionInt *t = (__GXTexRegionInt *)region;

    ASSERTMSGLINE(0x4FD, region, "TexRegion Object Pointer is null");
    CHECK_GXBEGIN(0x4FF, "GXInitTexCacheRegion");
    ASSERTMSGLINEV(0x501, (tmem_even & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexCacheRegion", "tmem even");
    ASSERTMSGLINEV(0x503, (tmem_odd & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexCacheRegion", "tmem odd");
    switch (size_even) {
    case GX_TEXCACHE_32K:
        WidthExp2 = 3;
        break;
    case GX_TEXCACHE_128K:
        WidthExp2 = 4;
        break;
    case GX_TEXCACHE_512K:
        WidthExp2 = 5;
        break;
    default:
        ASSERTMSGLINEV(0x50B, 0, "%s: Invalid %s size", "GXInitTexCacheRegion", "tmem even");
        break;
    }
    t->image1 = 0;
    SET_REG_FIELD(0x510, t->image1, 15, 0, tmem_even >> 5);
    SET_REG_FIELD(0x511, t->image1, 3, 15, WidthExp2);
    SET_REG_FIELD(0x512, t->image1, 3, 18, WidthExp2);
    t->image1 &= 0xFFDFFFFF;
    switch (size_odd) {
    case GX_TEXCACHE_32K:
        WidthExp2 = 3;
        break;
    case GX_TEXCACHE_128K:
        WidthExp2 = 4;
        break;
    case GX_TEXCACHE_512K:
        WidthExp2 = 5;
        break;
    case GX_TEXCACHE_NONE:
        WidthExp2 = 0;
        break;
    default:
        ASSERTMSGLINEV(0x51B, 0, "%s: Invalid %s size", "GXInitTexCacheRegion", "tmem odd");
        break;
    }
    t->image2 = 0;
    SET_REG_FIELD(0X520, t->image2, 15, 0, tmem_odd >> 5);
    SET_REG_FIELD(0x521, t->image2, 3, 15, WidthExp2);
    SET_REG_FIELD(0x522, t->image2, 3, 18, WidthExp2);
    t->is32bMipmap = is_32b_mipmap;
    t->isCached = 1;
}

void GXInitTexPreLoadRegion(GXTexRegion *region, u32 tmem_even, u32 size_even, u32 tmem_odd, u32 size_odd)
{
    __GXTexRegionInt *t = (__GXTexRegionInt *)region;

    ASSERTMSGLINE(0x53F, region, "TexRegion Object Pointer is null");
    CHECK_GXBEGIN(0x541, "GXInitTexPreLoadRegion");
    ASSERTMSGLINEV(0x543, (tmem_even & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexPreLoadRegion", "tmem even");
    ASSERTMSGLINEV(0x545, (tmem_odd & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexPreLoadRegion", "tmem odd");
    ASSERTMSGLINEV(0x547, (size_even & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexPreLoadRegion", "size even");
    ASSERTMSGLINEV(0x549, (size_odd & 0x1F) == 0, "%s: %s pointer not aligned to 32B", "GXInitTexPreLoadRegion", "size odd");

    t->image1 = 0;
    SET_REG_FIELD(0x54D, t->image1, 15, 0, tmem_even >> 5);
    t->image1 &= 0xFFFC7FFF;
    t->image1 &= 0xFFE3FFFF;
    t->image1 = (t->image1 & 0xFFDFFFFF) | 0x200000;

    t->image2 = 0;
    SET_REG_FIELD(0x553, t->image2, 15, 0, tmem_odd >> 5);
    t->image2 &= 0xFFFC7FFF;
    t->image2 &= 0xFFE3FFFF;
    t->is32bMipmap = 0;
    t->isCached = 0;
    t->sizeEven = (u16) (size_even >> 5U);
    t->sizeOdd = (u16) (size_odd >> 5U);
}

void GXGetTexRegionAll(const GXTexRegion *region, u8 *is_cached, u8 *is_32b_mipmap, u32 *tmem_even, u32 *size_even, u32 *tmem_odd, u32 *size_odd)
{
    const __GXTexRegionInt *t = (const __GXTexRegionInt *)region;

    ASSERTMSGLINE(0x572, region, "TexRegion Object Pointer is null");
    *tmem_even = GET_REG_FIELD(t->image1, 15, 0) << 5;
    *tmem_odd = GET_REG_FIELD(t->image2, 15, 0) << 5;
    if (t->isCached) {
        switch (GET_REG_FIELD(t->image1, 3, 15)) {
        case 3:
            *size_even = 0x8000;
            break;
        case 4:
            *size_even = 0x20000;
            break;
        case 5:
            *size_even = 0x80000;
            break;
        default:
            *size_even = 0;
            break;
        }
        switch (GET_REG_FIELD(t->image2, 3, 15)) {
        case 3:
            *size_odd = 0x8000;
            break;
        case 4:
            *size_odd = 0x20000;
            break;
        case 5:
            *size_odd = 0x80000;
            break;
        default:
            *size_odd = 0;
            break;
        }
    } else {
        *size_even = t->sizeEven << 5;
        *size_odd = t->sizeOdd << 5;
    }
    *is_32b_mipmap = t->is32bMipmap;
    *is_cached = t->isCached;
}

void GXInitTlutRegion(GXTlutRegion *region, u32 tmem_addr, GXTlutSize tlut_size)
{
    __GXTlutRegionInt *t = (__GXTlutRegionInt *)region;

    ASSERTMSGLINE(0x5A5, region, "TLutRegion Object Pointer is null");
    CHECK_GXBEGIN(0x5A7, "GXInitTlutRegion");
    ASSERTMSGLINEV(0x5A8, (tmem_addr & 0x1FF) == 0, "%s: tmem pointer is not aligned to 512B", "GXInitTlutRegion");
    ASSERTMSGLINEV(0x5A9, tlut_size <= 0x400, "%s: tlut size exceeds 16K", "GXInitTlutRegion");
    t->loadTlut1 = 0;
    tmem_addr -= 0x80000;
    SET_REG_FIELD(0x5AD, t->loadTlut1, 10, 0, tmem_addr >> 9);
    SET_REG_FIELD(0x5AE, t->loadTlut1, 11, 10, tlut_size);
    SET_REG_FIELD(0x5AF, t->loadTlut1, 8, 24, 0x65);
}

void GXGetTlutRegionAll(const GXTlutRegion *region, u32 *tmem_addr, GXTlutSize *tlut_size)
{
    const __GXTlutRegionInt *t = (const __GXTlutRegionInt *)region;

    ASSERTMSGLINE(0x5C3, region, "TLutRegion Object Pointer is null");
    *tmem_addr = (GET_REG_FIELD(t->loadTlut1, 10, 0) << 9) + 0x80000;
    *tlut_size = GET_REG_FIELD(t->loadTlut1, 11, 10);
}

void GXInvalidateTexRegion(GXTexRegion *region)
{
    s32 wle;
    s32 hle;
    s32 wlo;
    s32 hlo;
    s32 count;
    u32 reg0;
    u32 reg1;
    __GXTexRegionInt *r = (__GXTexRegionInt *)region;

    ASSERTMSGLINE(0x5DA, region, "TexRegion Object Pointer is null");
    CHECK_GXBEGIN(0x5DC, "GXInvalidateTexRegion");

    wle = GET_REG_FIELD(r->image1, 3, 15) - 1;
    hle = GET_REG_FIELD(r->image1, 3, 18) - 1;
    wlo = GET_REG_FIELD(r->image2, 3, 15) - 1;
    hlo = GET_REG_FIELD(r->image2, 3, 18) - 1;
    if (wle < 0) {
        wle = 0;
    }
    if (hle < 0) {
        hle = 0;
    }
    if (wlo < 0) {
        wlo = 0;
    }
    if (hlo < 0) {
        hlo = 0;
    }
    count = wle + hle;
    if (r->is32bMipmap) {
        count = wlo + hlo - 2 + count;
    }
    reg0 = 0;
    SET_REG_FIELD(0x5ED, reg0, 9, 0, GET_REG_FIELD(r->image1, 9, 6));
    SET_REG_FIELD(0x5EE, reg0, 4, 9, count);
    SET_REG_FIELD(0x5EF, reg0, 8, 24, 0x66);
    if (wlo != 0) {
        count = wlo + hlo;
        if (r->is32bMipmap) {
            count = wle + hle - 2 + count;
        }
        reg1 = 0;
        SET_REG_FIELD(0x5F9, reg1, 9, 0, GET_REG_FIELD(r->image2, 9, 6));
        SET_REG_FIELD(0x5FA, reg1, 4, 9, count);
        SET_REG_FIELD(0x5FB, reg1, 8, 24, 0x66);
    }
    __GXFlushTextureState();
    GX_WRITE_RAS_REG(reg0);
    if (wlo != 0) {
        GX_WRITE_RAS_REG(reg1);
    }
    __GXFlushTextureState();

    reg0; reg1; r;  // needed to match
}

void GXInvalidateTexAll(void)
{
    u32 reg0;
    u32 reg1;

    CHECK_GXBEGIN(0x60C, "GXInvalidateTexAll");
    reg0 = 0x66001000;
    reg1 = 0x66001100;
    __GXFlushTextureState();
    GX_WRITE_RAS_REG(reg0);
    GX_WRITE_RAS_REG(reg1);
    __GXFlushTextureState();
}

GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback f)
{
    GXTexRegionCallback oldcb = gx->texRegionCallback;

    gx->texRegionCallback = f;
    return oldcb;
}

GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback f)
{
    GXTlutRegionCallback oldcb = gx->tlutRegionCallback;

    gx->tlutRegionCallback = f;
    return oldcb;
}

void GXPreLoadEntireTexture(GXTexObj *tex_obj, GXTexRegion *region)
{
    u8 isMipMap;
    u8 is32bit; 
    u32 wd;
    u32 ht;
    u32 maxLevelIndex;
    u32 loadImage0;
    u32 loadImage1;
    u32 loadImage2;
    u32 loadImage3;
    u32 base; 
    u32 tmem1; 
    u32 tmem2; 
    u32 tmemAR;
    u32 tmemGB;
    u32 nTiles;
#if DEBUG
    u32 totalOdd; 
    u32 totalEven;
    u32 count; 
#endif
    u32 rowTiles; 
    u32 colTiles; 
    u32 cmpTiles; 
    u32 i;
    __GXTexObjInt *t = (__GXTexObjInt *)tex_obj;
    __GXTexRegionInt *r = (__GXTexRegionInt *)region;

    ASSERTMSGLINE(0x64D, tex_obj, "Texture Object Pointer is null");
    ASSERTMSGLINE(0x64D, region, "TexRegion Object Pointer is null");
    CHECK_GXBEGIN(0x64F, "GXPreLoadEntireTexture");
    isMipMap = (t->flags & 1) == 1;
    is32bit = GET_REG_FIELD(t->image0, 4, 20) == 6;

    loadImage0 = 0;
    SET_REG_FIELD(0, loadImage0, 8, 24, 0x60);
    base = t->image3 & 0x1FFFFF;
    SET_REG_FIELD(0x658, loadImage0, 21, 0, base);

    loadImage1 = 0;
    SET_REG_FIELD(0, loadImage1, 8, 24, 0x61);
    tmem1 = r->image1 & 0x7FFF;
    SET_REG_FIELD(0x65E, loadImage1, 15, 0, tmem1);

    loadImage2 = 0;
    SET_REG_FIELD(0, loadImage2, 8, 24, 0x62);
    tmem2 = r->image2 & 0x7FFF;
    SET_REG_FIELD(0x664, loadImage2, 15, 0, tmem2);

    loadImage3 = 0;
    SET_REG_FIELD(0, loadImage3, 8, 24, 0x63);
    SET_REG_FIELD(0x669, loadImage3, 15, 0, t->loadCnt);
    SET_REG_FIELD(0x66A, loadImage3, 2, 15, t->loadFmt);
    maxLevelIndex = 0;
    nTiles = t->loadCnt;
    if (isMipMap != 0) {
        wd = GET_REG_FIELD(t->image0, 10, 0) + 1;
        ht = GET_REG_FIELD(t->image0, 10, 10) + 1;
        if (wd > ht) {
            maxLevelIndex = (u16)(31 - __cntlzw(wd));
        } else {
            maxLevelIndex = (u16)(31 - __cntlzw(ht));
        }
#if DEBUG
        count = nTiles;
        totalOdd = totalEven = 0;
        for (i = 0; i < maxLevelIndex; i++) {
            if (i & 1) {
                if (count == 0) {
                    count = 1;
                }
                totalOdd += count;
            } else {
                if (count == 0) {
                    count = 1;
                }
                totalEven += count;
            }
            __GetImageTileCount(t->fmt, wd >> (i + 1), ht >> (i + 1), &rowTiles, &colTiles, &cmpTiles);
            count = rowTiles * colTiles;
        }
#endif
    } else {
#if DEBUG
        totalEven = (nTiles == 0) ? 1 : nTiles;
        totalOdd = totalEven;
#endif
    }
#if DEBUG
    if (is32bit) {
        totalOdd = isMipMap ? totalOdd : 0;
        totalEven = totalEven + totalOdd;
        ASSERTMSGLINE(0x693, totalEven <= r->sizeEven, "GXPreLoadEntireTexture: Even tmem size does not match the texture size");
        ASSERTMSGLINE(0x694, totalEven <= r->sizeOdd, "GXPreLoadEntireTexture: Odd tmem size does not match the texture size");
    } else if (isMipMap != 0) {
        if (r->sizeEven > r->sizeOdd) {
            ASSERTMSGLINE(0x699, totalEven <= r->sizeEven, "GXPreLoadEntireTexture: Even tmem size does not match the texture size");
            ASSERTMSGLINE(0x69A, totalOdd <= r->sizeOdd, "GXPreLoadEntireTexture: Odd tmem size does not match the texture size");
        } else {
            ASSERTMSGLINE(0x69D, totalEven <= r->sizeOdd, "GXPreLoadEntireTexture: Odd tmem size does not match the texture size");
            ASSERTMSGLINE(0x69E, totalOdd <= r->sizeEven, "GXPreLoadEntireTexture: Even tmem size does not match the texture size");
        }
    } else if (r->sizeEven > r->sizeOdd) {
        ASSERTMSGLINE(0x6A3, totalEven <= r->sizeEven, "GXPreLoadEntireTexture: Even tmem size does not match the texture size");
    } else {
        ASSERTMSGLINE(0x6A5, totalOdd <= r->sizeOdd, "GXPreLoadEntireTexture: Odd tmem size does not match the texture size");
    }
#endif
    __GXFlushTextureState();
    GX_WRITE_RAS_REG(loadImage0);
    GX_WRITE_RAS_REG(loadImage1);
    GX_WRITE_RAS_REG(loadImage2);
    GX_WRITE_RAS_REG(loadImage3);
    if (maxLevelIndex != 0) {
        tmemAR = tmem1;
        tmemGB = tmem2;
        for (i = 0; i < maxLevelIndex; i++) {
            if (is32bit != 0) {
                base += nTiles * 2;
                tmemAR += nTiles;
                tmemGB += nTiles;
            } else {
                base += nTiles;
                if (i & 1) {
                    tmemGB += nTiles;
                } else {
                    tmemAR += nTiles;
                }
            }
            tmem1 = (i & 1) ? tmemAR : tmemGB;
            tmem2 = (i & 1) ? tmemGB : tmemAR;
            __GetImageTileCount(t->fmt, (u16) (wd >> (i + 1)), (u16) (ht >> (i + 1)), &rowTiles, &colTiles, &cmpTiles);
            nTiles = rowTiles * colTiles;
            SET_REG_FIELD(0x6D6, loadImage0, 21, 0, base);
            SET_REG_FIELD(0x6D7, loadImage1, 15, 0, tmem1);
            SET_REG_FIELD(0x6D8, loadImage2, 15, 0, tmem2);
            SET_REG_FIELD(0x6D9, loadImage3, 15, 0, nTiles);
            GX_WRITE_RAS_REG(loadImage0);
            GX_WRITE_RAS_REG(loadImage1);
            GX_WRITE_RAS_REG(loadImage2);
            GX_WRITE_RAS_REG(loadImage3);
        }
    }
    __GXFlushTextureState();

    // needed to match debug
    maxLevelIndex; maxLevelIndex; base; base; base; tmem1; tmem1; tmem2; tmem2;

}

void GXSetTexCoordScaleManually(GXTexCoordID coord, u8 enable, u16 ss, u16 ts)
{
    CHECK_GXBEGIN(0x6F6, "GXSetTexCoordScaleManually");
    ASSERTMSGLINEV(0x6F8, coord < 8, "%s: bad texcoord specified", "GXSetTexCoordScaleManually");
    gx->tcsManEnab = (gx->tcsManEnab & ~(1 << coord)) | (enable << coord);
    if (enable != 0) {
        SET_REG_FIELD(0x6FE, gx->suTs0[coord], 16, 0, (u16)(ss - 1));
        SET_REG_FIELD(0x6FF, gx->suTs1[coord], 16, 0, (u16)(ts - 1));
        GX_WRITE_RAS_REG(gx->suTs0[coord]);
        GX_WRITE_RAS_REG(gx->suTs1[coord]);
        gx->bpSentNot = GX_FALSE;
    }
}

void GXSetTexCoordCylWrap(GXTexCoordID coord, u8 s_enable, u8 t_enable)
{
    CHECK_GXBEGIN(0x718, "GXSetTexCoordCylWrap");
    ASSERTMSGLINEV(0x71A, coord < 8, "%s: bad texcoord specified", "GXSetTexCoordCylWrap");
    SET_REG_FIELD(0x71C, gx->suTs0[coord], 1, 17, s_enable);
    SET_REG_FIELD(0x71D, gx->suTs1[coord], 1, 17, t_enable);
    if (gx->tcsManEnab & (1 << coord)) {
        GX_WRITE_RAS_REG(gx->suTs0[coord]);
        GX_WRITE_RAS_REG(gx->suTs1[coord]);
        gx->bpSentNot = GX_FALSE;
    }
}

void GXSetTexCoordBias(GXTexCoordID coord, u8 s_enable, u8 t_enable)
{
    CHECK_GXBEGIN(0x737, "GXSetTexCoordBias");
    ASSERTMSGLINEV(0x739, coord < 8, "%s: bad texcoord specified", "GXSetTexCoordBias");
    SET_REG_FIELD(0x73B, gx->suTs0[coord], 1, 16, s_enable);
    SET_REG_FIELD(0x73C, gx->suTs1[coord], 1, 16, t_enable);
    if (gx->tcsManEnab & (1 << coord)) {
        GX_WRITE_RAS_REG(gx->suTs0[coord]);
        GX_WRITE_RAS_REG(gx->suTs1[coord]);
        gx->bpSentNot = GX_FALSE;
    }
}

static void __SetSURegs(u32 tmap, u32 tcoord)
{
    u32 w;
    u32 h;
    u8 s_bias;
    u8 t_bias;

    w = GET_REG_FIELD(gx->tImage0[tmap], 10, 0);
    h = GET_REG_FIELD(gx->tImage0[tmap], 10, 10);
    SET_REG_FIELD(0x75A, gx->suTs0[tcoord], 16, 0, w);
    SET_REG_FIELD(0x75B, gx->suTs1[tcoord], 16, 0, h);
    s_bias = GET_REG_FIELD(gx->tMode0[tmap], 2, 0) == 1;
    t_bias = GET_REG_FIELD(gx->tMode0[tmap], 2, 2) == 1;
    SET_REG_FIELD(0x761, gx->suTs0[tcoord], 1, 16, s_bias);
    SET_REG_FIELD(0x762, gx->suTs1[tcoord], 1, 16, t_bias);
    GX_WRITE_RAS_REG(gx->suTs0[tcoord]);
    GX_WRITE_RAS_REG(gx->suTs1[tcoord]);
    gx->bpSentNot = GX_FALSE;
}

void __GXSetSUTexRegs(void)
{
    u32 nStages;
    u32 nIndStages;
    u32 i;
    u32 map;
    u32 tmap;
    u32 coord;
    u32 *ptref;

    if (gx->tcsManEnab != 0xFF) {
        nStages = GET_REG_FIELD(gx->genMode, 4, 10) + 1;
        nIndStages = GET_REG_FIELD(gx->genMode, 3, 16);
        for (i = 0; i < nIndStages; i++) {
            switch (i) {
            case 0:
                tmap = GET_REG_FIELD(gx->iref, 3, 0);
                coord = GET_REG_FIELD(gx->iref, 3, 3);
                break;
            case 1:
                tmap = GET_REG_FIELD(gx->iref, 3, 6);
                coord = GET_REG_FIELD(gx->iref, 3, 9);
                break;
            case 2:
                tmap = GET_REG_FIELD(gx->iref, 3, 12);
                coord = GET_REG_FIELD(gx->iref, 3, 15);
                break;
            case 3:
                tmap = GET_REG_FIELD(gx->iref, 3, 18);
                coord = GET_REG_FIELD(gx->iref, 3, 21);
                break;
            }
            if (!(gx->tcsManEnab & (1 << coord))) {
                __SetSURegs(tmap, coord);
            }
        }
        i = 0;
        for (i = 0; i < nStages; i++) {
            ptref = &gx->tref[i / 2];
            map = gx->texmapId[i];
            tmap = map & 0xFFFFFEFF;
            if (i & 1) {
                coord = GET_REG_FIELD(*ptref, 3, 15);
            } else {
                coord = GET_REG_FIELD(*ptref, 3, 3);
            }
            if ((tmap != 0xFF) && !(gx->tcsManEnab & (1 << coord)) && (gx->tevTcEnab & (1 << i))) {
                __SetSURegs(tmap, coord);
            }
        }
    }
}

void __GXGetSUTexSize(GXTexCoordID coord, u16 *width, u16 *height)
{
    *width = (u16)gx->suTs0[coord] + 1;
    *height = (u16)gx->suTs1[coord] + 1;
}

void __GXSetTmemConfig(u32 config)
{
	switch (config) {
	case 1:
		GX_WRITE_RAS_REG(0x8c0d8000);
		GX_WRITE_RAS_REG(0x900dc000);

		GX_WRITE_RAS_REG(0x8d0d8800);
		GX_WRITE_RAS_REG(0x910dc800);

		GX_WRITE_RAS_REG(0x8e0d9000);
		GX_WRITE_RAS_REG(0x920dd000);

		GX_WRITE_RAS_REG(0x8f0d9800);
		GX_WRITE_RAS_REG(0x930dd800);

		GX_WRITE_RAS_REG(0xac0da000);
		GX_WRITE_RAS_REG(0xb00de000);

		GX_WRITE_RAS_REG(0xad0da800);
		GX_WRITE_RAS_REG(0xb10de800);

		GX_WRITE_RAS_REG(0xae0db000);
		GX_WRITE_RAS_REG(0xb20df000);

		GX_WRITE_RAS_REG(0xaf0db800);
		GX_WRITE_RAS_REG(0xb30df800);

		break;
	case 0:
	default:
		GX_WRITE_RAS_REG(0x8c0d8000);
		GX_WRITE_RAS_REG(0x900dc000);

		GX_WRITE_RAS_REG(0x8d0d8400);
		GX_WRITE_RAS_REG(0x910dc400);

		GX_WRITE_RAS_REG(0x8e0d8800);
		GX_WRITE_RAS_REG(0x920dc800);

		GX_WRITE_RAS_REG(0x8f0d8c00);
		GX_WRITE_RAS_REG(0x930dcc00);

		GX_WRITE_RAS_REG(0xac0d9000);
		GX_WRITE_RAS_REG(0xb00dd000);

		GX_WRITE_RAS_REG(0xad0d9400);
		GX_WRITE_RAS_REG(0xb10dd400);

		GX_WRITE_RAS_REG(0xae0d9800);
		GX_WRITE_RAS_REG(0xb20dd800);

		GX_WRITE_RAS_REG(0xaf0d9c00);
		GX_WRITE_RAS_REG(0xb30ddc00);

		break;
	}
}
