#include "HttpParse.h"

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

    weatherData.visibility = json["visibility"].get<double>();
    weatherData.windSpeed = json["wind"]["speed"].get<double>();
    weatherData.city = json["name"].get<std::string>();
    weatherData.country = json["sys"]["country"].get<std::string>();
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
    res += "City: " + wd.city + ", " + wd.country + '\n'
        + "Weather: " + wd.weatherType.main + '\n'
        + "Weather description: " + wd.weatherType.description + '\n'
        + "Temperature: " + std::to_string(wd.temperature.Celsius) + '\n'
        + "Temperature(Feels like): " + std::to_string(wd.temperature.feelsLike) + '\n'
        + "Temperature minimum: " + std::to_string(wd.temperature.minTemperature) + '\n'
        + "Temperature maximum: " + std::to_string(wd.temperature.maxTemperature) + '\n'
        + "Visibility: " + std::to_string(wd.visibility) + '\n'
        + "Wind speed: " + std::to_string(wd.windSpeed) + '\n';

    return res;
}
