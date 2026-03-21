using Godot;

namespace AnimalCrossing.Graphics;

/// <summary>
/// TEV (Texture Environment) combiner state, equivalent to the GX TEV pipeline.
/// The GameCube's TEV unit performs per-pixel color/alpha combining with up to 16 stages.
/// Animal Crossing uses up to 3 stages.
///
/// Each stage combines inputs (texture, vertex color, constants) using configurable
/// operations (add, subtract, multiply) to produce the final pixel color.
/// </summary>
public class TEVState
{
    public const int MaxStages = 3;
    public const int MaxTextures = 8;

    /// <summary>TEV stage configuration.</summary>
    public struct Stage
    {
        // Color combiner inputs: a, b, c, d → output = (d + lerp(a, b, c)) * scale + bias
        public byte ColorA, ColorB, ColorC, ColorD;
        public byte ColorOp, ColorBias, ColorScale;
        public bool ColorClamp;
        public byte ColorOutReg;

        // Alpha combiner (same structure)
        public byte AlphaA, AlphaB, AlphaC, AlphaD;
        public byte AlphaOp, AlphaBias, AlphaScale;
        public bool AlphaClamp;
        public byte AlphaOutReg;

        // Texture and color channel bindings
        public byte TexMap;      // Which texture unit (0-7)
        public byte TexCoordId;  // Which texcoord set
        public byte ColorChanId; // Which color channel (vertex color)

        // Indirect texture
        public byte IndTexStage;
        public byte IndTexFormat;
        public byte IndTexBias;
        public byte IndTexMtxId;
        public byte IndTexWrapS, IndTexWrapT;
        public bool IndTexAddPrev;

        public bool Enabled;
    }

    /// <summary>Alpha compare configuration (for alpha testing).</summary>
    public struct AlphaCompare
    {
        public byte Func0;
        public byte Ref0;
        public byte Op;
        public byte Func1;
        public byte Ref1;
    }

    /// <summary>Fog configuration.</summary>
    public struct FogConfig
    {
        public byte Type;
        public float StartZ, EndZ;
        public float NearZ, FarZ;
        public Color Color;
        public bool Enabled;
    }

    public Stage[] Stages { get; } = new Stage[MaxStages];
    public int NumStages { get; set; } = 1;

    // TEV registers: PREV (output), REG0, REG1 (=PRIM), REG2 (=ENV)
    public Color[] Registers { get; } = new Color[4];
    public Color[] KonstColors { get; } = new Color[4];

    // Alpha compare
    public AlphaCompare AlphaComp;

    // Fog
    public FogConfig Fog;

    // Swap tables (remap RGBA channels per stage)
    public byte[,] SwapTable { get; } = new byte[4, 4];

    public TEVState()
    {
        // Default swap table: identity
        for (int i = 0; i < 4; i++)
        {
            SwapTable[i, 0] = 0; // R
            SwapTable[i, 1] = 1; // G
            SwapTable[i, 2] = 2; // B
            SwapTable[i, 3] = 3; // A
        }

        // Default TEV register colors
        Registers[0] = new Color(0, 0, 0, 0); // PREV
        Registers[1] = new Color(0, 0, 0, 0); // REG0
        Registers[2] = new Color(1, 1, 1, 1); // REG1/PRIM (white)
        Registers[3] = new Color(1, 1, 1, 1); // REG2/ENV (white)
    }

    /// <summary>Reset to default state.</summary>
    public void Reset()
    {
        NumStages = 1;
        for (int i = 0; i < MaxStages; i++)
        {
            Stages[i] = new Stage { Enabled = false };
        }
        Stages[0].Enabled = true;
        // Default stage 0: output = texture * vertex color
        Stages[0].ColorA = 0; // PREV
        Stages[0].ColorB = 0;
        Stages[0].ColorC = 0;
        Stages[0].ColorD = 0; // PREV
    }
}

/// <summary>
/// GX blend mode configuration.
/// </summary>
public struct BlendMode
{
    public byte Type;      // GX_BM_NONE, GX_BM_BLEND, GX_BM_LOGIC, GX_BM_SUBTRACT
    public byte SrcFactor; // GX_BL_SRCALPHA, etc.
    public byte DstFactor; // GX_BL_INVSRCALPHA, etc.
    public byte LogicOp;

    // GX blend type constants
    public const byte None = 0;
    public const byte Blend = 1;
    public const byte Logic = 2;
    public const byte Subtract = 3;
}

/// <summary>
/// GX depth (Z-buffer) configuration.
/// </summary>
public struct DepthMode
{
    public bool TestEnable;
    public byte CompareFunc; // GX_LEQUAL, etc.
    public bool WriteEnable;
}
