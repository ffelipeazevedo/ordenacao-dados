#include <stdlib.h>
#include <stdio.h>
#include <time.h>             // clock() - medição do tempo (Etapa 2)

// Constantes
#define SEMENTE 42
#define ORDENADO  1                   // cenário: inicialmente ordenado
#define INVERSO   2                   // cenário: inicialmente ordenado inversamente
#define ALEATORIO 3                   // cenário: dados em posições aleatórias
#define QTD_TAMANHOS 6                // 10, 100, 1.000, 10.000, 100.000, 1.000.000
 // métodos de ordenação
#define BUBBLE    1                  
#define SELECTION 2
#define INSERTION 3
#define SHELL     4

// Variaveis globais
long long comparacoes = 0;    // comparações entre elementos do vetor
long long permutacoes = 0;    // trocas/deslocamentos de elementos do vetor
// (os #define de métodos, cenários e tamanhos entram a partir da Etapa 1)

// Funcoes
void aviso_pendente(char *nome, int etapa);          // avisa que a opção ainda não foi implementada
void limpa_buffer(void);                             // descarta o que sobrou no teclado
void imprimir_vetor(int v[], int n);                 // imprimi o vetor
void gerar_ordenado(int v[], int n);                 // preenche com 1, 2, ..., n
void gerar_inverso(int v[], int n);                  // preenche com n, ..., 2, 1
void gerar_aleatorio(int v[], int n);                // 1..n embaralhados, sem repetição
int esta_ordenado(int v[], int n);                   // 1 = crescente, 0 = não está ordenado
void gerar_vetor(int cenario, int v[], int n);       // chama o gerador do cenário
void zerar_contadores(void);                         // zera comparacoes e permutacoes
void ordenar(int metodo, int v[], int n);            // chama o método escolhido
double medir_ordenacao(int metodo, int v[], int n);  // ordena e devolve o tempo em segundos
void testar_metodo(int metodo);                      // teste pelo menu: 3 cenários de um tamanho
void Bolha(int A[], int n);                          // Bubblesort (material da professora)
void Selecao_Direta(int A[], int n);                 // Selection Sort (material da professora)
void InsertionSort(int A[], int n);                  // Insertion Sort (material da professora)
void shellsort(int A[], int n);                      // Shell Sort (material da professora)
char *nome_metodo(int metodo);                       // número do método -> nome para o arquivo
char *nome_cenario(int cenario);                     // número do cenário -> texto do enunciado
void gravar_resultado(FILE *arq, int n, int cenario, long long comp, long long perm, double tempo); // grava 1 bloco no .txt
void rodar_experimento_completo(void);               // 4 métodos x 6 tamanhos x 3 cenários -> .txt

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
                testar_metodo(BUBBLE);
                break;

            case 3:     // ordena um vetor de teste com Selection Sort
                testar_metodo(SELECTION);
                break;

            case 4:     // ordena um vetor de teste com Insertion Sort
                testar_metodo(INSERTION);
                break;

            case 5:     // ordena um vetor de teste com Shell Sort
                testar_metodo(SHELL);
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

// Devolve o nome do método para gravar no arquivo
char *nome_metodo(int metodo){
    switch (metodo) {
        case BUBBLE:    return "Bubblesort";
        case SELECTION: return "Selection Sort";
        case INSERTION: return "Insertion Sort";
        case SHELL:     return "Shell Sort";
    }
    return "Desconhecido";
}

// Devolve a descrição do cenário exatamente como no enunciado
char *nome_cenario(int cenario){
    switch (cenario) {
        case ORDENADO:  return "inicialmente ordenado";
        case INVERSO:   return "inicialmente ordenado inversamente";
        case ALEATORIO: return "com dados posicionados de forma aleatória";
    }
    return "desconhecido";
}

// Grava no arquivo o bloco de um conjunto, no formato pedido no enunciado
void gravar_resultado(FILE *arq, int n, int cenario, long long comp, long long perm, double tempo){
    fprintf(arq, "Conjunto com %d elementos - %s\n", n, nome_cenario(cenario));
    fprintf(arq, "Quantidade de Comparações: %lld\n", comp);
    fprintf(arq, "Quantidades de Permutações: %lld\n", perm);
    fprintf(arq, "Tempo gasto para ordenação: %f segundos\n\n", tempo);  
}

