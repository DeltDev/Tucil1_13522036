#include <bits/stdc++.h>
#include "token.h"
using namespace std;
//GameMatrix adalah matriks yang berisi token dan matriks yang berisi boolean untuk menentukan apakah cell sudah dikunjungi
class GameMatrix{
    private:
        int ColSize,RowSize;
        vector<vector<Token> > TokenMatrix; //matriks yang hanya berisi token
        vector<vector<bool> > VisitedMatrix; //matriks yang menunjukkan apakah cell sudah dikunjungi atau belum
        bool isGameMatrixValid;
        void InitiateTokenMatrix(); //membuat matriks token baru
        void InitiateVisitedMatrix(); //membuat matriks visited baru
        void CheckGameMatrixValidity(); //mengecek apakah GameMatrix valid
    public:
        GameMatrix(int Row, int Col); //konstruktur GameMatrix
        Token GetTokenCell(int Row, int Col); //mendapatkan token pada baris dan kolom yang dicari
        bool GetVisitedCell(int Row, int Col); //mendapatkan nilai apakah cell sudah dikunjungi atau belum
        void InputGameMatrix(int Row, int Col); //menginput gameMatrix
        void SetVisitedCell(int Row, int Col, bool cellValue); //mengubah nilai cell visited matrix (untuk backtracking)
        int GetRow(); //mendapatkan banyak baris matriks
        int GetCol(); //mendapatkan banyak kolom matriks
        void PrintTokenMatrix(); //mencetak matriks token
        void PrintVisitedMatrix(); //mencetak matriks visited
        bool GetGameMatrixValidity(); //mendapatkan nilai isGameMatrixValid
};