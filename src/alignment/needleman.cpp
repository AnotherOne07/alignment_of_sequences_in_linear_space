#include <iostream>
#include <string>
#include <vector>

using namespace std;

int compare_directions(int top, int left, int diagonal, int gap, int mismatch, int match, bool is_match){
	int result;
	int top_acc, left_acc, diagonal_acc;

	top_acc = top + gap;
	left_acc = left + gap;
	if (is_match)
		diagonal_acc = diagonal + match;
	else
		diagonal_acc = diagonal + mismatch;

	/* 
	 * cout << " TOP = " << top_acc << "| LEFT = " << left_acc << "| DIAGONAL = " << diagonal_acc;
	 */

	if (top_acc < left_acc && top_acc < diagonal_acc)
		result = top_acc;
	else if (left_acc < top_acc && left_acc < diagonal_acc)
		result = left_acc;
	else
		result = diagonal_acc;
		
	return result;
}

void alignment(string X, string Y, int xAxis, int yAxis, vector<vector<int>> &m){
    string newX = "", newY = "";
    int top, left;
    int i, j;
    i = xAxis;
    j = yAxis;
    while(true){
        if (i == 0 || j == 0)
            break;

        top = m[i-1][j];
        left = m[i][j-1];

        if (X[i-1] == Y[j-1]){
            newX = X[i-1] + newX;
            newY = Y[j-1] + newY;
            i = i - 1;
            j = j - 1;
        }
        else if (top < left){
            newX = X[i-1] + newX;
            newY = "-" + newY; 
            i = i - 1;
        }
        else {
            newX = "-" + newX;
            newY = Y[j-1] + newY;
            j = j - 1;
        }
    }
    cout << newX << "\n";
    cout << newY << "\n";
    return;
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

int main(){

    string X {"TACGA"};
    string Y {"TATGA"};

    int xAxis, yAxis;

    xAxis = X.length() + 1;
    yAxis = Y.length() + 1;

    // int m[xAxis][yAxis];
    vector<vector<int>> m (xAxis, vector<int>(yAxis,0));

    int gap=2, mismatch=1, match=0;

    // cout << X +  ": " << xAxis << "\n";
    // cout << Y +  ": " << yAxis << "\n";

    // Preenchendo a linha e coluna 0, que representam os gaps
    m[0][0] = 0;
    for (int i = 1; i < xAxis; i++)
    {
        m[i][0] = m[i-1][0] + gap; 
    }
    
    for (int i = 1;i < yAxis;i++){
        m[0][i] = m[0][i-1] + gap;
    }
    
    
    /* 
    A sequencia original deve ser "fixada" no eixo X
    A sequencia 
    */
    for(int i=1;i<xAxis;i++){
        for(int j=1;j<yAxis;j++){
            // m[i][j] = 0;
            bool is_match; 
            is_match = X[i] == Y[j];
            // cout << "\nIndíce: [" << i << "]["<< j<< "]: " ;
            int result = compare_directions(m[i-1][j], m[i][j-1], m[i-1][j-1], gap, mismatch, match,is_match);
            m[i][j] = result;		
            }
    }

    for(int i=0;i<yAxis;i++){
        for(int j=0;j<xAxis;j++){
            cout << m[j][i] << " ";
        }
        cout << "\n";
    }

    alignment( X, Y, xAxis, yAxis, m);

    return 0;
}
