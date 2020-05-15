#include "MainWin.h"
#include <stdlib.h>
#include <wx/msgdlg.h>

void onEndClicked(wxCommandEvent& e) {
	exit(0);
}

MainWin::MainWin() : wxFrame(nullptr, wxID_ANY, "Tic Tac Toe", wxPoint(0, 0), wxSize(600, 400), 0) {
	name = ""; //ustawienie wartosci poczatkowych
	handler = new wxPNGHandler; //utworzenie handlera dla zmian w tle
	wxImage::AddHandler(handler);
	name = "Gracz";
	image.LoadFile(wxT("APPBG1"), wxBITMAP_TYPE_BMP_RESOURCE); //za�adowanie t�a z zasob�w
	Connect(wxEVT_PAINT, wxPaintEventHandler(MainWin::OnDraw)); //utworzenie po��czenia mi�dzy zdarzeniami
	this->Menu(); //otowrzenie menu g��wnego aplikacji
}

void MainWin::Menu() { //menu g��wne
	pNameText = new wxStaticText(this, wxID_ANY, "Nazwa gracza: ", wxPoint(225, 20), wxSize(150, 20), wxALIGN_CENTER); //tekst statyczny
	wxFont font = pNameText->GetFont();
	font.SetPointSize(10);
	font.SetWeight(wxFONTWEIGHT_BOLD);
	pNameText->SetFont(font);
	playersName = new wxTextCtrl(this, 998, name, wxPoint(225, 40), wxSize(150, 20)); //pole do wpisywania nazwy gracza
	//playersName->SetBackgroundColour(wxColour(146, 198, 240, 255));

	firstText = new wxStaticText(this, wxID_ANY, "Kto zaczyna gr�: ", wxPoint(225, 70), wxSize(150, 20), wxALIGN_CENTER); //tekst statyczny
	firstText->SetFont(font);
	wxArrayString turn;
	turn.Add("Gracz");
	turn.Add("Komputer");
	first = new wxComboBox(this, 999, "", wxPoint(225, 90), wxSize(150, 75), turn, wxCB_READONLY); //lista rozwijana z mozliwo�cia wyboru czy zaczyna gracz czy te� komputer
	first->SetSelection(0);

	start = new wxButton(this, 1000, "Zacznij gr�", wxPoint(225, 280), wxSize(150, 75)); //przycisk "Zacznij gr�"
	start->SetFont(font);
	start->SetBackgroundColour(wxColour(146, 198, 240, 255));

	wxArrayString choices;
	for (int i = 0; i < 5; i++) {
		choices.Add(std::to_string(i + 3));
	}
	sizes = new wxComboBox(this, 1002, "", wxPoint(225, 160), wxSize(150, 75), choices, wxCB_READONLY); //lista rozwijana z rozmiarami planszy do wyboru
	sizes->SetSelection(0);
	sizeText = new wxStaticText(this, wxID_ANY, "Rozmiar planszy: ", wxPoint(225, 140), wxSize(150, 20), wxALIGN_CENTER); //tekst statyczny
	sizeText->SetFont(font);

	inLine = new wxComboBox(this, 1003, "", wxPoint(225, 220), wxSize(150, 75), wxArrayString(1, "3"), wxCB_READONLY); //lista rozwijana z liczba znak�w w linii do wyboru
	inLine->SetSelection(0);

	inLineText = new wxStaticText(this, wxID_ANY, "Liczba znak�w w linii: ", wxPoint(225, 200), wxSize(150, 20), wxALIGN_CENTER); //tekst statyczny
	inLineText->SetFont(font);

	end = new wxButton(this, 1001, "X", wxPoint(550, -2), wxSize(50, 50)); //przycisk "koniec" /"X"
	end->SetFont(font);
	end->SetBackgroundColour(wxColour(146, 198, 240, 255));

	this->Center();
	this->SetBackgroundColour(wxColour(208, 228, 245, 255));
	image.LoadFile(wxT("APPBG1"), wxBITMAP_TYPE_BMP_RESOURCE); //Za�adowanie t�a z zasob�w
	Refresh();

	wxEvtHandler::Bind(wxEVT_TEXT, &MainWin::OnTextChange, this, 998, 998);
	wxEvtHandler::Bind(wxEVT_BUTTON, &MainWin::OnStartClicked, this, 1000, 1000); //przypisanie funkcji dla poszczeg�lnych p�l
	wxEvtHandler::Bind(wxEVT_BUTTON, &onEndClicked, 1001, 1001);
	wxEvtHandler::Bind(wxEVT_COMBOBOX, &MainWin::OnSizesChange, this, 1002, 1002);


}

