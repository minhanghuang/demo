cmake_minimum_required(VERSION 3.19)
project(sqlite3_orm_demo)

set(CMAKE_CXX_STANDARD 14)

set(TARGET_NAME ${PROJECT_NAME})

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(SQLiteCpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
pkg_check_modules(NLOHMANNJSON REQUIRED nlohmann_json)
pkg_check_modules(SQLite3 REQUIRED sqlite3)
#pkg_check_modules(SQLITECPP REQUIRED SQLiteCpp)
#message(${SQLite3_INCLUDE_DIRS})
#message(${SQLite3_LIBRARY_DIRS})
#message(${SQLite3_LIBRARIES})

include_directories(
        ${Boost_INCLUDE_DIRS}
        ${NLOHMANNJSON_INCLUDE_DIRS}
        ${SQLite3_INCLUDE_DIRS}
)

link_directories (
        ${Boost_LIBRARY_DIRS}
        ${NLOHMANNJSON_LIBRARY_DIRS}
        ${SQLite3_LIBRARY_DIRS}
)

add_executable(${TARGET_NAME}_runner main.cc)

target_link_libraries(${TARGET_NAME}_runner
        ${Boost_LIBRARIES}
        ${NLOHMANNJSON_LIBRARIES}
        ${SQLite3_LIBRARIES}
        )
