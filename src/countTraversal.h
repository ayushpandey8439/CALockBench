//
// Created by Ayush Pandey on 03/07/2024.
//

#ifndef COUNTTRAVERSAL_H
#define COUNTTRAVERSAL_H

#include "./struct/connection.h"
#include "containers.h"

namespace sb7
{
    // This class counts the number of different components in the STMBench graph.
    class countTraversal
    {
    public:
        DataHolder dh;
        map<int, int> typeCount;

        countTraversal(DataHolder& d)
        {
            dh = d;
            typeCount[0] = 0; //ComplexAssembly
            typeCount[1] = 0; //BaseAssembly
            typeCount[2] = 0; //CompositePart
            typeCount[3] = 0; //AtomicPart
        }

        void traverse(ComplexAssembly* complexAssembly, set<int>* visited)
        {
            if (visited->contains(complexAssembly->getId()))
            {
                return;
            }
            visited->insert(complexAssembly->getId());
            typeCount[0] += 1;
            Set<Assembly*>* subAssemblies = complexAssembly->getSubAssemblies();
            SetIterator<Assembly*> iter = subAssemblies->getIter();
            if (complexAssembly->areChildrenBaseAssemblies())
            {
                while (iter.has_next())
                {
                    auto* ba = (BaseAssembly*)(iter.next());
                    traverse(ba, visited);
                }
            }
            else
            {
                while (iter.has_next())
                {
                    auto* ca = (ComplexAssembly*)(iter.next());
                    traverse(ca, visited);
                }
            }
        }

        void traverse(BaseAssembly* baseAssembly, set<int>* visited)
        {
            if (visited->contains(baseAssembly->getId()))
            {
                return;
            }
            visited->insert(baseAssembly->getId());
            typeCount[1] += 1;
            BagIterator<CompositePart*> iter = baseAssembly->getComponents()->getIter();
            while (iter.has_next())
            {
                CompositePart* compositePart = iter.next();
                traverse(compositePart, visited);
            }
        }

        void traverse(CompositePart* compositePart, set<int>* visited)
        {
            if (visited->contains(compositePart->getId()))
            {
                return;
            }
            visited->insert(compositePart->getId());
            typeCount[2] += 1;
            AtomicPart* apart = compositePart->getRootPart();
            traverse(apart, visited);
        }

        void traverse(AtomicPart* apart, set<int>* visited)
        {
            if (visited->contains(apart->getId()))
            {
                return;
            }
            visited->insert(apart->getId());
            typeCount[3] += 1;
            Set<Connection*>* toConns = apart->getToConnections();
            SetIterator<Connection*> iter = toConns->getIter();

            while (iter.has_next())
            {
                Connection* connection = iter.next();
                traverse(connection->getDestination(), visited);
            }
        }
    };
}

#endif //COUNTTRAVERSAL_H
