//
// Created by Ayush Pandey on 03/07/2024.
//

#ifndef CONTAINMENTBENCHMARK_H
#define CONTAINMENTBENCHMARK_H

#include "containmentBenchmark.h"
#include "operations/operations.h"
#include "./struct/connection.h"
#include "containers.h"
#include "queue"

namespace sb7
{
    class containmentBenchmarkTraversal
    {
    public:
        DataHolder dh;
        map<long int, tuple<int, int, int>> containedCount{};
        long int totalLabelSizeCALock = 0;
        long int totalLabelSizeDomLock = 0;
        long int totalLabelSizeMID = 0;
        long int totalLabelSizeFlexi = 0;

        containmentBenchmarkTraversal(DataHolder& d)
        {
            dh = d;
        }

        void traverse(ComplexAssembly* complexAssembly)
        {
            if (containedCount.count(complexAssembly->getLabellingId()) > 0)
            {
                return;
            }
            set<int> visitedVertices{};
            tuple count(0, 0, 0);
            findContained(dh.getModule()->getDesignRoot(),
                          complexAssembly->getLabellingId(),
                          complexAssembly->m_pre_number,
                          complexAssembly->m_post_number,
                          complexAssembly->rlm_pre_number,
                          complexAssembly->rlm_post_number,
                          complexAssembly->m_levelFromRoot,
                          count,
                          visitedVertices);
            containedCount.insert({complexAssembly->getLabellingId(), count});
            totalLabelSizeCALock += get_list_memory_usage(complexAssembly->pathLabel);
            totalLabelSizeDomLock += (sizeof complexAssembly->m_post_number) + (sizeof complexAssembly->m_pre_number);
            totalLabelSizeMID += (sizeof complexAssembly->rlm_post_number) + (sizeof complexAssembly->rlm_pre_number) +
                sizeof(complexAssembly->m_post_number) + (sizeof complexAssembly->m_pre_number);
            totalLabelSizeFlexi += (sizeof complexAssembly->m_levelFromRoot) + sizeof(complexAssembly->m_post_number) +
                (sizeof complexAssembly->m_pre_number);
            Set<Assembly*>* subAssm = complexAssembly->getSubAssemblies();
            SetIterator<Assembly*> iter = subAssm->getIter();
            if (complexAssembly->areChildrenBaseAssemblies())
            {
                while (iter.has_next())
                {
                    traverse((BaseAssembly*)iter.next());
                }
            }
            else
            {
                while (iter.has_next())
                {
                    traverse((ComplexAssembly*)iter.next());
                }
            }
        }

        void traverse(BaseAssembly* baseAssembly)
        {
            if (containedCount.count(baseAssembly->getLabellingId()) > 0)
            {
                return;
            }
            set<int> visitedVertices{};
            tuple count(0, 0, 0);
            findContained(dh.getModule()->getDesignRoot(),
                          baseAssembly->getLabellingId(),
                          baseAssembly->m_pre_number, baseAssembly->m_post_number,
                          baseAssembly->rlm_pre_number,
                          baseAssembly->rlm_post_number,
                          baseAssembly->m_levelFromRoot,
                          count,
                          visitedVertices);
            containedCount.insert({baseAssembly->getLabellingId(), count});
            totalLabelSizeCALock += get_list_memory_usage(baseAssembly->pathLabel);
            totalLabelSizeDomLock += (sizeof baseAssembly->m_post_number) + (sizeof baseAssembly->m_pre_number);
            totalLabelSizeMID += (sizeof baseAssembly->rlm_post_number) + (sizeof baseAssembly->rlm_pre_number) + sizeof
                (baseAssembly->m_post_number) + (sizeof baseAssembly->m_pre_number);
            totalLabelSizeFlexi += (sizeof baseAssembly->m_levelFromRoot) + sizeof(baseAssembly->m_post_number) + (
                sizeof baseAssembly->m_pre_number);
            BagIterator<CompositePart*> iter = baseAssembly->getComponents()->getIter();
            while (iter.has_next())
            {
                traverse((CompositePart*)iter.next());
            }
        }

