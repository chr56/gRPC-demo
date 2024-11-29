cmake_minimum_required(VERSION 3.21)

project(gRPC-demo C CXX)
set(CMAKE_CXX_STANDARD 17)

include(cmake/find_grpc.cmake)
include(cmake/compile_grpc_proto.cmake)

compile_grpc_proto(grpc_proto_demo demo "src/demo.proto")

foreach(_target_
  client_demo server_demo)
  add_executable(${_target_} "src/${_target_}.cc")
  target_link_libraries(${_target_}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    grpc_proto_demo
    absl::check
    absl::log
  )  
endforeach()
