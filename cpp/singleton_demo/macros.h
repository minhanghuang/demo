#include <memory>

#define DISALLOW_COPY_AND_ASSIGN(classname) \
  classname(const classname&) = delete;     \
  classname& operator=(const classname&) = delete;

#define DECLARE_SINGLETON(classname)                                         \
 public:                                                                     \
  static std::shared_ptr<classname> Instance(bool create_if_needed = true) { \
    static std::shared_ptr<classname> instance = nullptr;                    \
    if (!instance && create_if_needed) {                                     \
      static std::once_flag flag;                                            \
      std::call_once(flag, [&] { instance.reset(new classname()); });        \
    }                                                                        \
    return instance;                                                         \
  }                                                                          \
                                                                             \
 private:                                                                    \
  classname();                                                               \
  DISALLOW_COPY_AND_ASSIGN(classname)
