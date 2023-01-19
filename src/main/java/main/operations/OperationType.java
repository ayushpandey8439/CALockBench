package main.operations;

class OperationType {
    optype type;
    int count;
    double probability;
    int success;
    int aborted;
    int failure;
    int maxttc;
    final String name;

    OperationType(optype ty, String n){
        type = ty;
        count=0;
        probability = 0;
        success=0;
        aborted=0;
        failure = 0;
        maxttc=0;
        name = n;

    }

}
