#include <bits/stdc++.h>
#include "token.h"

using namespace std;

Token::Token(string InputString,set<string> ValidTokenStrings){
    TokenString = InputString;
    isValidToken = isTokenValid(InputString,ValidTokenStrings);
}

bool Token::isTokenValid(string InputString, set<string> ValidTokenStrings){
    set<string> ValidTokens;
    ValidTokens = ValidTokenStrings;
    bool check = false;
    for(int i = 0; i<ValidTokens.size(); i++){
        if(ValidTokens.find(InputString) != ValidTokens.end()){
            check = true;
            break;
        }
    }
    return check;
}

string Token::GetTokenString(){
    return TokenString;
}

bool Token::GetTokenValidity(){
    return isValidToken;
}