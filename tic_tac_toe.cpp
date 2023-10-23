#include <iostream>
#include <vector>
#include <limits>

using namespace std;

char board[3][3] = { {'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'} };

void printBoard() {
    cout << "  0 1 2" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isBoardFull() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '-') return false;
        }
    }
    return true;
}

bool checkWin(char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;

    return false;
}

int minimax(bool maximizing) {
    if (checkWin('x')) return -10;
    if (checkWin('o')) return 10;
    if (isBoardFull()) return 0;

    if (maximizing) {
        int maxEval = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '-') {
                    board[i][j] = 'o';
                    int eval = minimax(false);
                    maxEval = std::max(maxEval, eval);
                    board[i][j] = '-';
                }
            }
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '-') {
                    board[i][j] = 'x';
                    int eval = minimax(true);
                    minEval = std::min(minEval, eval);
                    board[i][j] = '-';
                }
            }
        }
        return minEval;
    }
}

void bestMove() {
    int maxEval = std::numeric_limits<int>::min();
    int moveX = -1;
    int moveY = -1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '-') {
                board[i][j] = 'o';
                int eval = minimax(false);
                if (eval > maxEval) {
                    maxEval = eval;
                    moveX = i;
                    moveY = j;
                }
                board[i][j] = '-';
            }
        }
    }
    board[moveX][moveY] = 'o';
}

int main() {
    int x, y;
    while (true) {
        printBoard();
        cout << "Enter your move (row and column): ";
        cin >> x >> y;
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == '-') {
            board[x][y] = 'x';
            if (checkWin('x')) {
                printBoard();
                cout << "You win!" << endl;
                break;
            }
            if (isBoardFull()) {
                printBoard();
                cout << "It's a tie!" << endl;
                break;
            }
            bestMove();
            if (checkWin('o')) {
                printBoard();
                cout << "Computer wins!" << endl;
                break;
            }
            if (isBoardFull()) {
                printBoard();
                cout << "It's a tie!" << endl;
                break;
            }
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }
    return 0;
}
