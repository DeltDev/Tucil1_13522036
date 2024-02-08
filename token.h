#ifndef TOKEN_H
#define TOKEN_H
#include <bits/stdc++.h>

using namespace std;
//Token adalah object yang berupa string (sel individu pada matrix dan sequence)
class Token{
    private:
        string TokenString; //string token
        bool isValidToken; //cek apakah token valid
        //token yang valid adalah token yang memiliki nilai TokenString berupa salah satu dari string berikut: "1C", "55", "7A", "BD", "E9", "FF"
        bool isTokenValid(string InputString, set<string> ValidTokenStrings); //periksa apakah token valid
    public:
        Token(string InputString, set<string> ValidTokenStrings); //konstruktor token
        string GetTokenString(); //mengembalikan nilai TokenString
        bool GetTokenValidity(); //mengembalikan nilai isValidToken
};

#endif