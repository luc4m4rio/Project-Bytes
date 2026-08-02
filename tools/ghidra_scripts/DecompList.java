import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class DecompList extends GhidraScript {
    public void run() throws Exception {
        String outDir=System.getenv("EC_OUT"); if(outDir==null) outDir="/tmp";
        String list=System.getenv("FN_LIST"); if(list==null) return;
        FunctionManager fm=currentProgram.getFunctionManager();
        // ensure functions exist at each address
        for(String h: list.split(",")){
            long a=Long.parseLong(h.trim(),16);
            Address ad=toAddr(a);
            if(getInstructionAt(ad)==null) disassemble(ad);
            if(fm.getFunctionAt(ad)==null) { try{createFunction(ad,null);}catch(Exception e){} }
        }
        DecompInterface dec=new DecompInterface(); dec.setOptions(new DecompileOptions()); dec.openProgram(currentProgram);
        PrintWriter pw=new PrintWriter(new BufferedWriter(new FileWriter(outDir+"/3310_EC_transform_funcs.txt")));
        for(String h: list.split(",")){
            long a=Long.parseLong(h.trim(),16);
            Function f=fm.getFunctionAt(toAddr(a));
            pw.println("\n/* ================= 0x"+Long.toHexString(a)+"  ("+(f!=null?f.getName():"?")+") ================= */");
            if(f==null){ pw.println("(no function)"); continue; }
            // callees
            Set<Address> callees=new TreeSet<>();
            for(Instruction ins: getInstructions(f)){
                for(Reference r: ins.getReferencesFrom()) if(r.getReferenceType().isCall()) callees.add(r.getToAddress());
            }
            pw.println("// calls: "+callees);
            DecompileResults dr=dec.decompileFunction(f,120,monitor);
            if(dr!=null&&dr.decompileCompleted()&&dr.getDecompiledFunction()!=null) pw.println(dr.getDecompiledFunction().getC());
            else pw.println("// (decompile failed)");
        }
        pw.close();
        println("DecompList done");
    }
    Iterable<Instruction> getInstructions(Function f){
        List<Instruction> r=new ArrayList<>();
        InstructionIterator it=currentProgram.getListing().getInstructions(f.getBody(),true);
        while(it.hasNext()) r.add(it.next());
        return r;
    }
}
