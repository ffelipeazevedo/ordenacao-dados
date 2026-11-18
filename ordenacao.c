#include <stdlib.h>
#include <stdio.h>
#include <time.h>             // clock() - medição do tempo (Etapa 2)

// Constantes
#define SEMENTE 42
#define ORDENADO  1                   // cenário: inicialmente ordenado
#define INVERSO   2                   // cenário: inicialmente ordenado inversamente
#define ALEATORIO 3                   // cenário: dados em posições aleatórias


// Variaveis globais
long long comparacoes = 0;    // comparações entre elementos do vetor
long long permutacoes = 0;    // trocas/deslocamentos de elementos do vetor
// (os #define de métodos, cenários e tamanhos entram a partir da Etapa 1)

// Funcoes
void aviso_pendente(char *nome, int etapa);    // avisa que a opção ainda não foi implementada
void limpa_buffer(void);                       // descarta o que sobrou no teclado
void imprimir_vetor(int v[], int n);           // imprimi o vetor
void gerar_ordenado(int v[], int n);           // preenche com 1, 2, ..., n
void gerar_inverso(int v[], int n);            // preenche com n, ..., 2, 1
void gerar_aleatorio(int v[], int n);          // 1..n embaralhados, sem repetição
int esta_ordenado(int v[], int n);             // 1 = crescente, 0 = não está ordenado
void gerar_vetor(int cenario, int v[], int n); // chama o gerador do cenário
void zerar_contadores(void);                   // zera comparacoes e permutacoes
void Bolha(int A[], int n);                    // Bubblesort (material da professora)





// Menu provisório para testar as funções de ordenação
// Cada case chama aviso_pendente() até a etapa correspondente ficar pronta;
// aí trocamos essa linha pela chamada da função real.
int main(){
    int opcao;              // opção escolhida no menu

    for (;;) {
        printf("\n===== TRABALHO 3 - ORDENACAO DE DADOS =====\n");
        printf("1. Testar geracao dos vetores\n");
        printf("2. Testar Bubblesort\n");
        printf("3. Testar Selection Sort\n");
        printf("4. Testar Insertion Sort\n");
        printf("5. Testar Shell Sort\n");
        printf("6. Rodar experimento completo (gera .txt)\n");
        printf("0. Sair\n");
        printf("Opcao: ");

        // validacao para ver se o usuario digitou algo fora do esperado
        if (scanf("%d", &opcao) != 1)
            opcao = -1;
        limpa_buffer();

        switch (opcao) {
            case 1:  
                int teste[10];                

                for (int c = ORDENADO; c <= ALEATORIO; c++){
                    gerar_vetor(c, teste, 10);
                    printf("\nCenario %d:\n", c);
                    imprimir_vetor(teste, 10);
                    printf("Esta ordenado? %s\n", esta_ordenado(teste, 10) ? "sim" : "nao");
                }
                break;

            case 2:     // ordena um vetor de teste com Bubblesort
                        // testa o Bubblesort nos 3 cenários
                teste[10];

                for (int c = ORDENADO; c <= ALEATORIO; c++){
                    gerar_vetor(c, teste, 10);
                    printf("\nCenario %d - antes:  ", c);
                    imprimir_vetor(teste, 10);

                    zerar_contadores();                  // começa a contagem do zero
                    Bolha(teste, 10);

                    printf("Cenario %d - depois: ", c);
                    imprimir_vetor(teste, 10);
                    printf("Comparacoes: %lld | Permutacoes: %lld | Ordenado? %s\n",
                        comparacoes, permutacoes, esta_ordenado(teste, 10) ? "sim" : "nao");
                }
                break;

            case 3:     // ordena um vetor de teste com Selection Sort
                aviso_pendente("Selection Sort", 4);
                break;

            case 4:     // ordena um vetor de teste com Insertion Sort
                aviso_pendente("Insertion Sort", 5);
                break;

            case 5:     // ordena um vetor de teste com Shell Sort
                aviso_pendente("Shell Sort", 6);
                break;

            case 6:     // 4 métodos x 6 tamanhos x 3 cenários -> arquivo .txt
                aviso_pendente("Experimento completo + arquivo .txt", 8);
                break;

            case 0:     // encerra o programa
                printf("Saindo...\n");
                return 0;

            default:
                printf("Opcao invalida!\n");
        }
    }
}

// Bubblesort - código do material da professora
void Bolha(int A[], int n){
    int i, j, troca;

    for (i = n - 1; i >= 1; i--){            // a cada passada, o maior vai para a posição i
        for (j = 0; j < i; j++){             // compara os vizinhos até a posição i
            comparacoes++;                   // conta a comparação A[j] > A[j+1]
            if (A[j] > A[j + 1]){            // fora de ordem: troca
                troca = A[j];
                A[j] = A[j + 1];
                A[j + 1] = troca;
                permutacoes++;               // conta a troca
            }
        }
    }
}


// Zera os contadores antes de cada ordenação
// Sem isso, a contagem de um vetor somaria com a do anterior
void zerar_contadores(void){
    comparacoes = 0;
    permutacoes = 0;
}

// preenche o vetor de acordo com o cenário (ORDENADO 1,  INVERSO 2 ou ALEATORIO 3)
void gerar_vetor(int cenario, int v[], int n){
    switch (cenario) {
        case ORDENADO:
            gerar_ordenado(v, n);
            break;
        case INVERSO:
            gerar_inverso(v, n);
            break;
        case ALEATORIO:
            gerar_aleatorio(v, n);
            break;
    }
}

// Retorna 1 se estiver ordenado e 0 no primeiro par fora de ordem
// Confere se o vetor está em ordem crescente
int esta_ordenado(int v[], int n){
    for (int i = 0; i < n - 1; i++){    // até n-2: compara v[i] com o vizinho v[i+1]
        if (v[i] > v[i + 1])
            return 0;                   // achou par fora de ordem, já pode parar
    }
    return 1;                           // percorreu tudo sem achar erro
}

// preenche o vetor de forma aleatoria
void gerar_aleatorio(int v[], int n){
    int j, aux;

    gerar_ordenado(v, n);
    srand(SEMENTE);

    for (int i = n - 1; i > 0; i--){
        j = ((rand() % 32768) * 32768 + rand() % 32768) % (i + 1);

        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}


// preenche o vetor sem repetir numeros de forma ordenada
void gerar_ordenado(int v[], int n){
    for (int i = 0; i < n; i++){
        v[i] = i + 1;
    }
}

// preenche o vetor sem repetir numeros de forma inversa
void gerar_inverso(int v[], int n){
    for (int i = 0; i < n; i++){
        v[i] = n - i;
    }
}


// Imprimir o vetor
void imprimir_vetor(int v[], int n){
    for (int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

// Descarta tudo o que sobrou no buffer do teclado até o Enter
// Evita que uma letra digitada no lugar de um número trave o programa
void limpa_buffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);   // lê e joga fora caractere por caractere
}

// Mostra qual opção foi escolhida e em qual etapa ela será implementada
// Provisória: some do código quando todas as opções estiverem prontas
void aviso_pendente(char *nome, int etapa){
    printf("\n%s\n", nome);
    printf("[PENDENTE] sera implementada na Etapa %d.\n", etapa);
}