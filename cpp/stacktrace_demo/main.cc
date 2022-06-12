#include <iostream>
#include <signal.h>     // ::signal, ::raise
#include <boost/stacktrace.hpp>


// void my_signal_handler(int signum) {
//     ::signal(signum, SIG_DFL);
//     boost::stacktrace::safe_dump_to("./backtrace.dump");
//     ::raise(SIGABRT);
// }

int main(int argc, char *argv[]) {
  std::cout << "stacktrace" << std::endl;

  return 0;
}

