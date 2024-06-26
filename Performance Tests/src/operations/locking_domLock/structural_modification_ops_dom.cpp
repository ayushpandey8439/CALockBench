#include "structural_modification_ops_dom.h"

#include "../../parameters.h"
#include "../../sb7_exception.h"
#include "../../thread/thread.h"
#include "../../interval.h"
#include "../../DomRelabelling.h"
#include "../../dominatorHelper.h"
extern IntervalCheck ICheck;

/////////////////////////////
// StructuralModification1 //
/////////////////////////////

int sb7::DomStructuralModification1::run(int tid) const {
	//WriteLockHandle writeLockHandle(dom_lock_srv.getLock());
	dataHolder->createCompositePart();
	return 0;
}

/////////////////////////////
// StructuralModification2 //
/////////////////////////////

int sb7::DomStructuralModification2::run(int tid) const {
	//WriteLockHandle writeLockHandle(dom_lock_srv.getLock());

	// generate random composite part id and try to look it up
	int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
	CompositePart *cpart = dataHolder->getCompositePart(cpartId);

	if(cpart == NULL|| cpart->m_post_number==0 || cpart->m_pre_number==0) {
		throw Sb7Exception();
	}
<<<<<<< HEAD
    long int min=5000000, max=0;
    min = cpart->m_pre_number;
    max = cpart->m_post_number;
=======
    long min=INFINITY, max=0;
    min=cpart->m_pre_number;
    max=cpart->m_post_number;

>>>>>>> blockingImplementation
    pthread_rwlock_t  *lock = dominatorHelper::getDominatorLock(dataHolder, &(min),&(max));
    auto *inv = new interval(min,max,1);
    if(!ICheck.IsOverlap(inv, 1, tid)) {
        pthread_rwlock_wrlock(lock);
        dataHolder->deleteCompositePart(cpart);
        pthread_rwlock_unlock(lock);
        ICheck.Delete(tid);
    }
	return 0;
}

/////////////////////////////
// StructuralModification3 //
/////////////////////////////

int sb7::DomStructuralModification3::run(int tid) const {
	// generate random composite part id
	int cpartId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
	CompositePart *cpart = dataHolder->getCompositePart(cpartId);

	if(cpart == NULL || cpart->m_pre_number==0 || cpart->m_post_number==0) {
		throw Sb7Exception();
	}

	// generate random base assembly id
	int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
	BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

	if(bassm == NULL|| bassm->m_pre_number==0 || bassm->m_post_number==0) {
		throw Sb7Exception();
	}

    long min = bassm-> m_pre_number;
    long max = bassm-> m_post_number;
    if(cpart-> m_pre_number < min )
        min = cpart-> m_pre_number;
    if(cpart-> m_post_number > max )
        max = cpart-> m_post_number;

<<<<<<< HEAD
    auto *inv = new interval(dataHolder->getModule()->getDesignRoot()->m_pre_number,dataHolder->getModule()->getDesignRoot()->m_post_number,1);
=======
    pthread_rwlock_t  *lock = dominatorHelper::getDominatorLock(dataHolder, &(min),&(max));
    auto *inv = new interval(min,max,1);
>>>>>>> blockingImplementation
    if(!ICheck.IsOverlap(inv, 1, tid)) {
        bassm->addComponent(cpart);
        auto t1 = std::chrono::high_resolution_clock::now();
        auto *r = new DomRelabelling(dataHolder);
        auto t1 = std::chrono::high_resolution_clock::now();
        r->traverse(dataHolder->getModule()->getDesignRoot());
        auto t2 = std::chrono::high_resolution_clock::now();
<<<<<<< HEAD
        ICheck.modificationTimeDom+= t2-t1;
=======
        ICheck.modificationTimeDom+= (t2-t1);
        ICheck.count.fetch_add(1);
        pthread_rwlock_unlock(lock);
>>>>>>> blockingImplementation
        ICheck.Delete(tid);
    }
	return 0;
}

