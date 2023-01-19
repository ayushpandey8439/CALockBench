package main.struct;

import main.struct.assembly_type;

import java.util.HashSet;
import java.util.Set;

public class BaseAssembly extends Assembly {
    public String type = "ba";
    Set<CompositePart> compositePartSet = new HashSet<>();

    public BaseAssembly(long id, int buildDate, ComplexAssembly superAssembly) {
        super(id, buildDate, superAssembly);
    }


    public assembly_type getType(){
        return assembly_type.assembly_type_base;
    }

    public Set<CompositePart> getCompositeParts(){
        return compositePartSet;
    }

    public boolean addComponent(CompositePart c ){
        return compositePartSet.add(c);
    }

    public boolean removeComponent(CompositePart c){
        return compositePartSet.remove(c);
    }
}
