import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.pcode.*;
import java.io.*;
import java.util.*;

// Report EVERY instruction whose pcl-folded / absolute constant lands in a target range,
// regardless of whether the instruction is inside a defined function.
public class TableRefs extends GhidraScript {
    long LO=0xBFCF0000L, HI=0xBFD16E40L;
    public void run() throws Exception {
        String outDir=System.getenv("EC_OUT"); if(outDir==null) outDir="/tmp";
        Listing lst=currentProgram.getListing();
        FunctionManager fm=currentProgram.getFunctionManager();
        // target ranges: [start,end,name]
        long[][] T={
          {0xBFD12D6CL,0xBFD12D8FL,0}, // Table A lowercase 0-9a-z
          {0xBFD12D8FL,0xBFD12DB3L,1}, // Table B uppercase 0-9A-Z
          {0xBFD084B0L,0xBFD085B0L,2}, // SHA-256 K-table
          {0xBFCFAD7CL,0xBFCFAF7CL,3}, // CRC-32 table
        };
        String[] tn={"TableA_lc(0-9a-z)","TableB_uc(0-9A-Z)","SHA256_K","CRC32_tbl"};
        PrintWriter pw=new PrintWriter(new BufferedWriter(new FileWriter(outDir+"/3310_EC_table_refs.txt")));
        long scanned=0, withPcl=0;
        // instrAddr -> set of target-indices it references
        List<long[]> refs=new ArrayList<>(); // {instrAddr, targetIndex, resolvedAddr}
        InstructionIterator it=lst.getInstructions(true);
        while(it.hasNext()){
            Instruction ins=it.next(); scanned++;
            long ia=ins.getAddress().getOffset();
            long pclv=ia & ~3L;
            List<Long> consts=new ArrayList<>(); boolean hasPcl=false;
            for(PcodeOp op: ins.getPcode())
                for(Varnode vn: op.getInputs())
                    if(vn!=null && vn.isConstant()){
                        long v=vn.getOffset()&0xFFFFFFFFL; consts.add(v);
                        if(v==pclv) hasPcl=true;
                    }
            if(hasPcl) withPcl++;
            // candidate resolved addresses
            Set<Long> cand=new HashSet<>();
            for(long c:consts){
                if(hasPcl && c!=pclv){ cand.add((pclv+c)&0xFFFFFFFFL); cand.add((pclv+(int)c)&0xFFFFFFFFL); }
                if(!hasPcl && c>=LO && c<=HI) cand.add(c);       // absolute mov-limm
            }
            for(long a:cand)
                for(int k=0;k<T.length;k++)
                    if(a>=T[k][0] && a<T[k][1]) refs.add(new long[]{ia,k,a});
        }
        pw.println("scanned instructions="+scanned+"  (with pcl folding="+withPcl+")\n");
        for(int k=0;k<T.length;k++){
            pw.println("=== "+tn[k]+"  [0x"+Long.toHexString(T[k][0])+"..0x"+Long.toHexString(T[k][1])+"] ===");
            int c=0;
            for(long[] r:refs) if(r[1]==k){
                Address ia=toAddr(r[0]); Function f=fm.getFunctionContaining(ia);
                pw.printf("   ref @ 0x%08X -> 0x%08X   %s%n", r[0], r[2], f!=null?("in "+f.getName()):"(not in a function)");
                c++;
            }
            if(c==0) pw.println("   (no resolved references found)");
            pw.println();
        }
        pw.close();
        println("TableRefs done. total resolved refs="+refs.size());
    }
}
