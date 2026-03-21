using System;
using Godot;

namespace AnimalCrossing.Graphics;

/// <summary>
/// Decodes GameCube texture formats to RGBA8 for use with Godot's Image class.
/// Equivalent to the texture decoding in pc_gx_texture.c.
///
/// Supported GameCube formats:
///   I4      - 4-bit intensity (grayscale)
///   I8      - 8-bit intensity
///   IA4     - 4-bit intensity + 4-bit alpha
///   IA8     - 8-bit intensity + 8-bit alpha
///   RGB565  - 16-bit color (5-6-5)
///   RGB5A3  - 16-bit color with alpha (RGB555 or RGBA4443)
///   RGBA8   - 32-bit color (two-pass: AR then GB)
///   CI4     - 4-bit indexed color (with palette)
///   CI8     - 8-bit indexed color (with palette)
///   CMPR    - S3TC/DXT1 compressed (4x4 blocks)
/// </summary>
public static class TextureDecoder
{
    public enum GXTexFmt
    {
        I4 = 0,
        I8 = 1,
        IA4 = 2,
        IA8 = 3,
        RGB565 = 4,
        RGB5A3 = 5,
        RGBA8 = 6,
        CI4 = 8,
        CI8 = 9,
        CI14X2 = 10,
        CMPR = 14,
    }

    /// <summary>
    /// Decode a GameCube texture to RGBA8 byte array.
    /// Returns width*height*4 bytes in RGBA order.
    /// </summary>
    public static byte[] Decode(byte[] src, int width, int height, GXTexFmt format, byte[]? palette = null)
    {
        byte[] rgba = new byte[width * height * 4];

        switch (format)
        {
            case GXTexFmt.I4:
                DecodeI4(src, rgba, width, height);
                break;
            case GXTexFmt.I8:
                DecodeI8(src, rgba, width, height);
                break;
            case GXTexFmt.IA4:
                DecodeIA4(src, rgba, width, height);
                break;
            case GXTexFmt.IA8:
                DecodeIA8(src, rgba, width, height);
                break;
            case GXTexFmt.RGB565:
                DecodeRGB565(src, rgba, width, height);
                break;
            case GXTexFmt.RGB5A3:
                DecodeRGB5A3(src, rgba, width, height);
                break;
            case GXTexFmt.RGBA8:
                DecodeRGBA8(src, rgba, width, height);
                break;
            case GXTexFmt.CI4:
                DecodeCI4(src, rgba, width, height, palette);
                break;
            case GXTexFmt.CI8:
                DecodeCI8(src, rgba, width, height, palette);
                break;
            case GXTexFmt.CMPR:
                DecodeCMPR(src, rgba, width, height);
                break;
            default:
                GD.PrintErr($"[TEX] Unsupported format: {format}");
                break;
        }

        return rgba;
    }

    /// <summary>Create a Godot ImageTexture from decoded data.</summary>
    public static ImageTexture CreateTexture(byte[] src, int width, int height, GXTexFmt format, byte[]? palette = null)
    {
        byte[] rgba = Decode(src, width, height, format, palette);
        var image = Image.CreateFromData(width, height, false, Image.Format.Rgba8, rgba);
        return ImageTexture.CreateFromImage(image);
    }

    // --- I4: 8x8 tiles, 4 bits per pixel ---
    private static void DecodeI4(byte[] src, byte[] dst, int w, int h)
    {
        int srcPos = 0;
        for (int ty = 0; ty < h; ty += 8)
        {
            for (int tx = 0; tx < w; tx += 8)
            {
                for (int y = 0; y < 8 && ty + y < h; y++)
                {
                    for (int x = 0; x < 8 && tx + x < w; x += 2)
                    {
                        if (srcPos >= src.Length) return;
                        byte b = src[srcPos++];

                        int i0 = (b >> 4) * 17; // Expand 4-bit to 8-bit
                        int i1 = (b & 0xF) * 17;

                        SetPixel(dst, w, tx + x, ty + y, (byte)i0, (byte)i0, (byte)i0, 255);
                        if (tx + x + 1 < w)
                            SetPixel(dst, w, tx + x + 1, ty + y, (byte)i1, (byte)i1, (byte)i1, 255);
                    }
                }
            }
        }
    }

