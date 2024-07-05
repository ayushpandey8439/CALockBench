//
// Created by Ayush Pandey on 04/07/2024.
//

#ifndef FLEXIGRANHELPER_H
#define FLEXIGRANHELPER_H
#include <thread>
#include "../../data_holder.h"
#include "../../struct/connection.h"

using namespace sb7;

class FlexigranHelper
{
public:
    static pthread_rwlock_t* getFlexiLock(DataHolder* dataHolder, int* min, int* max, int* level)
    {
        return Flexi_traverse(dataHolder->getModule()->getDesignRoot(), min, max, level);
    }


    static pthread_rwlock_t* Flexi_traverse(ComplexAssembly* cassm, int* min, int* max, int* level)
    {
        Set<Assembly*>* subAssm = cassm->getSubAssemblies();
        SetIterator<Assembly*> iter = subAssm->getIter();
        bool childrenAreBase = cassm->areChildrenBaseAssemblies();

        // think about transforming this into a nicer oo design
        while (iter.has_next())
        {
            Assembly* assm = iter.next();
            if (assm->m_pre_number <= *min && assm->m_post_number >= *max)
            {
                if (!childrenAreBase)
                {
                    return Flexi_traverse((ComplexAssembly*)assm, min, max, level);
                }
                else
                {
                    return Flexi_traverse((BaseAssembly*)assm, min, max, level);
                }
            }
        }

        //cassm -> m_post_number = dfscounter++;

        *min = cassm->m_pre_number;
        *max = cassm->m_post_number;
        *level = cassm->m_levelFromRoot;
        return &(cassm->NodeLock);
    }

    static pthread_rwlock_t* Flexi_traverse(BaseAssembly* bassm, int* min, int* max, int* level)
    {
        BagIterator<CompositePart*> iter = bassm->getComponents()->getIter();

        while (iter.has_next())
        {
            CompositePart* cpart = iter.next();

            if (cpart->m_pre_number <= *min && cpart->m_post_number >= *max)
            {
                return Flexi_traverse(cpart, min, max, level);
            }
        }
        //bassm -> m_post_number = dfscounter++;
        *min = bassm->m_pre_number;
        *max = bassm->m_post_number;
        *level = bassm->m_levelFromRoot;
        return &(bassm->NodeLock);
    }

    static pthread_rwlock_t* Flexi_traverse(CompositePart* cpart, int* min, int* max, int* level)
    {
        AtomicPart* rootPart = cpart->getRootPart();
        Set<AtomicPart*> visitedPartSet;
        return Flexi_traverse(rootPart, visitedPartSet, min, max, level);

        //cpart -> m_post_number = dfscounter++;
    }

    static pthread_rwlock_t* Flexi_traverse(AtomicPart* apart,
                                     Set<AtomicPart*>& visitedPartSet, int* min, int* max, int* level)
    {
        if (apart == NULL)
        {
            return &(apart->NodeLock);
        }
        else if (!visitedPartSet.contains(apart))
        {
            visitedPartSet.add(apart);

            // visit all connected parts
            Set<Connection*>* toConns = apart->getToConnections();
            SetIterator<Connection*> iter = toConns->getIter();

            while (iter.has_next())
            {
                Connection* conn = iter.next();
                if ((conn->getDestination())->m_pre_number <= *min && (conn->getDestination())->m_post_number >= *max)
                    return Flexi_traverse(conn->getDestination(), visitedPartSet, min, max, level);
            }
        }
        //apart -> m_post_number = dfscounter++;

        *min = apart->m_pre_number;
        *max = apart->m_post_number;
        *level = apart->m_levelFromRoot;
        return &(apart->NodeLock);
    }
};
#endif //FLEXIGRANHELPER_H
