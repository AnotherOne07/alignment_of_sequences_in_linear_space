#include <iostream>
#include <string>
#include <vector>
#include "../utils/alignment.h"
#include "needleman.h"
#include <algorithm>

using namespace std;

AlignmentResult backtrace(string X, string Y, int rows, int cols, vector<vector<int>> &m, int gap, int mismatch, int match){
    string newX = "", newY = "";
    int i, j;
    i = rows;
    j = cols;
    while(i > 0 || j > 0){
	if(
	i>0 && j > 0 && 
	m[i][j] == m[i-1][j-1] + // a condional verifica se o score atual é "consequência" do custo da anterior
	((X[i-1] == Y[j-1])? match : mismatch)){ 
	
		newX += X[i-1];
		newY += Y[j-1];
		i--;
		j--;
	}
	else if (
		// PRIORIDADE 2: TOP
		i > 0 &&
		m[i][j] == m[i-1][j] + gap
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
            	//int result = compare_directions(m[i-1][j], m[i][j-1], m[i-1][j-1], gap, mismatch, match,is_match);
            	m[i][j] = min({diagonal,top,left});		
            }
    }
    
    return backtrace(X,Y,rows,cols,m,gap,mismatch,match);
}
