cmake_minimum_required(VERSION 3.21)

project(gRPC-demo C CXX)
set(CMAKE_CXX_STANDARD 17)

include(cmake/find_grpc.cmake)
include(cmake/compile_grpc_proto.cmake)


add_subdirectory(echo)
