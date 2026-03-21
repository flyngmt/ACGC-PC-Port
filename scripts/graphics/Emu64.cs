using System;
using Godot;
using AnimalCrossing.Core;
using AnimalCrossing.Disc;

namespace AnimalCrossing.Graphics;

/// <summary>
/// N64 display list interpreter, equivalent to emu64.c in the decomp.
/// Processes F3DEX2 GBI (Graphics Binary Interface) commands and translates
/// them to GXRenderer calls (which in turn use Godot's rendering).
///
/// The original game was written for the N64's Reality Signal Processor (RSP),
/// and this interpreter emulates the RSP's graphics command processing.
///
/// Pipeline: Raw GBI commands (8 bytes each) → Emu64 → GXRenderer → Godot
///
/// Vertex pipeline:
///   G_VTX → Load vertices into buffer (up to 32 entries)
///   G_TRI1/TRI2 → Reference loaded vertices to form triangles
///   G_MTX → Set/multiply model-view and projection matrices
///
/// Texture pipeline:
///   G_SETTIMG → Set texture image source address
///   G_SETTILE → Configure tile (format, size, line, palette)
///   G_LOADTILE/G_LOADBLOCK → Load texture data into TMEM
///   G_SETTILESIZE → Set tile clamp/wrap bounds
///
/// State pipeline:
///   G_SETCOMBINE → Configure color combiner (maps to TEV stages)
///   G_SETOTHERMODE → Blend, depth, alpha settings
///   G_GEOMETRYMODE → Cull, lighting, fog flags
///   G_SETPRIMCOLOR/G_SETENVCOLOR → Constant colors
/// </summary>
public class Emu64
{
    private readonly GXRenderer _gx;
    private readonly AssetLoader? _assets;

    // Vertex buffer (N64 has 32 vertex slots)
    private const int MaxVertices = 32;
    private readonly GXRenderer.GXVertex[] _vertexBuffer = new GXRenderer.GXVertex[MaxVertices];

    // Matrix (4x4 float)
    private readonly float[] _tempMatrix = new float[16];

    // Texture state
    private uint _texImageAddr;
    private byte _texImageFmt;
    private byte _texImageSiz;
    private ushort _texImageWidth;

    // TMEM (Texture Memory - 4KB on N64)
    private readonly byte[] _tmem = new byte[4096];

    // Tile descriptors (8 tiles)
    private readonly TileDescriptor[] _tiles = new TileDescriptor[8];

    // Geometry mode
    private uint _geometryMode;

    // Other mode (RDP settings)
    private uint _otherModeH;
    private uint _otherModeL;

    // Combine mode (64-bit value split across two words)
    private uint _combineModeHi;
    private uint _combineModeLo;

    // Display list call stack
    private const int MaxDLDepth = 18;
    private readonly DLStackEntry[] _dlStack = new DLStackEntry[MaxDLDepth];
    private int _dlStackDepth;

    // Frame statistics
    public int FrameCommands { get; private set; }
    public int FrameTriangles { get; private set; }
    public int FrameVertices { get; private set; }
    public int FrameCrashes { get; private set; }

    private struct TileDescriptor
    {
        public byte Format;
        public byte Size;     // Texel size (0=4bit, 1=8bit, 2=16bit, 3=32bit)
        public ushort Line;   // Line size in 64-bit words
        public ushort TMemAddr;
        public byte Palette;
        public byte ClampS, ClampT;
        public byte MirrorS, MirrorT;
        public byte MaskS, MaskT;
        public byte ShiftS, ShiftT;
        public ushort ULS, ULT, LRS, LRT; // Tile bounds (10.2 fixed point)
    }

    private struct DLStackEntry
    {
        public byte[] Data;
        public int Position;
    }

    public Emu64(GXRenderer gx, AssetLoader? assets = null)
    {
        _gx = gx;
        _assets = assets;
    }

