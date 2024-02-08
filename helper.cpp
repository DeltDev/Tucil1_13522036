#include <bits/stdc++.h>
#include "token.h"
#include "helper.h"
using namespace std;

vector<string> StringToStringList(string inputString){

}
vector<Token> StringListToTokenList(vector<string> StringList, set<string> ValidTokens){
    vector<Token> ListOut;
    for(int i = 0; i<StringList.size(); i++){
        Token temp = Token(StringList[i],ValidTokens);
        ListOut.push_back(temp);
    }
    return ListOut;
}
void PrintTokenList(vector<Token> TokenList){
    for(int i = 0; i<TokenList.size(); i++){
        cout<<TokenList[i].GetTokenString()<<"\n";
    }
}