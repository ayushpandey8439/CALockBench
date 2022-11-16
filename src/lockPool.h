//
// Created by Ayush Pandey on 16/11/2022.
//

#ifndef STMBENCH_LOCKPOOL_H
#define STMBENCH_LOCKPOOL_H
#include <vector>
#include <set>
#include <string>
#include "data_holder.h"

using namespace std;

class lockPool {
    pthread_rwlock_t lockPoolLock;
    std::multiset<string> pool;
public:
    bool acquireLock(const string& lockLabel){
        pthread_rwlock_wrlock(&lockPoolLock);
        if(pool.find(lockLabel) == pool.end()){
            pool.insert(lockLabel);
            pthread_rwlock_unlock(&lockPoolLock);
            return true;
        } else {
            pthread_rwlock_unlock(&lockPoolLock);
            return false;
        }

    }

    void releaseLock(string lockLabel){
        pthread_rwlock_wrlock(&lockPoolLock);
        auto it = pool.find(lockLabel);
        if(it != pool.end()){
            pool.erase(it);
        }
        pthread_rwlock_unlock(&lockPoolLock);
    }

    vector<string> addToLockRequest(vector<string> lockRequest, vector<string> label){
        vector<string> common(lockRequest.size()+label.size());
        if(lockRequest.empty()){
            return label;
        } else {
            auto it = set_intersection(lockRequest.begin(), lockRequest.end(), label.begin(), label.end(), common.begin());
            common.resize(it-common.begin());
            return common;
        }
    }

    pthread_rwlock_t * getLockObject(string objectId, sb7::DataHolder * dh){
        string typeIdentifier = objectId.substr(0,2);
        string id = objectId.substr(2);
        if(typeIdentifier == "ca"){
            sb7::CompositePart * cp = dh->getCompositePart(stoi(id));
            return &(cp->NodeLock);
        } else if(typeIdentifier == "ba") {
            sb7::BaseAssembly * ba = dh->getBaseAssembly(stoi(id));
            return &(ba->NodeLock);
        } else if(typeIdentifier == "cp"){
            sb7::CompositePart * cp  = dh->getCompositePart(stoi(id));
            return &(cp->NodeLock);
        } else if(typeIdentifier == "ap"){
            sb7::Map<int, sb7::AtomicPart *> * index  = dh->getAtomicPartIdIndex();
            sb7::Map<int, sb7::AtomicPart *>::Query query;
            query.key = stoi(id);
            index->get(query);
            return &(query.val->NodeLock);
        } else {
            return NULL;
        }
    }
};


#endif //STMBENCH_LOCKPOOL_H
