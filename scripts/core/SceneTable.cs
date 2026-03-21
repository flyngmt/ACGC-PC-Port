using System;
using System.Collections.Generic;

namespace AnimalCrossing.Core;

/// <summary>
/// Defines a game scene with its initialization, execution, and cleanup callbacks.
/// Equivalent to DLFTBL_GAME in the original decomp.
/// </summary>
public class SceneDefinition
{
    public string Name { get; }
    public int Index { get; }
    public int GameStructSize { get; }
    public Action<GameState>? Init { get; set; }
    public Action<GameState>? Execute { get; set; }
    public Action<GameState>? Cleanup { get; set; }

    public SceneDefinition(string name, int index, int gameStructSize = 0)
    {
        Name = name;
        Index = index;
        GameStructSize = gameStructSize;
    }
}

/// <summary>
/// Registry of all game scenes, equivalent to game_dlftbls[] in the decomp.
/// Scene transitions are driven by setting NextScene on the current GameState.
/// </summary>
public static class SceneTable
{
    public static SceneDefinition FirstGame { get; } = new("first_game", Constants.SceneFirstGame);
    public static SceneDefinition SecondGame { get; } = new("second_game", Constants.SceneSecondGame);
    public static SceneDefinition Trademark { get; } = new("trademark", Constants.SceneTrademark);
    public static SceneDefinition Select { get; } = new("select", Constants.SceneSelect);
    public static SceneDefinition Play { get; } = new("play", Constants.ScenePlay);
    public static SceneDefinition ModelViewer { get; } = new("model_viewer", Constants.SceneModelViewer);
    public static SceneDefinition PlayerSelect { get; } = new("player_select", Constants.ScenePlayerSelect);

    private static readonly Dictionary<int, SceneDefinition> _byIndex = new()
    {
        [Constants.SceneFirstGame] = FirstGame,
        [Constants.SceneSecondGame] = SecondGame,
        [Constants.SceneTrademark] = Trademark,
        [Constants.SceneSelect] = Select,
        [Constants.ScenePlay] = Play,
        [Constants.SceneModelViewer] = ModelViewer,
        [Constants.ScenePlayerSelect] = PlayerSelect,
    };

    public static SceneDefinition? GetByIndex(int index)
    {
        return _byIndex.GetValueOrDefault(index);
    }

    public static IEnumerable<SceneDefinition> All => _byIndex.Values;
}
