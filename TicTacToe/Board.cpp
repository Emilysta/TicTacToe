#include "Board.h"
#include <iostream>
#include <time.h>

Board::Board() {
    size = 0;
    board = nullptr;
    whoseMove = Who::none;
    winner = Who::none;
    countOfMovesToEnd = 0;
}
Board::Board(const Board& boardToCopy) {
    size = boardToCopy.size;
    board = new What*[size];
    for (int i = 0; i < size; ++i) { 
        board[i] = new What[size];
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; j++) {
            board[i][j]= boardToCopy.board[i][j];
        }
    }
    whoseMove = boardToCopy.whoseMove;
    winner = boardToCopy.winner;
    countOfMovesToEnd = boardToCopy.countOfMovesToEnd;
}

Board::Board(int newSize) {
    srand((unsigned)(time(NULL)));
    size = newSize;
    board = new What * [size];//tablica o rozmiarze np 4x4 
    for (int i = 0; i < size; ++i) {
        board[i] = new What[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = What::none;
        }
    }
    winner = Who::none;
    whoseMove = Who(std::rand() % 2 + 1);
    countOfMovesToEnd = size * size;
 }

Board::~Board() {
    for (int i = 0; i < size; i++) {
        delete board[i];
    }
    delete[] board;
}

bool Board::checkVertical(int i_column) { //sprawdz w pionie
    for (int i = 0; i < size-1; i++) {//i_column indeks sprawdzanej kolumny
        if (board[i][i_column] != board[i+1][i_column]) {
            return false;
        }
    }
    return true;
}

bool Board::checkHorizontal(int i_row) { //sprawdz w poziomie
    for (int i = 0; i < size - 1; i++) { //i_row indeks sprawdzanego rzedu 
        if (board[i_row][i] != board[i_row][i+1]) {
            return false;
        }
    }
    return true;
}
bool Board::checkFirstDiagonal() {
    for (int i = 0; i < size - 1; i++) { //sprawdzenie czy na przekatnej \ nie ma wygranej 
        if (board[i][i] != board[i+1][i+1]) {
            return false;
        }
    }
    return true;
}
bool Board::checkSecondDiagonal() {
    for (int i = 0; i < size - 1; i++) { //sprawdzenie czy na przekatnej / nie ma wygranej 
        if (board[i][size-i-1] != board[i+1][size-(i+1)-1]) {
            return false;
        }
    }
    return true;
}

bool Board::isEnd(int row,int column) {
    if (checkVertical(column) == true)
        return true;
    if (checkHorizontal(row) == true) {
        return true;
    }
    if (row == column) {
        if (checkFirstDiagonal() == true) {
            return true;
        }
    }
    for (int i = 0; i < size; i++) {
        if ((row == i && column == size - i - 1)) {
            if (checkSecondDiagonal() == true)
                return true;
        }
    }
    return false;
}

void Board::show() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << (char)(board[i][j]);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

bool Board::isMoveLeft() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == What::none)
            {
                return true;
            }
        }
    }
    return false;

}

int Board::evaluate(What sign) {
    for (int i = 0; i < size; i++)
    {
        if (checkHorizontal(i)) {
            if (board[i][0] == sign) {
                return 10;
            }
            else {
                return -10;
            }
        }
        if (checkVertical(i)) {
            if (board[0][i] == sign) {
                return 10;
            }
            else {
                return -10;
            }
        }
        
    }
    if (checkFirstDiagonal()) {
        if (board[0][0] == sign) {
            return 10;
        }
        else {
            return -10;
        }
    }
    if (checkSecondDiagonal()) {
        if (board[0][size-1] == sign) {
            return 10;
        }
        else {
            return -10;
        }
    }

    return 0;
}

Who Board::checkWinner() {
    if (winner == Who::none && isMoveLeft() == false) {
        return Who::none;
    }
    else {
        return winner;
    }
}
