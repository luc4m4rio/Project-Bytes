// Ghidra headless post-script
// Dumps function list, imports, and interesting strings for each analyzed binary.
// Output goes to <project_dir>/function_report.txt (passed as script arg).
//
// Run via analyzeHeadless -postScript ExportFunctionInfoScript.java <output_file>

import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import ghidra.util.task.TaskMonitor;

import java.io.*;
import java.util.*;

public class ExportFunctionInfoScript extends GhidraScript {

    // Strings of interest for NVRAM/password/SMM analysis
    private static final String[] KEYWORDS = {
        "password", "Password", "PASSWORD",
        "nvram", "NVRAM", "NvRam",
        "NvLock", "nvlock",
        "smm", "SMM", "SmmPassword",
        "bios", "BIOS",
        "sha256", "SHA256", "sha-256",
        "otp", "OTP",
        "credential", "Credential",
        "hash", "Hash", "HASH",
        "unlock", "Unlock",
        "admin", "Admin",
        "PwdHash", "pwdhash",
        "0xb2", "0xB2",          // SMI port
        "DBUtil", "dbutil",
        "9B0C1EC",               // CVE-2021-21551 IOCTL prefix
    };

    @Override
    public void run() throws Exception {
        String outputPath = getScriptArgs().length > 0
            ? getScriptArgs()[0]
            : "/tmp/ghidra_report.txt";

        String programName = currentProgram.getName();
        println("[ExportFunctionInfo] Analyzing: " + programName);

        try (PrintWriter out = new PrintWriter(new FileWriter(outputPath, true))) {
            out.println("\n========================================");
            out.println("BINARY: " + programName);
            out.println("PATH:   " + currentProgram.getExecutablePath());
            out.println("FORMAT: " + currentProgram.getExecutableFormat());
            out.println("LANG:   " + currentProgram.getLanguageID());
            out.println("========================================");

            // Functions
            out.println("\n--- FUNCTIONS ---");
            FunctionIterator funcs = currentProgram.getListing().getFunctions(true);
            int fcount = 0;
            while (funcs.hasNext()) {
                Function f = funcs.next();
                out.printf("  0x%08X  %s\n", f.getEntryPoint().getOffset(), f.getName());
                fcount++;
            }
            out.println("  Total: " + fcount);

            // Imports / external symbols
            out.println("\n--- IMPORTS ---");
            SymbolTable symTable = currentProgram.getSymbolTable();
            SymbolIterator extSyms = symTable.getExternalSymbols();
            while (extSyms.hasNext()) {
                Symbol s = extSyms.next();
                out.println("  " + s.getName() + "  [" + s.getSource() + "]");
            }

            // Defined strings + keyword hits
            out.println("\n--- KEYWORD HITS IN STRINGS ---");
            Memory mem = currentProgram.getMemory();
            DataIterator dataIter = currentProgram.getListing().getDefinedData(true);
            while (dataIter.hasNext()) {
                Data d = dataIter.next();
                if (d.hasStringValue()) {
                    String val = d.getDefaultValueRepresentation();
                    for (String kw : KEYWORDS) {
                        if (val.contains(kw)) {
                            out.printf("  0x%08X  %s\n",
                                d.getAddress().getOffset(), val);
                            break;
                        }
                    }
                }
            }

            // Raw memory scan for keyword byte patterns
            out.println("\n--- RAW MEMORY KEYWORD SCAN ---");
            for (MemoryBlock block : mem.getBlocks()) {
                if (!block.isInitialized()) continue;
                byte[] bytes;
                try {
                    bytes = new byte[(int) block.getSize()];
                    block.getBytes(block.getStart(), bytes);
                } catch (Exception e) {
                    continue;
                }
                String blockStr = new String(bytes, java.nio.charset.StandardCharsets.ISO_8859_1);
                for (String kw : KEYWORDS) {
                    int idx = 0;
                    while ((idx = blockStr.indexOf(kw, idx)) >= 0) {
                        long addr = block.getStart().getOffset() + idx;
                        // Extract surrounding context (up to 64 chars)
                        int start = Math.max(0, idx - 8);
                        int end = Math.min(blockStr.length(), idx + kw.length() + 48);
                        String ctx = blockStr.substring(start, end)
                            .replaceAll("[\\x00-\\x1F\\x7F-\\xFF]", ".");
                        out.printf("  0x%08X  [%s]  ...%s...\n", addr, kw, ctx);
                        idx += kw.length();
                    }
                }
            }

            out.println("\n--- END: " + programName + " ---\n");
        }

        println("[ExportFunctionInfo] Done: " + programName);
    }
}
