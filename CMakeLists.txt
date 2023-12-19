if(NOT UNIX)
    message(FATAL_ERROR "Not a unix system.")
endif()

cmake_minimum_required(VERSION 3.16)

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CPP_COMPILER g++)

project(Emulator
        DESCRIPTION "A minimalistic ARM emulator"
        VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)


add_subdirectory(./src)
