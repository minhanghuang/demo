// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hdmap:srv/LocalMap.idl
// generated code does not contain a copyright notice

#ifndef HDMAP__SRV__DETAIL__LOCAL_MAP__TRAITS_HPP_
#define HDMAP__SRV__DETAIL__LOCAL_MAP__TRAITS_HPP_

#include "hdmap/srv/detail/local_map__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<hdmap::srv::LocalMap_Request>()
{
  return "hdmap::srv::LocalMap_Request";
}

template<>
inline const char * name<hdmap::srv::LocalMap_Request>()
{
  return "hdmap/srv/LocalMap_Request";
}

template<>
struct has_fixed_size<hdmap::srv::LocalMap_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<hdmap::srv::LocalMap_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<hdmap::srv::LocalMap_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<hdmap::srv::LocalMap_Response>()
{
  return "hdmap::srv::LocalMap_Response";
}

template<>
inline const char * name<hdmap::srv::LocalMap_Response>()
{
  return "hdmap/srv/LocalMap_Response";
}

template<>
struct has_fixed_size<hdmap::srv::LocalMap_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<hdmap::srv::LocalMap_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<hdmap::srv::LocalMap_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<hdmap::srv::LocalMap>()
{
  return "hdmap::srv::LocalMap";
}

template<>
inline const char * name<hdmap::srv::LocalMap>()
{
  return "hdmap/srv/LocalMap";
}

template<>
struct has_fixed_size<hdmap::srv::LocalMap>
  : std::integral_constant<
    bool,
    has_fixed_size<hdmap::srv::LocalMap_Request>::value &&
    has_fixed_size<hdmap::srv::LocalMap_Response>::value
  >
{
};

template<>
struct has_bounded_size<hdmap::srv::LocalMap>
  : std::integral_constant<
    bool,
    has_bounded_size<hdmap::srv::LocalMap_Request>::value &&
    has_bounded_size<hdmap::srv::LocalMap_Response>::value
  >
{
};

template<>
struct is_service<hdmap::srv::LocalMap>
  : std::true_type
{
};

template<>
struct is_service_request<hdmap::srv::LocalMap_Request>
  : std::true_type
{
};

template<>
struct is_service_response<hdmap::srv::LocalMap_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // HDMAP__SRV__DETAIL__LOCAL_MAP__TRAITS_HPP_
