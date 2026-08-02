import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import java.io.*;
import java.util.*;

// Pre-analysis: disassemble at many known-good code offsets (from objdump clean runs)
// so Ghidra's flow analysis can then find real functions/call targets reliably.
public class SeedDisasm extends GhidraScript {
    public void run() throws Exception {
        String sf = System.getenv("SEEDS_FILE");
        List<Long> seeds = new ArrayList<>();
        seeds.add(0xBFCF0000L); // reset entry
        if (sf != null) {
            BufferedReader br = new BufferedReader(new FileReader(sf));
            String ln;
            while ((ln = br.readLine()) != null) {
                ln = ln.trim();
                if (ln.isEmpty()) continue;
                try { seeds.add(Long.parseLong(ln, 16)); } catch (Exception e) {}
            }
            br.close();
        }
        addEntryPoint(toAddr(0xBFCF0000L));
        int done = 0;
        for (Long s : seeds) {
            Address a = toAddr(s);
            if (getInstructionAt(a) != null) continue;   // already code
            try { disassemble(a); done++; } catch (Exception e) {}
        }
        println("SeedDisasm: seeded " + done + " of " + seeds.size() + " points");
    }
}