    /// <summary>
    /// Execute a display list. This is the main entry point, equivalent to
    /// emu64_taskstart() in the original code.
    /// </summary>
    public void Execute(DisplayList dl)
    {
        FrameCommands = 0;
        FrameTriangles = 0;
        FrameVertices = 0;
        FrameCrashes = 0;

        ExecuteInternal(dl);
    }

    /// <summary>Execute display list commands from raw byte data.</summary>
    public void Execute(byte[] data, int offset = 0)
    {
        var dl = DisplayList.FromBytes(data, offset);
        Execute(dl);
    }

    private void ExecuteInternal(DisplayList dl)
    {
        for (int i = 0; i < dl.Count; i++)
        {
            var cmd = dl[i];
            FrameCommands++;

            try
            {
                ProcessCommand(cmd);
            }
            catch (Exception ex)
            {
                FrameCrashes++;
                if (FrameCrashes <= 5)
                    GD.PrintErr($"[EMU64] Command 0x{cmd.Opcode:X2} crash: {ex.Message}");
            }

            if (cmd.Opcode == DisplayList.G_ENDDL)
                break;
        }
    }

    private void ProcessCommand(DisplayList.GfxCommand cmd)
    {
        switch (cmd.Opcode)
        {
            case DisplayList.G_NOOP:
                HandleNoop(cmd);
                break;
            case DisplayList.G_VTX:
                HandleVertex(cmd);
                break;
            case DisplayList.G_TRI1:
                HandleTri1(cmd);
                break;
            case DisplayList.G_TRI2:
                HandleTri2(cmd);
                break;
            case DisplayList.G_QUAD:
                HandleQuad(cmd);
                break;
            case DisplayList.G_MTX:
                HandleMatrix(cmd);
                break;
            case DisplayList.G_POPMTX:
                HandlePopMatrix(cmd);
                break;
            case DisplayList.G_GEOMETRYMODE:
                HandleGeometryMode(cmd);
                break;
            case DisplayList.G_TEXTURE:
                HandleTexture(cmd);
                break;
            case DisplayList.G_SETTIMG:
                HandleSetTImg(cmd);
                break;
            case DisplayList.G_SETTILE:
                HandleSetTile(cmd);
                break;
            case DisplayList.G_SETTILESIZE:
                HandleSetTileSize(cmd);
                break;
            case DisplayList.G_LOADBLOCK:
                HandleLoadBlock(cmd);
                break;
            case DisplayList.G_LOADTILE:
                HandleLoadTile(cmd);
                break;
            case DisplayList.G_LOADTLUT:
                HandleLoadTLUT(cmd);
                break;
            case DisplayList.G_SETCOMBINE:
                HandleSetCombine(cmd);
                break;
            case DisplayList.G_SETOTHERMODE_H:
                HandleSetOtherModeH(cmd);
                break;
            case DisplayList.G_SETOTHERMODE_L:
                HandleSetOtherModeL(cmd);
                break;
            case DisplayList.G_SETPRIMCOLOR:
                HandleSetPrimColor(cmd);
                break;
            case DisplayList.G_SETENVCOLOR:
                HandleSetEnvColor(cmd);
                break;
            case DisplayList.G_SETFOGCOLOR:
                HandleSetFogColor(cmd);
                break;
            case DisplayList.G_SETFILLCOLOR:
                HandleSetFillColor(cmd);
                break;
            case DisplayList.G_SETBLENDCOLOR:
                HandleSetBlendColor(cmd);
                break;
            case DisplayList.G_FILLRECT:
                HandleFillRect(cmd);
                break;
            case DisplayList.G_SETSCISSOR:
                HandleSetScissor(cmd);
                break;
            case DisplayList.G_DL:
                HandleDL(cmd);
                break;
            case DisplayList.G_ENDDL:
                // Handled by caller
                break;
            case DisplayList.G_CULLDL:
                HandleCullDL(cmd);
                break;
            case DisplayList.G_MOVEWORD:
                HandleMoveWord(cmd);
                break;
            case DisplayList.G_MOVEMEM:
                HandleMoveMem(cmd);
                break;

            // Sync commands (no-ops on modern hardware)
            case DisplayList.G_RDPLOADSYNC:
            case DisplayList.G_RDPPIPESYNC:
            case DisplayList.G_RDPTILESYNC:
            case DisplayList.G_RDPFULLSYNC:
            case DisplayList.G_SPNOOP:
                break;

            default:
                // Unknown/unimplemented opcode
                break;
        }
    }

