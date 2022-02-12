#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define V 5000

void floydWarshall(int **graph)
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

	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
		{
			dist[i][j] = graph[i][j];
		}

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
	floydWarshall(graph);
	time(&end);
	printf("\nTempo de execução : %ld segundos.\n", end - start);
	return 0;
}
