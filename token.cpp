#include <bits/stdc++.h>
#include "token.h"

using namespace std;
Token::Token(string InputString){
    TokenString = InputString;
}

bool Token::isTokenValid(string InputString){
    if(InputString == "BD"){
        return true;
    } else {
        return false;
    }
}
