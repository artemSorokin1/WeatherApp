#include "EnterWindow.h"

EnterWindow::EnterWindow(const wxString &title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(380, 480)) {
    auto boxSizerVertical = new wxBoxSizer(wxVERTICAL);
    auto boxSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);
    auto panel = new wxPanel(this, wxID_ANY);

    auto enterText = new wxStaticText(panel, wxID_ANY, "Вход", wxPoint(165, 110));
    wxFont enterTextFont = enterText->GetFont();
    enterTextFont.SetPointSize(22);
    enterTextFont.SetWeight(wxFONTWEIGHT_BOLD);
    enterText->SetFont(enterTextFont);

    usernameField = new wxTextCtrl(panel, wxID_ANY, wxT(""),
                                   wxPoint(120, 190), wxSize(150, -1));
    passwordField = new wxTextCtrl(panel, wxID_ANY, wxT(""),
                                   wxPoint(120, 230), wxSize(150, -1), wxTE_PASSWORD);

    usernameField->SetHint("Введите имя");
    passwordField->SetHint("Введите пароль");

    auto enterButton = new wxButton(panel, wxID_ANY, wxT("Enter"), wxPoint(150, 280));
    auto swapButton = new wxButton(panel, wxID_ANY, wxT("Нет аккаунтa? Регистрация"), wxPoint(100, 400));

    boxSizerVertical->Add(usernameField, 0 , wxALL, 10);
    boxSizerVertical->Add(passwordField, 0 , wxALL, 10);
    boxSizerVertical->Add(enterButton, 0, wxALL, 10);
    boxSizerVertical->Add(swapButton, 0, wxALL, 10);

    boxSizerHorizontal->AddStretchSpacer();

    panel->SetSizer(boxSizerVertical);
    panel->SetSizer(boxSizerHorizontal);

    enterButton->Bind(wxEVT_BUTTON, &EnterWindow::OnEnterButtonClick, this);
    swapButton->Bind(wxEVT_BUTTON, &EnterWindow::OnSwapButtonClick, this);
    Center();

}

void EnterWindow::OnEnterButtonClick(wxCommandEvent &event) {
    wxString name = usernameField->GetValue();
    wxString password = passwordField->GetValue();
    UserData userData;
    userData.type = Types::Enter;
    userData.password = password;
    userData.username = name;
    bool isCorrectUser = Client::tryToEnter(userData);
    if (isCorrectUser) {
        auto mainWindow = new MainWindow("Узнать погоду", userData.username);
        mainWindow->Show(true);
        Close(true);
    } else {
        this->passwordField->Clear();
        this->usernameField->Clear();
        wxMessageBox(wxT("Неправильное имя пользователя или пароль"), wxT(""), wxICON_ERROR | wxCENTRE);
    }
}

void EnterWindow::OnSwapButtonClick(wxCommandEvent &event) {
    auto registrationWindow = new RegistrationWindow(wxT("Окно Регистрации"));
    registrationWindow->Show(true);
    this->Close(true);
}