/////////////////////////////
// StructuralModification4 //
/////////////////////////////

int sb7::DomStructuralModification4::run(int tid) const {
    int cassmId = get_random()->nextInt(parameters.getMaxComplexAssemblies()) + 1;
    cassmId = (cassmId *(tid+1)) % parameters.getMaxComplexAssemblies();
    ComplexAssembly *cassm = dataHolder->getComplexAssembly(cassmId);
    if (cassm == nullptr || cassm->isDeleted) {
        throw Sb7Exception();
    }

<<<<<<< HEAD
	// generate random base assembly id
	int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
	BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

	if(bassm == nullptr) {
		throw Sb7Exception();
	}	

	// select one of composite parts used in the base assembly
	Set<CompositePart *> *cpartBag = bassm->getComponents();
	int compNum = cpartBag->size();

	if(compNum == 0) {
		throw Sb7Exception();
	}

	int nextId = get_random()->nextInt(compNum);

	// find component with that ordinal number
	SetIterator<CompositePart *> iter = cpartBag->getIter();
	int i = 0;

	while(iter.has_next()) {
		CompositePart *cpart = iter.next();

		if(nextId == i) {
            auto *inv = new interval(dataHolder->getModule()->getDesignRoot()->m_pre_number,dataHolder->getModule()->getDesignRoot()->m_post_number,1);
            if(!ICheck.IsOverlap(inv, 1, tid)) {
                bassm->removeComponent(cpart);
                auto *r = new DomRelabelling(dataHolder);
                r->traverse(dataHolder->getModule()->getDesignRoot());
                ICheck.Delete(tid);
            }
			return 0;
		}

		i++;
	}

	throw Sb7Exception(
		"SM4: concurrent modification of BaseAssembly.components!");
=======
    auto * l = new interval (dataHolder->getModule()->getDesignRoot()->m_pre_number, dataHolder->getModule()->getDesignRoot()->m_post_number, 1);
    if(!ICheck.IsOverlap(l, 1, tid)) {
        dataHolder->createSubAssembly(dataHolder->getModule()->getDesignRoot(), 1);
        auto *r = new DomRelabelling(dataHolder);
        auto t1 = std::chrono::high_resolution_clock::now();
        r->traverse(dataHolder->getModule()->getDesignRoot());
        auto t2 = std::chrono::high_resolution_clock::now();
        ICheck.modificationTimeDom+= (t2-t1);
        ICheck.count.fetch_add(1);
        ICheck.Delete(tid);
    }
    return 0;
>>>>>>> blockingImplementation
}

/////////////////////////////
// StructuralModification5 //
/////////////////////////////

