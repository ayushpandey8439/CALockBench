//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_ID_POOL_H
#define STMBENCH_ID_POOL_H


#include <vector>

using namespace std;

namespace sb7 {

    class IdPool {
    protected:
        typedef vector<int> int_vector;

    public:
        explicit IdPool(int maxId);

        virtual ~IdPool() = default;

        int getId();

        void putId(int id);

    private:
        int_vector m_ids;
    };
}


#endif //STMBENCH_ID_POOL_H
