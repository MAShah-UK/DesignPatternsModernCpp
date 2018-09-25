cmake_minimum_required(VERSION 3.12)
project(Decorator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Decorator main.cpp Shapes.h DynamicDecorator.h StaticDecorator.h FunctionalDecorator.h)