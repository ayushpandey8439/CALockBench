#include "operations.h"

#include "base/traversal_ops.h"
#include "base/query_ops.h"
#include "base/short_traversal_ops.h"
#include "base/operation_ops.h"
#include "base/structural_modification_ops.h"

#include "locking_coarse/traversal_ops_lc.h"
#include "locking_coarse/query_ops_lc.h"
#include "locking_coarse/short_traversal_ops_lc.h"
#include "locking_coarse/operation_ops_lc.h"
#include "locking_coarse/structural_modification_ops_lc.h"

#include "locking_medium/traversal_ops_lm.h"
#include "locking_medium/query_ops_lm.h"
#include "locking_medium/short_traversal_ops_lm.h"
#include "locking_medium/operation_ops_lm.h"
#include "locking_medium/structural_modification_ops_lm.h"

#include "locking_fine/traversal_ops_lf.h"
#include "locking_fine/query_ops_lf.h"
#include "locking_fine/short_traversal_ops_lf.h"
#include "locking_fine/operation_ops_lf.h"
#include "locking_fine/structural_modification_ops_lf.h"

#include "../parameters.h"
#include "CALock/query_ops_ca.h"
#include "CALock/operation_ops_ca.h"
#include "CALock/structural_modification_ops_ca.h"

#include "DomLock/query_ops_dom.h"
#include "DomLock/operation_ops_dom.h"
#include "DomLock/structural_modification_ops_dom.h"

#include "Mid/query_ops_mid.h"
#include "Mid/operation_ops_mid.h"
#include "Mid/structural_modification_ops_mid.h"

#include "NumLock/query_ops_num.h"
#include "NumLock/operation_ops_num.h"
#include "NumLock/structural_modification_ops_num.h"

using namespace sb7;

void sb7::Operations::initOperationTypes() {
    // initialize operation types in raising order of enum values
    optypes.emplace_back(TRAVERSAL, "TRAVERSAL");
    optypes.emplace_back(TRAVERSAL_RO, "TRAVERSAL_RO");
    optypes.emplace_back(SHORT_TRAVERSAL, "SHORT_TRAVERSAL");
    optypes.emplace_back(SHORT_TRAVERSAL_RO, "SHORT_TRAVERSAL_RO");
    optypes.emplace_back(OPERATION, "OPERATION");
    optypes.emplace_back(OPERATION_RO, "OPERATION_RO");
    optypes.emplace_back(STRUCTURAL_MODIFICATION, "STRUCTURAL_MODIFICATION");
}

void sb7::Operations::initOperations(DataHolder *dh) {
    if (parameters.getLockType() == Parameters::lock_coarse) {
        initOperationsLockCoarse(dh);
    } else if (parameters.getLockType() == Parameters::lock_medium) {
        initOperationsLockMedium(dh);
    } else if (parameters.getLockType() == Parameters::lock_ca) {
        initOperationsLockCA(dh);
    } else if (parameters.getLockType() == Parameters::lock_dom) {
        initOperationsLockDom(dh);
    } else if (parameters.getLockType() == Parameters::lock_mid) {
        initOperationsLockMid(dh);
    } else if (parameters.getLockType() == Parameters::lock_num) {
//        initOperationsLockNum(dh);
    }
}

//void sb7::Operations::initOperationsNoLock(DataHolder *dh) {
//    ops.push_back(new Traversal1(dh));
//    ops.push_back(new Traversal2a(dh));
//    ops.push_back(new Traversal2b(dh));
//    ops.push_back(new Traversal2c(dh));
//    ops.push_back(new Traversal3a(dh));
//    ops.push_back(new Traversal3b(dh));
//    ops.push_back(new Traversal3c(dh));
//    ops.push_back(new Traversal4(dh));
//    ops.push_back(new Traversal5(dh));
//    ops.push_back(new Traversal6(dh));
//    ops.push_back(new Query6(dh));
//    ops.push_back(new Query7(dh));
//
//    ops.push_back(new ShortTraversal1(dh));
//    ops.push_back(new ShortTraversal2(dh));
//    ops.push_back(new Traversal7(dh));
//    ops.push_back(new Query4(dh));
//    ops.push_back(new Query5(dh));
//    ops.push_back(new ShortTraversal6(dh));
//    ops.push_back(new ShortTraversal7(dh));
//    ops.push_back(new ShortTraversal8(dh));
//    ops.push_back(new ShortTraversal9(dh));
//    ops.push_back(new ShortTraversal10(dh));
//
//    ops.push_back(new Query1(dh));
//    ops.push_back(new Query2(dh));
//    ops.push_back(new Query3(dh));
//    ops.push_back(new Traversal8(dh));
//    ops.push_back(new Traversal9(dh));
//    ops.push_back(new Operation6(dh));
//    ops.push_back(new Operation7(dh));
//    ops.push_back(new Operation8(dh));
//    ops.push_back(new Operation9(dh));
//    ops.push_back(new Operation10(dh));
//    ops.push_back(new Operation11(dh));
//    ops.push_back(new Operation12(dh));
//    ops.push_back(new Operation13(dh));
//    ops.push_back(new Operation14(dh));
//    ops.push_back(new Operation15(dh));
//
//    ops.push_back(new StructuralModification1(dh));
//    ops.push_back(new StructuralModification2(dh));
//    ops.push_back(new StructuralModification3(dh));
//    ops.push_back(new StructuralModification4(dh));
//    ops.push_back(new StructuralModification5(dh));
//    ops.push_back(new StructuralModification6(dh));
//    ops.push_back(new StructuralModification7(dh));
//    ops.push_back(new StructuralModification8(dh));
//}

