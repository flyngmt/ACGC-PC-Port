using System;
using System.Collections.Generic;

namespace AnimalCrossing.Graphics;

/// <summary>
/// N64 display list (Gfx command buffer) representation.
/// The game builds display lists of graphics commands which are then
/// interpreted by the Emu64 processor to produce actual rendering.
///
/// Each command is 8 bytes (two 32-bit words).
/// The high byte of word0 contains the opcode.
/// </summary>
public class DisplayList
{
    /// <summary>A single N64 graphics command (GBI instruction).</summary>
    public struct GfxCommand
    {
        public uint Word0;
        public uint Word1;

        public byte Opcode => (byte)(Word0 >> 24);

        public GfxCommand(uint w0, uint w1)
        {
            Word0 = w0;
            Word1 = w1;
        }
    }

    // F3DEX2 opcodes (matching F3DEX_GBI_2 defines)
    public const byte G_NOOP          = 0x00;
    public const byte G_VTX           = 0x01;
    public const byte G_MODIFYVTX     = 0x02;
    public const byte G_CULLDL        = 0x03;
    public const byte G_BRANCH_Z      = 0x04;
    public const byte G_TRI1          = 0x05;
    public const byte G_TRI2          = 0x06;
    public const byte G_QUAD          = 0x07;
    public const byte G_SPECIAL_3     = 0xD3;
    public const byte G_SPECIAL_2     = 0xD4;
    public const byte G_SPECIAL_1     = 0xD5;
    public const byte G_DMA_IO        = 0xD6;
    public const byte G_TEXTURE       = 0xD7;
    public const byte G_POPMTX        = 0xD8;
    public const byte G_GEOMETRYMODE  = 0xD9;
    public const byte G_MTX           = 0xDA;
    public const byte G_MOVEWORD      = 0xDB;
    public const byte G_MOVEMEM       = 0xDC;
    public const byte G_LOAD_UCODE    = 0xDD;
    public const byte G_DL            = 0xDE;
    public const byte G_ENDDL         = 0xDF;
    public const byte G_SPNOOP        = 0xE0;
    public const byte G_RDPHALF_1     = 0xE1;
    public const byte G_SETOTHERMODE_L = 0xE2;
    public const byte G_SETOTHERMODE_H = 0xE3;
    public const byte G_TEXRECT       = 0xE4;
    public const byte G_TEXRECTFLIP   = 0xE5;
    public const byte G_RDPLOADSYNC   = 0xE6;
    public const byte G_RDPPIPESYNC   = 0xE7;
    public const byte G_RDPTILESYNC   = 0xE8;
    public const byte G_RDPFULLSYNC   = 0xE9;
    public const byte G_SETKEYGB      = 0xEA;
    public const byte G_SETKEYR       = 0xEB;
    public const byte G_SETCONVERT    = 0xEC;
    public const byte G_SETSCISSOR    = 0xED;
    public const byte G_SETPRIMDEPTH  = 0xEE;
    public const byte G_RDPSETOTHERMODE = 0xEF;
    public const byte G_LOADTLUT      = 0xF0;
    public const byte G_RDPHALF_2     = 0xF1;
    public const byte G_SETTILESIZE   = 0xF2;
    public const byte G_LOADBLOCK     = 0xF3;
    public const byte G_LOADTILE      = 0xF4;
    public const byte G_SETTILE       = 0xF5;
    public const byte G_FILLRECT      = 0xF6;
    public const byte G_SETFILLCOLOR  = 0xF7;
    public const byte G_SETFOGCOLOR   = 0xF8;
    public const byte G_SETBLENDCOLOR = 0xF9;
    public const byte G_SETPRIMCOLOR  = 0xFA;
    public const byte G_SETENVCOLOR   = 0xFB;
    public const byte G_SETCOMBINE    = 0xFC;
    public const byte G_SETTIMG       = 0xFD;
    public const byte G_SETZIMG       = 0xFE;
    public const byte G_SETCIMG       = 0xFF;

    private readonly List<GfxCommand> _commands = new();

    public int Count => _commands.Count;
    public GfxCommand this[int index] => _commands[index];

    public void Add(uint word0, uint word1)
    {
        _commands.Add(new GfxCommand(word0, word1));
    }

    public void Clear()
    {
        _commands.Clear();
    }

    /// <summary>
    /// Parse display list commands from raw big-endian byte data.
    /// Each command is 8 bytes.
    /// </summary>
    public static DisplayList FromBytes(byte[] data, int offset = 0, int maxCommands = int.MaxValue)
    {
        var dl = new DisplayList();
        int pos = offset;

        while (pos + 7 < data.Length && dl.Count < maxCommands)
        {
            uint w0 = (uint)((data[pos] << 24) | (data[pos + 1] << 16) |
                             (data[pos + 2] << 8) | data[pos + 3]);
            uint w1 = (uint)((data[pos + 4] << 24) | (data[pos + 5] << 16) |
                             (data[pos + 6] << 8) | data[pos + 7]);
            pos += 8;

            dl.Add(w0, w1);

            // Stop at end of display list
            if ((w0 >> 24) == G_ENDDL)
                break;
        }

        return dl;
    }
}
