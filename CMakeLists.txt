if(NOT UNIX)
    message(FATAL_ERROR "Not a unix system.")
endif()

cmake_minimum_required(VERSION 3.16)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_compile_options(-Wall -Wextra -Wpedantic) # enable all warnings
add_compile_options(-fshort-enums) # make enums 32 bit wide

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CPP_COMPILER g++)

project(Emulator
        DESCRIPTION "A minimalistic ARM emulator"
        VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(./root)
