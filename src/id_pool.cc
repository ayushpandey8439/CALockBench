#include "id_pool.h"
#include "sb7_exception.h"

namespace sb7 {

	IdPool::IdPool(int maxId) {
		for(int i = 0;i < maxId + 1;i++) {
			putId(i);
		}
	}

	int IdPool::getId() {
		int idSize = m_ids.size();

		if(idSize == 0) {
			throw Sb7Exception("Id pool exausted");
		}

		int ret = *(m_ids.begin());
		m_ids.erase(m_ids.begin());

		return ret;
	}

	void IdPool::putId(int id) {
		m_ids.insert(m_ids.end(), id);
	}

}
