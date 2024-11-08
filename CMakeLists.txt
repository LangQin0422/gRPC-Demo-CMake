cmake_minimum_required(VERSION 3.15)

# Project name
project(grpc-demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure C++ standard is propagated to Abseil
set(ABSL_PROPAGATE_CXX_STD ON)

# Find necessary packages
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

# Link proto definitions
add_library(protolib proto/server.proto)
target_link_libraries(protolib gRPC::grpc++)
target_include_directories(protolib PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)

# Generate gRPC templates
protobuf_generate(TARGET protolib LANGUAGE cpp)
protobuf_generate(TARGET protolib LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}")

# Link sub directory/projects
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(tests)
