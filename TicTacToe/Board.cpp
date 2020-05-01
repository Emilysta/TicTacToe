#include "Board.h"
#include <iostream>
Board::Board(int newSize) {
    size = newSize;
    board = new char[size*size]; //tablica o rozmiarze np 4x4 
                                 //zapisana jako tablica od 0 do 15 
    for (int i = 0; i < size * size; i++) {
        board[i] = '_';
    }
 }

Board::~Board() {
    delete[] board;
}

bool Board::isEnd() {
    return true;
}

void Board::show() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << board[i*size + j];
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}