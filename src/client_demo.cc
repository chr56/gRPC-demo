#include <iostream>
#include <string>

#include "absl/strings/str_format.h"

#include <grpcpp/grpcpp.h>

#include "demo.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using convention::Demo;
using convention::GreetingReply;
using convention::GreetingRequest;

class DemoClient
{
public:
  DemoClient(std::shared_ptr<Channel> channel)
      : stub_(Demo::NewStub(channel)) {}

  std::string echo(const std::string &message)
  {

    ClientContext context;

    GreetingRequest request;
    request.set_message(message);

    GreetingReply reply;

    Status status = stub_->Echo(&context, request, &reply);

    if (status.ok())
    {
      return reply.message();
    }
    else
    {
      std::cerr << status.error_code() << ": " << std::endl
                << status.error_message() << std::endl;
      return "ERROR";
    }
  }

private:
  std::unique_ptr<Demo::Stub> stub_;
};

int main(int argc, char **argv)
{

  DemoClient greeter(
      grpc::CreateChannel("localhost:12345", grpc::InsecureChannelCredentials()));

  std::string data("world");
  std::string reply = greeter.echo(data);

  std::cout << reply << std::endl;

  return 0;
}
