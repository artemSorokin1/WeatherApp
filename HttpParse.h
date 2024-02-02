#pragma once
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
            feelsLike(feelsLike - 273.15),
            maxTemperature(maxTemp - 273.15),
            minTemperature(minTemp - 273.15) {}
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
    double visibility;
    double windSpeed;
    std::string city;
    std::string country;
};

Date dateParse(const std::string &s);

WeatherData weatherParse(const std::string& request);

std::ostream& operator<<(std::ostream & out, const Time & time);

std::ostream& operator<<(std::ostream & out, const WeatherData & wd);

std::string weatherDataToString(const WeatherData & wd);

