package main.struct;

public class Connection {
    AtomicPart from;
    AtomicPart to;

    public Connection(AtomicPart f, AtomicPart t) {
        from = f;
        to = t;
    }

    public Connection getReversed() {
        return new Connection(to, from);
    }

    public AtomicPart getDestination() {
        return to;
    }

    public AtomicPart getSource() {
        return from;
    }
}
