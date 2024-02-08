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

The executable will then be available to run with `./vrp [path to input file]` in the main directory.

Alternatively, the source can be explicitly compiled with the following command in the main directory:

`g++ main.cpp vrp_solver.cpp vrp_solver.hpp Point.hpp -Wc++11-extensions -std=c++20 -O3`

## External Sources

[1] Y. Gajpal and P. Abad, “Saving-based algorithms for vehicle routing problem with simultaneous pickup and delivery,” Journal of the Operational Research Society, vol. 61, no. 10, pp. 1498–1509, Oct. 2010. doi:10.1057/jors.2009.83  (accessed via SciHub: https://sci-hub.se/10.2307/40802326)

[2] R. C. Larson and A. R. Odoni, “6.4.12 Single-Depot VRP,” Urban Operations Research, https://web.mit.edu/urban_or_book/www/book/chapter6/6.4.12.html (accessed Feb. 7, 2024).

[3] F. Liu et al., “Heuristics for vehicle routing problem: A survey and recent advances,” arXiv.org, https://arxiv.org/abs/2303.04147 (accessed Feb. 7, 2024). 