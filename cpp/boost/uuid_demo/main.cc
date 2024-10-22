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
    std::cout << " ------------  UUID  ------------ " << std::endl;
    boost::uuids::random_generator gen;
    boost::uuids::uuid uuid = gen();
    std::string uu = boost::uuids::to_string(uuid);
    std::cout << "Generated UUID as string: " << uu << std::endl;
  }

  return 0;
}
