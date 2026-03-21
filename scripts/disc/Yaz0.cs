using System;
using Godot;

namespace AnimalCrossing.Disc;

/// <summary>
/// Yaz0 (SZS) decompression algorithm used by Nintendo for compressed game assets.
/// The foresta.rel.szs module and other compressed files use this format.
///
/// Format:
///   Header: "Yaz0" magic (4 bytes) + decompressed size (BE32) + padding (8 bytes)
///   Data:   Groups of (1 flag byte + up to 8 chunks)
///           Flag bit 1 = literal byte, Flag bit 0 = back-reference (copy from earlier output)
/// </summary>
public static class Yaz0
{
    private const uint Magic = 0x59617A30; // "Yaz0"

    public static byte[]? Decompress(byte[] src)
    {
        if (src.Length < 16)
            return null;

        // Verify magic
        uint magic = (uint)((src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3]);
        if (magic != Magic)
        {
            GD.PrintErr("[Yaz0] Invalid magic");
            return null;
        }

        // Read decompressed size (big-endian)
        uint decompSize = (uint)((src[4] << 24) | (src[5] << 16) | (src[6] << 8) | src[7]);
        byte[] dst = new byte[decompSize];

        int srcPos = 16; // Skip header
        int dstPos = 0;

        while (dstPos < decompSize && srcPos < src.Length)
        {
            byte flags = src[srcPos++];

            for (int bit = 7; bit >= 0 && dstPos < decompSize && srcPos < src.Length; bit--)
            {
                if ((flags & (1 << bit)) != 0)
                {
                    // Literal byte
                    dst[dstPos++] = src[srcPos++];
                }
                else
                {
                    // Back-reference: copy from earlier in output
                    if (srcPos + 1 >= src.Length) break;

                    byte b1 = src[srcPos++];
                    byte b2 = src[srcPos++];

                    int dist = ((b1 & 0x0F) << 8) | b2;
                    int copyPos = dstPos - dist - 1;

                    int length = b1 >> 4;
                    if (length == 0)
                    {
                        // Extended length: read another byte
                        if (srcPos >= src.Length) break;
                        length = src[srcPos++] + 0x12;
                    }
                    else
                    {
                        length += 2;
                    }

                    // Copy bytes (may overlap, so copy one at a time)
                    for (int j = 0; j < length && dstPos < decompSize; j++)
                    {
                        if (copyPos + j >= 0 && copyPos + j < dstPos)
                            dst[dstPos++] = dst[copyPos + j];
                        else
                            dst[dstPos++] = 0;
                    }
                }
            }
        }

        return dst;
    }
}
