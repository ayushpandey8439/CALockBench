//
// Created by Ayush Pandey on 09/01/2023.
//


//************************************************************************************************************************

#include <csignal>
#include "../../data_holder.h"
#include "../../struct/connection.h"
#include "../../data_holder.h"
using namespace sb7;


bool comp(numInterval *i, numInterval *j) { return (i->pre < j->pre); }

bool Vcomp(pair<int, int> a, pair<int, int> b) { return (a.second < b.second); }

class NumHelper {
public:
    static pthread_rwlock_t *getNumLock(DataHolder *dh, float *min, float *max) {
        return Num_traverse(dh->getModule()->getDesignRoot(), min, max);
    }


    static pthread_rwlock_t *Num_traverse(ComplexAssembly *cassm, float *min, float *max) {


        Set<Assembly *> *subAssm = cassm->getSubAssemblies();
        SetIterator<Assembly *> iter = subAssm->getIter();
        bool childrenAreBase = cassm->areChildrenBaseAssemblies();

        // think about transforming this long into a nicer oo design
        while (iter.has_next()) {
            Assembly *assm = iter.next();
            if (assm->m_pre_number <= *min && assm->m_post_number >= *max) {

                if (!childrenAreBase) {
                    return Num_traverse((ComplexAssembly *) assm, min, max);
                } else {
                    return Num_traverse((BaseAssembly *) assm, min, max);
                }

            }
        }

        //cassm -> m_post_number = dfscounter++;

        *min = cassm->m_pre_number;
        *max = cassm->m_post_number;
        return &(cassm->NodeLock);
    }

    static pthread_rwlock_t *Num_traverse(BaseAssembly *bassm, float *min, float *max) {


        BagIterator<CompositePart *> iter = bassm->getComponents()->getIter();

        while (iter.has_next()) {

            CompositePart *cpart = iter.next();

            if (cpart->m_pre_number <= *min && cpart->m_post_number >= *max) {
                return Num_traverse(cpart, min, max);
            }
        }
        //bassm -> m_post_number = dfscounter++;
        *min = bassm->m_pre_number;
        *max = bassm->m_post_number;
        return &(bassm->NodeLock);
    }

    static pthread_rwlock_t *Num_traverse(CompositePart *cpart, float *min, float *max) {


        AtomicPart *rootPart = cpart->getRootPart();
        Set<AtomicPart *> visitedPartSet;
        return Num_traverse(rootPart, visitedPartSet, min, max);

        //cpart -> m_post_number = dfscounter++;
    }

    static pthread_rwlock_t *Num_traverse(AtomicPart *apart,
                                          Set<AtomicPart *> &visitedPartSet, float *min, float *max) {
        float ret;

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
                    return Num_traverse(conn->getDestination(), visitedPartSet, min, max);
            }
        }
        //apart -> m_post_number = dfscounter++;

        *min = apart->m_pre_number;
        *max = apart->m_post_number;
        return &(apart->NodeLock);
    }


    //Generate locking options
    vector<numInterval *> GetOptimalLockingOptions(vector<numInterval *> &IntervalArray, DataHolder * dataHolder) {
        int LocalNoOfRequestedNode = IntervalArray.size();
        int accessType = 1;
        sort(IntervalArray.begin(), IntervalArray.end(), comp);

        //Merge overlapping intervals inline function
        //***************************************************
        int top = 0;
        for (int i = 0; i < IntervalArray.size(); i++) {
            if (IntervalArray[top]->pre <= IntervalArray[i]->post &&
                IntervalArray[top]->post >= IntervalArray[i]->pre) {
                IntervalArray[top]->pre = min(IntervalArray[top]->pre, IntervalArray[i]->pre);
                IntervalArray[top]->post = max(IntervalArray[top]->post, IntervalArray[i]->post);

                IntervalArray[top]->mode = max(IntervalArray[top]->mode, IntervalArray[i]->mode);

            } else
                IntervalArray[++top] = IntervalArray[i];

        }

        IntervalArray.resize(top + 1);
        LocalNoOfRequestedNode = min(top + 1, LocalNoOfRequestedNode);
        //***************************************************

        //Maintain the information of empty holes in the sorted list of requested nodes in a vector "Holes"
        vector<pair<int, int> > Holes(LocalNoOfRequestedNode - 1);

        //Maintains the total number of nodes locked by an option
        vector<int> K(LocalNoOfRequestedNode);
        K[0] = IntervalArray[LocalNoOfRequestedNode - 1]->post - IntervalArray[0]->pre + 1;


        for (int i = 0; i < IntervalArray.size() - 1; i++) {
            Holes[i] = make_pair((IntervalArray[i + 1]->pre - IntervalArray[i]->post), i);

        }

        sort(Holes.rbegin(), Holes.rend());
        //fill vector K with all entries of locked nodes by an option
        for (int i = 1; i < LocalNoOfRequestedNode; i++) {
            K[i] = K[i - 1] - Holes[i - 1].first + 1;
        }

        //Call to the function whih chooses the best locking option
        int bestOption = PinPoint(K,dataHolder);

        sort(Holes.begin(), Holes.begin() + bestOption, Vcomp);

        int L, R, LockMode1, LockMode2;
        vector<numInterval *> Pinned(bestOption + 1);

        L = IntervalArray[0]->pre;
        LockMode1 = IntervalArray[0]->mode;
        for (int i = 1; i <= bestOption; i++) {
            R = IntervalArray[Holes[i - 1].second]->post;
            LockMode2 = IntervalArray[Holes[i - 1].second]->mode;

            numInterval *iv1 = new numInterval(L, R, max(LockMode1, LockMode2));
            Pinned[i - 1] = iv1;
            L = IntervalArray[Holes[i - 1].second + 1]->pre;
        }
        R = IntervalArray[LocalNoOfRequestedNode - 1]->post;
        LockMode2 = IntervalArray[LocalNoOfRequestedNode - 1]->mode;
        numInterval *iv1 = new numInterval(L, R, max(LockMode1, LockMode2));
        Pinned[bestOption] = iv1;


        return Pinned;


    }

    //Pinpoint the best locking option
    int PinPoint(vector<int>&K, DataHolder * dataHolder)
    {
        // n is the number of lead nodes in the hierarchy. For STMBench, it is the number cof composite parts.
        // Each composite part contains a graph of atomic parts.
        auto composites = dataHolder->getCompositePartIdIndex()->getAll();
        int n = 0;
        while(composites.has_next()){
            n++;
            composites.next();
        }
        int k;
        int K_Size = K.size();
        vector<double>Batches(K_Size);
        int minIndex;
        double minExecTime = 10000.0;
        for(int i_k = 0; i_k<K_Size;i_k++)
        {
            k = K[i_k];

            double perThreadTime = ((double)i_k*0.00004201) + 0.000551;
            double fr=1;
            int i,j;
            /*		for(i = n-k,j=n; i>n-k-k,j>n-k; i--,j--)
                    {
            //nu[c++] = i;
            fr = fr * ((double)i/j);

            }
            Batches[i_k] = ceil(15 * (double)(1-fr));
            */

            Batches[i_k] = 1 + ceil(15 * ((double)k/(4*n)));
            double newExec = Batches[i_k]*perThreadTime;
            if(minExecTime > newExec)
            {
                minExecTime = newExec;
                minIndex = i_k;
            }
        }

        return minIndex;

    }
};
