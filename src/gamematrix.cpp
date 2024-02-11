#include <bits/stdc++.h>
#include "token.h"
#include "gamematrix.h"

using namespace std;

GameMatrix::GameMatrix(int Row, int Col,set <string> ValidTokenStrings){
    RowSize = Row;
    ColSize = Col;
    isGameMatrixValid = false;
    InitiateTokenMatrix(ValidTokenStrings);
    InitiateVisitedMatrix();
}
void GameMatrix::InitiateTokenMatrix(set<string> ValidTokenStrings){
    for(int i = 0; i<RowSize; i++){
        vector<Token> rowInit;
        
        for(int j = 0; j<ColSize; j++){
            Token TokenInit = Token(".",ValidTokenStrings);
            rowInit.push_back(TokenInit);
        }
        TokenMatrix.push_back(rowInit);
        rowInit.clear();
    }
} 
void GameMatrix::InitiateVisitedMatrix(){
    for(int i = 0; i<RowSize; i++){
        vector<bool> rowInit;
        for(int j = 0; j<ColSize; j++){
            rowInit.push_back(false);
        }
        VisitedMatrix.push_back(rowInit);
        rowInit.clear();
    }
} 
Token GameMatrix::GetTokenCell(int Row, int Col){
    return TokenMatrix[Row][Col];
}
bool GameMatrix::GetVisitedCell(int Row, int Col){
    return VisitedMatrix[Row][Col];
}

void GameMatrix::SetVisitedCell(int Row, int Col, bool cellValue){
    VisitedMatrix[Row][Col] = cellValue;
    return;
}

void GameMatrix::SetTokenCell(int Row, int Col, Token value){
    TokenMatrix[Row][Col] = value;
    return;
}
int GameMatrix::GetCol(){
    return ColSize;
}

int GameMatrix::GetRow(){
    return RowSize;
}

void GameMatrix::PrintTokenMatrix(){
    for(int i = 0; i<RowSize; i++){
        for(int j = 0; j<ColSize; j++){
            if(j == ColSize-1){
                cout<<TokenMatrix[i][j].GetTokenString();
            } else{
                cout<<TokenMatrix[i][j].GetTokenString() + " ";
            }
        }
        cout<<"\n";
    }
}

void GameMatrix::PrintVisitedMatrix(){
    for(int i = 0; i<RowSize; i++){
        for(int j = 0; j<ColSize; j++){
            if(j == ColSize-1){
                cout<<VisitedMatrix[i][j];
            } else{
                cout<<VisitedMatrix[i][j]<<" ";
            }
        }
        cout<<"\n";
    }
}
bool GameMatrix::GetGameMatrixValidity(){
    return isGameMatrixValid;
}

void GameMatrix::CheckGameMatrixValidity(){
    isGameMatrixValid = true;
    for(int i = 0; i<RowSize; i++){
        for(int j = 0; j<ColSize; j++){
            if(!TokenMatrix[i][j].GetTokenValidity()){
                isGameMatrixValid = false;
                return;
            }
        }
    }
    return;
}

void GameMatrix::InputGameMatrix(vector<vector<string> > StringMatrix, set<string> ValidTokenStrings){
    for(int i = 0; i<RowSize; i++){
        for(int j = 0; j<ColSize; j++){
            TokenMatrix[i][j] = Token(StringMatrix[i][j], ValidTokenStrings);
        }
    }
    CheckGameMatrixValidity();
}