#include "structural_modification_ops.h"

#include "../../parameters.h"
#include "../../sb7_exception.h"

/////////////////////////////
// StructuralModification1 //
/////////////////////////////

int sb7::StructuralModification1::run() const {
    dataHolder->createCompositePart();
    return 0;
}

/////////////////////////////
// StructuralModification2 //
/////////////////////////////

int sb7::StructuralModification2::run() const {
    // generate random composite part id and try to look it up
    int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
    CompositePart *cpart = dataHolder->getCompositePart(cpartId);

    if (cpart == NULL) {
        throw Sb7Exception();
    }

    dataHolder->deleteCompositePart(cpart);

    return 0;
}

/////////////////////////////
// StructuralModification3 //
/////////////////////////////

int sb7::StructuralModification3::run() const {
    // generate random composite part id
    int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
    CompositePart *cpart = dataHolder->getCompositePart(cpartId);

    if (cpart == NULL) {
        throw Sb7Exception();
    }

    // generate random base assembly id
    int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

    if (bassm == NULL) {
        throw Sb7Exception();
    }

    bassm->addComponent(cpart);

    return 0;
}

/////////////////////////////
// StructuralModification4 //
/////////////////////////////

int sb7::StructuralModification4::run() const {
    // generate random base assembly id
    int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

    if (bassm == NULL) {
        throw Sb7Exception();
    }

    // select one of composite parts used in the base assembly
    Bag<CompositePart *> *cpartBag = bassm->getComponents();
    int compNum = cpartBag->size();

    if (compNum == 0) {
        throw Sb7Exception();
    }

    int nextId = get_random()->nextInt(compNum);

    // find component with that ordinal number
    BagIterator<CompositePart *> iter = cpartBag->getIter();
    int i = 0;

    while (iter.has_next()) {
        CompositePart *cpart = iter.next();

        if (nextId == i) {
            bassm->removeComponent(cpart);
            return 0;
        }

        i++;
    }

    throw Sb7Exception(
            "SM4: concurrent modification of BaseAssembly.components!");
}

/////////////////////////////
// StructuralModification5 //
/////////////////////////////

int sb7::StructuralModification5::run() const {
    // generate random base assembly id
    int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

    if (bassm == NULL) {
        throw Sb7Exception();
    }

    // create sibling base assembly
    dataHolder->createBaseAssembly(bassm->getSuperAssembly());

    return 0;
}

/////////////////////////////
// StructuralModification6 //
/////////////////////////////

int sb7::StructuralModification6::run() const {
    // generate random base assembly id
    int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
    BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

    if (bassm == NULL) {
        throw Sb7Exception();
    }

    // get parent and check that it has at least one more child
    ComplexAssembly *cassm = bassm->getSuperAssembly();
    Set<Assembly *> *subAssmSet = cassm->getSubAssemblies();

    // don't let the tree break
    if (subAssmSet->size() == 1) {
        throw Sb7Exception();
    }

    dataHolder->deleteBaseAssembly(bassm);

    return 0;
}

/////////////////////////////
// StructuralModification7 //
/////////////////////////////

int sb7::StructuralModification7::run() const {
    // generate random complex assembly id
    int cassmId = get_random()->nextInt(
            parameters.getMaxComplexAssemblies()) + 1;
    ComplexAssembly *cassm = dataHolder->getComplexAssembly(cassmId);

    if (cassm == NULL) {
        throw Sb7Exception();
    }

    // create sub assembly
    dataHolder->createSubAssembly(cassm, parameters.getNumAssmPerAssm());

    return 1;
}

/////////////////////////////
// StructuralModification8 //
/////////////////////////////

int sb7::StructuralModification8::run() const {
    // generate random complex assembly id
    int cassmId = get_random()->nextInt(
            parameters.getMaxComplexAssemblies()) + 1;
    ComplexAssembly *cassm = dataHolder->getComplexAssembly(cassmId);

    if (cassm == NULL) {
        throw Sb7Exception();
    }

    // get super assembly
    ComplexAssembly *superAssm = cassm->getSuperAssembly();

    // don't continue if we got root complex assembly
    if (superAssm == NULL) {
        throw Sb7Exception();
    }

    // check if this would break the tree structure
    Set<Assembly *> *assmSet = superAssm->getSubAssemblies();

    if (assmSet->size() == 1) {
        throw Sb7Exception();
    }

    // delete selected complex assembly
    dataHolder->deleteComplexAssembly(cassm);

    return 1;
}
