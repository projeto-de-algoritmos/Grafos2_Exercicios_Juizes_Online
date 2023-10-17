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

// Função "desenfileirar" - Retorna o primeiro elemento da fila
int desenfileirar() {
    int x = fila->elemento;
    Fila *aux = fila;
    fila = fila->prox;
    free(aux);
    return x;
}

// Função "estaVazia" - Verifica se a fila está vazia
int estaVazia() {
    if (fila == NULL)
        return 1;
    return 0;
}

int numCidades, numEstradas, numCidadesRota, cidadeConserto, grafo[1000][1000], custos[1000];

void inicializarGrafo() {
    for (int i = 0; i < numCidades; i++) {
        for (int j = 0; j < numCidades; j++) {
            grafo[i][j] = INT_MAX;
        }
        custos[i] = INT_MAX;
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

    while (scanf("%d %d %d %d", &numCidades, &numEstradas, &numCidadesRota, &cidadeConserto) == 4) {
        if (numCidades == 0 && numEstradas == 0 && numCidadesRota == 0 && cidadeConserto == 0)
            break;

        inicializarGrafo();
 
        for (int i = 1; i <= numEstradas; i++) {

            int cidadeOrigem, cidadeDestino, custoEstrada;
            scanf("%d %d %d", &cidadeOrigem, &cidadeDestino, &custoEstrada);
            // Se ambas as cidades estiverem fora da rota de serviço
            if (cidadeOrigem >= numCidadesRota && cidadeDestino >= numCidadesRota) {
                // Adicione a aresta normalmente (ida e volta)
                grafo[cidadeOrigem][cidadeDestino] = custoEstrada;
                grafo[cidadeDestino][cidadeOrigem] = custoEstrada;
            }
            // Se a cidadeDestino pertencer à rota de serviço
            if (cidadeOrigem >= numCidadesRota && cidadeDestino < numCidadesRota)
                grafo[cidadeOrigem][cidadeDestino] = custoEstrada; // Adicione apenas a estrada que chega na cidadeDestino

            // Se a cidadeOrigem pertencer à rota de serviço
            if (cidadeOrigem < numCidadesRota && cidadeDestino >= numCidadesRota)
                grafo[cidadeDestino][cidadeOrigem] = custoEstrada; // Adicione apenas a estrada que chega na cidadeOrigem

            // Se ambas as cidades forem cidades consecutivas na rota de serviço
            if (cidadeOrigem < numCidadesRota && cidadeDestino < numCidadesRota && abs(cidadeOrigem - cidadeDestino) == 1) { // cidadeOrigem < numCidadesRota && cidadeDestino < numCidadesRota significa que cidadeOrigem e cidadeDestino pertencem à rota de serviço
                // Adicione a estrada normalmente
                grafo[cidadeOrigem][cidadeDestino] = custoEstrada;
                grafo[cidadeDestino][cidadeOrigem] = custoEstrada;
            }
        }
        printf("%d\n", dijkstra(cidadeConserto, numCidadesRota - 1));
    }
    return 0;
}
