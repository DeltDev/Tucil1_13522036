#ifndef TOKEN_H
#define TOKEN_H
#include <bits/stdc++.h>

using namespace std;
//Token adalah object yang berupa string
class Token{
    public:
        string TokenString; //string token
        bool isTokenValid; //cek apakah token valid

        Token(string InputString); //konstruktor token
    private:
        bool isTokenValid(string InputString); //periksa apakah token valid
};

#endif