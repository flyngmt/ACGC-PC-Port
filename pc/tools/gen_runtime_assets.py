#!/usr/bin/env python3
"""gen_runtime_assets.py - Convert .inc #includes to runtime-loaded binary assets.

Scans source files for #include "assets/*.inc" patterns, rewrites them with
#ifdef TARGET_PC sized-array declarations, and generates pc/src/pc_assets.c
loader + pc/include/pc_assets.h header.

Supports two loading modes:
  1. ROM-direct: reads from DOL + REL files (orig/GAFE01_00/)
  2. .bin fallback: reads from extracted .bin files (assets/)

Binary data from GC ROM is big-endian. After loading on LE PC,
multi-byte fields need byte-swapping:
  - u8/unsigned char: no swap
  - u16/unsigned short: swap each u16
  - Vtx: swap s16/u16 fields (first 12 bytes of each 16-byte vertex)

Usage:
    python gen_runtime_assets.py             # full run
    python gen_runtime_assets.py --scan-only # just report stats
    python gen_runtime_assets.py --dry-run   # show changes without writing
    python gen_runtime_assets.py --fix-offsets        # fix ROM offsets in existing source files
    python gen_runtime_assets.py --fix-offsets --dry-run  # preview offset fixes
"""

import re
import os
import sys
import struct
import shutil
from pathlib import Path
from collections import defaultdict

DECOMP_ROOT = Path(__file__).resolve().parent.parent.parent  # ac-decomp/
BIN_DIR = DECOMP_ROOT / "build" / "GAFE01_00" / "bin"
DOL_PATH = DECOMP_ROOT / "orig" / "GAFE01_00" / "sys" / "main.dol"
REL_PATH = DECOMP_ROOT / "orig" / "GAFE01_00" / "files" / "foresta.rel.szs"
FORESTA_SYMBOLS = DECOMP_ROOT / "config" / "GAFE01_00" / "foresta" / "symbols.txt"
DOL_SYMBOLS = DECOMP_ROOT / "config" / "GAFE01_00" / "symbols.txt"
OUTPUT_ASSETS_C = DECOMP_ROOT / "pc" / "src" / "pc_assets.c"
OUTPUT_ASSETS_H = DECOMP_ROOT / "pc" / "include" / "pc_assets.h"
RUNTIME_BIN_DIR = DECOMP_ROOT / "pc" / "build32" / "bin" / "assets"

SCAN_DIRS = [DECOMP_ROOT / "src"]

ARRAY_INC_RE = re.compile(
    r'([ \t]*)'
    r'((?:static|extern)\s+)?'
    r'((?:unsigned\s+(?:char|short|int|long))|(?:[A-Za-z_]\w*))'
    r'(\s+)'
    r'(\w+)'
    r'(\s*\[\s*(?:\w+)?\s*\])'
    r'(\s*(?:ATTRIBUTE_ALIGN\(\d+\)|__attribute__\s*\(\(aligned\(\d+\)\)\))\s*)?'
    r'(\s*=\s*\{[^\n]*)\n'
    r'([ \t]*)#include\s+"(assets/[^"]+\.inc)"\s*\n'
    r'([ \t]*\};)',
    re.MULTILINE
)

# Regex to find existing pc_load_asset calls in already-modified source files
# Groups: 1=prefix, 2=bin_path, 3=var_name, 4=size, 5=comma, 6=rom_off, 7=comma, 8=rom_src, 9=suffix
PC_LOAD_ASSET_RE = re.compile(
    r'(pc_load_asset\("([^"]*)",\s*(\w+),\s*)(0x[0-9a-fA-F]+)(,\s*)(0x[0-9a-fA-F]+)(,\s*)(\d+)(,\s*\d+\))'
)

TYPE_NORMALIZE = {
    'unsigned char': 'u8', 'unsigned short': 'u16',
    'unsigned int': 'u32', 'unsigned long': 'u32', 'char': 'u8',
}

# Asset swap types
SWAP_NONE = 0
SWAP_U16 = 1
SWAP_VTX = 2
SWAP_U32 = 3

# ROM sources
SRC_REL = 0
SRC_DOL = 1
SRC_NONE = 2  # .bin fallback only


def get_swap_type(elem_type):
    norm = TYPE_NORMALIZE.get(elem_type, elem_type)
    if norm in ('u8', 's8', 'char'): return SWAP_NONE
    elif norm in ('u16', 's16'): return SWAP_U16
    elif norm == 'Vtx': return SWAP_VTX
    elif norm in ('u32', 's32'): return SWAP_U32
    return SWAP_NONE


def is_function_local(indent_str):
    return len(indent_str.replace('\t', '    ')) >= 4


# --- DOL/REL offset computation ---

def parse_dol_header(dol_path):
    """Parse DOL header -> list of (file_offset, load_addr, size) for all sections."""
    with open(dol_path, 'rb') as f:
        data = f.read(0x100)
    text_offs = struct.unpack('>7I', data[0x00:0x1C])
    data_offs = struct.unpack('>11I', data[0x1C:0x48])
    text_addrs = struct.unpack('>7I', data[0x48:0x64])
    data_addrs = struct.unpack('>11I', data[0x64:0x90])
    text_sizes = struct.unpack('>7I', data[0x90:0xAC])
    data_sizes = struct.unpack('>11I', data[0xAC:0xD8])

    sections = []
    for i in range(7):
        if text_sizes[i] > 0:
            sections.append((text_offs[i], text_addrs[i], text_sizes[i], 'text'))
    for i in range(11):
        if data_sizes[i] > 0:
            sections.append((data_offs[i], data_addrs[i], data_sizes[i], 'data'))
    return sections


def parse_rel_header(rel_path):
    """Parse REL header -> list of (file_offset, size) per section index."""
    with open(rel_path, 'rb') as f:
        data = f.read(0x200)  # enough for header + section table
    num_sections = struct.unpack('>I', data[0x0C:0x10])[0]
    sec_info_off = struct.unpack('>I', data[0x10:0x14])[0]

    sections = []
    for i in range(num_sections):
        off = sec_info_off + i * 8
        sec_offset = struct.unpack('>I', data[off:off+4])[0]
        sec_size = struct.unpack('>I', data[off+4:off+8])[0]
        sec_offset &= ~1  # clear exec flag
        sections.append((sec_offset, sec_size))
    return sections


