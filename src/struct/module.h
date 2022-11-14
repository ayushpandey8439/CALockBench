//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_MODULE_H
#define STMBENCH_MODULE_H

#include <utility>

#include "manual.h"
#include "design_obj.h"

using namespace std;

namespace sb7 {

    class ComplexAssembly;

    class Module : public DesignObj {
    public:
        Module(int id, string type, int buildDate, Manual *manual)
                : DesignObj(id, std::move(type), buildDate), m_manual(manual) {
            m_manual->setModule(this);
        }

        // call after constructor to finish initialization
        //void connectManual() const {
        //	wr_ptr<Manual> manual(m_manual);
        //	sh_ptr<Module> sh((Module *)this);
        //	manual->setModule(sh);
        //}

        ~Module() override = default;

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
        ComplexAssembly *m_designRoot{};
    };
}
#endif //STMBENCH_MODULE_H
