/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Minhang Huang <huangminhang@trunk.tech>, 2021/12/30 10:53
*/
#include <iostream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem.hpp>


int main() {
    std::cout << "Hello, split!" << std::endl;
//    std::string abs_path = "/Users/cox/work/code/github/demo/cpp/split_demo"; // 是文件夹-
    std::string abs_path = "/Users/cox/work/code/github/demo/cpp/split_demo/haha.tar.gz"; // 是文件夹-
//    std::string abs_path = "/Users/cox/work/code/github/demo/cpp/splixxxxxemo"; // 不是文件夹-
//    std::string abs_path = "/Users/cox/work/code/github/demo/cpp/split_demo/hdmap.tar.gz"; // 不是文件夹-
//    std::string abs_path = "http://192.168.199.4:8080/file/bags/"; // 不是文件夹-
//    std::string abs_path = "http://192.168.199.4:8080/file/bags/hdmap.tar.gz"; // 不是文件夹-


    boost::filesystem::path p(abs_path);
    std::cout << "判断是否是文件夹: " << boost::filesystem::is_directory(p) << std::endl;
    std::cout << "判断是否是文件: " << boost::filesystem::is_regular_file(p) << std::endl;

    std::vector<std::string> ret_split;
    boost::split(ret_split, abs_path, boost::is_any_of(":// ."), boost::token_compress_on);
    for (const auto& s : ret_split) {
        std::cout << "s:" << s << std::endl;
    }
    std::cout << "pro:" << *(ret_split.end()-3) << std::endl;

    return 0;
}
