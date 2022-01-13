cmake_minimum_required(VERSION 3.5)
project(test_lib)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)

 # yaml-cpp
message("-----yaml------")
find_package(yaml-cpp REQUIRED)
message(${YAML_CPP_INCLUDE_DIR}) # /opt/tmaps/lib/cmake/yaml-cpp/../../../include
#message(${YAML_CPP_LIBRARY_DIRS}) # 暂时没有
message(${YAML_CPP_LIBRARIES}) # yaml-cpp

pkg_check_modules(Yaml-cpp REQUIRED yaml-cpp)
message(${Yaml-cpp_INCLUDE_DIRS}) # /opt/tmaps/include
message(${Yaml-cpp_LIBRARY_DIRS}) # /opt/tmaps/lib
message(${Yaml-cpp_LIBRARIES}) # yaml-cpp

## gtest
message("-----gtest------")
find_package(GTest REQUIRED)
message(${GTEST_INCLUDE_DIRS}) # /opt/tmaps/include
#message(${GTEST_LIBRARY_DIRS}) # 暂时没有
message(${GTEST_LIBRARIES}) # /opt/tmaps/lib/libgtest.so

pkg_check_modules(Gtest REQUIRED gtest)
message(${Gtest_INCLUDE_DIRS}) # /opt/tmaps/include
message(${Gtest_LIBRARY_DIRS}) # /opt/tmaps/lib
message(${Gtest_LIBRARIES}) # gtestpthread

### # gflags
message("-----gflags------")
find_package(gflags REQUIRED)
#message(${Gflags_INCLUDE_DIRS}) # /opt/tmaps/include
#message(${Gflags_LIBRARY_DIRS}) # /opt/tmaps/lib
#message(${Gflags_LIBRARIES}) # gflags

pkg_check_modules(Gflags REQUIRED gflags)
message(${Gflags_INCLUDE_DIRS}) # /opt/tmaps/include
message(${Gflags_LIBRARY_DIRS}) # /opt/tmaps/lib
message(${Gflags_LIBRARIES}) # gflags
#
## # glog
message("-----glog------")
find_package(glog REQUIRED)
#message(${Glog_INCLUDE_DIRS}) # /opt/tmaps/include
#message(${Glog_LIBRARY_DIRS}) # /opt/tmaps/lib
#message(${Glog_LIBRARIES}) # glog

pkg_check_modules(Glog REQUIRED libglog)
message(${Glog_INCLUDE_DIRS}) # /opt/tmaps/include
message(${Glog_LIBRARY_DIRS}) # /opt/tmaps/lib
message(${Glog_LIBRARIES}) # glog

## curl
message("-----Curl------")
find_package(CURL REQUIRED)
#message(${Curl_INCLUDE_DIRS})
#message(${Curl_LIBRARY_DIRS})
#message(${Curl_LIBRARIES})

pkg_check_modules(Curl REQUIRED libcurl)
message(${Curl_INCLUDE_DIRS}) # /opt/tmaps/include
message(${Curl_LIBRARY_DIRS}) # /opt/tmaps/lib
message(${Curl_LIBRARIES}) # curl

# # tmaps msg
message("-----msg------")
pkg_check_modules(TmapsMsg REQUIRED tmaps_msg)
message(${TmapsMsg_INCLUDE_DIRS}) # /opt/tmaps/include


add_executable(test_lib main.cpp)