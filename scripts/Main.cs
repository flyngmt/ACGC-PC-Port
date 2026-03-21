using Godot;
using AnimalCrossing.Core;

namespace AnimalCrossing;

/// <summary>
/// Main scene controller. Entry point for the Godot application.
/// Creates and manages the GameManager which drives the entire game.
///
/// Scene hierarchy:
///   Main (Node3D) ← this script
///     ├── Camera3D         - Game camera (controlled by game logic)
///     ├── DirectionalLight - Scene lighting
///     ├── WorldEnvironment - Rendering environment
///     ├── UI (CanvasLayer) - HUD overlay
///     │   ├── DebugLabel   - Debug info display
///     │   └── FPSLabel     - FPS counter
///     └── GameManager      - Core game logic (added at runtime)
///         ├── GXRenderer   - Graphics system
///         ├── GCInput      - Input system
///         └── AudioManager - Audio system
/// </summary>
public partial class Main : Node3D
{
    private GameManager? _gameManager;
    private Label? _debugLabel;
    private Label? _fpsLabel;
    private Camera3D? _camera;

    public override void _Ready()
    {
        // Get UI references
        _debugLabel = GetNode<Label>("UI/DebugLabel");
        _fpsLabel = GetNode<Label>("UI/FPSLabel");
        _camera = GetNode<Camera3D>("Camera3D");

        // Create and add GameManager
        _gameManager = new GameManager();
        AddChild(_gameManager);

        _debugLabel.Text = "Animal Crossing - Godot 4.6.1 C# Port\nInitializing...";

        GD.Print("[MAIN] Scene ready. GameManager created.");
    }

    public override void _Process(double delta)
    {
        // Update FPS display
        if (_fpsLabel != null && _gameManager != null)
        {
            _fpsLabel.Text = $"{_gameManager.Timer.CurrentFps:F1} FPS";
        }

        // Update debug info
        if (_debugLabel != null && _gameManager != null)
        {
            string sceneName = _gameManager.CurrentScene?.Name ?? "none";
            string stage = _gameManager.CurrentStage.ToString();
            _debugLabel.Text = $"Scene: {sceneName}\nState: {stage}\nFrame: {_gameManager.GameFrame}";
        }

        // Toggle frame limiter with F3
        if (Godot.Input.IsActionJustPressed("toggle_framelimit") && _gameManager != null)
        {
            _gameManager.Timer.NoFrameLimit = !_gameManager.Timer.NoFrameLimit;
            GD.Print($"[MAIN] Frame limiter: {(_gameManager.Timer.NoFrameLimit ? "OFF" : "ON")}");
        }

        // Quit on Escape
        if (Godot.Input.IsKeyPressed(Key.Escape))
        {
            GetTree().Quit();
        }
    }

    public override void _ExitTree()
    {
        GD.Print("[MAIN] Exiting.");
    }
}
