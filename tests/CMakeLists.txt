cmake_minimum_required(VERSION 3.15)
project(Tests)

add_executable(TestBasic ${CMAKE_CURRENT_SOURCE_DIR}/src/TestBasic.cc)

target_link_libraries(TestBasic clientlib)
target_include_directories(TestBasic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../client/src)
