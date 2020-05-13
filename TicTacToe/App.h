#pragma once
#include "wx/wx.h"
#include "MainWin.h"
class App : public wxApp {
	MainWin* mainWin;
public: 
	App();
	~App();
	virtual bool OnInit();
};

