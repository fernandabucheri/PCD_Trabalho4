#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>
#include <time.h>

#define V 5000

void floydWarshall(int **graph, int N_THREADS)
{
	int **dist;

	dist = malloc(5000 * sizeof(int *));
	int i = 0;
	for (; i < 5000; i++)
		dist[i] = malloc(5000 * sizeof(int));

	i = 0;
	int j, k;
	int tid = -1;
	int tid2 = -1;

#pragma omp parallel for shared(dist, graph) private(i, j) num_threads(N_THREADS)
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
		{
			dist[i][j] = graph[i][j];
		}

#pragma omp parallel for shared(dist) private(i, j, k) num_threads(N_THREADS)
	for (k = 0; k < V; k++)
	{
		for (i = 0; i < V; i++)
		{
			for (j = 0; j < V; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
}

int main()
{

	int **graph;
	time_t start, end;
	graph = malloc(5000 * sizeof(int *));
	int i = 0;
	for (; i < 5000; i++)
		graph[i] = malloc(5000 * sizeof(int));
	int N_THREADS;
	printf("Digite o numero de threads\n");
	scanf("%d", &N_THREADS);

	i = 0;
	int j = 0;
	for (; i < V; i++)
	{
		for (j = 0; j < V; j++)
		{
			graph[i][j] = rand() % 2500;
		}
	}

	time(&start);
	floydWarshall(graph, N_THREADS);
	time(&end);
	printf("\nTempo de execução : %ld segundos.\n", end - start);
	return 0;
}
