#include <bits/stdc++.h>
#include "helper.h"
#include "token.h"
#include "sequence.h"
using namespace std;
//Atribut untuk menyelesaikan tucil
string OptimalAnswer; //string jawaban
int pointsCounter; //poin yang dipegang sekarang
int MaxPoints; //poin maksimal
int bufferCounter; //banyak buffer yang diambil sekarang
int MinBuffer; //buffer minimal
vector<vector<Token> > TokenMatrix; //Matriks yang berisi token
vector<vector<bool> > VisitedMatrix;//matriks yang menentukan apakah string sudah dikunjungi atau belum
int MatrixRow,MatrixCol; //panjang baris dan kolom kedua matriks di atas
int bufferSize; //panjang buffer
stack<pair<int,int> > CoordinateStack;//stack yang berisi koordinat tempat
vector<TokenSequence> SequenceList; //daftar sequence yang ada
vector<bool> SequenceCheckList; //list yang berfungsi untuk mengecek apakah sequence sudah pernah ada atau belum
vector<int> pointsList; //daftar poin yang dimiliki setiap sequence
bool isTokenMatrixValid; //mengecek apakah semua token pada matriks valid
bool AllSequenceValid; //mengecek apakah semua sequence valid
//debugging
// string test,out;
// stack<string> Stack1, Stack2;
int main(){

    // while(test != "."){
    //     cin>>test;
    //     if(test!= "."){
    //         Stack1.push(test);
    //     }

    // }
    // out = StringStackToString(Stack1);
    // Stack2 = FlipStack(Stack1);
    // cout<<out<<"\n";
    // out = StringStackToString(Stack2);
    // cout<<out<<"\n";
}