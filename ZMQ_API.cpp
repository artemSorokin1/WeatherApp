#include "ZMQ_API.h"

namespace zmq_api {

    void serializeData(const Data &data, std::string &output) {
        nlohmann::json json;
        json["username"] = data.username;
        json["data"] = data.data;
        output = json.dump();
    }

    void deserializeData(const std::string &input, Data &data) {
        nlohmann::json json = nlohmann::json::parse(input);
        data.username = json["username"].get<std::string>();
        data.data = json["data"].get<std::string>();
    }

    void serializeSimpleMessage(const SimpleMessage &msg, std::string &output) {
        nlohmann::json json;
        json["name"] = msg.name;
        json["msg"] = msg.msg;
        output = json.dump();
    }

    void deserializeSimpleMessage(const std::string &input, SimpleMessage &msg) {
        nlohmann::json json = nlohmann::json::parse(input);
        msg.name = json["name"].get<std::string>();
        msg.msg = json["msg"].get<std::string>();
    }

    void serializeReplyFromServer(const ReplyFromServer &reply, std::string &output) {
        nlohmann::json json;
        json["id_socket_listener"] = reply.id_socket_listener;
        json["id_socket_writer"] = reply.id_socket_writer;
        output = json.dump();
    }

    void deserializeReplyFromServer(const std::string &input, ReplyFromServer &reply) {
        nlohmann::json json = nlohmann::json::parse(input);
        reply.id_socket_writer = json["id_socket_writer"];
        reply.id_socket_listener = json["id_socket_listener"];
    }

    void serializeUser(const UserData &ud, std::string &output) {
        nlohmann::json json;
        json["login"] = ud.login;
        json["password"] = ud.password;
        json["username"] = ud.username;
        json["id"] = ud.id;
        json["type"] = ud.type;
        output = json.dump();
    }

    void deserializeUser(const std::string &input, UserData &ud) {
        nlohmann::json json = nlohmann::json::parse(input);
        ud.login = json["login"].get<std::string>();
        ud.password = json["password"].get<std::string>();
        ud.username = json["username"].get<std::string>();
        ud.id = json["id"].get<int>();
        ud.type = json["type"].get<Types>();
    }

    void sendMessage(zmq::socket_t &socket, const std::string &s) {
        zmq::message_t msg(s.size());
        memcpy(msg.data(), s.c_str(), s.size());
        socket.send(msg, zmq::send_flags::dontwait);
    }

    std::string receiveMessage(zmq::socket_t &socket) {
        bool replyStatus = true;
        zmq::message_t msg;
        try {
            replyStatus = socket.recv(&msg);
        } catch (...) {
            replyStatus = false;
        }
        if (!replyStatus) {
            throw std::runtime_error("receive msg problem");
        }
        std::string res = msg.to_string();
        return res;
    }

    std::string receiveMessageDontWait(zmq::socket_t &socket) {
        int replyStatus = true;
        zmq::message_t msg;
        replyStatus = socket.recv(&msg, ZMQ_DONTWAIT);
        if (replyStatus == -1 || msg.empty()) {
            return "Wait";
        }
        std::string res(static_cast<char *>(msg.data()), msg.size());
        return res;
    }

    void sendToClient(zmq::socket_t &socket, const std::string &userId, const std::string & message) {
        zmq::message_t userMsg(userId.size());
        memcpy(userMsg.data(), userId.c_str(), userId.size());

        zmq::message_t messageToSend(message.size());
        memcpy(messageToSend.data(), message.c_str(), message.size());

        socket.send(userMsg, zmq::send_flags::sndmore);
        socket.send(zmq::str_buffer(""), zmq::send_flags::sndmore);
        socket.send(messageToSend, zmq::send_flags::none);
    }

    std::pair<std::string, std::string> receiveFromClient(zmq::socket_t &socket) {
        std::pair<std::string, std::string> res;
        zmq::message_t identity;
        socket.recv(&identity);

        zmq::message_t delimiter;
        socket.recv(&delimiter);

        zmq::message_t message;
        socket.recv(&message);
        std::string id = identity.to_string();
        std::string msg = message.to_string();
        res = {id, msg};
        return res;
    }

}
