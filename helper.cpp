#include <bits/stdc++.h>
#include "token.h"

using namespace std;

void PrintTokenList(vector<Token> TokenList){
    for(int i = 0; i<TokenList.size(); i++){
        cout<<TokenList[i].GetTokenString()<<"\n";
    }
}