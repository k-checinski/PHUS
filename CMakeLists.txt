cmake_minimum_required(VERSION 3.15)
project(PHUS_EDAMI)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(PHUS_EDAMI code/main.cpp
        code/Transaction.h code/Transaction.cpp
        code/Sequence.h code/Sequence.cpp code/IndexTable.h code/types.h code/IndexTable.cpp code/finding_hus.h code/finding_hus.cpp code/phus.h code/phus.cpp
        code/SequenceReader.cpp code/Sequence.h)

add_executable(PHUS_EDAMI_TEST tests/tests_main.cpp tests/catch.hpp
        code/Sequence.h code/Sequence.cpp tests/Sequence_tests.cpp
        code/Transaction.h code/Transaction.cpp tests/Transaction_tests.cpp
        code/types.h code/IndexTable.cpp tests/IndexTable_tests.cpp
        code/finding_hus.h code/finding_hus.cpp
        tests/SequenceReader_tests.cpp code/SequenceReader.h code/SequenceReader.cpp
        code/phus.cpp code/phus.h tests/phus_tests.cpp)

