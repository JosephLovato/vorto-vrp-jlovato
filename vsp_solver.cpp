#include "vsp_solver.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void vsp_solver::VSPSolver::load_data(std::fstream &file) {
  std::string line = "";
  getline(file, line);
  while (!file.eof()) {
    getline(file, line);
    if (line == "")
      break;
    std::istringstream ss(line);
    std::string trash;
    std::getline(ss, trash, ' ');
    std::string pickup_string;
    std::getline(ss, pickup_string, ' ');
    std::string dropoff_string;
    std::getline(ss, dropoff_string, '\n');
    pickup_string = pickup_string.substr(1, pickup_string.size() - 2);
    dropoff_string = dropoff_string.substr(1, dropoff_string.size() - 2);
    std::istringstream pickup_ss(pickup_string);
    std::string pickup_x_string;
    std::string pickup_y_string;
    std::getline(pickup_ss, pickup_x_string, ',');
    std::getline(pickup_ss, pickup_y_string, '\n');
    std::istringstream dropoff_ss(dropoff_string);
    std::string dropoff_x_string;
    std::string dropoff_y_string;
    std::getline(dropoff_ss, dropoff_x_string, ',');
    std::getline(dropoff_ss, dropoff_y_string, '\n');
    loads.push_back(Load(std::stod(pickup_x_string), std::stod(pickup_y_string),
                         std::stod(dropoff_x_string),
                         std::stod(dropoff_y_string)));
  }
  // for (Load l : loads) {
  //   std::cout << std::setprecision(std::numeric_limits<double>::max_digits10)
  //             << l.pickup.x << l.pickup.y << " " << l.dropoff.x <<
  //             l.dropoff.y
  //             << std::endl;
  // }
}