#include "ServiceLogic.h"

#define DEFAULT_PORT "50051"

int main() {
    grpc::EnableDefaultHealthCheckService(true);
    grpc::ServerBuilder builder;

    ServiceLogic service;
    builder.AddListeningPort(absl::StrFormat("0.0.0.0:%s", DEFAULT_PORT), grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    ABSL_LOG(INFO) << absl::StrFormat("Controller is listening on 0.0.0.0:%s", DEFAULT_PORT);

    server->Wait();
    return 0;
}
