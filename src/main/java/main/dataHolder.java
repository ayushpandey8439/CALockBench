package main;


import main.struct.AtomicPart;
import main.struct.BaseAssembly;
import main.struct.ComplexAssembly;
import main.struct.CompositePart;
import main.struct.Module;
import java.util.*;

public class dataHolder {
    public Module module;
    ComplexAssembly designRoot;

    public Map<Long, AtomicPart> atomicPartIndex = new HashMap<>();
    public Map<Long, CompositePart> compositePartIndex= new HashMap<>();
    public Map<Long, BaseAssembly> baseAssemblyIndex= new HashMap<>();
    public Map<Long, ComplexAssembly> complexAssemblyIndex= new HashMap<>();

    public Map<Integer, Set<AtomicPart>> apartBuildDateIndex= new HashMap<>();



    public void init(){
        List<CompositePart> designLibrary= new ArrayList<>(parameters.initialTotalCompParts);
        for (int i = 0; i < parameters.initialTotalCompParts; i++) {
            designLibrary.add(createCompositePart());
        }
        module = createModule();
        designRoot = createAssemblies();
        connectAssembliesParts(designLibrary, parameters.initialTotalCompParts, parameters.numCompPerAssm);
    }


    public Module createModule(){
       long id =  id_Pool.getNext();
        int buildDate = createBuildDate(parameters.minModuleDate, parameters.maxModuleDate);
        Module m = new Module(id, buildDate);
        return m;
    }
    int createBuildDate(int min, int max){
        return NumberGenerator.r.nextInt(min, max+1);
    }
    ComplexAssembly createAssemblies(){
        return createComplexAssembly(null, parameters.numAssmPerAssm);
    }

    ComplexAssembly createComplexAssembly(ComplexAssembly parent, int childNum){
        long id = id_Pool.getNext();
        int buildDate = createBuildDate(parameters.minAssmDate, parameters.maxAssmDate);
        ComplexAssembly cassm = new ComplexAssembly(id,buildDate, parent, parameters.numAssmLevels);
        complexAssemblyIndex.put(id, cassm);
        if(parent!=null){
            parent.addSubAssembly(cassm);
        }
        boolean createBase = cassm.areChildrenBaseAssemblies();

        for (int i = 0; i < childNum; i++) {
            if(createBase){
                createBaseAssembly(cassm);
            } else {
                createComplexAssembly(cassm, childNum);
            }

        }
        return cassm;
    }

    void createBaseAssembly(ComplexAssembly parent){
        long id = id_Pool.getNext();
        int buildDate = createBuildDate(parameters.minAssmDate, parameters.maxAssmDate);
        BaseAssembly bassm = new BaseAssembly(id,buildDate, parent );
        baseAssemblyIndex.put(id, bassm);
        parent.addSubAssembly(bassm);
    }

    CompositePart createCompositePart(){
        long id = id_Pool.getNext();
        boolean young = NumberGenerator.r.nextInt(100)<parameters.youngCompFrac;
        int buildDate;
        if(young){
            buildDate = createBuildDate(parameters.minYoungCompDate, parameters.maxYoungCompDate);
        } else {
            buildDate = createBuildDate(parameters.minOldCompDate, parameters.maxOldCompDate);
        }

        CompositePart cpart = new main.struct.CompositePart(id, buildDate);

        ArrayList<AtomicPart> aparts = new ArrayList<>(parameters.numAtomicPerComp);
        for (int i = 0; i < parameters.numAtomicPerComp; i++) {
            AtomicPart a = createAtomicPart();
            cpart.addPart(a);
            aparts.add(a);
        }

        createConnections(aparts, parameters.numAtomicPerComp, parameters.numConnPerAtomic);

        compositePartIndex.put(id, cpart);
        return cpart;

    }

    AtomicPart createAtomicPart(){
        long id = id_Pool.getNext();
        int buildDate = createBuildDate(parameters.minAtomicDate, parameters.maxAtomicDate);
        int x = NumberGenerator.r.nextInt(parameters.xyRange);
        int y = NumberGenerator.r.nextInt(parameters.xyRange);

        AtomicPart a = new AtomicPart(id, buildDate, x, y);
        atomicPartIndex.put(id, a);
        apartBuildDateIndex.computeIfAbsent(buildDate, k -> new HashSet<AtomicPart>()).add(a);
        return a;
    }


    void createConnections(List<AtomicPart> aparts, int size, int outConn){

        // this piece of code connects the Atomic parts in a ring. which might be detremental to a proper test of labelling performance.
//        for (int i = 0; i < size - 1; i++) {
//            aparts.get(i).connectTo(aparts.get(i+1));
//        }
//        aparts.get(size-1).connectTo(aparts.get(0));

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < outConn; j++) {
                int connectToInd = NumberGenerator.r.nextInt(size);
                aparts.get(i).connectTo(aparts.get(connectToInd));
            }
        }
    }

    void connectAssembliesParts(List<CompositePart> designLibrary, int partNum, int connNum){
        for(BaseAssembly b: baseAssemblyIndex.values()){
            for (int i = 0; i < connNum; i++) {
                int partInd = NumberGenerator.r.nextInt(partNum);
                b.addComponent(designLibrary.get(partInd));
            }
        }
        System.out.println("Finished creating composite parts");

    }
}
