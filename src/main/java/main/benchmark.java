package main;

import main.worker.worker;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static main.sb7_lock.dh;

public class benchmark {
    int threadNum = parameters.threadNum;
    ExecutorService TPool;
    Map<Integer, worker> Threads = new HashMap<>();

    public benchmark() throws InterruptedException {
        TPool = Executors.newFixedThreadPool(threadNum);
        for (int i = 0; i < threadNum; i++) {
            worker w = new worker(i);
            this.Threads.put(i, w);
        }
    }

    public void run() throws InterruptedException {

        for (worker w: Threads.values()){
            TPool.submit(w);
        }

        Thread.sleep(parameters.experimentLengthMs);
        for (worker w: Threads.values()){
            w.exit();
        }

        TPool.shutdown();
    }
}
