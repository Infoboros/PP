cmake_minimum_required(VERSION 3.17)
project(pi)

set(CMAKE_CXX_STANDARD 20)

find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})


add_executable(pi main.cpp)
target_link_libraries(pi ${MPI_LIBRARIES})