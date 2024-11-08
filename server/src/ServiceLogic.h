#ifndef SERVER_H_
#define SERVER_H_

#include <grpcpp/grpcpp.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/client_context.h>

#include "proto/server.pb.h"
#include "proto/server.grpc.pb.h"

class ServiceLogic final : public Server::Service {
public:
    ServiceLogic() {};

    grpc::Status Put(grpc::ServerContext* context, const PutArgs* args, PutReply* reply) override {
        store_[args->key()] = args->value();

        ABSL_LOG(INFO) << absl::StrFormat("[PUT] Key: %s, Value: %s", args->key(), args->value());

        return grpc::Status::OK;
    }

    grpc::Status Get(grpc::ServerContext* context, const GetArgs* args, GetReply* reply) override {
        if (store_.find(args->key()) == store_.end()) {
            return grpc::Status(grpc::StatusCode::NOT_FOUND, "Key not found");
        }

        reply->set_value(store_[args->key()]);

        ABSL_LOG(INFO) << absl::StrFormat("[GET] Key: %s, Value: %s", args->key(), reply->value());

        return grpc::Status::OK;
    }

private:
    std::unordered_map<std::string, std::string> store_;
};

#endif