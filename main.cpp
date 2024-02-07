#include "vsp_solver.hpp"
#include <__errc>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  // read in file and do error handling
  if (argc == 1) {
    std::cout << "Please put the path to a vsp input file "
                 "as the first and only command-line argument"
              << std::endl;
    return -1;
  }
  std::fstream file;
  file.open(argv[1]);
  if (file.fail()) {
    std::cout << "Input file not found" << std::endl;
    return -2;
  }

  vsp_solver::VSPSolver vsp_solver;
  vsp_solver.load_data(file);
  return 0;
}