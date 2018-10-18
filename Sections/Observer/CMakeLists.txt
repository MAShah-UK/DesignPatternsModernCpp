cmake_minimum_required(VERSION 3.12)
project(Observer)

set(CMAKE_CXX_STANDARD 17)

add_executable(Observer main.cpp Observer.h Observable.h)