/**
 * Main program for running the VRP solver
 *
 * @file main.cpp
 * @author Joey Lovato (josephlovato.github.io)
 * @date 2024-02-07
 *
 */

#include "vrp_solver.hpp"
#include <__errc>
#include <algorithm>
#include <cmath>
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

  vrp_solver::VRPSolver instance(500, 720);
  instance.load_data(file);

  // select minimum using range of lambda
  double min_cost = MAXFLOAT;
  std::vector<std::vector<int>> min_cost_solution;
  for (double lambda = 0.0; lambda <= 1.0; lambda += 0.05) {
    auto solution = instance.solve_savings_algorithm(lambda);
    double total_minutes = instance.calculate_total_minutes(solution);
    double cost = instance.total_cost(solution.size(), total_minutes);
    if (cost < min_cost) {
      min_cost = cost;
      min_cost_solution = solution;
    }
  }
  instance.print_solution(min_cost_solution);

  // default lambda
  // auto solution = instance.solve_savings_algorithm(1.0);
  // instance.print_solution(solution);
  return 0;
}