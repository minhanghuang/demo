#include <fstream>  // fstream
#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Hello fstream." << std::endl;
  /// - ofstream: 写
  /// - ifstream: 读
  /// - fstream: 读写
  std::fstream fs;
  /// std::ios::in 读
  /// std::ios::out 写
  /// std::ios::ate
  /// std::ios::app 追加
  /// std::ios::trunc 如果文件存在,先删除,再创建
  /// std::ios::binary 二进制
  fs.open("/Users/cox/data.json", std::ios::out);
  fs << "{'header':'bbb'}" << std::endl;
  fs.close();  // 关闭句柄
  return 0;
}
