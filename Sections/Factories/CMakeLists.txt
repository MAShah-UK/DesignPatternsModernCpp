cmake_minimum_required(VERSION 3.12)
project(Factories)

set(CMAKE_CXX_STANDARD 17)

add_executable(Factories main.cpp Point.h HotDrink.h HotDrinkFactory.h DrinkFactory.h)