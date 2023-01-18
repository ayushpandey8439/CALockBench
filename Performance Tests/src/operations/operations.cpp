//
// Created by Ayush Pandey on 15/11/2022.
//

#include "operations.h"
#include "../parameters.h"
#include "../struct/connection.h"
#include <algorithm>


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

#include "locking_ca/traversal_ops_ca.h"
#include "locking_ca/query_ops_ca.h"
#include "locking_ca/operation_ops_ca.h"
#include "locking_ca/structural_modification_ops_ca.h"


#include "locking_domLock//traversal_ops_dom.h"
#include "locking_domLock/query_ops_dom.h"
#include "locking_domLock/short_traversal_ops_dom.h"
#include "locking_domLock/operation_ops_dom.h"
#include "locking_domLock/structural_modification_ops_dom.h"


using namespace sb7;


void sb7::Operations::initOperationTypes() {
    // initialize operation types in raising order of enum values
    optypes.emplace_back(TRAVERSAL, "TRAVERSAL");
    optypes.emplace_back(TRAVERSAL_RO, "TRAVERSAL_RO");
    optypes.emplace_back(SHORT_TRAVERSAL, "SHORT_TRAVERSAL");
    optypes.emplace_back(SHORT_TRAVERSAL_RO, "SHORT_TRAVERSAL_RO");
    optypes.emplace_back(OPERATION, "OPERATION");
    optypes.emplace_back(OPERATION_RO, "OPERATION_RO");
    optypes.emplace_back(STRUCTURAL_MODIFICATION,
                                    "STRUCTURAL_MODIFICATION");
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
    }
}

void sb7::Operations::initOperationsLockCoarse(DataHolder *dh) {
    //These have been commented out because the benchmark results in the paper ignore long traversals
    // T1-T6 and Q6, Q7. These are not used in any of the reported results.
    //ops.push_back(new LCTraversal1(dh));
    //ops.push_back(new LCTraversal2a(dh));
    //ops.push_back(new LCTraversal2b(dh));
    //ops.push_back(new LCTraversal2c(dh));
    //ops.push_back(new LCTraversal3a(dh));
    //ops.push_back(new LCTraversal3b(dh));
    //ops.push_back(new LCTraversal3c(dh));
    //ops.push_back(new LCTraversal4(dh));
    //ops.push_back(new LCTraversal5(dh));
    //ops.push_back(new LCTraversal6(dh));
    //ops.push_back(new LCQuery6(dh));
    //ops.push_back(new LCQuery7(dh));

    //ops.push_back(new LCShortTraversal1(dh));
    //ops.push_back(new LCShortTraversal2(dh));
    //ops.push_back(new LCTraversal7(dh));
    //ops.push_back(new LCQuery4(dh));
    //ops.push_back(new LCQuery5(dh));
    //ops.push_back(new LCShortTraversal6(dh));
    //ops.push_back(new LCShortTraversal7(dh));
    //ops.push_back(new LCShortTraversal8(dh));
    //ops.push_back(new LCShortTraversal9(dh));
    //ops.push_back(new LCShortTraversal10(dh));

    ops.push_back(new LCQuery1(dh));
    ops.push_back(new LCQuery2(dh));
    //ops.push_back(new LCQuery3(dh)); Not implemented
    //ops.push_back(new LCTraversal8(dh)); Trivial and does not need locks.
//    ops.push_back(new LCTraversal9(dh)); Trivial and does not need locks.
    ops.push_back(new LCOperation6(dh));
    ops.push_back(new LCOperation7(dh));
    //ops.push_back(new LCOperation8(dh));
    ops.push_back(new LCOperation9(dh));
    ops.push_back(new LCOperation10(dh));
//    ops.push_back(new LCOperation11(dh)); Traversal operation
//    ops.push_back(new LCOperation12(dh));
//    ops.push_back(new LCOperation13(dh));
//    ops.push_back(new LCOperation14(dh));
//    ops.push_back(new LCOperation15(dh)); Index update
//
//    ops.push_back(new LCStructuralModification1(dh)); Node creation
    ops.push_back(new LCStructuralModification2(dh));
    ops.push_back(new LCStructuralModification3(dh));
    //    ops.push_back(new LCStructuralModification4(dh));
//    ops.push_back(new LCStructuralModification5(dh));
//    ops.push_back(new LCStructuralModification6(dh));
//    ops.push_back(new LCStructuralModification7(dh));
//    ops.push_back(new LCStructuralModification8(dh));


}


