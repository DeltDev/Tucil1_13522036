#ifndef TOKEN_H
#define TOKEN_H
#include <bits/stdc++.h>

using namespace std;
//Token adalah object yang berupa string
class Token{
    private:
        string TokenString; //string token
        bool isValidToken; //cek apakah token valid
        bool isTokenValid(string InputString); //periksa apakah token valid
    public:
        Token(string InputString); //konstruktor token
        string GetTokenString(); //mengembalikan nilai TokenString
        bool GetTokenValidity(); //mengembalikan nilai isValidToken
};

#endif