#pragma once
#include "wx/wx.h"
#include "MainWin.h"
class App : public wxApp {//utowrzenie aplikacji
	MainWin* mainWin; // okno g��wne aplikacji
public: 
	App();
	~App();
	virtual bool OnInit();
};

