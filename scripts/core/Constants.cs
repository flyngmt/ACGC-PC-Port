namespace AnimalCrossing.Core;

/// <summary>
/// Global constants matching the original GameCube hardware and game parameters.
/// </summary>
public static class Constants
{
    // Display
    public const int GCWidth = 640;
    public const int GCHeight = 480;
    public const int FramesPerSecond = 60;
    public const double FrameTimeUs = 16667.0; // microseconds per frame at 60Hz

    // GameCube hardware clocks
    public const uint BusClock = 162000000;
    public const uint CoreClock = 486000000;
    public const uint TimerClock = BusClock / 4;

    // Memory sizes
    public const int MainMemorySize = 24 * 1024 * 1024;  // 24 MB
    public const int ARAMSize = 16 * 1024 * 1024;         // 16 MB
    public const int FIFOSize = 256 * 1024;                // 256 KB
    public const int DefaultHyralSize = 256 * 1024;        // 256 KB scene arena

    // Audio
    public const int AudioSampleRate = 32000;
    public const int AudioChannels = 2;
    public const int AudioRingBufferSamples = 32768;

    // Controller
    public const int MaxControllers = 4;
    public const int StickMagnitude = 80;
    public const int AxisDeadzone = 4000;
    public const int TriggerThreshold = 100;

    // GC button masks (matching PAD defines)
    public const ushort PadButtonLeft   = 0x0001;
    public const ushort PadButtonRight  = 0x0002;
    public const ushort PadButtonDown   = 0x0004;
    public const ushort PadButtonUp     = 0x0008;
    public const ushort PadTriggerZ     = 0x0010;
    public const ushort PadTriggerR     = 0x0020;
    public const ushort PadTriggerL     = 0x0040;
    public const ushort PadButtonA      = 0x0100;
    public const ushort PadButtonB      = 0x0200;
    public const ushort PadButtonX      = 0x0400;
    public const ushort PadButtonY      = 0x0800;
    public const ushort PadButtonStart  = 0x1000;

    // N64 geometry mode flags
    public const uint GZBuffer         = 0x00000001;
    public const uint GTextureEnable   = 0x00000002;
    public const uint GShade           = 0x00000004;
    public const uint GShadingSmooth   = 0x00200000;
    public const uint GCullFront       = 0x00000200;
    public const uint GCullBack        = 0x00000400;
    public const uint GFog             = 0x00010000;
    public const uint GLighting        = 0x00020000;
    public const uint GTextureGen      = 0x00040000;

    // GC epoch: January 1, 2000 00:00:00 UTC
    public static readonly System.DateTime GCEpoch = new(2000, 1, 1, 0, 0, 0, System.DateTimeKind.Utc);

    // Disc formats
    public const uint CISOHeaderSize = 0x8000;
    public const uint CISOBlockSize = 0x100000; // 1 MB
    public const uint CISOMagic = 0x4349534F; // "CISO"

    // Scene indices
    public const int SceneFirstGame = 0;
    public const int SceneSecondGame = 1;
    public const int SceneTrademark = 2;
    public const int SceneSelect = 3;
    public const int ScenePlay = 7;
    public const int SceneModelViewer = 10;
    public const int ScenePlayerSelect = 19;
}