    // --- I8: 8x4 tiles, 8 bits per pixel ---
    private static void DecodeI8(byte[] src, byte[] dst, int w, int h)
    {
        int srcPos = 0;
        for (int ty = 0; ty < h; ty += 4)
        {
            for (int tx = 0; tx < w; tx += 8)
            {
                for (int y = 0; y < 4 && ty + y < h; y++)
                {
                    for (int x = 0; x < 8 && tx + x < w; x++)
                    {
                        if (srcPos >= src.Length) return;
                        byte i = src[srcPos++];
                        SetPixel(dst, w, tx + x, ty + y, i, i, i, 255);
                    }
                }
            }
        }
    }

    // --- IA4: 8x4 tiles, 8 bits per pixel (4 intensity + 4 alpha) ---
    private static void DecodeIA4(byte[] src, byte[] dst, int w, int h)
    {
        int srcPos = 0;
        for (int ty = 0; ty < h; ty += 4)
        {
            for (int tx = 0; tx < w; tx += 8)
            {
                for (int y = 0; y < 4 && ty + y < h; y++)
                {
                    for (int x = 0; x < 8 && tx + x < w; x++)
                    {
                        if (srcPos >= src.Length) return;
                        byte b = src[srcPos++];
                        byte a = (byte)((b >> 4) * 17);
                        byte i = (byte)((b & 0xF) * 17);
                        SetPixel(dst, w, tx + x, ty + y, i, i, i, a);
                    }
                }
            }
        }
    }

    // --- IA8: 4x4 tiles, 16 bits per pixel (8 alpha + 8 intensity) ---
    private static void DecodeIA8(byte[] src, byte[] dst, int w, int h)
    {
        int srcPos = 0;
        for (int ty = 0; ty < h; ty += 4)
        {
            for (int tx = 0; tx < w; tx += 4)
            {
                for (int y = 0; y < 4 && ty + y < h; y++)
                {
                    for (int x = 0; x < 4 && tx + x < w; x++)
                    {
                        if (srcPos + 1 >= src.Length) return;
                        byte a = src[srcPos++];
                        byte i = src[srcPos++];
                        SetPixel(dst, w, tx + x, ty + y, i, i, i, a);
                    }
                }
            }
        }
    }

    // --- RGB565: 4x4 tiles, 16 bits per pixel ---
    private static void DecodeRGB565(byte[] src, byte[] dst, int w, int h)
    {
        int srcPos = 0;
        for (int ty = 0; ty < h; ty += 4)
        {
            for (int tx = 0; tx < w; tx += 4)
            {
                for (int y = 0; y < 4 && ty + y < h; y++)
                {
                    for (int x = 0; x < 4 && tx + x < w; x++)
                    {
                        if (srcPos + 1 >= src.Length) return;
                        ushort pixel = (ushort)((src[srcPos] << 8) | src[srcPos + 1]);
                        srcPos += 2;

                        byte r = (byte)(((pixel >> 11) & 0x1F) * 255 / 31);
                        byte g = (byte)(((pixel >> 5) & 0x3F) * 255 / 63);
                        byte b = (byte)((pixel & 0x1F) * 255 / 31);
                        SetPixel(dst, w, tx + x, ty + y, r, g, b, 255);
                    }
                }
            }
        }
    }

