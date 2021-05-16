/*
    Sudoku solver using backtracking
    @file solve.cpp
    @author Qui Ngoc Nguyen
    @version 1.0 05/16/21
*/
#include <iostream>
#include <algorithm>
#include <iterator>
#define N 9
using namespace std;

static int btCounter = 0, testCounter = 0;

void printBoard(const int board[N][N]) {
    cout << "The solution is as follows: \n" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "    ";
        for (int j = 0; j < N; ++j) {
            cout << board[i][j] << " ";
        } cout << endl;
    } cout << endl;
}

bool isValid(const int board[N][N], const int& row, const int& col, const int& num) {

    if (find(begin(board[row]), end(board[row]), num) != end(board[row])) { return false; }

    for (int i = 0; i < N; ++i) {
        if (board[i][col] == num) { return false; }
    }

    int initRow = row - row % 3,
        initCol = col - col % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[initRow + i][initCol + j] == num) { return false; }
        }
    }

    return true;
}

bool getNextEmptyCell(const int board[N][N], int& row, int& col) {
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (board[row][col] == 0) { return true; }
        }
    }
    return false;
}

bool solve(int board[N][N]) {
    int row, col;

    if (!getNextEmptyCell(board, row, col)) { return true; }

    for (int temp = 1; temp <= N; ++temp) {
        if (isValid(board, row, col, temp)) {
            board[row][col] = temp;
            ++testCounter;
            if (solve(board)) { return true; }
            ++btCounter;
            board[row][col] = 0;
        }
    }
    return false;
}

int main(){
    int board[N][N] = {{ 0, 0, 6, 0, 0, 0, 3, 0, 0 },
                       { 0, 0, 1, 9, 0, 3, 7, 6, 0 },
                       { 4, 7, 3, 0, 0, 0, 8, 0, 0},
                       { 0, 6, 0, 7, 2, 0, 9, 3, 0,},
                       { 3, 4, 0, 5, 0, 0, 0, 7, 8 },
                       { 1, 0, 0, 3, 8, 0, 2, 4, 0 },
                       { 0, 8, 0, 2, 0, 1, 4, 0, 0 },
                       { 7, 3, 0, 0, 0, 0, 1, 0, 0 },
                       { 0, 1, 9, 4, 0, 7, 5, 0, 0 }};

    if (solve(board)) { 
        printBoard(board); 
        cout << "Num of tested solutions: " << testCounter << endl;
        cout << "      Num of backtracks: " << btCounter << endl;
    } else { 
        cout << "There was no solution found." << endl; 
    }

    return EXIT_SUCCESS;
}

#undef N;
