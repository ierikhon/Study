cmake_minimum_required(VERSION 2.8)
project(LAB5)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

find_package(GTest REQUIRED)
include_directories(include ${GTEST_INCLUDE_DIRS})

set (BASE src/Lab6_AC.cpp src/AC_base.cpp)
set (JOKER src/Lab6_JO.cpp src/AC_joker.cpp)


if (ac)
    add_executable(Lab5_base ${BASE})
endif()
if (jo)
    add_executable(Lab5_joker ${JOKER})
endif()