    // --- Command handlers ---

    private void HandleNoop(DisplayList.GfxCommand cmd)
    {
        // NOOP can carry tags for widescreen mode switching
        uint tag = cmd.Word1;
        if (tag == 0xAC5701) // PC_NOOP_WIDESCREEN_STRETCH
        {
            // Switch to stretch mode
        }
        else if (tag == 0xAC5700) // PC_NOOP_WIDESCREEN_STRETCH_OFF
        {
            // Switch back to pillarbox
        }
    }

    private void HandleVertex(DisplayList.GfxCommand cmd)
    {
        // G_VTX: Load vertices into buffer
        // w0: [31:24]=opcode [23:20]=numverts(n) [19:17]=??? [16:1]=length [0]=???
        // w1: address of vertex data
        int numVerts = ((int)(cmd.Word0 >> 12) & 0xFF);
        int startIdx = ((int)(cmd.Word0 >> 1) & 0x7F) - numVerts;

        FrameVertices += numVerts;

        // In a full implementation, we'd read vertex data from the game's memory
        // For now, create placeholder vertices
        for (int i = 0; i < numVerts && startIdx + i < MaxVertices; i++)
        {
            _vertexBuffer[startIdx + i] = new GXRenderer.GXVertex
            {
                Position = Vector3.Zero,
                Normal = Vector3.Up,
                Color = Colors.White,
                TexCoord0 = Vector2.Zero,
            };
        }
    }

    private void HandleTri1(DisplayList.GfxCommand cmd)
    {
        // G_TRI1: Draw one triangle
        int v0 = (int)((cmd.Word0 >> 16) & 0xFF) / 2;
        int v1 = (int)((cmd.Word0 >> 8) & 0xFF) / 2;
        int v2 = (int)(cmd.Word0 & 0xFF) / 2;

        if (v0 < MaxVertices && v1 < MaxVertices && v2 < MaxVertices)
        {
            _gx.Begin(GXRenderer.GXPrimitive.Triangles);
            _gx.AddVertex(_vertexBuffer[v0]);
            _gx.AddVertex(_vertexBuffer[v1]);
            _gx.AddVertex(_vertexBuffer[v2]);
            _gx.End();
            FrameTriangles++;
        }
    }

    private void HandleTri2(DisplayList.GfxCommand cmd)
    {
        // G_TRI2: Draw two triangles
        int v0 = (int)((cmd.Word0 >> 16) & 0xFF) / 2;
        int v1 = (int)((cmd.Word0 >> 8) & 0xFF) / 2;
        int v2 = (int)(cmd.Word0 & 0xFF) / 2;
        int v3 = (int)((cmd.Word1 >> 16) & 0xFF) / 2;
        int v4 = (int)((cmd.Word1 >> 8) & 0xFF) / 2;
        int v5 = (int)(cmd.Word1 & 0xFF) / 2;

        _gx.Begin(GXRenderer.GXPrimitive.Triangles);
        if (v0 < MaxVertices && v1 < MaxVertices && v2 < MaxVertices)
        {
            _gx.AddVertex(_vertexBuffer[v0]);
            _gx.AddVertex(_vertexBuffer[v1]);
            _gx.AddVertex(_vertexBuffer[v2]);
            FrameTriangles++;
        }
        if (v3 < MaxVertices && v4 < MaxVertices && v5 < MaxVertices)
        {
            _gx.AddVertex(_vertexBuffer[v3]);
            _gx.AddVertex(_vertexBuffer[v4]);
            _gx.AddVertex(_vertexBuffer[v5]);
            FrameTriangles++;
        }
        _gx.End();
    }

