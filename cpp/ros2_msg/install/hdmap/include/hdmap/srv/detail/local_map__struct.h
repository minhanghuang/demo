// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from hdmap:srv/LocalMap.idl
// generated code does not contain a copyright notice

#ifndef HDMAP__SRV__DETAIL__LOCAL_MAP__STRUCT_H_
#define HDMAP__SRV__DETAIL__LOCAL_MAP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'id'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/LocalMap in the package hdmap.
typedef struct hdmap__srv__LocalMap_Request
{
  rosidl_runtime_c__String id;
  int64_t len;
} hdmap__srv__LocalMap_Request;

// Struct for a sequence of hdmap__srv__LocalMap_Request.
typedef struct hdmap__srv__LocalMap_Request__Sequence
{
  hdmap__srv__LocalMap_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hdmap__srv__LocalMap_Request__Sequence;


// Constants defined in the message

// Struct defined in srv/LocalMap in the package hdmap.
typedef struct hdmap__srv__LocalMap_Response
{
  int64_t status;
} hdmap__srv__LocalMap_Response;

// Struct for a sequence of hdmap__srv__LocalMap_Response.
typedef struct hdmap__srv__LocalMap_Response__Sequence
{
  hdmap__srv__LocalMap_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} hdmap__srv__LocalMap_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // HDMAP__SRV__DETAIL__LOCAL_MAP__STRUCT_H_
