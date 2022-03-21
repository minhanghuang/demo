// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from hdmap:msg/Lane.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "hdmap/msg/detail/lane__rosidl_typesupport_introspection_c.h"
#include "hdmap/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "hdmap/msg/detail/lane__functions.h"
#include "hdmap/msg/detail/lane__struct.h"


// Include directives for member types
// Member `lane_id`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void Lane__rosidl_typesupport_introspection_c__Lane_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  hdmap__msg__Lane__init(message_memory);
}

void Lane__rosidl_typesupport_introspection_c__Lane_fini_function(void * message_memory)
{
  hdmap__msg__Lane__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember Lane__rosidl_typesupport_introspection_c__Lane_message_member_array[1] = {
  {
    "lane_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(hdmap__msg__Lane, lane_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers Lane__rosidl_typesupport_introspection_c__Lane_message_members = {
  "hdmap__msg",  // message namespace
  "Lane",  // message name
  1,  // number of fields
  sizeof(hdmap__msg__Lane),
  Lane__rosidl_typesupport_introspection_c__Lane_message_member_array,  // message members
  Lane__rosidl_typesupport_introspection_c__Lane_init_function,  // function to initialize message memory (memory has to be allocated)
  Lane__rosidl_typesupport_introspection_c__Lane_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t Lane__rosidl_typesupport_introspection_c__Lane_message_type_support_handle = {
  0,
  &Lane__rosidl_typesupport_introspection_c__Lane_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_hdmap
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, hdmap, msg, Lane)() {
  if (!Lane__rosidl_typesupport_introspection_c__Lane_message_type_support_handle.typesupport_identifier) {
    Lane__rosidl_typesupport_introspection_c__Lane_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &Lane__rosidl_typesupport_introspection_c__Lane_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
