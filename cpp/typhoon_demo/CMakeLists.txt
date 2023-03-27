cmake_minimum_required(VERSION 3.5)
project(typhoon_demo)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(PkgConfig REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
pkg_check_modules(RosCpp REQUIRED roscpp)
pkg_check_modules(Nlohmann_json REQUIRED nlohmann_json)
pkg_check_modules(Typhoon typhoon)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${RosCpp_INCLUDE_DIRS}
  ${Typhoon_INCLUDE_DIRS}
  ${Nlohmann_json_INCLUDE_DIRS}
)

link_directories (
  ${Boost_LIBRARY_DIRS}
  ${RosCpp_LIBRARY_DIRS}
  ${Typhoon_LIBRARY_DIRS}
  ${Nlohmann_json_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)
add_executable(ros_typhoon_runner ros_main.cc)

target_link_libraries(${TARGET_NAME}_runner
  ${Nlohmann_json_LIBRARIES}
  ${Typhoon_LIBRARIES}
)

target_link_libraries(ros_typhoon_runner
  ${Nlohmann_json_LIBRARIES}
  ${Typhoon_LIBRARIES}
  ${Boost_LIBRARIES}
  ${RosCpp_LIBRARIES}
)