def parse_symbols_with_section(path):
    """Parse symbols.txt -> {name: [(section_name, offset, size), ...]}.

    Keeps ALL occurrences of each symbol name (static symbols can appear
    in multiple compilation units at different addresses).
    """
    symbols = defaultdict(list)
    if not path.exists():
        return dict(symbols)
    with open(path, encoding='utf-8') as f:
        for line in f:
            m = re.match(
                r'(\w+)\s*=\s*\.(\w+):(0x[0-9a-fA-F]+);\s*//.*?size:(0x[0-9a-fA-F]+)',
                line
            )
            if m:
                symbols[m.group(1)].append((
                    m.group(2),  # section name
                    int(m.group(3), 16),  # offset/address
                    int(m.group(4), 16),  # size
                ))
    return dict(symbols)


def compute_dol_file_offset(va, dol_sections):
    """Convert a virtual address to DOL file offset."""
    for file_off, load_addr, size, kind in dol_sections:
        if load_addr <= va < load_addr + size:
            return file_off + (va - load_addr)
    return None


def build_rom_offset_table(foresta_syms, dol_syms, rel_sections, dol_sections):
    """Build {name: [(rom_source, file_offset, sec_offset, size), ...]} mapping.

    Keeps ALL occurrences for duplicate static symbol names.
    """
    # REL section mapping: .text=1, .ctors=2, .dtors=3, .rodata=4, .data=5, .bss=6
    REL_SECTION_MAP = {'text': 1, 'ctors': 2, 'dtors': 3, 'rodata': 4, 'data': 5, 'bss': 6}

    offsets = defaultdict(list)

    # REL symbols (section-relative offsets)
    for name, entries in foresta_syms.items():
        for sec_name, sec_offset, size in entries:
            sec_idx = REL_SECTION_MAP.get(sec_name)
            if sec_idx is not None and sec_idx < len(rel_sections):
                rel_sec_file_off, rel_sec_size = rel_sections[sec_idx]
                if rel_sec_file_off > 0:
                    offsets[name].append((SRC_REL, rel_sec_file_off + sec_offset, sec_offset, size))

    # DOL symbols (virtual addresses)
    for name, entries in dol_syms.items():
        if name not in offsets:
            for sec_name, va, size in entries:
                file_off = compute_dol_file_offset(va, dol_sections)
                if file_off is not None:
                    offsets[name].append((SRC_DOL, file_off, va, size))

    return dict(offsets)


def resolve_file_offsets(file_entries, rom_offsets):
    """Resolve correct ROM offsets for static symbols in a source file.

    Symbols from the same .c file occupy contiguous .data section addresses.
    Finds the set of symbol occurrences forming a valid contiguous chain.
    Updates each entry's rom_src, rom_off, and byte_size in place.
    """
    if not file_entries:
        return

    # Single entry: use first available occurrence (can't disambiguate without neighbors)
    if len(file_entries) == 1:
        e = file_entries[0]
        options = rom_offsets.get(e['name'], [])
        if len(options) == 1:
            e['rom_src'] = options[0][0]
            e['rom_off'] = options[0][1]
            e['byte_size'] = options[0][3]
        # If multiple options and no neighbors to disambiguate, keep first (or current)
        return

    # Multiple entries: find contiguous chain in .data section
    first_name = file_entries[0]['name']
    first_options = rom_offsets.get(first_name, [])

    for first_src, first_rom_off, first_sec_off, first_size in first_options:
        chain = [(first_src, first_rom_off, first_sec_off, first_size)]
        prev_end = first_sec_off + first_size
        ok = True

        for i in range(1, len(file_entries)):
            entry_name = file_entries[i]['name']
            options = rom_offsets.get(entry_name, [])
            found = False

            for src, rom_off, sec_off, size in options:
                # Next symbol should start at prev_end, possibly with alignment padding
                # Allow up to 31 bytes of alignment padding
                if prev_end <= sec_off <= prev_end + 0x1F:
                    chain.append((src, rom_off, sec_off, size))
                    prev_end = sec_off + size
                    found = True
                    break

            if not found:
                ok = False
                break

        if ok and len(chain) == len(file_entries):
            # Found a consistent set - apply resolved offsets
            for entry, (src, rom_off, sec_off, size) in zip(file_entries, chain):
                entry['rom_src'] = src
                entry['rom_off'] = rom_off
                entry['byte_size'] = size
            return

    # Fallback: couldn't find consistent chain, keep tentative values
    pass


# --- Source scanning and rewriting ---

def scan_files(scan_dirs):
    files = []
    for scan_dir in scan_dirs:
        for root, dirs, fnames in os.walk(scan_dir):
            for fname in fnames:
                if fname.endswith(('.c', '.cpp', '.c_inc')):
                    fpath = Path(root) / fname
                    try:
                        content = fpath.read_text(encoding='utf-8', errors='replace')
                    except Exception:
                        continue
                    if '.inc"' in content:
                        matches = list(ARRAY_INC_RE.finditer(content))
                        if matches:
                            files.append((fpath, content, matches))
    return files


def get_bin_path(inc_path):
    return BIN_DIR / inc_path.replace('.inc', '.bin')


def get_runtime_bin_path(inc_path):
    return inc_path.replace('.inc', '.bin')


def sanitize_func_name(path):
    rel = path.relative_to(DECOMP_ROOT)
    name = str(rel).replace('\\', '_').replace('/', '_').replace('.', '_').replace('-', '_')
    return f'_pc_load_{name}'


