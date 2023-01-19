package main;

public class sb7_lock {
    public static dataHolder dh = new dataHolder();
    public static void main(String[] args) throws InterruptedException {
        parameters params = new parameters();
        params.readParams(args);
        params.print();
        dh.init();
        benchmark b = new benchmark();
        b.run();
    }
}
