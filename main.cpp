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

  vsp_solver::VSPSolver vsp_solver(500, 720);
  vsp_solver.load_data(file);
  auto solution = vsp_solver.solve();
  // for (auto &route : solution) {
  //   std::cout << vsp_solver.calculate_route_minutes(route) << std::endl;
  // }
  vsp_solver.print_solution(solution);
  // std::cout << vsp_solver.calculate_total_minutes(solution) << std::endl;
  return 0;
}