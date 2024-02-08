/**
 * Solver for the time-limited pickup-dropoff vehicle
 * routing problem
 *
 * @file vrp_solver.hpp
 * @author Joey Lovato (josephlovato.github.io)
 * @version 0.1
 * @date 2024-02-07
 *
 */
#include "Point.hpp"
#include <fstream>
#include <vector>

namespace vrp_solver {

const Point ZeroPoint = Point(0, 0); // Cartesian zero

/**
 * One load with a cartesian pickup point and dropoff point
 */
class Load {
public:
  Load(double pickup_x, double pickup_y, double dropoff_x, double dropoff_y) {
    pickup = Point(pickup_x, pickup_y);
    dropoff = Point(dropoff_x, dropoff_y);
  };
  Point pickup;
  Point dropoff;
};

/**
 * Savings represented by merging loads i and j
 */
struct PointPairSavings {
  int i;
  int j;
  double savings;
  double algorithmic_savings; // lambda applied
};

/**
 * Utility and core functions for solving a time-limited pickup-dropoff vehicle
 * routing problem instance
 */
class VRPSolver {
  std::vector<Load> loads;
  int cost_per_driver;
  int max_driver_minutes;

public:
  /**
   * Construct a new VRPSolver object
   *
   * @param cost_per_driver cost of each driver (relative a to a minute-unit)
   * @param max_driver_minutes the maximum number of minutes each driver can
   * spend on their route
   */
  VRPSolver(int cost_per_driver, int max_driver_minutes) {
    this->cost_per_driver = cost_per_driver;
    this->max_driver_minutes = max_driver_minutes;
  }

  /**
   * Load VRP instance from an input file
   *
   * @param file
   */
  void load_data(std::fstream &file);

  /**
   * Calculate the total cost of a solution
   *
   * @param number_of_drivers
   * @param total_number_of_driven_minutes
   * @return double
   */
  double total_cost(int number_of_drivers,
                    double total_number_of_driven_minutes);

  /**
   * Calculate the total minutes of a solution
   *
   * @param solution list of vectors, where index i is the ith driver's ordered
   * list of load ids
   * @return double
   * @note load ids are indexed by 0
   */
  double calculate_total_minutes(const std::vector<std::vector<int>> &solution);

  /**
   * Calculate the total minutes of one route of loads for a driver
   *
   * @param route ordered list of loads ids
   * @return double
   * @note load ids are indexed by 0 internally
   */
  double calculate_route_minutes(const std::vector<int> &route);

  /**
   * Solve the VRP instance with the savings algorithm
   *
   * @param lambda coefficient to apply to the distance between the dropoff and
   * pickup of two loads in the savings calculation
   * @return std::vector<std::vector<int>>
   */
  std::vector<std::vector<int>> solve_savings_algorithm(double lambda);

  /**
   * Prints a solution to the VRP
   *
   * @note load ids are converted to 1-indexing
   */
  void print_solution(const std::vector<std::vector<int>> &);
};

} // namespace vrp_solver