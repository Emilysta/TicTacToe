#pragma once
#include "wx/wx.h"
#include "MainWin.h"
class App : public wxApp {//utowrzenie aplikacji
	MainWin* mainWin; // okno g³ówne aplikacji
public: 
	App();
	~App();
	virtual bool OnInit();
};

