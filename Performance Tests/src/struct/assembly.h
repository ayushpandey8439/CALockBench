//
// Created by Ayush Pandey on 15/11/2022.
//

#ifndef STMBENCH_ASSEMBLY_H
#define STMBENCH_ASSEMBLY_H

#include <utility>

#include "../containers.h"
#include "design_obj.h"
#include "module.h"

using namespace std;

namespace sb7 {

    class ComplexAssembly;

    // Use this small hack in order to discover what type of object
    // we are dealing with in runtime.
    // TODO might not be necessary now (?)
    enum assembly_type {
        assembly_type_complex,
        assembly_type_base
    };

    class Assembly : public DesignObj {
    public:
        Assembly(int id, string type, int bd, Module *module,
                 ComplexAssembly *superAssembly)
                : DesignObj(id, std::move(type), bd), m_superAssembly(superAssembly),
                  m_module(module) {
        }

        ~Assembly() override = default;

        ComplexAssembly *getSuperAssembly() const {
            return m_superAssembly;
        }

        Module *getModule() const {
            return m_module;
        }

        virtual enum assembly_type getType() const = 0;

    protected:
        ComplexAssembly *m_superAssembly;
        Module *m_module;
    };

    class ComplexAssembly : public Assembly {
    public:
        typedef Set<Assembly *> assembly_set;

    public:
        ComplexAssembly(int id, string type, int bd, Module *module,
                        ComplexAssembly *superAssembly)
                : Assembly(id, std::move(type), bd, module, superAssembly),
                  m_subAssemblies(new assembly_set()) {
            setLevel();
        }

        ~ComplexAssembly() override {
            delete m_subAssemblies;
        }

        bool addSubAssembly(Assembly *assembly) const;

        bool removeSubAssembly(Assembly *assembly) const;

        assembly_set *getSubAssemblies() const {
            return m_subAssemblies;
        }

        short getLevel() const {
            return m_level;
        }

        bool areChildrenBaseAssemblies() const {
            return m_level == 2;
        }

        enum assembly_type getType() const override {
            return assembly_type_complex;
        }

    private:
        void setLevel();

    protected:
        assembly_set *m_subAssemblies;
        short m_level{};
    };

    class CompositePart;

    class BaseAssembly : public Assembly {
    protected:
        typedef Set<CompositePart *> composite_part_bag;

    public:
        BaseAssembly(int id, string type, int buildDate, Module *module,
                     ComplexAssembly *superAssembly)
                : Assembly(id, std::move(type), buildDate, module, superAssembly),
                  m_components(new composite_part_bag()) {
        }

        ~BaseAssembly() override {
            delete m_components;
        }

        void addComponent(CompositePart *cpart) const;

        bool removeComponent(CompositePart *cpart) const;

        composite_part_bag *getComponents() const {
            return m_components;
        }

        enum assembly_type getType() const override {
            return assembly_type_base;
        }

    protected:
        composite_part_bag *m_components;
    };
}

#endif //STMBENCH_ASSEMBLY_H
