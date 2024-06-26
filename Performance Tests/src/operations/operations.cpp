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

    ops.push_back(new LCQuery1(dh));
    ops.push_back(new LCQuery2(dh));
//
//    ops.push_back(new LCOperation6(dh));
//    ops.push_back(new LCOperation7(dh));
    ops.push_back(new LCOperation9(dh));
    ops.push_back(new LCOperation10(dh));
//
    ops.push_back(new LCStructuralModification2(dh));
    ops.push_back(new LCStructuralModification3(dh));



}


void sb7::Operations::initOperationsLockMedium(DataHolder *dh) {


    ops.push_back(new LMQuery1(dh));
    ops.push_back(new LMQuery2(dh));
//
//    ops.push_back(new LMOperation6(dh));
//    ops.push_back(new LMOperation7(dh));
    ops.push_back(new LMOperation9(dh));
    ops.push_back(new LMOperation10(dh));
//
    ops.push_back(new LMStructuralModification2(dh));
    ops.push_back(new LMStructuralModification3(dh));



}


void sb7::Operations::initOperationsLockCA(DataHolder *dh) {

      ops.push_back(new CAQuery1(dh));
      ops.push_back(new CAQuery2(dh));
//      ops.push_back(new CAOperation6(dh));
//      ops.push_back(new CAOperation7(dh));
      ops.push_back(new CAOperation9(dh));
      ops.push_back(new CAOperation10(dh)); // Aggregation
      ops.push_back(new CAStructuralModification2(dh));
      ops.push_back(new CAStructuralModification3(dh));
<<<<<<< HEAD
=======
      /// These operations are only used for isolated structural modifications.
      /// Do not use them in a performance benchmark. Correctness is not guaranteed
//    ops.push_back(new CAStructuralModification4(dh));
//    ops.push_back(new CAStructuralModification5(dh));
//    ops.push_back(new CAStructuralModification6(dh));
//    ops.push_back(new CAStructuralModification7(dh));
//    ops.push_back(new CAStructuralModification8(dh));
>>>>>>> blockingImplementation

}

void sb7::Operations::initOperationsLockDom(DataHolder *dh) {
    ops.push_back(new DomQuery1(dh));
    ops.push_back(new DomQuery2(dh));
//    ops.push_back(new DomOperation6(dh));
//    ops.push_back(new DomOperation7(dh));
    ops.push_back(new DomOperation9(dh));
    ops.push_back(new DomOperation10(dh));
    ops.push_back(new DomStructuralModification2(dh));
    ops.push_back(new DomStructuralModification3(dh));
<<<<<<< HEAD

=======
    /// These operations are only used for isolated structural modifications.
    /// Do not use them in a performance benchmark. These are performed under a mutex to get absolute performance measure
//        ops.push_back(new DomStructuralModification4(dh));
//    ops.push_back(new DomStructuralModification5(dh));
//    ops.push_back(new DomStructuralModification6(dh));
//    ops.push_back(new DomStructuralModification7(dh));
//    ops.push_back(new DomStructuralModification8(dh));
>>>>>>> blockingImplementation
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

