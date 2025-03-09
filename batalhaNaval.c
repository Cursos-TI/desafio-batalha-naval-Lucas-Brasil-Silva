#include <stdio.h>
#include <string.h>

#define TAM_CARACTERES 10
#define TAM_NUMEROS 10
#define LINHA_TABULEIRO 10
#define COLUNA_TABULEIRO 10
#define TAM_NAVIO 3
#define COLUNA_INDICE 2
#define LINHA_INDICE 6
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

void margemHorizontal(char listaCaracteres[TAM_CARACTERES]) {
    
    printf("\n  ");
    for (int i = 0; i < TAM_CARACTERES; i++)
    {
        printf(" %c", listaCaracteres[i]);
    }
    printf("\n");
}

void posicionarNavios(int tabuleiro[LINHA_TABULEIRO][COLUNA_TABULEIRO],int indices[LINHA_INDICE][COLUNA_INDICE]) {
    for (int i = 0; i < LINHA_INDICE; i++)
    {
        int linha = indices[i][1];
        int coluna = indices[i][0];

        tabuleiro[linha][coluna] = NAVIO;
    }
    
}

// Função responsavel por identificar o indice das posições do navio no tabuleiro 
void indiceNavios(char *navioVertical[], char *navioHorizontal[], char listaCaracteres[TAM_CARACTERES], int indices[LINHA_INDICE][COLUNA_INDICE]) { 

    int contador = 0;

    for (int i = 0; i < TAM_NAVIO; i++)
    {
        // Declaração de variáveis que estão recebenddo as posições do navio.
        char letraVer = navioVertical[i][0];
        char letraHor = navioHorizontal[i][0];

        // Loop que identificar o indice das posições
        for (int j = 0; j < TAM_CARACTERES; j++) {
            // Verificar qual caracter foi inserido, quando encontar, adiciona na lista indice o indice do caracter e do número.
            if (listaCaracteres[j] == letraVer) {
                indices[contador][0] = j;
                indices[contador][1] = strcmp(&navioVertical[i][1], "10") == 0 ? 9 : (navioVertical[i][1] - '0') - 1; 
                contador++;
            }
            if (listaCaracteres[j] == letraHor) {
                indices[contador][0] = j;
                indices[contador][1] = strcmp(&navioHorizontal[i][1], "10") == 0 ? 9 : (navioHorizontal[i][1] - '0') - 1;
                contador++;
            }
            
        }
        
    }
    
}

int verificarRepeticao(char *listaPosicoes[]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        for (int j = i + 1; j < TAM_NAVIO; j++) {
            if (strcmp(listaPosicoes[i], listaPosicoes[j]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int listasSaoDiferentes(char *navioVertical[], char *navioHorizontal[]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        for (int j = 0; j < TAM_NAVIO; j++) {
            if (strcmp(navioHorizontal[i], navioVertical[j]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int posicaolimite(char *navioVertical[], char *navioHorizontal[], char listaCaracteres[TAM_CARACTERES], char *listaNumeros[TAM_NUMEROS]) {
    
    int validacao = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        // Declaração de variáveis que estão recebenddo as posições do navio.
        char letraVer = navioVertical[i][0]; // sempre será um caracter
        char letraHor = navioHorizontal[i][0];
        
        for (int j = 0; j < TAM_CARACTERES; j++) {
            if (listaCaracteres[j] == letraHor) {
                validacao++;
            }
            if (listaCaracteres[j] == letraVer) {
                validacao++;
            }
            if (strcmp(&navioHorizontal[i][1], listaNumeros[j]) == 0) {
                validacao++;
            }
            if (strcmp(&navioVertical[i][1], listaNumeros[j]) == 0) {
                validacao++;
            }
        }
    }
    
    if (validacao == 12) {
        return 1;
    } else {
        return 0;
    }
}

int validarEntrada(char *navioVertical[], char *navioHorizontal[], char listaCaracteres[TAM_CARACTERES], char *listaNumeros[TAM_NUMEROS], int indices[LINHA_INDICE][COLUNA_INDICE]) {
    
    if (!listasSaoDiferentes(navioVertical, navioHorizontal) && !verificarRepeticao(navioHorizontal) && !verificarRepeticao(navioVertical) && posicaolimite(navioVertical, navioHorizontal, listaCaracteres, listaNumeros)) {
    //    printf("\n Executando funcao!!\n");
        indiceNavios( navioVertical,navioHorizontal, listaCaracteres, indices);
        return 1;
    } else {
        printf("\nDigite posições validas!\nElas precisão estejam entre a linha 1 à 10, coluna A à J e náo podem se sobrepor.\n");
        return 0;
    }
}


int main() {
    
    int tabuleiro[LINHA_TABULEIRO][COLUNA_TABULEIRO];
    char listaCaracteres[TAM_CARACTERES] = {'A','B','C','D','E','F','G','H','I','J'};
    char *listaNumeros[TAM_NUMEROS] = {"1","2","3","4","5","6","7","8","9","10"};
    char *navioVertical[TAM_NAVIO] = {"E2","E3","E4"};
    char *navioHorizontal[TAM_NAVIO] = {"B7","C7","D7"};
    int indices[LINHA_INDICE][COLUNA_INDICE];

    criarTabuleiro(tabuleiro);
    
    margemHorizontal(listaCaracteres);
    
    exibirTabuleiro(tabuleiro);

    if (validarEntrada(navioVertical, navioHorizontal, listaCaracteres, listaNumeros, indices)) {
        posicionarNavios(tabuleiro, indices);
        margemHorizontal(listaCaracteres);
        exibirTabuleiro(tabuleiro);

    }

    return 0;
}
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
