#include "operation_ops_lm.h"

#include "../../parameters.h"
#include "../../sb7_exception.h"
#include "lock_srv_lm.h"
#include "../../thread/thread.h"
#include "../../mediumPool.h"

////////////////
// Operation6 //
////////////////
extern mediumPool mPool;

int sb7::LMOperation6::run(int tid) const {
//	ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());

	// Generate one random number that is in range of possible complex assembly
	// identifiers. It is used to look up complex assembly.
	//
	// TODO try to figure out how to generate these ids in a more precise way
	// so this operation fails only if it is really 
	//
	int cassmId = get_random()->nextInt(
		parameters.getMaxComplexAssemblies()) + 1;

	// lookup complex assembly using complex assembly index
	Map<int, ComplexAssembly *> *cassmInd =
		dataHolder->getComplexAssemblyIdIndex();
	Map<int, ComplexAssembly *>::Query query;
	query.key = cassmId;
	cassmInd->get(query);

	// If complex assembly is not found throw an exception.
	// This is an easy way to get out of the transaction.
	if(!query.found || !query.val->hasLabel) {
		throw Sb7Exception();
	}
    int ret;

    // if complex assembly was found process it
    ComplexAssembly *cassm = query.val;
    ComplexAssembly *superAssm = cassm->getSuperAssembly();
    // if this assembly is root perform operation on it
    if(superAssm == NULL || !superAssm->hasLabel) {
        ComplexAssembly *superAssm = cassm->getSuperAssembly();
        int lockLvl = (superAssm == NULL ? cassm : superAssm)->getLevel() - 1;
        int lockType = (lockLvl*10)+1;
        auto * c = new mediumLock(0,lockType);
        mPool.acquire(c,tid);
        performOperationOnComplexAssembly(cassm);
        mPool.release(tid);
        return 0;
    } else {
        // else perform operation on all it's siblings (including itself)
        Set<Assembly *> *siblingAssms = superAssm->getSubAssemblies();
        SetIterator<Assembly *> iter = siblingAssms->getIter();
        ret = 0;
        ComplexAssembly *superAssm = cassm->getSuperAssembly();
        int lockLvl = (superAssm == NULL ? cassm : superAssm)->getLevel() - 1;
        int lockType = (lockLvl*10)+1;
        auto * c = new mediumLock(0,lockType);
        mPool.acquire(c,tid);
        while(iter.has_next()) {
            performOperationOnComplexAssembly((ComplexAssembly *)iter.next());
            ret++;
        }
        mPool.release(tid);
        return 0;
    }

    return 0;
}

int sb7::LMOperation6::processComplexAssemblyWrap(sb7::ComplexAssembly *cassm) const {
    return 0;
}

void sb7::LMOperation6::performOperationOnComplexAssembly(
		ComplexAssembly *cassm) const {
	cassm->nullOperation();
}

////////////////
// Operation7 //
////////////////

int sb7::LMOperation7::run(int tid) const {
//	ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//	ReadLockHandle bassmLockHandle(lm_lock_srv.getBaseAssemblyLock());

	return innerRun(tid);
}

int sb7::LMOperation7::innerRun(int tid) const {
	// Generate one random number that is in range of possible base assembly
	// identifiers. It is used to look up base assembly from index.
	//
	// TODO try to figure out how to generate these ids in a more precise way
	// so this operation fails only if it is really 
	//
	int bassmId = get_random()->nextInt(parameters.getMaxBaseAssemblies()) + 1;
	
	// lookup base assembly using base assembly index
	Map<int, BaseAssembly *> *bassmInd = dataHolder->getBaseAssemblyIdIndex();
	Map<int, BaseAssembly *>::Query query;
	query.key = bassmId;
	bassmInd->get(query);

	if(!query.found || !query.val->hasLabel) {
		throw Sb7Exception();
	}

	// process all sibling base assemblies
	ComplexAssembly *superAssm = query.val->getSuperAssembly();
	Set<Assembly *> *siblingSet = superAssm->getSubAssemblies();
	SetIterator<Assembly *> iter = siblingSet->getIter();
	int ret = 0;
    auto * c = new mediumLock(0,2);
    mPool.acquire(c,tid);

	while(iter.has_next()) {
		performOperationOnBaseAssembly((BaseAssembly *)iter.next());
		ret++;
	}
    mPool.release(tid);

	return ret;
}

void sb7::LMOperation7::performOperationOnBaseAssembly(
		BaseAssembly *bassm) const {
	bassm->nullOperation();
}

////////////////
// Operation8 //
////////////////

int sb7::LMOperation8::run(int tid) const {
	ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
	ReadLockHandle cpartLockHandle(lm_lock_srv.getCompositePartLock());

	return innerRun();
}

