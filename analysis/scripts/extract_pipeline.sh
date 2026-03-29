#!/usr/bin/env bash
# Dell BIOS Extraction Pipeline
# Usage: ./extract_pipeline.sh <firmware.exe>
#
# Stage 1: Dell PFS Extract  - unpacks the .exe update package
# Stage 2: UEFIExtract       - parses the UEFI firmware image, dumps all modules/PE images
# Stage 3: Ghidra headless   - auto-analyzes every PE image found

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"

FIRMWARE_INPUT="$REPO_ROOT/firmware/input"
PFS_OUT="$REPO_ROOT/firmware/extracted/pfs"
UEFI_OUT="$REPO_ROOT/firmware/extracted/uefi"
PE_OUT="$REPO_ROOT/firmware/extracted/pe_images"
GHIDRA_PROJECTS="$REPO_ROOT/ghidra_projects"

BIOS_UTILS="/home/user/tools/BIOSUtilities"
UEFIEXTRACT="/home/user/tools/UEFITool/build_uefiextract/uefiextract"
GHIDRA_HEADLESS="/home/user/tools/ghidra_12.0.4_PUBLIC/support/analyzeHeadless"

usage() {
    echo "Usage: $0 <path/to/firmware.exe>"
    echo "       $0 --skip-pfs <path/to/bios.bin>  (skip PFS stage, feed .bin directly)"
    exit 1
}

