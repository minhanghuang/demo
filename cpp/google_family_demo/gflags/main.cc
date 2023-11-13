#include <iostream>

#include <gflags/gflags.h>

DEFINE_bool(verbose, false, "Display program name before message");
DEFINE_string(message, "Hello World!", "Message to print");

int main(int argc, char* argv[]) {
  std::cout << "Hello, gflags." << std::endl;
  // make -j$(nproc) && ./gflags_demo_runner --verbose=true --message="Custom Message"
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  // 使用定义的标志
  std::cout << FLAGS_verbose << std::endl;
  std::cout << FLAGS_message << std::endl;
  return 0;
}
