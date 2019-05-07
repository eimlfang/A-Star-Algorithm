#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

enum class State {kEmpty, kObstacle};

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

vector<vector<State>> Search(vector<vector<State>> board, int start[2], int goal[2]) {
    cout << "No path found!" << endl;
    return vector<vector<State>> {};
}

int main() {
    auto board = ReadBoarderFile("/Users/eimlfang/Documents/FZJ/Project/A-Star-Algorithm/1.board");
    int start[2] = {0, 0};
    int goal[2] = {4, 5};
    auto solution = Search(board, start, goal);
    PrintBoard(solution);
}