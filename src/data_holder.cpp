#include <cstdio>
#include <iostream>

#include "data_holder.h"
#include "parameters.h"
#include "sb7_exception.h"
#include "helpers.h"
#include "thread/thread.h"

#include "struct/connection.h"

using namespace sb7;
using namespace std;

sb7::DataHolder::~DataHolder() {
    // destroy indexes
    /*delete atomicPartIdIndex;
    delete atomicPartBuildDateIndex;
    delete documentTitleIndex;
    delete compositePartIdIndex;
    delete baseAssemblyIdIndex;
    delete complexAssemblyIdIndex;

    // destroy id pools
    delete compositePartIdPool;
    delete atomicPartIdPool;
    delete moduleIdPool;
    delete documentIdPool;
    delete manualIdPool;
    delete baseAssemblyIdPool;
    delete complexAssemblyIdPool;*/
}

void sb7::DataHolder::allocateData() {
    // initialize indexes
    m_atomicPartIdIndex = new atomic_part_int_index();
    m_atomicPartBuildDateIndex = new atomic_part_set_int_index();
    m_documentTitleIndex = new document_string_index();
    m_compositePartIdIndex = new composite_part_int_index();
    m_baseAssemblyIdIndex = new base_assembly_int_index();
    m_complexAssemblyIdIndex = new complex_assembly_int_index();

    // initialize id pools
    m_compositePartIdPool = new IdPool(parameters.getMaxCompParts());
    m_atomicPartIdPool = new IdPool(parameters.getMaxAtomicParts());
    m_moduleIdPool = new IdPool(parameters.getNumModules());
    m_documentIdPool = new IdPool(parameters.getMaxCompParts());
    m_manualIdPool = new IdPool(parameters.getNumModules());
    m_baseAssemblyIdPool = new IdPool(parameters.getMaxBaseAssemblies());
    m_complexAssemblyIdPool = new IdPool(parameters.getMaxComplexAssemblies());
}

void sb7::DataHolder::init() {
    allocateData();

    // first create composite parts and everything below them
    int initialTotalCompParts = parameters.getInitialTotalCompParts();
    auto **designLibrary = new CompositePart *[initialTotalCompParts];
    createCompositeParts(designLibrary, initialTotalCompParts);

    // create module
    m_module = createModule();

    // create assemblies
    ComplexAssembly *designRoot = createAssemblies();

    // connect module and design root
    m_module->setDesignRoot(designRoot);

    // connect assemblies and composite parts
    connectAssembliesParts(designLibrary,
                           initialTotalCompParts,
                           parameters.getNumCompPerAssm());

    // delete design library
    delete[] designLibrary;
}

Document *sb7::DataHolder::createDocument(int cpartId) {
    int docId = m_documentIdPool->getId();

    ITOA(cpartIdStr, cpartId)
    string docTitle = "Composite Part #" + (string) cpartIdStr;
    string txt = "I am the documentation for composite part #";
    txt += cpartIdStr;
    txt += '\n';
    string docText = createText(parameters.getDocumentSize(), txt);

    auto *doc = new Document(docId, docTitle, docText);

    m_documentTitleIndex->put(docTitle, doc);

    return doc;
}

Manual *sb7::DataHolder::createManual(int moduleId) {
    int manualId = m_manualIdPool->getId();

    ITOA(moduleIdStr, moduleId);
    string manTitle = "Manual for module #" + (string) moduleIdStr;
    string txt = "I am the manual for module #";
    txt += moduleIdStr;
    txt += '\n';
    string manText = createText(parameters.getManualSize(), txt);

    auto *man = new Manual(manualId, manTitle, manText);

    return man;
}

string sb7::DataHolder::createText(unsigned size, const string &txt) {
    string ret;

    while (ret.size() < size) {
        ret.append(txt);
    }

    return ret;
}

string sb7::DataHolder::createType() {
    int typeNum = get_random()->nextInt(parameters.getNumTypes());
    ITOA(itoa_buf, typeNum);
    string txt = "type #" + (string) itoa_buf;
    return txt;
}

int sb7::DataHolder::createBuildDate(int min, int max) {
    return min + get_random()->nextInt(max - min + 1);
}

void sb7::DataHolder::createCompositeParts(CompositePart *designLibrary[],
                                           int dlSize) {

    //std::cout << "Creating composite parts:" << std::endl;

    for (int i = 0; i < dlSize; i++) {
        //std::cout << "\r";
        designLibrary[i] = createCompositePart();
        //std::cout << "Composite part " << i + 1 << " of " << dlSize << std::flush;
    }

    std::cout << std::endl << "Finished creating composite parts" << std::endl;
}

