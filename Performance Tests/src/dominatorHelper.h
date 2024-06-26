//
// Created by Ayush Pandey on 09/01/2023.
//

#include "data_holder.h"
#include "./struct/connection.h"

//************************************************************************************************************************

using namespace sb7;
class dominatorHelper{
public:
    static pthread_rwlock_t *getDominatorLock(DataHolder* dh, long int *min, long int *max) {
<<<<<<< HEAD
        //cout<<"Find dominator called";
=======
>>>>>>> blockingImplementation
        return Dom_traverse(dh->getModule()->getDesignRoot(), min, max);
    }


    static pthread_rwlock_t * Dom_traverse(ComplexAssembly *cassm, long int *min, long int *max) {
        Set<Assembly *> *subAssm = cassm->getSubAssemblies();
        SetIterator<Assembly *> iter = subAssm->getIter();
        bool childrenAreBase = cassm->areChildrenBaseAssemblies();

        // think about transforming this long into a nicer oo design
        while(iter.has_next()) {
            Assembly *assm = iter.next();
            if(assm -> m_pre_number <= *min && assm -> m_post_number >= *max)
            {
                if(!childrenAreBase) {
                    return Dom_traverse((ComplexAssembly *)assm,min , max);
                } else {
                    return Dom_traverse((BaseAssembly *)assm, min, max);
                }

            }
        }

        //cassm -> m_post_number = dfscounter++;

        *min = cassm -> m_pre_number;
        *max = cassm -> m_post_number;
        return &(cassm -> NodeLock);
    }

    static pthread_rwlock_t * Dom_traverse(BaseAssembly *bassm, long int *min, long int *max) {


        SetIterator<CompositePart *> iter = bassm->getComponents()->getIter();

        while(iter.has_next()) {

            CompositePart *cpart = iter.next();

            if(cpart -> m_pre_number <= *min && cpart -> m_post_number >= *max)
            {
                return Dom_traverse(cpart, min, max);
            }
        }
        //bassm -> m_post_number = dfscounter++;
        *min = bassm -> m_pre_number;
        *max = bassm -> m_post_number;
        return &(bassm -> NodeLock);
    }

    static pthread_rwlock_t * Dom_traverse(CompositePart *cpart, long int *min, long int *max) {




        AtomicPart *rootPart = cpart->getRootPart();
        Set<AtomicPart *> visitedPartSet;
        return Dom_traverse(rootPart, visitedPartSet, min, max);
    }

    static pthread_rwlock_t * Dom_traverse(AtomicPart *apart, Set<AtomicPart *> &visitedPartSet,long int *min, long int *max) {
        if(apart == NULL) {

            return &(apart -> NodeLock);
        } else if(!visitedPartSet.contains(apart)) {


            visitedPartSet.add(apart);

            // visit all connected parts
            Set<Connection *> *toConns = apart->getToConnections();
            SetIterator<Connection *> iter = toConns->getIter();

            while(iter.has_next()) {
                Connection *conn = iter.next();
                if((conn->getDestination())-> m_pre_number <= *min && (conn->getDestination()) -> m_post_number >= *max)
                    return Dom_traverse(conn->getDestination(), visitedPartSet, min, max);
            }
        }
        //apart -> m_post_number = dfscounter++;

        *min = apart -> m_pre_number;
        *max = apart -> m_post_number;
        return &(apart -> NodeLock);
    }
};
