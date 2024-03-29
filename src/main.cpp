#include <bits/stdc++.h>
#include "helper.h"
#include "token.h"
#include "sequence.h"
#include "gamematrix.h"
using namespace std;
typedef chrono::milliseconds MSEC;
typedef chrono::high_resolution_clock HRC;
//Atribut untuk menyelesaikan tucil
//Atribut jawaban akhir
bool method; //metode input
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

set<string> validTokens;// himpunan daftar token yang valid
vector<vector<string> > inputStringMatrix;
void UpdateFinalAnswer(int currentPoints, int currentBuffer, vector<Token> currentTokenList, vector<pair<int,int> > currentCoordinateList){
    // cout<<"Masuk Update Final Answer"<<"\n";
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
int currentBuffer, vector<TokenSequence> currentSequenceList){
    // cout<<"Masuk Solve Optimal"<< "BufferLeft="<<BufferLeft<<"\n";
    if(BufferLeft<=0){ //Basecase: jika BufferLeft<=0, jangan jalankan prosedur ini karena buffer sudah penuh.
        return;
    }
    string newAnswer;
    newAnswer = currentAnswer;
    vector<Token> newTokenList;
    newTokenList = currentTokenList; 
    vector<pair<int,int> > newCoordinateList = currentCoordinateList;
    int newBufferLeft,newPoints,newBufferCount;
    newBufferLeft = BufferLeft;
    newBufferCount = currentBuffer;
    

    pair<int,int> currentCoordinate;
    int substringCheck;                
    if(state == "Horizontal"){
        // cout<<"Masuk State Horizontal"<<"\n";
        for(int i = 0; i<MatrixCol; i++){
            if(!gameMatrix.GetVisitedCell(currentRow,i)){//Jika token di sel[currentRow][i] belum dikunjungi
                newPoints = 0;
                newAnswer = newAnswer + gameMatrix.GetTokenCell(currentRow,i).GetTokenString(); //Tambahkan string token yang ditunjuk ke string answer
                newTokenList.push_back(gameMatrix.GetTokenCell(currentRow,i));//Push token ke TokenList dari belakang
                currentCoordinate = make_pair(i+1,currentRow+1);
                newCoordinateList.push_back(currentCoordinate); //Push koordinat saat ini ke CoordinateList dari belakang
                gameMatrix.SetVisitedCell(currentRow,i,true); //Tandai sel[currentRow][i] sudah dikunjungi
                
                newBufferLeft--; //Kurangi BufferLeft dengan 1
                newBufferCount++; //Tambahkan currentBuffer dengan 1
                
                for(int i = 0; i<currentSequenceList.size(); i++){ //1.	Cek semua sequence di SequenceList
                    substringCheck = isSubstring(newAnswer,currentSequenceList[i].GetSequenceString());

                    if(substringCheck != -1){//Jika string dari sequence tersebut adalah substring dari newAnswer, maka
                        newPoints+=currentSequenceList[i].GetSequencePoints(); //Tambahkan poin sesuai dengan yang ditentukan oleh sequence
                    }
                }

                
                UpdateFinalAnswer(newPoints,newBufferCount, newTokenList, newCoordinateList);//Update jawaban
                
                SolveOptimal(gameMatrix,"Vertical",newAnswer,newBufferLeft,newPoints,newTokenList,newCoordinateList,currentRow,i,newBufferCount,currentSequenceList);
                //Panggil fungsi ini lagi secara rekursif dengan parameter yang sudah diupdate di atas ditambah dengan nilai currentCol = i, nilai currentRow sama, dan state = “Vertical”
                //Batalkan semua perubahan parameter untuk iterasi berikutnya
                newAnswer.erase(newAnswer.size() - gameMatrix.GetTokenCell(currentRow,i).GetTokenString().length());//1. Hapus string token yang ditunjuk dari string answer (hapus token terakhir yang ditambahkan)
                newTokenList.pop_back();//2. pop newTokenList dari belakang
                newCoordinateList.pop_back();//3. Pop CoordinateList dari belakang
                gameMatrix.SetVisitedCell(currentRow,i,false);//4. Tandai sel[currentRow][i] belum dikunjungi
                newBufferLeft++;//5. Tambah BufferLeft dengan 1
                newBufferCount--; //6. Kurangi currentBuffer dengan 1
               
            }
        }
    } else if(state == "Vertical"){

        for(int i = 0; i<MatrixRow; i++){
            if(!gameMatrix.GetVisitedCell(i,currentCol)){//Jika token di sel[currentRow][i] belum dikunjungi
                newPoints = 0;
                newAnswer = newAnswer + gameMatrix.GetTokenCell(i,currentCol).GetTokenString(); //Tambahkan string token yang ditunjuk ke string answer
                newTokenList.push_back(gameMatrix.GetTokenCell(i,currentCol));//Push token ke TokenList dari belakang
                currentCoordinate = make_pair(currentCol+1,i+1);
                newCoordinateList.push_back(currentCoordinate); //Push koordinat saat ini ke CoordinateList dari belakang
                gameMatrix.SetVisitedCell(i,currentCol,true); //Tandai sel[currentRow][i] sudah dikunjungi
                
                newBufferLeft--; //Kurangi BufferLeft dengan 1
                newBufferCount++; //Tambahkan currentBuffer dengan 1

                for(int i = 0; i<currentSequenceList.size(); i++){ //1.	Cek semua sequence di SequenceList
                    substringCheck = isSubstring(newAnswer,currentSequenceList[i].GetSequenceString());

                    if(substringCheck != -1){//Jika string dari sequence tersebut adalah substring dari newAnswer, maka
                        newPoints+=currentSequenceList[i].GetSequencePoints(); //Tambahkan poin sesuai dengan yang ditentukan oleh sequence
                    }
                }

                // cout<<"Poin yang akan ditambahkan: "<<PointAddition<<"\n";
                // cout<<"Jumlah poin yang didapatkan dari sequence ini: "<<newPoints<<"\n";
                UpdateFinalAnswer(newPoints,newBufferCount, newTokenList, newCoordinateList);//Update jawaban
                
                SolveOptimal(gameMatrix,"Horizontal",newAnswer,newBufferLeft,newPoints,newTokenList,newCoordinateList,i,currentCol,newBufferCount,currentSequenceList);
                //Panggil fungsi ini lagi secara rekursif dengan parameter yang sudah diupdate di atas ditambah dengan nilai currentCol = i, nilai currentRow sama, dan state = “Vertical”
                //Batalkan semua perubahan parameter untuk iterasi berikutnya
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

void OutputFile(GameMatrix gameMatrix,bool method,auto exec_time){
    ofstream OutputFile;
    string OutputFileName = ""; //dummy
    string OutputPath = "../test/";
    cout<<"Masukkan nama file anda (WAJIB DIAKHIRI DENGAN '.txt'): "<<"\n";
    while(true){
        cin>>OutputFileName;
        if(isSubstring(OutputFileName,".txt") != -1){
            break;
        } else {
            cout<<"Format nama salah! Silahkan input nama file output lagi.\n";
        }
    }
    OutputFile.open(OutputPath+OutputFileName);
    if(method){ //jika metode yang dipilih adalah metode generation acak
        for(int i = 0; i<MatrixRow; i++){ //outputkan matriks ke file
            string RowOut = "";
            for(int j = 0; j<MatrixCol; j++){
                RowOut = RowOut + gameMatrix.GetTokenCell(i,j).GetTokenString();
                if(j != MatrixCol-1){
                    RowOut = RowOut + " ";
                }
            }
            OutputFile<<RowOut;
            OutputFile<<"\n";
        }
        OutputFile<<"\n";

        for(int i = 0; i<sequenceSize; i++){ //output semua sequence beserta poinnya
            string sequenceOut = "";
            for(int j = 0; j<SequenceList[i].GetSequence().size(); j++){
                sequenceOut = sequenceOut + SequenceList[i].GetSequence()[j].GetTokenString();
                if(j != SequenceList[i].GetSequence().size()-1){
                    sequenceOut = sequenceOut + " ";
                }
            }
            OutputFile<<sequenceOut;
            OutputFile<<"\n";
            OutputFile<<to_string(SequenceList[i].GetSequencePoints());
            OutputFile<<"\n";
        }
        OutputFile<<"\n";
    }
    
    OutputFile<<to_string(MaxPoints);
    OutputFile<<"\n";
    string SequenceFinalAnswer = "";
    for(int i = 0; i<TokenListFinalAnswer.size(); i++){
        SequenceFinalAnswer = SequenceFinalAnswer + TokenListFinalAnswer[i].GetTokenString();
        if(i != TokenListFinalAnswer.size()-1){
            SequenceFinalAnswer = SequenceFinalAnswer + " ";
        }
    }
    OutputFile<<SequenceFinalAnswer;
    OutputFile<<"\n";
    for(int i = 0; i<CoordinateListFinalAnswer.size(); i++){
        string CoordinateOut = to_string(CoordinateListFinalAnswer[i].first) + "," + to_string(CoordinateListFinalAnswer[i].second);
        OutputFile<<CoordinateOut;
        OutputFile<<"\n";
    }
    OutputFile<<exec_time.count();
    OutputFile<<" ms";
    OutputFile.close();
    cout<<OutputFileName<<" sudah tersimpan di folder test!\n";
}

void OutputAnswer(auto exec_time){
    cout<<"Max points: "<<MaxPoints<<"\n";
    cout<<"Final Answer: ";
    for(int i = 0; i<TokenListFinalAnswer.size(); i++){
        cout<<TokenListFinalAnswer[i].GetTokenString()<<" ";
    }
    cout<<"\n";
    cout<<"Final Coordinates: \n";
    for(int i = 0; i<CoordinateListFinalAnswer.size(); i++){
        cout<<CoordinateListFinalAnswer[i].first<<","<<CoordinateListFinalAnswer[i].second<<"\n";
    }
    cout<<"\n";
    cout<<exec_time.count()<<" ms\n";
}

void OutputFilePrompt(GameMatrix gameMatrix, bool choice,auto exec_time){
    cout<<"Apakah ingin menyimpan solusi sebagai file .txt? (Jawab dengan cara ketik HANYA dengan 'y' atau 'Y' untuk YA atau ketik selain kedua input tersebut untuk TIDAK): ";

        string answer;
        cin>>answer;
        if(answer == "y" || answer == "Y"){
            OutputFile(gameMatrix,choice,exec_time);
        }
}
int main(){
    
    cout<<"Masukkan metode input Breach Protocol yang diinginkan dengan mengetik:\n 0: input file \n 1: Random Matrix and Sequence generation\n";
    cin>>method;
    if(method){
        int validTokensAmount;
        cout<<"Masukkan banyak token yang valid: ";
        cin>>validTokensAmount;
        while(validTokensAmount<=0){ //handling input token valid
            cout<<"Banyak token yang valid yang diinput tidak valid! Silahkan input ulang:  ";
            cin>>validTokensAmount;
        }
        cout<<"Masukan daftar token yang valid: ";
        string ValidTokensListString;
        cin.ignore();
        getline(cin,ValidTokensListString); 
        vector<string> TokensStringList;
        TokensStringList = StringToStringList(ValidTokensListString);

        for(int i = 0; i<TokensStringList.size(); i++){
            validTokens.insert(TokensStringList[i]);
        }
        while(validTokens.size() != validTokensAmount){  //handling input token
            cout<<"Banyak token unik yang diinput tidak sesuai dengan banyak token valid! Silahkan input ulang: ";
            validTokens.clear();
            cin.ignore();
            getline(cin,ValidTokensListString); 
            TokensStringList = StringToStringList(ValidTokensListString);
            for(int i = 0; i<TokensStringList.size(); i++){
                validTokens.insert(TokensStringList[i]);
            }
        }
        vector<Token> ValidTokensList;
        ValidTokensList = StringListToTokenList(TokensStringList,validTokens);
        cout<<"Masukkan ukuran buffer: ";
        cin>>bufferSize;
        while(bufferSize<=0){ //handling ukuran buffer
            cout<<"Ukuran buffer tidak valid! Silahkan input ulang: ";
            cin>>bufferSize;
        }
        cout<<"Masukkan banyak baris dan kolom matriks: ";
        cin>>MatrixRow>>MatrixCol;

        while(MatrixCol <=0 || MatrixRow<=0){
            cout<<"Ukuran matriks tidak valid! Silahkan input ulang: ";
            cin>>MatrixRow>>MatrixCol;
        } 
        srand(time(NULL));
        GameMatrix gameMatrix = GameMatrix(MatrixRow,MatrixCol,validTokens);
        for(int i = 0; i<MatrixRow; i++){
            for(int j = 0; j<MatrixCol; j++){
                int ChosenToken = (rand() % validTokensAmount);
                gameMatrix.SetTokenCell(i,j,ValidTokensList[ChosenToken]);
            }
        }
        
        cout<<"Masukkan banyak sequence: ";
        cin>>sequenceSize;
        while(sequenceSize<=0){ //handling ukuran buffer
            cout<<"Banyak sequence tidak valid! Silahkan input ulang: ";
            cin>>sequenceSize;
        }
        int MaxSequenceLength;
        cout<<"Masukkan panjang sequence maksimum: ";
        cin>>MaxSequenceLength;
        while(MaxSequenceLength<=0){ //handling ukuran buffer
            cout<<"Panjang sequence maksimum tidak valid! Silahkan input ulang: ";
            cin>>MaxSequenceLength;
        }
        gameMatrix.PrintTokenMatrix();
        for(int i = 0; i<sequenceSize; i++){
            int SequenceLength = (rand() % MaxSequenceLength) +1;
            int ChosenPoints = (rand() % 101);
            vector<Token> GeneratedSequence;
            for(int i = 0; i<SequenceLength; i++){
                int ChosenToken = (rand() % validTokensAmount);
                GeneratedSequence.push_back(ValidTokensList[ChosenToken]);
            }
        
            TokenSequence newSequence = TokenSequence(GeneratedSequence,ChosenPoints);
            SequenceList.push_back(newSequence);
            GeneratedSequence.clear();
        }

        for(int i = 0; i<sequenceSize; i++){
            for(int j = 0; j<SequenceList[i].GetSequence().size(); j++){
                cout<<SequenceList[i].GetSequence()[j].GetTokenString()<<" ";
            }
            cout<<"Poin = "<<SequenceList[i].GetSequencePoints()<<"\n";
        }
        auto start = HRC::now();
        SolveOptimal(gameMatrix,"Horizontal","",bufferSize,0,TokenListFinalAnswer,CoordinateListFinalAnswer,0,0,0,SequenceList);
        auto end = HRC::now();
        OutputAnswer(chrono::duration_cast<MSEC>(end-start));
        OutputFilePrompt(gameMatrix,method,chrono::duration_cast<MSEC>(end-start));
    } else {
        JumpStart:
            ifstream InputFile;
            cout<<"Masukkan nama file (WAJIB DIAKHIRI DENGAN '.txt' dan WAJIB ADA DI FOLDER test): ";
            string FileName;
            string InputPath = "../test/";
            cin>>FileName;
            InputFile.open(InputPath + FileName);

            while(!InputFile.is_open()){
                cout<<"File tidak ditemukan! Silahkan input ulang.\n";
                cout<<"Masukkan nama file (WAJIB DIAKHIRI DENGAN '.txt' dan ADA di dalam repository): ";
                cin>>FileName;
                InputFile.open(FileName);
            }
        // if(!InputFile.is_open()){
        //     cout<<"File tidak ditemukan! Program akan berhenti. \n";
        //     return 0;
        // }
            int linecount = 0;
            string RowFile;
            vector<string> RowFileStripped;
            while(!InputFile.eof()){
                linecount++;
                getline(InputFile,RowFile);

                RowFileStripped = StringToStringList(RowFile);

                if(linecount<=2){
                    if(linecount == 1){
                        bufferSize = stoi(RowFileStripped[0]);
                    }else{
                        MatrixCol = stoi(RowFileStripped[0]);
                        MatrixRow =stoi(RowFileStripped[1]);
                    }
                } else if(linecount>2 && linecount<=MatrixRow+2){
                
                    inputStringMatrix.push_back(RowFileStripped);
                    for(int i = 0; i<MatrixCol; i++){
                        validTokens.insert(RowFileStripped[i]);
                    }
                } else if(linecount == MatrixRow+3){
                    sequenceSize = stoi(RowFileStripped[0]);
                } else{
                    if(InputFile.eof()){
                        break;
                    }
                    for(int i = 0; i<RowFileStripped.size(); i++){
                        validTokens.insert(RowFileStripped[i]);
                    }
                    vector<Token> TokenSeqTemp;
                    TokenSeqTemp = StringListToTokenList(RowFileStripped,validTokens);

                    linecount++;
                    getline(InputFile,RowFile);

                    RowFileStripped = StringToStringList(RowFile);
                    int tempPoints = stoi(RowFileStripped[0]);

                    TokenSequence TempSequence = TokenSequence(TokenSeqTemp,tempPoints);
                    SequenceList.push_back(TempSequence);
                }
            }
        if(bufferSize<=0 || MatrixCol<=0 || MatrixRow<=0 || sequenceSize<=0 || MatrixCol != inputStringMatrix[0].size() || MatrixRow != inputStringMatrix.size() || sequenceSize != SequenceList.size()){//handling input file
            cout<<"Isi file tidak valid. Silahkan input ulang. \n";
            goto JumpStart;
            return 0;
        }
        GameMatrix gameMatrix = GameMatrix(MatrixRow,MatrixCol,validTokens);
        gameMatrix.InputGameMatrix(inputStringMatrix,validTokens);

        auto start = HRC::now();
        SolveOptimal(gameMatrix,"Horizontal","",bufferSize,0,TokenListFinalAnswer,CoordinateListFinalAnswer,0,0,0,SequenceList);
        auto end = HRC::now();
        OutputAnswer(chrono::duration_cast<MSEC>(end-start));
        OutputFilePrompt(gameMatrix,method,chrono::duration_cast<MSEC>(end-start));
    }
    return 0;
}