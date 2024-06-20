#ifndef SB7_MODULE_H_
#define SB7_MODULE_H_

#include "manual.h"
#include "design_obj.h"

using namespace std;

namespace sb7 {

	class ComplexAssembly;

	class Module : public DesignObj {
		public:
			Module(int id, string type, int buildDate, Manual *manual)
					: DesignObj(id, type, buildDate), m_manual(manual) {
				m_manual->setModule(this);
			}

			// call after constructor to finish initialization
			//void connectManual() const {
			//	wr_ptr<Manual> manual(m_manual);
			//	sh_ptr<Module> sh((Module *)this);
			//	manual->setModule(sh);
			//}

			virtual ~Module() { }

			void setDesignRoot(ComplexAssembly *designRoot) {
				m_designRoot = designRoot;
			}

			ComplexAssembly *getDesignRoot() const {
				return m_designRoot;
			}

			Manual *getManual() const {
				return m_manual;
			}


		private:
			Manual *m_manual;
			ComplexAssembly *m_designRoot;
	};
}

#endif /*SB7_MODULE_H_*/
