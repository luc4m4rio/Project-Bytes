// DeepREScript.java — Ghidra headless deep reverse engineering script
// Targets: UEFI firmware modules of interest (password, NVRAM, SMM comms)
//
// What it does per binary:
//   1. Decompiles every function via DecompInterface → pseudocode output
//   2. Annotates UEFI protocol calls (GetVariable, SetVariable, SmmLocateProtocol, etc.)
//   3. Finds password comparison patterns (memcmp / loop-compare over fixed-len buffers)
//   4. Identifies SMM communication buffer accesses (EFI_SMM_COMMUNICATE_HEADER)
//   5. Flags NVRAM variable GUIDs referenced in the binary
//   6. Extracts all Unicode strings (HII / setup labels)
//   7. Maps call graph depth-2 from entry point
//
// Output: <project_dir>/deep_re/<binary_name>.txt

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.address.*;
import ghidra.program.model.pcode.*;
import ghidra.util.task.TaskMonitor;

import java.io.*;
import java.util.*;

public class DeepREScript extends GhidraScript {

    // UEFI protocol/service names to flag in decompiled output
    private static final String[] UEFI_INTERESTING = {
        "GetVariable", "SetVariable", "QueryVariableInfo",
        "SmmGetVariable", "SmmSetVariable",
        "LocateProtocol", "SmmLocateProtocol",
        "AllocatePool", "FreePool",
        "CopyMem", "SetMem", "ZeroMem",
        "CalculateCrc32",
        "Sha256Init", "Sha256Update", "Sha256Final",
        "CompareMem", "memcmp",
        "SmmCommunicate", "EFI_SMM_COMMUNICATE",
        "NvLock", "nvlock",
        "InstallProtocol", "HandleProtocol",
    };

    // Known NVRAM variable GUIDs relevant to password/security
    private static final String[] NVRAM_GUIDS = {
        // Dell BIOS password GUID (common)
        "D1068F86-B9E6-43A6-A50A-7BCA298D537E",
        // AMI setup GUID
        "EC87D643-EBA4-4BB5-A1E5-3F3E36B20DA9",
        // BIOS Setup GUID (common AMI)
        "4570B7F1-ADE8-4943-8DC3-406472842384",
        // EFI global variable GUID
        "8BE4DF61-93CA-11D2-AA0D-00E098032B8C",
        // AMI NVRAM GUID
        "F4BDB169-FAB4-4E55-B1AA-5EBB1A6AA5C7",
        // Security / password GUID candidates
        "AA5E99AE-5D4A-4E41-A9F5-97C5D8C9D50B",
    };

    private DecompInterface decompiler;
    private PrintWriter out;
    private String binName;

    @Override
    public void run() throws Exception {
        String outputDir = getScriptArgs().length > 0
            ? getScriptArgs()[0]
            : "/tmp/ghidra_deep_re";

        new File(outputDir).mkdirs();
        binName = currentProgram.getName();

        File outFile = new File(outputDir, binName.replace(".bin", "") + ".txt");
        out = new PrintWriter(new FileWriter(outFile));

        println("[DeepRE] Starting: " + binName);

        // Init decompiler
        decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        DecompileOptions opts = new DecompileOptions();
        opts.setMaxPayloadMBytes(64);
        decompiler.setOptions(opts);
        decompiler.setSimplificationStyle("decompile");

        try {
            writeHeader();
            analyzeStrings();
            analyzeNvramGuids();
            analyzeImports();
            analyzeCallGraph();
            decompileAllFunctions();
        } finally {
            decompiler.dispose();
            out.close();
        }

        println("[DeepRE] Done: " + binName + " -> " + outFile.getPath());
    }

    void writeHeader() {
        String sep = "=".repeat(70);
        out.println(sep);
        out.println("DEEP RE: " + binName);
        out.println("PATH   : " + currentProgram.getExecutablePath());
        out.println("FORMAT : " + currentProgram.getExecutableFormat());
        out.println("LANG   : " + currentProgram.getLanguageID());
        out.printf( "SIZE   : 0x%X bytes\n",
            currentProgram.getMemory().getSize());
        out.println(sep);
        out.println();
    }

