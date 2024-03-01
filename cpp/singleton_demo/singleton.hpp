#include <memory>
#include <mutex>

template <typename T>
class Singleton {
 public:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  static std::shared_ptr<T> Instance() {
    static std::shared_ptr<T> instance = nullptr;
    if (!instance) {
      static std::once_flag flag;
      std::call_once(flag, [&] { instance = std::make_shared<T>(); });
    }
    return instance;
  }

 private:
  Singleton() = default;
  ~Singleton() = default;
};
