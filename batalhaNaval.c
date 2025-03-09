#include <stdio.h>
#include <string.h>

#define TABULEIRO_TAM 10
#define TAM_NAVIO 3
#define COLUNA_INDICE 2
#define LINHA_INDICE 6
#define VALOR_NAVIO 3

// Caracteres de colunas do tabuleiro (A-J)
const char listaCaracteres[TABULEIRO_TAM] = {'A','B','C','D','E','F','G','H','I','J'};
// Valores de linha do tabuleiro (1-10)
char *listaNumeros[TABULEIRO_TAM] = {"1","2","3","4","5","6","7","8","9","10"};

// Inicializa o tabuleiro com água (0).
void criar_tabuleiro(int tabuleiro[TABULEIRO_TAM][TABULEIRO_TAM]) {
    for (int i = 0; i < TABULEIRO_TAM; i++) {
        for (int j = 0; j < TABULEIRO_TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Exibe o tabuleiro formatado
void exibir_tabuleiro(int tabuleiro[TABULEIRO_TAM][TABULEIRO_TAM]) {
    printf("\n  ");
    for (int i = 0; i < TABULEIRO_TAM; i++) {
        printf(" %c", listaCaracteres[i]);
    }
    printf("\n");

    for (int i = 0; i < TABULEIRO_TAM; i++) {
        // printf(i < TABULEIRO_TAM - 1 ? "%d  " : "%d ", i + 1);
        printf("%2d ", i + 1);
        for (int j = 0; j < TABULEIRO_TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Posiciona os navios no tabuleiro
void posicionar_navios(int tabuleiro[TABULEIRO_TAM][TABULEIRO_TAM],int indices[LINHA_INDICE][COLUNA_INDICE]) {
    for (int i = 0; i < LINHA_INDICE; i++) {
        tabuleiro[indices[i][1]][indices[i][0]] = VALOR_NAVIO;
    }
}

// converte coordenadas de texto (ex: "B7") para índices numéricos
void converter_coordenadas(const char *coordenada, int *linha, int *coluna) {
    *coluna = coordenada[0] - 'A';
    *linha = (strcmp(&coordenada[1], "10") == 0) ? 9 : (coordenada[1] - '0') - 1;
}

// Armazena os índices das posições dos navios
void indiceNavios(const char *navioVertical[], const char *navioHorizontal[], int indices[LINHA_INDICE][COLUNA_INDICE]) { 

    int contador = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        converter_coordenadas(navioVertical[i], &indices[contador][1], &indices[contador][0]);
        contador++;
        
        converter_coordenadas(navioHorizontal[i], &indices[contador][1], &indices[contador][0]);
        contador++;
    }
    
}

// Verifica se há repetição em uma lista de coordenadas
int verificar_repeticao(const char *lista_posicoes[]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        for (int j = i + 1; j < TAM_NAVIO; j++) {
            if (strcmp(lista_posicoes[i], lista_posicoes[j]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

// Verifica se há sobreposição entre os navios
int verificar_sobreposicao(const char *navioVertical[], const char *navioHorizontal[]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        for (int j = 0; j < TAM_NAVIO; j++) {
            if (strcmp(navioHorizontal[i], navioVertical[j]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

// Verifica se as coordenadas estão dentro dos limites do tabuleiro
int validar_limnites(const char *navioVertical[], const char *navioHorizontal[]) {
    int validacao = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {        
        for (int j = 0; j < TABULEIRO_TAM; j++) {
            if (listaCaracteres[j] == navioHorizontal[i][0]) {
                validacao++;
            }
            if (listaCaracteres[j] == navioVertical[i][0]) {
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
    return validacao == 12;
}

// Valida todas as regras antes de posicionar os navios
int validar_entrada(const char *navioVertical[], const char *navioHorizontal[], int indices[LINHA_INDICE][COLUNA_INDICE]) {
    
    if (!verificar_sobreposicao(navioVertical, navioHorizontal) &&
        !verificar_repeticao(navioHorizontal) &&
        !verificar_repeticao(navioVertical) &&
        validar_limnites(navioVertical, navioHorizontal)) {

        indiceNavios(navioVertical,navioHorizontal,indices);
        return 1;
    } else {
        printf("\nErro: Posições inválidas!\nCertifique-se de que os navios estão dentro do tabuleiro e não se sobrepõem.\n\n");
        return 0;
    }
}

// Função principal responsavel por gerencias o programa.
int main() {
    
    int tabuleiro[TABULEIRO_TAM][TABULEIRO_TAM];
    const char *navioVertical[TAM_NAVIO] = {"E2","E3","E4"};
    const char *navioHorizontal[TAM_NAVIO] = {"B7","C7","D7"};
    int indices[LINHA_INDICE][COLUNA_INDICE];

    criar_tabuleiro(tabuleiro);
    
    exibir_tabuleiro(tabuleiro);

    if (validar_entrada(navioVertical, navioHorizontal, indices)) {
        posicionar_navios(tabuleiro, indices);
        exibir_tabuleiro(tabuleiro);
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
