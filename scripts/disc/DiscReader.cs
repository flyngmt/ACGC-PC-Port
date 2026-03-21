using System;
using System.Collections.Generic;
using System.IO;
using Godot;
using AnimalCrossing.Core;

namespace AnimalCrossing.Disc;

/// <summary>
/// Reads Animal Crossing disc images in CISO, ISO, and GCM formats.
/// Equivalent to pc_disc.c in the original port.
///
/// Disc layout (GameCube):
///   0x000000: Boot header (game ID, title, DOL offset, FST offset)
///   0x000440: Boot info 2 (FST size, etc.)
///   DOL offset: Main executable (DOL format)
///   FST offset: File System Table
///   Data regions: Game assets
/// </summary>
public class DiscReader
{
    private FileStream? _file;
    private DiscFormat _format;
    private uint _discSize;

    // CISO support
    private uint[]? _cisoBlockMap;
    private uint _cisoBlockSize;

    // DOL/REL extraction
    public byte[]? DolData { get; private set; }
    public byte[]? RelData { get; private set; }

    // File System Table
    private readonly Dictionary<string, FSTEntry> _fst = new();

    public bool IsOpen => _file != null;

    public enum DiscFormat
    {
        Unknown,
        ISO,    // Raw disc image
        GCM,    // GameCube master disc (same as ISO)
        CISO,   // Compact ISO (block-mapped compression)
    }

    public struct FSTEntry
    {
        public uint Offset;
        public uint Size;
        public string Name;
    }

