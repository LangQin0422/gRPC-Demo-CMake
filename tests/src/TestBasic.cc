#include "Client.h"

int main() {
    Client client;
    client.Put("key", "value");

    std::string value;
    client.Get("key", value);
}
