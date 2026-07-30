#include <dolphin/gx.h>
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JSupport.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JUtility/JUTFont.h"
#include "types.h"

JUTFont::IsLeadByte const JUTResFont::saoAboutEncoding_[3] = { JUTFont::isLeadByte_1Byte, JUTFont::isLeadByte_2Byte,
                                                               JUTFont::isLeadByte_ShiftJIS };
const u32 suAboutEncoding_ = 3;

JUTResFont::JUTResFont() {
    initialize_state();
}

JUTResFont::JUTResFont(const ResFONT* resource, JKRHeap* heap) {
    initialize_state();
    JUTResFont::initiate(resource, heap);
}

JUTResFont::~JUTResFont() {
#ifdef TARGET_PC
    if (_44 != -1) {
        GXDestroyTexObj(&_24);
    }
#endif
    if (mValid) {
        deleteMemBlocks_ResFont();
        initialize_state();
        JUTFont::initialize_state();
    }
}

void JUTResFont::deleteMemBlocks_ResFont() {
    delete[] mMemBlocks;
}

void JUTResFont::initialize_state() {
    mResource = nullptr;
    mMemBlocks = nullptr;
    mWidthBlocks = nullptr;
    mGlyphBlocks = nullptr;
    mMapBlocks = nullptr;
    mWidth = 0;
    mHeight = 0;
    _44 = -1;
}

bool JUTResFont::initiate(const ResFONT* resource, JKRHeap* heap) {
    if (!protected_initiate(resource, heap)) {
        deleteMemBlocks_ResFont();
        initialize_state();
        JUTFont::initialize_state();
        mValid = false;
        return false;
    }
    return true;
}

bool JUTResFont::protected_initiate(const ResFONT* resource, JKRHeap* heap) {
    void** blocks;

#ifdef TARGET_PC
    if (_44 != -1) {
        GXDestroyTexObj(&_24);
    }
#endif
    deleteMemBlocks_ResFont();
    initialize_state();
    JUTFont::initialize_state();

    if (!resource) {
        return false;
    }

    mResource = resource;
    mValid = true;

    countBlock();
    u32 blockNum = mWidthBlockCount + mGlyphBlockCount + mMapBlockCount;

    mMemBlocks = new (heap, 0) void*[blockNum];
    blocks = mMemBlocks;
    if (mMemBlocks == nullptr) {
        return false;
    } else {
        if (mWidthBlockCount != 0) {
            mWidthBlocks = (ResFONT::WidthBlock**)blocks;
            blocks += mWidthBlockCount;
        }

        if (mGlyphBlockCount != 0) {
            mGlyphBlocks = (ResFONT::GlyphBlock**)blocks;
            blocks += mGlyphBlockCount;
        }

        if (mMapBlockCount != 0) {
            mMapBlocks = (ResFONT::MapBlock**)blocks;
        }
    }

    setBlock();
    return true;
}

void JUTResFont::countBlock() {
    mWidthBlockCount = 0;
    mGlyphBlockCount = 0;
    mMapBlockCount = 0;

    BlockHeader* data = (BlockHeader*)mResource->mData;
    for (u32 i = 0; i < mResource->mNumBlocks; i++, data = (BlockHeader*)data->getNext()) {
        int magic = data->mMagic;
        switch (magic) {
            case 'WID1':
                mWidthBlockCount++;
                break;

            case 'GLY1':
                mGlyphBlockCount++;
                break;

            case 'MAP1':
                mMapBlockCount++;
                break;

            case 'INF1':
                // mInfoBlock;
                break;

            default:
                JUTReportConsole("JUTResFont: Unknown data block\n");
        }
    };
}

