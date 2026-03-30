// XRefPasswordScript.java — Traces cross-references to password/NVRAM addresses
// and decompiles the referencing functions plus their call chains (depth 3).
// Run as: -postScript XRefPasswordScript.java <output_dir>

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import ghidra.program.model.mem.*;
import ghidra.util.task.TaskMonitor;

import java.io.*;
import java.util.*;

public class XRefPasswordScript extends GhidraScript {

    // Target addresses to trace XRefs from (adjust per binary)
    // PE_0529 password/NVRAM cluster
    private static final long[] TARGET_ADDRS = {
        0x000D4500L, // "Show Password"
        0x000D4510L, // "Password"
        0x000D4520L, // "Secured"
        0x000E91F0L, // "Password Jumper"
        0x000E9258L, // "Clear NVRAM Jumper"
        0x0007EA70L, // "Password Setup"
        0x0007F110L, // "Off - Disk password incorrect"
        0x0007F130L, // "Off - Boot password incorrect"
        0x0007FB10L, // "NVRAM Data Invalid"
        0x0007FB28L, // "NVRAM Cleared By Jumper"
        0x0007FBB0L, // "NVRAM Checksum Error"
        0x00081680L, // "Unable to log to NVRAM"
    };

    private DecompInterface decompiler;
    private PrintWriter out;
    private Set<Long> decompiledFunctions = new HashSet<>();

    @Override
    public void run() throws Exception {
        String outputDir = getScriptArgs().length > 0
            ? getScriptArgs()[0]
            : "/tmp/ghidra_xref";
        new File(outputDir).mkdirs();

        String binName = currentProgram.getName();
        File outFile = new File(outputDir, binName.replace(".bin","") + "_xref.txt");
        out = new PrintWriter(new FileWriter(outFile));

        decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        DecompileOptions opts = new DecompileOptions();
        opts.setMaxPayloadMBytes(128);
        decompiler.setOptions(opts);
        decompiler.setSimplificationStyle("decompile");

        out.println("=".repeat(70));
        out.println("XREF TRACE: " + binName);
        out.println("=".repeat(70));

        try {
            for (long targetAddr : TARGET_ADDRS) {
                Address addr = currentProgram.getAddressFactory()
                    .getDefaultAddressSpace().getAddress(targetAddr);

                // Get data/label at this address
                Data data = currentProgram.getListing().getDataAt(addr);
                String label = data != null ? data.getDefaultValueRepresentation() : "(no data)";
                if (label.length() > 80) label = label.substring(0, 80) + "...";

                out.printf("\n%s\n", "─".repeat(70));
                out.printf("TARGET: 0x%08X  %s\n", targetAddr, label);
                out.printf("%s\n", "─".repeat(70));

                // Find all references TO this address
                ReferenceIterator refs =
                    currentProgram.getReferenceManager().getReferencesTo(addr);

                int refCount = 0;
                while (refs.hasNext()) {
                    Reference ref = refs.next();
                    Address fromAddr = ref.getFromAddress();
                    Function func = currentProgram.getFunctionManager()
                        .getFunctionContaining(fromAddr);

                    if (func != null) {
                        out.printf("\n  [XREF from 0x%08X in %s]\n",
                            fromAddr.getOffset(), func.getName());
                        decompileFunctionChain(func, 0, 3);
                        refCount++;
                    }
                }
                if (refCount == 0) {
                    out.println("  (no direct xrefs found)");
                }
            }
        } finally {
            decompiler.dispose();
            out.close();
        }

        println("[XRefPassword] Done -> " + outFile.getPath());
    }

    void decompileFunctionChain(Function f, int depth, int maxDepth)
            throws Exception {
        if (depth > maxDepth) return;
        long addr = f.getEntryPoint().getOffset();
        if (decompiledFunctions.contains(addr)) {
            out.printf("%s[already shown: 0x%08X %s]\n",
                "  ".repeat(depth+1), addr, f.getName());
            return;
        }
        decompiledFunctions.add(addr);

        String indent = "  ".repeat(depth + 1);
        out.printf("%s┌─ 0x%08X  %s  (%d params)\n",
            indent, addr, f.getName(), f.getParameterCount());

        // Decompile
        DecompileResults res = decompiler.decompileFunction(f, 90, TaskMonitor.DUMMY);
        if (res != null && res.decompileCompleted()) {
            DecompiledFunction df = res.getDecompiledFunction();
            if (df != null) {
                String code = df.getC();
                // Flag password/NVRAM/SMM lines
                for (String line : code.split("\n")) {
                    String trimmed = line.trim();
                    boolean interesting = trimmed.contains("password") ||
                        trimmed.contains("Password") ||
                        trimmed.contains("NVRAM") || trimmed.contains("nvram") ||
                        trimmed.contains("hash") || trimmed.contains("Hash") ||
                        trimmed.contains("GetVariable") ||
                        trimmed.contains("SetVariable") ||
                        trimmed.contains("CompareMem") ||
                        trimmed.contains("ZeroMem") ||
                        trimmed.contains("CopyMem") ||
                        trimmed.contains("Smm") || trimmed.contains("SMM") ||
                        trimmed.contains("sha") || trimmed.contains("SHA") ||
                        trimmed.contains("0xb2") || trimmed.contains("0xB2") ||
                        trimmed.contains("jumper") || trimmed.contains("Jumper") ||
                        trimmed.contains("lock") || trimmed.contains("Lock") ||
                        trimmed.contains("incorrect") || trimmed.contains("Invalid") ||
                        trimmed.contains("checksum") || trimmed.contains("Checksum") ||
                        // mark ALL calls (function pointer calls through tables)
                        trimmed.contains("(**(code **)(");

                    String marker = interesting ? " ◄◄◄" : "";
                    out.println(indent + "│  " + line + marker);
                }
            }
        } else {
            out.println(indent + "│  [decompile failed]");
        }
        out.println(indent + "└" + "─".repeat(60));

        // Recurse into callees (only 1 level deep after depth 0)
        if (depth < 1) {
            for (Function callee : f.getCalledFunctions(TaskMonitor.DUMMY)) {
                long calleeAddr = callee.getEntryPoint().getOffset();
                if (!decompiledFunctions.contains(calleeAddr)) {
                    decompileFunctionChain(callee, depth + 1, maxDepth);
                }
            }
        }
    }
}
