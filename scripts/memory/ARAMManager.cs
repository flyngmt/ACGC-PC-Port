using System;
using Godot;
using AnimalCrossing.Core;

namespace AnimalCrossing.Memory;

/// <summary>
/// ARAM (Auxiliary RAM) simulation, equivalent to pc_aram.c.
/// The GameCube has 16 MB of auxiliary RAM used primarily for audio data
/// and texture streaming. DMA transfers move data between main RAM and ARAM.
///
/// In the original:
///   - ARAM is a separate 16 MB memory space
///   - Bump allocator (no free, allocate-only)
///   - DMA transfers are asynchronous on real hardware (synchronous on PC)
///   - Used by jaudio_NES for sound banks and sequence data
/// </summary>
public class ARAMManager
{
    private byte[] _memory;
    private int _allocPos;
    private readonly int _size;

    public int Size => _size;
    public int Used => _allocPos;
    public int Free => _size - _allocPos;

    public ARAMManager(int size = Constants.ARAMSize)
    {
        _size = size;
        _memory = new byte[size];
        _allocPos = 0;
    }

    /// <summary>
    /// Allocate a block of ARAM. Returns the ARAM offset.
    /// Bump allocator with 32-byte alignment (matching original).
    /// </summary>
    public int Alloc(int size)
    {
        // Align to 32 bytes
        int aligned = (_allocPos + 31) & ~31;
        if (aligned + size > _size)
        {
            GD.PrintErr($"[ARAM] Out of memory: requested {size}, available {_size - aligned}");
            return -1;
        }

        int offset = aligned;
        _allocPos = aligned + size;
        return offset;
    }

    /// <summary>
    /// DMA transfer between main RAM and ARAM.
    /// type 0 = main → ARAM, type 1 = ARAM → main.
    /// </summary>
    public void DMATransfer(int type, int aramOffset, byte[] mainData, int mainOffset, int length)
    {
        if (aramOffset < 0 || aramOffset + length > _size)
        {
            // OOB reads return zeros (matching original behavior)
            if (type == 1 && mainData != null)
            {
                int valid = Math.Max(0, Math.Min(length, _size - Math.Max(0, aramOffset)));
                if (valid > 0 && aramOffset >= 0)
                    Array.Copy(_memory, aramOffset, mainData, mainOffset, valid);
                if (valid < length)
                    Array.Clear(mainData, mainOffset + valid, length - valid);
            }
            return;
        }

        if (type == 0)
        {
            // Main → ARAM
            Array.Copy(mainData, mainOffset, _memory, aramOffset, length);
        }
        else
        {
            // ARAM → Main
            Array.Copy(_memory, aramOffset, mainData, mainOffset, length);
        }
    }

    /// <summary>Read bytes directly from ARAM.</summary>
    public byte[] Read(int offset, int length)
    {
        byte[] data = new byte[length];
        if (offset >= 0 && offset + length <= _size)
            Array.Copy(_memory, offset, data, 0, length);
        return data;
    }

    /// <summary>Write bytes directly to ARAM.</summary>
    public void Write(int offset, byte[] data, int srcOffset = 0, int length = -1)
    {
        if (length < 0) length = data.Length - srcOffset;
        if (offset >= 0 && offset + length <= _size)
            Array.Copy(data, srcOffset, _memory, offset, length);
    }

    /// <summary>Reset ARAM (clear all data and allocations).</summary>
    public void Reset()
    {
        Array.Clear(_memory, 0, _memory.Length);
        _allocPos = 0;
    }
}
