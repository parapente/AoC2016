#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

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
    const string delimiter = "\n";
    vector<string> instructions;
    vector<string> sides, other_sides;
    vector<vector<string>> candidates = {{}, {}, {}};
    string tmp_string;
    bool is_triangle;
    int triangles = 0;
    int side_sum;
    smatch string_match;
    int counter = 0;

    regex space_regex ("\\s+");
    regex item_between_spaces_regex("\\s*([\\d\\s]+)\\s*");

    fin.open("03.dat");
    while(!fin.eof()) {
        getline(fin, line);
        if (line == "") continue;

        counter++;
        tmp_string = regex_replace(line, space_regex, " ");
        regex_match(tmp_string, string_match, item_between_spaces_regex);
        tmp_string = string_match[1];
        sides = split(tmp_string, " ");
        for (int i=0; i < sides.size(); i++) {
            candidates[i].push_back(sides[i]);
        }

        if (counter % 3 == 0) {
            for (auto candidate : candidates) {
                is_triangle = true;
                for (auto side : candidate) {
                    other_sides = candidate;
                    for (vector<string>::iterator it = other_sides.begin(); it != other_sides.end(); ++it) {
                        if (*it == side) {
                            other_sides.erase(it);
                            break;
                        }
                    }
                    side_sum = 0;
                    for (vector<string>::iterator it = other_sides.begin(); it != other_sides.end(); ++it) {
                        side_sum += stoi(*it);
                    }

                    if (side_sum <= stoi(side)) {
                        is_triangle = false;
                        break;
                    }
                }
                if (is_triangle)
                    triangles += 1;
            }

            for (int i = 0; i < candidates.size(); i++) {
                candidates[i].clear();
            }
        }
    }
    cout << triangles << endl;
}