void sb7::Operations::initOperationsLockCoarse(DataHolder *dh) {

    ops.push_back(new LCQuery1(dh));
    ops.push_back(new LCQuery2(dh));
    ops.push_back(new LCOperation6(dh));
    ops.push_back(new LCOperation7(dh));
    ops.push_back(new LCOperation9(dh));
    ops.push_back(new LCOperation10(dh));
    ops.push_back(new LCStructuralModification2(dh));
    ops.push_back(new LCStructuralModification3(dh));
}

void sb7::Operations::initOperationsLockMedium(DataHolder *dh) {
    ops.push_back(new LMQuery1(dh));
    ops.push_back(new LMQuery2(dh));
    ops.push_back(new LMOperation6(dh));
    ops.push_back(new LMOperation7(dh));
    ops.push_back(new LMOperation9(dh));
    ops.push_back(new LMOperation10(dh));
    ops.push_back(new LMStructuralModification2(dh));
    ops.push_back(new LMStructuralModification3(dh));
}


void sb7::Operations::initOperationsLockDom(DataHolder *dh) {
    ops.push_back(new DomQuery1(dh));
    ops.push_back(new DomQuery2(dh));
    ops.push_back(new DomOperation6(dh));
    ops.push_back(new DomOperation7(dh));
    ops.push_back(new DomOperation9(dh));
    ops.push_back(new DomOperation10(dh));
    ops.push_back(new DomStructuralModification2(dh));
    ops.push_back(new DomStructuralModification3(dh));
}


void sb7::Operations::initOperationsLockCA(DataHolder *dh) {
    ops.push_back(new CAQuery1(dh));
    ops.push_back(new CAQuery2(dh)); // Aggregation
    ops.push_back(new CAOperation6(dh));
    ops.push_back(new CAOperation7(dh));
    ops.push_back(new CAOperation9(dh));
    ops.push_back(new CAOperation10(dh)); // Aggregation
    ops.push_back(new CAStructuralModification2(dh));
    ops.push_back(new CAStructuralModification3(dh));
}

void sb7::Operations::initOperationsLockMid(DataHolder *dh) {
    ops.push_back(new MidQuery1(dh));
    ops.push_back(new MidQuery2(dh)); // Aggregation
    ops.push_back(new MidOperation6(dh));
    ops.push_back(new MidOperation7(dh));
    ops.push_back(new MidOperation9(dh));
    ops.push_back(new MidOperation10(dh)); // Aggregation
    ops.push_back(new MidStructuralModification2(dh));
    ops.push_back(new MidStructuralModification3(dh));
}
//
//void sb7::Operations::initOperationsLockNum(DataHolder *dh) {
//    ops.push_back(new NumQuery1(dh));
//    ops.push_back(new NumQuery2(dh)); // Aggregation
//    ops.push_back(new NumOperation6(dh));
//    ops.push_back(new NumOperation7(dh));
//    ops.push_back(new NumOperation9(dh));
//    ops.push_back(new NumOperation10(dh)); // Aggregation
//    ops.push_back(new NumStructuralModification2(dh));
//    ops.push_back(new NumStructuralModification3(dh));
//}

