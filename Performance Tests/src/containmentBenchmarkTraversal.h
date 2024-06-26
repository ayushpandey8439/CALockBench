//
// Created by Ayush Pandey on 11/11/2022.
//

#ifndef SB7_LOCK_CONTAINMENTTRAVERSAL_H
#define SB7_LOCK_CONTAINMENTTRAVERSAL_H

#include "operations/operations.h"
#include "containers.h"
#include "queue"

namespace sb7 {
    class containmentBenchmarkTraversal{
    public:
        DataHolder dh;
        map<long int, pair< int, int>> containedCount{};
        long int totalLabelSizeCALock=0;
        long int totalLabelSizeDomLock=0;
        containmentBenchmarkTraversal(DataHolder &d){
            dh=d;
        }
        void traverse(ComplexAssembly * complexAssembly){
            if(containedCount.count(complexAssembly->getLabellingId())>0){
                return;
            }
            set<int> visitedVertices{};
            int CACount=0, DomCount=0;
            tie(CACount,DomCount)=findContained(dh.getModule()->getDesignRoot(), complexAssembly->getLabellingId(), complexAssembly->m_pre_number, complexAssembly->m_post_number, visitedVertices);
            containedCount.insert({complexAssembly->getLabellingId(), {CACount, DomCount}});
            totalLabelSizeCALock+= sizeof complexAssembly->pathLabel;
            totalLabelSizeDomLock+= (sizeof complexAssembly->m_post_number) + (sizeof complexAssembly->m_pre_number);
            Set<Assembly *> *subAssm = complexAssembly->getSubAssemblies();
            SetIterator<Assembly *> iter = subAssm->getIter();
            if(complexAssembly->areChildrenBaseAssemblies()){
                while(iter.has_next()){
                    traverse((BaseAssembly*) iter.next());
                }
            }else {
                while(iter.has_next()){
                    traverse((ComplexAssembly*) iter.next());
                }
            }
        }

        void traverse(BaseAssembly * baseAssembly){
            if(containedCount.count(baseAssembly->getLabellingId())>0){
                return;
            }
            set<int> visitedVertices{};
            int CACount=0, DomCount=0;
            tie(CACount,DomCount)=findContained(dh.getModule()->getDesignRoot(), baseAssembly->getLabellingId(), baseAssembly->m_pre_number, baseAssembly->m_post_number, visitedVertices);
            containedCount.insert({baseAssembly->getLabellingId(), {CACount, DomCount}});
            totalLabelSizeCALock+= sizeof baseAssembly->pathLabel;
            totalLabelSizeDomLock+= (sizeof baseAssembly->m_post_number) + (sizeof baseAssembly->m_pre_number);
            SetIterator<CompositePart *> iter = baseAssembly->getComponents()->getIter();
            while(iter.has_next()){
                traverse((CompositePart*) iter.next());
            }
        }

        void traverse(CompositePart * compositePart){
            if(containedCount.count(compositePart->getLabellingId())>0){
                return;
            }
            set<int> visitedVertices{};
            int CACount=0, DomCount=0;
            tie(CACount,DomCount)=findContained(dh.getModule()->getDesignRoot(), compositePart->getLabellingId(), compositePart->m_pre_number, compositePart->m_post_number, visitedVertices);
            containedCount.insert({compositePart->getLabellingId(), {CACount, DomCount}});
            totalLabelSizeCALock+= sizeof compositePart->pathLabel;
            totalLabelSizeDomLock+= (sizeof compositePart->m_post_number) + (sizeof compositePart->m_pre_number);
            AtomicPart *rootPart = compositePart->getRootPart();
            traverse(rootPart);
        }

        void traverse(AtomicPart * apart){
            if(containedCount.count(apart->getLabellingId())>0){
                return;
            }
            set<int> visitedVertices{};
            int CACount=0, DomCount=0;
            tie(CACount,DomCount)=findContained(dh.getModule()->getDesignRoot(), apart->getLabellingId(), apart->m_pre_number, apart->m_post_number, visitedVertices);
            containedCount.insert({apart->getLabellingId(), {CACount, DomCount}});
            totalLabelSizeCALock+= sizeof apart->pathLabel;
            totalLabelSizeDomLock+= (sizeof apart->m_post_number) + (sizeof apart->m_pre_number);
            Set<Connection *> *toConns = apart->getToConnections();
            SetIterator<Connection *> iter = toConns->getIter();
            while(iter.has_next()) {
                traverse(iter.next()->getDestination());
            }
        }

