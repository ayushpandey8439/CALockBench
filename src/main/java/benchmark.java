import worker.worker;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class benchmark {
    int threadNum = parameters.threadNum;
    Map<Integer, worker> Threads = new HashMap<>();
    public benchmark() throws InterruptedException {
        ExecutorService TPool = Executors.newFixedThreadPool(threadNum);
        for (int i = 0; i < threadNum; i++) {
            worker w = new worker(i);
            this.Threads.put(i, w);
        }

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