//
//void sb7::Operations::initOperationsLockFine(DataHolder *dh) {
//    ops.push_back(new LFTraversal1(dh));
//    ops.push_back(new LFTraversal2a(dh));
//    ops.push_back(new LFTraversal2b(dh));
//    ops.push_back(new LFTraversal2c(dh));
//    ops.push_back(new LFTraversal3a(dh));
//    ops.push_back(new LFTraversal3b(dh));
//    ops.push_back(new LFTraversal3c(dh));
//    ops.push_back(new LFTraversal4(dh));
//    ops.push_back(new LFTraversal5(dh));
//    ops.push_back(new LFTraversal6(dh));
//    ops.push_back(new LFQuery6(dh));
//    ops.push_back(new LFQuery7(dh));
//
//    ops.push_back(new LFShortTraversal1(dh));
//    ops.push_back(new LFShortTraversal2(dh));
//    ops.push_back(new LFTraversal7(dh));
//    ops.push_back(new LFQuery4(dh));
//    ops.push_back(new LFQuery5(dh));
//    ops.push_back(new LFShortTraversal6(dh));
//    ops.push_back(new LFShortTraversal7(dh));
//    ops.push_back(new LFShortTraversal8(dh));
//    ops.push_back(new LFShortTraversal9(dh));
//    ops.push_back(new LFShortTraversal10(dh));
//
//    ops.push_back(new LFQuery1(dh));
//    ops.push_back(new LFQuery2(dh));
//    ops.push_back(new LFQuery3(dh));
//    ops.push_back(new LFTraversal8(dh));
//    ops.push_back(new LFTraversal9(dh));
//    ops.push_back(new LFOperation6(dh));
//    ops.push_back(new LFOperation7(dh));
//    ops.push_back(new LFOperation8(dh));
//    ops.push_back(new LFOperation9(dh));
//    ops.push_back(new LFOperation10(dh));
//    ops.push_back(new LFOperation11(dh));
//    ops.push_back(new LFOperation12(dh));
//    ops.push_back(new LFOperation13(dh));
//    ops.push_back(new LFOperation14(dh));
//    ops.push_back(new LFOperation15(dh));
//
//    ops.push_back(new LFStructuralModification1(dh));
//    ops.push_back(new LFStructuralModification2(dh));
//    ops.push_back(new LFStructuralModification3(dh));
//    ops.push_back(new LFStructuralModification4(dh));
//    ops.push_back(new LFStructuralModification5(dh));
//    ops.push_back(new LFStructuralModification6(dh));
//    ops.push_back(new LFStructuralModification7(dh));
//    ops.push_back(new LFStructuralModification8(dh));
//}
void sb7::Operations::generateCdf() {
    // count number of operations of each type
    for (std::vector<Operation *>::iterator iter = ops.begin();
         iter != ops.end(); iter++) {
        Operation *op = *iter;
        optypes[op->type].count++;
    }

    // calculate ratio of each operation type
    double shortTraversalsRatio = parameters.getShortTraversalsRatio() / 100.0;
    double operationsRatio = parameters.getOperationsRatio() / 100.0;
    double traversalsRatio = parameters.getTraversalsRatio() / 100.0;
    double structuralModificationsRatio =
            parameters.getStructuralModificationsRatio() / 100.0;

    double readOnlyOperationsRatio =
            parameters.getReadOnlyOperationsRatio() / 100.0;
    double updateOperationsRatio = 1.0 - readOnlyOperationsRatio;

    double sumRatios = shortTraversalsRatio +
                       operationsRatio +
                       traversalsRatio +
                       structuralModificationsRatio * updateOperationsRatio;

    shortTraversalsRatio /= sumRatios;
    operationsRatio /= sumRatios;
    traversalsRatio /= sumRatios;
    structuralModificationsRatio /= sumRatios;

    // calculate ratio of each operation belonging to a type
    optypes[TRAVERSAL].probability =
            traversalsRatio * updateOperationsRatio /
            optypes[TRAVERSAL].count;

    optypes[TRAVERSAL_RO].probability =
            traversalsRatio * readOnlyOperationsRatio /
            optypes[TRAVERSAL_RO].count;

    optypes[SHORT_TRAVERSAL].probability =
            shortTraversalsRatio * updateOperationsRatio /
            optypes[SHORT_TRAVERSAL].count;
    optypes[SHORT_TRAVERSAL_RO].probability =
            shortTraversalsRatio * readOnlyOperationsRatio /
            optypes[SHORT_TRAVERSAL_RO].count;

    optypes[OPERATION].probability =
            operationsRatio * updateOperationsRatio /
            optypes[OPERATION].count;
    optypes[OPERATION_RO].probability =
            operationsRatio * readOnlyOperationsRatio /
            optypes[OPERATION_RO].count;

    optypes[STRUCTURAL_MODIFICATION].probability =
            structuralModificationsRatio * updateOperationsRatio /
            optypes[STRUCTURAL_MODIFICATION].count;

    // Before calculating the CDF, find the operations that are improbable. Since their probability if zero.
    auto it = std::remove_if(ops.begin(), ops.end(),
                             [this](Operation *o) { return optypes[o->type].probability == 0; });
    ops.erase(it, ops.end());

    // calculate cdf
    double currCdf = 0;

    for (std::vector<Operation *>::iterator iter = ops.begin();
         iter != ops.end(); iter++) {
        Operation *op = *iter;
        currCdf += optypes[op->type].probability;
        cdf.push_back(currCdf);
    }
}