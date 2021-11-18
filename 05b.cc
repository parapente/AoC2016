#include <fstream>
#include <iostream>
#include <string>

#include <openssl/md5.h>

using namespace std;

string hash_to_hex_string(unsigned char* md) {
    string result;
    char part[3];
    int i;
    for(i=0; i <MD5_DIGEST_LENGTH; i++) {
        sprintf(part, "%02x", md[i]);
        result += part;
    }

    return result;
}

char random_hex_char(void) {
    char result[2];
    sprintf(result, "%x", rand() % 16);
    return result[0];
}

int main(void) {
    string data;
    ifstream fin;
    string password = "________";
    string fancy_password;
    string test_string, hex_string;
    int i, position, index, chars_found = 0;
    unsigned char result[MD5_DIGEST_LENGTH];

    fin.open("05.dat");
    getline(fin, data);
    i = 0;
    while (chars_found < 8) {
        test_string = data + to_string(i);
        MD5((unsigned char*) test_string.c_str(), test_string.length(), result);
        hex_string = hash_to_hex_string(result);
        if (hex_string.substr(0, 5).compare("00000") == 0) {
            position = stoi(hex_string.substr(5, 1), nullptr, 16);
            if (position < 8 && password[position] == '_') {
                password[position] = hex_string[6];
                chars_found += 1;
            }
        }
        i += 1;
        fancy_password = password;
        index = 0;
        for (auto character : fancy_password) {
            if (character == '_') {
                fancy_password[index] = random_hex_char();
            }
            index++;
        }
        cout << "password: " << fancy_password << "\r";
    }

    cout << endl << password << endl;
    fin.close();
}
