#pragma once
#include "wx/wx.h"
#include "wx/combo.h"
#include "Game.h"
#include "wx/image.h"
#include <wx/event.h>


class MainWin : public wxFrame
{
	/*menu g��wne*/
	wxButton* start; //przycisk zacznij gr�
	wxComboBox* sizes;//lista rozwijana z opcjami wyboru rozmiatu planszy
	wxComboBox* inLine;//lista rozwijana z opcjami wyboru ilosci znakow w lini potrzebnych do wygranej
	wxComboBox* first;//lista rozwijana z opcjami wyboru kto zaczyna gr�
	wxStaticText* sizeText; //teskst w menu
	wxStaticText* inLineText; //teskst w menu
	wxStaticText* firstText;
	wxTextCtrl* playersName; //pole uzupe�niane dla nazwy gracza
	wxStaticText* pNameText; //teskst w menu
	/*t�o aplikacji w menu g��wnym*/
	wxBitmap image;
	wxStaticBitmap* image2;
	wxImageHandler* handler;
	/*gra*/
	wxButton** buttons;
	Game* game;
	/*koniec gry oraz koniec dzia�ania aplikacji*/
	wxButton* end;
	/*string do ptzretrzymania nazwy gracza*/
	std::string name;

public:

	MainWin();
	~MainWin();
	void Menu();
	void clearMain(); //wyczy�� okno g��wne z element�w
	void clearGame(); //wyczy�� okno gry z element�w
	void OnDraw(wxPaintEvent& event); //Event potrzebny do tworzenia t�a okna g��wnego
	//void OnDraw2(wxPaintEvent& event); //Event potrzebny do tworzenia zdjecia w oknie gry
	void OnEndClickedEdit(wxCommandEvent& e); //Zmiana dzia�ania przycisku Koniec dla okna gry
	void OnStartClicked(wxCommandEvent& e); //Rozpoczecie gry poprzez nacisniecie przycisku zacznij gr�
	void OnSizesChange(wxCommandEvent& e); //Event reaguj�cy na zmian� w li�cie rozwijanej rozmiar�w planszy
	void OnClickMove(wxCommandEvent& e); //Event gry, po naci�ni�ciu na pole planszy wpisz znak i uruchom ruch komputera
	void OnTextChange(wxCommandEvent& e); //Event zmiany tekstu w okienku Nazwa gracza
};

