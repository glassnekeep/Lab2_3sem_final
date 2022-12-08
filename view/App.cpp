#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);
wxIMPLEMENT_WXWIN_MAIN_CONSOLE;

bool App::OnInit() {
	auto* mainFrame = new MainFrame("Lab 2");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
