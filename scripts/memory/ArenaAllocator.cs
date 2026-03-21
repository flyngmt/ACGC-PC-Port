using System;

namespace AnimalCrossing.Memory;

/// <summary>
/// Arena (bump) allocator, equivalent to the THA/Hyral allocator in the original.
/// Each game scene gets its own arena for isolated memory management.
///
/// The GameCube's memory model uses arena allocators extensively:
///   - Main heap: ~24 MB for global allocations
///   - Scene arenas (Hyral/THA): ~256 KB per scene, freed on scene transition
///   - ARAM: 16 MB auxiliary memory for audio/texture streaming
///
/// In C#, managed memory handles most allocation needs, but the arena pattern
/// is preserved for compatibility with game logic that depends on arena semantics
/// (e.g., allocating from both ends, checking remaining space).
/// </summary>
public class ArenaAllocator : IDisposable
{
    private byte[] _buffer;
    private int _headPos; // Allocates forward from start
    private int _tailPos; // Allocates backward from end

    public int Size => _buffer.Length;
    public int Used => _headPos + (Size - _tailPos);
    public int Free => _tailPos - _headPos;

    public ArenaAllocator(int size)
    {
        _buffer = new byte[size];
        _headPos = 0;
        _tailPos = size;
    }

    /// <summary>Allocate from the head (forward direction).</summary>
    public Span<byte> AllocHead(int size, int alignment = 16)
    {
        // Align up
        int aligned = (_headPos + alignment - 1) & ~(alignment - 1);
        if (aligned + size > _tailPos)
            throw new OutOfMemoryException($"Arena overflow: requested {size}, free {_tailPos - aligned}");

        _headPos = aligned + size;
        return _buffer.AsSpan(aligned, size);
    }

    /// <summary>Allocate from the tail (backward direction).</summary>
    public Span<byte> AllocTail(int size, int alignment = 16)
    {
        int aligned = (_tailPos - size) & ~(alignment - 1);
        if (aligned < _headPos)
            throw new OutOfMemoryException($"Arena overflow (tail): requested {size}, free {aligned - _headPos}");

        _tailPos = aligned;
        return _buffer.AsSpan(aligned, size);
    }

    /// <summary>Reset the arena, freeing all allocations.</summary>
    public void Reset()
    {
        _headPos = 0;
        _tailPos = _buffer.Length;
    }

    /// <summary>Resize the arena (preserves head allocations if new size is larger).</summary>
    public void Resize(int newSize)
    {
        if (newSize < _headPos)
            throw new InvalidOperationException("Cannot shrink below current head position");

        byte[] newBuf = new byte[newSize];
        Array.Copy(_buffer, newBuf, Math.Min(_buffer.Length, newSize));
        _buffer = newBuf;
        _tailPos = newSize;
    }

    /// <summary>Get the raw buffer for direct memory access.</summary>
    public byte[] GetBuffer() => _buffer;

    public void Dispose()
    {
        _buffer = Array.Empty<byte>();
        _headPos = 0;
        _tailPos = 0;
    }
}
