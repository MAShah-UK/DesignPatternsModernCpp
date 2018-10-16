cmake_minimum_required(VERSION 3.12)
project(Mediator)

set(CMAKE_CXX_STANDARD 17)

add_executable(Mediator main.cpp Person.cpp Person.h Chatroom.cpp Chatroom.h SportingMatch.h)