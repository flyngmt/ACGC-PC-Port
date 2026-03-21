using System;
using System.Collections.Generic;
using Godot;
using AnimalCrossing.Core;

namespace AnimalCrossing.Graphics;

/// <summary>
/// GX (GameCube Graphics API) renderer implementation using Godot's rendering system.
/// Replaces the OpenGL-based pc_gx.c with Godot-native rendering.
///
/// The original rendering pipeline: Game code → N64 display lists → emu64 interpreter → GX API → OpenGL
/// New pipeline: Game code → N64 display lists → Emu64 interpreter → GXRenderer → Godot RenderingServer
///
/// GX state machine manages:
///   - Vertex format and submission
///   - Matrix stack (projection + modelview)
///   - TEV combiner stages
///   - Texture binding and configuration
///   - Blending, depth test, culling, scissor
///   - Lighting (ambient + directional)
///   - Fog
/// </summary>
public partial class GXRenderer : Node3D
{
    // Matrix stacks
    private readonly Stack<Transform3D> _projStack = new();
    private readonly Stack<Transform3D> _mvStack = new();
    private Transform3D _projection = Transform3D.Identity;
    private Transform3D _modelView = Transform3D.Identity;

    // TEV state
    public TEVState TEV { get; } = new();

    // Blend / depth
    public BlendMode Blend;
    public DepthMode Depth;

    // Geometry mode flags
    public uint GeometryMode { get; set; }

    // Scissor
    public Rect2I Scissor { get; set; } = new(0, 0, Constants.GCWidth, Constants.GCHeight);

    // Viewport
    public Rect2I Viewport { get; set; } = new(0, 0, Constants.GCWidth, Constants.GCHeight);

    // Current vertex buffer for primitive assembly
    private readonly List<GXVertex> _vertices = new();
    private GXPrimitive _currentPrimitive = GXPrimitive.None;

    // Texture cache
    private readonly Dictionary<ulong, ImageTexture> _textureCache = new();

    // Lighting
    public struct Light
    {
        public Vector3 Direction;
        public Color Color;
        public bool Enabled;
    }

    public Color AmbientColor { get; set; } = new(0.2f, 0.2f, 0.2f, 1.0f);
    public Light[] Lights { get; } = new Light[8];

    // Fill color (for rectangle fills)
    public Color FillColor { get; set; }
    public Color FogColor { get; set; }
    public Color PrimColor { get; set; } = Colors.White;
    public Color EnvColor { get; set; } = Colors.White;
    public Color BlendColor { get; set; }

    // Collected meshes for this frame
    private readonly List<MeshData> _frameMeshes = new();

    public struct GXVertex
    {
        public Vector3 Position;
        public Vector3 Normal;
        public Color Color;
        public Vector2 TexCoord0;
        public Vector2 TexCoord1;
    }

    public enum GXPrimitive
    {
        None = 0,
        Quads = 0x80,
        Triangles = 0x90,
        TriangleStrip = 0x98,
        TriangleFan = 0xA0,
        Lines = 0xA8,
        LineStrip = 0xB0,
        Points = 0xB8,
    }

    private struct MeshData
    {
        public ArrayMesh Mesh;
        public Transform3D Transform;
        public StandardMaterial3D Material;
    }

    public override void _Ready()
    {
        TEV.Reset();
        Depth = new DepthMode { TestEnable = true, CompareFunc = 3, WriteEnable = true };
    }

    // --- Matrix operations ---

    public void SetProjection(float[] mtx4x4)
    {
        _projection = MatrixFromArray(mtx4x4);
    }

    public void SetModelView(float[] mtx4x4)
    {
        _modelView = MatrixFromArray(mtx4x4);
    }

    public void PushMatrix()
    {
        _mvStack.Push(_modelView);
    }

    public void PopMatrix()
    {
        if (_mvStack.Count > 0)
            _modelView = _mvStack.Pop();
    }

    public void MultiplyMatrix(float[] mtx4x4)
    {
        _modelView *= MatrixFromArray(mtx4x4);
    }

    // --- Primitive submission ---

    public void Begin(GXPrimitive primitive)
    {
        _currentPrimitive = primitive;
        _vertices.Clear();
    }

    public void AddVertex(GXVertex vertex)
    {
        _vertices.Add(vertex);
    }

