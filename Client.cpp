#include "Client.hpp"


int main(int argc, char* argv[]) {

    std::string get = getWeatherData("Moscow", "artem");
    std::cout << get << '\n';
}
