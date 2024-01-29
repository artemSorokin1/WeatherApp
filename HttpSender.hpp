#pragma once
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

class HttpSender {
public:
    static std::string sendHttpRequest(const std::string& host, const std::string& path)
    {
        try {
            // Создаем объект io_context
            asio::io_context io_context;

            // Создаем resolver для разрешения DNS и установки соединения
            asio::ip::tcp::resolver resolver(io_context);

            // Создаем сокет для установки соединения с сервером
            asio::ip::tcp::socket socket(io_context);

            // Разрешаем DNS-имя сервера OpenWeatherAPI
            auto endpoints = resolver.resolve("api.openweathermap.org", "http");

            // Устанавливаем соединение
            asio::connect(socket, endpoints);

            // Формируем HTTP-запрос
            http::request<http::string_body> request(http::verb::get, path, 11);
            request.set(http::field::host, host);
            request.set(http::field::user_agent, "Boost Beast");

            // Отправляем HTTP-запрос
            http::write(socket, request);

            // Читаем и выводим HTTP-ответ
            beast::flat_buffer buffer;
            http::response<http::dynamic_body> response;
            http::read(socket, buffer, response);

            std::string responseData = boost::beast::buffers_to_string(response.body().data());

            // Закрываем соединение
            beast::error_code ec;
            socket.close(ec);
            if (ec && ec != asio::error::eof) {
                throw beast::system_error{ec};
            }
            return responseData;

        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }

    }

};
