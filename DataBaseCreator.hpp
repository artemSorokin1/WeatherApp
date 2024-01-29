#pragma once
#include <pqxx/pqxx>
#include <iostream>

const int DATA_BASE_PORT = 5432;

class DataBaseCreator {
public:
    static void initDataBase() {
        std::string login = "Gena Killer";
        std::string password = "123";
//        pqxx::connection connection(
//                "dbname=USERS user=admin password=admin hostaddr=127.0.0.1 port=" + std::to_string(DATA_BASE_PORT));
//        pqxx::work txn(connection);
//        pqxx::result is = txn.exec("ELECT EXISTS (SELECT 1 FROM information_schema.tables WHERE table_schema = 'public' AND table_name = 'users'");
//        if (is[0][0].as<bool>()) {
//
//        }
//
////        txn.exec("CREATE DATABASE USERS");
////        txn.exec("USE USERS");
//        txn.exec("CREATE TABLE users (id INT, username VARCHAR(50), login VARCHAR(50), password VARCHAR(50))");
//        /// only for test
//        txn.exec("INSERT INTO users (id, username, login, password) VALUES (1, 'artem', 'artem', '12345')");
        ///
//        pqxx::connection connection("dbname=USERS user=admin password=admin hostaddr=127.0.0.1 port=" + std::to_string(5432));
//        pqxx::work txn(connection);
//        pqxx::result result = txn.exec("SELECT * FROM users");
//        bool isCorrectUser = false;
//        for (pqxx::result::const_iterator row = result.begin(); row != result.end(); ++row) {
//            if (row["login"].as<std::string>() == login && row["password"].as<std::string>() == password) {
//                isCorrectUser = true;
//            }
//        }
//
//        if (isCorrectUser) {
//            std::cout << "OK" << '\n';
//        } else {
//            std::cout << "No" << '\n';
//        }
//        txn.commit();
//        connection.close();
    }

};
