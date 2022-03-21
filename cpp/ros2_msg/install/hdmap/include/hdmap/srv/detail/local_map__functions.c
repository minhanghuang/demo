// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from hdmap:srv/LocalMap.idl
// generated code does not contain a copyright notice
#include "hdmap/srv/detail/local_map__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Include directives for member types
// Member `id`
#include "rosidl_runtime_c/string_functions.h"

bool
hdmap__srv__LocalMap_Request__init(hdmap__srv__LocalMap_Request * msg)
{
  if (!msg) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__init(&msg->id)) {
    hdmap__srv__LocalMap_Request__fini(msg);
    return false;
  }
  // len
  return true;
}

void
hdmap__srv__LocalMap_Request__fini(hdmap__srv__LocalMap_Request * msg)
{
  if (!msg) {
    return;
  }
  // id
  rosidl_runtime_c__String__fini(&msg->id);
  // len
}

hdmap__srv__LocalMap_Request *
hdmap__srv__LocalMap_Request__create()
{
  hdmap__srv__LocalMap_Request * msg = (hdmap__srv__LocalMap_Request *)malloc(sizeof(hdmap__srv__LocalMap_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hdmap__srv__LocalMap_Request));
  bool success = hdmap__srv__LocalMap_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
hdmap__srv__LocalMap_Request__destroy(hdmap__srv__LocalMap_Request * msg)
{
  if (msg) {
    hdmap__srv__LocalMap_Request__fini(msg);
  }
  free(msg);
}


bool
hdmap__srv__LocalMap_Request__Sequence__init(hdmap__srv__LocalMap_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  hdmap__srv__LocalMap_Request * data = NULL;
  if (size) {
    data = (hdmap__srv__LocalMap_Request *)calloc(size, sizeof(hdmap__srv__LocalMap_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hdmap__srv__LocalMap_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hdmap__srv__LocalMap_Request__fini(&data[i - 1]);
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
hdmap__srv__LocalMap_Request__Sequence__fini(hdmap__srv__LocalMap_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hdmap__srv__LocalMap_Request__fini(&array->data[i]);
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

hdmap__srv__LocalMap_Request__Sequence *
hdmap__srv__LocalMap_Request__Sequence__create(size_t size)
{
  hdmap__srv__LocalMap_Request__Sequence * array = (hdmap__srv__LocalMap_Request__Sequence *)malloc(sizeof(hdmap__srv__LocalMap_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = hdmap__srv__LocalMap_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
hdmap__srv__LocalMap_Request__Sequence__destroy(hdmap__srv__LocalMap_Request__Sequence * array)
{
  if (array) {
    hdmap__srv__LocalMap_Request__Sequence__fini(array);
  }
  free(array);
}


bool
hdmap__srv__LocalMap_Response__init(hdmap__srv__LocalMap_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  return true;
}

void
hdmap__srv__LocalMap_Response__fini(hdmap__srv__LocalMap_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
}

hdmap__srv__LocalMap_Response *
hdmap__srv__LocalMap_Response__create()
{
  hdmap__srv__LocalMap_Response * msg = (hdmap__srv__LocalMap_Response *)malloc(sizeof(hdmap__srv__LocalMap_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(hdmap__srv__LocalMap_Response));
  bool success = hdmap__srv__LocalMap_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
hdmap__srv__LocalMap_Response__destroy(hdmap__srv__LocalMap_Response * msg)
{
  if (msg) {
    hdmap__srv__LocalMap_Response__fini(msg);
  }
  free(msg);
}


bool
hdmap__srv__LocalMap_Response__Sequence__init(hdmap__srv__LocalMap_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  hdmap__srv__LocalMap_Response * data = NULL;
  if (size) {
    data = (hdmap__srv__LocalMap_Response *)calloc(size, sizeof(hdmap__srv__LocalMap_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = hdmap__srv__LocalMap_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        hdmap__srv__LocalMap_Response__fini(&data[i - 1]);
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
hdmap__srv__LocalMap_Response__Sequence__fini(hdmap__srv__LocalMap_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      hdmap__srv__LocalMap_Response__fini(&array->data[i]);
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

hdmap__srv__LocalMap_Response__Sequence *
hdmap__srv__LocalMap_Response__Sequence__create(size_t size)
{
  hdmap__srv__LocalMap_Response__Sequence * array = (hdmap__srv__LocalMap_Response__Sequence *)malloc(sizeof(hdmap__srv__LocalMap_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = hdmap__srv__LocalMap_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
hdmap__srv__LocalMap_Response__Sequence__destroy(hdmap__srv__LocalMap_Response__Sequence * array)
{
  if (array) {
    hdmap__srv__LocalMap_Response__Sequence__fini(array);
  }
  free(array);
}
