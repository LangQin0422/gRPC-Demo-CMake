#include "Client.h"
#include <grpcpp/create_channel.h>
#include <grpcpp/client_context.h>
#include "absl/log/log.h"

#define SERVER_ADDRESS "localhost:50051"

Client::Client()
    : stub_(Server::NewStub(grpc::CreateChannel(SERVER_ADDRESS, grpc::InsecureChannelCredentials()))) {}

bool Client::Put(const std::string& key, const std::string& value) {
    grpc::ClientContext context;
    PutArgs args;
    PutReply reply;

    args.set_key(key);
    args.set_value(value);

    grpc::Status status = stub_->Put(&context, args, &reply);

    if (!status.ok()) {
        ABSL_LOG(INFO) << "[PUT] Error: " << status.error_message();
        return false;
    }

    ABSL_LOG(INFO) << "[PUT] Key: " << key << ", Value: " << value;
    return true;
}

bool Client::Get(const std::string& key, std::string& value) {
    grpc::ClientContext context;
    GetArgs args;
    GetReply reply;

    args.set_key(key);

    grpc::Status status = stub_->Get(&context, args, &reply);

    if (!status.ok()) {
        ABSL_LOG(INFO) << "[GET] Error: " << status.error_message();
        return false;
    }

    value = reply.value();
    ABSL_LOG(INFO) << "[GET] Key: " << key << ", Value: " << value;
    return true;
}