void JUTResFont::setBlock() {
    int widthNum = 0;
    int glyphNum = 0;
    int mapNum = 0;
    mMaxCode = -1;

    BlockHeader* data = (BlockHeader*)mResource->mData;
    for (u32 i = 0; i < mResource->mNumBlocks; i++, data = (BlockHeader*)data->getNext()) {
        int magic = data->mMagic;
        switch (magic) {
            case 'INF1': {
                mInfoBlock = (ResFONT::InfoBlock*)data;
                u32 u = mInfoBlock->mFontType;
                JUT_ASSERT(u < suAboutEncoding_);
                mIsLeadByte = (IsLeadByte*)&saoAboutEncoding_[u];
                break;
            }
            case 'WID1':
                mWidthBlocks[widthNum] = (ResFONT::WidthBlock*)data;
                widthNum++;
                break;

            case 'GLY1':
                mGlyphBlocks[glyphNum] = (ResFONT::GlyphBlock*)data;
                glyphNum++;
                break;

            case 'MAP1':
                mMapBlocks[mapNum] = (ResFONT::MapBlock*)data;
                if (mMaxCode > mMapBlocks[mapNum]->mStartCode) {
                    mMaxCode = mMapBlocks[mapNum]->mStartCode;
                }
                mapNum++;
                break;

            default:
                JUTReportConsole("Unknown data block\n");
                break;
        }
    }
}

void JUTResFont::setGX() {
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_RGBA4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBX8, 15);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
}

void JUTResFont::setGX(JUtility::TColor color0, JUtility::TColor color1) {
    if (u32(color0) == 0 && u32(color1) == -1) {
        setGX();
    } else {
        GXSetNumChans(1);
        GXSetNumTevStages(2);
        GXSetNumTexGens(1);

        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

        GXSetTevColor(GX_TEVREG0, color0);
        GXSetTevColor(GX_TEVREG1, color1);

        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_A1, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBX8, 15);

        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    }
}

f32 JUTResFont::drawChar_scale(f32 pos_x, f32 pos_y, f32 scale_x, f32 scale_y, int chr, bool flag) {
    JUTFont::TWidth width;
    f32 posMinX;
    // declaration order matters!
    f32 posMinY, scaled_height;
    f32 posMaxX;

    JUT_ASSERT(mValid);
    loadFont(chr, GX_TEXMAP0, &width);

    if ((mFixed) || (!flag)) {
        posMinX = pos_x;
    } else {
        posMinX = (pos_x - width.w0 * (scale_x / getCellWidth()));
    }

    f32 retval = mFixedWidth * (scale_x / getCellWidth());
    if (!mFixed) {
        if (!flag) {
            retval = (width.w1 + width.w0) * (scale_x / getCellWidth());
        } else {
            retval = width.w1 * (scale_x / getCellWidth());
        }
    }
    posMaxX = posMinX + scale_x;
    // getAscent needs to be called before getHeight for the sake of weak function order
    posMinY = pos_y - getAscent() * (scale_y / getHeight());
    scaled_height = scale_y / getHeight();
    f32 descent = getDescent();
    f32 posMaxY = descent * scaled_height + pos_y;

    // glyph section
    ResFONT::GlyphBlock* used_glyphs = mGlyphBlocks[_66];
    u16 tex_width = used_glyphs->mTextureWidth;
    u16 tex_height = used_glyphs->mTextureHeight;
    int t_width = mWidth;
    int t_height = mHeight;
    int shift_width = (t_width + used_glyphs->mCellWidth) << 15;
    int texMinX = (t_width << 15) / tex_width;
    int texMinY = (t_height << 15) / tex_height;
    int shift_height = t_height + used_glyphs->mCellHeight << 15;
    const u32 texMaxX = shift_width / tex_width;
    const u32 texMaxY = shift_height / tex_height;
    // end glyph section
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    // Bottom left
    GXPosition3f32(posMinX, posMinY, 0.0f);
    GXColor1u32(mColor1);
    GXPosition2u16(texMinX, texMinY);

    // Bottom right
    GXPosition3f32(posMaxX, posMinY, 0.0f);
    GXColor1u32(mColor2);
    GXPosition2u16(texMaxX, texMinY);

    // Top right
    GXPosition3f32(posMaxX, posMaxY, 0.0f);
    GXColor1u32(mColor4);
    GXPosition2u16(texMaxX, texMaxY);

    // Top left
    GXPosition3f32(posMinX, posMaxY, 0.0f);
    GXColor1u32(mColor3);
    GXPosition2u16(texMinX, texMaxY);
    GXEnd();

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);

    return retval;
}

