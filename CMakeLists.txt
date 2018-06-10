cmake_minimum_required(VERSION 3.5.1)
project(genTree)

set(CMAKE_CXX_STANDARD 98)

add_executable(genTree AvlTree.h main.cpp List.h testMacros.h Hash.h)