CompositePart *sb7::DataHolder::createCompositePart() {
    int id = m_compositePartIdPool->getId();
    string type = createType();

    // generate build date
    bool youngCPart = get_random()->nextInt(HUNDRED_PERCENT) <
                      parameters.getYoungCompFrac();
    int min, max;

    if (youngCPart) {
        min = parameters.getMinYoungCompDate();
        max = parameters.getMaxYoungCompDate();
    } else {
        min = parameters.getMinOldCompDate();
        max = parameters.getMaxOldCompDate();
    }

    int buildDate = createBuildDate(min, max);

    // make document connected to this composite part
    Document *doc = createDocument(id);

    // make composite part using all data previously created
    auto *cpart = new CompositePart(id, type, buildDate, doc);

    // create atomic parts
    auto **parts =
            new AtomicPart *[parameters.getNumAtomicPerComp()];
    createAtomicParts(parts, parameters.getNumAtomicPerComp(), cpart);

    // create connections among atomic parts
    createConnections(parts, parameters.getNumAtomicPerComp(),
                      parameters.getNumConnPerAtomic());

    // put composite part into index
    m_compositePartIdIndex->put(id, cpart);

    // delete parts
    delete[] parts;

    // finally return created composite part
    return cpart;
}

void sb7::DataHolder::createAtomicParts(AtomicPart *parts[],
                                        int psize, CompositePart *cpart) {
    for (int i = 0; i < psize; i++) {
        AtomicPart *apart = createAtomicPart();
        cpart->addPart(apart);
        parts[i] = apart;
    }
}

AtomicPart *sb7::DataHolder::createAtomicPart() {
    int id = m_atomicPartIdPool->getId();
    string type = createType();
    int buildDate = createBuildDate(
            parameters.getMinAtomicDate(),
            parameters.getMaxAtomicDate());
    int x = get_random()->nextInt(parameters.getXYRange());
    int y = get_random()->nextInt(parameters.getXYRange());

    auto *apart = new AtomicPart(id, type, buildDate, x, y);

    m_atomicPartIdIndex->put(id, apart);
    addAtomicPartToBuildDateIndex(apart);

    return apart;
}

void sb7::DataHolder::createConnections(AtomicPart *parts[],
                                        int size, int outConn) {
    // connect all atomic parts in a ring in order to get fully
    // connected graph
    for (int i = 0; i < size - 1; i++) {
        connectAtomicParts(parts[i], parts[i + 1]);
    }

    connectAtomicParts(parts[size - 1], parts[0]);

    // add random connections
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < outConn; j++) {
            int connectToInd = get_random()->nextInt(size);
            connectAtomicParts(parts[i], parts[connectToInd]);
        }
    }
}

void sb7::DataHolder::connectAtomicParts(AtomicPart *start, AtomicPart *end) {
    string type = createType();
    int len = generateConnectionLength();
    start->connectTo(end, type, len);
}

int sb7::DataHolder::generateConnectionLength() {
    return get_random()->nextInt(parameters.getXYRange()) + 1;
}

Module *sb7::DataHolder::createModule() {
    // generate all required data elements
    int id = m_moduleIdPool->getId();
    string type = createType();
    int buildDate = createBuildDate(
            parameters.getMinModuleDate(),
            parameters.getMaxModuleDate());

    // create manual
    Manual *man = createManual(id);

    // create return value
    auto *mod = new Module(id, type, buildDate, man);

    // connect manual -> module
    //mod->connectManual();

    return mod;
}

ComplexAssembly *sb7::DataHolder::createAssemblies() {
    ComplexAssembly *designRoot = createComplexAssembly(
            nullptr, parameters.getNumAssmPerAssm());
    return designRoot;
}

void sb7::DataHolder::connectAssembliesParts(
        CompositePart *designLibrary[], int partNum, int connNum) {
    MapIterator<int, BaseAssembly *> iter = m_baseAssemblyIdIndex->getAll();

    while (iter.has_next()) {
        BaseAssembly *ba = iter.next();

        for (int i = 0; i < connNum; i++) {
            int partInd = get_random()->nextInt(partNum);
            ba->addComponent(designLibrary[partInd]);
        }
    }
}

