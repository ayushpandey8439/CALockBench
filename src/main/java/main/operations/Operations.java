package main.operations;

import main.dataHolder;
import main.lockingType;
import main.operations.coarse.read;
import main.operations.coarse.write;
import main.parameters;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import static main.operations.optype.*;
import static main.sb7_lock.dh;

public class Operations {
    public Map<optype, OperationType> optypes = new HashMap<>();
    public ArrayList<Operation> ops = new ArrayList<>();
    public ArrayList<Double> cdf = new ArrayList<>();

    public Operations(){
        initOperationTypes();
        initOperations();
        generateCdf();
    }

    public void initOperationTypes() {
        optypes.put(OPERATION,new OperationType(OPERATION, "OPERATION"));
        optypes.put(OPERATION_RO, new OperationType(OPERATION_RO, "OPERATION_RO"));
        optypes.put(STRUCTURAL_MODIFICATION, new OperationType(STRUCTURAL_MODIFICATION,"STRUCTURAL_MODIFICATION"));
    }

    public void initOperations(){
        if(parameters.lockType == lockingType.lock_coarse){
             initOperationsLockCoarse();
        } else if(parameters.lockType == lockingType.lock_medium){
//            initOperationsLockMedium();
        }else if(parameters.lockType == lockingType.lock_ca){
//            initOperationsLockCA();
        }else if(parameters.lockType == lockingType.lock_dom){
//            initOperationsLockDom();
        }
    }

    void initOperationsLockCoarse(){
        ops.add(new read.Query1(dh));
        ops.add(new read.Query2(dh));
        ops.add(new write.operation1(dh));
        ops.add(new write.operation2(dh));
    }

    public void generateCdf(){
        for(int i=0; i<ops.size();i++){
            Operation o = ops.get(i);
            optypes.get(o.type).count++;
        }

        double operationsRatio = parameters.operationsRatio / 100.0;
        double structuralModificationsRatio =
                parameters.structuralModificationsRatio / 100.0;

        double readOnlyOperationsRatio =
                parameters.readOnlyOperationsRatio / 100.0;
        double updateOperationsRatio = 1.0 - readOnlyOperationsRatio;

        double sumRatios = operationsRatio +
                          structuralModificationsRatio * updateOperationsRatio;

        operationsRatio /= sumRatios;
        structuralModificationsRatio /= sumRatios;

        optypes.get(OPERATION).probability = operationsRatio * updateOperationsRatio / optypes.get(OPERATION).count;
        optypes.get(OPERATION_RO).probability =operationsRatio * readOnlyOperationsRatio / optypes.get(OPERATION_RO).count;
        optypes.get(STRUCTURAL_MODIFICATION).probability =structuralModificationsRatio * updateOperationsRatio / optypes.get(STRUCTURAL_MODIFICATION).count;

        ops.removeIf(operation -> {return optypes.get(operation.type).probability==0; });
        double currCdf = 0;
        for(Operation op: ops){
            currCdf+= optypes.get(op.type).probability;
            cdf.add(currCdf);
        }

    }


}
