using AnimalCrossing.Input;
using AnimalCrossing.Memory;

namespace AnimalCrossing.Core;

/// <summary>
/// Represents the state of a single game scene, equivalent to the GAME struct
/// in the original decomp. Each scene (title, gameplay, save menu, etc.)
/// gets its own GameState instance with isolated memory.
/// </summary>
public class GameState
{
    /// <summary>Current controller input for all 4 ports.</summary>
    public PadStatus[] Pads { get; } = new PadStatus[Constants.MaxControllers];

    /// <summary>Scene-local memory arena (Hyral/THA allocator).</summary>
    public ArenaAllocator Arena { get; }

    /// <summary>The scene definition that created this state.</summary>
    public SceneDefinition Scene { get; }

    /// <summary>Whether this scene is still active.</summary>
    public bool IsRunning { get; set; } = true;

    /// <summary>Whether rendering should be skipped this frame.</summary>
    public bool DisableDisplay { get; set; }

    /// <summary>The next scene to transition to, or null if staying.</summary>
    public SceneDefinition? NextScene { get; set; }

    /// <summary>Debug state tracking for crash diagnostics.</summary>
    public int DoingPoint { get; set; }

    public GameState(SceneDefinition scene, int arenaSize = Constants.DefaultHyralSize)
    {
        Scene = scene;
        Arena = new ArenaAllocator(arenaSize);
        for (int i = 0; i < Pads.Length; i++)
            Pads[i] = new PadStatus();
    }

    public void Dispose()
    {
        Arena.Dispose();
    }
}
