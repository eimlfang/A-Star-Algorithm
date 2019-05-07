#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

enum class State {kEmpty, kObstacle, kClosed};

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
    }else {
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

vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) {
    cout << "No path found!" << endl;
    return vector<vector<State>> {};
}

int Heuristic(int x1, int y1, int x2, int y2) {
    return abs(x2-x1) + abs(y2-y1);
}

void AddToOne(int x, int y, int g, int h,
        vector<vector<int>> *openNodes,
        vector<vector<State>> *grid) {
    vector<int> node{x, y, g, h};
    openNodes->push_back(node);
    grid[x][y] = State::kClosed;
}

int main() {
#ifdef _WIN32
 string path = "D:\\Developer\\A-Star-Algorithm\\1.board";
#else
    string path = "/Users/eimlfang/Documents/FZJ/Project/A-Star-Algorithm/1.board";
#endif
    auto board = ReadBoarderFile(path);
    PrintBoard(board);
//    int init[2]{0, 0};
//    int goal[2]{4, 5};
//    auto solution = Search(board, init, goal);
//    PrintBoard(solution);
}