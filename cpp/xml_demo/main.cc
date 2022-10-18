#include <iostream>
#include <tinyxml2.h>

int main(int argc, char *argv[]) {
  std::cout << "Hello XML." << std::endl;
  tinyxml2::XMLDocument doc;
  doc.LoadFile("test.xml");
  return 0;
}
