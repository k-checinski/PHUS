cmake_minimum_required(VERSION 3.15)
project(PHUS_EDAMI)

set(CMAKE_CXX_STANDARD 14)

add_executable(PHUS_EDAMI code/main.cpp code/Sequence.h code/Sequence.cpp)
add_executable(PHUS_EDAMI_TEST code/Sequence.h code/Sequence.cpp
        tests/tests_main.cpp tests/catch.hpp tests/Sequence_tests.cpp)