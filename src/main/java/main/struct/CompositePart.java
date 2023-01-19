package main.struct;


import java.util.HashSet;
import java.util.Set;

public class CompositePart extends designObject {
    public String type = "cp";

    Set<BaseAssembly> usedIn = new HashSet<>();
    Set<AtomicPart> atomicParts = new HashSet<>();
    AtomicPart rootPart;

    public CompositePart(long id, int buildDate) {
        super(id, buildDate);
    }

    public boolean addAssembly(BaseAssembly b){
        return usedIn.add(b);
    }

    public boolean removeAssembly(BaseAssembly b){
        return usedIn.remove(b);
    }

    public boolean addPart(AtomicPart a){
        return atomicParts.add(a);
    }

    public boolean removePart(AtomicPart a){
        return atomicParts.remove(a);
    }

    public Set<AtomicPart> getAtomicParts() {
        return atomicParts;
    }

    public Set<BaseAssembly> getUsedIn() {
        return usedIn;
    }
}
