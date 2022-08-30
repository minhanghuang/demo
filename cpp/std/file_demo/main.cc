#include <iostream>

bool FileExists(const std::string &path) {
  if (FILE *file = fopen(path.c_str(), "r")) {
    fclose(file);
    return true;
  }
  return false;
}

int main(int argc, char *argv[]) {
  std::cout << "file demo" << std::endl;
  std::cout << "ret:" << FileExists("/opt/trunk_master/share/trunk_hdmap_actor/data/Ningbo/yz_bidirection_20220723.json") << std::endl;
  std::cout << "ret:" << FileExists("/opt/trunk_master/share/trunk_hdmap_actor/data/Ningbo/yz_bidirection_20220723.json") << std::endl;
  std::cout << "ret:" << FileExists("/opt/trunk_master/share/trunk_hdmap_actor/data/Ningbo/ssss.json") << std::endl;
  return 0;
}
