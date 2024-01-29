#pragma once
#include <wx/wx.h>
#include "Enter.hpp"

class RegistrationWindow : public wxFrame
{
public:
    RegistrationWindow(const wxString& title)
            : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(640, 480)) {
        auto boxSizerVertical = new wxBoxSizer(wxVERTICAL);
        auto boxSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);
        auto panel = new wxPanel(this, wxID_ANY);

        usernameField = new wxTextCtrl(panel, wxID_ANY, wxT(""),
                                       wxPoint(230, 170), wxSize(150, -1));
        loginField = new wxTextCtrl(panel, wxID_ANY, wxT(""),
                                    wxPoint(230, 210), wxSize(150, -1));
        passwordField = new wxTextCtrl(panel, wxID_ANY, wxT(""),
                                       wxPoint(230, 250), wxSize(150, -1), wxTE_PASSWORD);

        usernameField->SetHint("Введите имя");
        loginField->SetHint("Введите логин");
        passwordField->SetHint("Введите пароль");

        auto registerButton = new wxButton(panel, wxID_ANY, wxT("Зарегистрироваться"), wxPoint(250, 300));

        boxSizerVertical->Add(usernameField, 0 , wxALL, 10);
        boxSizerVertical->Add(loginField, 0 , wxALL, 10);
        boxSizerVertical->Add(passwordField, 0 , wxALL, 10);
        boxSizerVertical->Add(registerButton, 0, wxALL, 10);

        boxSizerHorizontal->AddStretchSpacer();

        panel->SetSizer(boxSizerVertical);
        panel->SetSizer(boxSizerHorizontal);

        registerButton->Bind(wxEVT_BUTTON, &RegistrationWindow::OnRegisterButtonClick, this);
        Center();
    }

    void OnRegisterButtonClick(wxCommandEvent& event) {
        wxString username = usernameField->GetValue();
        wxString login = loginField->GetValue();
        wxString password = passwordField->GetValue();

        UserData userData;
        userData.username = username;
        userData.type = Types::Register;
        userData.login = login;
        userData.password = password;

        bool isCorrectData = tryToRegister(userData);
        if (isCorrectData) {
            auto enterWindow = new EnterWindow("Вход");
            enterWindow->Show(true);
            Close(true);
        } else {
            usernameField->Clear();
            loginField->Clear();
            passwordField->Clear();
            // TODO: сделать вывод об ошибке регистрации
//            wxMessageBox(wxT("Неправильное имя пользователя, логин или пароль"), wxT(""), wxICON_ERROR | wxCENTRE);
        }

        wxMessageBox(wxT("Регистрация успешно завершена."), wxT("Успех"));
    }

private:
    wxTextCtrl* usernameField;
    wxTextCtrl* loginField;
    wxTextCtrl* passwordField;
};

class RegistrationApp : public wxApp
{
public:
    bool OnInit()
    {
        RegistrationWindow* window = new RegistrationWindow(wxT("Окно регистрации"));
        window->Show(true);
        return true;
    }
};

//wxIMPLEMENT_APP(RegistrationApp);
