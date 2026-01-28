#include <iostream>
#include <string>

using namespace std;

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

    string X {"TATGA"};
    string Y {"TACGA"};

    int xAxis, yAxis;

    xAxis = X.length() + 1;
    yAxis = Y.length() + 1;

    int m[xAxis][yAxis];

    int gap=2, mismatch=1, match=0;

    cout << X +  ": " << xAxis << "\n";
    cout << Y +  ": " << yAxis << "\n";

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
    for(int i=0;i<xAxis;i++){
        for(int j=0;j<yAxis;j++){
            // m[i][j] = 0;
            
        }
    }

    for(int i=0;i<yAxis;i++){
        for(int j=0;j<xAxis;j++){
            cout << m[j][i] << " ";
        }
        cout << "\n";
    }

    return 0;
}