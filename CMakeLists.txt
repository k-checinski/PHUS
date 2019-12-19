cmake_minimum_required(VERSION 3.15)
project(PHUS_EDAMI)

set(CMAKE_CXX_STANDARD 14)


add_executable(PHUS_EDAMI code/main.cpp
        code/Transaction.h code/Transaction.cpp
        code/Sequence.h code/Sequence.cpp code/IndexTable.h code/types.h code/IndexTable.cpp code/finding_hus.h code/finding_hus.cpp)

add_executable(PHUS_EDAMI_TEST code/Sequence.h code/Sequence.cpp
        code/Transaction.h tests/Transaction_tests.cpp
        tests/tests_main.cpp tests/catch.hpp tests/Sequence_tests.cpp code/Transaction.cpp code/types.h code/IndexTable.cpp tests/IndexTable_tests.cpp code/finding_hus.h code/finding_hus.cpp tests/finding_hus_tests.cpp)