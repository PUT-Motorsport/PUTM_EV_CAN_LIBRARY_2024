cmake_minimum_required(VERSION 3.0.0)
project(PUTM_EV_CAN_LIBRARY VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_definitions(UNIT_TESTS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS "-O3")

set(CMAKE_EXPORT_COMPILE_COMMANDS)

include_directories("./lib/")

add_executable(PUTM_EV_CAN_LIBRARY main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
