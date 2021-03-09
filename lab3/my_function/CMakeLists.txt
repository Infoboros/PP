cmake_minimum_required(VERSION 3.17)
project(my_function)

set(CMAKE_CXX_STANDARD 20)

find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})


add_executable(my_function main.cpp)
target_link_libraries(my_function ${MPI_LIBRARIES})