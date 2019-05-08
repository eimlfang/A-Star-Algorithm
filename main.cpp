#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm> // for sort

using namespace std;

enum class State {
    kEmpty, kObstacle, kClosed, kPath
};


string CellString(State cell) {
    switch (cell) {
        case State::kObstacle:
            return "⛰️   ";
        default:
            return "0   ";
    }
}

vector<State> ParseLine(string line) {
    istringstream sline(line);
    char c;
    int n;
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
    } else {
        cout << "Read file failed, path is " << path << endl;
    }
    return board;
}

void PrintBoard(vector<vector<State>> board) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            cout << CellString(board[i][j]) << " ";
        }
        cout << endl;
    }
}

int Heuristic(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

void AddToOpen(int x, int y, int g, int h,
               vector<vector<int>> &openList,
               vector<vector<State>> &grid) {
    vector<int> node{x, y, g, h};
    openList.push_back(node);
    grid[x][y] = State::kClosed;
}

bool Compare(vector<int> a, vector<int> b) {
    int f1 = a[2] + a[3];
    int f2 = b[2] + b[3];
    return f1 > f2;
}

/**
 * 二维int向量排序，根据Compare函数规则
 * @param v
 */
void CellSort(vector<vector<int>> *v) {
    sort(v->begin(), v->end(), Compare);
}

vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) {
    vector<vector<int>> open{};
    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);

    AddToOpen(x, y, g, h, open, grid);

    cout << "No path found!" << "\n";
    while(open.size() > 0) {
    // Sort the open list using `CellSort`, and get the current node.
        CellSort(&open);
    // Get the x and y values from the current node,
    // and set grid[x][y] to kPath.
        vector<int> currentNode = open[0];
        x = currentNode[0];
        y = currentNode[1];
        grid[x][y] = State::kPath;
    // Check if you've reached the goal. If so, return grid.
        if (x == goal[0] && y == goal[y]) {
            return grid;
        }

    // If we're not done, expand search to current node's neighbors. This step will be completed in a later quiz.
    // ExpandNeighbors

    }
    return vector<vector<State>>{};
}

int main() {
#ifdef _WIN32
    string path = "D:\\Developer\\A-Star-Algorithm\\1.board";
#else
    string path = "/Users/eimlfang/Documents/FZJ/Project/A-Star-Algorithm/1.board";
#endif
    auto board = ReadBoarderFile(path);
//    PrintBoard(board);
    int init[2]{0, 0};
    int goal[2]{4, 5};
    auto solution = Search(board, init, goal);
    PrintBoard(solution);
}