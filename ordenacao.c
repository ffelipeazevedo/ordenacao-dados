#include <stdlib.h>
#include <stdio.h>
#include <time.h>             // clock() - medição do tempo (Etapa 2)

// Constantes
// (os #define de métodos, cenários e tamanhos entram a partir da Etapa 1)

// Funcoes
void aviso_pendente(char *nome, int etapa);    // avisa que a opção ainda não foi implementada
void limpa_buffer(void);                       // descarta o que sobrou no teclado

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
            case 1:     // gera ordenado / inverso / aleatório e imprime
                aviso_pendente("Geracao dos vetores", 1);
                break;

            case 2:     // ordena um vetor de teste com Bubblesort
                aviso_pendente("Bubblesort", 3);
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