int sb7::LMOperation8::innerRun() const {
	// Generate one random number that is in range of possible base assembly
	// identifiers. It is used to look up base assembly from index.
	//
	// TODO try to figure out how to generate these ids in a more precise way
	// so this operation fails only if it is really 
	//
	int bassmId = get_random()->nextInt(
		parameters.getMaxBaseAssemblies()) + 1;
	
	// lookup base assembly using base assembly index
	Map<int, BaseAssembly *> *bassmInd = dataHolder->getBaseAssemblyIdIndex();
	Map<int, BaseAssembly *>::Query query;
	query.key = bassmId;
	bassmInd->get(query);

	if(!query.found) {
		throw Sb7Exception();
	}

	Set<CompositePart *> *componentBag = query.val->getComponents();
	SetIterator<CompositePart *> iter = componentBag->getIter();
	int ret = 0;

	while(iter.has_next()) {
		performOperationOnComponent(iter.next());
		ret++;
	}

	return ret;
}

void sb7::LMOperation8::performOperationOnComponent(CompositePart *comp) const {
	comp->nullOperation();
}

////////////////
// Operation9 //
////////////////

int sb7::LMOperation9::run(int tid) const {
//	ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//	WriteLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());

	return LMQuery1::innerRun(tid);
}

void sb7::LMOperation9::performOperationOnAtomicPart(AtomicPart *apart) const {
	apart->swapXY();
}

////////////////
// Operation10 //
////////////////

int sb7::LMOperation10::run(int tid) const {
//	ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
//	WriteLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());

	return LMQuery2::innerRun(tid);
}


void sb7::LMOperation10::performOperationOnAtomicPart(AtomicPart *apart) const {
	apart->swapXY();
}

/////////////////
// Operation11 //
/////////////////

#define MANUAL_TEXT_START_1 'I'
#define MANUAL_TEXT_START_2 'i'

int sb7::LMOperation11::run(int tid) const {
	ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
	WriteLockHandle manLockHandle(lm_lock_srv.getManualLock());

	return LMTraversal8::traverse(dataHolder->getModule()->getManual());
}

int sb7::LMOperation11::traverse(Manual *manual) const {
	int ret;

	if(manual->startsWith(MANUAL_TEXT_START_1)) {
		ret = manual->replaceChar(MANUAL_TEXT_START_1, MANUAL_TEXT_START_2);
	} else if(manual->startsWith(MANUAL_TEXT_START_2)) {
		ret = manual->replaceChar(MANUAL_TEXT_START_2, MANUAL_TEXT_START_1);
	} else {
		throw Sb7Exception("OP11: unexpected Manual.text!");
	}

	return ret;
}

/////////////////
// Operation12 //
/////////////////

int sb7::LMOperation12::processComplexAssemblyWrap(
		ComplexAssembly *cassm) const {
	ComplexAssembly *superAssm = cassm->getSuperAssembly();
	int lockLvl = (superAssm == NULL ? cassm : superAssm)->getLevel() - 1;
	WriteLockHandle assmLockHandle(lm_lock_srv.getAssemblyLock(lockLvl));

	performOperationOnComplexAssembly(cassm);
    return 0;
}

void sb7::LMOperation12::performOperationOnComplexAssembly(
		ComplexAssembly *cassm) const {
	cassm->updateBuildDate();
}

/////////////////
// Operation13 //
/////////////////

int sb7::LMOperation13::run(int tid) const {
	ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
	WriteLockHandle bassmLockHandle(lm_lock_srv.getBaseAssemblyLock());
	return innerRun(tid);
}

void sb7::LMOperation13::performOperationOnBaseAssembly(
		BaseAssembly *bassm) const {
	bassm->updateBuildDate();
}

/////////////////
// Operation14 //
/////////////////

int sb7::LMOperation14::run(int tid) const {
	ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
	WriteLockHandle cpartLockHandle(lm_lock_srv.getCompositePartLock());

	return innerRun();
}

void sb7::LMOperation14::performOperationOnComponent(
		CompositePart *cpart) const {
	cpart->updateBuildDate();
}

/////////////////
// Operation15 //
/////////////////

int sb7::LMOperation15::run(int tid) const {
	ReadLockHandle smLockHandle(lm_lock_srv.getStructureModificationLock());
	WriteLockHandle apartLockHandle(lm_lock_srv.getAtomicPartLock());

	return LMQuery1::innerRun(tid);
}

void sb7::LMOperation15::performOperationOnAtomicPart(AtomicPart *apart) const {
	dataHolder->removeAtomicPartFromBuildDateIndex(apart);
	apart->updateBuildDate();
	dataHolder->addAtomicPartToBuildDateIndex(apart);
}
