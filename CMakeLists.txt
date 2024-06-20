cmake_minimum_required(VERSION 3.27)
project(STMBench)

set(CMAKE_CXX_STANDARD 26)
include_directories(libraries/boost_1_81_0)

add_library(STMBenchOps src/operations/operations.cc)
add_library(STMBenchStruct
        src/struct/assembly.cc
        src/struct/atomic_part.cc
        src/struct/composite_part.cc
        src/struct/design_obj.cc
        src/struct/document.cc
        src/struct/manual.cc)
add_library(STMBenchHelpers
        src/random.cc
        src/helpers.cc
        src/thread/thread.cc
        src/thread/thread_fun.cc
        src/benchmark.cc
        src/parameters.cc
        src/benchmark.cc
        src/data_holder.cc
        src/id_pool.cc
        src/randomc/mersenne.cc)
add_library(STMBenchLockCoarse
        src/operations/locking_coarse/lock_srv_lc.cc
        src/operations/locking_coarse/operation_ops_lc.cc
        src/operations/locking_coarse/query_ops_lc.cc
        src/operations/locking_coarse/short_traversal_ops_lc.cc
        src/operations/locking_coarse/structural_modification_ops_lc.cc
        src/operations/locking_coarse/traversal_ops_lc.cc
        src/operations/CALock/operation_ops_ca.cpp
        src/operations/CALock/query_ops_ca.cpp)
add_library(STMBenchLockMedium
        src/operations/locking_medium/lock_srv_lm.cc
        src/operations/locking_medium/operation_ops_lm.cc
        src/operations/locking_medium/query_ops_lm.cc
        src/operations/locking_medium/short_traversal_ops_lm.cc
        src/operations/locking_medium/structural_modification_ops_lm.cc
        src/operations/locking_medium/traversal_ops_lm.cc)
add_library(STMBenchLockFine
        src/operations/locking_fine/operation_ops_lf.cc
        src/operations/locking_fine/query_ops_lf.cc
        src/operations/locking_fine/short_traversal_ops_lf.cc
        src/operations/locking_fine/structural_modification_ops_lf.cc
        src/operations/locking_fine/traversal_ops_lf.cc)

add_library(STMBenchLockingCA
        src/operations/CALock/CAPool.h
        src/operations/CALock/CAPool.cpp
        src/operations/CALock/structural_modification_ops_ca.cpp
        src/operations/CALock/traversal_ops_ca.cpp)
add_library(STMBenchLockingDom
        src/operations/DomLock/DomPool.h
        src/operations/DomLock/DomPool.cpp
        src/operations/DomLock/operation_ops_dom.cpp
        src/operations/DomLock/query_ops_dom.cpp
        src/operations/DomLock/short_traversal_ops_dom.cpp
        src/operations/DomLock/structural_modification_ops_dom.cpp
        src/operations/DomLock/traversal_ops_dom.cpp
        src/operations/DomLock/dominatorHelper.h)

add_library(STMBenchLockMid
        src/operations/Mid/MidPool.h
        src/operations/Mid/MidPool.cpp
        src/operations/Mid/operation_ops_mid.cc
        src/operations/Mid/query_ops_mid.cc
        src/operations/Mid/short_traversal_ops_mid.cc
        src/operations/Mid/structural_modification_ops_mid.cc
        src/operations/Mid/traversal_ops_mid.cc
        src/operations/Mid/traversal_ops_mid.h
        src/operations/Mid/midHelper.h)


add_executable(STMBench src/sb7_lock.cc
        src/operations/base/operation_ops.cc
        src/operations/base/query_ops.cc
        src/operations/base/short_traversal_ops.cc
        src/operations/base/structural_modification_ops.cc
        src/operations/base/traversal_ops.cc
        src/labelling/DomLock/DomLockLabeling.cpp
        src/labelling/DomLock/DomLockTraversal.h
        src/labelling/DomLock/DomLockRelabeling.cpp
        src/labelling/DomLock/DomLockRelabeling.h
        src/labelling/CALock/CALockLabeling.cpp
        src/labelling/CALock/CALockLabeling.h
        src/labelling/CALock/CALockRelabeling.cpp
        src/labelling/CALock/CALockRelabeling.h
        src/operations/CALock/operation_ops_ca.cpp
        src/display/output.cpp
        src/display/output.h
)
target_link_libraries(STMBenchOps STMBenchLockCoarse STMBenchLockMedium STMBenchLockFine STMBenchLockingCA STMBenchLockingDom STMBenchLockMid)

target_link_libraries(STMBench STMBenchHelpers STMBenchOps STMBenchStruct)

