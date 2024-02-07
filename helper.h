#include <bits/stdc++.h>

using namespace std;
template <typename TemplateDataType>//ini berfungsi untuk mengubah data type menjadi parameter
stack<TemplateDataType> FlipStack (stack<TemplateDataType> StringStack); //Fungsi ini akan membalik seluruh isi stack
string StringStackToString(stack <string> StringStack); //Fungsi ini akan mengubah stack yang isinya string menjadi string utuh
vector<vector <TemplateDataType> > InitiateNewMatrix(int Row, int Col); //membuat matrix string baru
void PrintMatrix(int Row, int Col, vector<vector<TemplateDataType> > Matrix); //mencetak isi matriks
vector<vector<TemplateDataType> > EmptyMatrix(); //untuk membuat matriks kosong
