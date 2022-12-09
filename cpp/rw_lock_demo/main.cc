#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// from Baidu Apollo.
template <typename RWLock>
class ReadLockGuard {
 public:
  explicit ReadLockGuard(RWLock& lock) : rw_lock_(lock) { rw_lock_.ReadLock(); }

  ~ReadLockGuard() { rw_lock_.ReadUnlock(); }

 private:
  ReadLockGuard(const ReadLockGuard& other) = delete;
  ReadLockGuard& operator=(const ReadLockGuard& other) = delete;
  RWLock& rw_lock_;
};

template <typename RWLock>
class WriteLockGuard {
 public:
  explicit WriteLockGuard(RWLock& lock) : rw_lock_(lock) {
    rw_lock_.WriteLock();
  }

  ~WriteLockGuard() { rw_lock_.WriteUnlock(); }

 private:
  WriteLockGuard(const WriteLockGuard& other) = delete;
  WriteLockGuard& operator=(const WriteLockGuard& other) = delete;
  RWLock& rw_lock_;
};

class AtomicRWLock {
  friend class ReadLockGuard<AtomicRWLock>;
  friend class WriteLockGuard<AtomicRWLock>;

 public:
  static const int32_t RW_LOCK_FREE = 0;
  static const int32_t WRITE_EXCLUSIVE = -1;
  static const uint32_t MAX_RETRY_TIMES = 5;
  AtomicRWLock() {}
  explicit AtomicRWLock(bool write_first) : write_first_(write_first) {}

 private:
  // all these function only can used by ReadLockGuard/WriteLockGuard;
  void ReadLock();
  void WriteLock();

  void ReadUnlock();
  void WriteUnlock();

  AtomicRWLock(const AtomicRWLock&) = delete;
  AtomicRWLock& operator=(const AtomicRWLock&) = delete;
  std::atomic<uint32_t> write_lock_wait_num_ = {0};
  std::atomic<int32_t> lock_num_ = {0};
  bool write_first_ = true;
};

inline void AtomicRWLock::ReadLock() {
  uint32_t retry_times = 0;
  int32_t lock_num = lock_num_.load();
  if (write_first_) {
    do {
      while (lock_num < RW_LOCK_FREE || write_lock_wait_num_.load() > 0) {
        if (++retry_times == MAX_RETRY_TIMES) {
          // saving cpu
          std::this_thread::yield();
          retry_times = 0;
        }
        lock_num = lock_num_.load();
      }
    } while (!lock_num_.compare_exchange_weak(lock_num, lock_num + 1,
                                              std::memory_order_acq_rel,
                                              std::memory_order_relaxed));
  } else {
    do {
      while (lock_num < RW_LOCK_FREE) {
        if (++retry_times == MAX_RETRY_TIMES) {
          // saving cpu
          std::this_thread::yield();
          retry_times = 0;
        }
        lock_num = lock_num_.load();
      }
    } while (!lock_num_.compare_exchange_weak(lock_num, lock_num + 1,
                                              std::memory_order_acq_rel,
                                              std::memory_order_relaxed));
  }
}

inline void AtomicRWLock::WriteLock() {
  int32_t rw_lock_free = RW_LOCK_FREE;
  uint32_t retry_times = 0;
  write_lock_wait_num_.fetch_add(1);
  while (!lock_num_.compare_exchange_weak(rw_lock_free, WRITE_EXCLUSIVE,
                                          std::memory_order_acq_rel,
                                          std::memory_order_relaxed)) {
    // rw_lock_free will change after CAS fail, so init agin
    rw_lock_free = RW_LOCK_FREE;
    if (++retry_times == MAX_RETRY_TIMES) {
      // saving cpu
      std::this_thread::yield();
      retry_times = 0;
    }
  }
  write_lock_wait_num_.fetch_sub(1);
}

inline void AtomicRWLock::ReadUnlock() { lock_num_.fetch_sub(1); }

