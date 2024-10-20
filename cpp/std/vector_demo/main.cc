#include <algorithm>  // 包含头文件以使用 std::max_element
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  std::cout << "Hello Vector." << std::endl;
  {
    /// 1. 收缩内存
    std::vector<int> vi;
    for (int i = 0; i < 10000; i++) {
      vi.emplace_back(i);
    }
    std::cout << "vi 容量:" << vi.capacity() << std::endl;
    std::cout << "vi 大小:" << vi.size() << std::endl;
    vi.clear();
    std::cout << "clear vi 容量:" << vi.capacity() << std::endl;
    std::cout << "clear vi 大小:" << vi.size() << std::endl;
    vi.resize(10);
    std::cout << "resize vi 容量:" << vi.capacity() << std::endl;
    std::cout << "resize vi 大小:" << vi.size() << std::endl;
    std::vector<int>().swap(vi);
    std::cout << "swap vi 容量:" << vi.capacity() << std::endl;
    std::cout << "swap vi 大小:" << vi.size() << std::endl;
    vi.resize(10);
    std::cout << "swap resize vi 容量:" << vi.capacity() << std::endl;
    std::cout << "swap resize vi 大小:" << vi.size() << std::endl;
    vi.emplace_back(1);
    vi.emplace_back(2);
    vi.emplace_back(3);
    vi.emplace_back(4);
    std::cout << "push vi 容量:" << vi.capacity() << std::endl;
    std::cout << "push vi 大小:" << vi.size() << std::endl;
    std::cout << "[0]: " << vi[0] << std::endl;
    std::cout << "[10]: " << vi[10] << std::endl;
    std::cout << "[11]: " << vi[11] << std::endl;
    for (const auto& it : vi) {
      std::cout << "it: " << it << std::endl;
    }
  }
  std::cout << "\n##########  \n" << std::endl;
  {
    // 清空
    std::vector<int> vi;
    vi.clear();
    vi.reserve(2);
    vi.emplace_back(1);
    vi.emplace_back(2);
    for (const auto& it : vi) {
      std::cout << "v: " << it << std::endl;
    }
  }

  {
    // find
    std::vector<int> vi{1, 2, 3, 4, 5, 6, 7};
    std::vector<int>::iterator it = std::find(vi.begin(), vi.end(), -1);
    if (it == vi.end()) {
      std::cout << "未查到." << std::endl;
    } else {
      std::cout << "查到." << std::endl;
    }
  }

  {
    std::cout << "@@@@@@@@@@@@@  排序 @@@@@@@@@@@@@ " << std::endl;
    std::vector<int> a{1, 7, 3, 4, 5, 0, -1, -32, -2, 8};

    // 升序
    // std::sort(a.begin(), a.end());  // sort: 默认升序
    // for (const auto& v : a) {
    //   std::cout << "v: " << v << std::endl;
    // }

    // 升序
    // std::sort(a.begin(), a.end(),
    //           [](int v1, int v2) { return v1 < v2; });
    // for (const auto& v : a) {
    //   std::cout << "v: " << v << std::endl;
    // }

    // 降序
    // std::sort(a.begin(), a.end(),
    //           [](int v1, int v2) { return v1 > v2; });
    // for (const auto& v : a) {
    //   std::cout << "v: " << v << std::endl;
    // }

    // 升序, 正数在前, 负数在后[0, 1, 3, 5, 7, 8, -32, -2, -1]
    std::sort(a.begin(), a.end(), [](int x1, int x2) { return x1 < x2; });
    std::stable_partition(a.begin(), a.end(), [](int x) { return x >= 0; });
    for (const auto& v : a) {
      std::cout << "v: " << v << std::endl;
    }
  }

  {
    std::cout << "@@@@@@@@@@@@@  最大元素 @@@@@@@@@@@@@ " << std::endl;
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6, 3};
    // 使用 std::max_element 查找最大元素
    std::vector<int>::iterator max_it =
        std::max_element(numbers.begin(), numbers.end());
    if (max_it != numbers.end()) {
      int max_value = *max_it;
      std::cout << "Max element is: " << max_value << std::endl;
    } else {
      std::cout << "Container is empty." << std::endl;
    }
  }

  {
    std::cout << "@@@@@@@@@@@@@  查找起始符 @@@@@@@@@@@@@ " << std::endl;
    std::vector<char> buffer = {0x01, 0x02, 0x03, 0x0a, 0x0a, 0x04, 0x05};

    // 定义起始符 (0x0a0a)
    std::vector<char> start_marker = {0x0a, 0x0a};

    // 在缓冲区中查找起始符的位置
    auto it = std::search(buffer.begin(), buffer.end(), start_marker.begin(),
                          start_marker.end());

    // 如果找到起始符，删除它之前的所有数据
    if (it != buffer.end()) {
      buffer.erase(buffer.begin(), it);
    } else {
      std::cerr << "未找到起始符" << std::endl;
    }

    // 输出剩余的 buffer 数据
    std::cout << "Modified buffer: ";
    for (char c : buffer) {
      std::cout << std::hex << static_cast<int>(c) << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
