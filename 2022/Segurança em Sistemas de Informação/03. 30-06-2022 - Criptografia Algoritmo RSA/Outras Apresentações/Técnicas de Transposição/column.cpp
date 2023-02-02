// CPP program for illustrating
// Columnar Transposition Cipher
#include<bits/stdc++.h>
using namespace std;

// Encryption
string encryptMessage(string msg, string key) {
    map<int, int> keyMap;
    for (int i = 0; i < key.length(); i++) keyMap[key[i]] = i;
    int col = key.length();
    int row = msg.length() / col;
    if (msg.length() % col) row++;
    string cipher = "";
    for (map<int, int>::iterator itr = keyMap.begin(); itr != keyMap.end(); itr++) {
        for (int i = itr->second; i < msg.length(); i += col) {
            cipher += msg[i];
        }
    }
    return cipher;
}

// Decryption
string decryptMessage(string msg, string key) {
    map<int, int> keyMap;
    for (int i = 0; i < key.length(); i++) keyMap[key[i]] = i;
    int col = key.length();
    int row = msg.length() / col;
    if (msg.length() % col) row++;
    string plainText = msg;
    int j = 0;
    for (map<int, int>::iterator itr = keyMap.begin(); itr != keyMap.end(); itr++) {
        for (int i = itr->second; i < msg.length(); i += col) {
            plainText[i] = msg[j];
            j++;
        }
    }
    return plainText;
}

int main(void) {
    ifstream in;
    ofstream out;
    out.open("output.txt");
    in.open("texto.txt");
    stringstream strStream;
    strStream << in.rdbuf();
    string msg = strStream.str();
    string key = "HACK";
    string cipher = encryptMessage(msg, key);
    out << "Encrypted Message: " << cipher << endl;
    out << "Decrypted Message: " << decryptMessage(cipher, key) << endl;
    in.close();
    out.close();
    return 0;
}