        void traverse(CompositePart* compositePart)
        {
            if (containedCount.count(compositePart->getLabellingId()) > 0)
            {
                return;
            }
            set<int> visitedVertices{};
            tuple count(0, 0, 0);
            findContained(dh.getModule()->getDesignRoot(),
                          compositePart->getLabellingId(),
                          compositePart->m_pre_number,
                          compositePart->m_post_number,
                          compositePart->rlm_pre_number,
                          compositePart->rlm_post_number,
                          compositePart->m_levelFromRoot,
                          count,
                          visitedVertices);
            containedCount.insert({compositePart->getLabellingId(), count});
            totalLabelSizeCALock += get_list_memory_usage(compositePart->pathLabel);
            totalLabelSizeDomLock += (sizeof compositePart->m_post_number) + (sizeof compositePart->m_pre_number);
            totalLabelSizeMID += (sizeof compositePart->rlm_post_number) + (sizeof compositePart->rlm_pre_number) +
                sizeof(compositePart->m_post_number) + (sizeof compositePart->m_pre_number);
            totalLabelSizeFlexi += (sizeof compositePart->m_levelFromRoot) + sizeof(compositePart->m_post_number) + (
                sizeof compositePart->m_pre_number);
            AtomicPart* rootPart = compositePart->getRootPart();
            traverse(rootPart);
        }

        void traverse(AtomicPart* apart)
        {
            if (containedCount.count(apart->getLabellingId()) > 0)
            {
                return;
            }
            set<int> visitedVertices{};
            tuple count(0, 0, 0);
            findContained(dh.getModule()->getDesignRoot(), apart->getLabellingId(),
                          apart->m_pre_number, apart->m_post_number,
                          apart->rlm_pre_number, apart->rlm_post_number, apart->m_levelFromRoot,
                          count,
                          visitedVertices);
            containedCount.insert({apart->getLabellingId(), count});
            totalLabelSizeCALock += get_list_memory_usage(apart->pathLabel);
            totalLabelSizeDomLock += (sizeof apart->m_post_number) + (sizeof apart->m_pre_number);
            totalLabelSizeMID += (sizeof apart->rlm_post_number) + (sizeof apart->rlm_pre_number) + sizeof(apart->
                m_post_number) + (sizeof apart->m_pre_number);
            totalLabelSizeFlexi += (sizeof apart->m_levelFromRoot) + sizeof(apart->m_post_number) + (sizeof apart->
                m_pre_number);
            Set<Connection*>* toConns = apart->getToConnections();
            SetIterator<Connection*> iter = toConns->getIter();
            while (iter.has_next())
            {
                traverse(iter.next()->getDestination());
            }
        }

        void findContained(ComplexAssembly* complexAssembly, int containerId, long int containerPre,
                           long int containerPost, long int containerRlmPre, long int containerRlmPost,
                           long int containerLevel,
                           tuple<int, int, int>& count,
                           set<int>& visitedVertices)
        {
            if (visitedVertices.contains(complexAssembly->getId()))
            {
                return;
            }
            if (complexAssembly->criticalAncestors.contains(containerId))
            {
                get<0>(count)++;
            }
            if (containerPost >= complexAssembly->m_pre_number && complexAssembly->m_post_number >= containerPre)
            {
                get<1>(count)++;
            }
            if ((containerPost >= complexAssembly->m_pre_number && complexAssembly->m_post_number >= containerPre) &&
                (containerRlmPost >= complexAssembly->rlm_pre_number && complexAssembly->rlm_post_number >=
                    containerRlmPre))
            {
                get<2>(count)++;
            }
            visitedVertices.insert(complexAssembly->getId());
            Set<Assembly*>* subAssm = complexAssembly->getSubAssemblies();
            SetIterator<Assembly*> iter = subAssm->getIter();
            while (iter.has_next())
            {
                if (complexAssembly->areChildrenBaseAssemblies())
                {
                    findContained((BaseAssembly*)iter.next(), containerId, containerPre, containerPost,
                                  containerRlmPre, containerRlmPost, containerLevel, count,
                                  visitedVertices);
                }
                else
                {
                    findContained((ComplexAssembly*)iter.next(), containerId, containerPre,
                                  containerPost, containerRlmPre, containerRlmPost, containerLevel, count,
                                  visitedVertices);
                }
            }
        }