void sb7::Operations::initOperationsLockMedium(DataHolder *dh) {
//ops.push_back(new LMTraversal1(dh));
    //ops.push_back(new LMTraversal2a(dh));
    //ops.push_back(new LMTraversal2b(dh));
    //ops.push_back(new LMTraversal2c(dh));
    //ops.push_back(new LMTraversal3a(dh));
    //ops.push_back(new LMTraversal3b(dh));
    //ops.push_back(new LMTraversal3c(dh));
    //ops.push_back(new LMTraversal4(dh));
    //ops.push_back(new LMTraversal5(dh));
    //ops.push_back(new LMTraversal6(dh));
    //ops.push_back(new LMQuery6(dh));
    //ops.push_back(new LMQuery7(dh));

    //ops.push_back(new LMShortTraversal1(dh));
    //ops.push_back(new LMShortTraversal2(dh));
    //ops.push_back(new LMTraversal7(dh));
    //ops.push_back(new LMQuery4(dh));
    //ops.push_back(new LMQuery5(dh));
    //ops.push_back(new LMShortTraversal6(dh));
    //ops.push_back(new LMShortTraversal7(dh));
    //ops.push_back(new LMShortTraversal8(dh));
    //ops.push_back(new LMShortTraversal9(dh));
    //ops.push_back(new LMShortTraversal10(dh));

    ops.push_back(new LMQuery1(dh));
    ops.push_back(new LMQuery2(dh));
    //ops.push_back(new LMQuery3(dh)); Not implemented
    //ops.push_back(new LMTraversal8(dh)); Trivial and does not need locks.
//    ops.push_back(new LMTraversal9(dh)); Trivial and does not need locks.
    ops.push_back(new LMOperation6(dh));
    ops.push_back(new LMOperation7(dh));
    //ops.push_back(new LMOperation8(dh));
    ops.push_back(new LMOperation9(dh));
    ops.push_back(new LMOperation10(dh));
//    ops.push_back(new LMOperation11(dh)); Traversal operation
//    ops.push_back(new LMOperation12(dh));
//    ops.push_back(new LMOperation13(dh));
//    ops.push_back(new LMOperation14(dh));
//    ops.push_back(new LMOperation15(dh)); Index update
//
//    ops.push_back(new LMStructuralModification1(dh)); Node creation
    ops.push_back(new LMStructuralModification2(dh));
    ops.push_back(new LMStructuralModification3(dh));
    //ops.push_back(new LMStructuralModification4(dh));
//    ops.push_back(new LMStructuralModification5(dh));
//    ops.push_back(new LMStructuralModification6(dh));
//    ops.push_back(new LMStructuralModification7(dh));
//    ops.push_back(new LMStructuralModification8(dh));


}


void sb7::Operations::initOperationsLockCA(DataHolder *dh) {
//ops.push_back(new CATraversal1(dh));
    //ops.push_back(new CATraversal2a(dh));
    //ops.push_back(new CATraversal2b(dh));
    //ops.push_back(new CATraversal2c(dh));
    //ops.push_back(new CATraversal3a(dh));
    //ops.push_back(new CATraversal3b(dh));
    //ops.push_back(new CATraversal3c(dh));
    //ops.push_back(new CATraversal4(dh));
    //ops.push_back(new CATraversal5(dh));
    //ops.push_back(new CATraversal6(dh));
    //ops.push_back(new CAQuery6(dh));
    //ops.push_back(new CAQuery7(dh));

    //ops.push_back(new CAShortTraversal1(dh));
    //ops.push_back(new CAShortTraversal2(dh));
    //ops.push_back(new CATraversal7(dh));
    //ops.push_back(new CAQuery4(dh));
    //ops.push_back(new CAQuery5(dh));
    //ops.push_back(new CAShortTraversal6(dh));
    //ops.push_back(new CAShortTraversal7(dh));
    //ops.push_back(new CAShortTraversal8(dh));
    //ops.push_back(new CAShortTraversal9(dh));
    //ops.push_back(new CAShortTraversal10(dh));

      ops.push_back(new CAQuery1(dh));
      ops.push_back(new CAQuery2(dh)); // Aggregation
    //ops.push_back(new CAQuery3(dh)); Not implemented
    //ops.push_back(new CATraversal8(dh)); Trivial and does not need locks.
//    ops.push_back(new CATraversal9(dh)); Trivial and does not need locks.
      ops.push_back(new CAOperation6(dh));
      ops.push_back(new CAOperation7(dh));
//      //ops.push_back(new CAOperation8(dh));//aggregation same as query 2
      ops.push_back(new CAOperation9(dh));
      ops.push_back(new CAOperation10(dh)); // Aggregation
//    ops.push_back(new CAOperation11(dh)); Traversal operation
//    ops.push_back(new CAOperation12(dh));
//    ops.push_back(new CAOperation13(dh));
//    ops.push_back(new CAOperation14(dh));
//    ops.push_back(new CAOperation15(dh)); Index update
//
//    ops.push_back(new CAStructuralModification1(dh)); Node creation
//      ops.push_back(new CAStructuralModification2(dh));
      ops.push_back(new CAStructuralModification3(dh));
      //      ops.push_back(new CAStructuralModification4(dh));
//      ops.push_back(new CAStructuralModification5(dh));
//    ops.push_back(new CAStructuralModification6(dh));
//    ops.push_back(new CAStructuralModification7(dh));
//    ops.push_back(new CAStructuralModification8(dh));

}

