#include "MyApp.h"


bool MyApp::OnInit(){
	auto* frame = new MainFrame();
	frame->SetMinSize(wxSize(800, 730));
	frame->Show();
	return true;
}