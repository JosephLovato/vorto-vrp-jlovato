cmake_minimum_required(VERSION 3.5)

# Ensure we can use gdb
set(CMAKE_BUILD_TYPE Debug)

project(vrp-vorto)

set(CMAKE_CXX_STANDARD 20)

add_executable(vrp main.cpp vrp_solver.cpp vrp_solver)