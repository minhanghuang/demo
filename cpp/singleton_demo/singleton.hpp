#include <mutex>

class Singleton {
 public:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  template <typename T>
  static T* Instance() {
    static T* instance = nullptr;
    if (!instance) {
      static std::once_flag flag;
      std::call_once(flag, [&] { instance = new (std::nothrow) T(); });
    }
    return instance;
  }

 private:
  Singleton() = default;
  ~Singleton() = default;
};
