#include <iostream>
#include <vector>
using namespace std;

const int N = 4;

bool isSafe(int row, int col, vector<int>& board) {
    for (int i = 0; i < row; i++) {
        int prevCol = board[i];
        if (prevCol == col || abs(prevCol - col) == abs(i - row))
            return false;
    }
    return true;
}

void solveBacktracking(int row, vector<int>& board) {
    if (row == N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << (board[i] == j ? "Q " : ". ");
            cout << endl;
        }
        cout << endl;
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col, board)) {
            board[row] = col;
            solveBacktracking(row + 1, board);
        }
    }
}

void solveBranchBound(int row, vector<int>& board, vector<bool>& colUsed, vector<bool>& diag1, vector<bool>& diag2) {
    if (row == N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << (board[i] == j ? "Q " : ". ");
            cout << endl;
        }
        cout << endl;
        return;
    }

    for (int col = 0; col < N; col++) {
        if (!colUsed[col] && !diag1[row - col + N - 1] && !diag2[row + col]) {
            board[row] = col;
            colUsed[col] = diag1[row - col + N - 1] = diag2[row + col] = true;

            solveBranchBound(row + 1, board, colUsed, diag1, diag2);

            colUsed[col] = diag1[row - col + N - 1] = diag2[row + col] = false;
        }
    }
}

int main() {
    cout << "Backtracking Solution(s):\n";
    vector<int> board(N, -1);
    solveBacktracking(0, board);

    cout << "Branch and Bound Solution(s):\n";
    vector<bool> colUsed(N, false), diag1(2 * N - 1, false), diag2(2 * N - 1, false);
    solveBranchBound(0, board, colUsed, diag1, diag2);

    return 0;
}
