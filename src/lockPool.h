//
// Created by Ayush Pandey on 16/11/2022.
//

#ifndef STMBENCH_LOCKPOOL_H
#define STMBENCH_LOCKPOOL_H
#include <vector>
#include <set>
#include <string>
#include <thread>         // std::thread
#include <shared_mutex>
#include "data_holder.h"
#include "lscaHelpers.h"

using namespace std;
using namespace sb7;

extern shared_mutex lockPoolLock;

struct classcomp {
    bool operator() (const DesignObj* lhs, const DesignObj* rhs) const
    {return lhs->getId()<rhs->getId();}
};

class lockPool {
public:
    set<DesignObj *, classcomp> lpool;

    bool testLockPoolConflict(vector<DesignObj *> testLabel) const{
        set<DesignObj *, classcomp> localLpool = lpool;
        bool conflict = false;
        if(localLpool.find(testLabel.back()) != localLpool.end()){
            return true;
        }
        for(DesignObj *  o: localLpool) {
            vector<DesignObj*> lockedLabel = o->getPathLabel();
            vector<DesignObj*> common = lscaHelpers::findLSCA(lockedLabel,testLabel);
            if (localLpool.find(common.back()) == localLpool.end() && common.back() != testLabel.back()) {
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
        vector<DesignObj*> testLabel = designObject->getPathLabel();
        bool conflict = false;
        int conflictSize = lpool.size();
        conflict = testLockPoolConflict(testLabel);

        if(!conflict){
            lpool.insert(designObject);
            lockPoolLock.unlock();
            return true;
        }
        lockPoolLock.unlock();
        return false;
    }

    void releaseLock(DesignObj*  designObject){
        lockPoolLock.lock();
        lpool.erase(designObject);
        lockPoolLock.unlock();
    }

    vector<DesignObj*> addToLockRequest(vector<DesignObj*> lockRequest, vector<DesignObj*> label){
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
