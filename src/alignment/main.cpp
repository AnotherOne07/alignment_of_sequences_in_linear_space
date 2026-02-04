#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Necessário para reverse
#include <climits>   // Necessário para INT_MAX

using namespace std;

struct AlignmentResult{
    int score;
    string x_aligned;
    string y_aligned;
};

// Algoritmo de Needleman-Wunsch para reconstrução (Caso Base)
// Respeita a prioridade: Diagonal > Cima > Esquerda
AlignmentResult needleman(string X, string Y, int gap, int mismatch, int match){
    int rows = X.length();
    int cols = Y.length();

    // Matriz de DP
    vector<vector<int>> m(rows + 1, vector<int>(cols + 1));

    // Inicialização das bordas
    for (int i = 0; i <= rows; i++) m[i][0] = i * gap;
    for (int j = 0; j <= cols; j++) m[0][j] = j * gap;
    
    // Preenchimento da matriz
    for(int i = 1; i <= rows; i++){
        for(int j = 1; j <= cols; j++){
            int cost = (X[i-1] == Y[j-1]) ? match : mismatch;
            
            int diagonal = m[i-1][j-1] + cost;
            int top = m[i-1][j] + gap;      // Gap em Y
            int left = m[i][j-1] + gap;     // Gap em X
            
            m[i][j] = min({diagonal, top, left});        
        }
    }
    
    // Backtracking
    string newX = "", newY = "";
    int i = rows;
    int j = cols;
    
    while(i > 0 || j > 0){
        int current = m[i][j];
        
        // Custos para verificação de qual caminho foi tomado
        // Usamos um valor gigante (mas seguro) para evitar acesso inválido em índices negativos
        int cost_diag = (i > 0 && j > 0) ? (m[i-1][j-1] + ((X[i-1] == Y[j-1]) ? match : mismatch)) : 999999999;
        int cost_up   = (i > 0)          ? (m[i-1][j] + gap)   : 999999999;
        // cost_left não precisa ser verificado explicitamente no 'else', mas seria: (j > 0) ? ...

        // PRIORIDADE 1: DIAGONAL
        if (i > 0 && j > 0 && current == cost_diag) {
            newX += X[i-1];
            newY += Y[j-1];
            i--; j--;
        }
        // PRIORIDADE 2: CIMA (Gap em Y)
        else if (i > 0 && current == cost_up) {
            newX += X[i-1];
            newY += "-"; 
            i--;
        }
        // PRIORIDADE 3: ESQUERDA (Gap em X)
        else {
            newX += "-";
            newY += Y[j-1];
            j--;
        }
    }
    
    reverse(newX.begin(), newX.end());
    reverse(newY.begin(), newY.end());

    return {m[rows][cols], newX, newY};
}

// Algoritmo Linear Space (Retorna apenas a última coluna de custos)
vector<int> space_efficient_alignment(string X, string Y, int gap, int mismatch, int match){
    int rows = X.length();
    int cols = Y.length();

    // Vetores colunares (Tamanho = Altura da matriz = rows)
    vector<int> prev(rows + 1);
    vector<int> curr(rows + 1);

    // Inicializa a coluna 0 (apenas gaps em X)
    for(int i = 0; i <= rows; i++){
        prev[i] = i * gap;
    }

    // Itera sobre as colunas de Y
    for(int j = 1; j <= cols; j++){
        // O elemento [0] da coluna atual é sempre gaps em Y
        curr[0] = j * gap;    
        
        for (int i = 1; i <= rows; i++){
            int cost = (X[i-1] == Y[j-1]) ? match : mismatch;
            
            int diagonal = prev[i-1] + cost;
            int top = curr[i-1] + gap; // Cima (na mesma coluna)
            int left = prev[i] + gap;  // Esquerda (coluna anterior)
            
            curr[i] = min({diagonal, top, left});
        }  
        prev = curr;
    }
    return prev; 
}

// Wrapper para rodar o algoritmo linear com strings invertidas
vector<int> backward_space_efficient_alignment(string X, string Y, int gap, int mismatch, int match){
    reverse(X.begin(), X.end());
    reverse(Y.begin(), Y.end());
    return space_efficient_alignment(X, Y, gap, mismatch, match);
}

// Algoritmo de Hirschberg Principal
AlignmentResult divide_and_conquer_alignment(string X, string Y, int gap, int mismatch, int match){
    
    // CORREÇÃO 1: Caso base estrito. 
    // Se uma das strings for vazia, chamamos o needleman para resolver trivialmente.
    // Isso força o Hirschberg a resolver todas as ambiguidades de posicionamento.
    if (Y.length() <= 1) {
        return needleman(X, Y, gap, mismatch, match);
    }

    int rows = X.length();
    // Divide Y ao meio
    int mid = Y.length() / 2;
    
    // Substrings
    string Y_left = Y.substr(0, mid);
    string Y_right = Y.substr(mid);

    // Calculo dos Scores (Forward e Backward)
    vector<int> F = space_efficient_alignment(X, Y_left, gap, mismatch, match);
    vector<int> G = backward_space_efficient_alignment(X, Y_right, gap, mismatch, match);
    
    int q_star = -1;
    long long best = LLONG_MAX; // Usar valor seguro para infinito

    // Encontra o ponto de corte ótimo em X
    for(int i = 0; i <= rows; i++){
        long long cost = (long long)F[i] + G[rows - i];
        
        // REGRA DO HUXLEY: "Escolha o menor índice i"
        // Usamos '<' estrito. Se houver empate, mantemos o índice 'i' anterior (que é menor).
        if (cost < best) {
            best = cost;
            q_star = i;
        }
    }

    // Conquista (Recursão)
    AlignmentResult left_alignment = divide_and_conquer_alignment(X.substr(0, q_star), Y_left, gap, mismatch, match);
    AlignmentResult right_alignment = divide_and_conquer_alignment(X.substr(q_star), Y_right, gap, mismatch, match);
    
    return{
        left_alignment.score + right_alignment.score,
        left_alignment.x_aligned + right_alignment.x_aligned,
        left_alignment.y_aligned + right_alignment.y_aligned
    };
}

int main(){
    // Otimização de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string X, Y;
    if (cin >> X >> Y) {
        int gap = 2, mismatch = 1, match = 0;
        AlignmentResult result = divide_and_conquer_alignment(X, Y, gap, mismatch, match);
        
        cout << result.score << endl;
        cout << result.x_aligned << endl;
        cout << result.y_aligned << endl;
    }
    return 0;
}
