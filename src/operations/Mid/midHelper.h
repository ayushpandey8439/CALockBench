//
// Created by Ayush Pandey on 20/06/2024.
//

#ifndef SB7_LOCK_MIDHELPER_H
#define SB7_LOCK_MIDHELPER_H

#include "pthread.h"
#include "../../data_holder.h"
#include "../../struct/connection.h"

using namespace sb7;

class MidHelper {
public:
    static pthread_rwlock_t *getMidLock(DataHolder *dh, float *min, float *max, float *rlm_min, float *rlm_max) {
        return midTraverse(dh->getModule()->getDesignRoot(), min, max, rlm_min, rlm_max);
    }


    static pthread_rwlock_t *
    midTraverse(ComplexAssembly *cassm, float *min, float *max, float *rlm_min, float *rlm_max) {


        Set<Assembly *> *subAssm = cassm->getSubAssemblies();
        SetIterator<Assembly *> iter = subAssm->getIter();
        bool childrenAreBase = cassm->areChildrenBaseAssemblies();

        // think about transforming this into a nicer oo design
        while (iter.has_next()) {
            Assembly *assm = iter.next();
            if (assm->m_pre_number <= *min && assm->m_post_number >= *max) {

                if (!childrenAreBase) {
                    return midTraverse((ComplexAssembly *) assm, min, max, rlm_min, rlm_max);
                } else {
                    return midTraverse((BaseAssembly *) assm, min, max, rlm_min, rlm_max);
                }

            }
        }

        //cassm -> m_post_number = dfscounter++;

        *min = cassm->m_pre_number;
        *max = cassm->m_post_number;
        *rlm_min = cassm->rlm_pre_number;
        *rlm_max = cassm->rlm_post_number;
        return &(cassm->NodeLock);
    }

    static pthread_rwlock_t *midTraverse(BaseAssembly *bassm, float *min, float *max, float *rlm_min, float *rlm_max) {


        BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();

        while (iter.has_next()) {

            CompositePart *cpart = iter.next();

            if (cpart->m_pre_number <= *min && cpart->m_post_number >= *max) {
                return midTraverse(cpart, min, max, rlm_min, rlm_max);
            }
        }
        //bassm -> m_post_number = dfscounter++;
        *min = bassm->m_pre_number;
        *max = bassm->m_post_number;
        *rlm_min = bassm->rlm_pre_number;
        *rlm_max = bassm->rlm_post_number;
        return &(bassm->NodeLock);
    }

    static pthread_rwlock_t *midTraverse(CompositePart *cpart, float *min, float *max, float *rlm_min, float *rlm_max) {


        AtomicPart *rootPart = cpart->getRootPart();
        Set<AtomicPart *> visitedPartSet;
        return midTraverse(rootPart, visitedPartSet, min, max, rlm_min, rlm_max);

        //cpart -> m_post_number = dfscounter++;
    }

    static pthread_rwlock_t *midTraverse(AtomicPart *apart,
                                         Set<AtomicPart *> &visitedPartSet, float *min, float *max, float *rlm_min,
                                         float *rlm_max) {

        if (apart == NULL) {

            return &(apart->NodeLock);
        } else if (!visitedPartSet.contains(apart)) {


            visitedPartSet.add(apart);

            // visit all connected parts
            Set<Connection *> *toConns = apart->getToConnections();
            SetIterator<Connection *> iter = toConns->getIter();

            while (iter.has_next()) {
                Connection *conn = iter.next();
                if ((conn->getDestination())->m_pre_number <= *min && (conn->getDestination())->m_post_number >= *max)
                    return midTraverse(conn->getDestination(), visitedPartSet, min, max, rlm_min, rlm_max);
            }
        }
        //apart -> m_post_number = dfscounter++;

        *min = apart->m_pre_number;
        *max = apart->m_post_number;
        *rlm_min = apart->rlm_pre_number;
        *rlm_max = apart->rlm_post_number;
        return &(apart->NodeLock);
    }
};

#endif //SB7_LOCK_MIDHELPER_H
