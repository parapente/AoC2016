#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

bool is_abba(string ip_part)
{
    int i = 0;
    bool result = false;
    while (i < (ip_part.length() - 3)) {
        if (ip_part[i] == ip_part[i+3]
            && ip_part[i+1] == ip_part[i+2]
            && ip_part[i] != ip_part[i+1]
        ) {
            result = true;
        }
        i += 1;
    }
    return result;
}

bool multi_or(vector<bool> list)
{
    if (!list.size())
        return false;

    bool result = list[0];
    for (auto item : list) {
        result |= item;
    }
    
    return result;
}

vector<string> explode(string const & s, char delim)
{
    vector<string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }

    return result;
}

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

int main(void) {
    string line;
    ifstream fin;
    int total = 0;

    fin.open("07.dat");
    while(!fin.eof()) {
        getline(fin, line);
        if (line == "") continue;

        vector<bool> results;
        vector<bool> results_brackets;
    
        int i = 0;
        for (auto part : explode(replace_all(line, "]", "["), '[')) {
            if ((i % 2) == 0) {
                results.push_back(is_abba(part));
            } else {
                results_brackets.push_back(is_abba(part));
            }
            i++;
        }

        const bool valid = multi_or(results) && !multi_or(results_brackets);
        if (valid) {
            total++;
        }
    }

    cout << total << endl;

    fin.close();
}
