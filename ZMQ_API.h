#pragma once
#include <iostream>
#include <unistd.h>
#include <zmq.hpp>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

enum class Types {
    Register, Enter
};

class UserData {
public:
    Types type;
    std::string login;
    std::string password;
    std::string username;
    size_t id;

};

class ReplyFromServer {
public:
    int id_socket_listener;
    int id_socket_writer;

};

class SimpleMessage {
public:
    std::string name;
    std::string msg;

};

class Data {
public:
    std::string data;
    std::string username;

};

namespace zmq_api {
    void serializeData(const Data &data, std::string &output);
    void deserializeData(const std::string &input, Data &data);
    void serializeSimpleMessage(const SimpleMessage &msg, std::string &output);
    void deserializeSimpleMessage(const std::string &input, SimpleMessage &msg);
    void serializeReplyFromServer(const ReplyFromServer &reply, std::string &output);
    void deserializeReplyFromServer(const std::string &input, ReplyFromServer &reply);
    void serializeUser(const UserData &ud, std::string &output);
    void deserializeUser(const std::string &input, UserData &ud);
    void sendMessage(zmq::socket_t &socket, const std::string &s);
    std::string receiveMessage(zmq::socket_t &socket);
    std::string receiveMessageDontWait(zmq::socket_t &socket);
    void sendToClient(zmq::socket_t &socket, const std::string &userId, const std::string & message);
    std::pair<std::string, std::string> receiveFromClient(zmq::socket_t &socket);

}

