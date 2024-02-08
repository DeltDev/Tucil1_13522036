#include <bits/stdc++.h>
#include "sequence.h"

TokenSequence::TokenSequence(vector<Token> InputSequence){
    Sequence = InputSequence;
    ValidSequence = true;

    for(int i = 0; i<InputSequence.size(); i++){
        if(!InputSequence[i].GetTokenValidity()){
            ValidSequence = false;
            break;
        }
    }

    if(ValidSequence){
        SequenceString = ConvertSequenceToString();
    }
}

vector<Token> TokenSequence::GetSequence(){
    return Sequence;
}
bool TokenSequence::GetSequenceValidity(){
    return ValidSequence;
}
string TokenSequence::GetSequenceString(){
    return SequenceString;
}
string TokenSequence::ConvertSequenceToString(){
    string out = "";

    for(int i = 0; i<Sequence.size(); i++){
        out = out + Sequence[i].GetTokenString();
    }

    return out;
}

