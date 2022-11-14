#include "query_ops_lc.h"
#include "lock_srv_lc.h"
#include "../../thread/thread.h"

#include "../../helpers.h"
#include "../../containers.h"
#include "../../parameters.h"
#include "../../struct/assembly.h"

////////////
// Query1 //
////////////

#define QUERY1_ITER 10

int sb7::LCQuery1::run() const {
    ReadLockHandle readLockHandle(lc_lock_srv.getLock());
    return innerRun();
}

int sb7::LCQuery1::innerRun() const {
    int count = 0;

    for (int i = 0; i < QUERY1_ITER; i++) {
        int apartId = get_random()->nextInt(
                parameters.getMaxAtomicParts()) + 1;

        Map<int, AtomicPart *> *apartInd = dataHolder->getAtomicPartIdIndex();
        Map<int, AtomicPart *>::Query query;
        query.key = apartId;
        apartInd->get(query);

        if (query.found) {
            performOperationOnAtomicPart(query.val);
            count++;
        }
    }

    return count;
}

void sb7::LCQuery1::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->nullOperation();
}

////////////
// Query2 //
////////////

sb7::LCQuery2::LCQuery2(DataHolder *dh, optype t, const char *n, int percent)
        : Operation(t, n, dh) {
    maxAtomicDate = parameters.getMaxAtomicDate();
    minAtomicDate = parameters.getMaxAtomicDate() -
                    percent * (parameters.getMaxAtomicDate() -
                               parameters.getMinAtomicDate()) / 100;
}

int sb7::LCQuery2::run() const {
    ReadLockHandle readLockHandle(lc_lock_srv.getLock());
    return innerRun();
}

int sb7::LCQuery2::innerRun() const {
    int count = 0;
    Map<int, Set<AtomicPart *> *> *setInd =
            dataHolder->getAtomicPartBuildDateIndex();
    MapIterator<int, Set<AtomicPart *> *> iter =
            setInd->getRange(minAtomicDate, maxAtomicDate);

    while (iter.has_next()) {
        Set<AtomicPart *> *apartSet = iter.next();
        SetIterator<AtomicPart *> apartIter = apartSet->getIter();

        while (apartIter.has_next()) {
            AtomicPart *apart = apartIter.next();
            performOperationOnAtomicPart(apart);
            count++;
        }
    }

    return count;
}

void sb7::LCQuery2::performOperationOnAtomicPart(AtomicPart *apart) const {
    apart->nullOperation();
}

////////////
// Query4 //
////////////

#define QUERY4_ITER 100

int sb7::LCQuery4::run() const {
    ReadLockHandle readLockHandle(lc_lock_srv.getLock());

    int ret = 0;

    for (int i = 0; i < QUERY4_ITER; i++) {
        // construct name of documentation for composite part
        int partId = get_random()->nextInt(parameters.getMaxCompParts()) + 1;
        // TODO move all these constants to separate header file
        ITOA(itoa_buf, partId);
        string title = "Composite Part #" + (string) itoa_buf;

        // search for document with that name
        Map<string, Document *> *docInd = dataHolder->getDocumentTitleIndex();
        Map<string, Document *>::Query query;
        query.key = title;
        docInd->get(query);

        if (query.found) {
            Document *doc = query.val;
            CompositePart *cpart = doc->getCompositePart();
            Bag<BaseAssembly *> *usedIn = cpart->getUsedIn();
            BagIterator<BaseAssembly *> iter = usedIn->getIter();

            while (iter.has_next()) {
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

int sb7::LCQuery5::run() const {
    ReadLockHandle readLockHandle(lc_lock_srv.getLock());
    int ret = 0;

    Map<int, BaseAssembly *> *bassmInd = dataHolder->getBaseAssemblyIdIndex();
    MapIterator<int, BaseAssembly *> iter = bassmInd->getAll();

    while (iter.has_next()) {
        ret += checkBaseAssembly(iter.next());
    }

    return ret;
}

int sb7::LCQuery5::checkBaseAssembly(BaseAssembly *bassm) {
    int assmBuildDate = bassm->getBuildDate();
    Bag<CompositePart *> *cparts = bassm->getComponents();
    BagIterator<CompositePart *> iter = cparts->getIter();

    while (iter.has_next()) {
        CompositePart *cpart = iter.next();

        if (cpart->getBuildDate() > assmBuildDate) {
            bassm->nullOperation();
            return 1;
        }
    }

    return 0;
}

////////////
// Query6 //
////////////

int sb7::LCQuery6::run() const {
    ReadLockHandle readLockHandle(lc_lock_srv.getLock());
    return checkComplexAssembly(dataHolder->getModule()->getDesignRoot());
}

int sb7::LCQuery6::checkAssembly(Assembly *assembly) const {
    if (assembly->getType() == assembly_type_complex) {
        return checkComplexAssembly((ComplexAssembly *) assembly);
    } else {
        return checkBaseAssembly((BaseAssembly *) assembly);
    }
}

int sb7::LCQuery6::checkComplexAssembly(ComplexAssembly *assembly) const {
    int ret = 0;

    Set<Assembly *> *subAssmSet = assembly->getSubAssemblies();
    SetIterator<Assembly *> iter = subAssmSet->getIter();

    while (iter.has_next()) {
        ret += checkAssembly(iter.next());
    }

    if (ret) {
        assembly->nullOperation();
        ret++;
    }

    return ret;
}

////////////
// Query7 //
////////////

int sb7::LCQuery7::run() const {
    ReadLockHandle readLockHandle(lc_lock_srv.getLock());
    int ret = 0;

    Map<int, AtomicPart *> *apartInd = dataHolder->getAtomicPartIdIndex();
    MapIterator<int, AtomicPart *> iter = apartInd->getAll();

    while (iter.has_next()) {
        AtomicPart *apart = iter.next();
        apart->nullOperation();
        ret++;
    }

    return ret;
}
