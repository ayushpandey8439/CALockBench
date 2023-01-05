cmake_minimum_required(VERSION 3.23)
project(Hierarchical_locks_Graph)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Hierarchical_locks_Graph
        src/BinaryTree.h
        src/errorHandler.h
        src/interval.h
        src/intervalTree.h
        src/lock.h
        src/lockPool.h
        src/main.cpp
        src/ParallelPthread.h
        src/Tree.h
        src/TreeNode.h)
