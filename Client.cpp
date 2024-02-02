#include "Client.h"

bool Client::tryToEnter(const UserData & userData) {
    zmq::context_t ctx(1);
    zmq::socket_t connectServerSocket(ctx, zmq::socket_type::req);
    connectServerSocket.connect(address + std::to_string(SERVER_CONNECTION_PORT));
    connectServerSocket.set(zmq::sockopt::sndtimeo, 2000);
    std::string serializeUserData;
    zmq_api::serializeUser(userData, serializeUserData);
    zmq_api::sendMessage(connectServerSocket, serializeUserData);
    std::string reply = zmq_api::receiveMessage(connectServerSocket);
    if (reply == "Success") {
        return true;
    }
    return false;
}

std::string Client::tryToRegister(const UserData & userData) {
    zmq::context_t ctx(1);
    zmq::socket_t connectServerSocket(ctx, zmq::socket_type::req);
    connectServerSocket.connect(address + std::to_string(SERVER_CONNECTION_PORT));
    connectServerSocket.set(zmq::sockopt::sndtimeo, 2000);
    std::string serializeUserData;
    zmq_api::serializeUser(userData, serializeUserData);
    zmq_api::sendMessage(connectServerSocket, serializeUserData);
    std::string reply = zmq_api::receiveMessage(connectServerSocket);
    return reply;
}

std::string Client::getWeatherData(const std::string &city, const std::string &name) {
    zmq::context_t ctx(1);
    zmq::socket_t serverSocketPost(ctx, zmq::socket_type::pub);
    serverSocketPost.connect(address + std::to_string(SERVER_RECEIVER_PORT));
    zmq::socket_t serverSocketGet(ctx, zmq::socket_type::sub);
    serverSocketGet.connect(address + std::to_string(SERVER_SENDER_PORT));
    serverSocketGet.set(zmq::sockopt::subscribe, "");
    zmq::socket_t serverSocket(ctx, zmq::socket_type::req);
    serverSocket.connect(address + std::to_string(8001));

    std::string result;
    nlohmann::json json;
    json["name"] = name;
    json["city"] = city;
    std::string data = json.dump();
    zmq_api::sendMessage(serverSocket, data);
    Data requestData;
    zmq_api::deserializeData(zmq_api::receiveMessage(serverSocket), requestData);
    for (;;) {
        if (requestData.username == name) {
            return requestData.data;
        }
    }
}


