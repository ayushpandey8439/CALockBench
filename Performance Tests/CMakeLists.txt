cmake_minimum_required(VERSION 3.22)
project(sb7_lock)

set(CMAKE_CXX_STANDARD 20)
include_directories(libraries/boost_1_81_0)


add_executable(sb7_lock src/sb7_lock.cpp src/benchmark.cpp  src/data_holder.cpp
        src/helpers.cpp src/id_pool.cpp src/parameters.cpp src/random.cpp src/operations/operations.cpp
        src/coarsePool.h src/mediumPool.h

        src/operations/locking_coarse/lock_srv_lc.cpp src/operations/locking_coarse/operation_ops_lc.cpp
        src/operations/locking_coarse/query_ops_lc.cpp src/operations/locking_coarse/short_traversal_ops_lc.cpp
        src/operations/locking_coarse/structural_modification_ops_lc.cpp src/operations/locking_coarse/traversal_ops_lc.cpp

        src/struct/assembly.cpp src/struct/atomic_part.cpp src/struct/composite_part.cpp src/struct/design_obj.cpp
        src/struct/document.cpp src/struct/manual.cpp

        src/thread/thread.cpp src/thread/thread_fun.cpp
        src/operations/locking_medium/lock_srv_lm.cpp src/operations/locking_medium/lock_srv_lm.h
        src/operations/locking_medium/operation_ops_lm.cpp src/operations/locking_medium/operation_ops_lm.h
        src/operations/locking_medium/query_ops_lm.cpp src/operations/locking_medium/query_ops_lm.h
        src/operations/locking_medium/short_traversal_ops_lm.cpp src/operations/locking_medium/short_traversal_ops_lm.h
        src/operations/locking_medium/structural_modification_ops_lm.cpp
        src/operations/locking_medium/structural_modification_ops_lm.h
        src/operations/locking_medium/traversal_ops_lm.cpp
        src/operations/locking_medium/traversal_ops_lm.h

        src/labelAssignmentTest.cpp
        src/labelAssignmentTraversal.cpp
        src/operations/locking_ca/query_ops_ca.cpp src/operations/locking_ca/query_ops_ca.h
        src/operations/locking_ca/operation_ops_ca.cpp src/operations/locking_ca/operation_ops_ca.h
        src/operations/locking_ca/traversal_ops_ca.cpp src/operations/locking_ca/traversal_ops_ca.h
        src/operations/locking_ca/structural_modification_ops_ca.cpp
        src/operations/locking_ca/structural_modification_ops_ca.h
        src/lockPool.cpp src/lockPool.h src/lscaHelpers.cpp src/lscaHelpers.h


        src/operations/locking_domLock/operation_ops_dom.cpp
        src/operations/locking_domLock/query_ops_dom.cpp src/operations/locking_domLock/short_traversal_ops_dom.cpp
        src/operations/locking_domLock/structural_modification_ops_dom.cpp src/operations/locking_domLock/traversal_ops_dom.cpp
        src/dominatorHelper.cpp src/dominatorHelper.h


        src/interval.cpp src/interval.h src/intervalAssignment.cpp src/intervalAssignment.h src/CArelabelling.cpp src/CArelabelling.h src/DomRelabelling.cpp src/DomRelabelling.h)


set_target_properties( sb7_lock PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../ )