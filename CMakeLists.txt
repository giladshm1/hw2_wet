cmake_minimum_required(VERSION 3.19)
project(hw2_wet)

set(CMAKE_CXX_STANDARD 11)

add_executable(hw2_wet main.cpp HashTable.h AVLTree.h Group.h Player.h UnionFind.h PlayersManager.cpp PlayersManager.h library2.h LinkedList.h Group.cpp)