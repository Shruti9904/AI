#include <bits/stdc++.h>
using namespace std;

const int ROW = 5;
const int COL = 5;

int dRow[] = {-1, 1, 0, 0}; // up, down
int dCol[] = {0, 0, -1, 1}; // left, right

struct Cell {
    int row, col;
    int g, h, f;
    pair<int, int> parent;
};

// Custom comparator for the priority queue (min-heap by f value)
struct CompareCells {
    bool operator()(const Cell& a, const Cell& b) {
        return a.f > b.f; 
    }
};

bool isValid(int row, int col, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
    return row >= 0 && row < ROW &&
           col >= 0 && col < COL &&
           grid[row][col] == 0 && !visited[row][col];
}

int manhattan(int r, int c, int gr, int gc) {
    return abs(r - gr) + abs(c - gc);
}

void printGrid(vector<vector<int>>& grid) {
    cout << "\nMaze Grid:\n";
    for (auto& row : grid) {
        for (auto& cell : row) {
            cout << (cell == 1 ? "# " : ". ");  // Wall = #, Free = .
        }
        cout << endl;
    }
    cout << "\nLegend: '#' = wall (1), '.' = free path (0)\n\n";
}

bool aStar(vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    priority_queue<Cell, vector<Cell>, CompareCells> openSet;
    vector<vector<bool>> visited(ROW, vector<bool>(COL, false));
    vector<vector<pair<int, int>>> parent(ROW, vector<pair<int, int>>(COL, {-1, -1}));

    int sr = start.first, sc = start.second;
    int gr = goal.first, gc = goal.second;

    Cell startCell = {sr, sc, 0, manhattan(sr, sc, gr, gc), 0 + manhattan(sr, sc, gr, gc), {-1, -1}};
    openSet.push(startCell);

    while (!openSet.empty()) {
        Cell curr = openSet.top();
        openSet.pop();

        int r = curr.row;
        int c = curr.col;

        if (visited[r][c])
            continue;

        visited[r][c] = true;

        if (r == gr && c == gc) {
            cout << "Path found from Start (" << sr << "," << sc << ") to Goal (" << gr << "," << gc << "):\n";
            vector<pair<int, int>> path;

            while (!(r == sr && c == sc)) {
                path.push_back({r, c});
                pair<int, int> p = parent[r][c];
                r = p.first;
                c = p.second;
            }
            path.push_back({sr, sc});
            reverse(path.begin(), path.end());

            for (auto [pr, pc] : path)
                cout << "(" << pr << "," << pc << ") ";
            cout << endl;
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + dRow[i];
            int nc = c + dCol[i];

            if (isValid(nr, nc, grid, visited)) {
                int gNew = curr.g + 1;
                int hNew = manhattan(nr, nc, gr, gc);
                int fNew = gNew + hNew;

                openSet.push({nr, nc, gNew, hNew, fNew, {r, c}});
                parent[nr][nc] = {r, c};
            }
        }
    }

    cout << "No path found from Start (" << sr << "," << sc << ") to Goal (" << gr << "," << gc << ").\n";
    return false;
}

int main() {
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {4, 4};

    printGrid(grid);
    aStar(grid, start, goal);

    return 0;
}

