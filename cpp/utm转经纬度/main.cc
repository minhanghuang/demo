#include <cmath>
#include <iostream>

#include "coor_conv.hpp"

int main(int argc, char* argv[]) {
  std::cout << "C++ UTM 转经纬度" << std::endl;

  // 宁波
  double x = 388676.7544641104;
  double y = 3317647.0183873773;
  WGS84Corr t;
  UTMXYToLatLon(x, y, 51, false, t);
  double lat = RadToDeg(t.lat);
  double log = RadToDeg(t.log);

  std::cout << "纬度: " << lat << std::endl;
  std::cout << "经度: " << log << std::endl;
  return 0;
}
