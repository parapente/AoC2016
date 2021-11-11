#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const vector<vector<char>> keypad = {
                                        {'-', '-', '1', '-', '-'},
                                        {'-', '2', '3', '4', '-'},
                                        {'5', '6', '7', '8', '9'},
                                        {'-', 'A', 'B', 'C', '-'},
                                        {'-', '-', 'D', '-', '-'}
                                    };

int main(void) {
    string line;
    ifstream fin;
    const string delimiter = "\n";
    vector<string> instructions;
    std::vector<int> coord = {1, 1};

    fin.open("02.dat");
    while(!fin.eof()) {
        getline(fin, line);
        if (line == "") continue;

        for (auto instruction : line) {
            switch(instruction) {
                case 'R':
                    if (coord[0] < (keypad[coord[1]].size() - 1) && keypad[coord[1]][coord[0] + 1] != '-') {
                        coord[0] += 1;
                    }
                    break;
                case 'L':
                    if (coord[0] > 0 && keypad[coord[1]][coord[0] - 1] != '-') {
                        coord[0] -= 1;
                    }
                    break;
                case 'U':
                    if (coord[1] > 0 && keypad[coord[1] - 1][coord[0]] != '-') {
                        coord[1] -= 1;
                    }
                    break;
                case 'D':
                    if (coord[1] < (keypad.size() - 1) && keypad[coord[1] + 1][coord[0]] != '-') {
                        coord[1] += 1;
                    }
            }
        }
        cout << keypad[coord[1]][coord[0]];
    }
    cout << endl;
}
