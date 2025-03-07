#include <stdio.h>

#define TAMANHO_CARACTERES 10
#define LINHA_TABULEIRO 10
#define COLUNA_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define COLUNAS 2
#define MATRIZ_INDICES 6
#define NAVIO 3

// Cria o tabuleiro somente com agua ou seja com 0.
void criarTabuleiro(int tabuleiro[LINHA_TABULEIRO][COLUNA_TABULEIRO]) {
    for (int i = 0; i < LINHA_TABULEIRO; i++)
    {
        for (int j = 0; j < COLUNA_TABULEIRO; j++)
        {
            tabuleiro[i][j] = 0;
        }
        
    }
}

void exibirTabuleiro(int tabuleiro[LINHA_TABULEIRO][COLUNA_TABULEIRO]) {
    for (int i = 0; i < LINHA_TABULEIRO; i++)
    {
        // imprimir na parte veritical os numeros de 1 à 10.
        printf(i < LINHA_TABULEIRO - 1 ? "%d  " : "%d ", i + 1);

        for (int j = 0; j < COLUNA_TABULEIRO; j++)
        {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void margemHorizontal(char listaCaracteres[TAMANHO_CARACTERES]) {
    
    printf("  ");
    for (int i = 0; i < TAMANHO_CARACTERES; i++)
    {
        printf(" %c", listaCaracteres[i]);
    }
    printf("\n");
}

void posicionarNavios(int tabuleiro[LINHA_TABULEIRO][COLUNA_TABULEIRO],int matrizIndices[MATRIZ_INDICES][COLUNAS]) {
    for (int i = 0; i < MATRIZ_INDICES; i++)
    {
        int linha = matrizIndices[i][1];
        int coluna = matrizIndices[i][0];

        tabuleiro[linha][coluna] = NAVIO;
    }
    
}

void indiceNavios(char *navioVertical[], char *navioHorizontal[], char listaCaracteres[TAMANHO_CARACTERES], int matrizIndices[MATRIZ_INDICES][COLUNAS]) { 

    int contador = 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++)
    {
        char letra1 = navioVertical[i][0];
        char numero1 = navioVertical[i][1];
        char letra2 = navioHorizontal[i][0];
        char numero2 = navioHorizontal[i][1];

        for (int j = 0; j < TAMANHO_CARACTERES; j++)
        {
            if (listaCaracteres[j] == letra1)
            {
                matrizIndices[contador][0] = j;
                matrizIndices[contador][1] = (numero1 - '0') - 1;
                contador++;
            }
            if (listaCaracteres[j] == letra2) 
            {
                matrizIndices[contador][0] = j;
                matrizIndices[contador][1] = (numero2 - '0') - 1;
                contador++;
            }
            
        }
        
    }
    
}


int main() {
    
    int tabuleiro[LINHA_TABULEIRO][COLUNA_TABULEIRO];
    char listaCaracteres[TAMANHO_CARACTERES] = {'A','B','C','D','E','F','G','H','I','J'};
    char *navioVertical[TAMANHO_NAVIO] = {"H7","H8","H9"};
    char *navioHorizontal[TAMANHO_NAVIO] = {"C6","D6","E6"};
    int matrizIndices[MATRIZ_INDICES][COLUNAS];

    criarTabuleiro(tabuleiro);
    
    margemHorizontal(listaCaracteres);

    indiceNavios(navioVertical, navioHorizontal, listaCaracteres, matrizIndices);
    
    posicionarNavios(tabuleiro, matrizIndices);
    
    exibirTabuleiro(tabuleiro);
    
    
    return 0;
}

// Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0
