using System;
using System.Collections.Generic;
using Godot;
using AnimalCrossing.Core;

namespace AnimalCrossing.Audio;

/// <summary>
/// Audio system using Godot's AudioServer and AudioStreamPlayer nodes.
/// Replaces the SDL2 audio backend (pc_audio.c) and jaudio_NES engine.
///
/// The original audio architecture:
///   Game thread  → Na_GameFrame() queues audio commands via message queues
///   Audio thread → Processes commands, produces PCM samples into ring buffer
///   SDL callback → Reads ring buffer, feeds to speakers
///
/// Godot equivalent:
///   Game frame → Process audio commands
///   AudioStreamGenerator → Generate PCM samples
///   Godot AudioServer → Output to speakers
///
/// The game's audio engine (jaudio_NES) synthesizes audio from:
///   - Music sequences (MIDI-like format with custom instruments)
///   - Sound effects (triggered by game events)
///   - Ambient sounds (environmental audio)
///   - NES emulator audio (for in-game NES games)
/// </summary>
public partial class AudioManager : Node
{
    private AudioStreamPlayer? _musicPlayer;
    private AudioStreamPlayer? _sfxPlayer;
    private AudioStreamPlayer? _ambientPlayer;

    // PCM generation for jaudio output
    private AudioStreamGenerator? _generatorStream;
    private AudioStreamGeneratorPlayback? _generatorPlayback;

    // Ring buffer for sample generation (matching original architecture)
    private readonly short[] _ringBuffer = new short[Constants.AudioRingBufferSamples];
    private int _writePos;
    private int _readPos;

    // Audio state
    public bool IsInitialized { get; private set; }
    public float MasterVolume { get; set; } = 1.0f;
    public float MusicVolume { get; set; } = 1.0f;
    public float SfxVolume { get; set; } = 1.0f;

    // DSP sample rate
    private uint _dspSampleRate = (uint)Constants.AudioSampleRate;

    // Sound effect pool
    private readonly Dictionary<int, AudioStreamWav> _sfxCache = new();

    public override void _Ready()
    {
        InitAudioPlayers();
        IsInitialized = true;
        GD.Print("[AUDIO] Initialized");
    }

    private void InitAudioPlayers()
    {
        // Music player using AudioStreamGenerator for PCM output
        _generatorStream = new AudioStreamGenerator
        {
            MixRate = Constants.AudioSampleRate,
            BufferLength = 0.1f, // 100ms buffer
        };

        _musicPlayer = new AudioStreamPlayer
        {
            Stream = _generatorStream,
            Bus = "Master",
        };
        AddChild(_musicPlayer);

        // SFX player
        _sfxPlayer = new AudioStreamPlayer
        {
            Bus = "Master",
        };
        AddChild(_sfxPlayer);

        // Ambient player
        _ambientPlayer = new AudioStreamPlayer
        {
            Bus = "Master",
        };
        AddChild(_ambientPlayer);
    }

    /// <summary>
    /// Start audio playback. Called after game initialization.
    /// Equivalent to AIStartDMA().
    /// </summary>
    public void StartPlayback()
    {
        _musicPlayer?.Play();
        _generatorPlayback = (AudioStreamGeneratorPlayback?)_musicPlayer?.GetStreamPlayback();
    }

    /// <summary>
    /// Stop audio playback.
    /// Equivalent to AIStopDMA().
    /// </summary>
    public void StopPlayback()
    {
        _musicPlayer?.Stop();
        _generatorPlayback = null;
    }

    /// <summary>
    /// Feed PCM samples from the game's audio engine into the generator.
    /// Called by the game's audio processing (equivalent to AIInitDMA).
    /// </summary>
    public void FeedSamples(short[] samples, int count)
    {
        if (_generatorPlayback == null) return;

        int framesToPush = count / 2; // stereo → frame count
        int framesAvailable = _generatorPlayback.GetFramesAvailable();
        int toPush = Math.Min(framesToPush, framesAvailable);

        for (int i = 0; i < toPush; i++)
        {
            int idx = i * 2;
            if (idx + 1 < samples.Length)
            {
                float left = samples[idx] / 32768f * MasterVolume;
                float right = samples[idx + 1] / 32768f * MasterVolume;
                _generatorPlayback.PushFrame(new Vector2(left, right));
            }
        }
    }

    /// <summary>
    /// Process one audio frame. Called by the game loop.
    /// In the original, this runs on a separate audio producer thread.
    /// </summary>
    public void ProcessFrame()
    {
        // This would call into the jaudio_NES engine to produce samples
        // For now, push silence if the generator needs data
        if (_generatorPlayback == null) return;

        int available = _generatorPlayback.GetFramesAvailable();
        for (int i = 0; i < available; i++)
        {
            _generatorPlayback.PushFrame(Vector2.Zero);
        }
    }

    /// <summary>Get the current buffer fill level (for frame pacing diagnostics).</summary>
    public int GetBufferFill()
    {
        return _writePos - _readPos;
    }

    /// <summary>
    /// Play a one-shot sound effect.
    /// </summary>
    public void PlaySfx(AudioStream stream, float volumeDb = 0.0f)
    {
        if (_sfxPlayer == null) return;
        _sfxPlayer.Stream = stream;
        _sfxPlayer.VolumeDb = volumeDb + Mathf.LinearToDb(SfxVolume);
        _sfxPlayer.Play();
    }

    /// <summary>
    /// Create an AudioStreamWAV from raw PCM16 sample data.
    /// Used for converting game audio assets to Godot format.
    /// </summary>
    public static AudioStreamWav CreateFromPCM16(short[] samples, int sampleRate = 32000, bool stereo = true)
    {
        byte[] data = new byte[samples.Length * 2];
        Buffer.BlockCopy(samples, 0, data, 0, data.Length);

        return new AudioStreamWav
        {
            Format = AudioStreamWav.FormatEnum.Format16Bits,
            MixRate = sampleRate,
            Stereo = stereo,
            Data = data,
        };
    }

    public override void _ExitTree()
    {
        StopPlayback();
        IsInitialized = false;
    }
}
