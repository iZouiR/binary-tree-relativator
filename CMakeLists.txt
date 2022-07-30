cmake_minimum_required(VERSION 3.23)
project(BinaryTreeRelativator)

set(CMAKE_CXX_STANDARD 14)

add_executable(BinaryTreeRelativator Main.cpp BinaryTree.h Commander.h FileAccessor.h)
