cmake_minimum_required(VERSION 3.15)
project(Server)

add_executable(Server ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)

target_link_libraries(Server protolib)
target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
