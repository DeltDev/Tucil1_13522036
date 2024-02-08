#include <bits/stdc++.h>
#include "token.h"
using namespace std;
//TokenSequence adalah senarai/list yang terdiri atas token yang berurutan
class TokenSequence{
    private:
        vector<Token> Sequence; //Sequence dalam bentuk list
        bool ValidSequence; //menentukan apakah sequence valid
        //sequence yang valid adalah sequence yang tidak mengandung token yang tidak valid sama sekali
        string SequenceString; //sequence dalam bentuk string
        //alasan ada string ini adalah untuk mengurangi kompleksitas waktu dibandingkan dengan membandingkan array
        string ConvertSequenceToString();//mengubah sequence menjadi string tanpa spasi
    public:
        TokenSequence(vector<Token> InputSequence); //konstruktur TokenSequence
        vector<Token> GetSequence(); //mendapatkan atribut Sequence
        bool GetSequenceValidity(); //mendapatkan atribut ValidSequence
        string GetSequenceString(); //mendapatkan atribut SequenceString
};