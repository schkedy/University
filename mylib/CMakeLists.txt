cmake_minimum_required(VERSION 3.22)
project(mylib)

set(CMAKE_CXX_STANDARD 23   )
set(EXEC mylib.cpp mylib.h)
add_library(mylib SHARED ${EXEC} )

target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})