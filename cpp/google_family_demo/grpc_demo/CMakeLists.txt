cmake_minimum_required(VERSION 3.18)

project(grpc_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PROTOFILE_CACHE ON CACHE BOOL "generate v2x protofile flag.")

find_package(PkgConfig REQUIRED)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG)
if(gRPC_FOUND)
  message(STATUS "find grpc cmake config")
  list(APPEND GRPCPP_LIBRARIES gRPC::grpc++)
else ()
  find_package(PkgConfig REQUIRED)
  pkg_search_module(GRPC REQUIRED grpc)
  pkg_search_module(GRPCPP REQUIRED grpc++)
  list(APPEND GRPCPP_INCLUDE_DIRS ${GRPC_INCLUDE_DIRS})
  list(APPEND GRPCPP_LIBRARIES ${GRPC_LIBRARIES})
endif()


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Protobuf_INCLUDE_DIRS}
  ${GRPCPP_INCLUDE_DIRS}
)

link_directories (
  ${Protobuf_LIBRARY_DIRS}
  ${GRPCPP_LIBRARY_DIRS}
)

file(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")


if(${PROTOFILE_CACHE})
  set(PROTOFILE_CACHE OFF CACHE BOOL "generate protofile flag." FORCE)
  EXECUTE_PROCESS(
    COMMAND
    which grpc_cpp_plugin # 获取grpc plugin路径
    OUTPUT_VARIABLE GRPC_CPP_PLUGIN
  )
  string(REGEX REPLACE "\n" "" GRPC_CPP_PLUGIN "${GRPC_CPP_PLUGIN}") # 删除GRPC_CPP_PLUGIN变量中的换行符
  FOREACH(FIL ${PROTO_FILES})
    message("### generate proto file: ${FIL}")
    GET_FILENAME_COMPONENT(FIL_WE ${FIL} NAME_WE)
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FIL})
    string(REGEX REPLACE "(.+)\\${FILE_NAME}.*" "\\1" FILE_PATH ${FIL})
    EXECUTE_PROCESS(
      COMMAND
      ${PROTOBUF_PROTOC_EXECUTABLE}
      -I${CMAKE_CURRENT_SOURCE_DIR}
      --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}       # protobuf file
      --grpc_out=${CMAKE_CURRENT_SOURCE_DIR}      # grpc file
      --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN} # grpc plugin
      ${FIL}
    )
  ENDFOREACH()
endif(${PROTOFILE_CACHE})

file(GLOB sources
  "proto/*.cc"
)

add_executable(simple_server
  ${sources}
  simple/server.cc
)

add_executable(simple_client
  ${sources}
  simple/client.cc
)

target_link_libraries(simple_server
  ${Protobuf_LIBRARIES}
  ${GRPCPP_LIBRARIES}

)

target_link_libraries(simple_client
  ${Protobuf_LIBRARIES}
  ${GRPCPP_LIBRARIES}
)
