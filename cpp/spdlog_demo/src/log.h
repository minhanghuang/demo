#ifndef SPDLOG_DEMO_LOG_H_
#define SPDLOG_DEMO_LOG_H_
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <memory>

namespace tlog {

class Logger {
public:
    static Logger& instance() {
        static Logger instance;
        return instance;
    }
    auto get_logger() const {
        return logger_;
    }

private:
    Logger() {
        init();
    }
    ~Logger() {
        spdlog::drop_all();// 释放所有logger
    }
    void init() {
        init_file();
        init_logger();
    }
    void init_file() {
        log_root_path = "/var/log/trunk/brainshell/";
        info_file_path = "bshell_info.log";
        error_file_path = "bshell_erro.log";
        rotation_h = 5;// 分割时间
        rotation_m = 59;
    }

    void init_logger() {
        info_sink_ = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
                log_root_path + info_file_path, rotation_h, rotation_m);
        error_sink_ = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
                log_root_path + error_file_path, rotation_h, rotation_m);

        info_sink_->set_level(spdlog::level::info);// debug< info< warn< error< critical  日志信息低于设置的级别时, 不予显示
        error_sink_->set_level(spdlog::level::err);

        sinks_.push_back(info_sink_);   // info
        sinks_.push_back(error_sink_);  // error

        logger_ = std::make_shared<spdlog::logger>("bshell", begin(sinks_), end(sinks_));
        logger_->set_pattern("[%l] [%Y-%m-%d %H:%M:%S,%e] [Process:%P] - %v");
        logger_->flush_on(spdlog::level::info); // 设置当触发 info 或更严重的错误时立刻刷新日志到 disk
        spdlog::register_logger(logger_);       // 注册logger
        spdlog::flush_every(std::chrono::seconds(10));// 每隔10秒刷新一次日志
    }

private:
    std::shared_ptr<spdlog::logger> logger_;
    std::shared_ptr<spdlog::sinks::daily_file_sink_mt> info_sink_;     // info
    std::shared_ptr<spdlog::sinks::daily_file_sink_mt> error_sink_;    // error
    std::vector<spdlog::sink_ptr> sinks_;
    std::string log_root_path;
    std::string error_file_path;
    std::string info_file_path;
    short int rotation_h{};
    short int rotation_m{};

};// Logger

    #define XLOG tlog::Logger::instance().get_logger()

}// namespace tlog


#endif//SPDLOG_DEMO_LOG_H_
