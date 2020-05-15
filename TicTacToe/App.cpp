#include "App.h"

wxIMPLEMENT_APP(App);

App::App(){
	mainWin = new MainWin(); //utworzenie okna g³ównego
}

App::~App(){
	delete mainWin;//zniszczenie okna
}

bool App::OnInit() //pokazanie okna g³ównego
{
	mainWin->Show();
	return true;
}
