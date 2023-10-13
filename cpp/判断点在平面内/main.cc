#include <iostream>
#include <vector>

struct Point {
  double x;
  double y;
};
using Plane = std::vector<Point>;

/*
 * 计算point是否在立方体内
 */
static bool IsPointInsidePlane(const Point& point, const Plane& plane) {
  if (plane.size() <= 2) return false;
  int j = plane.size() - 1;
  int c = 0;
  for (int i = 0; i < plane.size(); ++i) {
    if ((plane[i].y > point.y) != (plane[j].y > point.y)) {
      const double side = [&]() -> double {
        Point p1;
        p1.x = plane[i].x - point.x;
        p1.y = plane[i].y - point.y;
        Point p2;
        p2.x = plane[j].x - point.x;
        p2.y = plane[j].y - point.y;
        return p1.x * p2.y - p1.y * p2.x;
      }();
      if (plane[i].y < plane[j].y ? side > 0.0 : side < 0.0) {
        ++c;
      }
    }
    j = i;
  }
  return c & 1;
}

int main(int argc, char* argv[]) {
  std::cout << "判断点和2D平面的关系" << std::endl;
  {
    // test1
    Point point;
    point.x = 2;
    point.y = 2;
    std::cout << "point: [" << point.x << "," << point.y << "]" << std::endl;
    Plane plane;
    plane.push_back({0, 0});
    plane.push_back({3, 0});
    plane.push_back({3, 3});
    plane.push_back({0, 3});
    for (int i = 0; i < plane.size(); i++) {
      std::cout << "p" << i << ": [" << plane.at(i).x << "," << plane.at(i).y
                << "]" << std::endl;
    }
    std::cout << "ret: " << IsPointInsidePlane(point, plane) << std::endl;
  }
  {
    // test2
    Point point;
    point.x = 442924;
    point.y = 4.38037e+06;
    std::cout << "point: [" << point.x << "," << point.y << "]" << std::endl;
    Plane plane;
    plane.push_back({443799.53306361655, 4380379.201141661});
    plane.push_back({443809.42208646255, 4380379.247825142});
    plane.push_back({443809.40840252, 4380382.1470681885});
    plane.push_back({443799.51937967545, 4380382.1003845874});
    for (int i = 0; i < plane.size(); i++) {
      std::cout << "p" << i << ": [" << plane.at(i).x << "," << plane.at(i).y
                << "]" << std::endl;
    }
    std::cout << "ret: " << IsPointInsidePlane(point, plane) << std::endl;
  }

  return 0;
}
