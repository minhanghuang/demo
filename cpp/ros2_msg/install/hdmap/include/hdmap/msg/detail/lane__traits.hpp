// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from hdmap:msg/Lane.idl
// generated code does not contain a copyright notice

#ifndef HDMAP__MSG__DETAIL__LANE__TRAITS_HPP_
#define HDMAP__MSG__DETAIL__LANE__TRAITS_HPP_

#include "hdmap/msg/detail/lane__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<hdmap::msg::Lane>()
{
  return "hdmap::msg::Lane";
}

template<>
inline const char * name<hdmap::msg::Lane>()
{
  return "hdmap/msg/Lane";
}

template<>
struct has_fixed_size<hdmap::msg::Lane>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<hdmap::msg::Lane>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<hdmap::msg::Lane>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // HDMAP__MSG__DETAIL__LANE__TRAITS_HPP_
