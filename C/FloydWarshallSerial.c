#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 5000

void floydWarshall(int **graph) {
    int **dist;
    int i, j, k;

    dist = malloc(V * sizeof(int *));
    for (i = 0; i < V; i++)
        dist[i] = malloc(V * sizeof(int));

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    for (k = 0; k < V; k++)
        for (i = 0; i < V; i++)
            for (j = 0; j < V; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

int main() {

    int **graph;
    int i, j;
    time_t start, end;

    graph = malloc(V * sizeof(int *));

    for (i = 0; i < V; i++)
        graph[i] = malloc(V * sizeof(int));

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            graph[i][j] = rand() % 2500;

    time(&start);
    floydWarshall(graph);
    time(&end);
    printf("\nTempo de execução : %ld segundos.\n", end - start);
    return 0;
}
