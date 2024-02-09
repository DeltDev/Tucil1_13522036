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
vector<pair<int,int> > CoordinateList;//List yang berisi koordinat tempat
vector<TokenSequence> SequenceList; //daftar sequence yang ada
vector<bool> SequenceCheckList; //list yang berfungsi untuk mengecek apakah sequence sudah pernah ada atau belum

bool AllSequenceValid; //mengecek apakah semua sequence valid
set<string> validTokens;// himpunan daftar token yang valid
vector<vector<string> > inputStringMatrix;
void UpdateFinalAnswer(int currentPoints, int currentBuffer, vector<Token> currentTokenList, vector<pair<int,int> > currentCoordinateList){
    cout<<"Masuk Update Final Answer"<<"\n";
    if(MaxPoints < currentPoints){ //Jika poin akhir saat ini < currentPoints
        MaxPoints = currentPoints; //Update poin akhir dengan currentPoints
        MinBuffer = currentBuffer; //Update buffer akhir dengan currentBuffer
        TokenListFinalAnswer = currentTokenList; //Update Token List akhir dengan currentTokenList
        CoordinateListFinalAnswer = currentCoordinateList; //Update Coordinate List akhir dengan currentCoordinateList
    } else if(MaxPoints == currentPoints){ //Jika poin akhir saat ini = currentPoints
        if(MinBuffer > currentBuffer){ //Jika buffer akhir saat ini > currentBuffer
        //Update semua atribut akhir sama seperti dengan kondisi jika poin akhir < currentPoints
            MaxPoints = currentPoints; 
            MinBuffer = currentBuffer;
            TokenListFinalAnswer = currentTokenList;
            CoordinateListFinalAnswer = currentCoordinateList;
        }
    }//Jika poin akhir saat ini > currentPoints, jangan update jawaban
    return;
}
//debugging
// string test,out;
// stack<string> Stack1, Stack2;
void SolveOptimal(GameMatrix gameMatrix, string state, string currentAnswer, int BufferLeft, int currentPoints, 
vector<Token> currentTokenList, vector<pair<int, int> >  currentCoordinateList,int currentRow, int currentCol ,
int currentBuffer, vector<bool> currentSequenceCheckList, vector<TokenSequence> currentSequenceList){
    cout<<"Masuk Solve Optimal"<< "BufferLeft="<<BufferLeft<<"\n";
    if(BufferLeft<=0){ //Basecase: jika BufferLeft<=0, jangan jalankan prosedur ini karena buffer sudah penuh.
        return;
    }
    string newAnswer;
    newAnswer = currentAnswer;
    vector<Token> newTokenList;
    newTokenList = currentTokenList; 
    vector<pair<int,int> > newCoordinateList = currentCoordinateList;
    int newBufferLeft,newPoints,newBufferCount,PointAddition;
    newBufferLeft = BufferLeft;
    newBufferCount = currentBuffer;
    PointAddition = 0;
    vector<bool> newSequenceCheckList = currentSequenceCheckList;
    pair<int,int> currentCoordinate;
    if(state == "Horizontal"){
        cout<<"Masuk State Horizontal"<<"\n";
        for(int i = 0; i<MatrixCol; i++){
            if(!gameMatrix.GetVisitedCell(currentRow,i)){//Jika token di sel[currentRow][i] belum dikunjungi
                newAnswer = newAnswer + gameMatrix.GetTokenCell(currentRow,i).GetTokenString(); //Tambahkan string token yang ditunjuk ke string answer
                newTokenList.push_back(gameMatrix.GetTokenCell(currentRow,i));//Push token ke TokenList dari belakang
                currentCoordinate = make_pair(i+1,currentRow+1);
                newCoordinateList.push_back(currentCoordinate); //Push koordinat saat ini ke CoordinateList dari belakang
                gameMatrix.SetVisitedCell(currentRow,i,true); //Tandai sel[currentRow][i] sudah dikunjungi
                
                newBufferLeft--; //Kurangi BufferLeft dengan 1
                newBufferCount++; //Tambahkan currentBuffer dengan 1
                
                for(int i = 0; i<currentSequenceList.size(); i++){ //1.	Cek semua sequence di SequenceList
                    if(!newSequenceCheckList[i]){ //Jika nilai SequenceCheckList dari Sequence yang diperiksa bernilai false
                        if(newAnswer.find(currentSequenceList[i].GetSequenceString()) != string::npos){//Jika string dari sequence tersebut adalah substring dari newAnswer, maka
                            PointAddition+=currentSequenceList[i].GetSequencePoints(); //Tambahkan PointAddition dengan poin yang dimiliki oleh sequence tersebut
                            newSequenceCheckList[i] = true; //Tandai SequenceCheckList dari sequence yang diperiksa jadi true
                        }
                    }
                }
                newPoints = currentPoints + PointAddition; //Tambahkan currentPoints dengan PointAddition
                UpdateFinalAnswer(newPoints,newBufferCount, newTokenList, newCoordinateList);//Update jawaban
                SolveOptimal(gameMatrix,"Vertical",newAnswer,newBufferLeft,newPoints,newTokenList,newCoordinateList,currentRow,i,newBufferCount,newSequenceCheckList,currentSequenceList);
                //Panggil fungsi ini lagi secara rekursif dengan parameter yang sudah diupdate di atas ditambah dengan nilai currentCol = i, nilai currentRow sama, dan state = “Vertical”
                //BELUM DIKERJAKAN Batalkan semua perubahan parameter untuk iterasi berikutnya
                newAnswer.erase(newAnswer.size() - gameMatrix.GetTokenCell(currentRow,i).GetTokenString().length());//1. Hapus string token yang ditunjuk dari string answer (hapus token terakhir yang ditambahkan)
                newTokenList.pop_back();//2. pop newTokenList dari belakang
                newCoordinateList.pop_back();//3. Pop CoordinateList dari belakang
                gameMatrix.SetVisitedCell(currentRow,i,false);//4. Tandai sel[currentRow][i] belum dikunjungi
                newBufferLeft++;//5. Tambah BufferLeft dengan 1
                newBufferCount--; //6. Kurangi currentBuffer dengan 1
                
            }
        }
    } else if(state == "Vertical"){
        cout<<"Masuk State Vertical"<<"\n";
        for(int i = 0; i<MatrixRow; i++){
            if(!gameMatrix.GetVisitedCell(i,currentCol)){//Jika token di sel[currentRow][i] belum dikunjungi
                newAnswer = newAnswer + gameMatrix.GetTokenCell(i,currentCol).GetTokenString(); //Tambahkan string token yang ditunjuk ke string answer
                newTokenList.push_back(gameMatrix.GetTokenCell(i,currentCol));//Push token ke TokenList dari belakang
                currentCoordinate = make_pair(currentCol+1,i+1);
                newCoordinateList.push_back(currentCoordinate); //Push koordinat saat ini ke CoordinateList dari belakang
                gameMatrix.SetVisitedCell(i,currentCol,true); //Tandai sel[currentRow][i] sudah dikunjungi
                
                newBufferLeft--; //Kurangi BufferLeft dengan 1
                newBufferCount++; //Tambahkan currentBuffer dengan 1
                
                for(int i = 0; i<currentSequenceList.size(); i++){ //1.	Cek semua sequence di SequenceList
                    if(!newSequenceCheckList[i]){ //Jika nilai SequenceCheckList dari Sequence yang diperiksa bernilai false
                        if(newAnswer.find(currentSequenceList[i].GetSequenceString()) != string::npos){//Jika string dari sequence tersebut adalah substring dari newAnswer, maka
                            PointAddition+=currentSequenceList[i].GetSequencePoints(); //Tambahkan PointAddition dengan poin yang dimiliki oleh sequence tersebut
                            newSequenceCheckList[i] = true; //Tandai SequenceCheckList dari sequence yang diperiksa jadi true
                        }
                    }
                }
                newPoints = currentPoints + PointAddition; //Tambahkan currentPoints dengan PointAddition
                UpdateFinalAnswer(newPoints,newBufferCount, newTokenList, newCoordinateList);//Update jawaban
                SolveOptimal(gameMatrix,"Horizontal",newAnswer,newBufferLeft,newPoints,newTokenList,newCoordinateList,i,currentCol,newBufferCount,newSequenceCheckList,currentSequenceList);
                //Panggil fungsi ini lagi secara rekursif dengan parameter yang sudah diupdate di atas ditambah dengan nilai currentCol = i, nilai currentRow sama, dan state = “Vertical”
                //BELUM DIKERJAKAN Batalkan semua perubahan parameter untuk iterasi berikutnya
                newAnswer.erase(newAnswer.size() - gameMatrix.GetTokenCell(i,currentCol).GetTokenString().length());//1. Hapus string token yang ditunjuk dari string answer (hapus token terakhir yang ditambahkan)
                newTokenList.pop_back();//2. pop newTokenList dari belakang
                newCoordinateList.pop_back();//3. Pop CoordinateList dari belakang
                gameMatrix.SetVisitedCell(i,currentCol,false);//4. Tandai sel[currentRow][i] belum dikunjungi
                newBufferLeft++;//5. Tambah BufferLeft dengan 1
                newBufferCount--; //6. Kurangi currentBuffer dengan 1
            }
        }
    }
}

int main(){
    MinBuffer = 999999999;
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

    SolveOptimal(gameMatrix,"Horizontal",OptimalFinalAnswer,bufferSize,MaxPoints,TokenListFinalAnswer,CoordinateListFinalAnswer,0,0,MinBuffer,SequenceCheckList,SequenceList);
    cout<<"Max points: "<<MaxPoints<<"\n";
    cout<<"Final Answer: ";
    for(int i = 0; i<TokenListFinalAnswer.size(); i++){
        cout<<TokenListFinalAnswer[i].GetTokenString()<<" ";
    }
    cout<<"\n";
    cout<<"Final Coordinates: \n";
    for(int i = 0; i<CoordinateListFinalAnswer.size(); i++){
        cout<<CoordinateListFinalAnswer[i].first<<","<<CoordinateListFinalAnswer[i].second<<" ";
    }
    cout<<"\n";
    return 0;
    return 0;
}