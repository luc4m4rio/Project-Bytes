import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.pcode.*;
import java.io.*;
import java.util.*;

public class FindCrypto extends GhidraScript {
    long LO=0xBFCF0000L, HI=0xBFD16E40L;
    public void run() throws Exception {
        String outDir=System.getenv("EC_OUT"); if(outDir==null) outDir="/tmp";
        FunctionManager fm=currentProgram.getFunctionManager();
        Listing lst=currentProgram.getListing();

        // xref via pcode constants (captures pcl-folded and mov-limm addresses)
        Map<Long,Set<Function>> xref=new HashMap<>();
        InstructionIterator it=lst.getInstructions(true);
        while(it.hasNext()){
            Instruction ins=it.next();
            Function f=fm.getFunctionContaining(ins.getAddress());
            if(f==null) continue;
            long pclv=ins.getAddress().getOffset() & ~3L;
            // collect this instruction's pcode constants
            List<Long> consts=new ArrayList<>();
            boolean hasPcl=false;
            for(PcodeOp op: ins.getPcode())
                for(Varnode vn: op.getInputs())
                    if(vn!=null && vn.isConstant()){
                        long v=vn.getOffset() & 0xFFFFFFFFL;
                        consts.add(v);
                        if(v==pclv) hasPcl=true;
                    }
            for(long c:consts){
                long t=-1;
                if(hasPcl){
                    if(c!=pclv){                 // c is an offset relative to pcl
                        long a=pclv + c, b=pclv + (int)c; // unsigned & signed offset
                        for(long cand:new long[]{a,b}) if(cand>=LO&&cand<=HI){t=cand; xref.computeIfAbsent(t,k->new HashSet<>()).add(f);}
                        continue;
                    }
                } else if(c>=LO && c<=HI){        // absolute mov-limm address
                    xref.computeIfAbsent(c,k->new HashSet<>()).add(f);
                }
            }
        }

        println("DEBUGCOUNT xref_targets="+xref.size()+" funcs="+fm.getFunctionCount());
        {int cov=0; for(long a=0xBFD07000L;a<0xBFD09000L;a+=2){ if(fm.getFunctionContaining(toAddr(a))!=null){cov++;} } println("DEBUG high-region(0xBFD07000-0xBFD09000) addrs-in-funcs="+cov);}
        long[] tgts   ={0xBFD084B0L,0xBFCFAD7CL,0xBFCFAD80L,0xBFD04DC8L,0xBFD04DF8L,0xBFD0525CL,0xBFD12D6CL,0xBFD12D70L};
        String[] tname={"SHA256_K_table","CRC32_table[0]","CRC32_table[1]","str:VerifyEcSdsaSignature",
                        "str:dellbatterydell#1","str:dellbatterydell#2","base62_table","base62_table+4"};
        PrintWriter pw=new PrintWriter(new BufferedWriter(new FileWriter(outDir+"/3310_EC_crypto_report.txt")));
        DecompInterface dec=new DecompInterface(); dec.setOptions(new DecompileOptions()); dec.openProgram(currentProgram);
        Set<Function> found=new LinkedHashSet<>();

        pw.println("=== functions referencing crypto/encoding data (pcode-constant xref) ===");
        for(int i=0;i<tgts.length;i++){
            Set<Function> fs=new TreeSet<>((a,b)->a.getEntryPoint().compareTo(b.getEntryPoint()));
            for(long t=tgts[i]-64;t<=tgts[i]+64;t++){ Set<Function> s=xref.get(t); if(s!=null) fs.addAll(s);}
            pw.println("\n"+tname[i]+" @0x"+Long.toHexString(tgts[i])+"  <- "+fs.size()+" fn:");
            for(Function f:fs){ pw.println("   "+f.getEntryPoint()+"  size="+f.getBody().getNumAddresses()+"  "+f.getName()); found.add(f);}
        }

        // Heuristic: hash/crypto = high logic-op density
        pw.println("\n=== instruction-mix heuristic ===");
        Set<String> logic=new HashSet<>(Arrays.asList("xor","xor_s","and","and_s","or","or_s","bic","bic_s",
            "asl","asl_s","asr","asr_s","lsr","lsr_s","ror","rol","bset","bclr","btst","bxor","abs","norm","swap","extb","extw"));
        List<Object[]> sc=new ArrayList<>();
        for(Function f:fm.getFunctions(true)){
            long tot=0,lg=0,x=0,r=0;
            InstructionIterator fi=lst.getInstructions(f.getBody(),true);
            while(fi.hasNext()){Instruction in=fi.next();String m=in.getMnemonicString().toLowerCase();tot++;
                if(logic.contains(m))lg++; if(m.startsWith("xor"))x++; if(m.startsWith("ror")||m.startsWith("rol"))r++;}
            if(tot>=15 && lg*100/tot>=25 && (x+r)>=2) sc.add(new Object[]{(double)lg/tot,f,tot,lg,x,r});
        }
        sc.sort((a,b)->Double.compare((double)b[0],(double)a[0]));
        for(Object[] q:sc){Function f=(Function)q[1];
            pw.printf("   %s %-18s n=%d logic=%d(%.0f%%) xor=%d rot=%d%n",f.getEntryPoint(),f.getName(),(long)q[2],(long)q[3],(double)q[0]*100,(long)q[4],(long)q[5]);
            found.add(f);}

        pw.println("\n\n=== decompilation of identified functions ===");
        for(Function f:found){
            DecompileResults dr=dec.decompileFunction(f,120,monitor);
            pw.println("\n/* ---- "+f.getName()+" @ "+f.getEntryPoint()+"  (size "+f.getBody().getNumAddresses()+") ---- */");
            if(dr!=null&&dr.decompileCompleted()&&dr.getDecompiledFunction()!=null) pw.println(dr.getDecompiledFunction().getC());
            else pw.println("   (decompile failed)");
        }
        pw.close();
        println("crypto/encoding functions identified: "+found.size());
    }
}