    // --- RGB5A3: 4x4 tiles, 16 bits per pixel ---
    private static void DecodeRGB5A3(byte[] src, byte[] dst, int w, int h)
    {
        int srcPos = 0;
        for (int ty = 0; ty < h; ty += 4)
        {
            for (int tx = 0; tx < w; tx += 4)
            {
                for (int y = 0; y < 4 && ty + y < h; y++)
                {
                    for (int x = 0; x < 4 && tx + x < w; x++)
                    {
                        if (srcPos + 1 >= src.Length) return;
                        ushort pixel = (ushort)((src[srcPos] << 8) | src[srcPos + 1]);
                        srcPos += 2;

                        byte r, g, b, a;
                        if ((pixel & 0x8000) != 0)
                        {
                            // RGB555: no alpha
                            r = (byte)(((pixel >> 10) & 0x1F) * 255 / 31);
                            g = (byte)(((pixel >> 5) & 0x1F) * 255 / 31);
                            b = (byte)((pixel & 0x1F) * 255 / 31);
                            a = 255;
                        }
                        else
                        {
                            // RGBA4443: 3-bit alpha
                            a = (byte)(((pixel >> 12) & 0x07) * 255 / 7);
                            r = (byte)(((pixel >> 8) & 0x0F) * 255 / 15);
                            g = (byte)(((pixel >> 4) & 0x0F) * 255 / 15);
                            b = (byte)((pixel & 0x0F) * 255 / 15);
                        }
                        SetPixel(dst, w, tx + x, ty + y, r, g, b, a);
                    }
                }
            }
        }
    }

    // --- RGBA8: 4x4 tiles, two passes (AR then GB) ---
    private static void DecodeRGBA8(byte[] src, byte[] dst, int w, int h)
    {
        int srcPos = 0;
        for (int ty = 0; ty < h; ty += 4)
        {
            for (int tx = 0; tx < w; tx += 4)
            {
                // First pass: AR pairs
                byte[] ar = new byte[32];
                for (int i = 0; i < 32 && srcPos < src.Length; i++)
                    ar[i] = src[srcPos++];

                // Second pass: GB pairs
                byte[] gb = new byte[32];
                for (int i = 0; i < 32 && srcPos < src.Length; i++)
                    gb[i] = src[srcPos++];

                for (int y = 0; y < 4 && ty + y < h; y++)
                {
                    for (int x = 0; x < 4 && tx + x < w; x++)
                    {
                        int idx = (y * 4 + x) * 2;
                        byte a = ar[idx];
                        byte r = ar[idx + 1];
                        byte g = gb[idx];
                        byte b = gb[idx + 1];
                        SetPixel(dst, w, tx + x, ty + y, r, g, b, a);
                    }
                }
            }
        }
    }

    // --- CI4: 8x8 tiles, 4-bit palette index ---
    private static void DecodeCI4(byte[] src, byte[] dst, int w, int h, byte[]? palette)
    {
        if (palette == null) return;
        int srcPos = 0;
        for (int ty = 0; ty < h; ty += 8)
        {
            for (int tx = 0; tx < w; tx += 8)
            {
                for (int y = 0; y < 8 && ty + y < h; y++)
                {
                    for (int x = 0; x < 8 && tx + x < w; x += 2)
                    {
                        if (srcPos >= src.Length) return;
                        byte b = src[srcPos++];
                        int idx0 = b >> 4;
                        int idx1 = b & 0xF;

                        SetPalettePixel(dst, w, tx + x, ty + y, palette, idx0);
                        if (tx + x + 1 < w)
                            SetPalettePixel(dst, w, tx + x + 1, ty + y, palette, idx1);
                    }
                }
            }
        }
    }

    // --- CI8: 8x4 tiles, 8-bit palette index ---
    private static void DecodeCI8(byte[] src, byte[] dst, int w, int h, byte[]? palette)
    {
        if (palette == null) return;
        int srcPos = 0;
        for (int ty = 0; ty < h; ty += 4)
        {
            for (int tx = 0; tx < w; tx += 8)
            {
                for (int y = 0; y < 4 && ty + y < h; y++)
                {
                    for (int x = 0; x < 8 && tx + x < w; x++)
                    {
                        if (srcPos >= src.Length) return;
                        int idx = src[srcPos++];
                        SetPalettePixel(dst, w, tx + x, ty + y, palette, idx);
                    }
                }
            }
        }
    }

    // --- CMPR (DXT1/S3TC): 8x8 super-blocks of 4x4 sub-blocks ---
    private static void DecodeCMPR(byte[] src, byte[] dst, int w, int h)
    {
        int srcPos = 0;
        for (int ty = 0; ty < h; ty += 8)
        {
            for (int tx = 0; tx < w; tx += 8)
            {
                // Each 8x8 super-block contains four 4x4 DXT1 sub-blocks
                for (int by = 0; by < 2; by++)
                {
                    for (int bx = 0; bx < 2; bx++)
                    {
                        if (srcPos + 7 >= src.Length) return;
                        DecodeDXT1Block(src, srcPos, dst, w, h, tx + bx * 4, ty + by * 4);
                        srcPos += 8;
                    }
                }
            }
        }
    }

