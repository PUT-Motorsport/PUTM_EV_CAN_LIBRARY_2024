cmake_minimum_required(VERSION 3.23)
project(headers_gen)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(headers_gen
        csv.h
        main.cpp
        outputdocument.cpp
        outputdocument.h)