    public void End()
    {
        if (_vertices.Count == 0 || _currentPrimitive == GXPrimitive.None)
            return;

        FlushPrimitive();
        _currentPrimitive = GXPrimitive.None;
    }

    // --- Texture management ---

    public void BindTexture(int unit, ImageTexture? texture)
    {
        // Textures are applied through materials when creating meshes
    }

    public ImageTexture? DecodeAndCacheTexture(byte[] data, int width, int height,
                                                TextureDecoder.GXTexFmt format,
                                                byte[]? palette = null)
    {
        // Simple hash for cache lookup
        ulong hash = ComputeHash(data);
        if (_textureCache.TryGetValue(hash, out var cached))
            return cached;

        var tex = TextureDecoder.CreateTexture(data, width, height, format, palette);
        _textureCache[hash] = tex;
        return tex;
    }

    // --- GX state setters (called by Emu64 interpreter) ---

    public void SetGeometryMode(uint mode)
    {
        GeometryMode |= mode;
    }

    public void ClearGeometryMode(uint mode)
    {
        GeometryMode &= ~mode;
    }

    public void SetScissor(int x, int y, int w, int h)
    {
        Scissor = new Rect2I(x, y, w, h);
    }

    public void SetViewport(int x, int y, int w, int h)
    {
        Viewport = new Rect2I(x, y, w, h);
    }

    public void SetBlendMode(byte type, byte src, byte dst, byte logicOp)
    {
        Blend = new BlendMode { Type = type, SrcFactor = src, DstFactor = dst, LogicOp = logicOp };
    }

    public void SetDepthMode(bool testEnable, byte compareFunc, bool writeEnable)
    {
        Depth = new DepthMode { TestEnable = testEnable, CompareFunc = compareFunc, WriteEnable = writeEnable };
    }

    public void SetFogColor(byte r, byte g, byte b, byte a)
    {
        FogColor = new Color(r / 255f, g / 255f, b / 255f, a / 255f);
    }

    public void SetPrimColor(byte r, byte g, byte b, byte a)
    {
        PrimColor = new Color(r / 255f, g / 255f, b / 255f, a / 255f);
        TEV.Registers[2] = PrimColor; // REG1 = PRIM
    }

    public void SetEnvColor(byte r, byte g, byte b, byte a)
    {
        EnvColor = new Color(r / 255f, g / 255f, b / 255f, a / 255f);
        TEV.Registers[3] = EnvColor; // REG2 = ENV
    }

    // --- Frame management ---

    public void BeginFrame()
    {
        _frameMeshes.Clear();
    }

    public void EndFrame()
    {
        // Render all collected meshes
        // In Godot, this is handled by the scene tree automatically
        // The meshes added as children will be rendered by the engine
    }

    // --- Internal ---

    private void FlushPrimitive()
    {
        // Convert the vertex buffer to a Godot mesh based on primitive type
        var arrays = new Godot.Collections.Array();
        arrays.Resize((int)Mesh.ArrayType.Max);

        var positions = new Vector3[_vertices.Count];
        var normals = new Vector3[_vertices.Count];
        var colors = new Color[_vertices.Count];
        var uvs = new Vector2[_vertices.Count];

        for (int i = 0; i < _vertices.Count; i++)
        {
            positions[i] = _vertices[i].Position;
            normals[i] = _vertices[i].Normal;
            colors[i] = _vertices[i].Color;
            uvs[i] = _vertices[i].TexCoord0;
        }

        arrays[(int)Mesh.ArrayType.Vertex] = positions;
        arrays[(int)Mesh.ArrayType.Normal] = normals;
        arrays[(int)Mesh.ArrayType.Color] = colors;
        arrays[(int)Mesh.ArrayType.TexUV] = uvs;

        // Generate indices based on primitive type
        int[] indices = GenerateIndices();
        if (indices.Length == 0) return;
        arrays[(int)Mesh.ArrayType.Index] = indices;

        var mesh = new ArrayMesh();
        mesh.AddSurfaceFromArrays(Mesh.PrimitiveType.Triangles, arrays);

        // Create material from current TEV state
        var material = CreateMaterialFromTEV();
        mesh.SurfaceSetMaterial(0, material);

        // Add as child MeshInstance3D
        var instance = new MeshInstance3D
        {
            Mesh = mesh,
            Transform = _modelView,
        };
        AddChild(instance);
    }