    private void HandleQuad(DisplayList.GfxCommand cmd)
    {
        // G_QUAD: Draw a quad (4 vertices, 2 triangles)
        HandleTri2(cmd); // Same encoding as TRI2
    }

    private void HandleMatrix(DisplayList.GfxCommand cmd)
    {
        // G_MTX: Set/multiply matrix
        // w0: [7:3]=params (push/load, projection/modelview)
        // w1: address of 4x4 fixed-point matrix
        byte param = (byte)((cmd.Word0 >> 0) & 0xFF);
        bool push = (param & 0x01) == 0;   // G_MTX_NOPUSH=1
        bool load = (param & 0x02) != 0;   // G_MTX_LOAD=2
        bool proj = (param & 0x04) != 0;   // G_MTX_PROJECTION=4

        // In a full implementation, we'd read the matrix from game memory at cmd.Word1
        // and convert from N64 fixed-point format to float
        if (push && !proj)
            _gx.PushMatrix();
    }

    private void HandlePopMatrix(DisplayList.GfxCommand cmd)
    {
        _gx.PopMatrix();
    }

    private void HandleGeometryMode(DisplayList.GfxCommand cmd)
    {
        // G_GEOMETRYMODE: clear & set geometry mode bits
        uint clearBits = cmd.Word0 & 0x00FFFFFF;
        uint setBits = cmd.Word1;

        _geometryMode = (_geometryMode & ~clearBits) | setBits;
        _gx.GeometryMode = _geometryMode;
    }

    private void HandleTexture(DisplayList.GfxCommand cmd)
    {
        // G_TEXTURE: Enable/disable texturing, set scale
        // w0: [18:16]=level [15:8]=tile [7:1]=on
    }

    private void HandleSetTImg(DisplayList.GfxCommand cmd)
    {
        // G_SETTIMG: Set texture image source
        _texImageFmt = (byte)((cmd.Word0 >> 21) & 0x07);
        _texImageSiz = (byte)((cmd.Word0 >> 19) & 0x03);
        _texImageWidth = (ushort)((cmd.Word0 & 0xFFF) + 1);
        _texImageAddr = cmd.Word1;
    }

    private void HandleSetTile(DisplayList.GfxCommand cmd)
    {
        // G_SETTILE: Configure a tile descriptor
        int tile = (int)((cmd.Word1 >> 24) & 0x07);
        _tiles[tile].Format = (byte)((cmd.Word0 >> 21) & 0x07);
        _tiles[tile].Size = (byte)((cmd.Word0 >> 19) & 0x03);
        _tiles[tile].Line = (ushort)((cmd.Word0 >> 9) & 0x1FF);
        _tiles[tile].TMemAddr = (ushort)(cmd.Word0 & 0x1FF);
        _tiles[tile].Palette = (byte)((cmd.Word1 >> 20) & 0x0F);
        _tiles[tile].ClampT = (byte)((cmd.Word1 >> 18) & 0x01);
        _tiles[tile].MirrorT = (byte)((cmd.Word1 >> 17) & 0x01);
        _tiles[tile].MaskT = (byte)((cmd.Word1 >> 14) & 0x0F);
        _tiles[tile].ShiftT = (byte)((cmd.Word1 >> 10) & 0x0F);
        _tiles[tile].ClampS = (byte)((cmd.Word1 >> 9) & 0x01);
        _tiles[tile].MirrorS = (byte)((cmd.Word1 >> 8) & 0x01);
        _tiles[tile].MaskS = (byte)((cmd.Word1 >> 4) & 0x0F);
        _tiles[tile].ShiftS = (byte)(cmd.Word1 & 0x0F);
    }