MainWin::~MainWin() { //destruktor
	delete pNameText;
	delete playersName;
	delete start;
	delete sizes;
	delete inLine;
	delete sizeText;
	delete inLineText;
	delete firstText;
	delete first;
	delete end;
	delete handler;
}

void MainWin::clearMain() { //usuni�cie element�w okna g��wnego
	delete pNameText;
	delete playersName;
	delete start;
	delete sizes;
	delete inLine;
	delete sizeText;
	delete inLineText;
	delete firstText;
	delete first;
}

void MainWin::OnDraw(wxPaintEvent& event) { //ustawienie t�a menu g��wnego
	wxPaintDC dc(this);
	dc.DrawBitmap(image, wxPoint(-1, -1));
}

void MainWin::OnEndClickedEdit(wxCommandEvent& e) {
	this->clearGame();
}

void MainWin::clearGame() {//usuni�cie element�w okna gry, oraz usuni�cie funkcji przycisku "X"
	int size = game->getSize();
	for (int i = 0; i < size * size; i++) {
		delete buttons[i];
	}
	delete[] buttons;
	this->Menu();
	wxEvtHandler::Unbind(wxEVT_BUTTON, &MainWin::OnEndClickedEdit, this, 1001, 1001);
	delete game;
	delete image2;
}

void MainWin::OnStartClicked(wxCommandEvent& e) { //uruchomienie gry

	int size = sizes->GetSelection(); //pobranie informacji o rozmiarze planszy
	size = size + 3;
	int in_line = inLine->GetSelection(); //pobranie informacji o ilosci znakow w linii
	in_line = in_line + 3;
	int i = first->GetSelection();

	clearMain(); //wyczyszczenie okna
	image.LoadFile(wxT("APPBG2"), wxBITMAP_TYPE_BMP_RESOURCE); //zmiana t�a na inny plik z zasob�w
	Refresh();
	if (i == 0) {
		game = new Game(size, in_line,Who::player1); //ustawienie gry
	}
	else {
		game = new Game(size, in_line, Who::player2); //ustawienie gry
	}
	buttons = new wxButton * [size * size];
	float sizeOfButton = 380.0f / size; //ustawienie rozmiar�w dla przycisk�w planszy
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			buttons[i * size + j] = new wxButton(this, i * size + j + 1, " ", wxPoint(10 + j * sizeOfButton, 10 + i * sizeOfButton), wxSize(sizeOfButton, sizeOfButton)); //utworzneie przycisk�w
			wxEvtHandler::Bind(wxEVT_BUTTON, &MainWin::OnClickMove, this, i * size + j + 1, i * size + j + 1); //ustawienie zdarze�
			buttons[i * size + j]->SetBackgroundColour(wxColour(146, 198, 240, 255));
		}
	}

	if (game->whoseMove() == Who::player2) {
		image2 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("APPO"), wxBITMAP_TYPE_BMP_RESOURCE), wxPoint(425, 125), wxSize(150, 150)); //za�adownie bitmapy z zasob�w
		int move;
		game->computerMove(move); //rych komputera
		buttons[move]->SetLabel(game->getP2());  //Wyswietlenie informacji o przegranej u�ytkownika
		wxFont font = buttons[move]->GetFont();
		font.SetPointSize(20);
		font.SetWeight(wxFONTWEIGHT_BOLD);
		buttons[move]->SetFont(font);
		wxEvtHandler::Unbind(wxEVT_BUTTON, &MainWin::OnClickMove, this, move + 1, move + 1);//usuniecie funkcji z pola, w ktorym komputer ustawil swoj znak
	}
	wxEvtHandler::Unbind(wxEVT_BUTTON, &onEndClicked, 1001, 1001); //usuniecie starej funkcji dla przycisku "X"
	wxEvtHandler::Bind(wxEVT_BUTTON, &MainWin::OnEndClickedEdit, this, 1001, 1001);//ustawienie nowej funkcji
	image2 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("APPX"), wxBITMAP_TYPE_BMP_RESOURCE), wxPoint(425, 125), wxSize(150, 150)); //za�adownie bitmapy z zasob�w
}

