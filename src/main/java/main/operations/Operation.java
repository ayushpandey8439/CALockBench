package main.operations;

import main.dataHolder;

public abstract class Operation {
    String name;
    optype type;
    main.dataHolder dataHolder;

    public Operation(optype t, String n, dataHolder dh){
        name = n;
        type=t;
        dataHolder = dh;
    }

    public abstract void run(int tid);
}
