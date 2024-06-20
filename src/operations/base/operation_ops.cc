#include "operation_ops.h"

#include "../../parameters.h"
#include "../../sb7_exception.h"

////////////////
// Operation6 //
////////////////

int sb7::Operation6::run() const {
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
	if(!query.found) {
		throw Sb7Exception();
	}

	int ret;

	// if complex assembly was found process it
	ComplexAssembly *cassm = query.val;
	ComplexAssembly *superAssm = cassm->getSuperAssembly();

	// if this assembly is root perform operation on it
	if(superAssm == NULL) {
		performOperationOnComplexAssembly(cassm);
		ret = 1;
	} else {
		// else perform operation on all it's siblings (including itself)
		Set<Assembly *> *siblingAssms = superAssm->getSubAssemblies();
		SetIterator<Assembly *> iter = siblingAssms->getIter();
		ret = 0;

		while(iter.has_next()) {
			performOperationOnComplexAssembly((ComplexAssembly *)iter.next());
			ret++;
		}
	}

	return ret;
}

void sb7::Operation6::performOperationOnComplexAssembly(
		ComplexAssembly *cassm) const {
	cassm->nullOperation();
}

////////////////
// Operation7 //
////////////////

int sb7::Operation7::run() const {
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

	if(!query.found) {
		throw Sb7Exception();
	}

	// process all sibling base assemblies
	ComplexAssembly *superAssm = query.val->getSuperAssembly();
	Set<Assembly *> *siblingSet = superAssm->getSubAssemblies();
	SetIterator<Assembly *> iter = siblingSet->getIter();
	int ret = 0;

	while(iter.has_next()) {
		performOperationOnBaseAssembly((BaseAssembly *)iter.next());
		ret++;
	}

	return ret;
}

void sb7::Operation7::performOperationOnBaseAssembly(
		BaseAssembly *bassm) const {
	bassm->nullOperation();
}

////////////////
// Operation8 //
////////////////

int sb7::Operation8::run() const {
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

	Bag<CompositePart *> *componentBag = query.val->getComponents();
	BagIterator<CompositePart *> iter = componentBag->getIter();
	int ret = 0;

	while(iter.has_next()) {
		performOperationOnComponent(iter.next());
		ret++;
	}

	return ret;
}

void sb7::Operation8::performOperationOnComponent(CompositePart *comp) const {
	comp->nullOperation();
}

////////////////
// Operation9 //
////////////////

void sb7::Operation9::performOperationOnAtomicPart(AtomicPart *apart) const {
	apart->swapXY();
}

////////////////
// Operation10 //
////////////////

void sb7::Operation10::performOperationOnAtomicPart(AtomicPart *apart) const {
	apart->swapXY();
}

/////////////////
// Operation11 //
/////////////////

#define MANUAL_TEXT_START_1 'I'
#define MANUAL_TEXT_START_2 'i'

int sb7::Operation11::traverse(Manual *manual) const {
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

void sb7::Operation12::performOperationOnComplexAssembly(
		ComplexAssembly *cassm) const {
	cassm->updateBuildDate();
}

/////////////////
// Operation13 //
/////////////////

void sb7::Operation13::performOperationOnBaseAssembly(
		BaseAssembly *bassm) const {
	bassm->updateBuildDate();
}

/////////////////
// Operation14 //
/////////////////

void sb7::Operation14::performOperationOnComponent(
		CompositePart *cpart) const {
	cpart->updateBuildDate();
}

/////////////////
// Operation15 //
/////////////////

void sb7::Operation15::performOperationOnAtomicPart(AtomicPart *apart) const {
	dataHolder->removeAtomicPartFromBuildDateIndex(apart);
	apart->updateBuildDate();
	dataHolder->addAtomicPartToBuildDateIndex(apart);
}
