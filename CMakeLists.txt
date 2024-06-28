cmake_minimum_required(VERSION 3.27)
project(STMBench)

set(CMAKE_CXX_STANDARD 26)
include_directories(libraries/boost_1_81_0)

add_library(STMBenchOps
        src/operations/operations.cc
        src/operations/operations.h)
add_library(STMBenchLabelling
src/labelling/DomLock/DomLockLabeling.cpp
src/labelling/DomLock/DomLockLabeling.h

src/labelling/CALock/CALockLabeling.cpp
src/labelling/CALock/CALockLabeling.h
src/labelling/CALock/CALockRelabeling.cpp
src/labelling/CALock/CALockRelabeling.h
)

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
)

add_library(STMBenchLockMedium
        src/operations/locking_medium/lock_srv_lm.cc
        src/operations/locking_medium/operation_ops_lm.cc
        src/operations/locking_medium/query_ops_lm.cc
        src/operations/locking_medium/short_traversal_ops_lm.cc
        src/operations/locking_medium/structural_modification_ops_lm.cc
        src/operations/locking_medium/traversal_ops_lm.cc)


add_library(STMBenchLockCA
        src/operations/CALock/CAPool.h
        src/operations/CALock/CAPool.cpp
        src/operations/CALock/structural_modification_ops_ca.cpp
        src/operations/CALock/traversal_ops_ca.cpp
        src/operations/CALock/operation_ops_ca.cpp
        src/operations/CALock/query_ops_ca.cpp
        src/labelling/CALock/CALockLabeling.cpp
        src/labelling/CALock/CALockLabeling.h
        src/labelling/CALock/CALockRelabeling.cpp
        src/labelling/CALock/CALockRelabeling.h
        src/display/output.cpp
        src/display/output.h
)
add_library(STMBenchLockDom
        src/operations/DomLock/DomPool.h
        src/operations/DomLock/DomPool.cpp
        src/operations/DomLock/operation_ops_dom.cpp
        src/operations/DomLock/query_ops_dom.cpp
        src/operations/DomLock/short_traversal_ops_dom.cpp
        src/operations/DomLock/structural_modification_ops_dom.cpp
        src/operations/DomLock/traversal_ops_dom.cpp
        src/operations/DomLock/dominatorHelper.h
        src/labelling/DomLock/DomLockLabeling.cpp
        src/labelling/DomLock/DomLockLabeling.h)

add_library(STMBenchLockMid
        src/operations/Mid/MidPool.h
        src/operations/Mid/MidPool.cpp
        src/operations/Mid/operation_ops_mid.cc
        src/operations/Mid/query_ops_mid.cc
        src/operations/Mid/short_traversal_ops_mid.cc
        src/operations/Mid/structural_modification_ops_mid.cc
        src/operations/Mid/traversal_ops_mid.cc
        src/operations/Mid/traversal_ops_mid.h
        src/operations/Mid/midHelper.h
        src/labelling/MID/MidLabeling.h
        src/labelling/MID/MidLabeling.cpp
)

#add_library(STMBenchLockNum
#        src/operations/NumLock/NumPool.h
#        src/operations/NumLock/NumPool.cpp
#        src/operations/NumLock/numHelper.h
#        src/operations/NumLock/operation_ops_num.cc
#        src/operations/NumLock/structural_modification_ops_num.cc
#        src/operations/NumLock/traversal_ops_num.cc
#        src/operations/NumLock/query_ops_num.cc)
#
target_link_libraries(STMBenchOps
        STMBenchLockCoarse
        STMBenchLockMedium
        STMBenchLockCA
        STMBenchLockDom
        STMBenchLockMid)

add_executable(STMBench src/sb7_lock.cc)




target_link_libraries(STMBench  STMBenchOps STMBenchLabelling STMBenchHelpers  STMBenchStruct)
set_target_properties(STMBench PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