// Chama o método de ordenação de acordo com o número (BUBBLE, SELECTION, ...)
void ordenar(int metodo, int v[], int n){
    switch (metodo) {
        case BUBBLE:
            Bolha(v, n);
            break;
        case SELECTION:
            Selecao_Direta(v, n);
            break;
        case INSERTION:
            InsertionSort(v, n);
            break;
        case SHELL:
            shellsort(v, n);
            break;
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

// Selection Sort - código do material da professora
void Selecao_Direta(int A[], int n){
    int i, j, aux, menor;

    for (i = 0; i < n - 1; i++){             // posição i recebe o menor do trecho i..n-1
        menor = i;                           // supõe que o menor é o próprio A[i]
        for (j = i + 1; j < n; j++){         // procura um menor no resto do vetor
            comparacoes++;                   // conta a comparação A[j] < A[menor]
            if (A[j] < A[menor])
                menor = j;                   // guarda só a POSIÇÃO do menor
        }
        aux = A[i];                          // troca A[i] com o menor encontrado
        A[i] = A[menor];
        A[menor] = aux;
        permutacoes++;                       // conta a troca (1 por passada)
    }
}

// Insertion Sort - código do material da professora
void InsertionSort(int A[], int n){
    int i = 0;
    int j = 1;
    int aux = 0;

    while (j < n){                           // A[0..j-1] já está ordenado
        aux = A[j];                          // elemento a ser inserido
        i = j - 1;
        while ((i >= 0) && (A[i] > aux)){    // desloca os maiores que aux para a direita
            comparacoes++;                   // comparação A[i] > aux deu verdadeiro
            A[i + 1] = A[i];
            permutacoes++;                   // conta o deslocamento
            i = i - 1;
        }
        if (i >= 0)                          // o laço parou porque A[i] > aux deu falso:
            comparacoes++;                   // essa comparação também aconteceu
                                             // (se i == -1, o && nem avaliou A[i] > aux)
        A[i + 1] = aux;                      // coloca aux no buraco aberto
        j = j + 1;
    }
}

// Shell Sort - código do material da professora
void shellsort(int A[], int n){
    int i, j, h, aux;

    for (h = 1; h < n; h = 3 * h + 1);       // calcula o h inicial: 1, 4, 13, 40, ... até passar de n

    while (h > 1){
        h = (h - 1) / 3;                     // atualiza o valor de h (... 13 -> 4 -> 1)
        for (i = h; i < n; i++){             // insertion com distância h
            aux = A[i];
            j = i;
            // efetua comparações entre elementos com distância h:
            while (A[j - h] > aux){
                comparacoes++;               // comparação A[j-h] > aux deu verdadeiro
                A[j] = A[j - h];             // desloca o maior h posições para a direita
                permutacoes++;               // conta o deslocamento
                j -= h;
                if (j < h)                   // não há mais elemento a h posições à esquerda
                    break;
            }
            if (j >= h)                      // o laço parou porque A[j-h] > aux deu falso:
                comparacoes++;               // essa comparação também aconteceu
                                             // (se saiu pelo break, a condição não foi avaliada)
            A[j] = aux;                      // coloca aux no lugar
        }
    }
}

// Zera os contadores, cronometra a ordenação e devolve o tempo gasto em segundos
double medir_ordenacao(int metodo, int v[], int n){
    clock_t inicio, fim;

    zerar_contadores();             // contagem começa do zero para este vetor
    inicio = clock();               // marca o "relógio" antes de ordenar
    ordenar(metodo, v, n);
    fim = clock();                  // marca depois

    // clock() conta "tiques"; dividir por CLOCKS_PER_SEC converte para segundos
    // o (double) evita divisão inteira (que daria 0 para tempos menores que 1 s)
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// Teste pelo menu: pede o tamanho, aloca o vetor e ordena os 3 cenários
// Só imprime o vetor se for pequeno (até 20 elementos)
void testar_metodo(int metodo){
    int n;                  // tamanho do vetor informado pelo usuário
    int *v;                 // vetor dinâmico
    double tempo;           // tempo gasto na ordenação

    do {    // repete até digitar um tamanho válido
        printf("Tamanho do vetor (minimo 2): ");
        if (scanf("%d", &n) != 1)
            n = 0;
        limpa_buffer();
        if (n < 2)
            printf("Tamanho invalido!\n");
    } while (n < 2);

    v = (int*)malloc(n * sizeof(int));      // aloca n inteiros
    if (!v){
        printf("Problema de alocacao\n");
        return;
    }

    for (int c = ORDENADO; c <= ALEATORIO; c++){
        gerar_vetor(c, v, n);
        printf("\nCenario %d\n", c);
        if (n <= 20){
            printf("Antes:  ");
            imprimir_vetor(v, n);
        }

        tempo = medir_ordenacao(metodo, v, n);

        if (n <= 20){
            printf("Depois: ");
            imprimir_vetor(v, n);
        }
        printf("Comparacoes: %lld | Permutacoes: %lld | Tempo: %f s | Ordenado? %s\n",
               comparacoes, permutacoes, tempo, esta_ordenado(v, n) ? "sim" : "nao");
    }

    free(v);                // devolve a memória
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