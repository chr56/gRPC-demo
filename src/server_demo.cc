#include <iostream>
#include <string>

#include <grpcpp/grpcpp.h>

#include "demo.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using convention::Demo;
using convention::GreetingReply;
using convention::GreetingRequest;

class DemoServiceImpl final : public Demo::Service
{

  Status Echo(ServerContext *context, const GreetingRequest *request, GreetingReply *reply) override
  {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->message());
    return Status::OK;
  }
};

void RunServer(void)
{
  DemoServiceImpl service;

  const char *address = "0.0.0.0:12345";

  ServerBuilder builder;
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());

  std::cout << "Server listening on " << address << std::endl;

  server->Wait();
}

int main(int argc, char **argv)
{
  RunServer();
  return 0;
}
