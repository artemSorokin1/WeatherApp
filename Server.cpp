#include "Server.hpp"

int main(int argc, char* argv[]) {
    Server server;

    std::thread connectionThread([&server](){
        server.connectionHandler();
    });
    std::thread communicateThread([&server](){
       server.communicateWithClient();
    });

    connectionThread.join();
    connectionThread.join();

    return 0;
}
