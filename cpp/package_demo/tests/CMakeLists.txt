cmake_minimum_required(VERSION 3.5.1)
project(package_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(typhoon REQUIRED)
pkg_check_modules(Typhoon REQUIRED typhoon)

message("----find_package----")
message(${typhoon_INCLUDE_DIRS})
message(${typhoon_LIBRARY_DIRS})
message(${typhoon_LIBRARIES})
message("--------")

message("----pkg_check_modules----")
message(${Typhoon_INCLUDE_DIRS})
message(${Typhoon_LIBRARY_DIRS})
message(${Typhoon_LIBRARIES})
message("--------")

include_directories(
  ${Typhoon_INCLUDE_DIRS}
)

link_directories(
  ${Typhoon_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
  ${Typhoon_LIBRARIES}
)

