#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

enum State
{
    COPY,
    MARKER_START,
    MARKER_WHAT,
    MARKER_HOW_MANY,
    MARKER_END,
};

class Marker
{
    public:
        int times = 0;
        int chars = 0;
};

long int get_decompressed_length(string buffer)
{
    State current_state = State::COPY;
    string temp_buffer;
    Marker *current_marker = new Marker();
    long int decompressed_length = 0;

    for(auto character : buffer) {
        if (current_state == State::COPY) {
            if (character == '(') {
                delete current_marker;
                current_marker = new Marker();
                current_state = State::MARKER_START;
            } else if (isprint(character)) {
                decompressed_length++;
            }
        } else if (current_state == State::MARKER_START) {
            temp_buffer += character;
            current_state = State::MARKER_WHAT;
        } else if (current_state == State::MARKER_WHAT) {
            if (character == 'x') {
                current_marker->chars = stoi(temp_buffer);
                temp_buffer = "";
                current_state = State::MARKER_HOW_MANY;
            } else {
                temp_buffer += character;
            }
        } else if (current_state == State::MARKER_HOW_MANY) {
            if (character == ')') {
                current_marker->times = stoi(temp_buffer);
                temp_buffer = "";
                current_state = State::MARKER_END;
            } else {
                temp_buffer += character;
            }
        } else if (current_state == State::MARKER_END) {
            temp_buffer += character;
            current_marker->chars--;
            if (current_marker->chars == 0) {
                decompressed_length += current_marker->times * get_decompressed_length(temp_buffer);
                temp_buffer = "";
                current_state = State::COPY;
            }
        }
    }
    return decompressed_length;
}


int main(void) {
    string line;
    ifstream fin;
    long int total = 0;

    fin.open("09.dat");
    while(!fin.eof()) {
        getline(fin, line);
        if (line == "") continue;

        total += get_decompressed_length(line);
    }

    cout << total << endl;

    fin.close();
}