ComplexAssembly *sb7::DataHolder::createComplexAssembly(
        ComplexAssembly *parent, int childNum) {
    // create required data
    int id = m_complexAssemblyIdPool->getId();
    string type = createType();
    int buildDate = createBuildDate(
            parameters.getMinAssmDate(),
            parameters.getMaxAssmDate());

    // construct complex assembly
    auto *cassm = new ComplexAssembly(id, type, buildDate,
                                                 m_module, parent);

    // add complex assembly to the index
    m_complexAssemblyIdIndex->put(id, cassm);

    // add complex assembly to parent
    if (parent != nullptr) {
        parent->addSubAssembly(cassm);
    }

    // create children
    bool createBase = cassm->areChildrenBaseAssemblies();

    for (int i = 0; i < childNum; i++) {
        if (createBase) {
            createBaseAssembly(cassm);
        } else {
            createComplexAssembly(cassm, childNum);
        }
    }

    return cassm;
}

void sb7::DataHolder::createSubAssembly(ComplexAssembly *parent,
                                        int childNum) {
    if (parent->areChildrenBaseAssemblies()) {
        createBaseAssembly(parent);
    } else {
        createComplexAssembly(parent, childNum);
    }
}

void sb7::DataHolder::createBaseAssembly(ComplexAssembly *parent) {
    // create required data
    int id = m_baseAssemblyIdPool->getId();
    string type = createType();
    int buildDate = createBuildDate(
            parameters.getMinAssmDate(),
            parameters.getMaxAssmDate());

    // construct object
    auto *bassm = new BaseAssembly(id, type, buildDate,
                                           m_module, parent);

    // put into index
    m_baseAssemblyIdIndex->put(id, bassm);

    // add to parent
    parent->addSubAssembly(bassm);
}

void sb7::DataHolder::addAtomicPartToBuildDateIndex(AtomicPart *apart) {
    // search for set containing aparts with corresponding build date
    int buildDate = apart->getBuildDate();
    atomic_part_set_int_index::Query query;
    query.key = buildDate;
    m_atomicPartBuildDateIndex->get(query);
    atomic_part_set *apart_set;

    if (query.found) {
        apart_set = query.val;
    } else {
        apart_set = new atomic_part_set();
        m_atomicPartBuildDateIndex->put(buildDate, apart_set);
    }

    apart_set->add(apart);
}

void sb7::DataHolder::removeAtomicPartFromBuildDateIndex(AtomicPart *apart) {
    // get set of atomic parts with the same build date
    atomic_part_set_int_index::Query query;
    query.key = apart->getBuildDate();
    m_atomicPartBuildDateIndex->get(query);

    if (query.found) {
        query.val->remove(apart);
    }
}


//////////////////////////////////////
// search for objects using indexes //
//////////////////////////////////////

CompositePart *sb7::DataHolder::getCompositePart(int id) const {
    // make a search through an index
    composite_part_int_index::Query query;
    query.key = id;
    m_compositePartIdIndex->get(query);

    // if object was found, return it
    if (query.found) {
        return query.val;
    }

    // otherwise reutrn NULL
    return nullptr;
}

BaseAssembly *sb7::DataHolder::getBaseAssembly(int id) const {
    base_assembly_int_index::Query query;
    query.key = id;
    m_baseAssemblyIdIndex->get(query);

    if (query.found) {
        return query.val;
    }

    return nullptr;
}

ComplexAssembly *sb7::DataHolder::getComplexAssembly(int id) const {
    complex_assembly_int_index::Query query;
    query.key = id;
    m_complexAssemblyIdIndex->get(query);

    if (query.found) {
        return query.val;
    }

    return nullptr;
}

///////////////////////////////////////////
// Delete elements of the data structure //
///////////////////////////////////////////

void sb7::DataHolder::deleteDocument(Document *doc) {
    int id = doc->getDocumentId();

    // remove from document index
    m_documentTitleIndex->remove(doc->getTitle());

    // delete document object
    delete doc;

    // return id to pool
    m_documentIdPool->putId(id);
}

void sb7::DataHolder::deleteAtomicPart(AtomicPart *apart) {
    int id = apart->getId();
    if(apart->isDeleted){
        return;
    }

    // remove part from build date index
    //removeAtomicPartFromBuildDateIndex(apart);

    // remove atomic part from id index
    //m_atomicPartIdIndex->remove(id);

    // remove connections to other parts and delete them
    Set<Connection *> *connToSet = apart->getToConnections();
    SetIterator<Connection *> iterTo = connToSet->getIter();

    while (iterTo.has_next()) {
        Connection *conn = iterTo.next();

        // remove connection from destination part
        AtomicPart *apart = conn->getDestination();
        apart->removeConnectionFromOtherPart(conn);

        // delete connection
        delete conn;
    }

    // remove connections from other parts and delete them
    Set<Connection *> *connFromSet = apart->getFromConnections();
    SetIterator<Connection *> iterFrom = connFromSet->getIter();

    while (iterFrom.has_next()) {
        Connection *conn = iterFrom.next();

        // remove connection from destination part
        AtomicPart *apart = conn->getSource();
        apart->removeConnectionToOtherPart(conn);

        // delete connection
        delete (conn);
    }

    ///Objects relevant to the existance of
    /// the hierarchy have been marked deleted instead of being actually deleted
    // delete atomic part
    //delete apart;
    apart->Delete();
    // return id to the pool
    m_atomicPartIdPool->putId(id);
}

