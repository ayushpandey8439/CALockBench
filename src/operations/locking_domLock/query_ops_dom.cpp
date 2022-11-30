#include "query_ops_dom.h"

#include "../../helpers.h"
#include "../../parameters.h"
#include "../../interval.h"

extern IntervalCheck ICheck;

////////////
// Query1 //
////////////

#define QUERY1_ITER 10

int sb7::DomQuery1::run(int tid) const {
	//ReadLockHandle readLockHandle(dom_lock_srv.getLock());
	return innerRun(tid);
}

int sb7::DomQuery1::innerRun(int tid) const {
	int count = 0;
    int threadID = tid;
    int min=500000,max=0;
    vector<AtomicPart*> aparts;
    for(int i = 0; i < QUERY1_ITER; i++) {
        int apartId= get_random()->nextInt(
                parameters.getMaxAtomicParts()) + 1;
        Map<int, AtomicPart *> *apartInd = dataHolder->getAtomicPartIdIndex();
        Map<int, AtomicPart *>::Query query;
        query.key = apartId;
        apartInd->get(query);
        if(query.found && query.val->m_pre_number!=0){
            if((query.val)-> m_pre_number < min )
                min = (query.val)-> m_pre_number;
            if((query.val)-> m_post_number > max )
                max = (query.val)-> m_post_number;
        }
    }

    if(string(name) == "Q1"){
        auto *inv = new interval(min,max,0);
        if(!ICheck.IsOverlap(inv, 0, threadID))
        {
            for(auto *a :aparts){
                performOperationOnAtomicPart(a);
                count++;
            }
            ICheck.Delete(threadID);
        }
    }

    return count;
}

void sb7::DomQuery1::performOperationOnAtomicPart(AtomicPart *apart) const {
	apart->nullOperation();
}

////////////
// Query2 //
////////////

sb7::DomQuery2::DomQuery2(DataHolder *dh, optype t, const char *n, int percent)
		: Operation(t, n, dh) {
	maxAtomicDate = parameters.getMaxAtomicDate();
	minAtomicDate = parameters.getMaxAtomicDate() -
		percent * (parameters.getMaxAtomicDate() -
					parameters.getMinAtomicDate()) / 100;
}

int sb7::DomQuery2::run(int tid) const {
	//ReadLockHandle readLockHandle(dom_lock_srv.getLock());
	return innerRun(tid);
}

int sb7::DomQuery2::innerRun(int tid) const {
	int count = 0;
	Map<int, Set<AtomicPart *> *> *setInd =
		dataHolder->getAtomicPartBuildDateIndex();
	MapIterator<int, Set<AtomicPart *> *> iter =
		setInd->getRange(minAtomicDate, maxAtomicDate);

	while(iter.has_next()) {
		Set<AtomicPart *> *apartSet = iter.next();
		SetIterator<AtomicPart *> apartIter = apartSet->getIter();

		while(apartIter.has_next()) {
			AtomicPart *apart = apartIter.next();

            if(apart->m_pre_number!=0) {
                int min = apart-> m_pre_number;
                int max = apart-> m_post_number;
                auto *inv = new interval(min,max,0);
                if(!ICheck.IsOverlap(inv, 0, tid))
                {
                    performOperationOnAtomicPart(apart);
                    count++;
                    ICheck.Delete(tid);
                }
            }
		}
	}

	return count;
}

void sb7::DomQuery2::performOperationOnAtomicPart(AtomicPart *apart) const {
	apart->nullOperation();
}

////////////
// Query4 //
////////////

#define QUERY4_ITER 100

int sb7::DomQuery4::run(int tid) const {
	//ReadLockHandle readLockHandle(dom_lock_srv.getLock());

	int ret = 0;
	
	for(int i = 0;i < QUERY4_ITER;i++) {
		// construct name of documentation for composite part
		int partId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
		// TODO move all these constants to separate header file
		ITOA(itoa_buf, partId);
		string title = "Composite Part #" + (string)itoa_buf;

		// search for document with that name
		Map<string, Document *> *docInd = dataHolder->getDocumentTitleIndex();
		Map<string, Document *>::Query query;
		query.key = title;
		docInd->get(query);

		if(query.found) {
			Document *doc = query.val;
			CompositePart *cpart = doc->getCompositePart();
			Bag<BaseAssembly *> *usedIn = cpart->getUsedIn();
			BagIterator<BaseAssembly *> iter = usedIn->getIter();

			while(iter.has_next()) {
				BaseAssembly *bassm = iter.next();
				bassm->nullOperation();
				ret++;
			}
		}
	}

	return ret;
}

////////////
// Query5 //
////////////

int sb7::DomQuery5::run(int tid) const {
	//ReadLockHandle readLockHandle(dom_lock_srv.getLock());
	int ret = 0;

	Map<int, BaseAssembly *> *bassmInd = dataHolder->getBaseAssemblyIdIndex();
	MapIterator<int, BaseAssembly *> iter = bassmInd->getAll();

	while(iter.has_next()) {
		ret += checkBaseAssembly(iter.next());
	} 

	return ret;
}

int sb7::DomQuery5::checkBaseAssembly(BaseAssembly *bassm) const {
	int assmBuildDate = bassm->getBuildDate();
	Bag<CompositePart *> *cparts = bassm->getComponents();
	BagIterator<CompositePart *> iter = cparts->getIter();

	while(iter.has_next()) {
		CompositePart *cpart = iter.next();

		if(cpart->getBuildDate() > assmBuildDate) {
			bassm->nullOperation();
			return 1;
		}
	}

	return 0;
}

////////////
// Query6 //
////////////

int sb7::DomQuery6::run(int tid) const {
	//ReadLockHandle readLockHandle(dom_lock_srv.getLock());
	return checkComplexAssembly(dataHolder->getModule()->getDesignRoot());
}

int sb7::DomQuery6::checkAssembly(Assembly *assembly) const {
	if(assembly->getType() == assembly_type_complex) {
		return checkComplexAssembly((ComplexAssembly *)assembly);
	} else {
		return checkBaseAssembly((BaseAssembly *)assembly);
	}
}

int sb7::DomQuery6::checkComplexAssembly(ComplexAssembly *assembly) const {
	int ret = 0;

	Set<Assembly *> *subAssmSet = assembly->getSubAssemblies();
	SetIterator<Assembly *> iter = subAssmSet->getIter();

	while(iter.has_next()) {
		ret += checkAssembly(iter.next());
	}

	if(ret) {
		assembly->nullOperation();
		ret++;
	}

	return ret;
}

////////////
// Query7 //
////////////

int sb7::DomQuery7::run(int tid) const {
	//ReadLockHandle readLockHandle(dom_lock_srv.getLock());
	int ret = 0;

	Map<int, AtomicPart *> *apartInd = dataHolder->getAtomicPartIdIndex();
	MapIterator<int, AtomicPart *> iter = apartInd->getAll();

	while(iter.has_next()) {
		AtomicPart *apart = iter.next();
		apart->nullOperation();
		ret++;
	}

	return ret;
}
