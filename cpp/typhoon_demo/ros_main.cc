#include "ros/init.h"
#include "ros/node_handle.h"
#include "typhoon/civethandle.h"
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <ros/ros.h>
#include <typhoon/typhoon.h>
#include <unistd.h>
#include <utility>
#include <vector>

class Data {
public:
  Data() {
    typhoon::Options options;
    options.port = 9990;
    server_ = std::make_shared<typhoon::Server>(options);
  }
  void Start() {
    weather_timer_ = nh_.createTimer(ros::Duration(1), &Data::TimerCb, this);
    server_->Get("/api/typhoon/ros/",
                 std::bind(&Data::GetRequest, this, std::placeholders::_1,
                           std::placeholders::_2));
  }

private:
  void TimerCb(const ros::TimerEvent &event) {
    std::cout << "timer : " << conn_.size() << std::endl;
    const std::string msg = "dataxxx";
    auto conn = conn_;
    for (const auto &c : conn) {
      if (typhoon::RequestHandler::Write(c.first, c.second, msg.c_str(),
                                         msg.size()) <= 0) {
        std::cout << "xxxxx" << std::endl;
        {
          std::lock_guard<std::mutex> guard(mutex_);
          conn_.pop_back();
        }
      } else {
        std::cout << "send ok !!!!" << std::endl;
      }
    }
  }
  void GetRequest(typhoon::Application *app, typhoon::Connection *conn) {
    std::cout << "get" << std::endl;
    {
      std::lock_guard<std::mutex> guard(mutex_);
      // conn_[conn] = app;
      conn_.emplace_back(std::make_pair(app, conn));
    }
    std::string response_data;
    static const std::string header_protocol = "HTTP/1.1 200 OK\r\n";
    static const std::string header_boundary = "--boundarydonotcross\r\n";
    static const std::string header_connection = "Connection: close\r\n";
    static const std::string header_max_age = "Max-Age: 0\r\n";
    static const std::string header_expires = "Expires: 0\r\n";
    static const std::string header_cache_control =
        "Cache-Control: no-cache, no-store, must-revalidate, private\r\n";
    static const std::string header_pargma = "Pragma: no-cache\r\n";
    static const std::string header_content_type =
        "Content-Type: multipart/x-mixed-replace; boundary=" + header_boundary;
    static const std::string header_terminator = "\r\n";
    auto a = typhoon::RequestHandler::Write(
        conn_.front().first, conn_.front().second, header_protocol.c_str(),
        header_protocol.size());
    std::cout << "a: " << a << std::endl;
    // typhoon::RequestHandler::Write(app, conn, header_connection.c_str(),
    //                                header_connection.size());
    // typhoon::RequestHandler::Write(app, conn, header_max_age.c_str(),
    //                                header_max_age.size());
    // typhoon::RequestHandler::Write(app, conn, header_expires.c_str(),
    //                                header_expires.size());
    // typhoon::RequestHandler::Write(app, conn, header_cache_control.c_str(),
    //                                header_cache_control.size());
    // typhoon::RequestHandler::Write(app, conn, header_pargma.c_str(),
    //                                header_pargma.size());
    // typhoon::RequestHandler::Write(app, conn, header_content_type.c_str(),
    //                                header_content_type.size());
    // typhoon::RequestHandler::Write(app, conn, header_terminator.c_str(),
    //                                header_terminator.size());
    // typhoon::RequestHandler::Response(app, conn, "ok");
    sleep(10);
  }
  std::shared_ptr<typhoon::Server> server_;
  ros::NodeHandle nh_;
  ros::Timer weather_timer_;
  std::mutex mutex_;
  std::vector<std::pair<typhoon::Application *, typhoon::Connection *>> conn_;
};

void TimerCb(const ros::TimerEvent &event) {
  std::cout << "WeatherTimerCb" << std::endl;
}

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "ros_typhoon");
  ros::NodeHandle nh;
  Data data;
  data.Start();
  ros::MultiThreadedSpinner spinner(1);
  spinner.spin();
  return 0;
}
