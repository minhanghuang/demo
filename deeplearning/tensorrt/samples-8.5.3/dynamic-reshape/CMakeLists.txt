cmake_minimum_required(VERSION 3.5.1)

project(dynamic-reshape-sample VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})

file(GLOB SRC
  "*.cc"
)

add_executable(${TARGET_NAME}
  ${SRC}
)

target_link_libraries(${TARGET_NAME}
  ${CUDA_LIBRARIES}
  ${TENSORRT_LIBRARIES}
)

install(TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME}-targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

