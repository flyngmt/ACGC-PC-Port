using System.Diagnostics;

namespace AnimalCrossing.Core;

/// <summary>
/// Frame timing and pacing, equivalent to pc_vi.c.
/// Manages the 60 FPS game clock, retrace counting, and frame skip detection.
/// </summary>
public class FrameTimer
{
    private readonly Stopwatch _stopwatch = new();
    private long _frameStartTicks;
    private int _fpsFrameCount;
    private long _fpsStartTicks;

    /// <summary>Number of vertical retrace intervals elapsed (increments each frame).</summary>
    public uint RetraceCount { get; private set; }

    /// <summary>Total frames rendered.</summary>
    public uint FrameCounter { get; private set; }

    /// <summary>Current measured FPS.</summary>
    public double CurrentFps { get; private set; } = 60.0;

    /// <summary>Last frame time in milliseconds.</summary>
    public double LastFrameMs { get; private set; }

    /// <summary>Whether the frame limiter is disabled (unlocked FPS).</summary>
    public bool NoFrameLimit { get; set; }

    /// <summary>Game frame counter used by game logic (can differ from FrameCounter).</summary>
    public uint GameFrame { get; set; }

    /// <summary>Game frame counter as float (for interpolation).</summary>
    public float GameFrameF { get; set; } = 1.0f;

    public void Start()
    {
        _stopwatch.Start();
        _frameStartTicks = _stopwatch.ElapsedTicks;
        _fpsStartTicks = _frameStartTicks;
    }

    /// <summary>
    /// Called at the end of each frame. Handles frame pacing (spin-wait to 60 FPS)
    /// and FPS measurement. Equivalent to VIWaitForRetrace().
    /// </summary>
    public void WaitForRetrace()
    {
        long now = _stopwatch.ElapsedTicks;
        double freq = Stopwatch.Frequency;

        // Measure frame time
        if (_frameStartTicks > 0)
        {
            LastFrameMs = (now - _frameStartTicks) * 1000.0 / freq;
        }

        // Frame pacing: spin-wait until 16.667ms has elapsed
        if (!NoFrameLimit && _frameStartTicks > 0)
        {
            double targetUs = Constants.FrameTimeUs;
            while (true)
            {
                now = _stopwatch.ElapsedTicks;
                double elapsedUs = (now - _frameStartTicks) * 1_000_000.0 / freq;
                if (elapsedUs >= targetUs)
                    break;

                double remainUs = targetUs - elapsedUs;
                if (remainUs > 2000)
                    System.Threading.Thread.Sleep(1);
            }
        }

        // FPS counter (update every 60 frames)
        _fpsFrameCount++;
        if (_fpsFrameCount >= 60)
        {
            now = _stopwatch.ElapsedTicks;
            double secs = (now - _fpsStartTicks) / freq;
            CurrentFps = _fpsFrameCount / secs;
            _fpsStartTicks = now;
            _fpsFrameCount = 0;
        }

        _frameStartTicks = _stopwatch.ElapsedTicks;
        RetraceCount++;
        FrameCounter++;
    }

    /// <summary>
    /// Set the game frame rate multiplier. Called by SetGameFrame() in the original.
    /// Normal = 1.0, double-speed = 2.0, etc.
    /// </summary>
    public void SetGameFrame(float rate)
    {
        GameFrameF = rate;
    }
}