       pair<int, int> findContained(ComplexAssembly *complexAssembly, int containerId, long int containerPre, long int containerPost, set<int>& visitedVertices){
           int caCount=0, domCount =0;
            if(visitedVertices.contains(complexAssembly->getId())){
                return {0, 0};
            }
            if(complexAssembly->criticalAncestors.contains(containerId)){
                ++caCount;
            }
            if(containerPost >= complexAssembly->m_pre_number && complexAssembly->m_post_number>= containerPre) {
                ++domCount;
            }
            visitedVertices.insert(complexAssembly->getId());
            Set<Assembly *> *subAssm = complexAssembly->getSubAssemblies();
            SetIterator<Assembly *> iter = subAssm->getIter();
            while(iter.has_next()){
                int a,b;
                if(complexAssembly->areChildrenBaseAssemblies()){
                    tie(a,b)=findContained((BaseAssembly*) iter.next(), containerId, containerPre, containerPost, visitedVertices);
                    caCount+=a;
                    domCount+=b;
                } else {
                    tie(a,b)=findContained((ComplexAssembly*) iter.next(), containerId, containerPre, containerPost, visitedVertices);
                    caCount+=a;
                    domCount+=b;
                }
            }
           return {caCount, domCount};
        }
        pair<int, int> findContained(BaseAssembly * ba, int containerId, long int containerPre, long int containerPost, set<int>& visitedVertices){
            int caCount=0, domCount =0;
            if(visitedVertices.contains(ba->getId())){
                return {0, 0};
            }
            if(ba->criticalAncestors.contains(containerId)){
                ++caCount;
            }
            if(containerPost >= ba->m_pre_number && ba->m_post_number>= containerPre) {
                ++domCount;
            }
            visitedVertices.insert(ba->getId());
            SetIterator<CompositePart *> iter = ba->getComponents()->getIter();
            while(iter.has_next()){
                int a,b;
                tie(a,b)=findContained((CompositePart*) iter.next(), containerId, containerPre, containerPost, visitedVertices);
                caCount+=a;
                domCount+=b;
            }
            return {caCount, domCount};
        }

        pair<int, int> findContained(CompositePart * cp, int containerId, long int containerPre, long int containerPost, set<int>& visitedVertices){
            int caCount=0, domCount =0;
            if(visitedVertices.contains(cp->getId())){
                return {0, 0};
            }
            if(cp->criticalAncestors.contains(containerId)){
                ++caCount;
            }
            if(containerPost >= cp->m_pre_number && cp->m_post_number>= containerPre) {
                ++domCount;
            }
            visitedVertices.insert(cp->getId());
            AtomicPart *rootPart = cp->getRootPart();
            int a,b;
            tie(a,b)=findContained(rootPart, containerId, containerPre, containerPost, visitedVertices);
            caCount+=a;
            domCount+=b;
            return {caCount, domCount};
        }

        pair<int, int> findContained(AtomicPart * apart, int containerId, long int containerPre, long int containerPost, set<int>& visitedVertices){
            int caCount=0, domCount =0;
            if(visitedVertices.contains(apart->getId())){
                return {0, 0};
            }
            if(apart->criticalAncestors.contains(containerId)){
                ++caCount;
            }
            if(containerPost >= apart->m_pre_number && apart->m_post_number>= containerPre) {
                ++domCount;
            }
            visitedVertices.insert(apart->getId());
            // visit all connected parts
            Set<Connection *> *toConns = apart->getToConnections();
            SetIterator<Connection *> iter = toConns->getIter();
            while(iter.has_next()) {
                int a,b;
                tie(a,b)=findContained((AtomicPart*) iter.next()->getDestination(), containerId, containerPre, containerPost, visitedVertices);
                caCount+=a;
                domCount+=b;
            }
            return {caCount, domCount};
        }

        //void traverse(BaseAssembly *baseAssembly, set<int> &visitedVertices){}
//        void traverse(CompositePart *component, set<int> &visitedVertices) { }
//        void traverse(AtomicPart *part,
//                              Set<int> &visitedVertices){}
    };
}


#endif //SB7_LOCK_CONTAINMENTTRAVERSAL_H
