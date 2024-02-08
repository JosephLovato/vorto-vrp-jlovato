#include "vrp_solver.hpp"
#include <__errc>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  // read in file and do error handling
  if (argc == 1) {
    std::cout << "Please put the path to a vrp input file "
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

  vrp_solver::VRPSolver vrp_solver(500, 720);
  vrp_solver.load_data(file);
  auto solution = vrp_solver.solve();
  // for (auto &route : solution) {
  //   std::cout << vrp_solver.calculate_route_minutes(route) << std::endl;
  // }
  vrp_solver.print_solution(solution);
  // double total_minutes = vrp_solver.calculate_total_minutes(solution);
  // std::cout << vrp_solver.total_cost(solution.size(), total_minutes)
  //           << std::endl;
  // std::vector<std::vector<int>> other = {
  //     {1, 2, 3, 4},
  // };
  // std::cout << vrp_solver.total_cost(other.size(),
  //                                    vrp_solver.calculate_total_minutes(other))
  //           << std::endl;
  // std::cout << total_minutes << std::endl;
  return 0;
}