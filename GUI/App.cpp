#include "RegisterWindow.h"

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

wxIMPLEMENT_APP(EnterApp);
