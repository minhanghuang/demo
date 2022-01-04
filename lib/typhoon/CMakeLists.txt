cmake_minimum_required(VERSION 3.5)
project(typhoon VERSION 1.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

#####################################################################################
# pack
#####################################################################################
include(cmake/trunk_utils.cmake)
include(CMakePackageConfigHelpers)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)
include(GNUInstallDirs)
include(CTest)
include("${CMAKE_CURRENT_LIST_DIR}/cmake/typhoon.cmake")

set(PROJECT_DESCRIPTION "trunk typhoon")

if(NOT PACKAGE_HUB)
    trunk_make_package(${TARGET_NAME} ${PROJECT_VERSION} ${PROJECT_DESCRIPTION})
endif()

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

add_compile_options(-g)

#####################################################################################
# build
#####################################################################################
find_package(PkgConfig REQUIRED)
find_package(civetweb)
find_package(Boost REQUIRED COMPONENTS system thread)
pkg_check_modules(Nlohmann_json REQUIRED nlohmann_json)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Nlohmann_json_INCLUDE_DIRS}
    ${civetweb_INCLUDE_DIR}
)

link_directories (
    /usr/local/lib
    ${Boost_LIBRARY_DIRS}
    ${Nlohmann_json_LIBRARY_DIRS}
)

aux_source_directory(src/core TYPHOON_CORE_SOURCE_DIRS)

add_library(${TARGET_NAME} SHARED
    ${TYPHOON_CORE_SOURCE_DIRS}
)

target_link_libraries(${TARGET_NAME}
    libcivetweb-cpp.so
    libcivetweb.so
    ${Boost_LIBRARIES}
    ${Nlohmann_json_LIBRARIES}
)

add_subdirectory(example)

##################################################################################
# config
##################################################################################
set_target_properties(${TARGET_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    PROJECT_LABEL ${TARGET_NAME}
    DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
)

target_include_directories(${TARGET_NAME} INTERFACE # SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(TARGETS ${TARGET_NAME}
    EXPORT ${TARGET_NAME}-targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY src/
    DESTINATION include/typhoon/
    FILES_MATCHING
    PATTERN "*.h"
    PATTERN "*.hpp"
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/${TARGET_NAME}-config.cmake.in"
    "${PROJECT_BINARY_DIR}/${TARGET_NAME}-config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${TARGET_NAME}"
)

write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/${TARGET_NAME}-config-version.cmake"
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_file(${TARGET_NAME}.pc.in ${TARGET_NAME}.pc @ONLY)

install(EXPORT  ${TARGET_NAME}-targets
    DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${TARGET_NAME}"
)

install(FILES
    "${PROJECT_BINARY_DIR}/${TARGET_NAME}-config.cmake"
    "${PROJECT_BINARY_DIR}/${TARGET_NAME}-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${TARGET_NAME}"
)

install(FILES "${PROJECT_BINARY_DIR}/${TARGET_NAME}.pc"
    DESTINATION "${CMAKE_INSTALL_DATADIR}/pkgconfig"
)

