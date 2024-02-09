#include <bits/stdc++.h>
#include "helper.h"
#include "token.h"
#include "sequence.h"
#include "gamematrix.h"
using namespace std;
//Atribut untuk menyelesaikan tucil
//Atribut jawaban akhir
string OptimalFinalAnswer; //string jawaban
int MaxPoints; //jawaban poin maksimal
int MinBuffer; //jawaban buffer minimal
vector<Token> TokenListFinalAnswer; //daftar token yang dipilih sebagai jawaban akhir
vector<pair<int,int> > CoordinateListFinalAnswer; //daftar koordinat yang dipilih sebagai jawaban akhir

int MatrixRow,MatrixCol; //panjang baris dan kolom kedua matriks di atas
int bufferSize; //panjang buffer
int sequenceSize;//banyak sequence
vector<pair<int,int> > CoordinateStack;//stack yang berisi koordinat tempat
vector<TokenSequence> SequenceList; //daftar sequence yang ada
vector<bool> SequenceCheckList; //list yang berfungsi untuk mengecek apakah sequence sudah pernah ada atau belum

bool AllSequenceValid; //mengecek apakah semua sequence valid
set<string> validTokens;// himpunan daftar token yang valid
vector<vector<string> > inputStringMatrix;
//debugging
// string test,out;
// stack<string> Stack1, Stack2;
void SolveOptimal(GameMatrix gameMatrix, string state, string currentAnswer, int BufferLeft, int currentPoints, 
vector<Token> currentTokenList, vector<pair<int, int> >  currentCoordinateList,int currentRow, int currentCol ,
int currentBuffer, vector<bool> currentSequenceCheckList, vector<TokenSequence> currentSequenceList){
    if(BufferLeft<=0){ //Basecase: jika BufferLeft<=0, jangan jalankan prosedur ini karena buffer sudah penuh.
        return;
    }

    if(state == "Horizontal"){
        for(int i = 0; i<MatrixCol; i++){
            if(gameMatrix.GetVisitedCell(currentRow,i)){//Jika token di sel[currentRow][i] belum dikunjungi
                string newAnswer = currentAnswer + gameMatrix.GetTokenCell(currentRow,i).GetTokenString(); //Tambahkan string token yang ditunjuk ke string answer
                vector<Token> newTokenList = currentTokenList; 
                newTokenList.push_back(gameMatrix.GetTokenCell(currentRow,i));//Push token ke TokenList dari belakang
                pair<int,int> currentCoordinate = make_pair(i+1,currentRow+1);
                vector<pair<int,int> > newCoordinateList = currentCoordinateList;
                newCoordinateList.push_back(currentCoordinate); //Push koordinat saat ini ke CoordinateList dari belakang
                gameMatrix.SetVisitedCell(currentRow,i,true); //Tandai sel[currentRow][i] sudah dikunjungi
                int newBufferLeft,newPoints,newBufferCount,PointAddition;
                newBufferLeft = BufferLeft-1; //Kurangi BufferLeft dengan 1
                newBufferCount = currentBuffer+1; //Tambahkan currentBuffer dengan 1
                PointAddition = 0; //Buat variabel PointAddition untuk menentukan tambahan poin dengan cara berikut:
                vector<bool> newSequenceCheckList = currentSequenceCheckList;
                for(int i = 0; i<currentSequenceList.size(); i++){ //1.	Cek semua sequence di SequenceList
                    if(!newSequenceCheckList[i]){ //Jika nilai SequenceCheckList dari Sequence yang diperiksa bernilai false
                        if(newAnswer.find(currentSequenceList[i].GetSequenceString()) != string::npos){//Jika string dari sequence tersebut adalah substring dari newAnswer, maka
                            PointAddition+=currentSequenceList[i].GetSequencePoints(); //Tambahkan PointAddition dengan poin yang dimiliki oleh sequence tersebut
                            newSequenceCheckList[i] = true; //Tandai SequenceCheckList dari sequence yang diperiksa jadi true
                        }
                    }
                }
                newPoints = currentPoints + PointAddition; //Tambahkan currentPoints dengan PointAddition
                //BELUM DITAMBAHKAN Update jawaban
                SolveOptimal(gameMatrix,"Vertical",newAnswer,newBufferLeft,newPoints,newTokenList,newCoordinateList,currentRow,i,newBufferCount,newSequenceCheckList,currentSequenceList);
                //Panggil fungsi ini lagi secara rekursif dengan parameter yang sudah diupdate di atas ditambah dengan nilai currentCol = i, nilai currentRow sama, dan state = “Vertical”
                //BELUM DIKERJAKAN Batalkan semua perubahan parameter untuk iterasi berikutnya
            }
        }
    } else if(state == "Vertical"){
        //BELUM DIKERJAKAN
    }
}
void UpdateAnswer(){

}
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
        string TempString;
        int tempPoints;
        cin.ignore();
        getline(cin,TempString);
        cin>>tempPoints;
        vector<string> StringList;
        vector<Token> TokenList;
        StringList = StringToStringList(TempString);
        TokenList = StringListToTokenList(StringList,validTokens);
        TokenSequence tokenSequence = TokenSequence(TokenList,tempPoints);
        SequenceList.push_back(tokenSequence);
    }
    GameMatrix gameMatrix = GameMatrix(MatrixRow,MatrixCol,validTokens);
    gameMatrix.InputGameMatrix(inputStringMatrix,validTokens);
    gameMatrix.PrintTokenMatrix();
    gameMatrix.PrintVisitedMatrix();
    cout<<gameMatrix.GetGameMatrixValidity()<<"\n";
    return 0;
}