inline void AtomicRWLock::WriteUnlock() { lock_num_.fetch_add(1); }

class Zoo {
 public:
  void Eat() {
    std::thread t1(&Zoo::Cat, this);
    std::thread t2(&Zoo::Dog, this);
    std::thread t3(&Zoo::Mouse, this);
    t1.join();
    t2.join();
    t3.join();
  }

 private:
  void Cat() {
    // /// 1.多线程不加锁: 程序崩溃
    // std::cout << "Cat Eat." << std::endl;
    // food.clear();
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // food.emplace_back(1);
    // food.emplace_back(99);
    // std::cout << "Cat End." << std::endl;

    // /// 2.多线程加互斥锁: 程序不崩溃, 但是读取数据时, 影响别的线程读取数据
    // {
    //   std::unique_lock<std::mutex> lock(mutex_);
    //   std::cout << "Cat Eat." << std::endl;
    //   food.clear();
    //   std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //   food.emplace_back(1);
    //   food.emplace_back(99);
    //   std::cout << "Cat End." << std::endl;
    // }

    /// 3.多线程加读写锁: 程序不崩溃, 所有读锁不互斥 && 读锁和写锁互斥
    {
      WriteLockGuard<AtomicRWLock> lck(rw_lock_);
      std::cout << "Cat Eat." << std::endl;
      food.clear();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      food.emplace_back(1);
      food.emplace_back(99);
      std::cout << "Cat End." << std::endl;
    }
  }

  void Dog() {
    // /// 1.多线程不加锁: 程序崩溃
    // std::cout << "Dog Eat." << std::endl;
    // std::cout << "Dog ...  " << food.at(1) << std::endl;
    // std::cout << "Dog End." << std::endl;

    // /// 2.多线程加互斥锁: 程序不崩溃, 但是读取数据时, 影响别的线程读取数据
    // {
    //   std::unique_lock<std::mutex> lock(mutex_);
    //   std::cout << "Dog Eat." << std::endl;
    //   std::cout << "Dog ...  " << food.at(1) << std::endl;
    //   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //   std::cout << "Dog End." << std::endl;
    // }

    /// 3.多线程加读写锁: 程序不崩溃, 所有读锁不互斥 && 读锁和写锁互斥
    {
      ReadLockGuard<AtomicRWLock> lck(rw_lock_);
      std::cout << "Dog Eat." << std::endl;
      std::cout << "Dog ...  " << food.at(1) << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << "Dog End." << std::endl;
    }
  }

  void Mouse() {
    // /// 1.多线程不加锁: 程序崩溃
    // std::cout << "Mouse Eat." << std::endl;
    // std::cout << "Mouse ...  " << food.at(1) << std::endl;
    // std::cout << "Mouse End." << std::endl;

    // /// 2.多线程加互斥锁: 程序不崩溃, 但是读取数据时, 影响别的线程读取数据
    // {
    //   std::unique_lock<std::mutex> lock(mutex_);
    //   std::cout << "Mouse Eat." << std::endl;
    //   std::cout << "Mouse ...  " << food.at(1) << std::endl;
    //   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //   std::cout << "Mouse End." << std::endl;
    // }

    /// 3.多线程加读写锁: 程序不崩溃, 所有读锁不互斥 && 读锁和写锁互斥
    {
      ReadLockGuard<AtomicRWLock> lck(rw_lock_);
      std::cout << "Mouse Eat." << std::endl;
      std::cout << "Mouse ...  " << food.at(1) << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      std::cout << "Mouse End." << std::endl;
    }
  }
  std::vector<int> food{1, 2, 3};  // 共享资源
  std::mutex mutex_;               // 互斥锁
  AtomicRWLock rw_lock_;           // 读写锁
};

int main(int argc, char* argv[]) {
  std::cout << "Hello Read Write Lock." << std::endl;
  Zoo zoo;
  zoo.Eat();
  return 0;
}
