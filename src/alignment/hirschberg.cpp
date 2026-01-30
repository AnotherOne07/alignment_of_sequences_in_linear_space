#include <iostream>
#include <vector>
#include <string>
#include "utils/alignment.cpp"

// namespace serve como uma folder para as variáveis
// declarar um namespace global ajuda a legibilidade do código
// porém em projetos maiores deve ser evitado para não causar erros de escopo
using namespace std;

int main (){
    string X = "ACCGA";
    string Y = "ACCCA";
    int gap = 2, mismatch = 1, match = 0;
    int xAxis, yAxis;
    xAxis = X.length() + 1;
    yAxis = Y.length() + 1;
    vector<vector<int>> m(xAxis, vector<int>(yAxis, 0));

    // Preenchendo coluna base
    for(int i = 0; i < xAxis; i++){
        m[i][0] = i * gap;
    }
    
    for (int j = 1; j < yAxis; j++){
        m[0][1] = j * gap;
        space_efficient_alignment();
    }


    return 0;
}