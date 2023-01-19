package main.operations.coarse;

import main.dataHolder;
import main.operations.Operation;
import main.operations.optype;

public class write {
    public static class operation1 extends Operation {
        int percent = 1;
        public operation1(dataHolder d) {
            super(optype.OPERATION, "OP1", d);
        }
        @Override
        public void run(int tid) {
            lockserver.writeLock();
            read.Query1.innerRun(tid);
            lockserver.writeUnlock();
        }
    }
    public static class operation2 extends Operation { int percent = 1;
        public operation2(dataHolder d) {
            super(optype.OPERATION, "OP2", d);
        }
        @Override
        public void run(int tid) {
            lockserver.writeLock();
            read.Query2.innerRun(tid);
            lockserver.writeUnlock();
        }
    }
}
