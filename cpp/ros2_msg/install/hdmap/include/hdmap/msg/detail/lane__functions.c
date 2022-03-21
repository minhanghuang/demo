// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hdmap:msg/Lane.idl
// generated code does not contain a copyright notice
#include "hdmap/msg/detail/lane__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `lane_id`
#include "rosidl_runtime_c/string_functions.h"

bool
hdmap__msg__Lane__init(hdmap__msg__Lane * msg)
{
  if (!msg) {
    return false;
  }
  // lane_id
  if (!rosidl_runtime_c__String__init(&msg->lane_id)) {
    hdmap__msg__Lane__fini(msg);
    return false;
  }
  return true;
}

void
hdmap__msg__Lane__fini(hdmap__msg__Lane * msg)
{
  if (!msg) {
    return;
  }
  // lane_id
  rosidl_runtime_c__String__fini(&msg->lane_id);
}

hdmap__msg__Lane *
hdmap__msg__Lane__create()
{
  hdmap__msg__Lane * msg = (hdmap__msg__Lane *)malloc(sizeof(hdmap__msg__Lane));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hdmap__msg__Lane));
  bool success = hdmap__msg__Lane__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
hdmap__msg__Lane__destroy(hdmap__msg__Lane * msg)
{
  if (msg) {
    hdmap__msg__Lane__fini(msg);
  }
  free(msg);
}


bool
hdmap__msg__Lane__Sequence__init(hdmap__msg__Lane__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  hdmap__msg__Lane * data = NULL;
  if (size) {
    data = (hdmap__msg__Lane *)calloc(size, sizeof(hdmap__msg__Lane));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hdmap__msg__Lane__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hdmap__msg__Lane__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
hdmap__msg__Lane__Sequence__fini(hdmap__msg__Lane__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hdmap__msg__Lane__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

hdmap__msg__Lane__Sequence *
hdmap__msg__Lane__Sequence__create(size_t size)
{
  hdmap__msg__Lane__Sequence * array = (hdmap__msg__Lane__Sequence *)malloc(sizeof(hdmap__msg__Lane__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = hdmap__msg__Lane__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
hdmap__msg__Lane__Sequence__destroy(hdmap__msg__Lane__Sequence * array)
{
  if (array) {
    hdmap__msg__Lane__Sequence__fini(array);
  }
  free(array);
}