    private int[] GenerateIndices()
    {
        switch (_currentPrimitive)
        {
            case GXPrimitive.Triangles:
                {
                    int[] idx = new int[_vertices.Count];
                    for (int i = 0; i < idx.Length; i++) idx[i] = i;
                    return idx;
                }
            case GXPrimitive.Quads:
                {
                    int quadCount = _vertices.Count / 4;
                    int[] idx = new int[quadCount * 6];
                    for (int i = 0; i < quadCount; i++)
                    {
                        idx[i * 6 + 0] = i * 4 + 0;
                        idx[i * 6 + 1] = i * 4 + 1;
                        idx[i * 6 + 2] = i * 4 + 2;
                        idx[i * 6 + 3] = i * 4 + 0;
                        idx[i * 6 + 4] = i * 4 + 2;
                        idx[i * 6 + 5] = i * 4 + 3;
                    }
                    return idx;
                }
            case GXPrimitive.TriangleStrip:
                {
                    if (_vertices.Count < 3) return Array.Empty<int>();
                    int triCount = _vertices.Count - 2;
                    int[] idx = new int[triCount * 3];
                    for (int i = 0; i < triCount; i++)
                    {
                        if (i % 2 == 0)
                        {
                            idx[i * 3 + 0] = i;
                            idx[i * 3 + 1] = i + 1;
                            idx[i * 3 + 2] = i + 2;
                        }
                        else
                        {
                            idx[i * 3 + 0] = i + 1;
                            idx[i * 3 + 1] = i;
                            idx[i * 3 + 2] = i + 2;
                        }
                    }
                    return idx;
                }
            case GXPrimitive.TriangleFan:
                {
                    if (_vertices.Count < 3) return Array.Empty<int>();
                    int triCount = _vertices.Count - 2;
                    int[] idx = new int[triCount * 3];
                    for (int i = 0; i < triCount; i++)
                    {
                        idx[i * 3 + 0] = 0;
                        idx[i * 3 + 1] = i + 1;
                        idx[i * 3 + 2] = i + 2;
                    }
                    return idx;
                }
            default:
                return Array.Empty<int>();
        }
    }

    private StandardMaterial3D CreateMaterialFromTEV()
    {
        var mat = new StandardMaterial3D
        {
            VertexColorUseAsAlbedo = true,
            ShadingMode = BaseMaterial3D.ShadingModeEnum.Unshaded,
        };

        // Apply blend mode
        if (Blend.Type == BlendMode.Blend)
        {
            mat.Transparency = BaseMaterial3D.TransparencyEnum.Alpha;
        }

        // Apply cull mode from geometry flags
        if ((GeometryMode & Constants.GCullBack) != 0 && (GeometryMode & Constants.GCullFront) != 0)
            mat.CullMode = BaseMaterial3D.CullModeEnum.Disabled;
        else if ((GeometryMode & Constants.GCullFront) != 0)
            mat.CullMode = BaseMaterial3D.CullModeEnum.Front;
        else if ((GeometryMode & Constants.GCullBack) != 0)
            mat.CullMode = BaseMaterial3D.CullModeEnum.Back;
        else
            mat.CullMode = BaseMaterial3D.CullModeEnum.Disabled;

        // Apply depth
        mat.DepthDrawMode = Depth.WriteEnable
            ? BaseMaterial3D.DepthDrawModeEnum.Always
            : BaseMaterial3D.DepthDrawModeEnum.Disabled;
        mat.NoDepthTest = !Depth.TestEnable;

        return mat;
    }

    /// <summary>Clear all child mesh instances (call at start of each frame).</summary>
    public void ClearFrame()
    {
        foreach (var child in GetChildren())
        {
            if (child is MeshInstance3D)
            {
                child.QueueFree();
            }
        }
    }

    private static Transform3D MatrixFromArray(float[] m)
    {
        if (m.Length < 16) return Transform3D.Identity;
        return new Transform3D(
            new Vector3(m[0], m[1], m[2]),
            new Vector3(m[4], m[5], m[6]),
            new Vector3(m[8], m[9], m[10]),
            new Vector3(m[12], m[13], m[14])
        );
    }

    private static ulong ComputeHash(byte[] data)
    {
        // FNV-1a hash (matching the original's hash algorithm)
        ulong hash = 14695981039346656037;
        foreach (byte b in data)
        {
            hash ^= b;
            hash *= 1099511628211;
        }
        return hash;
    }
}
