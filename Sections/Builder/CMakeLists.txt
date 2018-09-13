cmake_minimum_required(VERSION 3.12)
project(Builder)

set(CMAKE_CXX_STANDARD 17)

add_executable(Builder main.cpp Person.cpp Person.h PersonBuilder.cpp PersonBuilder.h PersonAddressBuilder.h PersonJobBuilder.h)