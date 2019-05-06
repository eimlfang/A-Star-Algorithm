#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<int> ParseLine(string line) {
    char c;
    int n;
    istringstream sline(line);
    vector<int> row;
    while (sline >> c >> n && c == ',') {
        row.push_back(n);
    }
    return row;
}

vector<vector<int>> ReadBoarderFile(string path) {
    ifstream my_file;
    my_file.open(path);
    if (my_file) {
        string line;
        vector<vector<int>> v;
        while (getline(my_file, line)) {
            vector<int> l = ParseLine(line);
            v.push_back(l);
        }
        return v;
    }
}

void PrintBoard(vector<vector<int>> v) {
    cout << "PrintBoard" << "\n";
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[i].size(); ++j) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    auto board = ReadBoarderFile("/Users/eimlfang/Documents/FZJ/Project/A-Star-Algorithm/1.board");
    cout << "After read" << endl;
    PrintBoard(board);
}