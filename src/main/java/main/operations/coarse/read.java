package main.operations.coarse;

import main.NumberGenerator;
import main.dataHolder;
import main.operations.Operation;
import main.operations.optype;
import main.parameters;
import main.struct.AtomicPart;

import java.util.*;

import static main.sb7_lock.dh;

public class read {
    public static class Query1 extends Operation {
        public Query1(dataHolder d) {
            super(optype.OPERATION_RO, "Q1", d);
        }

        @Override
        public void run(int tid) {
            lockserver.readLock();
            innerRun(tid);
            lockserver.readUnlock();
        }

       public static void innerRun(int tid){
            List<AtomicPart> vals = dh.atomicPartIndex.values().stream().toList();
            int index = NumberGenerator.r.nextInt(vals.size());
            AtomicPart a = (vals.get(index));
            performOperationOnAtomicPart(a);
        }

        static void performOperationOnAtomicPart(AtomicPart apart) {
                return;
        }
    }
    public static class Query2 extends Operation {
        int percent = 1;
        public Query2(dataHolder d) {
            super(optype.OPERATION_RO, "Q2", d);
        }

        @Override
        public void run(int tid) {
            lockserver.readLock();
            innerRun(tid);
            lockserver.readUnlock();
        }

        public static void innerRun(int tid){
            List<Long> keys = dh.atomicPartIndex.keySet().stream().toList();
            int index = NumberGenerator.r.nextInt(0, keys.size()-100);
            Set<AtomicPart> aparts = new HashSet<>();
            for(int i=index; i<index+100;i++){
                aparts.add(dh.atomicPartIndex.get(keys.get(i)));
            }
            aparts.stream().map(atomicPart -> {
                performOperationOnAtomicPart(atomicPart);
                return null;
            });
        }

        static void performOperationOnAtomicPart(AtomicPart apart) {
            return;
        }
    }
}
