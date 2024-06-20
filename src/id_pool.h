#ifndef SB7_ID_POOL_H_
#define SB7_ID_POOL_H_

#include <vector>

using namespace std;

namespace sb7 {

	class IdPool {
		protected:
			typedef vector<int> int_vector;

		public:
			IdPool(int maxId);

			virtual ~IdPool() { }

			int getId();

			void putId(int id);

		private:
			int_vector m_ids;
	};
}

#endif /*SB7_ID_POOL_H_*/
