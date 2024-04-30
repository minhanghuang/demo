#include <iostream>
#include <mutex>
#include <string>
#include <unordered_map>

#include <boost/any.hpp>
#include <ros/init.h>
#include <ros/ros.h>
#include <std_msgs/String.h>

class Cache {
 private:
  struct RosBufferFrame {
    boost::any buffer;
    ros::Time time;
  };

 public:
  template <typename M>
  struct RosMsgFrame {
    M frame;
    ros::Time time;
  };

  Cache() : nh_(boost::make_shared<ros::NodeHandle>("~")) {}

  template <typename M>
  void RegisterSubscriber(const std::string& topic, uint32_t queue_size) {
    std::lock_guard<std::mutex> guard(buffer_mutex_);
    // 判断topic是否已经订阅
    if (topic.empty() || subs_.count(topic) > 0) {
      std::cerr << "repeated subscription topic: " << topic << std::endl;
      return;
    }

    // 移除buffer
    if (0 != buffers_.count(topic)) {
      buffers_.erase(topic);
    }

    // 订阅topic
    subs_[topic] =
        nh_->subscribe<M>(topic, queue_size,
                          boost::bind(&Cache::AnyCallback<M>, this, topic,
                                      boost::placeholders::_1));
  }

  template <typename M>
  RosMsgFrame<M> GetBuffer(const std::string& topic) {
    std::lock_guard<std::mutex> guard(buffer_mutex_);
    RosMsgFrame<M> frame;
    boost::shared_ptr<M const> msg_ptr = nullptr;

    if (buffers_.find(topic) == buffers_.end()) {
      std::cerr << "ros buffers could not find: " << topic << std::endl;
      return frame;
    }

    try {
      msg_ptr =
          boost::any_cast<boost::shared_ptr<M const>>(buffers_[topic].buffer);
    } catch (const boost::bad_any_cast& e) {
      std::cerr << "bad cast error: " << e.what() << std::endl;
      std::abort();
    }

    frame.frame = *msg_ptr;
    frame.time = buffers_[topic].time;
    return frame;
  }

 private:
  template <typename M>
  void AnyCallback(const std::string& topic,
                   const boost::shared_ptr<M const>& msg) {
    buffers_[topic] = RosBufferFrame{msg, ros::Time::now()};
  }

  ros::NodeHandlePtr nh_;

  std::mutex buffer_mutex_;

  std::unordered_map<std::string, ros::Subscriber> subs_;

  std::unordered_map<std::string, RosBufferFrame> buffers_;
};

int main(int argc, char** argv) {
  std::cout << "Hello, Ros Sub!" << std::endl;
  ros::init(argc, argv, "ros_demo_sub_node");
  const std::string topic_1 = "/demo/pub1";

  Cache cahce;
  cahce.RegisterSubscriber<std_msgs::String>(topic_1, 1);
  ros::Rate r(1);

  while (ros::ok()) {
    ros::spinOnce();
    auto data = cahce.GetBuffer<std_msgs::String>(topic_1);
    std::cout << "time: " << data.time.sec << std::endl;
    std::cout << "data: " << data.frame.data << std::endl;
    r.sleep();
  }

  return 0;
}
