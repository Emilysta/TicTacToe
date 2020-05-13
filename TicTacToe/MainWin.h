#pragma once
#include "wx/wx.h"
#include "wx/combo.h"
#include "Game.h"
#include "wx/image.h"
#include <wx/event.h>


class MainWin : public wxFrame
{
	/*menu g³ówne*/
	wxButton* start; //przycisk zacznij grê
	wxComboBox* sizes;//lista rozwijana z opcjami wyboru rozmiatu planszy
	wxComboBox* inLine;//lista rozwijana z opcjami wyboru ilosci znakow w lini potrzebnych do wygranej
	wxComboBox* first;//lista rozwijana z opcjami wyboru kto zaczyna grê
	wxStaticText* sizeText; //teskst w menu
	wxStaticText* inLineText; //teskst w menu
	wxStaticText* firstText;
	wxTextCtrl* playersName; //pole uzupe³niane dla nazwy gracza
	wxStaticText* pNameText; //teskst w menu
	/*t³o aplikacji w menu g³ównym*/
	wxBitmap image;
	wxStaticBitmap* image2;
	wxImageHandler* handler;
	/*gra*/
	wxButton** buttons;
	Game* game;
	/*koniec gry oraz koniec dzia³ania aplikacji*/
	wxButton* end;
	/*string do ptzretrzymania nazwy gracza*/
	std::string name;

public:

	MainWin();
	~MainWin();
	void Menu();
	void clearMain(); //wyczyœæ okno g³ówne z elementów
	void clearGame(); //wyczyœæ okno gry z elementów
	void OnDraw(wxPaintEvent& event); //Event potrzebny do tworzenia t³a okna g³ównego
	//void OnDraw2(wxPaintEvent& event); //Event potrzebny do tworzenia zdjecia w oknie gry
	void OnEndClickedEdit(wxCommandEvent& e); //Zmiana dzia³ania przycisku Koniec dla okna gry
	void OnStartClicked(wxCommandEvent& e); //Rozpoczecie gry poprzez nacisniecie przycisku zacznij grê
	void OnSizesChange(wxCommandEvent& e); //Event reaguj¹cy na zmianê w liœcie rozwijanej rozmiarów planszy
	void OnClickMove(wxCommandEvent& e); //Event gry, po naciœniêciu na pole planszy wpisz znak i uruchom ruch komputera
	void OnTextChange(wxCommandEvent& e); //Event zmiany tekstu w okienku Nazwa gracza
};

