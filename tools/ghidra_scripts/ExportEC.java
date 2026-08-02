import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class ExportEC extends GhidraScript {
    public void run() throws Exception {
        String outDir = System.getenv("EC_OUT");
        if (outDir == null) outDir = "/tmp";
        FunctionManager fm = currentProgram.getFunctionManager();
        Listing listing = currentProgram.getListing();

        // 1) Collect genuine function entries = destinations of CALL instructions.
        Set<Address> entries = new TreeSet<>();
        entries.add(toAddr(0xBFCF0000L));
        InstructionIterator it = listing.getInstructions(true);
        while (it.hasNext()) {
            Instruction ins = it.next();
            for (Reference r : ins.getReferencesFrom())
                if (r.getReferenceType().isCall()) entries.add(r.getToAddress());
        }
        println("Genuine call-target entries: " + entries.size());

        // 2) Remove ALL existing functions (drop over-seeded junk boundaries), keep instructions.
        List<Function> all = new ArrayList<>();
        for (Function f : fm.getFunctions(true)) all.add(f);
        for (Function f : all) { try { removeFunction(f); } catch (Exception e) {} }

        // 3) Recreate functions only at genuine entries that hold valid code.
        int made=0;
        for (Address d : entries) {
            try {
                if (getInstructionAt(d) == null) disassemble(d);
                if (getInstructionAt(d) == null) continue;   // couldn't decode -> skip (data)
                if (createFunction(d, null) != null) made++;
            } catch (Exception e) {}
        }
        println("Recreated " + made + " functions at call targets");

        // 4) Decompile. Write a CLEAN file (skip pure halt-only stubs) and a FULL file.
        DecompInterface dec = new DecompInterface();
        dec.setOptions(new DecompileOptions());
        dec.openProgram(currentProgram);

        PrintWriter cw  = new PrintWriter(new BufferedWriter(new FileWriter(outDir + "/3310_EC_decompiled.c")));
        PrintWriter fw  = new PrintWriter(new BufferedWriter(new FileWriter(outDir + "/3310_EC_functions.txt")));
        String hdr = "/* Dell Latitude 3310 Embedded Controller firmware (Microchip MEC, ARCompact LE)\n"
                   + "   Load base 0xBFCF0000  -  Ghidra decompilation  -  lang=" + currentProgram.getLanguageID() + "\n"
                   + "   Note: 'halt_unimplemented' markers are ARCompact opcodes the community SLEIGH\n"
                   + "   module does not yet model; surrounding logic is still valid. */\n";
        cw.println(hdr);
        int ok=0, stub=0;
        for (Function f : fm.getFunctions(true)) {
            long sz = f.getBody().getNumAddresses();
            DecompileResults r = dec.decompileFunction(f, 120, monitor);
            String c = (r!=null && r.decompileCompleted() && r.getDecompiledFunction()!=null)
                       ? r.getDecompiledFunction().getC() : null;
            boolean isStub = (c==null) || (sz<=4) ||
                    ( (c.contains("halt_baddata")||c.contains("halt_unimplemented"))
                       && !c.matches("(?s).*\\b(for|while|do|switch)\\b.*")
                       && c.split("\n").length < 9 );
            fw.println(f.getEntryPoint() + "\t" + sz + "\t" + f.getName() + (isStub?"\tSTUB":""));
            if (c==null) { cw.println("/* decompile failed: "+f.getName()+" */\n"); continue; }
            if (isStub) { stub++; continue; }
            cw.println(c);
            ok++;
        }
        cw.close(); fw.close();
        println("Wrote CLEAN functions=" + ok + "  skipped stubs=" + stub);
    }
}
