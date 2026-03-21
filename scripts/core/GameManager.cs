using Godot;
using AnimalCrossing.Disc;
using AnimalCrossing.Graphics;
using AnimalCrossing.Input;
using AnimalCrossing.Audio;
using AnimalCrossing.Save;

namespace AnimalCrossing.Core;

/// <summary>
/// Top-level game state machine. Manages the boot sequence, scene transitions,
/// and per-frame game logic. This is the C# equivalent of graph_proc() + game_main()
/// combined with the initialization from pc_main.c's main().
///
/// Boot sequence (matching original):
///   1. Load settings
///   2. Init disc/assets
///   3. Init memory card
///   4. Init graphics (Godot handles this)
///   5. Init audio
///   6. Run scene loop: first_game → select → play
/// </summary>
public partial class GameManager : Node
{
    public enum BootStage
    {
        Uninitialized,
        LoadingDisc,
        LoadingAssets,
        InitializingAudio,
        InitializingCard,
        Running,
        ShuttingDown,
    }

    [Export] public string DiscImagePath { get; set; } = "rom";

    public BootStage CurrentStage { get; private set; } = BootStage.Uninitialized;
    public DiscReader? Disc { get; private set; }
    public AssetLoader? Assets { get; private set; }
    public GXRenderer? Renderer { get; private set; }
    public GCInput? Input { get; private set; }
    public AudioManager? Audio { get; private set; }
    public SaveManager? SaveMgr { get; private set; }
    public FrameTimer Timer { get; } = new();

    public GameState? CurrentState { get; private set; }
    public SceneDefinition? CurrentScene { get; private set; }

    public uint GameFrame { get; private set; }
    public float GameFrameF { get; private set; } = 1.0f;

    public bool Verbose { get; set; }

    public override void _Ready()
    {
        ProcessMode = ProcessModeEnum.Always;
        Timer.Start();
        Boot();
    }

    private void Boot()
    {
        GD.Print("[AC] Animal Crossing - Godot 4.6.1 C# Port");
        GD.Print("[AC] Initializing...");

        // Step 1: Find and open disc image
        CurrentStage = BootStage.LoadingDisc;
        Disc = new DiscReader();
        string? discPath = FindDiscImage();
        if (discPath != null)
        {
            if (Disc.Open(discPath))
            {
                GD.Print($"[AC] Disc image loaded: {discPath}");
            }
            else
            {
                GD.PrintErr($"[AC] Failed to open disc image: {discPath}");
                Disc = null;
            }
        }
        else
        {
            GD.PrintErr("[AC] No disc image found. Place a .ciso/.iso/.gcm file in the rom/ directory.");
        }

        // Step 2: Load assets from disc
        CurrentStage = BootStage.LoadingAssets;
        if (Disc != null)
        {
            Assets = new AssetLoader(Disc);
            Assets.LoadAll();
            GD.Print($"[AC] Assets loaded: {Assets.AssetCount} entries");
        }

        // Step 3: Initialize audio
        CurrentStage = BootStage.InitializingAudio;
        Audio = new AudioManager();
        AddChild(Audio);

        // Step 4: Initialize memory card / save system
        CurrentStage = BootStage.InitializingCard;
        SaveMgr = new SaveManager();

        // Step 5: Initialize renderer
        Renderer = new GXRenderer();
        AddChild(Renderer);

        // Step 6: Initialize input
        Input = new GCInput();
        AddChild(Input);

        // Step 7: Register scene callbacks
        RegisterScenes();

        // Step 8: Start the game at the first scene
        CurrentStage = BootStage.Running;
        TransitionToScene(SceneTable.FirstGame);

        GD.Print("[AC] Boot complete. Starting game loop.");
    }