void sb7::Operations::initOperationsLockDom(DataHolder *dh) {
//ops.push_back(new DomTraversal1(dh));
    //ops.push_back(new DomTraversal2a(dh));
    //ops.push_back(new DomTraversal2b(dh));
    //ops.push_back(new DomTraversal2c(dh));
    //ops.push_back(new DomTraversal3a(dh));
    //ops.push_back(new DomTraversal3b(dh));
    //ops.push_back(new DomTraversal3c(dh));
    //ops.push_back(new DomTraversal4(dh));
    //ops.push_back(new DomTraversal5(dh));
    //ops.push_back(new DomTraversal6(dh));
    //ops.push_back(new DomQuery6(dh));
    //ops.push_back(new DomQuery7(dh));

    //ops.push_back(new DomShortTraversal1(dh));
    //ops.push_back(new DomShortTraversal2(dh));
    //ops.push_back(new DomTraversal7(dh));
    //ops.push_back(new DomQuery4(dh));
    //ops.push_back(new DomQuery5(dh));
    //ops.push_back(new DomShortTraversal6(dh));
    //ops.push_back(new DomShortTraversal7(dh));
    //ops.push_back(new DomShortTraversal8(dh));
    //ops.push_back(new DomShortTraversal9(dh));
    //ops.push_back(new DomShortTraversal10(dh));

    ops.push_back(new DomQuery1(dh));
    ops.push_back(new DomQuery2(dh));
    //ops.push_back(new DomQuery3(dh)); Not implemented
    //ops.push_back(new DomTraversal8(dh)); Trivial and does not need locks.
//    ops.push_back(new DomTraversal9(dh)); Trivial and does not need locks.
    ops.push_back(new DomOperation6(dh));
    ops.push_back(new DomOperation7(dh));
//    //ops.push_back(new DomOperation8(dh));
     ops.push_back(new DomOperation9(dh));
    ops.push_back(new DomOperation10(dh));
//    ops.push_back(new DomOperation11(dh)); Traversal operation
//    ops.push_back(new DomOperation12(dh));
//    ops.push_back(new DomOperation13(dh));
//    ops.push_back(new DomOperation14(dh));
//    ops.push_back(new DomOperation15(dh)); Index update
//
//    ops.push_back(new DomStructuralModification1(dh)); Node creation
    ops.push_back(new DomStructuralModification2(dh));
    ops.push_back(new DomStructuralModification3(dh));
    //    ops.push_back(new DomStructuralModification4(dh));
//    ops.push_back(new DomStructuralModification5(dh));
//    ops.push_back(new DomStructuralModification6(dh));
//    ops.push_back(new DomStructuralModification7(dh));
//    ops.push_back(new DomStructuralModification8(dh));

}


void sb7::Operations::generateCdf() {
    // count number of operations of each type
    for(std::vector<Operation *>::iterator iter = ops.begin();
        iter != ops.end();iter++) {
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

    // Before calculating the CDF, find the operations that are improbable.
    auto it = std::remove_if(ops.begin(), ops.end(),[this](Operation * o){return optypes[o->type].probability==0;});
    ops.erase(it,ops.end());

    // calculate cdf
    double currCdf = 0;

    for(auto iter = ops.begin(); iter != ops.end();iter++) {
        Operation *op = *iter;
        currCdf += optypes[op->type].probability;
        cdf.push_back(currCdf);
    }
}

