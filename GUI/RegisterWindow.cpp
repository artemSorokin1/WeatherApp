#include "RegisterWindow.h"

RegistrationWindow::RegistrationWindow(const wxString &title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(380, 480)) {
    auto boxSizerVertical = new wxBoxSizer(wxVERTICAL);
    auto boxSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);
    auto panel = new wxPanel(this, wxID_ANY);

    auto registerText = new wxStaticText(panel, wxID_ANY, "Регистрация", wxPoint(125, 110));
    wxFont registerTextFont = registerText->GetFont();
    registerTextFont.SetPointSize(22);
    registerTextFont.SetWeight(wxFONTWEIGHT_BOLD);
    registerText->SetFont(registerTextFont);

    usernameField = new wxTextCtrl(panel, wxID_ANY, wxT(""),
                                   wxPoint(120, 170), wxSize(150, -1));
    loginField = new wxTextCtrl(panel, wxID_ANY, wxT(""),
                                wxPoint(120, 210), wxSize(150, -1));
    passwordField = new wxTextCtrl(panel, wxID_ANY, wxT(""),
                                   wxPoint(120, 250), wxSize(150, -1), wxTE_PASSWORD);

    usernameField->SetHint("Введите имя");
    loginField->SetHint("Введите логин");
    passwordField->SetHint("Введите пароль");

    auto registerButton = new wxButton(panel, wxID_ANY, wxT("Зарегистрироваться"), wxPoint(120, 300));
    auto swapButton = new wxButton(panel, wxID_ANY, wxT("Есть аккаунт? Войти"), wxPoint(122, 400));

    boxSizerVertical->Add(usernameField, 0 , wxALL, 10);
    boxSizerVertical->Add(loginField, 0 , wxALL, 10);
    boxSizerVertical->Add(passwordField, 0 , wxALL, 10);
    boxSizerVertical->Add(registerButton, 0, wxALL, 10);
    boxSizerVertical->Add(swapButton, 0, wxALL, 10);

    boxSizerHorizontal->AddStretchSpacer();

    panel->SetSizer(boxSizerVertical);
    panel->SetSizer(boxSizerHorizontal);

    registerButton->Bind(wxEVT_BUTTON, &RegistrationWindow::OnRegisterButtonClick, this);
    swapButton->Bind(wxEVT_BUTTON, &RegistrationWindow::OnSwapButtonClick, this);
    Center();
}

void RegistrationWindow::OnRegisterButtonClick(wxCommandEvent &event) {
    wxString username = usernameField->GetValue();
    wxString login = loginField->GetValue();
    wxString password = passwordField->GetValue();

    UserData userData;
    userData.username = username;
    userData.type = Types::Register;
    userData.login = login;
    userData.password = password;

    std::string isCorrectData = Client::tryToRegister(userData);
    if (isCorrectData == "Success") {
        auto enterWindow = new EnterWindow("Вход");
        enterWindow->Show(true);
        Close(true);
    } else {
        usernameField->Clear();
        loginField->Clear();
        passwordField->Clear();
        if (isCorrectData == "Incorrect username") {
            wxMessageBox(wxT("Такое имя пользователя уже занято"), wxT(""), wxICON_ERROR | wxCENTRE);
        } else {
            wxMessageBox(wxT("На такой логин уже зарегистрирован аккаунт"), wxT(""), wxICON_ERROR | wxCENTRE);
        }
    }

}

void RegistrationWindow::OnSwapButtonClick(wxCommandEvent &event) {
    auto enterWindow = new EnterWindow(wxT("Окно Регистрации"));
    enterWindow->Show(true);
    this->Close(true);
}