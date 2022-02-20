#include "log.h"

namespace tlog {

Logger::Logger() {
    Init();
}

Logger::~Logger() {
    spdlog::drop_all();
}

void Logger::Init() {
    log_root_path = "/var/log/trunk/brainshell/";
    info_file_path = "bshell_info.log";
    error_file_path = "bshell_erro.log";
    rotation_h = 5;// 分割时间
    rotation_m = 59;
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

void Logger::AddHandler() {

}

} // namespace tlog