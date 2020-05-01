#pragma once
class Board{
	int size;
	char* board; //tablica znakow 'X', 'O'
public: 
	Board(int newSize);
	~Board();
	bool isEnd();
	void show();
};

