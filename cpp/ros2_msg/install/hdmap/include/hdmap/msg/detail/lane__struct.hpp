// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hdmap:msg/Lane.idl
// generated code does not contain a copyright notice

#ifndef HDMAP__MSG__DETAIL__LANE__STRUCT_HPP_
#define HDMAP__MSG__DETAIL__LANE__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__hdmap__msg__Lane __attribute__((deprecated))
#else
# define DEPRECATED__hdmap__msg__Lane __declspec(deprecated)
#endif

namespace hdmap
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Lane_
{
  using Type = Lane_<ContainerAllocator>;

  explicit Lane_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lane_id = "";
    }
  }

  explicit Lane_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : lane_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lane_id = "";
    }
  }

  // field types and members
  using _lane_id_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _lane_id_type lane_id;

  // setters for named parameter idiom
  Type & set__lane_id(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->lane_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hdmap::msg::Lane_<ContainerAllocator> *;
  using ConstRawPtr =
    const hdmap::msg::Lane_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hdmap::msg::Lane_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hdmap::msg::Lane_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hdmap::msg::Lane_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hdmap::msg::Lane_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hdmap::msg::Lane_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hdmap::msg::Lane_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hdmap::msg::Lane_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hdmap::msg::Lane_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hdmap__msg__Lane
    std::shared_ptr<hdmap::msg::Lane_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hdmap__msg__Lane
    std::shared_ptr<hdmap::msg::Lane_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Lane_ & other) const
  {
    if (this->lane_id != other.lane_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const Lane_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Lane_

// alias to use template instance with default allocator
using Lane =
  hdmap::msg::Lane_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace hdmap

#endif  // HDMAP__MSG__DETAIL__LANE__STRUCT_HPP_
