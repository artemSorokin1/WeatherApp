#pragma once
#include "MainWindow.hpp"
#include "RegisterWindow.h"

class EnterWindow : public wxFrame {
public:
    explicit EnterWindow(const wxString& title);
    void OnEnterButtonClick(wxCommandEvent& event);
    void OnSwapButtonClick(wxCommandEvent& event);

private:
    wxTextCtrl* usernameField;
    wxTextCtrl* passwordField;

};



