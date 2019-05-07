#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

enum class State {kEmpty, kObstacle};

string CellString(State s) {
    string ss;
    switch (s) {
        case State::kEmpty:
            ss = "0";
            break;
        case State::kObstacle:
            ss = "⛰️ ";
            break;
        default:
            ss = "0";
            break;
    }
    return ss;
}

vector<int> ParseLine(string line) {
    char c;
    int n;
    istringstream sline(line);
    vector<int> row;
    while (sline >> n >> c && c == ',') {
        row.push_back(n);
    }
    return row;
}

vector<vector<int>> ReadBoarderFile(string path) {
    ifstream my_file(path);
    vector<vector<int>> board{};
    if (my_file) {
        string line;
        while (getline(my_file, line)) {
            vector<int> row = ParseLine(line);
            board.push_back(row);
        }
    }
    return board;
}

void PrintBoard(vector<vector<int>> board) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    auto board = ReadBoarderFile("/Users/eimlfang/Documents/FZJ/Project/A-Star-Algorithm/1.board");
    PrintBoard(board);
}