void JUTResFont::loadFont(int chr, GXTexMapID id, JUTFont::TWidth* width) {
    if (width) {
        getWidthEntry(chr, width);
    }
    int fontcode = getFontCode(chr);
    loadImage(fontcode, id);
}

void JUTResFont::getWidthEntry(int chr, JUTFont::TWidth* width) const {
    int fontcode = getFontCode(chr);
    width->w0 = 0;
    width->w1 = mInfoBlock->mWidth;

    for (int i = 0; i < mWidthBlockCount; i++) {
        if (mWidthBlocks[i]->mStartCode <= fontcode && fontcode <= mWidthBlocks[i]->mEndCode) {
            *width = mWidthBlocks[i]->mChunkNum[(fontcode - mWidthBlocks[i]->mStartCode)];
            break;
        }
    }
    return;
}

int JUTResFont::getCellWidth() const {
    ResFONT::GlyphBlock* glyph;
    ResFONT::GlyphBlock** glyphs;

    glyphs = mGlyphBlocks;
    if (glyphs) {
        glyph = *glyphs;
        if (glyph) {
            return glyph->mCellWidth;
        }
    }
    return getWidth();
}

int JUTResFont::getCellHeight() const {
    ResFONT::GlyphBlock* glyph;
    ResFONT::GlyphBlock** glyphs;

    glyphs = mGlyphBlocks;
    if (glyphs) {
        glyph = *glyphs;
        if (glyph) {
            return glyph->mCellHeight;
        }
    }
    return getHeight();
}

bool JUTResFont::isLeadByte(int chr) const {
    return (*mIsLeadByte)(chr);
}

// regswaps
int JUTResFont::getFontCode(int chr) const {
    static const u16 halftofull[95] = {
        0x8140, 0x8149, 0x8168, 0x8194, 0x8190, 0x8193, 0x8195, 0x8166, 0x8169, 0x816A, 0x8196, 0x817B, 0x8143, 0x817C,
        0x8144, 0x815E, 0x824F, 0x8250, 0x8251, 0x8252, 0x8253, 0x8254, 0x8255, 0x8256, 0x8257, 0x8258, 0x8146, 0x8147,
        0x8183, 0x8181, 0x8184, 0x8148, 0x8197, 0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268,
        0x8269, 0x826A, 0x826B, 0x826C, 0x826D, 0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276,
        0x8277, 0x8278, 0x8279, 0x816D, 0x818F, 0x816E, 0x814F, 0x8151, 0x8165, 0x8281, 0x8282, 0x8283, 0x8284, 0x8285,
        0x8286, 0x8287, 0x8288, 0x8289, 0x828A, 0x828B, 0x828C, 0x828D, 0x828E, 0x828F, 0x8290, 0x8291, 0x8292, 0x8293,
        0x8294, 0x8295, 0x8296, 0x8297, 0x8298, 0x8299, 0x829A, 0x816F, 0x8162, 0x8170, 0x8160,
    };

    int ret = mInfoBlock->mDefaultCode;
    if ((getFontType() == 2) && (mMaxCode >= 0x8000U) && (chr >= 0x20) && (chr < 0x7FU)) {
        chr = halftofull[chr - 32];
    }

    for (int i = 0; i < mMapBlockCount; i++) {
        if ((mMapBlocks[i]->mStartCode <= chr) && (chr <= mMapBlocks[i]->mEndCode)) {
            if (mMapBlocks[i]->mMappingMethod == 0) {
                ret = chr - mMapBlocks[i]->mStartCode;
                break;
            } else if (mMapBlocks[i]->mMappingMethod == 2) {
                ret = *(&mMapBlocks[i]->mLeading + ((chr - mMapBlocks[i]->mStartCode))); // type punning sin
                break;
            } else if (mMapBlocks[i]->mMappingMethod == 3) {

                u16* leading_temp = &mMapBlocks[i]->mLeading;
                int phi_r5 = 0;
                int phi_r6_2 = mMapBlocks[i]->mNumEntries - 1;

                while (phi_r6_2 >= phi_r5) {
                    int temp_r7 = (phi_r6_2 + phi_r5) / 2;

                    if (chr < leading_temp[temp_r7 * 2]) {
                        phi_r6_2 = temp_r7 - 1;
                        continue;
                    }

                    if (chr > leading_temp[temp_r7 * 2]) {
                        phi_r5 = temp_r7 + 1;
                        continue;
                    }

                    ret = leading_temp[temp_r7 * 2 + 1]; // jank? possibly type punning fuckery
                    break;
                } // loop closes here
            } else if (mMapBlocks[i]->mMappingMethod == 1) {
                u16* phi_r5_2 = nullptr;
                if (mMapBlocks[i]->mNumEntries == 1) {
                    phi_r5_2 = &mMapBlocks[i]->mLeading;
                }
                ret = JUTResFont::convertSjis(chr, phi_r5_2);
                break;
            }
            break;
        }
    }
    return ret;
}

