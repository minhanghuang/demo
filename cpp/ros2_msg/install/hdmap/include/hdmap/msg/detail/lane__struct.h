// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hdmap:msg/Lane.idl
// generated code does not contain a copyright notice

#ifndef HDMAP__MSG__DETAIL__LANE__STRUCT_H_
#define HDMAP__MSG__DETAIL__LANE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'lane_id'
#include "rosidl_runtime_c/string.h"

// Struct defined in msg/Lane in the package hdmap.
typedef struct hdmap__msg__Lane
{
  rosidl_runtime_c__String lane_id;
} hdmap__msg__Lane;

// Struct for a sequence of hdmap__msg__Lane.
typedef struct hdmap__msg__Lane__Sequence
{
  hdmap__msg__Lane * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hdmap__msg__Lane__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HDMAP__MSG__DETAIL__LANE__STRUCT_H_
