cmake_minimum_required(VERSION 3.12)
project(SOLID_Design_Principles)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "C:/Program Files/boost/boost_1_68_0/")
find_package(Boost 1.68.0)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost library not found.")
endif()

add_executable(SOLID_Design_Principles main.cpp)