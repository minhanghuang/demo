cmake_minimum_required(VERSION 3.5.1)
project(absl_demo VERSION 0.0.0)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(absl REQUIRED)
# pkg_check_modules(name REQUIRED lib)

# include_directories(
  # ${name_INCLUDE_DIRS}
# )

# link_directories (
  # ${name_LIBRARY_DIRS}
# )

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
  # ${name_LIBRARIES}
  # absl::time
  # absl::algorithm
  absl::meta
)
