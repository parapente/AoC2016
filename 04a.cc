#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <regex>

using namespace std;

string replace_all(string str, const string &from, const string &to) {
    string result = str;

    if(from.empty())
        return result;
    size_t start_pos = 0;
    while((start_pos = result.find(from, start_pos)) != string::npos) {
        result.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }

    return result;
}

vector<tuple<char, int>> letter_frequency(string name)
{
    map<char, int> letters;

    for (auto letter : name) {
        try {
            letters[letter] = letters[letter] + 1;
        }
        catch(out_of_range error) {
            letters[letter] = 1;
        }
    }
    
    vector<tuple<char, int>> result;
    for (const auto [key, value] : letters) {
        result.push_back(tuple<char, int>{key, value});
    }
    return result;
}

bool sort_compare(tuple<char, int> const &a, tuple<char, int> const &b)
{
    return (get<1>(a) > get<1>(b) || ((get<1>(a) == get<1>(b)) && (get<0>(a) < get<0>(b))));
}

string calc_checksum(string name)
{
    vector<tuple<char, int>> letters;
    string checksum;

    letters = letter_frequency(replace_all(name, "-", ""));
    sort(letters.begin(), letters.end(), sort_compare);
    for (auto letter : letters) {
        checksum += get<0>(letter);
    }

    return checksum.substr(0, 5);
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
    const string delimiter = "\n";
    vector<string> instructions;
    vector<string> sides, other_sides;
    string room_name, sector_id, checksum;
    int total = 0;
    smatch string_match;

    regex line_parse ("(.+)-(\\d+)\\[(.{5})\\]");

    fin.open("04.dat");
    while(!fin.eof()) {
        getline(fin, line);
        if (line == "") continue;

        if(regex_match(line, string_match, line_parse)) {
            room_name = string_match[1];
            sector_id = string_match[2];
            checksum = string_match[3];
            if (calc_checksum(room_name) == checksum)
                total += stoi(sector_id);
        }
        else {
            cout << "Line not matched! (" << line << ")" << endl;
        }
    }
    cout << total << endl;
}
