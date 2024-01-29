#include <wx/wx.h>
#include "RegisterWindow.hpp"

class EnterApp : public wxApp
{
public:
    bool OnInit()
    {
        auto window = new EnterWindow(wxT("Вход"));
        window->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(RegistrationApp);
