cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Release)

project(vrp-vorto)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-pedantic -Wall -Wc++11-extensions -O3)

add_executable(vrp main.cpp vrp_solver.cpp vrp_solver)