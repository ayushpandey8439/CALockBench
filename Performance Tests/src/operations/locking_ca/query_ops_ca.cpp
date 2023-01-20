//
// Created by Ayush Pandey on 15/11/2022.
//

#include "query_ops_ca.h"
#include "../../helpers.h"
#include "../../parameters.h"
#include "../../lockPool.h"
#include "../../sb7_exception.h"
#include "boost/container/list.hpp"

extern lockPool pool;
////////////
// Query1 //
////////////

#define QUERY1_ITER 10


int sb7::CAQuery1::run(int tid) const {
    //ReadLockHandle readLockHandle(CA_lock_srv.getLock());
    return innerRun(tid);
}

int sb7::CAQuery1::innerRun(int tid) const {
    int count = 0;
    int apart = get_random()->nextInt(
            parameters.getMaxAtomicParts()) + 1;
    Map<int, AtomicPart *> *apartInd = dataHolder->getAtomicPartIdIndex();
    Map<int, AtomicPart *>::Query query;
    query.key = apart;
    apartInd->get(query);

    if (query.found && query.val->hasLabel) {
        AtomicPart * a = query.val;
        if(string(name)=="Q1"){
            auto * l = new lockObject(a->getLabellingId(), &a->criticalAncestors, 0);
            pool.acquireLock(l, tid);
            performOperationOnAtomicPart(query.val);
            count++;
            pool.releaseLock(l, tid);
        }
        else if(string(name) == "OP9"|| string(name) == "OP15") {
            auto * l = new lockObject(a->getLabellingId(), &a->criticalAncestors, 1);
            pool.acquireLock(l, tid);
            performOperationOnAtomicPart(query.val);
            count++;
            pool.releaseLock(l, tid);
        }
    } else {
        //cout<<"found without label"<<endl;
        throw Sb7Exception();
    }
    return count;
}

void sb7::CAQuery1::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->nullOperation();
}

////////////
// Query2 //
////////////

sb7::CAQuery2::CAQuery2(DataHolder *dh, optype t, const char *n, int p)
        : Operation(t, n, dh) {
    percent = p;
}

int sb7::CAQuery2::run(int tid) const {
    return innerRun(tid);
}

int sb7::CAQuery2::innerRun(int tid) const {
    int count = 0;

    int range = percent* (parameters.getMaxAtomicDate() -
                          parameters.getMinAtomicDate())/100;
    int min = get_random()->nextInt(parameters.getMaxAtomicDate()-range);
    int max = min+range;

    Map<int, Set<AtomicPart *> *> *setInd =
            dataHolder->getAtomicPartBuildDateIndex();
    MapIterator<int, Set<AtomicPart *> *> iter =
            setInd->getRange(min, max);

    while(iter.has_next()) {
        Set<AtomicPart *> *apartSet = iter.next();
        SetIterator<AtomicPart *> apartIter = apartSet->getIter();

        while(apartIter.has_next()) {
            AtomicPart *apart = apartIter.next();
            if(apart->hasLabel) {
                performOperationOnAtomicPart(apart);
                count++;
            }
        }
    }

    return count;
}

void sb7::CAQuery2::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->nullOperation();
}
