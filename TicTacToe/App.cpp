#include "App.h"

wxIMPLEMENT_APP(App);

App::App(){
	mainWin = new MainWin();
}

App::~App(){

}

bool App::OnInit()
{
	mainWin->Show();
	return true;
}
