cmake_minimum_required(VERSION 3.25) 
set(CMAKE_CXX_STANDARD 20)
project(Main) 
add_executable(Main main.cpp HASHtable.cpp HASHtable.h)
project(Test) 
add_executable(Test tests.cpp HASHtable.cpp HASHtable.h doctest.h)