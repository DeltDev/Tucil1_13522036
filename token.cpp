#include <bits/stdc++.h>
#include "token.h"

using namespace std;

Token::Token(string InputString){
    TokenString = InputString;
    isValidToken = isTokenValid(InputString);
}

bool Token::isTokenValid(string InputString){
    vector<string> ValidTokenStrings;
    ValidTokenStrings.push_back("1C");
    ValidTokenStrings.push_back("55");
    ValidTokenStrings.push_back("7A");
    ValidTokenStrings.push_back("BD");
    ValidTokenStrings.push_back("E9");
    ValidTokenStrings.push_back("FF");
    bool check = true;
    for(int i = 0; i<ValidTokenStrings.size(); i++){
        if(InputString != ValidTokenStrings[i]){
            check = false;
            break;
        }
    }
    if(check){
        return true;
    } else {
        return false;
    }
}

string Token::GetTokenString(){
    return TokenString;
}

bool Token::GetTokenValidity(){
    return isValidToken;
}