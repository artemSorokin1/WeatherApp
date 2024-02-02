#pragma once
#include <iostream>
#include <zmq.hpp>
#include <thread>
#include <vector>
#include "ZMQ_API.h"
#include <queue>
#include <sstream>
#include "HttpSender.hpp"
#include "HttpParse.h"
#include <pqxx/pqxx>

const std::string ADDRESS = "tcp://127.0.0.1:";
const std::string HOST = "api.openweathermap.org";
const std::string API_KEY = "ec40d8bfe34acc99d20c196843061399";
const int SERVER_CONNECTION_PORT = 8000;
const int SERVER_RECEIVER_PORT = 5555;
const int SERVER_SENDER_PORT = 5556;
const int PSQL_PORT = 5432;

class Server {
public:
    Server();
    void connectionHandler();
    void communicateWithClient();

private:
    zmq::context_t ctx;
    size_t currentUserId;
    zmq::socket_t connectionHandlerSocket;
    zmq::socket_t getSocket;
    zmq::socket_t postSocket;
    zmq::socket_t serverSocket;

};

Server::Server()
    : ctx(zmq::context_t(1)),
    currentUserId(1),
    connectionHandlerSocket(ctx, zmq::socket_type::rep),
    getSocket(ctx, zmq::socket_type::sub),
    postSocket(ctx, zmq::socket_type::pub),
    serverSocket(ctx, zmq::socket_type::rep) {
    connectionHandlerSocket.bind(ADDRESS + std::to_string(SERVER_CONNECTION_PORT));
    connectionHandlerSocket.set(zmq::sockopt::sndtimeo, 2000);
    getSocket.bind(ADDRESS + std::to_string(SERVER_RECEIVER_PORT));
    getSocket.set(zmq::sockopt::subscribe, "");
    postSocket.bind(ADDRESS + std::to_string(SERVER_SENDER_PORT));
    serverSocket.bind(ADDRESS + std::to_string(8001));
    serverSocket.set(zmq::sockopt::sndtimeo, 2000);
}

void Server::connectionHandler() {
    for (;;) {
        std::string request = zmq_api::receiveMessage(connectionHandlerSocket);
        UserData userData;
        zmq_api::deserializeUser(request, userData);
        bool isCorrectUser = false;
        std::string messageToClient;
        if (userData.type == Types::Enter) {
            pqxx::connection connection("dbname=USERS user=admin password=admin hostaddr=127.0.0.1 port=" + std::to_string(PSQL_PORT));
            pqxx::work txn(connection);
            pqxx::result result = txn.exec("SELECT * FROM users");
            for (pqxx::result::const_iterator row = result.begin(); row != result.end(); ++row) {
                if (row["username"].as<std::string>() == userData.username && row["password"].as<std::string>() == userData.password) {
                    isCorrectUser = true;
                }
            }
            messageToClient = (isCorrectUser ? "Success" : "Error");
            txn.commit();
            connection.close();
        } else {
            pqxx::connection connection("dbname=USERS user=admin password=admin hostaddr=127.0.0.1 port=" + std::to_string(PSQL_PORT));
            pqxx::work txn(connection);
            pqxx::result result = txn.exec("SELECT * FROM users");
            isCorrectUser = true;
            for (pqxx::result::const_iterator row = result.begin(); row != result.end(); ++row) {
                if (row["username"].as<std::string>() == userData.username) {
                    messageToClient = "Incorrect username";
                    isCorrectUser = false;
                    break;
                }
                if (row["login"].as<std::string>() == userData.login) {
                    messageToClient = "Incorrect login";
                    isCorrectUser = false;
                    break;
                }
            }
            if (isCorrectUser) {
                messageToClient = "Success";
                std::string query = "INSERT INTO users (id, username, login, password) VALUES (" + std::to_string(currentUserId++) + ", '"
                                                                                                 + userData.username + "', '"
                                                                                                 + userData.login + "', '"
                                                                                                 + userData.password + "')";
                std::cout << query << '\n';
                txn.exec(query);

            }
            txn.commit();
            connection.close();
        }
        zmq_api::sendMessage(connectionHandlerSocket, messageToClient);
    }
}

void Server::communicateWithClient() {
    for (;;) {
        std::string request = zmq_api::receiveMessage(serverSocket);
        nlohmann::json json = nlohmann::json::parse(request);
        const std::string PATH = "/data/2.5/weather?q=" + json["city"].get<std::string>() + "&appid=" + API_KEY;
        std::string weather = HttpSender::sendHttpRequest(HOST, PATH);
        Data data;
        data.username = json["name"].get<std::string>();
        data.data = weather;
        std::cout << weather << '\n';
        std::string stringData;
        zmq_api::serializeData(data, stringData);
        zmq_api::sendMessage(serverSocket, stringData);
    }
}



