#include <bits/stdc++.h>
#include "token.h"
#include "helper.h"
using namespace std;

vector<string> StringToStringList(string inputString){
    vector<string> StringList;
    string tempString;
    tempString = "";

    for(int i = 0; i<inputString.length(); i++){

        if(i == 0){
            if(inputString[i] != ' '){
                tempString = tempString + inputString[i];
            }
        } else {
            if(i == inputString.length()-1){
                if(inputString[i] != ' '){
                    tempString = tempString + inputString[i];
                }
                StringList.push_back(tempString);
                tempString = "";
            } else {
                if(inputString[i] == ' '){
                    if(inputString[i-1] !=' '){
                        StringList.push_back(tempString);
                        tempString = "";
                    }
                } else {
                    tempString = tempString + inputString[i];
                }
            }
        }
    }
    return StringList;
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

int isSubstring(string s1, string s2)
{

    if (s1.find(s2) != string::npos)
        return s1.find(s2);
    return -1;
}