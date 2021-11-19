#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <regex>

using namespace std;

void print_screen(vector<vector<char>>);
void rect(vector<int>, vector<vector<char>>&);
void rotate_row(vector<int>, vector<vector<char>>&);
void rotate_column(vector<int>, vector<vector<char>>&);

tuple<void(*)(vector<int>, vector<vector<char>>&),vector<int>> parse_command(string line)
{
    regex rect_regex("rect (\\d+)x(\\d+)");
    regex rotate_row_regex("rotate row y=(\\d+) by (\\d+)");
    regex rotate_column_regex("rotate column x=(\\d+) by (\\d+)");
    smatch match;

    if (regex_match(line, match, rect_regex)) {
        return make_tuple(&rect, vector<int>{stoi(match[1]), stoi(match[2])});
    }

    if (regex_match(line, match, rotate_row_regex)) {
        return make_tuple(&rotate_row, vector<int>{stoi(match[1]), stoi(match[2])});
    }

    if (regex_match(line, match, rotate_column_regex)) {
        return make_tuple(&rotate_column, vector<int>{stoi(match[1]), stoi(match[2])});
    }
}

void rect(vector<int> args, vector<vector<char>> &screen)
{
    int width = args[0], height = args[1];

    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            screen[y][x] = '#';
        }
    }
}

void rotate_row(vector<int> args, vector<vector<char>> &screen)
{
    int row = args[0];
    int offset = args[1];
    char item;

    for (int i=0; i<offset; i++) {
        item = screen[row].back();
        screen[row].pop_back();
        screen[row].insert(screen[row].begin(), item);
    }
}

void rotate_column(vector<int> args, vector<vector<char>> &screen)
{
    int column = args[0];
    int offset = args[1];
    char prev, keep;

    for (int i=0; i<offset; i++) {
        prev = screen[0][column];
        for (int y=0; y<screen.size(); y++) {
            keep = screen[(y+1)%screen.size()][column];
            screen[(y+1)%screen.size()][column] = prev;
            prev = keep;
        }
    }
}

void print_screen(vector<vector<char>> screen)
{
    for (auto row : screen) {
        for (auto pixel : row) {
            cout << pixel;
        }
        cout << endl;
    }
}

int main(void) {
    string line;
    ifstream fin;
    int total = 0;
    vector<vector<char>> screen;
    void (*cmd)(std::vector<int>, std::vector<std::vector<char>>&);
    vector<int> args;

    for (int row=0; row<6; row++) {
        screen.push_back(vector<char> {});
        for (int column=0; column<50; column++) {
            screen[row].push_back('.');
        }
    }

    fin.open("08.dat");
    while(!fin.eof()) {
        getline(fin, line);
        if (line == "") continue;

        cout << "Parsing line '" << line << endl;
        auto parse_output = parse_command(line);
        cmd = get<0>(parse_output);
        args = get<1>(parse_output);
        cmd(args, screen);
        print_screen(screen);
    }

    total = 0;
    for (auto line : screen) {
        for (auto pixel : line) {
            if (pixel == '#') {
                total += 1;
            }
        }
    }

    cout << "Pixels lit:" << total << endl;

    fin.close();
}
