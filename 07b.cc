#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

vector<string> get_aba_bab(string ip_part)
{
    int i = 0;
    vector<string> result;

    while (i < (ip_part.length() - 2)) {
        if (ip_part[i] == ip_part[i+2] && ip_part[i] != ip_part[i+1]) {
            result.push_back(ip_part.substr(i, 3));
        }
        i += 1;
    }

    return result;
}

bool check_ssl(vector<string> supernet, vector<string> hypernet)
{
    bool result = false;

    for (auto aba : supernet) {
        const string bab = string()+aba[1]+aba[0]+aba[1];
        for (auto hyper : hypernet) {
            if (bab.compare(hyper) == 0) {
                result = true;
            }
        }
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

        vector<string> supernet;
        vector<string> hypernet;
    
        int i = 0;
        for (auto part : explode(replace_all(line, "]", "["), '[')) {
            const vector<string> aba_bab = get_aba_bab(part);
            if ((i % 2) == 0) {
                supernet.insert(supernet.end() , aba_bab.begin(), aba_bab.end());
            } else {
                hypernet.insert(hypernet.end(), aba_bab.begin(), aba_bab.end());
            }
            i++;
        }

        const bool valid = check_ssl(supernet, hypernet);
        if (valid) {
            total++;
        }
    }

    cout << total << endl;

    fin.close();
}