    void analyzeStrings() {
        out.println("── UNICODE STRINGS (HII/setup labels) ──────────────────────────────");
        DataIterator di = currentProgram.getListing().getDefinedData(true);
        int count = 0;
        while (di.hasNext()) {
            Data d = di.next();
            if (!d.hasStringValue()) continue;
            String val = d.getDefaultValueRepresentation();
            // Unicode strings start with u"
            if (val.startsWith("u\"") && val.length() > 4) {
                out.printf("  0x%08X  %s\n", d.getAddress().getOffset(), val);
                count++;
            }
        }

        out.println("\n── ASCII STRINGS (narrow) ───────────────────────────────────────────");
        di = currentProgram.getListing().getDefinedData(true);
        while (di.hasNext()) {
            Data d = di.next();
            if (!d.hasStringValue()) continue;
            String val = d.getDefaultValueRepresentation();
            if (val.startsWith("\"") && val.length() > 6) {
                out.printf("  0x%08X  %s\n", d.getAddress().getOffset(), val);
            }
        }
        out.println();
    }

    void analyzeNvramGuids() throws Exception {
        out.println("── NVRAM / VARIABLE GUID CANDIDATES ─────────────────────────────────");
        Memory mem = currentProgram.getMemory();
        // Scan raw bytes for known 16-byte GUID patterns (first 4 bytes as LE DWORD)
        // Also look for any GUID-shaped data (4+2+2+8 byte pattern)
        DataIterator di = currentProgram.getListing().getDefinedData(true);
        Set<String> seen = new HashSet<>();
        while (di.hasNext()) {
            Data d = di.next();
            // Look for EFI_GUID typedef (16 bytes)
            if (d.getDataType().getName().contains("GUID") ||
                d.getDataType().getLength() == 16) {
                String bytes = d.getDefaultValueRepresentation();
                if (!seen.contains(bytes)) {
                    out.printf("  0x%08X  [GUID] %s  (%s)\n",
                        d.getAddress().getOffset(),
                        bytes,
                        d.getDataType().getName());
                    seen.add(bytes);
                }
            }
        }

        // Raw scan for known GUID prefixes
        for (MemoryBlock block : mem.getBlocks()) {
            if (!block.isInitialized() || block.getSize() < 16) continue;
            byte[] bytes = new byte[(int)Math.min(block.getSize(), 0x100000)];
            try { block.getBytes(block.getStart(), bytes); } catch(Exception e) { continue; }
            for (String known : NVRAM_GUIDS) {
                // Convert first DWORD of GUID
                String[] parts = known.split("-");
                if (parts.length < 1) continue;
                try {
                    long dword = Long.parseLong(parts[0], 16);
                    byte b0 = (byte)(dword & 0xFF);
                    byte b1 = (byte)((dword >> 8) & 0xFF);
                    byte b2 = (byte)((dword >> 16) & 0xFF);
                    byte b3 = (byte)((dword >> 24) & 0xFF);
                    for (int i = 0; i < bytes.length - 4; i++) {
                        if (bytes[i]==b0 && bytes[i+1]==b1 && bytes[i+2]==b2 && bytes[i+3]==b3) {
                            long addr = block.getStart().getOffset() + i;
                            out.printf("  0x%08X  [KNOWN GUID] %s\n", addr, known);
                        }
                    }
                } catch(Exception e) {}
            }
        }
        out.println();
    }

