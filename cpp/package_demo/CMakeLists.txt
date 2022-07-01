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
#                      CPack
# --------------------------------------------------------------
# 打包方式 
include(InstallRequiredSystemLibraries)
if (APPLE)
elseif (UNIX)
  set (CPACK_GENERATOR        "DEB")
  set (CPACK_SOURCE_GENERATOR "TGZ;ZIP")
endif ()

# system/architecture
if (WINDOWS)
  if (CMAKE_CL_64)
    set (CPACK_SYSTEM_NAME "win64")
  else ()
    set (CPACK_SYSTEM_NAME "win32")
  endif ()
  set (CPACK_PACKAGE_ARCHITECTURE)
elseif (APPLE)
  set (CPACK_PACKAGE_ARCHITECTURE "darwin")
else ()
  string (TOLOWER "${CMAKE_SYSTEM_NAME}" CPACK_SYSTEM_NAME)
  if (CMAKE_CXX_FLAGS MATCHES "-m32")
    set (CPACK_PACKAGE_ARCHITECTURE i386)
  else ()
    execute_process (
      COMMAND         dpkg --print-architecture
      RESULT_VARIABLE RV
      OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE
      )
    if (RV EQUAL 0)
          string (STRIP "${CPACK_PACKAGE_ARCHITECTURE}" CPACK_PACKAGE_ARCHITECTURE)
    else ()
      execute_process (COMMAND uname -m OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE)
      if (CPACK_PACKAGE_ARCHITECTURE MATCHES "x86_64")
            set (CPACK_PACKAGE_ARCHITECTURE amd64)
      else ()
        set (CPACK_PACKAGE_ARCHITECTURE i386)
      endif ()
    endif ()
  endif ()
endif ()

set(CPACK_PACKAGE_NAME   "${TARGET_NAME}")
set(CPACK_PACKAGE_CONTACT "job@minhang.me")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A HTTP library and server")
set(CPACK_INSTALL_PREFIX              "${CMAKE_INSTALL_PREFIX}")
set(CPACK_OUTPUT_FILE_PREFIX          "packages")
set(CPACK_PACKAGE_RELOCATABLE         TRUE)
set(CPACK_MONOLITHIC_INSTALL          TRUE)
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/minhanghuang/typhoon")
set(CPACK_PACKAGE_FILE_NAME   "lib${CPACK_PACKAGE_NAME}")
set(CPACK_PACKAGE_FILE_NAME   "${CPACK_PACKAGE_FILE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_PACKAGE_ARCHITECTURE}")

include(CPack)

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

