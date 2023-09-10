cmake_minimum_required(VERSION 3.5.1)

project(mnist-sample VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})

file(GLOB SRC
  "src/*.cc"
)

add_executable(${TARGET_NAME}
  main.cc
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

