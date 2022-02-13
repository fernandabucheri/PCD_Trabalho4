#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define V 5

void printSolution(int **dist) {
    printf("A matriz a seguir mostra as distâncias mais curtas entre cada par de vértices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(int **graph, int N_THREADS) {
    int **dist;
    int i, j, k;

    dist = malloc(V * sizeof(int *));
    for (i = 0; i < V; i++)
        dist[i] = malloc(V * sizeof(int));

#pragma omp parallel for shared(dist, graph) private(i, j) num_threads(N_THREADS)
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

#pragma omp parallel for shared(dist) private(i, j, k) num_threads(N_THREADS)
    for (k = 0; k < V; k++)
        for (i = 0; i < V; i++)
            for (j = 0; j < V; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    printSolution(dist);
}

int main() {

    int **graph;
    int i, j, N_THREADS;
    time_t start, end;

    graph = malloc(V * sizeof(int *));

    for (i = 0; i < V; i++)
        graph[i] = malloc(V * sizeof(int));

    printf("Digite o número de threads: \n");
    scanf("%d", &N_THREADS);

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            graph[i][j] = rand() % 2500;

    time(&start);
    floydWarshall(graph, N_THREADS);
    time(&end);
    printf("\nTempo de execução : %ld segundos.\n", end - start);
    return 0;
}