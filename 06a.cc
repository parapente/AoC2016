#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main(void) {
    string line;
    ifstream fin;
    vector<map<char, int>> frequency;

    fin.open("06.dat");
    while(!fin.eof()) {
        getline(fin, line);
        if (line == "") continue;

        int i = 0;
        map<char, int> test;
        for(auto character : line) {
            try {
                auto test = frequency.at(i);
            }
            catch (out_of_range error) {
                frequency.push_back(test);
            }
            try {
                frequency[i][character] = frequency[i].at(character) + 1;
            }
            catch (out_of_range error) {
                frequency[i][character] = 1;
            }
            i++;
        }
    }
    for (auto column : frequency) {
        int max = 0;
        char character_max = ' ';
        for (auto character: column) {
            if (get<1>(character) > max) {
                max = get<1>(character);
                character_max = get<0>(character);
            }

        }
        cout << character_max;
    }

    cout << endl;

    fin.close();
}
