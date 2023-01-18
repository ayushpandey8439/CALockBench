package struct;

public class Module extends designObject{
    ComplexAssembly designRoot;
    public Module(long id, int buildDate) {
        super(id, buildDate);
    }

    void setDesignRoot(ComplexAssembly d) {
        designRoot = d;
    }

    ComplexAssembly getDesignRoot(){
        return designRoot;
    }

}
