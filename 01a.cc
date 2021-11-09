#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const vector<vector<int>> headings = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

vector<int> add_matrix(vector<int> m1, vector<int> m2) {
    vector<int> result;

    result.push_back(m1[0] + m2[0]);
    result.push_back(m1[1] + m2[1]);
    return result;
}
    
vector<int> mul_matrix(vector<int> m1, int num) {
    vector<int> result;

    result.push_back(m1[0] * num);
    result.push_back(m1[1] * num);
    return result;
}

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int main(void) {
    string line;
    ifstream fin;
    const string delimiter = ", ";
    vector<string> instructions;
    std::vector<int> coord = {0, 0};
    int heading = 0;
    char command;
    int steps;

    fin.open("01.dat");
    getline(fin, line);

    instructions = split(line, delimiter);
    for (auto instruction : instructions) {
        command = instruction[0];
        steps = stoi(instruction.substr(1));
        if (command == 'R') {
            heading++;
            if (heading >= headings.size()) {
                heading = 0;
            }
        }
        else {
            heading--;
            if (heading < 0) {
                heading = headings.size() - 1;
            }
        }
        coord = add_matrix(coord, mul_matrix(headings[heading], steps));
    }
    cout << coord[0]+coord[1] << endl;
}
