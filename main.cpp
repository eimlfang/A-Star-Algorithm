#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<int> ParseLine(string s)
{
    char c;
    int n;
    istringstream stream(s);
    vector<int> v;
    while (stream >> c >> n && c == ',')
    {
        v.push_back(n);
    }
    return v;
}

vector<vector<int>> ReadBoarderFile(string path)
{
    ifstream my_file;
    my_file.open(path);
    if (my_file)
    {
        cout << "The FIle stream has been created!" << std::endl;
        string line;
        vector<vector<int>> v;
        while (getline(my_file, line))
        {
            cout << line << std::endl;
            int n;
            char c;
            istringstream stream(line);
            vector<int> v1;
            while (stream >> n >> c)
            {
                cout << n << " " << c;
                v1.push_back(n);
            }
            v.push_back(v1);
        }
    }
}

void PrintBoard(vector<vector<int>> v)
{
    cout << "PrintBoard"
         << "\n";
    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = 0; j < v[i].size(); ++j)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "Hello world" << endl;
    auto board = ReadBoarderFile("1.board");
    PrintBoard(board);
}