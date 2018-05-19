cmake_minimum_required(VERSION 2.8)
project(LAB5)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

find_package(GTest REQUIRED)
include_directories(include ${GTEST_INCLUDE_DIRS})

set (ALG src/Lab5_KMP.cpp src/algorithm.cpp)
set (SHIFT src/Lab5_SHIFT.cpp src/algorithm.cpp)
set (TEST src/KMPtest.cpp src/algorithm.cpp)

if (kmp)
    add_executable(Lab5_kmp ${ALG})
endif()
if (shift)
    add_executable(Lab5_shift ${SHIFT})
endif()
if (test)
    add_executable(Lab5_test ${TEST})
    target_link_libraries(Lab5_test ${GTEST_LIBRARIES} pthread)
    enable_testing()
    add_test(Lab5_test "./Lab5_test")
endif()

