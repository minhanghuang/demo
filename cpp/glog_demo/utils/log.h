/*
* Copyright (C) Trunk Technology, Inc. - All Rights Reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
*
* Written by Minhang Huang <huangminhang@trunk.tech>, 2021/12/25 23:08
*/
#ifndef GLOG_DEMO_LOG_H_
#define GLOG_DEMO_LOG_H_
#include <iostream>
#include <chrono>
#include <boost/filesystem.hpp>
#include <glog/logging.h>
#include <glog/stl_logging.h>


class Log {
public:
    ~Log() {
        google::ShutdownGoogleLogging();
    }
    static void init(int console_level=google::GLOG_INFO) {
        const std::string abs_path = "/var/log/trunk/glog_demo";
        int day = 1;
        boost::filesystem::path file_path(abs_path);
        if (!boost::filesystem::is_directory(file_path)) {
            boost::filesystem::create_directories(file_path);
        }
        std::chrono::seconds timestamp =
                std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
        boost::filesystem::directory_iterator end;
        for (boost::filesystem::directory_iterator pos(file_path); pos != end; pos++) {
//            std::cout << *pos << "--" << boost::filesystem::last_write_time(*pos) << std::endl;
            if (boost::filesystem::last_write_time(*pos)+day*24*60*60 < timestamp.count() &&
                !boost::filesystem::is_symlink(*pos)) {
                boost::filesystem::remove(*pos); // 删除过期日志
            }
        }

        // GLog生成的文件名格式是[文件名].[计算机名].[用户名].[log].[等级].[年月日时分秒].[PID]例
        FLAGS_log_dir = abs_path; // 将日志文件输出到本地
        google::InitGoogleLogging("glog_demo"); // glog_demo.bogon.cox.log.ERROR.20211226-151429.53038
        google::SetStderrLogging(console_level);  //大于指定级别的日志都输出到标准输出
//        FLAGS_logtostderr = false; // 日志只显示在终端
        FLAGS_alsologtostderr = false; // 让日志同时输出到终端
    }
};

#define MLOG(fmt) LOG(INFO) << fmt
#define MLOG_INFO(fmt) LOG(INFO) << fmt
#define MLOG_WARNING(fmt) LOG(WARNING) << fmt
#define MLOG_ERROR(fmt) LOG(ERROR) << fmt

#endif//GLOG_DEMO_LOG_H_
