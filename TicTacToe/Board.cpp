#include "Board.h"
#include <iostream>
#include <time.h>

Board::Board() {
    size = 0;
    board = nullptr;
    whoseMove = Who::none;
    lastMove = 1000;
    firstDiagonal = nullptr;
    secondDiagonal = nullptr;
}

Board::Board(int newSize) {
    srand((unsigned)(time(NULL)));
    size = newSize;
    board = new What[size*size]; //tablica o rozmiarze np 4x4 
                                 //zapisana jako tablica od 0 do 15 
    for (int i = 0; i < size * size; i++) {
        board[i] = What::none;
    }
    whoseMove = Who(std::rand() % 2 + 1);
    lastMove = NULL;
    firstDiagonal = new int[size];
    int u = size + 1;
    for (int j = 0; j < size; j++)
    {
        firstDiagonal[j] = j * u;
    }
    secondDiagonal = new int[size];
    int u2 = size - 1;
    for (int j = 0; j < size; j++)
    {
        secondDiagonal[j] = (j+1) * u2;
    }
 }

Board::~Board() {
    delete[] board;
}

bool Board::checkVertical(int i_column) { //sprawdz w pionie
    for (int i = 0; i < size-1; i++) {//i_column indeks sprawdzanej kolumny
        if (board[i_column + size * i] != board[i_column + size *(i+1)]) {
            return false;
        }
    }
    return true;
}

bool Board::checkHorizontal(int i_row) { //sprawdz w poziomie
    for (int i = 0; i < size - 1; i++) { //i_row indeks sprawdzanego rzedu 
        if (board[i_row*size+i] != board[i_row*size+i+1]) {
            return false;
        }
    }
    return true;
}
bool Board::checkFirstDiagonal() {
    for (int i = 0; i < size - 1; i++) { //sprawdzenie czy na przekatnej \ nie ma wygranej 
        if (board[firstDiagonal[i]] != board[firstDiagonal[i+1]]) {
            return false;
        }
    }
    return true;
}
bool Board::checkSecondDiagonal() {
    for (int i = 0; i < size - 1; i++) { //sprawdzenie czy na przekatnej / nie ma wygranej 
        if (board[secondDiagonal[i]] != board[secondDiagonal[i + 1]]) {
            return false;
        }
    }
    return true;
}

bool Board::isEnd(int index) {
    for (int i = 0; i < size; i++) {
        if (index % size == i) {
            if (checkVertical(i) == true) {
                return true;
            }
        }
        if (index / size == i) {
            if (checkHorizontal(i) == true) {
                return true;
            }
        }
        if (index == firstDiagonal[i]) {
            if (checkFirstDiagonal() == true)
                return true;
        }
        if (index == secondDiagonal[i]) {
            if (checkSecondDiagonal() == true)
                return true;
        }
    }
    return false;
}

void Board::show() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << (char)(board[i*size + j]);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}