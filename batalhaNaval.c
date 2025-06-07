#include <stdio.h>   // Biblioteca para entrada e saída padrão, como printf(), etc.
#include <string.h>  // Biblioteca que oferece funçoes para manipulação de strings, como strcmp(), etc.
#include <stdbool.h> // Biblioteca que define o tipo booleano(bool), como valores 'true' e 'false'.
#include <stdlib.h>  // Biblioteca que fornece funções para alocação dinâmica de menória, conversões de tipo (atoi) e funções utilitárias.

#define TABULEIRO_TAM 10
#define COLUNA_INDICE 2
#define LINHA_INDICE 12
#define TAM_NAVIO 3
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5
#define LINHA_HABILIDADE 3
#define COLUNA_HABILIDADE 5


// Caracteres de colunas do tabuleiro (A-J)
const char listaCaracteres[TABULEIRO_TAM] = {'A','B','C','D','E','F','G','H','I','J'};
// Valores de linha do tabuleiro (1-10)
const char *listaNumeros[TABULEIRO_TAM] = {"1","2","3","4","5","6","7","8","9","10"};

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
        printf("%2d ", i + 1); // Para os números com menos de 2 digito, é colocado 1 espaço a esquerda para garantir o alinhamento no printf.
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
    *linha = atoi(&coordenada[1]) - 1; // Essa expressão converte o número de string para inteiro e subtrai por 1.
}