int sb7::DomStructuralModification5::run(int tid) const {
<<<<<<< HEAD
	//WriteLockHandle writeLockHandle(dom_lock_srv.getLock());

	// generate random base assembly id
	int bassmId = get_random()->nextInt(
		parameters.getMaxBaseAssemblies()) + 1;
	BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

	if(bassm == NULL) {
		throw Sb7Exception();
	}

    auto * cassm =  bassm->getSuperAssembly();

    auto *inv = new interval(dataHolder->getModule()->getDesignRoot()->m_pre_number,dataHolder->getModule()->getDesignRoot()->m_post_number,1);
    if(!ICheck.IsOverlap(inv, 1, tid)) {
        // create sibling base assembly
        dataHolder->createBaseAssembly(bassm->getSuperAssembly());
=======
    auto * l = new interval (dataHolder->getModule()->getDesignRoot()->m_pre_number, dataHolder->getModule()->getDesignRoot()->m_post_number, 1);
    if(!ICheck.IsOverlap(l, 1, tid)) {
        dataHolder->createSubAssembly(dataHolder->getModule()->getDesignRoot(), 1);
>>>>>>> blockingImplementation
        auto *r = new DomRelabelling(dataHolder);
        auto t1 = std::chrono::high_resolution_clock::now();
        r->traverse(dataHolder->getModule()->getDesignRoot());
        auto t2 = std::chrono::high_resolution_clock::now();
        ICheck.modificationTimeDom+= (t2-t1);
        ICheck.count.fetch_add(1);
        ICheck.Delete(tid);
    }
    return 0;
}

/////////////////////////////
// StructuralModification6 //
/////////////////////////////

int sb7::DomStructuralModification6::run(int tid) const {
	//WriteLockHandle writeLockHandle(dom_lock_srv.getLock());

	// generate random base assembly id
	int bassmId = get_random()->nextInt(
		parameters.getMaxBaseAssemblies()) + 1;
	BaseAssembly *bassm = dataHolder->getBaseAssembly(bassmId);

	if(bassm == NULL) {
		throw Sb7Exception();
	}	

	// get parent and check that it has at least one more child
	ComplexAssembly *cassm = bassm->getSuperAssembly();
	Set<Assembly *> *subAssmSet = cassm->getSubAssemblies();

	// don't let the tree break
	if(subAssmSet->size() == 1) {
		throw Sb7Exception();
	}

    auto *inv = new interval(cassm->m_pre_number,cassm->m_post_number,1);
    if(!ICheck.IsOverlap(inv, 1, tid)) {
        dataHolder->deleteBaseAssembly(bassm);
        auto *r = new DomRelabelling(dataHolder);
        r->traverse(dataHolder->getModule()->getDesignRoot());
        ICheck.Delete(tid);
    }

	return 0;
}

/////////////////////////////
// StructuralModification7 //
/////////////////////////////

int sb7::DomStructuralModification7::run(int tid) const {
	//WriteLockHandle writeLockHandle(dom_lock_srv.getLock());

	// generate random complex assembly id
	int cassmId = get_random()->nextInt(
		parameters.getMaxComplexAssemblies()) + 1;
	ComplexAssembly *cassm = dataHolder->getComplexAssembly(cassmId);

	if(cassm == NULL) {
		throw Sb7Exception();
	}

    auto *inv = new interval(cassm->m_pre_number,cassm->m_post_number,1);
    if(!ICheck.IsOverlap(inv, 1, tid)) {
        // create sub assembly
        dataHolder->createSubAssembly(cassm, parameters.getNumAssmPerAssm());
        auto *r = new DomRelabelling(dataHolder);
        r->traverse(dataHolder->getModule()->getDesignRoot());
        ICheck.Delete(tid);
    }



	return 1;
}

/////////////////////////////
// StructuralModification8 //
/////////////////////////////

int sb7::DomStructuralModification8::run(int tid) const {
	//WriteLockHandle writeLockHandle(dom_lock_srv.getLock());

	// generate random complex assembly id
	int cassmId = get_random()->nextInt(
		parameters.getMaxComplexAssemblies()) + 1;
	ComplexAssembly *cassm = dataHolder->getComplexAssembly(cassmId);

	if(cassm == NULL) {
		throw Sb7Exception();
	}

	// get super assembly
	ComplexAssembly *superAssm = cassm->getSuperAssembly();

	// don't continue if we got root complex assembly
	if(superAssm == NULL) {
		throw Sb7Exception();
	}

	// check if this would break the tree structure
	Set<Assembly *> *assmSet = superAssm->getSubAssemblies();

	if(assmSet->size() == 1) {
		throw Sb7Exception();
	}

    auto *inv = new interval(superAssm->m_pre_number,superAssm->m_post_number,1);
    if(!ICheck.IsOverlap(inv, 1, tid)) {
        // delete selected complex assembly
        dataHolder->deleteComplexAssembly(cassm);
        auto *r = new DomRelabelling(dataHolder);
        r->traverse(dataHolder->getModule()->getDesignRoot());
        ICheck.Delete(tid);
    }


	return 1;
}