def process_all(scan_dirs, dry_run=False, scan_only=False):
    # Parse symbol tables (keeping all occurrences of each name)
    foresta_syms = parse_symbols_with_section(FORESTA_SYMBOLS)
    dol_syms = parse_symbols_with_section(DOL_SYMBOLS)
    total_foresta = sum(len(v) for v in foresta_syms.values())
    total_dol = sum(len(v) for v in dol_syms.values())
    print(f"Loaded {total_foresta} foresta symbols ({len(foresta_syms)} unique), "
          f"{total_dol} DOL symbols ({len(dol_syms)} unique)")

    # Parse DOL/REL headers for file offsets
    rom_offsets = {}
    if DOL_PATH.exists() and REL_PATH.exists():
        dol_sections = parse_dol_header(DOL_PATH)
        rel_sections = parse_rel_header(REL_PATH)
        rom_offsets = build_rom_offset_table(foresta_syms, dol_syms, rel_sections, dol_sections)
        total_offsets = sum(len(v) for v in rom_offsets.values())
        print(f"Computed {total_offsets} ROM file offsets ({len(rom_offsets)} unique names)")
    else:
        print("WARNING: DOL/REL not found, ROM-direct loading disabled")

    # Build unified size table (use first occurrence's size as tentative)
    all_syms = {}
    for name, entries in foresta_syms.items():
        all_syms[name] = entries[0][2]
    for name, entries in dol_syms.items():
        if name not in all_syms:
            all_syms[name] = entries[0][2]

    # Scan source files
    files = scan_files(scan_dirs)

    all_entries = []
    static_files = {}
    nonstatic_entries = []
    func_local_entries = []
    skipped = []
    name_counts = defaultdict(int)

    for fpath, content, matches in files:
        for m in matches:
            storage = (m.group(2) or '').strip()
            elem_type = m.group(3).strip()
            name = m.group(5)
            align_str = (m.group(7) or '').strip()
            inc_path = m.group(10)
            is_static = (storage == 'static')
            is_func_local = is_static and is_function_local(m.group(1))

            byte_size = all_syms.get(name)
            if byte_size is None:
                bin_path = get_bin_path(inc_path)
                if bin_path.exists():
                    byte_size = bin_path.stat().st_size
            if byte_size is None or byte_size == 0:
                skipped.append((fpath, name, inc_path, 'no size'))
                continue

            # Tentative ROM offset (first occurrence - will be resolved for statics)
            all_rom = rom_offsets.get(name, [])
            if all_rom:
                rom_src, rom_off = all_rom[0][0], all_rom[0][1]
            else:
                rom_src, rom_off = SRC_NONE, 0

            entry = {
                'file': fpath, 'name': name, 'type': elem_type,
                'byte_size': byte_size, 'storage': storage,
                'inc_path': inc_path, 'align': align_str,
                'is_static': is_static, 'is_func_local': is_func_local,
                'match': m, 'swap_type': get_swap_type(elem_type),
                'rom_src': rom_src, 'rom_off': rom_off,
            }
            all_entries.append(entry)

            if is_func_local:
                func_local_entries.append(entry)
            elif is_static:
                static_files.setdefault(str(fpath), []).append(entry)
            else:
                nonstatic_entries.append(entry)
                name_counts[name] += 1

    # Resolve correct ROM offsets for static symbols using adjacency matching
    resolved_count = 0
    for fpath, entries in static_files.items():
        resolve_file_offsets(entries, rom_offsets)
        resolved_count += len(entries)

    # Also resolve function-local entries (group by file)
    func_local_by_file = defaultdict(list)
    for entry in func_local_entries:
        func_local_by_file[str(entry['file'])].append(entry)
    for fpath, entries in func_local_by_file.items():
        resolve_file_offsets(entries, rom_offsets)

    dupes = {n: c for n, c in name_counts.items() if c > 1}

    # Report
    rom_count = sum(1 for e in all_entries if e['rom_src'] != SRC_NONE)
    bin_only = sum(1 for e in all_entries if e['rom_src'] == SRC_NONE)
    type_counts = defaultdict(int)
    for e in all_entries:
        type_counts[e['swap_type']] += 1

    print(f"\n=== Runtime Asset Scan ===")
    print(f"Files with .inc includes: {len(files)}")
    print(f"Total .inc arrays found:  {len(all_entries)}")
    print(f"  Non-static:             {len(nonstatic_entries)}")
    print(f"  File-scope static:      {len(all_entries) - len(nonstatic_entries) - len(func_local_entries)}")
    print(f"  Function-local static:  {len(func_local_entries)}")
    print(f"  Skipped (no size):      {len(skipped)}")
    print(f"ROM-direct capable:       {rom_count}")
    print(f".bin fallback only:       {bin_only}")
    print(f"Static symbols resolved:  {resolved_count}")
    print(f"By swap type: u8={type_counts[0]} u16={type_counts[1]} Vtx={type_counts[2]} u32={type_counts[3]}")

    total_bytes = sum(e['byte_size'] for e in all_entries)
    print(f"Total asset data: {total_bytes:,} bytes ({total_bytes/1048576:.1f} MB)")

    if scan_only:
        return

    # --- Modify source files ---
    modified_files = set()
    for fpath, content, matches in files:
        file_entries = [e for e in all_entries if e['file'] == fpath]
        if not file_entries:
            continue

        new_content = content
        for entry in sorted(file_entries, key=lambda e: e['match'].start(), reverse=True):
            m = entry['match']
            old_text = m.group(0)
            indent = m.group(1)
            elem_type = entry['type']
            name = entry['name']
            align = entry['align']
            byte_size = entry['byte_size']

            norm_type = TYPE_NORMALIZE.get(elem_type, elem_type)
            if norm_type in ('u8', 'char', 's8'):
                size_expr = f'0x{byte_size:X}'
            else:
                size_expr = f'0x{byte_size:X} / sizeof({elem_type})'

            pc_storage = 'static ' if entry['is_static'] else ''
            align_str = f' {align}' if align else ''

            if entry['is_func_local']:
                bin_path = get_runtime_bin_path(entry['inc_path'])
                pc_decl = f'{pc_storage}{elem_type} {name}[{size_expr}]{align_str};'
                lazy_lines = [
                    f'{indent}#ifdef TARGET_PC',
                    f'{indent}{pc_decl}',
                    f'{indent}static int {name}_loaded = 0;',
                    f'{indent}if (!{name}_loaded) {{',
                    f'{indent}    extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);',
                    f'{indent}    pc_load_asset("{bin_path}", {name}, 0x{byte_size:X}, 0x{entry["rom_off"]:X}, {entry["rom_src"]}, {entry["swap_type"]});',
                    f'{indent}    {name}_loaded = 1;',
                    f'{indent}}}',
                    f'{indent}#else',
                    f'{indent}{old_text}',
                    f'{indent}#endif',
                ]
                replacement = '\n'.join(lazy_lines)
            else:
                pc_decl = f'{pc_storage}{elem_type} {name}[{size_expr}]{align_str};'
                replacement = (
                    f'{indent}#ifdef TARGET_PC\n'
                    f'{indent}{pc_decl}\n'
                    f'{indent}#else\n'
                    f'{indent}{old_text}\n'
                    f'{indent}#endif'
                )

            new_content = new_content[:m.start()] + replacement + new_content[m.end():]

        # Per-file init function for file-scope statics
        file_statics = [e for e in file_entries if e['is_static'] and not e['is_func_local']]
        if file_statics:
            func_name = sanitize_func_name(fpath)
            init_lines = [f'\n#ifdef TARGET_PC']
            init_lines.append(f'extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);')
            init_lines.append(f'void {func_name}(void) {{')
            for entry in file_statics:
                bin_path = get_runtime_bin_path(entry['inc_path'])
                init_lines.append(
                    f'    pc_load_asset("{bin_path}", {entry["name"]}, '
                    f'0x{entry["byte_size"]:X}, 0x{entry["rom_off"]:X}, {entry["rom_src"]}, {entry["swap_type"]});'
                )
            init_lines.append(f'}}')
            init_lines.append(f'#endif')
            init_lines.append('')
            new_content += '\n'.join(init_lines)

        if new_content != content:
            modified_files.add(fpath)
            if not dry_run:
                fpath.write_text(new_content, encoding='utf-8')
            else:
                print(f"  [DRY-RUN] Would modify: {fpath.relative_to(DECOMP_ROOT)}")

    # Deduplicate central entries
    seen = set()
    central_entries = []
    for entry in nonstatic_entries:
        if entry['name'] not in seen:
            central_entries.append(entry)
            seen.add(entry['name'])

    init_func_names = [sanitize_func_name(Path(fp)) for fp in static_files]

    generate_pc_assets_c(central_entries, init_func_names, dry_run)
    generate_pc_assets_h(dry_run)

    # Copy .bin files
    copy_count = 0
    for entry in all_entries:
        src_bin = get_bin_path(entry['inc_path'])
        dst_bin = RUNTIME_BIN_DIR / get_runtime_bin_path(entry['inc_path']).replace('assets/', '')
        if src_bin.exists():
            if not dry_run:
                dst_bin.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(src_bin, dst_bin)
            copy_count += 1

    print(f"\n=== Results ===")
    print(f"Source files modified: {len(modified_files)}")
    print(f"Central loader entries: {len(central_entries)}")
    print(f"Per-file init functions: {len(init_func_names)}")
    print(f"Function-local lazy-loads: {len(func_local_entries)}")
    print(f"Bin files {'would copy' if dry_run else 'copied'}: {copy_count}")


