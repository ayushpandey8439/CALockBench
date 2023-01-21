#include "query_ops_dom.h"

#include "../../helpers.h"
#include "../../parameters.h"
#include "../../interval.h"
#include "../../sb7_exception.h"
#include "../../dominatorHelper.h"
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
    long min=INFINITY,max=-1;
    int apartId= get_random()->nextInt(
            parameters.getMaxAtomicParts()) + 1;
    Map<int, AtomicPart *> *apartInd = dataHolder->getAtomicPartIdIndex();
    Map<int, AtomicPart *>::Query query;
    query.key = apartId;
    apartInd->get(query);

    if(query.found && query.val->m_pre_number!=0 && query.val->m_post_number!=0){
        min=query.val->m_pre_number;
        max=query.val->m_post_number;

        if(string(name) == "Q1"){
            pthread_rwlock_t  *lock = dominatorHelper::getDominatorLock(dataHolder, &(min),&(max));
            auto *inv = new interval(min,max,0);
            if(!ICheck.IsOverlap(inv, 0, threadID))
            {
                pthread_rwlock_rdlock(lock);
                performOperationOnAtomicPart(query.val);
                count++;
                pthread_rwlock_unlock(lock);
                ICheck.Delete(threadID);
            }
        }
        else if(string(name) == "OP9" || string(name) == "OP15"){
            pthread_rwlock_t  *lock = dominatorHelper::getDominatorLock(dataHolder, &min,&(max));
            auto *inv = new interval(min,max,1);
            if(!ICheck.IsOverlap(inv, 1, threadID))
            {
                pthread_rwlock_wrlock(lock);
                performOperationOnAtomicPart(query.val);
                count++;
                pthread_rwlock_unlock(lock);
                ICheck.Delete(threadID);
            }
        }
    } else {
        Sb7Exception();
    }
    return count;
}

void sb7::DomQuery1::performOperationOnAtomicPart(AtomicPart *apart) const {
	apart->nullOperation();
}

////////////
// Query2 //
////////////

sb7::DomQuery2::DomQuery2(DataHolder *dh, optype t, const char *n, int p)
		: Operation(t, n, dh) {
    percent = p;
//	maxAtomicDate = parameters.getMaxAtomicDate();
//	minAtomicDate = parameters.getMaxAtomicDate() -
//		percent * (parameters.getMaxAtomicDate() -
//					parameters.getMinAtomicDate()) / 100;
}

int sb7::DomQuery2::run(int tid) const {
	//ReadLockHandle readLockHandle(dom_lock_srv.getLock());
	return innerRun(tid);
}

int sb7::DomQuery2::innerRun(int tid) const {
	int count = 0;
    long min=0, max=0;

    int range = percent* (parameters.getMaxAtomicDate() -
                          parameters.getMinAtomicDate())/100;
    int minA = get_random()->nextInt(parameters.getMaxAtomicDate()-range);
    int maxA = minA+range;

	Map<int, Set<AtomicPart *> *> *setInd =
		dataHolder->getAtomicPartBuildDateIndex();
	MapIterator<int, Set<AtomicPart *> *> iter =
		setInd->getRange(minA, maxA);

	while(iter.has_next()) {
		Set<AtomicPart *> *apartSet = iter.next();
		SetIterator<AtomicPart *> apartIter = apartSet->getIter();
        vector<AtomicPart*> aparts;
        while (apartIter.has_next()) {
            AtomicPart *apart = apartIter.next();
            if(apart->m_pre_number!=0 && apart->m_post_number!=0) {
                if(min == 0 && max == 0)
                {
                    min = apart-> m_pre_number;
                    max = apart-> m_post_number;
                }
                else {
                    if(apart-> m_pre_number < min )
                        min = apart-> m_pre_number;
                    if(apart-> m_post_number > max )
                        max = apart-> m_post_number;
                }
                aparts.push_back(apart);
            }
        }
        int mode = 0;
        if(string(name) == "Q2")
            mode = 0;
        if(string(name) == "OP10")
            mode = 1;

        pthread_rwlock_t  *lock = dominatorHelper::getDominatorLock(dataHolder, &(min),&(max));
        auto *inv = new interval(min,max,mode);
        if(!ICheck.IsOverlap(inv, mode, tid)) {
            if(mode==0){
                pthread_rwlock_rdlock(lock);
            } else {
                pthread_rwlock_wrlock(lock);
            }

            for(auto * apart: aparts){
                performOperationOnAtomicPart(apart);
                count++;
            }
            pthread_rwlock_unlock(lock);
            ICheck.Delete(tid);
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
			Set<BaseAssembly *> *usedIn = cpart->getUsedIn();
			SetIterator<BaseAssembly *> iter = usedIn->getIter();

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
	Set<CompositePart *> *cparts = bassm->getComponents();
	SetIterator<CompositePart *> iter = cparts->getIter();

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
