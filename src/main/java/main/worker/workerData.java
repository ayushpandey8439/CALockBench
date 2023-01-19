package main.worker;

import main.NumberGenerator;
import main.dataHolder;
import main.operations.Operations;

import java.util.ArrayList;

public class workerData {
    Operations operations;
    int opnum;
    public ArrayList<Integer> successfulOps = new ArrayList<>();
    public ArrayList<Integer> failedOps = new ArrayList<>();

    public workerData(){
        operations = new Operations();
        for (int i = 0; i < operations.ops.size(); i++) {
            successfulOps.add(0);
            failedOps.add(0);
        }
    }

    public int getOperationRndInd() {
        double oprnd = NumberGenerator.r.nextDouble();
        ArrayList<Double> opRat = operations.cdf;
        int opind = 0;
        double maxPossible = opRat.get(opRat.size()-1);
        oprnd = 1-oprnd;
        oprnd *= maxPossible;
        while (opRat.get(opind) < oprnd && opind < opRat.size()-1) {
            opind++;
        }
        return opind;
    }
}
