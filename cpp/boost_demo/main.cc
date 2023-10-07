#include <iostream>

#include <boost/array.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/version.hpp>

int main(int argc, char* argv[]) {
  std::cout << "Hello Boost! Version:" << BOOST_LIB_VERSION << std::endl;

  {
    std::cout << " ------------  多项式  ------------ " << std::endl;
    /// 多项式求解: a+b*x+c*x*x+d*x*x*x+...
    auto poly = boost::array<double, 4>{0, 1, 2, 3};  // 默认0
    for (const auto& p : poly) {
      std::cout << "p:" << p << std::endl;
    }
    double u = 2;
    double v = boost::math::tools::evaluate_polynomial(poly, u);
    std::cout << "v: " << v << std::endl;
  }

  {
    std::cout << " ------------  UUID  ------------ " << std::endl;
    boost::uuids::random_generator gen;
    boost::uuids::uuid uuid = gen();
    std::string uu = boost::uuids::to_string(uuid);
    std::cout << "Generated UUID as string: " << uu << std::endl;
  }

  return 0;
}