# --- Fix existing source files (--fix-offsets mode) ---

def fix_existing_offsets(scan_dirs, dry_run=False):
    """Scan already-modified source files for pc_load_asset calls and fix ROM offsets.

    Computes the REL .data section file offset from unique (non-duplicate) symbols
    whose ROM offsets are known-correct, then uses that constant to compute the
    correct ROM offset for every symbol from its .data section address.

    Does NOT require the REL/DOL files — only needs the symbol table.
    """
    # Parse symbol tables (keeping all occurrences)
    foresta_syms = parse_symbols_with_section(FORESTA_SYMBOLS)
    total_foresta = sum(len(v) for v in foresta_syms.values())
    unique_count = sum(1 for v in foresta_syms.values() if len(v) == 1)
    dup_count = sum(1 for v in foresta_syms.values() if len(v) > 1)
    print(f"Loaded {total_foresta} foresta symbols ({len(foresta_syms)} names, "
          f"{unique_count} unique, {dup_count} duplicated)")

    # Build lookup: name -> list of .data addresses and sizes
    # {name: [(sec_name, sec_offset, size), ...]}
    dup_names = {name for name, entries in foresta_syms.items() if len(entries) > 1}

    # Step 1: Scan source files for existing pc_load_asset calls to find
    # unique symbols and compute REL .data section file offset
    all_file_calls = {}  # fpath -> [(match, var_name, cur_size, cur_rom_off), ...]
    rel_data_base = None
    calibration_samples = []

    for scan_dir in scan_dirs:
        for root, dirs, fnames in os.walk(scan_dir):
            for fname in fnames:
                if not fname.endswith(('.c', '.cpp', '.c_inc')):
                    continue
                fpath = Path(root) / fname
                try:
                    content = fpath.read_text(encoding='utf-8', errors='replace')
                except Exception:
                    continue
                if 'pc_load_asset(' not in content:
                    continue
                calls = list(PC_LOAD_ASSET_RE.finditer(content))
                if not calls:
                    continue

                parsed = []
                for cm in calls:
                    var_name = cm.group(3)
                    cur_size = int(cm.group(4), 16)
                    cur_rom_off = int(cm.group(6), 16)
                    rom_src = int(cm.group(8))
                    parsed.append((cm, var_name, cur_size, cur_rom_off, rom_src))

                    # Use unique REL symbols to calibrate the .data base offset
                    if rom_src == SRC_REL and var_name not in dup_names:
                        entries = foresta_syms.get(var_name, [])
                        if len(entries) == 1:
                            sec_name, sec_offset, size = entries[0]
                            if sec_name == 'data':
                                base = cur_rom_off - sec_offset
                                calibration_samples.append((var_name, sec_offset, cur_rom_off, base))

                all_file_calls[fpath] = (content, parsed)

    if not calibration_samples:
        print("ERROR: No unique REL symbols found to calibrate .data base offset")
        return

    # Verify all calibration samples agree on the same base
    bases = set(s[3] for s in calibration_samples)
    if len(bases) == 1:
        rel_data_base = bases.pop()
        print(f"REL .data section file offset: 0x{rel_data_base:X} "
              f"(verified from {len(calibration_samples)} unique symbols)")
    else:
        # Multiple bases — use majority vote
        from collections import Counter
        base_counts = Counter(s[3] for s in calibration_samples)
        rel_data_base, count = base_counts.most_common(1)[0]
        print(f"WARNING: {len(bases)} different base offsets found, using majority "
              f"0x{rel_data_base:X} ({count}/{len(calibration_samples)} samples)")
        for base, cnt in base_counts.most_common():
            print(f"  0x{base:X}: {cnt} symbols")

    # Build ordered symbol list for neighbor-context validation
    # [(sec_off, name), ...] sorted by address
    all_syms_ordered = []
    for name, entries in foresta_syms.items():
        for sec_name, sec_off, size in entries:
            if sec_name == 'data':
                all_syms_ordered.append((sec_off, name))
    all_syms_ordered.sort()
    # Build index: sec_off -> position in ordered list
    sym_pos = {sec_off: i for i, (sec_off, _) in enumerate(all_syms_ordered)}

    # Step 2: For each file with duplicate symbols, compute correct ROM offsets
    fixed_files = 0
    fixed_calls = 0
    total_calls = 0

    for fpath, (content, parsed) in all_file_calls.items():
        total_calls += len(parsed)

        # Check if any asset in this file has a duplicate name
        has_dup = any(var_name in dup_names for _, var_name, _, _, _ in parsed)
        if not has_dup:
            continue

        file_names = [var_name for _, var_name, _, _, _ in parsed]
        file_rom_srcs = [rom_src for _, _, _, _, rom_src in parsed]

        # Derive name prefixes from ALL loaded symbols AND .bin paths for context validation.
        # e.g., obj_item_peach_pal -> "obj_item_peach", obj_item_orange_tex -> "obj_item_orange"
        # Also extract directory name from .bin path for per-asset disambiguation:
        # e.g., "assets/int_din_bront_body/int_din_bront_pal.bin" -> "int_din_bront_body"
        file_prefixes = set()
        per_asset_prefix = {}  # var_name -> specific prefix from .bin path
        for cm_match, var_name, _, _, _ in parsed:
            parts = var_name.rsplit('_', 1)
            if len(parts) >= 2 and len(parts[0]) >= 4:
                file_prefixes.add(parts[0])
            # Extract directory from .bin path as a more specific prefix
            bin_path = cm_match.group(2)  # e.g., "assets/int_din_bront_body/int_din_bront_pal.bin"
            path_parts = bin_path.replace('\\', '/').split('/')
            if len(path_parts) >= 2:
                asset_dir = path_parts[-2]  # e.g., "int_din_bront_body"
                if asset_dir != 'assets' and len(asset_dir) >= 4:
                    per_asset_prefix[var_name] = asset_dir
                    file_prefixes.add(asset_dir)
        file_prefix = file_prefixes if file_prefixes else None

        # Collect all candidate .data addresses for each symbol
        candidates = []
        for var_name in file_names:
            entries = foresta_syms.get(var_name, [])
            data_entries = [(sec_off, size) for sec_name, sec_off, size in entries
                           if sec_name == 'data']
            candidates.append(data_entries)

        # Find the correct .data addresses using context-aware resolution:
        # 1. Try contiguous chain (tight gap) — works for files with 2+ symbols
        # 2. If that fails or picks a wrong group, validate by checking
        #    neighboring symbols in the ordered symbol list
        # For single-symbol files, skip chain matching (can't disambiguate
        # without adjacency) and go straight to per-symbol fallback.
        resolved_addrs = None
        if len(candidates) >= 2:
            resolved_addrs = _find_contiguous_chain(candidates)

        # Validate the chain by checking neighbor context.
        # Only needed for PALETTE-ONLY chains (all elements <= 0x40 bytes) which
        # could match a centralized palette table. Chains containing textures or
        # vertices (large elements) are unambiguous.
        if resolved_addrs is not None and file_prefix is not None:
            all_small = all(size <= 0x40 for _, size in resolved_addrs)
            if all_small:
                # This could be a centralized palette table.
                # Check the first NON-LOADED symbol after the chain start —
                # in the correct compilation unit, it should be a texture/vertex.
                first_sec_off = resolved_addrs[0][0]
                pos = sym_pos.get(first_sec_off)
                loaded_names = set(file_names)
                if pos is not None:
                    neighbor_match = False
                    for j in range(1, min(10, len(all_syms_ordered) - pos)):
                        _, neighbor_name = all_syms_ordered[pos + j]
                        if neighbor_name in loaded_names:
                            continue  # skip our own loaded symbols
                        # First non-loaded neighbor found
                        if any(neighbor_name.startswith(p) for p in file_prefix):
                            neighbor_match = True
                        break
                    if not neighbor_match:
                        resolved_addrs = None

        # If tight chain failed/rejected, try context-aware per-symbol resolution
        if resolved_addrs is None:
            resolved_addrs = []
            for i, var_name in enumerate(file_names):
                entries = foresta_syms.get(var_name, [])
                data_entries = [(sec_off, size) for sec_name, sec_off, size in entries
                               if sec_name == 'data']
                if len(data_entries) == 1:
                    resolved_addrs.append(data_entries[0])
                elif len(data_entries) > 1 and file_prefix:
                    # Pick the occurrence whose NON-LOADED neighbors in the symbol table
                    # share our file prefix (= same compilation unit).
                    loaded_names = set(file_names)
                    # Try specific per-asset prefix first (from .bin path directory)
                    specific_prefix = per_asset_prefix.get(var_name)
                    matching = []
                    for sec_off, size in data_entries:
                        pos = sym_pos.get(sec_off)
                        if pos is None:
                            continue
                        found = False
                        for j in range(1, min(20, len(all_syms_ordered) - pos)):
                            neighbor_name = all_syms_ordered[pos + j][1]
                            # Stop at the next occurrence of our loaded symbol
                            # (= boundary of next compilation unit)
                            if neighbor_name in loaded_names:
                                break
                            if specific_prefix and neighbor_name.startswith(specific_prefix):
                                matching.append((sec_off, size))
                                found = True
                                break
                            elif not specific_prefix and any(neighbor_name.startswith(p) for p in file_prefix):
                                matching.append((sec_off, size))
                                found = True
                                break
                    if len(matching) == 1:
                        resolved_addrs.append(matching[0])
                    else:
                        resolved_addrs.append(None)
                else:
                    resolved_addrs.append(None)

        # Apply fixes
        new_content = content
        file_changed = False
        # Process in reverse order to preserve character positions
        for i in reversed(range(len(parsed))):
            cm, var_name, cur_size, cur_rom_off, rom_src = parsed[i]

            if rom_src != SRC_REL:
                continue  # only fix REL symbols

            addr = resolved_addrs[i] if resolved_addrs else None
            if addr is None:
                continue

            sec_off, correct_size = addr
            correct_rom_off = rel_data_base + sec_off

            if cur_rom_off != correct_rom_off or cur_size != correct_size:
                old_size_str = f'0x{cur_size:X}'
                old_rom_off_str = f'0x{cur_rom_off:X}'
                new_size_str = f'0x{correct_size:X}'
                new_rom_off_str = f'0x{correct_rom_off:X}'

                # Build replacement: groups are (1:prefix)(4:size)(5:,)(6:rom_off)(7:,)(8:src)(9:suffix)
                replacement = (
                    cm.group(1) +      # pc_load_asset("path", name,
                    new_size_str +     # size
                    cm.group(5) +      # ,
                    new_rom_off_str +  # rom_off
                    cm.group(7) +      # ,
                    cm.group(8) +      # rom_src
                    cm.group(9)        # , swap_type)
                )
                new_content = new_content[:cm.start()] + replacement + new_content[cm.end():]
                file_changed = True
                fixed_calls += 1

                rel_path = fpath.relative_to(DECOMP_ROOT)
                changes = []
                if old_size_str != new_size_str:
                    changes.append(f"size {old_size_str}->{new_size_str}")
                changes.append(f"off {old_rom_off_str}->{new_rom_off_str}")
                change_str = ', '.join(changes)
                prefix = "  " if dry_run else "  FIXED "
                print(f"{prefix}{rel_path}: {var_name}: {change_str}")

        if file_changed:
            fixed_files += 1
            if not dry_run:
                fpath.write_text(new_content, encoding='utf-8')

    print(f"\n=== Fix Results ===")
    print(f"Total pc_load_asset calls scanned: {total_calls}")
    print(f"Calls {'would fix' if dry_run else 'fixed'}: {fixed_calls}")
    print(f"Files {'would modify' if dry_run else 'modified'}: {fixed_files}")


