#include <math.h>

class Point {
public:
  Point() {
    x = 0;
    y = 0;
  }
  Point(double x, double y) {
    this->x = x;
    this->y = y;
  }
  double x;
  double y;
};

inline double distance_between(Point a, Point b) {
  return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
}
