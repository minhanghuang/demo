#include <cassert>
#include <iostream>
#include <string>

int main() {
  std::cout << "Hello, std::string!" << std::endl;

  const std::string s = "This is a string";
  //                     0123456789123456

  {
    // -------- 查找 --------
    // 1. std::string的查找函数 find (默认从左往右,惰性)
    std::string::size_type n11 = s.find("is");  // 找到[is], 返回[is]中[i]下标:2
    std::cout << "[is]第一次出现下标:" << n11 << std::endl;
    std::string::size_type n12 =
        s.find("This");  // 找到[This], 返回[This]中[T]下标:0
    std::cout << "[This]第一次出现下标:" << n12 << std::endl;
    std::string::size_type n13 =
        s.find("string");  // 找到[string], 返回[string]中[s]下标:10
    std::cout << "[string]第一次出现下标:" << n13 << std::endl;
    std::string::size_type n14 =
        s.find("haha");  // 未找到[haha], 返回std::string::npos
    std::cout << "[haha]未查到:" << n14 << std::endl;
    std::cout << "---\n" << std::endl;
  }
  {
    // 2. std::string的查找函数 rfind 从右往左(惰性)
    std::string::size_type n21 =
        s.rfind("is");  // 从右往左找到[is],返回[is]中[i]下标:5
    std::cout << "[is]从右往左,第一次出现下标:" << n21 << std::endl;
    std::cout << "---\n" << std::endl;
  }

  {
    // 3. std::string的查找函数 find_first_of (默认从左往右,下标=0开始)
    // 正向查找在原字符串中第一个与指定字符串（或字符）中的某个字符匹配的字符，返回它的位置
    std::string::size_type n31 = s.find_first_of(
        "sdf");  // 原字符串中,最早出现[s,d,f]任一字符,位置为:[This]中的[s],
                 // 故返回:3
    std::cout << "find_first_of: 正向查找[s,d,f]第一次出现下标:" << n31
              << std::endl;
    std::string::size_type n32 = s.find_first_of(
        "xyaf");  // 原字符串中,最早出现[x,y,a,f]任一字符,位置为:[a]中的[a],
                  // 故返回:8
    std::cout << "find_first_of: 正向查找[x,y,a,f]第一次出现下标:" << n32
              << std::endl;
    std::string::size_type n33 = s.find_first_of(
        "xysf",
        4);  // 原字符串从小标4开始,最早出现[x,y,s,f]任一字符,位置为:[string]中的[s],
             // 故返回:6
    std::cout << "find_first_of: 正向查找[x,y,s,f]从下标=4起,第一次出现下标:"
              << n33 << std::endl;
    std::cout << "---\n" << std::endl;
  }
  {
    // 4. std::string的查找函数 find_last_of (从右往左)
    // 逆向查找在原字符串中最后一个与指定字符串（或字符）中的某个字符匹配的字符，返回它的位置
    std::string::size_type n41 = s.find_last_of(
        "sdf");  // 原字符串中, 逆向查找,
                 // 第一次出现[s,d,f]任一字符,位置为:[string]中的[s], 故返回:10
    std::cout << "find_last_of: 逆向查找[s,d,f]第一次出现下标:" << n41
              << std::endl;
    std::string::size_type n42 = s.find_last_of(
        "xyaf");  // 原字符串中, 逆向查找,
                  // 第一次出现[x,y,a,f]任一字符,位置为:[a]中的[a], 故返回:8
    std::cout << "find_last_of: 逆向查找[x,y,a,f]第一次出现下标:" << n42
              << std::endl;
    std::string::size_type n43 = s.find_last_of(
        "xysf", 4);  // 原字符串从小标4开始,逆向查找,
                     // 第一次出现[x,y,s,f]任一字符,位置为:[is]中的[s], 故返回:6
    std::cout << "find_last_of: 逆向查找[x,y,s,f]从下标=4起,第一次出现下标:"
              << n43 << std::endl;
    std::cout << "---\n" << std::endl;
  }
  {
    // 5. std::string的查找函数 find_first_not_of
    // 正向查找在原字符串中第一个与指定字符串（或字符）中的任一字符都不匹配的字符
    std::string::size_type n51 = s.find_first_not_of(
        "sdf");  // 正向查找, 原串第0字符[T]与[s,d,f]都不匹配,故返回:0
    std::cout << "原字符中第一个与[s,d,f]不匹配的下标:" << n51 << std::endl;
    std::string::size_type n52 = s.find_first_not_of(
        "hTaf");  // 正向查找, 原串第2字符[i]与[h,T,a,f]都不匹配,故返回:2
    std::cout << "原字符中第一个与[h,T,a,f]不匹配的下标:" << n52 << std::endl;
    std::cout << "---\n" << std::endl;
  }
  {
    // 6. std::string的查找函数 find_last_not_of
    // 逆向查找在原字符串中第一个与指定字符串（或字符）中的任一字符都不匹配的字符
    std::string::size_type n61 = s.find_last_not_of(
        "sdf");  // 逆向查找, 原串第15字符[g]与[s,d,f]都不匹配,故返回:15
    std::cout << "逆向查找,原字符中第一个与[s,d,f]不匹配的下标:" << n61
              << std::endl;
    std::string::size_type n62 = s.find_last_not_of(
        "xgaf");  // 逆向查找, 原串第14字符[n]与[x,g,a,f]都不匹配,故返回:14
    std::cout << "逆向查找,原字符中第一个与[x,g,a,f]不匹配的下标:" << n62
              << std::endl;
    std::cout << "---\n" << std::endl;
  }

  {
    // 7. 生成一个const char*指针，指向以空字符终止的数组
    // c_str()函数返回一个指向正规C字符串的指针,
    // 内容是字符串对象的当前内容加上一个额外的终止字符(‘\0’)
    const char* c1 = s.c_str();
    std::cout << "c1: " << c1 << std::endl;

    auto c2 = s.data();
    std::cout << "c2: " << c2 << std::endl;
  }

  {
    // 8. 字符串拼接, 两种拼接方法效果性能没有差别
    std::string s1 = "Str";
    s1.append("ing");

    // 或
    // s1 += "ing";

    assert("String" == s1);
  }

  return 0;
}
