cmake_minimum_required(VERSION 3.23)
project(Hierarchical_locks_Tree)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(Hierarchical_locks_Tree
        src/BinaryTree.h
        src/errorHandler.h
        src/interval.h
        src/intervalTree.h
        src/lock.h
        src/main.cpp
        src/ParallelPthread.h
        src/Tree.h
        src/TreeNode.h)
