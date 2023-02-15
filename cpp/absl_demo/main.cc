#include <absl/hash/hash.h>
#include <absl/time/time.h>

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Hello absl." << std::endl;
  absl::Time t;
  absl::Hash<int> h;
  const absl::Duration d = absl::Nanoseconds(1);
  return EXIT_SUCCESS;
}
