# Alinhamento de sequências em espaço linear
Link YT: https://youtu.be/GppsMSFFP8Y

Desenvolvimento do algoritmo de Hirschberg para resolver problema de alinhamento de sequências.

## Contextualização
- O alinhamento de sequências é uma ferramenta fundalmental na Bioinformática para comparar DNA e proteínas. A abordagem clássica utiliza matrizes de tamanho m x n, o que torna inviável ara sequências muito longas, devido ao consumo de memória.

- A solução para esse problema baseia-se no algoritmo de Hirschberg, uma tecnica que combina Programação Dinâmica com Divisão e Conquista, permitindo encontrar o alinhamento ótimo utilizando espaço linear (m+n) mantendo a complexidade de tempo em O(mn)

## Objetivos
- Este trabalho busca implementar e comparar duas estratégias para o problema de alinhamento global de sequências:
1. Algoritmo clássico (Needleman-Wunsch): matriz completa para reconstruir o caminho  (backtracking)
2. Algoritmo em Espaço Linear (Hirschberg): Utiliza a técnica janela deslizante (mantendo apenas duas colunas na memória) e recursão para reconstruir o alinhamento.

# The Huxley
- https://thehuxley.com/problem/4842

# Ferramentas auxiliares
- https://bioboot.github.io/bimm143_W20/class-material/nw/

# Referências para o projeto
- https://dl.acm.org/doi/pdf/10.1145/360825.360861 (Artigo original do Hirschberg)
