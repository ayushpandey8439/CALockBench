import java.math.BigInteger;

public class id_Pool {
    static long id = 0;

    static long getNext(){
        return id++;
    }
}
