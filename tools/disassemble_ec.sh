#!/usr/bin/env bash
# Produce readable source from a carved MEC EC payload.
#
#   (A) GNU objdump  -> linear ARCompact disassembly listing (.asm)
#   (B) Ghidra       -> recursive-descent analysis + C decompilation (.c)
#
# Prereqweqs (see repo README for exact install commands):
#   - Synopsys ARC GNU toolchain (arc-snps-elf-objdump)  ->  ARC_BIN
#   - Ghidra 11.x with the community ARCompact SLEIGH module installed  ->  GHIDRA_HOME
#
# Usage: ARC_BIN=/opt/arc/.../bin GHIDRA_HOME=/opt/ghidra_11.3.2_PUBLIC \
#        ./disassemble_ec.sh  EC_code_loaded_base0xBFCF0000.bin  0xBFCF0000  out_dir
set -euo pipefail
PAY="$1"; BASE="${2:-0xBFCF0000}"; OUT="${3:-.}"
ARC_BIN="${ARC_BIN:?set ARC_BIN to the ARC toolchain bin dir}"
mkdir -p "$OUT"

# (A) objdump linear disassembly ---------------------------------------------
OBJCOPY="$ARC_BIN/arc-snps-elf-objcopy"
OBJDUMP="$ARC_BIN/arc-snps-elf-objdump"
"$OBJCOPY" -I binary -O elf32-littlearc -B arc \
  --rename-section .data=.text,alloc,load,readonly,code,contents \
  --change-section-address .data="$BASE" "$PAY" "$OUT/ec.elf"
"$OBJDUMP" -d -M cpu=arc700 "$OUT/ec.elf" \
  | sed 's#_binary_[A-Za-z0-9_]*_bin_##g' > "$OUT/EC_disasm_arc700.asm"
echo "wrote $OUT/EC_disasm_arc700.asm"

# (B) Ghidra decompilation ----------------------------------------------------
if [ -n "${GHIDRA_HOME:-}" ]; then
  export EC_OUT="$OUT"
  SCRIPTS="$(cd "$(dirname "$0")/ghidra_scripts" && pwd)"
  # Seeds: start addresses of long clean objdump runs (optional but improves coverage)
  export SEEDS_FILE="${SEEDS_FILE:-}"
  rm -rf "$OUT/_ghidra_proj"; mkdir -p "$OUT/_ghidra_proj"
  "$GHIDRA_HOME/support/analyzeHeadless" "$OUT/_ghidra_proj" ec \
     -import "$PAY" -processor "ARCompact:LE:32:default" \
     -loader BinaryLoader -loader-baseAddr "$BASE" \
     -scriptPath "$SCRIPTS" -preScript SeedDisasm.java -postScript ExportEC.java \
     -deleteProject
  echo "wrote $OUT/3310_EC_decompiled.c (Ghidra)"
else
  echo "GHIDRA_HOME not set; skipped decompilation step."
fi
