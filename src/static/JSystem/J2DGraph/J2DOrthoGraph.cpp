#include "JSystem/J2D/J2DGrafContext.h"

#ifdef TARGET_PC
#include "pc_platform.h"
#else
#define pc_widescreen_set_projection GXSetProjection
#endif

J2DOrthoGraph::J2DOrthoGraph() : J2DGrafContext(0.0f, 0.0f, 0.0f, 0.0f) {
    setLookat();
}

J2DOrthoGraph::J2DOrthoGraph(f32 left, f32 top, f32 right, f32 bottom, f32 near, f32 far)
    : J2DGrafContext(left, top, right, bottom) {
    mOrtho = JGeometry::TBox2f(0, 0, right, bottom);
    mNear = near;
    mFar = far;
    setLookat();
}

void J2DOrthoGraph::setPort() {
    J2DGrafContext::setPort();
    C_MTXOrtho(mMtx44, mOrtho.i.y, 0.5f + mOrtho.f.y, mOrtho.i.x, mOrtho.f.x, mNear, mFar);
    pc_widescreen_set_projection(mMtx44, GX_ORTHOGRAPHIC);
}

void J2DOrthoGraph::setOrtho(const JGeometry::TBox2f& bounds, f32 far, f32 near) {
    mOrtho = bounds;
    mNear = -near;
    mFar = -far;
}

void J2DOrthoGraph::setLookat() {
    PSMTXIdentity(mPosMtx);
    GXLoadPosMtxImm(mPosMtx, 0);
}

void J2DOrthoGraph::scissorBounds(JGeometry::TBox2f* out, const JGeometry::TBox2f* src) {
    f32 widthPower = this->getWidthPower();
    f32 heightPower = this->getHeightPower();
    f32 ix = mBounds.i.x >= 0 ? mBounds.i.x : 0;
    f32 iy = mBounds.i.y >= 0 ? mBounds.i.y : 0;
    f32 f0 = ix + widthPower * (src->i.x - mOrtho.i.x);
    f32 f2 = ix + widthPower * (src->f.x - mOrtho.i.x);
    f32 f1 = iy + heightPower * (src->i.y - mOrtho.i.y);
    f32 f3 = iy + heightPower * (src->f.y - mOrtho.i.y);
    out->set(f0, f1, f2, f3);
    out->intersect(mScissorBounds);
}

void J2DDrawLine(f32 x1, f32 y1, f32 x2, f32 y2, JUtility::TColor color, int line_width) {
    J2DOrthoGraph oGrph;
    oGrph.setLineWidth(line_width);
    oGrph.setColor(color);
    oGrph.moveTo(x1, y1);
    oGrph.lineTo(x2, y2);
}

void J2DFillBox(f32 l, f32 t, f32 x, f32 y, JUtility::TColor color) {
    J2DFillBox(JGeometry::TBox2f(l, t, l + x, t + y), color);
}

void J2DFillBox(const JGeometry::TBox2f& box, JUtility::TColor color) {
    J2DOrthoGraph oGrph;
    oGrph.setColor(color);
    oGrph.fillBox(box);
}

void J2DFillBox(f32 l, f32 t, f32 x, f32 y, JUtility::TColor c1, JUtility::TColor c2, JUtility::TColor c3,
                JUtility::TColor c4) {
    J2DFillBox(JGeometry::TBox2f(l, t, l + x, t + y), c1, c2, c3, c4);
}

void J2DFillBox(const JGeometry::TBox2f& box, JUtility::TColor c1, JUtility::TColor c2, JUtility::TColor c3,
                JUtility::TColor c4) {
    J2DOrthoGraph oGrph;
    oGrph.setColor(c1, c2, c3, c4);
    oGrph.fillBox(box);
}

void J2DDrawFrame(f32 l, f32 t, f32 x, f32 y, JUtility::TColor color, u8 line_width) {
    J2DDrawFrame(JGeometry::TBox2f(l, t, l + x, t + y), color, line_width);
}

void J2DDrawFrame(const JGeometry::TBox2f& box, JUtility::TColor color, u8 line_width) {
    J2DOrthoGraph oGrph;
    oGrph.setColor(color);
    oGrph.setLineWidth(line_width);
    oGrph.drawFrame(box);
}
