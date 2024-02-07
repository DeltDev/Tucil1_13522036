#include <bits/stdc++.h>

using namespace std;
stack<string> FlipStack (stack<string> StringStack); //Fungsi ini akan membalik seluruh isi stack
string StringStackToString(stack <string> StringStack); //Fungsi ini akan mengubah stack yang isinya string menjadi string utuh
vector<vector <string> > InitiateStringMatrix(int Row, int Col); //membuat matrix string baru
vector<vector <bool> > InitiateVisitedMatrix(int Row, int Col); //membuat matrix visited baru