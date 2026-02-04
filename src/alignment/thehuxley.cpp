#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

struct AlignmentResult{
	int score;
	string x_aligned;
	string y_aligned;
};

AlignmentResult backtrace(string X, string Y, int rows, int cols, vector<vector<int>> &m, int gap, int mismatch, int match){
    string newX = "", newY = "";
    int i, j;
    i = rows;
    j = cols;
    
    while(i > 0 || j > 0){
        int current = m[i][j];
        int cost_diag = (i > 0 && j > 0) ? (m[i-1][j-1] + ((X[i-1] == Y[j-1]) ? match : mismatch)) : 999999999;
        int cost_up   = (i > 0)          ? (m[i-1][j] + gap)   : 999999999;
        int cost_left = (j > 0)          ? (m[i][j-1] + gap)   : 999999999;
	if(
	i>0 && j > 0 && current == cost_diag 
	){ 
		newX += X[i-1];
		newY += Y[j-1];
		i--;
		j--;
	}
	else if (
		// PRIORIDADE 2: TOP
		i > 0 && current == cost_up
		){
            newX += X[i-1];
            newY +=  "-"; 
            i--;
        }
        else {
		// PRIORIDADE 3: LEFT
            newX += "-";
            newY += Y[j-1];
            j--;
        }
    }
    
    reverse(newX.begin(), newX.end());
    reverse(newY.begin(), newY.end());

    return {m[rows][cols], newX, newY};
}
/*
    Gaps: onde inserimos ou removemos caracteres
    Incompatibilidades (mismatches): onde os caracteres são diferentes


    O algoritmo de Needleman-Wunsch (1970)
    - Padrão ouro para alinhamento de sequências
    
    sejam 2 strings X e Y:
    Um matching M e um conjunto de pares ordenados (i,j) tal que cada
    índice de X ou Y aparece no máximo uma vez.
    */

AlignmentResult needleman(string X, string Y, int gap, int mismatch, int match){
    // O tamanho da matriz será definido pelo tamanho das cadeias
    int rows = X.length();
    int cols = Y.length();

    // int m[rows][cols];
    // em termos de alocação de memória, seria algo como:
    // um container de containers de inteiros
    // em relação aos parametros, o primeiro define o tamanho do container externo
    // enquanto que o segundo cria um "template" para garantir que haverá o número
    // correto de colunas
    vector<vector<int>> m (rows+1, vector<int>(cols+1)); // precisa ter um "espaço de sobra" para os gaps

    //int gap=2, mismatch=1, match=0;

    // Preenchendo a linha e coluna 0, que representam os gaps
    for (int i = 0; i <= rows; i++){
        m[i][0] = i * gap; 
    }
    for (int i = 0;i <= cols;i++){
        m[0][i] = i * gap;
    }
    
    
    /* 
    A sequencia original deve ser "fixada" no eixo X
    Preenchimento da matriz de alinhamento, considerando a ordem de prioridade top -> left
    */
    int diagonal,top,left,cost;
    for(int i=1;i<=rows;i++){
        for(int j=1;j<=cols;j++){
            	cost = X[i-1] == Y[j-1] ? match : mismatch; // custo da operação (match ou mismatch)
		diagonal = m[i -1][j-1] + cost;
		top = m[i-1][j] + gap; // alinhar X[i] com -
		left = m[i][j-1] + gap; // alinhar - com Y[j]
            	m[i][j] = min({diagonal,top,left});		
            }
    }
    
    return backtrace(X,Y,rows,cols,m,gap,mismatch,match);
}

// Retorna a última coluna da matriz de alinhamento de X com Y
// Retornamos um vetor de tamanho X.length() + 1
vector<int> space_efficient_alignment(string X, string Y, int gap, int mismatch, int match){

	int rows = X.length();
	int cols = Y.length();

	int top, left, diagonal;
	bool is_match;

	// O ponto chave do algoritmo de hirschberg é que não é necessário carregar a matriz completa
	// portanto ao invés de usar uma matriz[m][n] utilizamos somente o espaço de memória suficiente
	// para duas colunas por vez, estas que são suficientes para calcular o score da célula atual
	// Portanto, cada vetor deve ter o tamanho da altura da matriz, no caso, X.length()+1
	vector<int> prev(rows+1), curr(rows+1);

	// Preenchendo coluna base
	for(int j = 0; j <= rows; j++){
        	prev[j] = j * gap;
    	}


	// IMPORTANTE: nesse caso, inicia o loop com índice 1 pois a partir desse ponto a segunda coluna
	// estará sendo preenchida
	// DIAGONAL TOP
	// LEFT     TARGET
	for(int j = 1;j <= cols; j++){
		curr[0] = j * gap;	
		for (int i = 1; i <= rows; i++){
			is_match =  X[i-1] == Y[j-1];
			top = curr[i-1] + gap; // cima é o item anterior do array atual
			left = prev[i] + gap; // esquerda é o item atual do array anterior
			diagonal = prev[i-1] + (is_match ? match : mismatch);
			curr[i] = min({diagonal, top, left});
			/*
			curr[i] = compare_directions(
					top, 
					left, 
					diagonal, 
					gap, mismatch, match, 
					is_match);
			*/
		}  
		prev = curr;
	}
	return prev; // F
}

vector<int> backward_space_efficient_alignment(string X, string Y, int gap, int mismatch, int match){
    reverse(X.begin(), X.end());
    reverse(Y.begin(), Y.end());

    return space_efficient_alignment(X, Y, gap, mismatch, match);
}

AlignmentResult divide_and_conquer_alignment(string X, string Y, int gap, int mismatch, int match){
    if (Y.length() <= 1)
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
