#include "App.h"

wxIMPLEMENT_APP(App);

App::App(){
	mainWin = new MainWin(); //utworzenie okna g��wnego
}

App::~App(){
	delete mainWin;//zniszczenie okna
}

bool App::OnInit() //pokazanie okna g��wnego
{
	mainWin->Show();
	return true;
}
