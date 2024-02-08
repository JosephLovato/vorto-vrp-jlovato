#include "Point.hpp"
#include <fstream>
#include <vector>

namespace vrp_solver {

const Point ZeroPoint = Point(0, 0);

class Load {
public:
  Load(double pickup_x, double pickup_y, double dropoff_x, double dropoff_y) {
    pickup = Point(pickup_x, pickup_y);
    dropoff = Point(dropoff_x, dropoff_y);
  };
  Point pickup;
  Point dropoff;
};

struct PointPairSavings {
  int i;
  int j;
  double savings;
};

class VRPSolver {
  std::vector<Load> loads;
  int cost_per_driver;
  int max_driver_minutes;

public:
  VRPSolver(int cost_per_driver, int max_driver_minutes) {
    this->cost_per_driver = cost_per_driver;
    this->max_driver_minutes = max_driver_minutes;
  }
  void load_data(std::fstream &);
  double total_cost(int number_of_drivers,
                    double total_number_of_driven_minutes);
  double calculate_total_minutes(const std::vector<std::vector<int>> &);
  double calculate_route_minutes(const std::vector<int> &);
  std::vector<std::vector<int>> solve();
  void print_solution(const std::vector<std::vector<int>> &);
};

} // namespace vrp_solver