def _find_contiguous_chain(candidates):
    """Find a set of .data addresses from candidates that form a contiguous chain.

    candidates: list of [(sec_off, size), ...] for each symbol in file order.
    Returns: list of (sec_off, size) tuples, one per symbol, or None if no chain found.
    """
    if not candidates or not candidates[0]:
        return None

    # Try each candidate for the first symbol as starting point
    for first_sec_off, first_size in candidates[0]:
        chain = [(first_sec_off, first_size)]
        prev_end = first_sec_off + first_size
        ok = True

        for i in range(1, len(candidates)):
            if not candidates[i]:
                ok = False
                break
            found = False
            for sec_off, size in candidates[i]:
                # Allow up to 31 bytes of alignment padding
                if prev_end <= sec_off <= prev_end + 0x1F:
                    chain.append((sec_off, size))
                    prev_end = sec_off + size
                    found = True
                    break
            if not found:
                ok = False
                break

        if ok and len(chain) == len(candidates):
            return chain

    return None


def generate_pc_assets_c(central_entries, init_func_names, dry_run):
    lines = []
    lines.append('/* pc_assets.c - Runtime binary asset loader (auto-generated) */')
    lines.append('#ifdef TARGET_PC')
    lines.append('#include <stdio.h>')
    lines.append('#include <stdlib.h>')
    lines.append('#include <string.h>')
    lines.append('#include "types.h"')
    lines.append('#include "PR/gbi.h"')
    lines.append('#include "pc_assets.h"')
    lines.append('#include <dolphin/dvd.h>')
    lines.append('')
    lines.append('extern int g_pc_verbose;')
    lines.append('')

    # ROM source enum
    lines.append('enum { SRC_REL = 0, SRC_DOL = 1, SRC_NONE = 2 };')
    lines.append('enum { SWAP_NONE = 0, SWAP_U16 = 1, SWAP_VTX = 2, SWAP_U32 = 3 };')
    lines.append('')

    # Global ROM data buffers
    lines.append('static u8* g_rel_data = NULL;')
    lines.append('static u8* g_dol_data = NULL;')
    lines.append('')

    # Aurora owns disc-image parsing through nod. Keep these helpers in the
    # generator so regenerating the large asset table cannot resurrect the
    # retired custom pc_disc backend.
    lines.extend(r'''
static u32 aurora_read_be32(const u8* p) {
    return ((u32)p[0] << 24) | ((u32)p[1] << 16) | ((u32)p[2] << 8) | p[3];
}

static u8* aurora_yaz0_decode(const u8* src, u32 src_size, u32* out_size) {
    u32 decoded_size, src_pos = 16, dst_pos = 0;
    u8* dst;
    int bit;

    if (src_size < 16 || memcmp(src, "Yaz0", 4) != 0) return NULL;
    decoded_size = aurora_read_be32(src + 4);
    dst = (u8*)malloc(decoded_size);
    if (dst == NULL) return NULL;

    while (dst_pos < decoded_size && src_pos < src_size) {
        u8 flags = src[src_pos++];
        for (bit = 7; bit >= 0 && dst_pos < decoded_size; --bit) {
            if (src_pos >= src_size) break;
            if (flags & (1 << bit)) {
                dst[dst_pos++] = src[src_pos++];
            } else {
                u8 b1, b2;
                u32 distance, length, copy_pos;
                if (src_pos + 1 >= src_size) break;
                b1 = src[src_pos++];
                b2 = src[src_pos++];
                distance = ((u32)(b1 & 0x0F) << 8) | b2;
                if ((b1 >> 4) == 0) {
                    if (src_pos >= src_size) break;
                    length = (u32)src[src_pos++] + 0x12;
                } else {
                    length = (u32)(b1 >> 4) + 2;
                }
                if (distance >= dst_pos) {
                    free(dst);
                    return NULL;
                }
                copy_pos = dst_pos - distance - 1;
                while (length-- != 0 && dst_pos < decoded_size) {
                    dst[dst_pos++] = dst[copy_pos++];
                }
            }
        }
    }

    if (dst_pos != decoded_size) {
        free(dst);
        return NULL;
    }
    *out_size = decoded_size;
    return dst;
}

static u8* aurora_load_dvd_file(const char* path, u32* out_size) {
    DVDFileInfo file_info;
    u32 file_size, transfer_size;
    u8* buffer;
    s32 result;

    if (!DVDOpen(path, &file_info)) return NULL;
    file_size = file_info.length;
    transfer_size = (file_size + 31u) & ~31u;
    buffer = (u8*)aligned_alloc(32, transfer_size);
    if (buffer == NULL) {
        DVDClose(&file_info);
        return NULL;
    }
    result = DVDReadPrio(&file_info, buffer, (s32)transfer_size, 0, 2);
    DVDClose(&file_info);
    if (result < (s32)file_size) {
        free(buffer);
        return NULL;
    }
    *out_size = file_size;
    return buffer;
}

static int aurora_load_rom_images(void) {
    const u8* mounted_dol;
    s32 dol_size = 0;
    u32 rel_size = 0;
    u8* rel_raw;

    mounted_dol = DVDGetDOLLocation(&dol_size);
    if (mounted_dol == NULL || dol_size <= 0) return 0;
    g_dol_data = (u8*)malloc((size_t)dol_size);
    if (g_dol_data == NULL) return 0;
    memcpy(g_dol_data, mounted_dol, (size_t)dol_size);

    rel_raw = aurora_load_dvd_file("/foresta.rel.szs", &rel_size);
    if (rel_raw == NULL) {
        free(g_dol_data);
        g_dol_data = NULL;
        return 0;
    }
    if (rel_size >= 16 && memcmp(rel_raw, "Yaz0", 4) == 0) {
        u32 decoded_size = 0;
        g_rel_data = aurora_yaz0_decode(rel_raw, rel_size, &decoded_size);
        free(rel_raw);
        if (g_pc_verbose && g_rel_data != NULL) {
            printf("[PC] Aurora DVD: DOL %d bytes, REL %u -> %u bytes\n",
                   dol_size, rel_size, decoded_size);
        }
    } else {
        g_rel_data = rel_raw;
        if (g_pc_verbose) {
            printf("[PC] Aurora DVD: DOL %d bytes, REL %u bytes\n", dol_size, rel_size);
        }
    }

    if (g_rel_data == NULL) {
        free(g_dol_data);
        g_dol_data = NULL;
        return 0;
    }
    return 1;
}
'''.strip().splitlines())
    lines.append('')

    # Byte-swap functions
    lines.append('void pc_bswap_asset_u16(void* data, unsigned int size) {')
    lines.append('    u16* p = (u16*)data;')
    lines.append('    unsigned int i, count = size / 2;')
    lines.append('    for (i = 0; i < count; i++) p[i] = (u16)((p[i] >> 8) | (p[i] << 8));')
    lines.append('}')
    lines.append('')
    lines.append('void pc_bswap_asset_u32(void* data, unsigned int size) {')
    lines.append('    u32* p = (u32*)data;')
    lines.append('    unsigned int i, count = size / 4;')
    lines.append('    for (i = 0; i < count; i++)')
    lines.append('        p[i] = ((p[i]>>24)&0xFF)|((p[i]>>8)&0xFF00)|((p[i]<<8)&0xFF0000)|((p[i]<<24)&0xFF000000);')
    lines.append('}')
    lines.append('')
    lines.append('void pc_bswap_asset_vtx(void* data, unsigned int size) {')
    lines.append('    u8* p = (u8*)data;')
    lines.append('    unsigned int i, count = size / 16;')
    lines.append('    for (i = 0; i < count; i++) {')
    lines.append('        int j;')
    lines.append('        for (j = 0; j < 12; j += 2) { u8 t = p[j]; p[j] = p[j+1]; p[j+1] = t; }')
    lines.append('        p += 16;')
    lines.append('    }')
    lines.append('}')
    lines.append('')

    # Swap dispatch
    lines.append('static void do_swap(void* data, unsigned int size, int type) {')
    lines.append('    switch (type) {')
    lines.append('        case SWAP_U16: pc_bswap_asset_u16(data, size); break;')
    lines.append('        case SWAP_VTX: pc_bswap_asset_vtx(data, size); break;')
    lines.append('        case SWAP_U32: pc_bswap_asset_u32(data, size); break;')
    lines.append('        default: break;')
    lines.append('    }')
    lines.append('}')
    lines.append('')

    # Load a file into malloc'd buffer
    lines.append('static u8* load_file(const char* path, unsigned int* out_size) {')
    lines.append('    FILE* f = fopen(path, "rb");')
    lines.append('    unsigned int sz;')
    lines.append('    u8* buf;')
    lines.append('    if (!f) return NULL;')
    lines.append('    fseek(f, 0, SEEK_END); sz = (unsigned int)ftell(f); fseek(f, 0, SEEK_SET);')
    lines.append('    buf = (u8*)malloc(sz);')
    lines.append('    if (buf) fread(buf, 1, sz, f);')
    lines.append('    fclose(f);')
    lines.append('    if (out_size) *out_size = sz;')
    lines.append('    return buf;')
    lines.append('}')
    lines.append('')

    # Unified load function (ROM-direct + .bin fallback)
    lines.append('void pc_load_asset(const char* bin_path, void* dest, unsigned int size,')
    lines.append('                   unsigned int rom_off, int rom_src, int swap_type) {')
    lines.append('    int loaded = 0;')
    lines.append('    /* Try ROM-direct first */')
    lines.append('    if (rom_src != SRC_NONE) {')
    lines.append('        u8* rom = (rom_src == SRC_REL) ? g_rel_data : g_dol_data;')
    lines.append('        if (rom) { memcpy(dest, rom + rom_off, size); loaded = 1; }')
    lines.append('    }')
    lines.append('    /* Fallback to .bin file */')
    lines.append('    if (!loaded && bin_path) {')
    lines.append('        FILE* f = fopen(bin_path, "rb");')
    lines.append('        if (f) { fread(dest, 1, size, f); fclose(f); loaded = 1; }')
    lines.append('    }')
    lines.append('    if (!loaded) fprintf(stderr, "[PC] ASSET MISSING: %s\\n", bin_path ? bin_path : "(rom)");')
    lines.append('    if (loaded) do_swap(dest, size, swap_type);')
    lines.append('}')
    lines.append('')

    # Extern declarations
    by_type = defaultdict(list)
    for entry in central_entries:
        norm_type = TYPE_NORMALIZE.get(entry['type'], entry['type'])
        by_type[norm_type].append(entry['name'])

    lines.append('/* Extern declarations */')
    for typ in sorted(by_type.keys()):
        for name in sorted(by_type[typ]):
            lines.append(f'extern {typ} {name}[];')
    lines.append('')

    # Asset table with ROM offsets
    lines.append('typedef struct { const char* path; void* dest; unsigned int size; unsigned int rom_off; int rom_src; int swap; } PCAsset;')
    lines.append('static const PCAsset s_assets[] = {')
    for entry in central_entries:
        bin_path = get_runtime_bin_path(entry['inc_path'])
        lines.append(
            f'    {{"{bin_path}", {entry["name"]}, 0x{entry["byte_size"]:X}, '
            f'0x{entry["rom_off"]:X}, {entry["rom_src"]}, {entry["swap_type"]}}},')
    lines.append('};')
    lines.append('')

    # Per-file init declarations
    if init_func_names:
        lines.append('/* Per-file init functions for static arrays */')
        for func_name in sorted(init_func_names):
            lines.append(f'extern void {func_name}(void);')
        lines.append('')

    # pc_assets_init
    lines.append('int pc_assets_init(void) {')
    lines.append('    int i, loaded = 0, failed = 0, rom_mode = 0;')
    lines.append('    int total = (int)(sizeof(s_assets) / sizeof(s_assets[0]));')
    lines.append('')
    lines.append('    /* Load the mounted image through Aurora/nod first. */')
    lines.append('    rom_mode = aurora_load_rom_images();')
    lines.append('')
    lines.append('    /* Developer fallback for pre-extracted files. */')
    lines.append('    if (!rom_mode) {')
    lines.append('        g_rel_data = load_file("orig/GAFE01_00/files/foresta.rel.szs", NULL);')
    lines.append('        g_dol_data = load_file("orig/GAFE01_00/sys/main.dol", NULL);')
    lines.append('        if (g_rel_data && g_dol_data) {')
    lines.append('            rom_mode = 1;')
    lines.append('            if (g_pc_verbose) printf("[PC] ROM-direct mode: loaded pre-extracted DOL + REL\\n");')
    lines.append('        } else {')
    lines.append('            if (g_rel_data) { free(g_rel_data); g_rel_data = NULL; }')
    lines.append('            if (g_dol_data) { free(g_dol_data); g_dol_data = NULL; }')
    lines.append('        }')
    lines.append('    }')
    lines.append('')
    lines.append('    /* No ROM data: nothing to boot from. Let main report it. */')
    lines.append('    if (!rom_mode) {')
    lines.append('        printf("[PC] No ROM data found (no disc image, no pre-extracted DOL/REL)\\n");')
    lines.append('        return 0;')
    lines.append('    }')
    lines.append('')
    lines.append('    /* Load all central-table assets */')
    lines.append('    for (i = 0; i < total; i++) {')
    lines.append('        pc_load_asset(s_assets[i].path, s_assets[i].dest, s_assets[i].size,')
    lines.append('                      s_assets[i].rom_off, s_assets[i].rom_src, s_assets[i].swap);')
    lines.append('        loaded++;')
    lines.append('    }')
    lines.append('')

    if init_func_names:
        lines.append('    /* Load static arrays via per-file init functions */')
        for func_name in sorted(init_func_names):
            lines.append(f'    {func_name}();')
        lines.append('')

    lines.append('    /* Free ROM data */')
    lines.append('    if (g_rel_data) { free(g_rel_data); g_rel_data = NULL; }')
    lines.append('    if (g_dol_data) { free(g_dol_data); g_dol_data = NULL; }')
    lines.append('')
    lines.append('    if (g_pc_verbose)')
    lines.append('        printf("[PC] Assets: %d loaded (%s)\\n", loaded, rom_mode ? "ROM-direct" : ".bin fallback");')
    lines.append('')
    lines.append('    return 1;')
    lines.append('}')
    lines.append('')
    lines.append('#endif /* TARGET_PC */')
    lines.append('')

    content = '\n'.join(lines)
    if not dry_run:
        OUTPUT_ASSETS_C.write_text(content, encoding='utf-8')
        print(f"Generated: {OUTPUT_ASSETS_C.relative_to(DECOMP_ROOT)}")
    else:
        print(f"[DRY-RUN] Would generate: {OUTPUT_ASSETS_C.relative_to(DECOMP_ROOT)} ({len(central_entries)} entries)")


