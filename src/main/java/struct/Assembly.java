package struct;

public class Assembly extends designObject{
    ComplexAssembly m_superAssembly;
    public Assembly(long id, int buildDate, ComplexAssembly superAssembly) {
        super(id, buildDate);
        this.m_superAssembly = superAssembly;

    }
}
