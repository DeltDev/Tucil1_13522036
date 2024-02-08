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

vector<vector <TemplateDataType> > CreateNewMatrix(int Row, int Col){
    vector<vector <TemplateDataType> > NewMatrix(Row, vector<TemplateDataType> Col);
    return NewMatrix;
}
void PrintMatrix(int Row, int Col, vector<vector<TemplateDataType> > Matrix){
    for (int i = 0; i<Row; i++){
        for(int j = 0; j<Col; j++){
            if(j == Col-1){
                cout<<Matrix[i][j];
            } else {
                cout<<Matrix[i][j]<<" ";
            }
        }
        cout<<"\n";
    }
}
