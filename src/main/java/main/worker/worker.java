package main.worker;

import main.dataHolder;
import main.operations.Operations;

import static main.sb7_lock.dh;

public class worker implements Runnable{
    Thread t;
    boolean exit = false;
    int id;
    workerData data;

    public worker(int Id){
        id=Id;
        data = new workerData();
        System.out.println(id);
    }
    public void exit(){
        exit = true;
    }

    @Override
    public void run() {
        while(!exit){
            int opind = data.getOperationRndInd();
            try{
                long start = System.currentTimeMillis();
                data.operations.ops.get(opind).run(id);
                long end = System.currentTimeMillis();

            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }
    }


}
