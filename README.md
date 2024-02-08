# VRP Solver

This solver specifically solves the time-limited pickup-dropoff vehicle routing problem as specified by the *Vorto Algorithmic Challenge* document.

## Dependencies

This project requires CMake and C++20 (should be available in most GCC and Clang installs)

## Building

Execute the following commands (or use your favorite IDE):

`mkdir build`

`cd build`

`cmake ..`

`cmake --build .`

The executable will then be available to run with `./vrp` in the main directory.

Alternatively, the source can be explicitly compiled with the following command in the main directory:

`g++ main.cpp vrp_solver.cpp vrp_solver.hpp Point.hpp -Wc++11-extensions -std=c++20 -O3`

## External Sources

- Gajpal, Y., Abad, P. Saving-based algorithms for vehicle routing problem with simultaneous pickup and delivery. J Oper Res Soc 61, 1498–1509 (2010). https://doi.org/10.1057/jors.2009.83 (Accessed via SciHub: https://sci-hub.se/10.2307/40802326)
- Urban Operations Online Research Textbook, 6.4.12 Single-Depot VRP (https://web.mit.edu/urban_or_book/www/book/chapter6/contents6.html)