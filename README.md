# 3º Trabalho Prático – Métodos de Ordenação e Busca

**Universidade Federal do Paraná (UFPR)** – Setor de Educação Profissional e Tecnológica
**Curso:** Tecnologia em Análise e Desenvolvimento de Sistemas
**Disciplina:** Estrutura de Dados – Profa. Me. Andreia de Jesus

**Dupla:** Felipe Azevedo e Vitor Savi

| Questão | Tema | Responsável |
|---|---|---|
| 1 | Ordenação de Dados | Felipe |
| 2 | Busca de Dados | Vitor |

---

## Questão 1 – Ordenação de Dados

O programa ordena vetores dinâmicos de inteiros **sem repetição** com quatro métodos e mede, para cada ordenação:

- a quantidade de **comparações**;
- a quantidade de **permutações**;
- o **tempo gasto**.

### Métodos implementados

| Método | Função | Complexidade (material da disciplina) |
|---|---|---|
| Bubblesort | `bolha` | O(n²) – melhor caso: vetor ordenado |
| Selection Sort | `selecao_direta` | O(n²) em todos os casos |
| Insertion Sort | `insertion_sort` | O(n) no melhor caso, O(n²) no pior |
| Shell Sort | `shell_sort` | O(n log² n) – sequência h = 3h + 1 |

### Conjuntos de dados

Para cada tamanho (**10, 100, 1.000, 10.000, 100.000 e 1.000.000**) são gerados 3 vetores iniciais:

1. **Ordenado:** 1, 2, ..., n
2. **Inversamente ordenado:** n, ..., 2, 1
3. **Aleatório:** os números de 1 a n embaralhados, sem repetição

O vetor é alocado com `malloc`, ordenado nos 3 cenários e liberado com `free` antes do próximo tamanho. São 18 vetores por método, 72 ordenações no total.

### Compilação e execução

```bash
gcc ordenacao.c -o ordenacao
./ordenacao
```

No Windows, execute `ordenacao.exe`.

### Menu

```
1. Testar Bubblesort
2. Testar Selection Sort
3. Testar Insertion Sort
4. Testar Shell Sort
5. Rodar experimento completo (gera .txt)
0. Sair
```

- **Opções 1 a 4:** pedem um tamanho e ordenam os 3 cenários com o método escolhido. Para até 20 elementos, mostram o vetor antes e depois da ordenação.
- **Opção 5:** executa os 4 métodos com todos os tamanhos e cenários e grava o resultado em um arquivo `.txt`. O nome do arquivo é digitado na execução.

### Formato do arquivo de saída

```
Método de ordenação: Bubblesort

Conjunto com 10 elementos - inicialmente ordenado
Quantidade de Comparações: 45
Quantidades de Permutações: 0
Tempo gasto para ordenação: 0.000000 segundos

Conjunto com 10 elementos - inicialmente ordenado inversamente
...
```

### Decisões de implementação

- **Comparações:** contam apenas as comparações **entre elementos do vetor** (ex.: `A[j] > A[j+1]`). As comparações de controle dos laços não entram na contagem.
- **Permutações:** contam cada vez que um elemento muda de posição. No Bubblesort e no Selection Sort é cada troca. No Insertion Sort e no Shell Sort é cada deslocamento.
- **Contadores `long long`:** com 1.000.000 de elementos, os métodos O(n²) passam de 500 bilhões de comparações, valor que não cabe em `int`.
- **Semente fixa (`srand(42)`):** os 4 métodos ordenam exatamente o mesmo vetor aleatório de cada tamanho, o que deixa a comparação entre eles justa.
- **Dois `rand()` combinados:** no Windows, `RAND_MAX` vale 32.767. A combinação permite sortear posições em vetores de até 1.000.000 de elementos.
- **Verificação:** depois de cada ordenação, a função `esta_ordenado` confere se o vetor ficou em ordem crescente.

### Ajustes nos algoritmos do material da disciplina

| Método | Ajuste |
|---|---|
| Bubblesort | `<` trocado por `>` (o original ordena em ordem decrescente) |
| Selection Sort | Sintaxe corrigida (`in` → `int` e `}` faltando) |
| Insertion Sort | Nenhum, além dos contadores |
| Shell Sort | Sintaxe corrigida (`;` faltando e travessão no lugar de `-`); `while (h > 1)` para evitar uma passada extra com `h = 0` |

### Observação sobre o tempo de execução

Com 1.000.000 de elementos, o Bubblesort, o Selection Sort e o Insertion Sort (nos cenários inverso e aleatório) podem levar **dezenas de minutos cada**. O Shell Sort ordena o mesmo conjunto em menos de 1 segundo. O progresso aparece na tela durante a execução da opção 5.

---

## Questão 2 – Busca de Dados

Implementação da **Pesquisa Sequencial** e da **Pesquisa Binária**:

- O usuário informa a quantidade de elementos do vetor.
- O vetor é preenchido com números aleatórios entre 100 e 100.000.
- O usuário informa 3 números para buscar.
- Para cada número, o programa informa se ele foi encontrado e quantas comparações cada algoritmo fez.
- A pesquisa sequencial é feita no vetor original (não ordenado) e a binária no vetor ordenado.

---

## Referências

- Material da disciplina: *Classificação e Busca de Dados* e *Complexidade de Algoritmos* – Profa. Andreia de Jesus.
- BACKES, André Ricardo. *Estrutura de Dados Descomplicada: em Linguagem C*. Rio de Janeiro: Elsevier, 2016.