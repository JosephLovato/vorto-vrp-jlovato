/**
 * (Source code) Solver for the time-limited pickup-dropoff vehicle
 * routing problem
 *
 * @file vrp_solver.cpp
 * @author Joey Lovato (josephlovato.github.io)
 * @version 0.1
 * @date 2024-02-07
 *
 */

#include "vrp_solver.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

void vrp_solver::VRPSolver::load_data(std::fstream &file) {
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
}

double
vrp_solver::VRPSolver::total_cost(int number_of_drivers,
                                  double total_number_of_driven_minutes) {
  return (cost_per_driver * number_of_drivers) + total_number_of_driven_minutes;
}

double vrp_solver::VRPSolver::calculate_total_minutes(
    const std::vector<std::vector<int>> &solution) {
  double total = 0;
  for (auto &driver_loads : solution) {
    // add the total minutes of a driver's route, if there are any loads
    if (driver_loads.size() > 0) {
      // std::cout << calculate_route_minutes(driver_loads) << std::endl;
      total += calculate_route_minutes(driver_loads);
    }
  }
  return total;
}

double
vrp_solver::VRPSolver::calculate_route_minutes(const std::vector<int> &route) {
  if (route.size() == 0)
    return 0;

  double total = 0;
  // walk along the route, starting at (0,0)
  total += distance_between(ZeroPoint, loads[route[0]].pickup);
  for (int i = 0; i < int(route.size() - 1); i++) {
    // distance for this load (pickup to dropoff)
    total += distance_between(loads[route[i]].pickup, loads[route[i]].dropoff);
    // distance to next pickup
    total +=
        distance_between(loads[route[i]].dropoff, loads[route[i + 1]].pickup);
  }
  // finish with the last load, then back to (0,0)
  total += distance_between(loads[route[route.size() - 1]].pickup,
                            loads[route[route.size() - 1]].dropoff);
  total += distance_between(loads[route[route.size() - 1]].dropoff, ZeroPoint);
  return total;
}

std::vector<std::vector<int>>
vrp_solver::VRPSolver::solve_savings_algorithm(double lambda) {
  // Based on Clark & Wright Savings Algorithm (as described here:
  // https://web.mit.edu/urban_or_book/www/book/chapter6/6.4.12.html)
  // and discussions in this paper: https://sci-hub.se/10.2307/40802326

  // start with each load getting its own driver
  std::vector<std::vector<int>> driver_routes;
  std::vector<double> driver_times;
  std::unordered_map<int, int> load_to_driver_mapping;
  for (int i = 0; i < loads.size(); i++) {
    driver_routes.push_back({i});
    driver_times.push_back(calculate_route_minutes({i}));
    // std::cout << driver_times.back() << std::endl;
    load_to_driver_mapping[i] = i;
  }

  // calculate savings of each ordered pair of points
  std::vector<PointPairSavings> savings;
  for (int i = 0; i < loads.size(); i++) {
    for (int j = i + 1; j < loads.size(); j++) {
      // if we combine loads 1 and 2 in that order,
      // we have a savings of the trip from load 1 back to Zero
      // plus the distance from Zero to the pickup of load 2,
      // minus the distance we must now go from load 1 dropoff to load 2 pickup
      double positive_ij = distance_between(loads[i].dropoff, ZeroPoint) +
                           distance_between(ZeroPoint, loads[j].pickup);
      double negative_ij = distance_between(loads[i].dropoff, loads[j].pickup);
      double savings_ij = positive_ij - negative_ij;
      double algorithmic_savings_ij = positive_ij - (lambda * negative_ij);
      savings.push_back({i, j, savings_ij, algorithmic_savings_ij});

      // repeat for combining opposite order (2 then 1)
      double positive_ji = distance_between(loads[j].dropoff, ZeroPoint) +
                           distance_between(ZeroPoint, loads[i].pickup);
      double negative_ji = distance_between(loads[j].dropoff, loads[i].pickup);
      double savings_ji = positive_ji - negative_ji;
      double algorithmic_savings_ji = positive_ji - (lambda * negative_ji);
      savings.push_back({j, i, savings_ji, algorithmic_savings_ji});
    }
  }

  // arrange savings in decreasing magnitude of *algorithmic* savings
  sort(savings.begin(), savings.end(),
       [](PointPairSavings a, PointPairSavings b) {
         return a.algorithmic_savings > b.algorithmic_savings;
       });

  for (auto &s : savings) {
    // std::cout << s.i << "," << s.j << ": " << s.savings << std::endl;
    const int load_i_driver = load_to_driver_mapping[s.i];
    const int load_j_driver = load_to_driver_mapping[s.j];
    auto &i_route = driver_routes[load_i_driver];
    auto &j_route = driver_routes[load_j_driver];
    // if i and j are not in the same route,
    // check that i is at the end of its route
    // and that j is at the beginning of its route
    if (load_i_driver != load_j_driver && i_route.back() == s.i &&
        j_route.front() == s.j) {
      double new_time =
          driver_times[load_i_driver] + driver_times[load_j_driver] - s.savings;
      // add load j to i's driver
      if (new_time < max_driver_minutes) {
        // update driver map
        for (auto load : j_route) {
          load_to_driver_mapping[load] = load_i_driver;
        }
        // update time
        driver_times[load_j_driver] = 0;
        driver_times[load_i_driver] = new_time;
        // merge route of j onto back of route of i
        i_route.insert(i_route.end(), j_route.begin(), j_route.end());
        j_route.clear();
      }
    }
  }

  // scrub away all null drivers
  std::vector<std::vector<int>> solution;
  for (auto &route : driver_routes) {
    if (route.size() > 0) {
      solution.emplace_back(route);
    }
  }

  return solution;
}

void vrp_solver::VRPSolver::print_solution(
    const std::vector<std::vector<int>> &solution) {
  for (auto &driver_loads : solution) {
    if (driver_loads.size() > 0) {
      std::cout << "[";
      for (int i = 0; i < driver_loads.size() - 1; i++) {
        std::cout << driver_loads[i] + 1 // being stored as 0-index internally
                  << ",";
      }
      std::cout << driver_loads[driver_loads.size() - 1] + 1 << "]"
                << std::endl;
    }
  }
}
