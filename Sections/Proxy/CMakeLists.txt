cmake_minimum_required(VERSION 3.12)
project(Proxy)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proxy main.cpp PropertyProxy.h VirtualProxy.h CommunicationProxy.h)