        void findContained(BaseAssembly* ba, int containerId, long int containerPre,
                           long int containerPost, long int containerRlmPre, long int containerRlmPost,
                           long int containerLevel,
                           tuple<int, int, int>& count,
                           set<int>& visitedVertices)
        {
            if (visitedVertices.contains(ba->getId()))
            {
                return;
            }
            if (ba->criticalAncestors.contains(containerId))
            {
                get<0>(count)++;
            }
            if (containerPost >= ba->m_pre_number && ba->m_post_number >= containerPre)
            {
                get<1>(count)++;
            }
            if ((containerPost >= ba->m_pre_number && ba->m_post_number >= containerPre) &&
                (containerRlmPost >= ba->rlm_pre_number && ba->rlm_post_number >= containerRlmPre))
            {
                get<2>(count)++;
            }
            visitedVertices.insert(ba->getId());
            BagIterator<CompositePart*> iter = ba->getComponents()->getIter();
            while (iter.has_next())
            {
                findContained((CompositePart*)iter.next(), containerId, containerPre, containerPost,
                              containerRlmPre, containerRlmPost, containerLevel, count,
                              visitedVertices);
            }
        }

        void findContained(CompositePart* cp, int containerId, long int containerPre,
                           long int containerPost, long int containerRlmPre, long int containerRlmPost,
                           long int containerLevel,
                           tuple<int, int, int>& count,
                           set<int>& visitedVertices)
        {
            if (visitedVertices.contains(cp->getId()))
            {
                return;
            }
            if (cp->criticalAncestors.contains(containerId))
            {
                get<0>(count)++;
            }
            if (containerPost >= cp->m_pre_number && cp->m_post_number >= containerPre)
            {
                get<1>(count)++;
            }
            if ((containerPost >= cp->m_pre_number && cp->m_post_number >= containerPre) &&
                (containerRlmPost >= cp->rlm_pre_number && cp->rlm_post_number >= containerRlmPre))
            {
                get<2>(count)++;
            }
            visitedVertices.insert(cp->getId());
            AtomicPart* rootPart = cp->getRootPart();
            findContained(rootPart, containerId, containerPre, containerPost, containerRlmPre,
                          containerRlmPost, containerLevel, count, visitedVertices);
        }

        void findContained(AtomicPart* apart, int containerId, long int containerPre,
                           long int containerPost, long int containerRlmPre, long int containerRlmPost,
                           long int containerLevel,
                           tuple<int, int, int>& count,
                           set<int>& visitedVertices)
        {
            if (visitedVertices.contains(apart->getId()))
            {
                return;
            }
            if (apart->criticalAncestors.contains(containerId))
            {
                get<0>(count)++;
            }
            if (containerPost >= apart->m_pre_number && apart->m_post_number >= containerPre)
            {
                get<1>(count)++;
            }
            if ((containerPost >= apart->m_pre_number && apart->m_post_number >= containerPre) &&
                (containerRlmPost >= apart->rlm_pre_number && apart->rlm_post_number >= containerRlmPre))
            {
                get<2>(count)++;
            }
            visitedVertices.insert(apart->getId());
            // visit all connected parts
            Set<Connection*>* toConns = apart->getToConnections();
            SetIterator<Connection*> iter = toConns->getIter();
            while (iter.has_next())
            {
                findContained(iter.next()->getDestination(), containerId, containerPre,
                              containerPost, containerRlmPre, containerRlmPost, containerLevel, count,
                              visitedVertices);
            }
        }

        static size_t get_list_memory_usage(const std::list<int>& lst)
        {
            size_t list_size = sizeof(lst); // Size of the list object itself

            // Size of each node in the list
            size_t node_size = sizeof(int);

            // Total size of nodes
            size_t nodes_size = lst.size() * node_size;

            return list_size + nodes_size;
        }
    };
}

#endif //CONTAINMENTBENCHMARK_H