void sb7::DataHolder::deleteCompositePart(CompositePart *cpart) {
    int cpartId = cpart->getId();

    // remove composite part from composite part index
    //m_compositePartIdIndex->remove(cpartId);

    // delete document
    deleteDocument(cpart->getDocumentation());

    // delete atomic parts
    Set<AtomicPart *> *apartSet = cpart->getParts();
    SetIterator<AtomicPart *> iterApart = apartSet->getIter();

    while (iterApart.has_next()) {
        deleteAtomicPart(iterApart.next());
    }

    // break connection with all base assemblies
    Bag<BaseAssembly *> *bassmBag = cpart->getUsedIn();
    BagIterator<BaseAssembly *> iterBag = bassmBag->getIter();
    Set<BaseAssembly *> bassmSet;

    // first copy all base assemblies to separate set as bag will change
    // while breaking connection
    while (iterBag.has_next()) {
        bassmSet.add(iterBag.next());
    }

    // now use this set and break connections
    SetIterator<BaseAssembly *> iterSet = bassmSet.getIter();

    while (iterSet.has_next()) {
        BaseAssembly *bassm = iterSet.next();

        while (bassm->removeComponent(cpart)) {
            // do nothing in the body
        }
    }

    // mark composite part for deletion
    //delete cpart;
    cpart->Delete();
    // return id to the pool
    m_compositePartIdPool->putId(cpartId);
}

void sb7::DataHolder::deleteBaseAssembly(BaseAssembly *bassm) {

    // remove from base assembly index
    int bassmId = bassm->getId();
    m_baseAssemblyIdIndex->remove(bassmId);

    // remove from parent complex assembly
    ComplexAssembly *parent = bassm->getSuperAssembly();
    parent->removeSubAssembly(bassm);

    // remove links to all used components
    Bag<CompositePart *> *cpartBag = bassm->getComponents();
    Set<CompositePart *> cpartSet;

    // copy component bag to a local one, to avoid changes to set we are
    // iteration through
    BagIterator<CompositePart *> iterSh = cpartBag->getIter();

    while (iterSh.has_next()) {
        cpartSet.add(iterSh.next());
    }

    // now go through local bag and remove all components in there
    SetIterator<CompositePart *> iter = cpartSet.getIter();

    while (iter.has_next()) {
        CompositePart *cpart = iter.next();

        while (bassm->removeComponent(cpart)) {
            // do nothing
        }
    }

    // delete base assembly
    //delete bassm;
    bassm->Delete();
    // return id to pool
    m_baseAssemblyIdPool->putId(bassmId);
}

void sb7::DataHolder::deleteComplexAssembly(ComplexAssembly *cassm) {
    // remove assembly from assembly index
    int cassmId = cassm->getId();
    m_complexAssemblyIdIndex->remove(cassmId);

    // check if this is the root assembly
    ComplexAssembly *superAssm = cassm->getSuperAssembly();

    if (superAssm == nullptr) {
        throw Sb7Exception(
                "DeleteComplexAssembly: root Complex Assembly cannot be removed!");
    }

    // remove link from parent to this complex assembly
    superAssm->removeSubAssembly(cassm);

    // delete subtree under this assembly
    Set<Assembly *> *subAssmSet = cassm->getSubAssemblies();
    Set<Assembly *> tmpSubAssmSet;

    // copy set to a local one as it will be changing while removing
    // sub assemblies
    SetIterator<Assembly *> iterSubAssmSet = subAssmSet->getIter();

    while (iterSubAssmSet.has_next()) {
        tmpSubAssmSet.add(iterSubAssmSet.next());
    }

    // now delete all sub assemblies
    SetIterator<Assembly *> iter = tmpSubAssmSet.getIter();
    bool childrenAreBase = cassm->areChildrenBaseAssemblies();

    while (iter.has_next()) {
        if (childrenAreBase) {
            deleteBaseAssembly((BaseAssembly *) iter.next());
        } else {
            deleteComplexAssembly((ComplexAssembly *) iter.next());
        }
    }

    // delete asembly
    delete cassm;

    // return id to the id pool
    m_complexAssemblyIdPool->putId(cassmId);
}