    private static void DecodeDXT1Block(byte[] src, int srcOff, byte[] dst, int w, int h, int bx, int by)
    {
        // DXT1 block: 2 colors (RGB565 BE) + 4x4 2-bit indices
        ushort c0 = (ushort)((src[srcOff] << 8) | src[srcOff + 1]);
        ushort c1 = (ushort)((src[srcOff + 2] << 8) | src[srcOff + 3]);

        byte r0 = (byte)(((c0 >> 11) & 0x1F) * 255 / 31);
        byte g0 = (byte)(((c0 >> 5) & 0x3F) * 255 / 63);
        byte b0 = (byte)((c0 & 0x1F) * 255 / 31);
        byte r1 = (byte)(((c1 >> 11) & 0x1F) * 255 / 31);
        byte g1 = (byte)(((c1 >> 5) & 0x3F) * 255 / 63);
        byte b1 = (byte)((c1 & 0x1F) * 255 / 31);

        byte[][] colors = new byte[4][];
        colors[0] = new[] { r0, g0, b0, (byte)255 };
        colors[1] = new[] { r1, g1, b1, (byte)255 };

        if (c0 > c1)
        {
            colors[2] = new[] { (byte)((2 * r0 + r1) / 3), (byte)((2 * g0 + g1) / 3), (byte)((2 * b0 + b1) / 3), (byte)255 };
            colors[3] = new[] { (byte)((r0 + 2 * r1) / 3), (byte)((g0 + 2 * g1) / 3), (byte)((b0 + 2 * b1) / 3), (byte)255 };
        }
        else
        {
            colors[2] = new[] { (byte)((r0 + r1) / 2), (byte)((g0 + g1) / 2), (byte)((b0 + b1) / 2), (byte)255 };
            colors[3] = new byte[] { 0, 0, 0, 0 }; // Transparent
        }

        for (int y = 0; y < 4; y++)
        {
            byte row = src[srcOff + 4 + y];
            for (int x = 0; x < 4; x++)
            {
                int idx = (row >> (6 - x * 2)) & 3;
                int px = bx + x, py = by + y;
                if (px < w && py < h)
                {
                    SetPixel(dst, w, px, py, colors[idx][0], colors[idx][1], colors[idx][2], colors[idx][3]);
                }
            }
        }
    }

    private static void SetPixel(byte[] dst, int w, int x, int y, byte r, byte g, byte b, byte a)
    {
        int offset = (y * w + x) * 4;
        if (offset + 3 < dst.Length)
        {
            dst[offset] = r;
            dst[offset + 1] = g;
            dst[offset + 2] = b;
            dst[offset + 3] = a;
        }
    }

    private static void SetPalettePixel(byte[] dst, int w, int x, int y, byte[] palette, int index)
    {
        // Palette entries are RGB5A3 format (2 bytes each, big-endian)
        int palOff = index * 2;
        if (palOff + 1 >= palette.Length) return;

        ushort pixel = (ushort)((palette[palOff] << 8) | palette[palOff + 1]);
        byte r, g, b, a;

        if ((pixel & 0x8000) != 0)
        {
            r = (byte)(((pixel >> 10) & 0x1F) * 255 / 31);
            g = (byte)(((pixel >> 5) & 0x1F) * 255 / 31);
            b = (byte)((pixel & 0x1F) * 255 / 31);
            a = 255;
        }
        else
        {
            a = (byte)(((pixel >> 12) & 0x07) * 255 / 7);
            r = (byte)(((pixel >> 8) & 0x0F) * 255 / 15);
            g = (byte)(((pixel >> 4) & 0x0F) * 255 / 15);
            b = (byte)((pixel & 0x0F) * 255 / 15);
        }

        SetPixel(dst, w, x, y, r, g, b, a);
    }
}