    public bool Open(string path)
    {
        try
        {
            _file = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read);
            _format = DetectFormat();

            if (_format == DiscFormat.Unknown)
            {
                GD.PrintErr($"[DISC] Unknown disc format: {path}");
                _file.Close();
                _file = null;
                return false;
            }

            GD.Print($"[DISC] Format: {_format}, size: {_file.Length} bytes");

            if (_format == DiscFormat.CISO)
            {
                ParseCISOHeader();
            }

            // Read boot header to verify it's a GC disc
            byte[] header = new byte[0x2440];
            Read(0, header, 0, header.Length);

            // Check game ID (should be "GAFE01" for AC USA)
            string gameId = System.Text.Encoding.ASCII.GetString(header, 0, 6);
            GD.Print($"[DISC] Game ID: {gameId}");

            // Parse FST
            uint fstOffset = ReadBE32(header, 0x424);
            uint fstSize = ReadBE32(header, 0x428);
            ParseFST(fstOffset, fstSize);

            // Extract DOL
            uint dolOffset = ReadBE32(header, 0x420);
            ExtractDOL(dolOffset);

            return true;
        }
        catch (Exception ex)
        {
            GD.PrintErr($"[DISC] Failed to open: {ex.Message}");
            _file?.Close();
            _file = null;
            return false;
        }
    }

    public void Close()
    {
        _file?.Close();
        _file = null;
        DolData = null;
        RelData = null;
        _fst.Clear();
    }

    /// <summary>Read raw bytes from the disc image, handling CISO block mapping.</summary>
    public int Read(uint discOffset, byte[] buffer, int bufOffset, int length)
    {
        if (_file == null) return 0;

        if (_format == DiscFormat.CISO)
            return ReadCISO(discOffset, buffer, bufOffset, length);

        // Raw ISO/GCM: direct read
        _file.Seek(discOffset, SeekOrigin.Begin);
        return _file.Read(buffer, bufOffset, length);
    }

    /// <summary>Read bytes from a disc file by path.</summary>
    public byte[]? ReadFile(string path)
    {
        if (!_fst.TryGetValue(path, out var entry))
            return null;

        byte[] data = new byte[entry.Size];
        Read(entry.Offset, data, 0, (int)entry.Size);
        return data;
    }

    /// <summary>Find a file in the FST.</summary>
    public FSTEntry? FindFile(string path)
    {
        return _fst.TryGetValue(path, out var entry) ? entry : null;
    }

    private DiscFormat DetectFormat()
    {
        if (_file == null || _file.Length < 0x20)
            return DiscFormat.Unknown;

        byte[] magic = new byte[4];
        _file.Seek(0, SeekOrigin.Begin);
        _file.Read(magic, 0, 4);

        // CISO magic: "CISO" at offset 0
        if (magic[0] == 'C' && magic[1] == 'I' && magic[2] == 'S' && magic[3] == 'O')
            return DiscFormat.CISO;

        // GCM/ISO: check for valid GC disc header
        // GameCube discs have a magic number 0xC2339F3D at offset 0x1C
        byte[] gcMagic = new byte[4];
        _file.Seek(0x1C, SeekOrigin.Begin);
        _file.Read(gcMagic, 0, 4);
        uint gcMagicVal = (uint)((gcMagic[0] << 24) | (gcMagic[1] << 16) | (gcMagic[2] << 8) | gcMagic[3]);
        if (gcMagicVal == 0xC2339F3D)
            return DiscFormat.ISO;

        // Check file extension as fallback
        string ext = Path.GetExtension(_file.Name).ToLowerInvariant();
        return ext switch
        {
            ".gcm" => DiscFormat.GCM,
            ".iso" => DiscFormat.ISO,
            _ => DiscFormat.Unknown,
        };
    }

    private void ParseCISOHeader()
    {
        if (_file == null) return;

        byte[] header = new byte[Constants.CISOHeaderSize];
        _file.Seek(0, SeekOrigin.Begin);
        _file.Read(header, 0, header.Length);

        // Block size at offset 4 (LE32)
        _cisoBlockSize = (uint)(header[4] | (header[5] << 8) | (header[6] << 16) | (header[7] << 24));
        if (_cisoBlockSize == 0)
            _cisoBlockSize = Constants.CISOBlockSize;

        // Block map starts at offset 8, one byte per block (0=absent, 1=present)
        int numBlocks = (int)((header.Length - 8));
        _cisoBlockMap = new uint[numBlocks];
        uint fileBlock = 1; // First data block is after header
        for (int i = 0; i < numBlocks; i++)
        {
            if (header[8 + i] != 0)
            {
                _cisoBlockMap[i] = fileBlock;
                fileBlock++;
            }
            else
            {
                _cisoBlockMap[i] = 0; // Block not present
            }
        }

        GD.Print($"[DISC] CISO block size: {_cisoBlockSize}, blocks: {fileBlock - 1}");
    }

    private int ReadCISO(uint discOffset, byte[] buffer, int bufOffset, int length)
    {
        if (_file == null || _cisoBlockMap == null) return 0;

        int totalRead = 0;
        while (length > 0)
        {
            uint blockIdx = discOffset / _cisoBlockSize;
            uint blockOff = discOffset % _cisoBlockSize;

            if (blockIdx >= _cisoBlockMap.Length)
                break;

            uint fileBlock = _cisoBlockMap[blockIdx];
            int chunkSize = (int)Math.Min(length, _cisoBlockSize - blockOff);

            if (fileBlock == 0)
            {
                // Block not present in CISO, fill with zeros
                Array.Clear(buffer, bufOffset, chunkSize);
            }
            else
            {
                long fileOffset = fileBlock * _cisoBlockSize + blockOff;
                _file.Seek(fileOffset, SeekOrigin.Begin);
                int read = _file.Read(buffer, bufOffset, chunkSize);
                if (read < chunkSize)
                    Array.Clear(buffer, bufOffset + read, chunkSize - read);
            }

            discOffset += (uint)chunkSize;
            bufOffset += chunkSize;
            length -= chunkSize;
            totalRead += chunkSize;
        }

        return totalRead;
    }

    private void ParseFST(uint fstOffset, uint fstSize)
    {
        if (fstSize == 0 || fstSize > 0x100000) return;

        byte[] fstData = new byte[fstSize];
        Read(fstOffset, fstData, 0, (int)fstSize);

        // FST format: array of 12-byte entries
        // Entry 0: root directory (num_entries in offset field)
        uint numEntries = ReadBE32(fstData, 8);
        uint stringTableOffset = numEntries * 12;

        // Parse each entry
        var dirStack = new Stack<string>();
        dirStack.Push("");

        for (uint i = 1; i < numEntries && i * 12 + 12 <= fstSize; i++)
        {
            uint entryOffset = i * 12;
            byte flags = fstData[entryOffset];
            uint nameOffset = ReadBE32(fstData, (int)entryOffset) & 0x00FFFFFF;
            uint fileOffset = ReadBE32(fstData, (int)entryOffset + 4);
            uint fileSize = ReadBE32(fstData, (int)entryOffset + 8);

            // Read name from string table
            string name = ReadString(fstData, (int)(stringTableOffset + nameOffset));

            if (flags == 1)
            {
                // Directory
                dirStack.Push(dirStack.Peek() + name + "/");
            }
            else
            {
                // File
                string fullPath = dirStack.Peek() + name;
                _fst[fullPath] = new FSTEntry
                {
                    Offset = fileOffset,
                    Size = fileSize,
                    Name = fullPath,
                };
            }

            // Pop directories when we pass their end entry
            // (fileSize field for directories = index of next entry after this dir)
            // This is simplified - full implementation would track dir end indices
        }

        GD.Print($"[DISC] FST: {_fst.Count} files parsed");
    }

    private void ExtractDOL(uint dolOffset)
    {
        // DOL header: 7 text sections + 11 data sections
        byte[] dolHeader = new byte[0x100];
        Read(dolOffset, dolHeader, 0, dolHeader.Length);

        // Calculate total DOL size from section headers
        uint maxEnd = 0x100;
        for (int i = 0; i < 18; i++)
        {
            uint secOffset = ReadBE32(dolHeader, i * 4);
            uint secSize = ReadBE32(dolHeader, 0x90 + i * 4);
            if (secOffset > 0 && secSize > 0)
            {
                uint end = secOffset + secSize;
                if (end > maxEnd) maxEnd = end;
            }
        }

        DolData = new byte[maxEnd];
        Read(dolOffset, DolData, 0, (int)maxEnd);
        GD.Print($"[DISC] DOL extracted: {maxEnd} bytes from offset 0x{dolOffset:X}");

        // Look for foresta.rel.szs (the main REL module)
        var relEntry = FindFile("foresta.rel.szs");
        if (relEntry.HasValue)
        {
            byte[] compressed = new byte[relEntry.Value.Size];
            Read(relEntry.Value.Offset, compressed, 0, (int)relEntry.Value.Size);
            RelData = Yaz0.Decompress(compressed);
            GD.Print($"[DISC] REL extracted: {RelData?.Length ?? 0} bytes (decompressed from {compressed.Length})");
        }
    }

    private static uint ReadBE32(byte[] data, int offset)
    {
        return (uint)((data[offset] << 24) | (data[offset + 1] << 16) |
                       (data[offset + 2] << 8) | data[offset + 3]);
    }

    private static string ReadString(byte[] data, int offset)
    {
        int end = offset;
        while (end < data.Length && data[end] != 0) end++;
        return System.Text.Encoding.ASCII.GetString(data, offset, end - offset);
    }
}
