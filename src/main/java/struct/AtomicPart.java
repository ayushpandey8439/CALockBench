package struct;

import java.util.HashSet;
import java.util.Set;

public class AtomicPart extends designObject{
    Set<Connection> connectionsFrom = new HashSet<>();
    Set<Connection> connectionsTo = new HashSet<>();
    int m_x;
    int m_y;
    CompositePart partOf;

    public AtomicPart(long id, int buildDate, int x, int y) {
        super(id, buildDate);
        m_x = x;
        m_y = y;
    }

    CompositePart getPartOf(){
        return partOf;
    }

    public Set<Connection> getFromConnections() {
        return connectionsFrom;
    }
    public Set<Connection> getToConnections() {
        return connectionsTo;
    }

    public void connectTo(AtomicPart dest){
        Connection c = new Connection(this, dest);
        connectionsTo.add(c);
        dest.addConnectionFromOtherPart(c);
    }

    void addConnectionFromOtherPart(Connection c) {
        connectionsFrom.add(c);
    }
    void removeConnectionFromOtherPart(Connection c) {
        connectionsFrom.remove(c);
    }

    void removeConnectionToOtherPart(Connection c) {
       connectionsTo.remove(c);
    }

    void setCompositePart(CompositePart c){
        partOf = c;
    }

    public int getX() {
        return m_x;
    }

    public int getY() {
        return m_y;
    }

    public void swapXY() {
        int tmp = m_y;
        m_y = m_x;
        m_x = tmp;
    }
}
