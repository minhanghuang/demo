// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from hdmap:srv/LocalMap.idl
// generated code does not contain a copyright notice

#ifndef HDMAP__SRV__DETAIL__LOCAL_MAP__BUILDER_HPP_
#define HDMAP__SRV__DETAIL__LOCAL_MAP__BUILDER_HPP_

#include "hdmap/srv/detail/local_map__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace hdmap
{

namespace srv
{

namespace builder
{

class Init_LocalMap_Request_len
{
public:
  explicit Init_LocalMap_Request_len(::hdmap::srv::LocalMap_Request & msg)
  : msg_(msg)
  {}
  ::hdmap::srv::LocalMap_Request len(::hdmap::srv::LocalMap_Request::_len_type arg)
  {
    msg_.len = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hdmap::srv::LocalMap_Request msg_;
};

class Init_LocalMap_Request_id
{
public:
  Init_LocalMap_Request_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocalMap_Request_len id(::hdmap::srv::LocalMap_Request::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_LocalMap_Request_len(msg_);
  }

private:
  ::hdmap::srv::LocalMap_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::hdmap::srv::LocalMap_Request>()
{
  return hdmap::srv::builder::Init_LocalMap_Request_id();
}

}  // namespace hdmap


namespace hdmap
{

namespace srv
{

namespace builder
{

class Init_LocalMap_Response_status
{
public:
  Init_LocalMap_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::hdmap::srv::LocalMap_Response status(::hdmap::srv::LocalMap_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::hdmap::srv::LocalMap_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::hdmap::srv::LocalMap_Response>()
{
  return hdmap::srv::builder::Init_LocalMap_Response_status();
}

}  // namespace hdmap

#endif  // HDMAP__SRV__DETAIL__LOCAL_MAP__BUILDER_HPP_
