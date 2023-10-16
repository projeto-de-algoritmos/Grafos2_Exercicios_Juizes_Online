#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Fila {
    int elemento;
    struct Fila *prox;
} Fila;

Fila *fila = NULL;

// Função "enfileirar" - Adiciona um elemento na fila (FIFO - First In First Out)
void enfileirar(int x) {
    Fila *novoElemento = malloc(sizeof(Fila));
    novoElemento->elemento = x;
    novoElemento->prox = NULL;
    if (fila == NULL)
        fila = novoElemento;
    else {
        Fila *aux = fila;
        while (aux->prox != NULL) // Encontra o último elemento da fila
            aux = aux->prox;
        aux->prox = novoElemento;
    }
}

// Algoritmo de Dijkstra
int dijkstra(int origem, int destino) {
    custos[origem] = 0;
    enfileirar(origem);
    while (!estaVazia()) {
        int i = desenfileirar();
        for (int j = 0; j < numCidades; j++) {
            /*
            - Se existe uma aresta entre i e j (grafo[i][j] != INT_MAX)
            - Se o custo de j é maior que o custo de i + o custo da aresta (custos[j] > custos[i] + grafo[i][j])
            */
            if (grafo[i][j] != INT_MAX && custos[j] > custos[i] + grafo[i][j]) {
                custos[j] = custos[i] + grafo[i][j]; // Atualiza o custo de j --> garante o menor caminho
                enfileirar(j);
            }
        }
    }
    return custos[destino];
}

int main() {
    /*
    Leitura dos dados
    numCidades = número de cidades
    numEstradas = número de estradas
    numCidadesRota = número de cidades na rota de serviço
    cidadeConserto = cidade onde o veículo foi consertado
    */

    printf("%d\n", dijkstra(cidadeConserto, numCidadesRota - 1));

    return 0;
}
