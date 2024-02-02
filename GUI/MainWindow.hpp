#pragma once
#include <iostream>
#include <wx/wx.h>
#include <nlohmann/json.hpp>
#include "../Client.h"

class MainWindow : public wxFrame {
public:
    MainWindow(const wxString& title, std::string &username)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(640, 480)), username(std::move(username)) {
        auto panel = new wxPanel(this, wxID_ANY);
        auto sizer = new wxBoxSizer(wxVERTICAL);
        cityField = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        cityField->SetHint("Введите город:");
        sizer->Add(cityField, 0, wxALL | wxEXPAND, 5);
        auto findCityButton = new wxButton(panel, wxID_ANY, wxT("Узнать погоду"));
        sizer->Add(findCityButton, 0, wxALL | wxCENTRE, 5);
        outputData = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
        sizer->Add(outputData, 1, wxALL | wxEXPAND, 5);
        panel->SetSizer(sizer);
        findCityButton->Bind(wxEVT_BUTTON, &MainWindow::OnButtonClick, this);
        cityField->Bind(wxEVT_TEXT_ENTER, &MainWindow::OnButtonClick, this);
        Center();

    }

    void OnButtonClick(wxCommandEvent& event) {
        outputData->Clear();
        wxString city = cityField->GetValue();
        const std::string weather = Client::getWeatherData(city.ToStdString(), username);
        nlohmann::json checkErrorJson = nlohmann::json::parse(weather);
        bool status = (weather.size() > 70);
        if (!status) {
            wxMessageBox(wxT("Некоректно введенный город"), wxT(""), wxICON_ERROR | wxCENTRE);
        } else {
            WeatherData weatherData = weatherParse(weather);
            outputData->AppendText(weatherDataToString(weatherData));
        }
        cityField->Clear();
    }

private:
    wxTextCtrl* cityField;
    std::string username;
    wxTextCtrl* outputData;

};
