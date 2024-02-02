#pragma once
#include <wx/wx.h>
#include "MainWindow.hpp"
#include "EnterWindow.h"

class RegistrationWindow : public wxFrame
{
public:
    explicit RegistrationWindow(const wxString& title);
    void OnRegisterButtonClick(wxCommandEvent& event);
    void OnSwapButtonClick(wxCommandEvent& event);

private:
    wxTextCtrl* usernameField;
    wxTextCtrl* loginField;
    wxTextCtrl* passwordField;
};