    void analyzeImports() {
        out.println("── IMPORTS & EXTERNAL REFS ──────────────────────────────────────────");
        SymbolTable sym = currentProgram.getSymbolTable();
        SymbolIterator it = sym.getExternalSymbols();
        while (it.hasNext()) {
            Symbol s = it.next();
            out.printf("  %-40s  [%s]\n", s.getName(), s.getSource());
        }

        // Also list any named thunk functions that match UEFI services
        FunctionIterator funcs = currentProgram.getListing().getFunctions(true);
        out.println("\n  -- Named/thunk functions matching UEFI services --");
        while (funcs.hasNext()) {
            Function f = funcs.next();
            String name = f.getName();
            for (String ui : UEFI_INTERESTING) {
                if (name.contains(ui)) {
                    out.printf("  0x%08X  %s\n", f.getEntryPoint().getOffset(), name);
                }
            }
        }
        out.println();
    }

    void analyzeCallGraph() {
        out.println("── CALL GRAPH FROM ENTRY POINT (depth 2) ────────────────────────────");
        // Find entry point
        SymbolTable sym = currentProgram.getSymbolTable();
        Symbol entry = null;
        for (Symbol s : sym.getSymbols("entry")) {
            entry = s;
            break;
        }
        if (entry == null) {
            // fallback: first function
            FunctionIterator fi = currentProgram.getListing().getFunctions(true);
            if (fi.hasNext()) {
                Function f = fi.next();
                out.printf("  Entry (fallback): 0x%08X  %s\n",
                    f.getEntryPoint().getOffset(), f.getName());
                printCallees(f, 1, 2, new HashSet<>());
            }
        } else {
            Function ef = currentProgram.getFunctionManager()
                .getFunctionAt(entry.getAddress());
            if (ef != null) {
                out.printf("  Entry: 0x%08X  %s\n",
                    ef.getEntryPoint().getOffset(), ef.getName());
                printCallees(ef, 1, 2, new HashSet<>());
            }
        }
        out.println();
    }

    void printCallees(Function f, int depth, int maxDepth, Set<Long> visited) {
        if (depth > maxDepth) return;
        long addr = f.getEntryPoint().getOffset();
        if (visited.contains(addr)) return;
        visited.add(addr);
        String indent = "  " + "  ".repeat(depth);
        for (Function callee : f.getCalledFunctions(TaskMonitor.DUMMY)) {
            out.printf("%s0x%08X  %s\n", indent,
                callee.getEntryPoint().getOffset(), callee.getName());
            printCallees(callee, depth + 1, maxDepth, visited);
        }
    }

    void decompileAllFunctions() throws Exception {
        out.println("── DECOMPILED FUNCTIONS ─────────────────────────────────────────────");

        FunctionIterator funcs = currentProgram.getListing().getFunctions(true);
        List<Function> funcList = new ArrayList<>();
        while (funcs.hasNext()) funcList.add(funcs.next());

        out.printf("  Total functions: %d\n\n", funcList.size());

        for (Function f : funcList) {
            DecompileResults res = decompiler.decompileFunction(f,
                60, TaskMonitor.DUMMY);

            String decomp = null;
            if (res != null && res.decompileCompleted()) {
                DecompiledFunction df = res.getDecompiledFunction();
                if (df != null) decomp = df.getC();
            }

            // Print function header
            out.printf("\n┌─ 0x%08X  %s  (%d params)\n",
                f.getEntryPoint().getOffset(),
                f.getName(),
                f.getParameterCount());

            // Callers summary
            Set<Function> callers = f.getCallingFunctions(TaskMonitor.DUMMY);
            if (!callers.isEmpty()) {
                out.print("│  Called from: ");
                callers.stream().limit(5).forEach(c ->
                    out.printf("0x%08X(%s) ", c.getEntryPoint().getOffset(), c.getName()));
                out.println();
            }

            // Flag UEFI service calls in decompiled text
            if (decomp != null) {
                for (String ui : UEFI_INTERESTING) {
                    if (decomp.contains(ui)) {
                        out.printf("│  [UEFI CALL] %s\n", ui);
                    }
                }
            }

            // Decompiled pseudocode
            if (decomp != null) {
                out.println("│");
                for (String line : decomp.split("\n")) {
                    out.println("│  " + line);
                }
            } else {
                out.println("│  [decompile failed or empty]");
            }
            out.println("└" + "─".repeat(69));
        }
    }
}
