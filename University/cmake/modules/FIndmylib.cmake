set(CMAKE_INSTALL_PREFIX ~/home/len/CLionProjects/mylib)
set(CMAKE_PREFIX_PATH ~/home/len/CLionProjects/mylib/mylibConfig.cmake)

find_path(mylib_INCLUDE_DIR mylib.h
        ${CMAKE_INSTALL_PREFIX}/include)

find_library(mylib_LIBRARIES mylib
        ${CMAKE_INSTALL_PREFIX}/lib)

set(mylib_FOUND TRUE)
find_package(mylib REQUIRED CONFIG)

set(CMAKE_PREFIX_PATH ~/home/len/CLionProjects/mylib/mylibConfig.cmake)


set(CMAKE_MODULE_PATH ~/home/len/CLionProjects/University/cmake/modules)
set(CMAKE_CXX_STANDARD 23)
set(FIND_MYLIB_PATHS ~/home/len/CLionProjects/mylib)

include_directories(~/home/len/CLionProjects/mylib)
find_library(University mylib)
