#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int WIN_SCORE = 10;
const int DRAW_SCORE = 0;
const int LOSS_SCORE = -10;

// Function to print the Tic Tac Toe board
void printBoard(const vector<char>& board) {
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "-----------" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "-----------" << endl;
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
}

// Function to check if the board is full
bool boardFull(const vector<char>& board) {
    for (char c : board) {
        if (c == ' ')
            return false;
    }
    return true;
}

// Function to check if a player has won
bool checkWin(const vector<char>& board, char player) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == player && board[i + 1] == player && board[i + 2] == player)
            return true;
    }
    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player)
            return true;
    }
    // Check diagonals
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player))
        return true;
    return false;
}

// Function to evaluate the current board state
int evaluate(const vector<char>& board) {
    if (checkWin(board, 'O'))
        return WIN_SCORE;
    else if (checkWin(board, 'X'))
        return LOSS_SCORE;
    else
        return DRAW_SCORE;
}

// Minimax function with alpha-beta pruning
int minimax(vector<char>& board, int depth, bool isMaximizing, int alpha, int beta) {
    if (checkWin(board, 'O')) return WIN_SCORE;
    if (checkWin(board, 'X')) return LOSS_SCORE;
    if (boardFull(board)) return DRAW_SCORE;

    if (isMaximizing) {
        int maxEval = numeric_limits<int>::min();
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int eval = minimax(board, depth + 1, false, alpha, beta);
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                board[i] = ' ';
                if (beta <= alpha) break; // Pruning
            }
        }
        return maxEval;
    } else {
        int minEval = numeric_limits<int>::max();
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int eval = minimax(board, depth + 1, true, alpha, beta);
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                board[i] = ' ';
                if (beta <= alpha) break; // Pruning
            }
        }
        return minEval;
    }
}

// Function to get a valid move from the computer using minimax algorithm
int getComputerMove(vector<char>& board) {
    int bestMove = -1;
    int bestEval = numeric_limits<int>::min();
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int eval = minimax(board, 0, false, numeric_limits<int>::min(), numeric_limits<int>::max());
            board[i] = ' ';
            if (eval > bestEval) {
                bestEval = eval;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

int main() {
    vector<char> board(9, ' ');

    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "You are playing as 'X', and the computer is 'O'." << endl;

    while (true) {
        printBoard(board);
        // User's move
        int userMove;
        cout << "Enter your move (1-9): ";
        cin >> userMove;
        userMove--;
        if (userMove < 0 || userMove >= 9 || board[userMove] != ' ') {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[userMove] = 'X';
        if (checkWin(board, 'X')) {
            printBoard(board);
            cout << "You win!" << endl;
            break;
        }
        if (boardFull(board)) {
            printBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }

        // Computer's move
        int computerMove = getComputerMove(board);
        board[computerMove] = 'O';
        cout << "Computer plays move " << computerMove + 1 << endl;
        if (checkWin(board, 'O')) {
            printBoard(board);
            cout << "Computer wins!" << endl;
            break;
        }
        if (boardFull(board)) {
            printBoard(board);
            cout << "It's a draw!" << endl;
            break;
        }
    }

    return 0;
}

