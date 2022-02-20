#ifndef SPDLOG_DEMO_LOG_H_
#define SPDLOG_DEMO_LOG_H_
#include <iostream>
#include <memory>

#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace tlog {

class Logger {
public:
    static Logger& instance() {
        static Logger instance;
        return instance;
    }
    auto logger() const {
        return logger_;
    }
    void AddHandler();

private:
    Logger();
    ~Logger();
    void Init();
    std::shared_ptr<spdlog::logger> logger_;
    std::shared_ptr<spdlog::sinks::daily_file_sink_mt> info_sink_, error_sink_;
    std::vector<spdlog::sink_ptr> sinks_;
    std::string log_root_path;
    std::string error_file_path;
    std::string info_file_path;
    short int rotation_h{};
    short int rotation_m{};

};// Logger

#define XLOG tlog::Logger::instance().logger()

}// namespace tlog


#endif//SPDLOG_DEMO_LOG_H_
