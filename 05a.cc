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

int main(void) {
    string data;
    ifstream fin;
    string password, test_string, hex_string;
    int i;
    unsigned char result[MD5_DIGEST_LENGTH];

    fin.open("05.dat");
    getline(fin, data);
    i = 0;
    while (password.length() < 8) {
        test_string = data + to_string(i);
        MD5((unsigned char*) test_string.c_str(), test_string.length(), result);
        hex_string = hash_to_hex_string(result);
        if (hex_string.substr(0, 5).compare("00000") == 0) {
            password += hex_string[5];
        }
        i += 1;
        cout << "password: " << password << " i:" << i << "\r";
    }

    cout << endl << password << endl;
    fin.close();
}
