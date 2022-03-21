// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hdmap:msg/Lane.idl
// generated code does not contain a copyright notice

#ifndef HDMAP__MSG__DETAIL__LANE__BUILDER_HPP_
#define HDMAP__MSG__DETAIL__LANE__BUILDER_HPP_

#include "hdmap/msg/detail/lane__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace hdmap
{

namespace msg
{

namespace builder
{

class Init_Lane_lane_id
{
public:
  Init_Lane_lane_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hdmap::msg::Lane lane_id(::hdmap::msg::Lane::_lane_id_type arg)
  {
    msg_.lane_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hdmap::msg::Lane msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::hdmap::msg::Lane>()
{
  return hdmap::msg::builder::Init_Lane_lane_id();
}

}  // namespace hdmap

#endif  // HDMAP__MSG__DETAIL__LANE__BUILDER_HPP_