    private void HandleSetTileSize(DisplayList.GfxCommand cmd)
    {
        int tile = (int)((cmd.Word1 >> 24) & 0x07);
        _tiles[tile].ULS = (ushort)((cmd.Word0 >> 12) & 0xFFF);
        _tiles[tile].ULT = (ushort)(cmd.Word0 & 0xFFF);
        _tiles[tile].LRS = (ushort)((cmd.Word1 >> 12) & 0xFFF);
        _tiles[tile].LRT = (ushort)(cmd.Word1 & 0xFFF);
    }

    private void HandleLoadBlock(DisplayList.GfxCommand cmd)
    {
        // G_LOADBLOCK: Load texture data into TMEM
        // In a full implementation, this reads from _texImageAddr in game memory
    }

    private void HandleLoadTile(DisplayList.GfxCommand cmd)
    {
        // G_LOADTILE: Load a rectangular region of texture into TMEM
    }

    private void HandleLoadTLUT(DisplayList.GfxCommand cmd)
    {
        // G_LOADTLUT: Load a color lookup table into TMEM
    }

    private void HandleSetCombine(DisplayList.GfxCommand cmd)
    {
        // G_SETCOMBINE: Configure the color combiner
        _combineModeHi = cmd.Word0 & 0x00FFFFFF;
        _combineModeLo = cmd.Word1;
        // Map N64 combine mode to TEV stages
        MapCombineToTEV();
    }

    private void HandleSetOtherModeH(DisplayList.GfxCommand cmd)
    {
        int shift = (int)((cmd.Word0 >> 8) & 0xFF);
        int length = (int)(cmd.Word0 & 0xFF) + 1;
        uint mask = (uint)(((1L << length) - 1) << shift);
        _otherModeH = (_otherModeH & ~mask) | (cmd.Word1 & mask);
    }

    private void HandleSetOtherModeL(DisplayList.GfxCommand cmd)
    {
        int shift = (int)((cmd.Word0 >> 8) & 0xFF);
        int length = (int)(cmd.Word0 & 0xFF) + 1;
        uint mask = (uint)(((1L << length) - 1) << shift);
        _otherModeL = (_otherModeL & ~mask) | (cmd.Word1 & mask);
        ApplyOtherModeL();
    }

    private void HandleSetPrimColor(DisplayList.GfxCommand cmd)
    {
        byte r = (byte)((cmd.Word1 >> 24) & 0xFF);
        byte g = (byte)((cmd.Word1 >> 16) & 0xFF);
        byte b = (byte)((cmd.Word1 >> 8) & 0xFF);
        byte a = (byte)(cmd.Word1 & 0xFF);
        _gx.SetPrimColor(r, g, b, a);
    }

    private void HandleSetEnvColor(DisplayList.GfxCommand cmd)
    {
        byte r = (byte)((cmd.Word1 >> 24) & 0xFF);
        byte g = (byte)((cmd.Word1 >> 16) & 0xFF);
        byte b = (byte)((cmd.Word1 >> 8) & 0xFF);
        byte a = (byte)(cmd.Word1 & 0xFF);
        _gx.SetEnvColor(r, g, b, a);
    }

    private void HandleSetFogColor(DisplayList.GfxCommand cmd)
    {
        byte r = (byte)((cmd.Word1 >> 24) & 0xFF);
        byte g = (byte)((cmd.Word1 >> 16) & 0xFF);
        byte b = (byte)((cmd.Word1 >> 8) & 0xFF);
        byte a = (byte)(cmd.Word1 & 0xFF);
        _gx.SetFogColor(r, g, b, a);
    }

    private void HandleSetFillColor(DisplayList.GfxCommand cmd)
    {
        // Fill color is packed differently (RGBA 5551 x2 or RGBA32)
        uint c = cmd.Word1;
        byte r = (byte)((c >> 24) & 0xFF);
        byte g = (byte)((c >> 16) & 0xFF);
        byte b = (byte)((c >> 8) & 0xFF);
        byte a = (byte)(c & 0xFF);
        _gx.FillColor = new Color(r / 255f, g / 255f, b / 255f, a / 255f);
    }

