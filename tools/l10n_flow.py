#!/usr/bin/env python3

import argparse
import json
import shutil
import subprocess
import sys
from pathlib import Path


META_FILE_NAME = "l10n_meta.json"


def run(cmd, cwd=None):
    subprocess.run(cmd, cwd=cwd, check=True)


def find_message_files(unpack_dir: Path):
    data_candidates = sorted(unpack_dir.rglob("message_data.bin"))

    if not data_candidates:
        raise FileNotFoundError(
            "Could not find message_data.bin in unpacked archive. "
            "For this PC port, message resources are in forest_2nd.arc."
        )

    for data_path in data_candidates:
        table_path = data_path.with_name("message_data_table.bin")
        if table_path.exists():
            return data_path, table_path

    raise FileNotFoundError("Found message_data.bin but message_data_table.bin was not found next to it")


def get_archive_root(unpack_dir: Path, msg_data_path: Path):
    rel = msg_data_path.relative_to(unpack_dir)
    if len(rel.parts) == 0:
        raise RuntimeError("Unexpected archive layout while resolving archive root")
    return unpack_dir / rel.parts[0]


def extract_flow(args):
    root_dir = Path(__file__).resolve().parent.parent
    arc_tool = root_dir / "tools" / "arc_tool.py"
    msg_tool = root_dir / "tools" / "msg_tool.py"

    source_arc = Path(args.arc).resolve()
    if not source_arc.exists():
        raise FileNotFoundError(f"Source archive not found: {source_arc}")

    work_dir = Path(args.workdir).resolve()
    unpack_dir = work_dir / "unpacked"
    text_out = Path(args.text).resolve() if args.text else work_dir / "message_dump.txt"
    meta_path = work_dir / META_FILE_NAME

    if unpack_dir.exists() and not args.force:
        raise FileExistsError(f"Unpack directory already exists: {unpack_dir}. Use --force to overwrite")

    if unpack_dir.exists() and args.force:
        shutil.rmtree(unpack_dir)

    work_dir.mkdir(parents=True, exist_ok=True)
    unpack_dir.mkdir(parents=True, exist_ok=True)

    run([sys.executable, str(arc_tool), str(source_arc), str(unpack_dir)])

    msg_data_path, msg_table_path = find_message_files(unpack_dir)
    archive_root = get_archive_root(unpack_dir, msg_data_path)

    run([sys.executable, str(msg_tool), "-m", "unpack", str(msg_data_path), str(text_out)])

    meta = {
        "source_arc": str(source_arc),
        "work_dir": str(work_dir),
        "unpack_dir": str(unpack_dir),
        "archive_root": str(archive_root),
        "message_data_path": str(msg_data_path),
        "message_table_path": str(msg_table_path),
        "text_dump_path": str(text_out),
        "message_data_size": msg_data_path.stat().st_size,
        "message_table_size": msg_table_path.stat().st_size,
    }

    meta_path.write_text(json.dumps(meta, indent=2), encoding="utf-8")

    print(f"Extracted message files from: {source_arc}")
    print(f"Text dump: {text_out}")
    print(f"Metadata: {meta_path}")


def repack_flow(args):
    root_dir = Path(__file__).resolve().parent.parent
    arc_tool = root_dir / "tools" / "arc_tool.py"
    msg_tool = root_dir / "tools" / "msg_tool.py"

    work_dir = Path(args.workdir).resolve()
    meta_path = work_dir / META_FILE_NAME

    if not meta_path.exists():
        raise FileNotFoundError(
            f"Metadata file not found: {meta_path}. Run the extract step first"
        )

    meta = json.loads(meta_path.read_text(encoding="utf-8"))

    source_arc = Path(meta["source_arc"])
    archive_root = Path(meta["archive_root"])
    msg_data_path = Path(meta["message_data_path"])
    text_dump_path = Path(args.text).resolve() if args.text else Path(meta["text_dump_path"])

    if not text_dump_path.exists():
        raise FileNotFoundError(f"Text file not found: {text_dump_path}")

    if not archive_root.exists():
        raise FileNotFoundError(f"Unpacked archive root not found: {archive_root}")

    if not msg_data_path.exists():
        raise FileNotFoundError(f"message_data.bin not found: {msg_data_path}")

    run(
        [
            sys.executable,
            str(msg_tool),
            "-m",
            "pack",
            str(text_dump_path),
            str(msg_data_path),
            "--data_size",
            hex(int(meta["message_data_size"])),
            "--table_size",
            hex(int(meta["message_table_size"])),
        ]
    )

    out_arc = Path(args.out).resolve() if args.out else source_arc.with_name(f"{source_arc.stem}_l10n.arc")
    out_arc.parent.mkdir(parents=True, exist_ok=True)

    run([sys.executable, str(arc_tool), str(archive_root), str(out_arc)])

    print(f"Built localized archive: {out_arc}")

    if args.replace_source:
        backup_path = source_arc.with_suffix(source_arc.suffix + ".bak")
        shutil.copy2(source_arc, backup_path)
        shutil.copy2(out_arc, source_arc)
        print(f"Backed up original archive to: {backup_path}")
        print(f"Replaced source archive: {source_arc}")


def build_parser():
    parser = argparse.ArgumentParser(
        description="Localization flow for Animal Crossing message_data/message_data_table"
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    extract = subparsers.add_parser("extract", help="Unpack archive and dump messages to text")
    extract.add_argument("--arc", required=True, help="Path to source archive (usually dump/forest_2nd.arc)")
    extract.add_argument("--workdir", required=True, help="Working directory for unpacked archive and metadata")
    extract.add_argument("--text", required=False, help="Output message text file path")
    extract.add_argument("--force", action="store_true", help="Overwrite existing workdir/unpacked directory")
    extract.set_defaults(func=extract_flow)

    repack = subparsers.add_parser("repack", help="Encode messages and repack archive")
    repack.add_argument("--workdir", required=True, help="Working directory created by extract step")
    repack.add_argument("--text", required=False, help="Edited message text file path")
    repack.add_argument("--out", required=False, help="Output archive path")
    repack.add_argument(
        "--replace-source",
        action="store_true",
        help="Backup and replace the original source archive with localized output",
    )
    repack.set_defaults(func=repack_flow)

    return parser


def main():
    parser = build_parser()
    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