    private void RegisterScenes()
    {
        // first_game: Title/intro sequence
        SceneTable.FirstGame.Init = state =>
        {
            GD.Print("[AC] Scene: first_game (intro)");
        };
        SceneTable.FirstGame.Execute = state =>
        {
            // Intro plays, then transitions to select screen
            // TODO: Implement intro sequence
            state.NextScene = SceneTable.Select;
        };

        // select: Title screen / demo mode
        SceneTable.Select.Init = state =>
        {
            GD.Print("[AC] Scene: select (title screen)");
        };
        SceneTable.Select.Execute = state =>
        {
            // Title screen with demo playback
            // Press Start → player_select or play
            if (Input != null && Input.IsButtonPressed(Constants.PadButtonStart))
            {
                state.NextScene = SceneTable.PlayerSelect;
            }
        };

        // player_select: Character/save selection
        SceneTable.PlayerSelect.Init = state =>
        {
            GD.Print("[AC] Scene: player_select");
        };
        SceneTable.PlayerSelect.Execute = state =>
        {
            // Player selects a save file
            // TODO: Implement player selection
            if (Input != null && Input.IsButtonPressed(Constants.PadButtonA))
            {
                state.NextScene = SceneTable.Play;
            }
        };

        // play: Main gameplay
        SceneTable.Play.Init = state =>
        {
            GD.Print("[AC] Scene: play (main gameplay)");
        };
        SceneTable.Play.Execute = state =>
        {
            // Main gameplay loop - the bulk of the game
            // TODO: Implement gameplay systems (actors, NPCs, items, etc.)
        };

        // trademark: Nintendo logo display
        SceneTable.Trademark.Init = state =>
        {
            GD.Print("[AC] Scene: trademark (Nintendo logo)");
        };
        SceneTable.Trademark.Execute = state =>
        {
            state.NextScene = SceneTable.Select;
        };
    }

    public void TransitionToScene(SceneDefinition scene)
    {
        // Cleanup old scene
        if (CurrentState != null)
        {
            CurrentScene?.Cleanup?.Invoke(CurrentState);
            CurrentState.Dispose();
        }

        // Create new scene state
        CurrentScene = scene;
        CurrentState = new GameState(scene);
        scene.Init?.Invoke(CurrentState);

        GD.Print($"[AC] Transitioned to scene: {scene.Name}");
    }

    public override void _Process(double delta)
    {
        if (CurrentStage != BootStage.Running || CurrentState == null || CurrentScene == null)
            return;

        // Update input
        Input?.Poll(CurrentState.Pads);

        // Run scene logic
        CurrentScene.Execute?.Invoke(CurrentState);

        // Check for scene transition
        if (CurrentState.NextScene != null)
        {
            var nextScene = CurrentState.NextScene;
            CurrentState.NextScene = null;
            TransitionToScene(nextScene);
            return;
        }

        // Increment game frame
        GameFrame++;

        // Update window title with FPS
        Timer.WaitForRetrace();
        if (Timer.FrameCounter % 60 == 0)
        {
            DisplayServer.WindowSetTitle($"Animal Crossing - {Timer.CurrentFps:F1} FPS");
        }
    }

    private string? FindDiscImage()
    {
        // Search for disc image in common locations
        string[] searchDirs = { "rom", "orig", "." };
        string[] extensions = { "*.ciso", "*.iso", "*.gcm" };

        foreach (string dir in searchDirs)
        {
            string searchDir = System.IO.Path.IsPathRooted(dir) ? dir :
                System.IO.Path.Combine(OS.GetExecutablePath().GetBaseDir(), dir);

            if (!System.IO.Directory.Exists(searchDir))
            {
                // Also try relative to project directory
                searchDir = System.IO.Path.Combine(ProjectSettings.GlobalizePath("res://"), dir);
                if (!System.IO.Directory.Exists(searchDir))
                    continue;
            }

            foreach (string ext in extensions)
            {
                string[] files = System.IO.Directory.GetFiles(searchDir, ext);
                if (files.Length > 0)
                    return files[0];
            }
        }

        return null;
    }

    public override void _ExitTree()
    {
        CurrentStage = BootStage.ShuttingDown;
        CurrentState?.Dispose();
        Disc?.Close();
        GD.Print("[AC] Shutdown complete.");
    }
}