    private void HandleSetBlendColor(DisplayList.GfxCommand cmd)
    {
        byte r = (byte)((cmd.Word1 >> 24) & 0xFF);
        byte g = (byte)((cmd.Word1 >> 16) & 0xFF);
        byte b = (byte)((cmd.Word1 >> 8) & 0xFF);
        byte a = (byte)(cmd.Word1 & 0xFF);
        _gx.BlendColor = new Color(r / 255f, g / 255f, b / 255f, a / 255f);
    }

    private void HandleFillRect(DisplayList.GfxCommand cmd)
    {
        // G_FILLRECT: Fill a rectangle with the current fill color
        int x0 = (int)((cmd.Word1 >> 12) & 0xFFF) >> 2;
        int y0 = (int)(cmd.Word1 & 0xFFF) >> 2;
        int x1 = (int)((cmd.Word0 >> 12) & 0xFFF) >> 2;
        int y1 = (int)(cmd.Word0 & 0xFFF) >> 2;

        // Create a colored rectangle using GX primitives
        _gx.Begin(GXRenderer.GXPrimitive.Quads);
        var c = _gx.FillColor;
        float z = 0;
        _gx.AddVertex(new GXRenderer.GXVertex { Position = new Vector3(x0, y0, z), Color = c });
        _gx.AddVertex(new GXRenderer.GXVertex { Position = new Vector3(x1, y0, z), Color = c });
        _gx.AddVertex(new GXRenderer.GXVertex { Position = new Vector3(x1, y1, z), Color = c });
        _gx.AddVertex(new GXRenderer.GXVertex { Position = new Vector3(x0, y1, z), Color = c });
        _gx.End();
    }

    private void HandleSetScissor(DisplayList.GfxCommand cmd)
    {
        int x0 = (int)((cmd.Word0 >> 12) & 0xFFF) >> 2;
        int y0 = (int)(cmd.Word0 & 0xFFF) >> 2;
        int x1 = (int)((cmd.Word1 >> 12) & 0xFFF) >> 2;
        int y1 = (int)(cmd.Word1 & 0xFFF) >> 2;
        _gx.SetScissor(x0, y0, x1 - x0, y1 - y0);
    }

    private void HandleDL(DisplayList.GfxCommand cmd)
    {
        // G_DL: Call or branch to another display list
        // In a full implementation, we'd read the DL from game memory at cmd.Word1
    }

    private void HandleCullDL(DisplayList.GfxCommand cmd)
    {
        // G_CULLDL: Test bounding volume visibility
        // For now, never cull (always visible)
    }

    private void HandleMoveWord(DisplayList.GfxCommand cmd)
    {
        // G_MOVEWORD: Set a word in the RSP DMEM
        // Used for fog, lights, etc.
    }

    private void HandleMoveMem(DisplayList.GfxCommand cmd)
    {
        // G_MOVEMEM: DMA data to RSP DMEM
        // Used for viewport, lights, etc.
    }

    private void MapCombineToTEV()
    {
        // Map N64 color combiner mode to TEV stages
        // This is a simplified mapping - the full implementation would need
        // to handle all combiner input/output permutations

        _gx.TEV.NumStages = 1;
        _gx.TEV.Stages[0].Enabled = true;
    }

    private void ApplyOtherModeL()
    {
        // Extract render mode bits from otherModeL
        // Blend mode, Z mode, alpha compare, etc.
        bool zUpdate = (_otherModeL & 0x00000020) != 0;
        bool zCompare = (_otherModeL & 0x00000010) != 0;
        _gx.SetDepthMode(zCompare, 3 /* LEQUAL */, zUpdate);

        // Alpha compare
        bool alphaCvg = (_otherModeL & 0x00002000) != 0;

        // Blend mode bits
        uint blendBits = (_otherModeL >> 16) & 0xFFFF;
        if (blendBits != 0)
            _gx.SetBlendMode(BlendMode.Blend, 1, 1, 0); // SRC_ALPHA, INV_SRC_ALPHA
        else
            _gx.SetBlendMode(BlendMode.None, 0, 0, 0);
    }
}
