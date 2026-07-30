#ifndef J2DGXCOLORS10_H
#define J2DGXCOLORS10_H

#include "types.h"
#include "dolphin/gx.h"
#include "JSystem/JUtility/TColor.h"

#ifdef __cplusplus
/**
 * Everything is fabricated here except for the default ctor.
 * Copied from J3DGXColorS10.
 */
struct J2DGXColorS10 : public GXColorS10 {
    J2DGXColorS10() {
    }

    J2DGXColorS10(u16 _r, u16 _g, u16 _b, u16 _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    J2DGXColorS10(const J2DGXColorS10& other) {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
    }

    J2DGXColorS10(const u64& other) {
        GXColorS10* otherBytes = (GXColorS10*)&other;
        r = otherBytes->r;
        g = otherBytes->g;
        b = otherBytes->b;
        a = otherBytes->a;
    }

    inline operator u64() const {
        return toUInt64();
    }
    inline u64 toUInt64() const {
        return *(u64*)&r;
    }

    inline operator JUtility::TColor() const {
        return toTColor();
    }
    inline JUtility::TColor toTColor() const {
        return JUtility::TColor(r, g, b, a);
    }
};
#endif

#endif
