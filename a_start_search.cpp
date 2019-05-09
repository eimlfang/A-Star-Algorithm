#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm> // for sort

using namespace std;

enum class State {
    kEmpty, kObstacle, kClosed, kPath, kStart, kFinish
};

// directional deltas
const int delta[4][2]{{-1, 0},
                      {0,  -1},
                      {1,  0},
                      {0,  1}};


vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
        if (n == 0) {
            row.push_back(State::kEmpty);
        } else {
            row.push_back(State::kObstacle);
        }
    }
    return row;
}

vector<vector<State>> ReadBoarderFile(string path) {
    ifstream my_file(path);
    vector<vector<State>> board{};
    if (my_file) {
        string line;
        while (getline(my_file, line)) {
            vector<State> row = ParseLine(line);
            board.push_back(row);
        }
    }

    return board;
}

/**
 * Compare the F value of two cells
 * */
bool Compare(const vector<int> a, const vector<int> b) {
    int f1 = a[2] + a[3];
    int f2 = b[2] + b[3];
    return f1 > f2;
}

/**
 * Sort the two-dimensional vector of line in descending order.
 */
void CellSort(vector<vector<int>> *v) {
    sort(v->begin(), v->end(), Compare);
}

/**
 * Calculate the manhattan distance
 * */
int Heuristic(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

/**
 * Check that a cell is valid: on the grid, not an obstacle, and clear.
 * */
bool CheckValidCell(int x, int y, vector<vector<State>> &grid) {
    bool on_grid_x = (x >= 0 && x < grid.size());
    bool on_grid_y = (y >= 0 && y < grid[0].size());
    if (on_grid_x && on_grid_y)
        return grid[x][y] == State::kEmpty;
    return false;
}

/**
 * Add a node to the open list and mark it as open
 * */
void AddToOpen(int x, int y, int g, int h,
               vector<vector<int>> &openList,
               vector<vector<State>> &grid) {
    openList.push_back(vector<int>{x, y, g, h});
    grid[x][y] = State::kClosed;
}

/**
 * Expand current nodes's neighbors and add them to the open list.
 * */
void ExpandNeighbors(const vector<int> &current,
                     int goal[2],
                     vector<vector<int>> &openList,
                     vector<vector<State>> &grid
) {

    // Get current node's data.
    int x = current[0];
    int y = current[1];
    int g = current[2];

    // Loop through current node's potential neighbors.

    for (int i = 0; i < 4; i++) {
        auto x2 = x + delta[i][0];
        auto y2 = y + delta[i][1];

        // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
        if (CheckValidCell(x2, y2, grid)) {
            // Increment g value, compute h value, and add neighbor to open list.
            int g2 = g + 1;
            int h2 = Heuristic(x2, y2, goal[0], goal[1]);
            AddToOpen(x2, y2, g2, h2, openList, grid);
        }
    }
}

vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) {
    // Create the vector of open nodes.
    vector<vector<int>> open{};

    // Initialize the starting node.
    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);
    AddToOpen(x, y, g, h, open, grid);

    while (open.size() > 0) {
        // Get the next node
        CellSort(&open);
        auto current = open.back();
        open.pop_back();
        x = current[0];
        y = current[1];
        grid[x][y] = State::kPath;

        // Check if we are done.
        if (x == goal[0] && y == goal[1]) {
            grid[init[0]][init[1]] = State::kStart;
            grid[goal[0]][goal[1]] = State::kFinish;
            return grid;
        }

        // If we are not done, expand search to current node's neightbors.
         ExpandNeighbors(current, goal, open, grid);

    }

    cout << "No path found!" << "\n";
    return vector<vector<State>>{};
}

string CellString(State cell) {
    switch (cell) {
        case State::kObstacle:
            return "⛰️   ";
        case State::kPath:
            return "🚗   ";
        case State::kStart:
            return "🚦   ";
        case State::kFinish:
            return "🏁   ";
        default:
            return "0   ";
    }
}

void PrintBoard(const vector<vector<State>> board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            cout << CellString(board[i][j]);
        }
        cout << "\n";
    }
}

int run() {
    int init[2]{0, 0};
    int goal[2]{4, 5};
#ifdef _WIN32
    string path = "D:\\Developer\\A-Star-Algorithm\\1.board";
#else
    string path = "/Users/eimlfang/Documents/FZJ/Project/A-Star-Algorithm/1.board";
#endif
    auto board = ReadBoarderFile(path);
    auto solution = Search(board, init, goal);
    PrintBoard(solution);
}