[[ $# -lt 1 ]] && usage

SKIP_PFS=false
if [[ "$1" == "--skip-pfs" ]]; then
    SKIP_PFS=true
    FIRMWARE_FILE="$2"
else
    FIRMWARE_FILE="$1"
fi

[[ ! -f "$FIRMWARE_FILE" ]] && { echo "[!] File not found: $FIRMWARE_FILE"; exit 1; }

BASENAME="$(basename "$FIRMWARE_FILE" | sed 's/\.[^.]*$//')"
RUN_PFS_OUT="$PFS_OUT/$BASENAME"
RUN_UEFI_OUT="$UEFI_OUT/$BASENAME"
RUN_PE_OUT="$PE_OUT/$BASENAME"

mkdir -p "$RUN_PFS_OUT" "$RUN_UEFI_OUT" "$RUN_PE_OUT"

# ──────────────────────────────────────────────────────────────
# STAGE 1: Dell PFS Extract
# ──────────────────────────────────────────────────────────────
if [[ "$SKIP_PFS" == false ]]; then
    echo ""
    echo "══════════════════════════════════════════"
    echo " STAGE 1: Dell PFS Extract"
    echo "══════════════════════════════════════════"

    cp "$FIRMWARE_FILE" "$FIRMWARE_INPUT/"
    INPUT_COPY="$FIRMWARE_INPUT/$(basename "$FIRMWARE_FILE")"

    python3 "$BIOS_UTILS/main.py" Dell_PFS_Extract \
        -i "$INPUT_COPY" \
        -o "$RUN_PFS_OUT" \
        -v

    echo "[+] PFS extraction complete -> $RUN_PFS_OUT"
    ls -lh "$RUN_PFS_OUT"

    # Find the main BIOS .bin
    BIOS_BIN="$(find "$RUN_PFS_OUT" -iname "*System BIOS*" -o -iname "*bios*.bin" | head -1)"
    if [[ -z "$BIOS_BIN" ]]; then
        echo "[!] Could not auto-detect System BIOS bin. Files extracted:"
        find "$RUN_PFS_OUT" -type f | sort
        echo "[!] Set BIOS_BIN manually and re-run with --skip-pfs"
        exit 1
    fi
    echo "[+] Detected BIOS image: $BIOS_BIN"
else
    BIOS_BIN="$FIRMWARE_FILE"
    echo "[*] Skipping PFS stage, using: $BIOS_BIN"
fi

# ──────────────────────────────────────────────────────────────
# STAGE 2: UEFIExtract
# ──────────────────────────────────────────────────────────────
echo ""
echo "══════════════════════════════════════════"
echo " STAGE 2: UEFIExtract"
echo "══════════════════════════════════════════"

# UEFIExtract dumps to a dir named <input>.dump next to the input file
BIOS_BIN_COPY="$RUN_UEFI_OUT/$(basename "$BIOS_BIN")"
cp "$BIOS_BIN" "$BIOS_BIN_COPY"

"$UEFIEXTRACT" "$BIOS_BIN_COPY" all 2>&1 | tee "$RUN_UEFI_OUT/uefiextract.log"

DUMP_DIR="${BIOS_BIN_COPY}.dump"
if [[ ! -d "$DUMP_DIR" ]]; then
    echo "[!] UEFIExtract dump dir not found: $DUMP_DIR"
    exit 1
fi

echo "[+] UEFI extraction complete -> $DUMP_DIR"

# ──────────────────────────────────────────────────────────────
# Collect PE images (EFI DXE drivers, SMM modules, etc.)
# ──────────────────────────────────────────────────────────────
echo ""
echo "[*] Collecting PE images from dump..."
PE_COUNT=0
while IFS= read -r -d '' pe_file; do
    # Derive a flat name preserving parent dir context
    REL="$(realpath --relative-to="$DUMP_DIR" "$pe_file")"
    FLAT_NAME="$(echo "$REL" | tr '/' '__')"
    cp "$pe_file" "$RUN_PE_OUT/${FLAT_NAME}"
    ((PE_COUNT++))
done < <(find "$DUMP_DIR" -type f \( -iname "*.pe" -o -iname "*.efi" -o -iname "*.te" \) -print0)

# Also grab raw sections that look like PE (MZ header)
while IFS= read -r -d '' raw_file; do
    if [[ "$(xxd -l 2 "$raw_file" 2>/dev/null)" == *"4d5a"* ]]; then
        REL="$(realpath --relative-to="$DUMP_DIR" "$raw_file")"
        FLAT_NAME="$(echo "$REL" | tr '/' '__')"
        cp "$raw_file" "$RUN_PE_OUT/mz_${FLAT_NAME}"
        ((PE_COUNT++))
    fi
done < <(find "$DUMP_DIR" -type f -iname "*.raw" -print0)

echo "[+] Collected $PE_COUNT PE/EFI images -> $RUN_PE_OUT"

# ──────────────────────────────────────────────────────────────
# STAGE 3: Ghidra headless analysis
# ──────────────────────────────────────────────────────────────
echo ""
echo "══════════════════════════════════════════"
echo " STAGE 3: Ghidra Headless Analysis"
echo "══════════════════════════════════════════"

GHIDRA_PROJECT_DIR="$GHIDRA_PROJECTS/$BASENAME"
mkdir -p "$GHIDRA_PROJECT_DIR"

if [[ $PE_COUNT -eq 0 ]]; then
    echo "[!] No PE images found to analyze."
    exit 0
fi

echo "[*] Importing $PE_COUNT binaries into Ghidra project: $BASENAME"

"$GHIDRA_HEADLESS" \
    "$GHIDRA_PROJECT_DIR" "$BASENAME" \
    -import "$RUN_PE_OUT" \
    -recursive \
    -loader BinaryLoader \
    -postScript ExportFunctionInfoScript.java "$GHIDRA_PROJECT_DIR/function_report.txt" \
    -scriptPath "$SCRIPT_DIR" \
    -log "$GHIDRA_PROJECT_DIR/ghidra_import.log" \
    -max-cpu "$(nproc)" \
    2>&1 | tee "$GHIDRA_PROJECT_DIR/ghidra_run.log"

echo ""
echo "══════════════════════════════════════════"
echo " DONE"
echo "══════════════════════════════════════════"
echo " PFS output  : $RUN_PFS_OUT"
echo " UEFI dump   : $DUMP_DIR"
echo " PE images   : $RUN_PE_OUT ($PE_COUNT files)"
echo " Ghidra proj : $GHIDRA_PROJECT_DIR"
echo "══════════════════════════════════════════"
