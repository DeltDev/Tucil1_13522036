#include <bits/stdc++.h>
#include "token.h"
using namespace std;
vector<string> StringToStringList(string inputString); //untuk melakukan stripping token dari string yang mengandung spasi
vector<Token> StringListToTokenList(vector<string> StringList, set<string> ValidTokens);
//debugger
void PrintTokenList(vector<Token> TokenList);

