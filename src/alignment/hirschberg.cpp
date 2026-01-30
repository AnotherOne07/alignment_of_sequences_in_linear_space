#include <iostream>
#include <vector>
#include <string>
#include "utils/alignment.cpp"
#include "src/alignment/needleman.cpp"

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
    vector<vector<int>> m(xAxis, vector<int>(2, 0));

    // Meio da matriz
    int k = xAxis/2;

    // Preenchendo coluna base
    for(int i = 0; i < xAxis; i++){
        m[i][0] = i * gap;
    }
   
    m[0][1] = j * gap;
    Y1 = Y.substr(0,k+1);
    Y2 = Y.substr(k+1);
    space_efficient_alignment(X,Y1,gap,mismatch,match,m,j);
    backward_space_efficient_alignment(X,Y2,gap,mismatch,m,j);
	// q representa o índice que minimiza f(q,n/2) + g(q,n/2)
	//q = 
	// adiciona (q,n/2) à lista global P
	// divide_and_conquer_alignment()
	// divide_and_conquer_alignment()
    


    return 0;
}
