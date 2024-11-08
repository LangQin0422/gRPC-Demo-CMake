#ifndef CLIENT_H_
#define CLIENT_H_

#include <grpcpp/grpcpp.h>
#include "proto/server.pb.h"
#include "proto/server.grpc.pb.h"

class Client {
public:
    Client();

    bool Put(const std::string& key, const std::string& value);
    bool Get(const std::string& key, std::string& value);

private:
    std::unique_ptr<Server::Stub> stub_;
};

#endif // CLIENT_H
