/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Minhang Huang <huangminhang@trunk.tech>, 2021/12/30 19:27
*/
#include <iostream>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>


int main() {
    std::cout << "Hello, boost filesystem!" << std::endl;

    std::string abs_path1 = "/Users/cox/work/code/github/demo/cpp/filesystem_demo";
    std::string abs_path2 = "/Users/cox/work/code/github/demo/cpp/filesystem_demo/main.cc";
    std::string abs_path3 = "/Users/cox/work/code/github/demo/cpp/filesystem_demo/haha";
    std::string abs_path4 = "/Users/cox/work/code/github/demo/cpp/filesystem_demo/haha/ooo/uuuu/yyyy";
    std::string abs_path5 = "/Users/cox/work/code/github/demo/cpp/filesystem_demo/hihi";

    // 1. path
    boost::filesystem::path path1(abs_path1);
    boost::filesystem::path path2(abs_path2);
    boost::filesystem::path path3(abs_path3);
    boost::filesystem::path path4(abs_path4);
    boost::filesystem::path path5(abs_path5);
    std::cout << "输出字符串形式的路径: " << path1.string() << std::endl; // /Users/cox/work/code/github/demo/cpp/filesystem_demo
    std::cout << "文件名，不带扩展名: " << path1.stem() << std::endl; // "filesystem_demo"
    std::cout << "返回文件扩展名: " << path1.extension() << std::endl; // ""
    std::cout << "获取文件或目录的绝对路径: " << boost::filesystem::absolute(path1) << std::endl; // /Users/cox/work/code/github/demo/cpp/filesystem_demo
    std::cout << "当前路径: " << boost::filesystem::current_path() << std::endl; // 如果没有参数传入，则返回当前工作目录；否则，则将传入的目录设为当前工作目录


    // 2. 判断文件
    auto status = boost::filesystem::status(path1);
    std::cout << "文件状态-权限: " << status.permissions() << std::endl;
    std::cout << "文件状态-类型: " << status.type() << std::endl;

    std::cout << "判断-目录是否存在: " << boost::filesystem::is_directory(path1) << std::endl; // 1
    std::cout << "判断-目录是否存在: " << boost::filesystem::is_directory(path2) << std::endl; // 0
    std::cout << "判断-目录是否为空: " << boost::filesystem::is_empty(path1) << std::endl; // 0
    std::cout << "判断-目录是否为空: " << boost::filesystem::is_empty(path2) << std::endl; // 0
    std::cout << "判断-是否为文件: " << boost::filesystem::is_regular_file(path1) << std::endl; // 0
    std::cout << "判断-是否为文件: " << boost::filesystem::is_regular_file(path2) << std::endl; // 1
    std::cout << "判断-是否为链接文件: " << boost::filesystem::is_symlink(path1) << std::endl; // 0
    std::cout << "判断-是否为链接文件: " << boost::filesystem::is_symlink(path2) << std::endl; // 0
    std::cout << "判断-是否存在: " << boost::filesystem::exists(path1) << std::endl; // 1
    std::cout << "判断-是否存在: " << boost::filesystem::exists(path2) << std::endl; // 1
//   exception std::cout << "文件大小: " << boost::filesystem::file_size(path1) << std::endl; // exception
    std::cout << "文件大小: " << boost::filesystem::file_size(path2) << std::endl; // 2961 bytes
    std::cout << "最后修改时间: " << boost::filesystem::last_write_time(path1) << std::endl; // 1640914873 时间戳
    std::cout << "最后修改时间: " << boost::filesystem::last_write_time(path2) << std::endl; // 1640914873 时间戳

    // 3. 操作文件
    boost::filesystem::create_directory(path3); // 创建目录
//    exception boost::filesystem::create_directory(path4); // exception
    boost::filesystem::create_directories(path3); // 创建目录
    boost::filesystem::create_directories(path4); // 创建目录

//    boost::filesystem::remove(path3); // 删除目录
//    boost::filesystem::remove_all(path3); // 递归删除目录

//    boost::filesystem::rename(path3,path5); // 重命名目录(目录存在时)

//    boost::filesystem::copy_file() // 复制文件
//    boost::filesystem::copy_directory() // 复制目录


//    // 4. 遍历文件夹
    boost::filesystem::directory_iterator end_iter1; // 遍历当前目录
    for(boost::filesystem::directory_iterator file_iter(path1); file_iter != end_iter1; ++file_iter ) {
        std::cout << "file: " << *file_iter  << std::endl;
    }
    std::cout << "-------" << std::endl;
    boost::filesystem::recursive_directory_iterator end_iter2; // 递归地遍历一个目录和子目录，也就是迭代整个目录结构下的所有文件
    for(boost::filesystem::recursive_directory_iterator file_iter(path1); file_iter != end_iter2; ++file_iter ) {
        std::cout << "file: " << *file_iter  << std::endl;
    }

    // 5. 文件流
    // // 头文件<fstream>定义的文件流不能将boost::filesystem::path定义的目录作为参数。如果非要使用path对象打开文件流的话，那就添加头文件<boost/filesystem/fstream.hpp>
    boost::filesystem::path p{"haha.txt"};

    boost::filesystem::ofstream ofs{p};

    ofs << "Hello, world!\n";

    return 0;
}
