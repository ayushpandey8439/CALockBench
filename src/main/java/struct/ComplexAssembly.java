package struct;

import java.util.HashSet;
import java.util.Set;

public class ComplexAssembly extends Assembly{
    Set<Assembly> m_subAssemblies = new HashSet<>();
    int m_level;
    public ComplexAssembly(long id, int buildDate, ComplexAssembly superAssembly, int maxChildren) {
        super(id, buildDate, superAssembly);
        this.setlevel(maxChildren);
    }

    public assembly_type getType(){
        return assembly_type.assembly_type_complex;
    }

    public Set<Assembly> getSubAssemblies(){
        return m_subAssemblies;
    }

    public boolean addSubAssembly(Assembly a){
        return m_subAssemblies.add(a);
    }

    public int getlevel() {
        return m_level;
    }

    private void setlevel(int maxlevels) {
        if(super.m_superAssembly!=null){
            m_level = super.m_superAssembly.m_level-1;
        } else {
            m_level = maxlevels;
        }
    }

    public boolean areChildrenBaseAssemblies(){
        return m_level==2;
    }
}
