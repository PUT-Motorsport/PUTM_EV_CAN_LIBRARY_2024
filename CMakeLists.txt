cmake_minimum_required(VERSION 3.0.0)
project(PUTM_EV_CAN_LIBRARY VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(PUTM_EV_CAN_LIBRARY main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
