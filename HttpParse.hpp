#include <iostream>
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>

class Time {
public:
    size_t hours   = 0;
    size_t minutes = 0;
    size_t seconds = 0;
    std::string location;

};

class Date {
public:
    std::string month;
    Time time;
    size_t day  = 0;
    std::string dayOfTheWeak;
    size_t year = 0;

};

class Cords {
public:
    double latitude  = 0;
    double longitude = 0;

};

class Temp {
public:
    double Kelvin;
    double Celsius;
    double Fahrenheit;
    double feelsLike;
    double maxTemperature;
    double minTemperature;

    Temp(double & tempKelvin, double &feelsLike, double &maxTemp, double &minTemp)
    :
    Kelvin(tempKelvin),
    Celsius(Kelvin - 273.15),
    Fahrenheit(Celsius * 9 / 5 + 32),
    feelsLike(feelsLike),
    maxTemperature(maxTemp),
    minTemperature(minTemp) {}
    Temp() = default;

};

class WeatherType {
public:
    std::string main;
    std::string description;

};

class WeatherData {
public:
    Date date;
    Cords cords;
    Temp temperature;
    WeatherType weatherType;

};

class HttpParser {
public:

};

Date dateParse(const std::string &s) {
    Date date;
    Time time;
    std::stringstream stream(s);
    std::string t;
    char del;
    stream >> t >> date.dayOfTheWeak >> date.day >> date.month >> date.year;
    std::string currenTime;
    stream >> time.hours >> del >> time.minutes >> del >> time.seconds >> time.location;
    date.time = time;
    return date;
}

WeatherData weatherParse(const std::string& request) {
    WeatherData weatherData;
    WeatherType weatherType;
    Cords cords;

    nlohmann::json json = nlohmann::json::parse(request);

    cords.longitude= json["coord"]["lon"].get<double>();
    cords.latitude= json["coord"]["lat"].get<double>();

    weatherType.main = json["weather"][0]["main"].get<std::string>();
    weatherType.description = json["weather"][0]["description"].get<std::string>();

    double deg = json["main"]["temp"].get<double>();
    double degFeels = json["main"]["feels_like"].get<double>();
    double degMin = json["main"]["temp_min"].get<double>();
    double degMax = json["main"]["temp_max"].get<double>();

    Temp temperature(deg, degFeels, degMax, degMin);

    weatherData.weatherType = weatherType;
    weatherData.cords = cords;
    weatherData.temperature = temperature;

    return weatherData;
}

std::ostream& operator<<(std::ostream & out, const Time & time) {
    out << time.hours << ":" << time.minutes << ":" << time.seconds << " " << time.location;
    return out;
}

std::ostream& operator<<(std::ostream & out, const WeatherData & wd) {
    out << "Date: " << wd.date.dayOfTheWeak << ' ' << wd.date.day << ' '
                    << wd.date.month << ' ' << wd.date.year << " " << wd.date.time << std::endl;
    out << "Type: " << wd.weatherType.main << " " << wd.weatherType.description << std::endl;
    out << "Temperature(Kelvin): " << wd.temperature.Kelvin << std::endl;
    out << "Temperature(Feels Like): " << wd.temperature.feelsLike;
    return out;
}


std::string weatherDataToString(const WeatherData & wd) {
    std::string res;
    res += "Weather Type:\n" +
            wd.weatherType.main + ", " + wd.weatherType.description + '\n' +
            "Temperature(Celsius):\n" +
            std::to_string(wd.temperature.Celsius) + '\n' +
            "Temperature(Feels Like):\n" +
            std::to_string(wd.temperature.feelsLike - 273.15) + '\n';

    return res;
}
