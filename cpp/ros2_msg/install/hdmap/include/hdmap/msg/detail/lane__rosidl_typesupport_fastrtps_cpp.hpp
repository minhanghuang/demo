// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from hdmap:msg/Lane.idl
// generated code does not contain a copyright notice

#ifndef HDMAP__MSG__DETAIL__LANE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define HDMAP__MSG__DETAIL__LANE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "hdmap/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "hdmap/msg/detail/lane__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace hdmap
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hdmap
cdr_serialize(
  const hdmap::msg::Lane & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hdmap
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  hdmap::msg::Lane & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hdmap
get_serialized_size(
  const hdmap::msg::Lane & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hdmap
max_serialized_size_Lane(
  bool & full_bounded,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace hdmap

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_hdmap
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, hdmap, msg, Lane)();

#ifdef __cplusplus
}
#endif

#endif  // HDMAP__MSG__DETAIL__LANE__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
