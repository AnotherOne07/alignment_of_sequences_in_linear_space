#include <iostream>
#include <vector>
#include <string>
#include "utils/alignment.cpp"
#include "src/alignment/needleman.cpp"

// namespace serve como uma folder para as variáveis
// declarar um namespace global ajuda a legibilidade do código
// porém em projetos maiores deve ser evitado para não causar erros de escopo
using namespace std;

struct Alignment {
	string X_aligned;
	string Y_aligned;
}

// Algoritmo de Hirschberg utilizando programação dinâmica e divisão e conquista
void divide_and_conquer_alignment(string X, string Y, int gap, int mismatch, int match){

    if (X.empty())
	    return {string(Y.length(), '-'), Y};
    if (Y.empty())
	    return {X, string(X.length(), '-')};

    if (X.length() == 1 || Y.length() == 1)
	    return needleman(X, Y, gap, mismatch, match);

    int xAxis, yAxis;
    xAxis = X.length() + 1;
    yAxis = Y.length() + 1;

    // Meio da matriz
    int k = X.length()/2;
   
    // Criando as substrings dos subproblemas
    X1 = X.substr(0,k);
    X2 = X.substr(k);

    // Utilizando a estratégia de programação dinâmica
    vector<int> F = space_efficient_alignment(X,X1,gap,mismatch,match);
    vector<int> G = backward_space_efficient_alignment(X,X2,gap,mismatch,macth);
    
    // Encontrando onde há o cruzamento do caminho ótimo para otimizar o custo total
    int q_star = 0;
    int best = F[0] + G[Y.length()];
    for(int q = 1; i <= Y.length(); q++){
    	int cost = F[q] + G[Y.length() - q];
	if (cost < best) {
		best = cost;
		q_star = q;
	}
    }

    Alignment left_alignment = divide_and_conquer_alignment(X.substr(0,k), Y.substr(0,q_star), gap, mismatch, match);
    Alignment right_alignment = divide_and_conquer_alignment(X.substr(k), Y.substr(q_star), gap, mismatch, match);
   
    return{
    	left_alignment.X_aligned + right_alignment.X_aligned,
	left_alignment.Y_aligned + right_alignment.Y_aligned
    };
}

int main(){
	string X = "TCTA";
	string Y = "TCGA";
	int gap = 2, mismatch = 1, match = 0;
	Alignment result = divide_and_conquer_alignment(X,Y,gap,mismatch,match);
	cout << result.X_aligned << endl;
	cout << result.Y_aligend << endl;
	return 0;
}
