//
// Created by Ayush Pandey on 16/11/2022.
//

#ifndef STMBENCH_LOCKPOOL_H
#define STMBENCH_LOCKPOOL_H
#include <vector>
#include <set>
#include <string>
#include <thread>         // std::thread
#include <mutex>
#include "data_holder.h"
#include "lscaHelpers.h"

using namespace std;
using namespace sb7;

extern mutex lockPoolLock;

struct classcomp {
    bool operator() (const DesignObj* lhs, const DesignObj* rhs) const
    {return lhs->getId()<rhs->getId();}
};

class lockPool {
public:
    set<DesignObj *, classcomp> lpool;
    set<string> lockedIds;

    bool testLockPoolConflict(list<string> testLabel){
        bool conflict = false;
        for(DesignObj *  o: lpool) {
            if(lockedIds.find(testLabel.back()) != lockedIds.end()){
                return true;
            }

            list<string> lockedLabel = o->getPathLabel();
            list<string> common = lscaHelpers::findLSCA(lockedLabel,testLabel);
            if (lockedIds.find(common.back()) == lockedIds.end() && common.back() != testLabel.back()) {
                conflict |= false;
            } else {
                conflict |= true;
                break;
            }
        }
        return conflict;
    }

    bool acquireLock(DesignObj * designObject){
        lockPoolLock.lock();
        list<string> testLabel = designObject->getPathLabel();
        bool conflict = false;
        conflict = testLockPoolConflict(testLabel);

        if(!conflict){
            lpool.insert(designObject);
            lockedIds.insert(testLabel.back());
            lockPoolLock.unlock();
            return true;
        }
        lockPoolLock.unlock();
        return false;
    }

    void releaseLock(DesignObj*  designObject){
        lockPoolLock.lock();
        lpool.erase(designObject);
        lockedIds.erase(designObject->getPathLabel().back());
        lockPoolLock.unlock();
    }

    list<string> addToLockRequest(list<string> lockRequest, list<string> label){
        if(lockRequest.empty()){
            return label;
        } else {
            return lscaHelpers::findLSCA(lockRequest, label);
        }
    }

    DesignObj * getLockObject(string objectId, sb7::DataHolder * dh){
        string typeIdentifier = objectId.substr(0,2);
        string id = objectId.substr(2);
        if(typeIdentifier == "ca"){
            sb7::ComplexAssembly * ca = dh->getComplexAssembly(stoi(id));
            return ca;
        } else if(typeIdentifier == "ba") {
            sb7::BaseAssembly * ba = dh->getBaseAssembly(stoi(id));
            return ba;
        } else if(typeIdentifier == "cp"){
            sb7::CompositePart * cp  = dh->getCompositePart(stoi(id));
            return cp;
        } else if(typeIdentifier == "ap"){
            sb7::Map<int, sb7::AtomicPart *> * index  = dh->getAtomicPartIdIndex();
            sb7::Map<int, sb7::AtomicPart *>::Query query;
            query.key = stoi(id);
            index->get(query);
            return query.val;
        } else {
            return NULL;
        }
    }
};


#endif //STMBENCH_LOCKPOOL_H
