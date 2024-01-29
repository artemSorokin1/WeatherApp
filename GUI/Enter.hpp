#include "MainWindow.hpp"

class EnterWindow : public wxFrame {
public:
    EnterWindow(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(640, 480)) {
        auto boxSizerVertical = new wxBoxSizer(wxVERTICAL);
        auto boxSizerHorizontal = new wxBoxSizer(wxHORIZONTAL);
        auto panel = new wxPanel(this, wxID_ANY);

        usernameField = new wxTextCtrl(panel, wxID_ANY, wxT(""),
                                               wxPoint(230, 190), wxSize(150, -1));
        passwordField = new wxTextCtrl(panel, wxID_ANY, wxT(""),
                                       wxPoint(230, 230), wxSize(150, -1), wxTE_PASSWORD);

        usernameField->SetHint("Введите имя");
        passwordField->SetHint("Введите пароль");

        auto enterButton = new wxButton(panel, wxID_ANY, wxT("Enter"), wxPoint(260, 280));

        boxSizerVertical->Add(usernameField, 0 , wxALL, 10);
        boxSizerVertical->Add(passwordField, 0 , wxALL, 10);
        boxSizerVertical->Add(enterButton, 0, wxALL, 10);

        boxSizerHorizontal->AddStretchSpacer();

        panel->SetSizer(boxSizerVertical);
        panel->SetSizer(boxSizerHorizontal);

        enterButton->Bind(wxEVT_BUTTON, &EnterWindow::OnEnterButtonClick, this);
        Center();

    }

    void OnEnterButtonClick(wxCommandEvent& event) {
        wxString name = usernameField->GetValue();
        wxString password = passwordField->GetValue();
        bool isCorrectUser = false;
        UserData userData;
        userData.type = Types::Enter;
        userData.password = password;
        userData.username = name;
        isCorrectUser = tryToEnter(userData);
        if (isCorrectUser) {
            auto mainWindow = new MainWindow("Узнать погоду", userData.username);
            mainWindow->Show(true);
            Close(true);
        } else {
            this->passwordField->Clear();
            this->loginField->Clear();
            this->usernameField->Clear();
            // TODO: сделать вывод об ошибке входа
//            wxMessageBox(wxT("Неправильное имя пользователя или пароль"), wxT(""), wxICON_ERROR | wxCENTRE);
        }
    }

private:
    wxTextCtrl* usernameField;
    wxTextCtrl* loginField;
    wxTextCtrl* passwordField;

};


