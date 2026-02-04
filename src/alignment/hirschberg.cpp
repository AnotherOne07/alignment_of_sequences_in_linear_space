#include <iostream>
#include <vector>
#include <string>
#include "needleman.h"
#include "../utils/alignment.h"

// namespace serve como uma folder para as variáveis
// declarar um namespace global ajuda a legibilidade do código
// porém em projetos maiores deve ser evitado para não causar erros de escopo
using namespace std;

/*
struct Alignment {
        int score;
        string X_aligned;
        string Y_aligned;
};
*/

/*
Alignment convert_typo(Alignment_needleman subs){
	return {subs.score, subs.X, subs.Y};
}
*/

// Algoritmo de Hirschberg utilizando programação dinâmica e divisão e conquista
AlignmentResult divide_and_conquer_alignment(string X, string Y, int gap, int mismatch, int match){
    // Também produz um alinhamento igualmente eficiente (mesmo score do alinhamento de score mínimo), 
    // porém o juiz do the huxley não aceita a solução
    if (X.length() <= 2 || Y.length() <= 2)
	    return needleman(X, Y, gap, mismatch, match);

    int rows = X.length();
    int cols = Y.length();

    // Meio da matriz
    // int k = X.length()/2;
    int mid = Y.length()/2;
   
    // Criando as substrings dos subproblemas
    string Y_left = Y.substr(0,mid);
    string Y_right = Y.substr(mid);

    // Utilizando a estratégia de programação dinâmica
    // Custo da metade esquerda 
    vector<int> F = space_efficient_alignment(X,Y_left,gap,mismatch,match);
    // Custo da metade direita
    vector<int> G = backward_space_efficient_alignment(X,Y_right,gap,mismatch,match);
    
    // Encontrando onde há o cruzamento do caminho ótimo para otimizar o custo total
    int q_star = -1;
    int best = 1000000;

//    int best = F[0] + G[X.length()];
    for(int i = 0; i <= rows; i++){
    	int cost = F[i] + G[rows - i];
	if (cost < best) {
		best = cost;
		q_star = i;
	}
    }

    // Realiza a conquista em cada lado das subcadeias geradas
    AlignmentResult left_alignment = divide_and_conquer_alignment(X.substr(0,q_star), Y_left, gap, mismatch, match);
    AlignmentResult right_alignment = divide_and_conquer_alignment(X.substr(q_star), Y_right, gap, mismatch, match);
   
    return{
    	left_alignment.score + right_alignment.score,
	left_alignment.x_aligned + right_alignment.x_aligned,
	left_alignment.y_aligned + right_alignment.y_aligned
    };
}

int main(){
	string X, Y;
	cin >> X >> Y;
	int gap = 2, mismatch = 1, match = 0;
	AlignmentResult result = divide_and_conquer_alignment(X,Y,gap,mismatch,match);
	cout << result.score << endl;
	cout << result.x_aligned << endl;
	cout << result.y_aligned << endl;
	return 0;
}
