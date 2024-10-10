cmake_minimum_required(VERSION 3.5)
project(udp_demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
pkg_check_modules(Asio REQUIRED asio)

include_directories(
  ${Asio_INCLUDE_DIRS}
)

add_executable(server server.cc)
add_executable(server_cb server_cb.cc)
add_executable(client client.cc)
add_executable(broadcast_client broadcast_client.cc)

target_link_libraries(server
  Threads::Threads
)
target_link_libraries(server_cb
  Threads::Threads
)
target_link_libraries(client
  Threads::Threads
)
target_link_libraries(broadcast_client
  Threads::Threads
)
