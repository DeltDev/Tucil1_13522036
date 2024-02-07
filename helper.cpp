#include <bits/stdc++.h>
#include "helper.h"

stack<TemplateDataType> FlipStack (stack<TemplateDataType> StackInput){
    stack<string> StackOut;

    stack<string> StackIn;
    StackIn = StackInput;

    while(!StackIn.empty()){
        StackOut.push(StackIn.top());
        StackIn.pop();
    }

    return StackOut;
}

string StringStackToString(stack <string> StringStack){
    string StringOut = "";
    string addition = "";
    stack<string> StackIn = StringStack;
    while(!StackIn.empty()){
        addition = StackIn.top();
        StackIn.pop();
        if(StackIn.empty()){
            StringOut = StringOut + addition;
        } else {
            StringOut = StringOut + addition + " ";
        }
    }

    return StringOut;
}

vector<vector <TemplateDataType> > InitiateNewMatrix(int Row, int Col){

}
void PrintMatrix(int Row, int Col, vector<vector<TemplateDataType> > Matrix){

}
vector<vector<TemplateDataType> > EmptyMatrix(){
    
}
