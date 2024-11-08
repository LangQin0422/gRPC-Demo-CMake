cmake_minimum_required(VERSION 3.15)
project(Client)

# Make it a library so that it can be linked to executables
add_library(clientlib ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cc)

target_link_libraries(clientlib protolib)