def generate_pc_assets_h(dry_run):
    content = (
        '/* pc_assets.h - Runtime binary asset loader (auto-generated) */\n'
        '#ifndef PC_ASSETS_H\n'
        '#define PC_ASSETS_H\n'
        '\n'
        'void pc_load_asset(const char* bin_path, void* dest, unsigned int size,\n'
        '                   unsigned int rom_off, int rom_src, int swap_type);\n'
        'void pc_bswap_asset_u16(void* data, unsigned int size);\n'
        'void pc_bswap_asset_u32(void* data, unsigned int size);\n'
        'void pc_bswap_asset_vtx(void* data, unsigned int size);\n'
        'int pc_assets_init(void);\n'
        '\n'
        '#endif /* PC_ASSETS_H */\n'
    )
    if not dry_run:
        OUTPUT_ASSETS_H.write_text(content, encoding='utf-8')
        print(f"Generated: {OUTPUT_ASSETS_H.relative_to(DECOMP_ROOT)}")
    else:
        print(f"[DRY-RUN] Would generate: {OUTPUT_ASSETS_H.relative_to(DECOMP_ROOT)}")


def main():
    dry_run = '--dry-run' in sys.argv
    scan_only = '--scan-only' in sys.argv
    fix_offsets = '--fix-offsets' in sys.argv

    print(f"Decomp root: {DECOMP_ROOT}")
    print()

    if fix_offsets:
        fix_existing_offsets(SCAN_DIRS, dry_run=dry_run)
    else:
        process_all(SCAN_DIRS, dry_run=dry_run, scan_only=scan_only)


if __name__ == '__main__':
    main()
