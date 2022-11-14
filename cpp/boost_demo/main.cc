#include <boost/array.hpp>
#include <boost/math/tools/rational.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Hello Boost!" << std::endl;

  /// array
  auto poly = boost::array<double, 4>{0, 1, 2, 3};  // 默认0
  for (const auto& p : poly) {
    std::cout << "p:" << p << std::endl;
  }

  /// 多项式求解: a+b*x+c*x*x+d*x*x*x+...
  double u = 2;
  double v = boost::math::tools::evaluate_polynomial(poly, u);
  std::cout << "v: " << v << std::endl;
  return 0;
}
