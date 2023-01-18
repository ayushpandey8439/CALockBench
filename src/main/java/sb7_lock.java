import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;

public class sb7_lock {

    public static void main(String[] args) throws InterruptedException {
        parameters params = new parameters();
        params.readParams(args);
        params.print();
        dataHolder dh = new dataHolder();
        dh.init();

        benchmark b = new benchmark();



    }
}
