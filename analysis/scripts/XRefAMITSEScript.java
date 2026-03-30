// XRefAMITSEScript.java
// Targeted deep XRef tracer for PE_0119 (AMI TSE) — password authentication path
// Searches for DellPassword/LinkDellPasswordData string XRefs and traces
// hash comparison, CompareMem, and SHA-256 pattern functions
//
// Usage: analyzeHeadless ... -postScript XRefAMITSEScript.java <output_file>

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import ghidra.app.decompiler.*;
import ghidra.util.task.TaskMonitor;
import java.io.*;
import java.util.*;

public class XRefAMITSEScript extends GhidraScript {

    private DecompInterface decompiler;
    private PrintWriter out;
    private Set<Address> visitedFunctions = new HashSet<>();
    private Map<Address, String> functionDecomp = new HashMap<>();

    // String addresses in PE_0119 that we want to trace XRefs from
    // These are filled in dynamically by scanning for the strings
    private Map<Long, String> targetStrings = new LinkedHashMap<>();

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String outputPath = args.length > 0 ? args[0] :
            "/home/user/Project-Bytes/ghidra_projects/Latitude_7X00_1.19.1/deep_re/PE_0119_xref.txt";

        out = new PrintWriter(new FileWriter(outputPath));

        decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);

        String progName = currentProgram.getName();
        out.println("======================================================================");
        out.println("AMI TSE XREF ANALYSIS: " + progName);
        out.println("TARGET: DellPassword / LinkDellPasswordData / Hash comparison");
        out.println("======================================================================");
        out.println();

        // Phase 1: Find DellPassword / LinkDellPasswordData strings
        findTargetStrings();

        // Phase 2: Find hash-related patterns (32-byte buffers, CompareMem)
        findHashPatterns();

        // Phase 3: Find SHA-256 init constants
        findSHA256Patterns();

        out.println();
        out.println("======================================================================");
        out.println("END OF ANALYSIS");
        out.println("======================================================================");
        out.flush();
        out.close();
        decompiler.dispose();

        println("[XRefAMITSE] Done: " + outputPath);
    }

    private void findTargetStrings() throws Exception {
        out.println("── PHASE 1: Target String XRef Trace ───────────────────────────────");
        out.println();

        Memory mem = currentProgram.getMemory();
        FunctionManager fm = currentProgram.getFunctionManager();
        AddressFactory af = currentProgram.getAddressFactory();

        // Strings to search for (as UTF-16LE patterns)
        String[] searchStrings = {
            "DellPassword",
            "LinkDellPasswordData",
            "Incorrect Password",
            "Enter Admin Password",
            "Passwords do not match",
            "Password",
            "password"
        };

        for (String needle : searchStrings) {
            out.println("── Searching for: \"" + needle + "\" ──────────────────");
            List<Address> found = findStringAddresses(needle);
            if (found.isEmpty()) {
                out.println("  (not found)");
                continue;
            }

            for (Address strAddr : found) {
                out.println("  String @ " + strAddr);

                // Get XRefs to this address
                ReferenceManager rm = currentProgram.getReferenceManager();
                ReferenceIterator refs = rm.getReferencesTo(strAddr);
                List<Reference> refList = new ArrayList<>();
                while (refs.hasNext()) refList.add(refs.next());

                if (refList.isEmpty()) {
                    out.println("    (no XRefs)");
                    continue;
                }

                for (Reference ref : refList) {
                    Address fromAddr = ref.getFromAddress();
                    Function func = fm.getFunctionContaining(fromAddr);
                    if (func == null) {
                        out.println("    XRef from " + fromAddr + " (no function)");
                        continue;
                    }

                    out.println("    XRef from " + fromAddr + " in " + func.getName() + " @ " + func.getEntryPoint());
                    decompileAndPrint(func, 0, 3);
                }
            }
            out.println();
        }
    }

    private void findHashPatterns() throws Exception {
        out.println("── PHASE 2: Hash Comparison Pattern Search ──────────────────────────");
        out.println();

        // Search for 32-byte (0x20) buffer references - typical SHA-256 digest size
        // Also look for calls with size arguments of 0x20, 0x28 (SHA variants)
        FunctionManager fm = currentProgram.getFunctionManager();

        out.println("  Scanning decompiled functions for 32-byte buffer ops (0x20 / 0x28)...");
        out.println("  Flagging: CompareMem, bcmp, memcmp patterns, [0x20] sized buffers");
        out.println();

        int scanned = 0;
        int flagged = 0;

        for (Function func : currentProgram.getFunctionManager().getFunctions(true)) {
            String decomp = getDecomp(func);
            if (decomp == null) continue;

            scanned++;

            boolean interesting = false;
            String reason = "";

            // Look for typical hash comparison patterns
            if (decomp.contains(",0x20)") || decomp.contains(",0x20,") ||
                decomp.contains(",32)") || decomp.contains("0x20 ==")) {
                interesting = true;
                reason += "[32-byte-op] ";
            }
            if (decomp.contains(",0x28)") || decomp.contains(",0x28,")) {
                interesting = true;
                reason += "[40-byte-op] ";
            }
            if ((decomp.toLowerCase().contains("compare") ||
                 decomp.toLowerCase().contains("bcmp") ||
                 decomp.toLowerCase().contains("memcmp")) &&
                (decomp.contains("0x20") || decomp.contains("0x10"))) {
                interesting = true;
                reason += "[compare-call] ";
            }
            // Password-related identifiers in decompiled code
            if (decomp.toLowerCase().contains("password") ||
                decomp.toLowerCase().contains("hash") ||
                decomp.toLowerCase().contains("digest")) {
                interesting = true;
                reason += "[password/hash-kw] ";
            }

            if (interesting) {
                flagged++;
                out.println("  FLAGGED: " + func.getName() + " @ " + func.getEntryPoint() + " — " + reason);
                printDecompWithHighlights(func, decomp,
                    new String[]{"0x20", "0x28", "compare", "Compare", "password", "Password", "hash", "Hash"});
                out.println();
            }
        }

        out.println("  Scanned " + scanned + " functions, flagged " + flagged);
        out.println();
    }

    private void findSHA256Patterns() throws Exception {
        out.println("── PHASE 3: SHA-256 Constant Search ─────────────────────────────────");
        out.println();

        // SHA-256 initial hash values (H0..H7)
        long[] sha256_init = {
            0x6a09e667L, 0xbb67ae85L, 0x3c6ef372L, 0xa54ff53aL,
            0x510e527fL, 0x9b05688cL, 0x1f83d9abL, 0x5be0cd19L
        };

        // SHA-256 round constants (first 4)
        long[] sha256_k0 = { 0x428a2f98L, 0x71374491L, 0xb5c0fbcfL, 0xe9b5dba5L };

        Memory mem = currentProgram.getMemory();
        AddressSpace space = currentProgram.getAddressFactory().getDefaultAddressSpace();

        out.println("  Searching for SHA-256 init constants (H0=0x6a09e667, H1=0xbb67ae85, ...):");

        for (long c : sha256_init) {
            searchConstantInMemory(c, "SHA256_INIT");
        }

        out.println();
        out.println("  Searching for SHA-256 round constants (K[0]=0x428a2f98, ...):");
        for (long c : sha256_k0) {
            searchConstantInMemory(c, "SHA256_K");
        }

        // SHA-1 init: 67452301 EFCDAB89 98BADCFE 10325476 C3D2E1F0
        long[] sha1_init = { 0x67452301L, 0xefcdab89L, 0x98badcfeL, 0x10325476L };
        out.println();
        out.println("  Searching for SHA-1 init constants (0x67452301, ...):");
        for (long c : sha1_init) {
            searchConstantInMemory(c, "SHA1_INIT");
        }

        out.println();
    }

    private void searchConstantInMemory(long value, String tag) throws Exception {
        Memory mem = currentProgram.getMemory();
        FunctionManager fm = currentProgram.getFunctionManager();

        // Search for 4-byte LE constant
        byte[] pattern = new byte[] {
            (byte)(value & 0xFF),
            (byte)((value >> 8) & 0xFF),
            (byte)((value >> 16) & 0xFF),
            (byte)((value >> 24) & 0xFF)
        };

        Address start = currentProgram.getMinAddress();
        Address end   = currentProgram.getMaxAddress();
        Address found = mem.findBytes(start, end, pattern, null, true, TaskMonitor.DUMMY);

        if (found != null) {
            Function func = fm.getFunctionContaining(found);
            String funcStr = func != null ? func.getName() + " @ " + func.getEntryPoint() : "(data section)";
            out.printf("    0x%08X @ %s — in %s [%s]%n", value, found, funcStr, tag);
        }
    }

    private List<Address> findStringAddresses(String needle) throws Exception {
        List<Address> results = new ArrayList<>();
        Memory mem = currentProgram.getMemory();

        // Search UTF-16LE
        byte[] utf16 = toUTF16LE(needle);
        Address start = currentProgram.getMinAddress();
        Address end   = currentProgram.getMaxAddress();

        Address found = start;
        while (found != null && found.compareTo(end) <= 0) {
            found = mem.findBytes(found, end, utf16, null, true, TaskMonitor.DUMMY);
            if (found != null) {
                results.add(found);
                try { found = found.add(utf16.length); } catch (Exception e) { break; }
            }
        }

        // Search ASCII
        byte[] ascii = needle.getBytes("ISO-8859-1");
        found = start;
        while (found != null && found.compareTo(end) <= 0) {
            found = mem.findBytes(found, end, ascii, null, true, TaskMonitor.DUMMY);
            if (found != null) {
                // Avoid re-adding addresses already found (might overlap with UTF-16 first byte match)
                boolean dup = false;
                for (Address a : results) {
                    if (Math.abs(a.getOffset() - found.getOffset()) < ascii.length) { dup = true; break; }
                }
                if (!dup) results.add(found);
                try { found = found.add(ascii.length); } catch (Exception e) { break; }
            }
        }

        return results;
    }

    private byte[] toUTF16LE(String s) {
        byte[] result = new byte[s.length() * 2];
        for (int i = 0; i < s.length(); i++) {
            result[i*2]   = (byte)(s.charAt(i) & 0xFF);
            result[i*2+1] = (byte)((s.charAt(i) >> 8) & 0xFF);
        }
        return result;
    }

    private String getDecomp(Function func) {
        Address ep = func.getEntryPoint();
        if (functionDecomp.containsKey(ep)) return functionDecomp.get(ep);

        try {
            DecompileResults res = decompiler.decompileFunction(func, 30, TaskMonitor.DUMMY);
            if (res != null && res.decompileCompleted()) {
                DecompiledFunction df = res.getDecompiledFunction();
                if (df != null) {
                    String d = df.getC();
                    functionDecomp.put(ep, d);
                    return d;
                }
            }
        } catch (Exception e) {}
        return null;
    }

    private void decompileAndPrint(Function func, int depth, int maxDepth) throws Exception {
        if (depth > maxDepth) return;
        if (visitedFunctions.contains(func.getEntryPoint())) return;
        visitedFunctions.add(func.getEntryPoint());

        String indent = "  ".repeat(depth + 2);
        String decomp = getDecomp(func);
        if (decomp == null) {
            out.println(indent + "[decompile failed: " + func.getName() + "]");
            return;
        }

        out.println(indent + "┌─ " + func.getEntryPoint() + "  " + func.getName());

        // Print decompiled code with highlighted lines
        printDecompWithHighlights(func, decomp,
            new String[]{"password", "Password", "DellPassword", "hash", "Hash",
                         "GetVariable", "SetVariable", "0x20", "Compare", "compare"});

        // Recurse into callees if depth allows
        if (depth < maxDepth) {
            FunctionManager fm = currentProgram.getFunctionManager();
            Set<Function> callees = func.getCalledFunctions(TaskMonitor.DUMMY);
            int calleeCount = 0;
            for (Function callee : callees) {
                if (calleeCount++ > 8) break; // limit fanout
                decompileAndPrint(callee, depth + 1, maxDepth);
            }
        }
    }

    private void printDecompWithHighlights(Function func, String decomp, String[] keywords) {
        String indent = "    ";
        String[] lines = decomp.split("\n");
        int printed = 0;
        boolean inFunc = false;

        for (String line : lines) {
            // Print all lines, flag interesting ones
            boolean flagged = false;
            for (String kw : keywords) {
                if (line.contains(kw)) { flagged = true; break; }
            }

            // Skip very long data lines
            if (line.length() > 200) continue;

            if (flagged) {
                out.println(indent + "◄◄◄ " + line.trim());
            } else {
                out.println(indent + "    " + line.trim());
            }
            printed++;
            if (printed > 60) {
                out.println(indent + "    ... [truncated at 60 lines] ...");
                break;
            }
        }
    }
}
