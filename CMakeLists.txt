cmake_minimum_required(VERSION 3.5)

# Ensure we can use gdb
set(CMAKE_BUILD_TYPE Debug)

project(vsp-vorto)

set(CMAKE_CXX_STANDARD 20)

include_directories(./include)

add_executable(vsp main.cpp vsp_solver.cpp vsp_solver)