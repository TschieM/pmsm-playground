cmake_minimum_required(VERSION 3.14)
project(pmsm-playground VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

find_package(yaml-cpp REQUIRED)

set(BUILD_PEDANTIC_DOC "Build the project with -Wall, -Wextra and -Wpedantic.")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)