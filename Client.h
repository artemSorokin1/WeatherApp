#pragma once
#include "ZMQ_API.h"
#include "HttpParse.h"

const std::string address = "tcp://127.0.0.1:";
const int SERVER_CONNECTION_PORT = 8000;
const int SERVER_RECEIVER_PORT = 5555;
const int SERVER_SENDER_PORT = 5556;

class Client {
public:
    static bool tryToEnter(const UserData & userData);
    static std::string tryToRegister(const UserData & userData);
    static std::string getWeatherData(const std::string & city, const std::string & name);

};

//void Client::Start() {
//    zmq::context_t ctx(1);
//    zmq::socket_t connectServerSocket(ctx, zmq::socket_type::req);
//    connectServerSocket.connect(address + std::to_string(SERVER_CONNECTION_PORT));
//    connectServerSocket.set(zmq::sockopt::sndtimeo, 2000);
//    zmq::socket_t serverSocketPost(ctx, zmq::socket_type::pub);
//    serverSocketPost.connect(address + std::to_string(SERVER_RECEIVER_PORT));
//    zmq::socket_t serverSocketGet(ctx, zmq::socket_type::sub);
//    serverSocketGet.connect(address + std::to_string(SERVER_SENDER_PORT));
//    serverSocketGet.set(zmq::sockopt::subscribe, "");
//
//    std::string name;
//    std::cout << "Username: ";
//    std::cin >> name;
//    std::cin.ignore();
//
//    zmq_api::sendMessage(connectServerSocket, name);
//
//    std::string request = zmq_api::receiveMessage(connectServerSocket);
//    std::cout << request << std::endl;
//
//    std::string city;
//    std::cout << "Введите город: ";
//    std::getline(std::cin, city);
//    nlohmann::json json;
//    json["name"] = name;
//    json["city"] = city;
//    std::string data = json.dump();
//    zmq_api::sendMessage(serverSocketPost, data);
//    Data requestData;
//    zmq_api::deserializeData(zmq_api::receiveMessage(serverSocketGet), requestData);
//    if (requestData.username == name) {
//        WeatherData weatherData = weatherParse(requestData.data);
//        std::cout << weatherData << std::endl;
//    }

//    std::thread receiveThread([&](){
//        while (true) {
//            std::stringstream request;
//            request << zmq_api::receiveMessage(serverSocketGet);
//            std::string username, msg;
//            request >> username >> msg;
//            if (username == name) {
//                std::cout << msg << '\n';
//            }
//        }
//    });
//
//    std::thread sendThread([&](){
//        while (true) {
//            std::cout << "Введите сообщение: ";
//            std::string msg;
//            std::cin >> msg;
//            zmq_api::sendMessage(serverSocketPost, name + " " + msg);
//        }
//    });
//
//    receiveThread.join();
//    sendThread.join();


//}

