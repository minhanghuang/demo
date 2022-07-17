#include <mutex>

class Sigaction {
public:
  Sigaction() = default;
  ~Sigaction() = default;
  Sigaction(const Sigaction &) = delete;
  Sigaction &operator=(const Sigaction &) = delete;
  static Sigaction *Instance(bool create_if_needed = true) {
    static Sigaction *instance = nullptr;
    if (!instance && create_if_needed) {
      static std::once_flag flag;
      std::call_once(flag, [&] { instance = new (std::nothrow) Sigaction(); });
    }
    return instance;
  }

  static std::string GetName() { return "singleton"; }

private:
};