void MainWin::OnSizesChange(wxCommandEvent& e) { //reakcja na zmian� w li�cie rozwijanej z informacj� o rozmiarze planszy
	inLine->Clear();
	int choice = sizes->GetSelection(); //pobranei informacji z pola
	choice = choice + 3;
	for (int i = 3; i <= choice; i++) { //stworzenie odpowiedniej listy rozwijanej z informacj� o ilosci znak�w w liniii
		inLine->AppendString(wxString(std::to_string(i)));
	}
	inLine->SetSelection(choice - 3);// ustawienie domy�lnego wyboru
}

void MainWin::OnClickMove(wxCommandEvent& e) {
	buttons[e.GetId() - 1]->SetLabel(game->getP1()); //ruch gracza, ustawienie napisu na przycisku
	wxFont font = buttons[e.GetId() - 1]->GetFont();
	font.SetPointSize(20);
	font.SetWeight(wxFONTWEIGHT_BOLD);
	buttons[e.GetId() - 1]->SetFont(font);
	int move;
	delete image2;
	image2= new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("APPO"), wxBITMAP_TYPE_BMP_RESOURCE), wxPoint(425, 125), wxSize(150, 150)); //za�adownie bitmapy z zasob�w
	wxMilliSleep(100); //zwolnienie wstawiania pierwszych ruch�w
	if (game->playerMove(e.GetId() - 1)) { //playerMove zwraca true jesli zmiana na polu spowodowa�a wygran�
		wxMessageBox("Wygra�e�/�a� "+name, "", 0); //Wyswietlenie informacji o wygranej
		clearGame();
	}
	else if (game->isEnd()) { //sprawdzenie, czy nie jest juz koniec gry, tzn., czy sa jeszcze jakies puste pola, na kt�re mozna sie ruszy�
		wxMessageBox("Remis", "", 0); //je�li jest koniec i nie bylo wygranej mamy remis
		clearGame();
	}
	else if (game->computerMove(move)) { //computerMove zwraca true jesli zmiana na polu spowodowa�a wygran�
		buttons[move]->SetLabel(game->getP2());  //Wyswietlenie informacji o przegranej u�ytkownika
		buttons[move]->SetFont(font);
		wxMessageBox("Przegra�e�/�a� "+name, "", 0);
		clearGame();
	}
	else {
		buttons[move]->SetLabel(game->getP2());
		buttons[move]->SetFont(font);
		delete image2;
		image2 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("APPX"), wxBITMAP_TYPE_BMP_RESOURCE), wxPoint(425, 125), wxSize(150, 150)); //za�adownie bitmapy z zasob�w
		wxEvtHandler::Unbind(wxEVT_BUTTON, &MainWin::OnClickMove, this, move + 1, move + 1);//usuniecie funkcji z pola, w ktorym komputer ustawil swoj znak
		if (game->isEnd()) { //sprawdzenie, czy nie jest juz koniec gry, tzn., czy sa jeszcze jakies puste pola, na kt�re mozna sie ruszy�
			wxMessageBox("Remis", "", 0); //je�li jest koniec i nie bylo wygranej mamy remis
			clearGame();
		}
	}
	wxEvtHandler::Unbind(wxEVT_BUTTON, &MainWin::OnClickMove, this, e.GetId(), e.GetId()); //usuniecie funkcji z pola, w ktorym gracz ustawil swoj znak
}

void MainWin::OnTextChange(wxCommandEvent& e) {
	name = playersName->GetLineText(0);
}



