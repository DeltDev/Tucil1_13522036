#include <bits/stdc++.h>
// #include "helper.h"
#include "token.h"
#include "sequence.h"
#include "gamematrix.h"
using namespace std;
//Atribut untuk menyelesaikan tucil
string OptimalAnswer; //string jawaban
int pointsCounter; //poin yang dipegang sekarang
int MaxPoints; //poin maksimal
int bufferCounter; //banyak buffer yang diambil sekarang
int MinBuffer; //buffer minimal

int MatrixRow,MatrixCol; //panjang baris dan kolom kedua matriks di atas
int bufferSize; //panjang buffer
int sequenceSize;
stack<pair<int,int> > CoordinateStack;//stack yang berisi koordinat tempat
vector<TokenSequence> SequenceList; //daftar sequence yang ada
vector<bool> SequenceCheckList; //list yang berfungsi untuk mengecek apakah sequence sudah pernah ada atau belum

bool isTokenMatrixValid; //mengecek apakah semua token pada matriks valid
bool AllSequenceValid; //mengecek apakah semua sequence valid
set<string> validTokens;// himpunan daftar token yang valid
vector<vector<string> > inputStringMatrix;
//debugging
// string test,out;
// stack<string> Stack1, Stack2;
int main(){
    cout<<"Masukkan panjang buffer\n";
    cin>>bufferSize;
    cout<<"Masukkan ukuran matriks (format: banyak kolom <spasi> banyak baris):"<<"\n";
    cin>>MatrixCol>>MatrixRow;
    cout<<"Masukkan matriks token:\n";

    for(int i = 0; i<MatrixRow;i++){//inisialisasi inputStringMatrix
        vector<string> TempStringList;
        for(int j = 0; j<MatrixCol; j++){
            TempStringList.push_back(".");
        }
        inputStringMatrix.push_back(TempStringList);
    }
    for(int i = 0; i<MatrixRow; i++){
        for(int j = 0; j<MatrixCol; j++){
            cin>>inputStringMatrix[i][j];
            validTokens.insert(inputStringMatrix[i][j]);
        }
    }
    cout<<"Masukkan banyak sequence: \n";
    cin>>sequenceSize;
    cout<<"Masukkan sequence dan poinnya (sequence dan poin dipisahkan dengan enter): \n";
    for(int i = 0; i<sequenceSize; i++){
        string TempSequence;
        int tempPoints;
        cin.ignore();
        getline(cin,TempSequence);
        cin>>tempPoints;
    }
    GameMatrix gameMatrix = GameMatrix(MatrixRow,MatrixCol,validTokens);
    gameMatrix.InputGameMatrix(inputStringMatrix,validTokens);
    gameMatrix.PrintTokenMatrix();
    gameMatrix.PrintVisitedMatrix();
    cout<<gameMatrix.GetGameMatrixValidity()<<"\n";
    return 0;
}