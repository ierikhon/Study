cmake_minimum_required(VERSION 2.8)
project(LAB5)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

find_package(GTest REQUIRED)
include_directories(include ${GTEST_INCLUDE_DIRS})

set (BASE src/Lab6_AC.cpp src/algorithm.cpp)
set (JOKER src/Lab6_JO.cpp src/algorithm.cpp)
set (TEST src/ACtest.cpp src/algorithm.cpp)
set (JTEST src/JOtest.cpp src/algorithm.cpp)

if (ac)
    add_executable(Lab6_base ${BASE})
endif()

if (jo)
    add_executable(Lab6_joker ${JOKER})
endif()

if (test)
    add_executable(Lab6_test ${TEST})
    target_link_libraries(Lab6_test ${GTEST_LIBRARIES} pthread)
    enable_testing()
    add_test(Lab5_test "./Lab6_test")
endif()

if (jtest)
    add_executable(Lab6_jtest ${JTEST})
    target_link_libraries(Lab6_jtest ${GTEST_LIBRARIES} pthread)
    enable_testing()
    add_test(Lab5_test "./Lab6_jtest")
endif()

