cmake_minimum_required(VERSION 3.5.1)

project(typhoon VERSION 1.2.3)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)

include_directories(
  ${Boost_INCLUDE_DIRS}
)

add_library(${TARGET_NAME} SHARED
  src/node.cc
)

target_link_libraries(${TARGET_NAME}
  ${Boost_LIBRARIES}
)

# --------------------------------------------------------------
#                       package 
# --------------------------------------------------------------
configure_file(
  cmake/${PROJECT_NAME}.pc.in
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc
  @ONLY
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${TARGET_NAME}-config.cmake.in"
  ${TARGET_NAME}-config.cmake
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME}"
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR TARGET_NAME
)

write_basic_package_version_file(${TARGET_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

message(${PROJECT_VERSION})

install(
  FILES 
    "${PROJECT_BINARY_DIR}/${TARGET_NAME}.pc"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/pkgconfig"
)

install(FILES 
  "${PROJECT_BINARY_DIR}/${TARGET_NAME}-config.cmake"
  "${PROJECT_BINARY_DIR}/${TARGET_NAME}-config-version.cmake"
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${TARGET_NAME}"
)

install(EXPORT ${TARGET_NAME}-targets
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${TARGET_NAME}"
)
install(DIRECTORY src/
  DESTINATION include/typhoon
  FILES_MATCHING
  PATTERN "*.h"
  PATTERN "*.hpp"
  PATTERN "*.inl"
)

install(TARGETS ${TARGET_NAME} 
  EXPORT ${TARGET_NAME}-targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

