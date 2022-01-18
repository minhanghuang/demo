cmake_minimum_required(VERSION 3.5)
project(cmake_demo)
set(TARGET_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${TARGET_NAME} main.cpp)

install(TARGETS ${TARGET_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY conf DESTINATION
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/conf"
)

file(COPY conf/ DESTINATION ${CMAKE_BINARY_DIR}/devel/share/${PROJECT_NAME}/conf)

# 对文件追加内容

file(APPEND haha.txt "message to write\n")
file(APPEND haha.txt "message to write")
file(APPEND haha.txt "message to write34")