void JUTResFont::loadImage(int code, GXTexMapID id) {

    int i = 0;
    for (; i < mGlyphBlockCount; i++) {
        if (mGlyphBlocks[i]->mStartCode <= code && code <= mGlyphBlocks[i]->mEndCode) {
            code -= mGlyphBlocks[i]->mStartCode;
            break;
        }
    }

    if (i == mGlyphBlockCount)
        return;

    s32 pageNumCells = mGlyphBlocks[i]->mNumRows * mGlyphBlocks[i]->mNumColumns;
    s32 pageIdx = code / pageNumCells;
    s32 cellIdxInPage = code % pageNumCells;
    s32 cellCol = (cellIdxInPage % mGlyphBlocks[i]->mNumRows);
    s32 cellRow = (cellIdxInPage / mGlyphBlocks[i]->mNumRows);
    mWidth = cellCol * mGlyphBlocks[i]->mCellWidth;
    mHeight = cellRow * mGlyphBlocks[i]->mCellHeight;

    if (pageIdx != _44 || i != _66) {
#ifdef TARGET_PC
        const void* image = &mGlyphBlocks[i]->mData[pageIdx * mGlyphBlocks[i]->mTextureSize];

        if (_44 != -1 && i == _66) {
            /* Pages in one glyph block share their descriptor. Keep Aurora's
             * texture-object identity and invalidate only its image data. */
            GXInitTexObjData(&_24, image);
        } else {
            if (_44 != -1) {
                GXDestroyTexObj(&_24);
            }
            GXInitTexObj(&_24, image, mGlyphBlocks[i]->mTextureWidth, mGlyphBlocks[i]->mTextureHeight,
                         (GXTexFmt)mGlyphBlocks[i]->mTextureFormat, GX_CLAMP, GX_CLAMP, 0);
            GXInitTexObjLOD(&_24, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0U, 0U, GX_ANISO_1);
        }
#else
        GXInitTexObj(&_24, &mGlyphBlocks[i]->mData[pageIdx * mGlyphBlocks[i]->mTextureSize],
                     mGlyphBlocks[i]->mTextureWidth, mGlyphBlocks[i]->mTextureHeight,
                     (GXTexFmt)mGlyphBlocks[i]->mTextureFormat, GX_CLAMP, GX_CLAMP, 0);

        GXInitTexObjLOD(&_24, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0U, 0U, GX_ANISO_1);
#endif
        _44 = pageIdx;
        _66 = i;
    }

    GXLoadTexObj(&_24, id);
}

// probably needs some work to match TP(debug)
int JUTResFont::convertSjis(int inChr, u16* inLead) const {
    u8 hi = JSUHiByte(inChr);
    u16 lead = JSULoByte(inChr);
    int out = lead - 0x40;
    if (0x40 <= out) {
        out--;
    }
    lead = 0x31c;
    if (inLead) {
        lead = *inLead;
    }
    return out + (hi - 0x88) * 0xbc + -0x5e + lead;
}
