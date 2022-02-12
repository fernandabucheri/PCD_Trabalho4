import multiprocessing as mp
import time as t
from functools import partial

import numpy as np

INF = float("inf")

# Informações para geração dos grafos
GRAPH_SIZE = 400
INF_LIMIT = 10
MIN_LIMIT = 1
MAX_LIMIT = 35


# https://github.com/TamaWilson/floyd_python/blob/master/floyd.py
def floyd_original(g):
    ponderados = g

    len_matrix = len(g)

    # Aplicação do algoritmo de Floyd
    for k in range(len_matrix):
        for i in range(len_matrix):
            for j in range(len_matrix):
                ponderados[i][j] = min(ponderados[i][j], ponderados[i][k] + ponderados[k][j])

    return ponderados


def floyd_serial(i, ponderados, ponderados_len, k):
    for j in range(ponderados_len):
        ponderados[i][j] = min(ponderados[i][j], ponderados[i][k] + ponderados[k][j])
    return i, ponderados[i]


def floyd_parallel(g, pool_size):
    ponderados = g

    len_matrix = len(g)

    pool = mp.Pool(processes=pool_size)

    # Aplicação do algoritmo de Floyd
    for k in range(len_matrix):
        p = partial(floyd_serial, ponderados=ponderados, ponderados_len=len_matrix, k=k)
        result_list = pool.map(p, range(len_matrix))
        for result in result_list:
            ponderados[result[0]] = result[1]
    pool.close()
    pool.join()
    return ponderados


if __name__ == '__main__':
    def graph_generator(size, inf_limit, rand_min, rand_max):
        graph = np.random.randint(rand_min, rand_max, size=(size, size))

        def inf_fill(x):
            return INF if x >= inf_limit else float(x)

        inf = np.vectorize(inf_fill)
        return inf(graph)


    pool_size = input('Digite o número de threads (int): ')

    generated_graph = graph_generator(GRAPH_SIZE, INF_LIMIT, MIN_LIMIT, MAX_LIMIT)
    if int(pool_size) > 0:
        t1 = t.time()
        floyd_parallel_result = floyd_parallel(generated_graph, int(pool_size))
        t2 = t.time()
        print(f'Tempo de execução do código paralelo: {t2 - t1}s')
    else:
        t1 = t.time()
        floyd_original_result = floyd_original(generated_graph)
        t2 = t.time()
        print(f'Tempo de execução do código serial: {t2 - t1}s')
