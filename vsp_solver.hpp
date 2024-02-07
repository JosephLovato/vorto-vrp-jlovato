#include <fstream>
#include <vector>

namespace vsp_solver {

class Point {
public:
  double x;
  double y;
};

class Load {
public:
  Load(double pickup_x, double pickup_y, double dropoff_x, double dropoff_y) {
    pickup = Point();
    dropoff = Point();
    pickup.x = pickup_x;
    pickup.y = pickup_y;
    dropoff.x = dropoff_x;
    dropoff.y = dropoff_y;
  };
  Point pickup;
  Point dropoff;
};

class VSPSolver {
  std::vector<Load> loads;

public:
  void load_data(std::fstream &);
};

} // namespace vsp_solver