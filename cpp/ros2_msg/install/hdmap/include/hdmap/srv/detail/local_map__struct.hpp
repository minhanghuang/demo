// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from hdmap:srv/LocalMap.idl
// generated code does not contain a copyright notice

#ifndef HDMAP__SRV__DETAIL__LOCAL_MAP__STRUCT_HPP_
#define HDMAP__SRV__DETAIL__LOCAL_MAP__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__hdmap__srv__LocalMap_Request __attribute__((deprecated))
#else
# define DEPRECATED__hdmap__srv__LocalMap_Request __declspec(deprecated)
#endif

namespace hdmap
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct LocalMap_Request_
{
  using Type = LocalMap_Request_<ContainerAllocator>;

  explicit LocalMap_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->len = 0ll;
    }
  }

  explicit LocalMap_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->len = 0ll;
    }
  }

  // field types and members
  using _id_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _id_type id;
  using _len_type =
    int64_t;
  _len_type len;

  // setters for named parameter idiom
  Type & set__id(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__len(
    const int64_t & _arg)
  {
    this->len = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hdmap::srv::LocalMap_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const hdmap::srv::LocalMap_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hdmap::srv::LocalMap_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hdmap::srv::LocalMap_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hdmap::srv::LocalMap_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hdmap::srv::LocalMap_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hdmap::srv::LocalMap_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hdmap::srv::LocalMap_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hdmap::srv::LocalMap_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hdmap::srv::LocalMap_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hdmap__srv__LocalMap_Request
    std::shared_ptr<hdmap::srv::LocalMap_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hdmap__srv__LocalMap_Request
    std::shared_ptr<hdmap::srv::LocalMap_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LocalMap_Request_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->len != other.len) {
      return false;
    }
    return true;
  }
  bool operator!=(const LocalMap_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LocalMap_Request_

// alias to use template instance with default allocator
using LocalMap_Request =
  hdmap::srv::LocalMap_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace hdmap


#ifndef _WIN32
# define DEPRECATED__hdmap__srv__LocalMap_Response __attribute__((deprecated))
#else
# define DEPRECATED__hdmap__srv__LocalMap_Response __declspec(deprecated)
#endif

namespace hdmap
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct LocalMap_Response_
{
  using Type = LocalMap_Response_<ContainerAllocator>;

  explicit LocalMap_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0ll;
    }
  }

  explicit LocalMap_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0ll;
    }
  }

  // field types and members
  using _status_type =
    int64_t;
  _status_type status;

  // setters for named parameter idiom
  Type & set__status(
    const int64_t & _arg)
  {
    this->status = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    hdmap::srv::LocalMap_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const hdmap::srv::LocalMap_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<hdmap::srv::LocalMap_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<hdmap::srv::LocalMap_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      hdmap::srv::LocalMap_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<hdmap::srv::LocalMap_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      hdmap::srv::LocalMap_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<hdmap::srv::LocalMap_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<hdmap::srv::LocalMap_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<hdmap::srv::LocalMap_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__hdmap__srv__LocalMap_Response
    std::shared_ptr<hdmap::srv::LocalMap_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__hdmap__srv__LocalMap_Response
    std::shared_ptr<hdmap::srv::LocalMap_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LocalMap_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    return true;
  }
  bool operator!=(const LocalMap_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LocalMap_Response_

// alias to use template instance with default allocator
using LocalMap_Response =
  hdmap::srv::LocalMap_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace hdmap

namespace hdmap
{

namespace srv
{

struct LocalMap
{
  using Request = hdmap::srv::LocalMap_Request;
  using Response = hdmap::srv::LocalMap_Response;
};

}  // namespace srv

}  // namespace hdmap

#endif  // HDMAP__SRV__DETAIL__LOCAL_MAP__STRUCT_HPP_