// Armazena os índices das posições dos navios
void indiceNavios(const char *navio_horizontal[], const char *navio_vertical[], const char *primeiro_navio_diagonal[], const char *segundo_navio_diagonal[], int indices[LINHA_INDICE][COLUNA_INDICE]) { 

    int contador = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        converter_coordenadas(navio_horizontal[i], &indices[contador][1], &indices[contador][0]);
        contador++;
        
        converter_coordenadas(navio_vertical[i], &indices[contador][1], &indices[contador][0]);
        contador++;
        
        converter_coordenadas(primeiro_navio_diagonal[i], &indices[contador][1], &indices[contador][0]);
        contador++;
        
        converter_coordenadas(segundo_navio_diagonal[i], &indices[contador][1], &indices[contador][0]);
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
int verificar_sobreposicao(const char *primeira_lista_coordenadas[], const char *segunda_lista_coordenadas[]) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        for (int j = 0; j < TAM_NAVIO; j++) {
            if (strcmp(primeira_lista_coordenadas[i], segunda_lista_coordenadas[j]) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

// Verifica se as coordenadas estão dentro dos limites do tabuleiro
int validar_limites(const char *primeira_lista_coordenadas[], const char *segunda_lista_coordenadas[]) {
    int validacao = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {        
        for (int j = 0; j < TABULEIRO_TAM; j++) {
            if (listaCaracteres[j] == primeira_lista_coordenadas[i][0]) {
                validacao++;
            }
            if (listaCaracteres[j] == segunda_lista_coordenadas[i][0]) {
                validacao++;
            }
            if (strcmp(&primeira_lista_coordenadas[i][1], listaNumeros[j]) == 0) {
                validacao++;
            }
            if (strcmp(&segunda_lista_coordenadas[i][1], listaNumeros[j]) == 0) {
                validacao++;
            }
        }
    }
    return validacao == 12;
}

// Verificar se todas os navios estão posicionados corretamente
bool verificar_todas_sobreposicoes(const char **lista[], int num_listas) {
    for (int i = 0; i < num_listas; i++) {
        for (int j = i + 1; j < num_listas; j++) {
            if (verificar_sobreposicao(lista[i], lista[j])) {
                return true;
            }
        }
        
    }
    return false;
}

// Valida todas as regras antes de posicionar os navios
int validar_entrada(const char *navio_horizontal[], const char *navio_vertical[], const char *primeiro_navio_diagonal[], const char *segundo_navio_diagonal[], int indices[LINHA_INDICE][COLUNA_INDICE]) {

    // Inicialização de array de ponteiros    
    const char **listas_navios[] = {navio_horizontal, navio_vertical, primeiro_navio_diagonal, segundo_navio_diagonal};

    if (!verificar_todas_sobreposicoes(listas_navios, 4) &&
        !verificar_repeticao(navio_horizontal) &&
        !verificar_repeticao(navio_vertical) &&
        !verificar_repeticao(primeiro_navio_diagonal) &&
        !verificar_repeticao(segundo_navio_diagonal) &&
        validar_limites(navio_horizontal, navio_vertical) &&
        validar_limites(primeiro_navio_diagonal, segundo_navio_diagonal)) {

        indiceNavios(navio_horizontal, navio_vertical, primeiro_navio_diagonal, segundo_navio_diagonal, indices);
        return 1;
    } else {
        printf("\nErro: Posições inválidas!\nCertifique-se de que os navios estão dentro do tabuleiro e não se sobrepõem.\n\n");
        return 0;
    }
}

// Posiciona um cone no tabuleiro.
void posicionar_habilidade_cone(const char *posicao, int tabuleiro[TABULEIRO_TAM][TABULEIRO_TAM]) {

    int coordenada_linha = atoi(&posicao[1]) - 2;
    int coordenada_coluna = (posicao[0] - 'A') - 1;
    int contador = 0;

    for (int i = 0; i < LINHA_HABILIDADE; i++) {
        for (int j = 0; j < COLUNA_HABILIDADE; j++) {
            if ((i == 0 && j == 2) || (i == 1 && j > 0 && j < 4) || (i == 2)) {
                if ((coordenada_linha + i >= 0 && coordenada_linha + i <= 9) && (coordenada_coluna + j >= 0 && coordenada_coluna + j <= 9)) {
                    tabuleiro[coordenada_linha + i][coordenada_coluna + j] = 1;
                } else {
                    contador++;
                }
            }
        }
    }

    if (contador > 0) {
        printf("\nHabilidade CONE está fora do tabuleiro, defina outro ponto inicial para a habilidade!\n");
    }
    
    
}

// Posiciona um cruz no tabuleiro.
void posicionar_habilidade_cruz(const char *posicao, int tabuleiro[TABULEIRO_TAM][TABULEIRO_TAM]) {

    int coordenada_linha = atoi(&posicao[1]) - 2;
    int coordenada_coluna = (posicao[0] - 'A') - 1;
    int contador = 0;

    for (int i = 0; i < LINHA_HABILIDADE; i++) {
        for (int j = 0; j < COLUNA_HABILIDADE; j++) {
            if ((i == 0 && j == 2) || (i == 1) || (i == 2 && j == 2)) {
                if ((coordenada_linha + i >= 0 && coordenada_linha + i <= 9) && (coordenada_coluna + j >= 0 && coordenada_coluna + j <= 9)) {
                    tabuleiro[coordenada_linha + i][coordenada_coluna + j] = 1;
                } else {
                    contador++;
                }
            }
        }
    }

    if (contador > 0) {
        printf("\nHabilidade CRUZ está fora do tabuleiro, defina outro ponto inicial para a habilidade!\n");
    }
}

// Posiciona um octaedro no tabuleiro.
void posicionar_habilidade_octaedro(const char *posicao, int tabuleiro[TABULEIRO_TAM][TABULEIRO_TAM]) {

    int coordenada_linha = atoi(&posicao[1]) - 2;
    int coordenada_coluna = (posicao[0] - 'A') - 1;
    int contador = 0;

    for (int i = 0; i < LINHA_HABILIDADE; i++) {
        for (int j = 0; j < COLUNA_HABILIDADE; j++) {
            if ((i == 0 && j == 2) || (i == 1 && j > 0 && j < 4) || (i == 2 && j == 2)) {
                if ((coordenada_linha + i >= 0 && coordenada_linha + i <= 9) && (coordenada_coluna + j >= 0 && coordenada_coluna + j <= 9)) {
                    tabuleiro[coordenada_linha + i][coordenada_coluna + j] = 1;
                } else {
                    contador++;
                }
            }
        }
    }

    if (contador > 0) {
        printf("\nHabilidade OCTAEDRO está fora do tabuleiro, defina outro ponto inicial para a habilidade!\n");
    }
}

// Função principal responsavel por gerencias o programa.
int main() {
    
    const char *navio_vertical[TAM_NAVIO] = {"E2","E3","E4"};
    const char *navio_horizontal[TAM_NAVIO] = {"B7","C7","D7"};
    const char *primeiro_navio_diagonal[TAM_NAVIO] = {"F5","G6","H7"};
    const char *segundo_navio_diagonal[TAM_NAVIO] = {"I2","H3","G4"};
    int tabuleiro[TABULEIRO_TAM][TABULEIRO_TAM];
    int indices[LINHA_INDICE][COLUNA_INDICE];
    const char posicao_cone[] = "B9";
    const char posicao_cruz[] = "B3";
    const char posicao_octaedro[] = "F8";

    criar_tabuleiro(tabuleiro);

    posicionar_habilidade_cone(posicao_cone, tabuleiro);

    posicionar_habilidade_cruz(posicao_cruz, tabuleiro);

    posicionar_habilidade_octaedro(posicao_octaedro, tabuleiro);

    if (validar_entrada(navio_vertical, navio_horizontal, primeiro_navio_diagonal, segundo_navio_diagonal, indices)) {
        posicionar_navios(tabuleiro, indices);
        exibir_tabuleiro(tabuleiro);
    }

    return 0;
}
