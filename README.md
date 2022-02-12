# Otimização do Algoritmo de caminho mínimo entre grafos de Floyd-Warshall, transformando de serial para paralelo.

<br>

## Descrição do algoritmo
O algoritmo de Floyd-Warshall foi desenvolvido por Bernard Roy, Stephen Warshall e Robert Floyd em 1962. 
Seu objetivo é encontrar o caminho mais curto entre todos os pares de vértices de um grafo direcionado e ponderado, gerando como saída uma matriz de distâncias que contém os valores do menor caminho entre cada par de vértices.

<br>

## Complexidade 
Os três laços aninhados são executados n vezes, logo, a complexidade final é O(n^3), ou mais precisamente, Θ(n^3). 

<br>

## Paralelização

Como mencionado anteriormente, o código tem uma alta complexidade, logo o nosso trabalho visa melhorar o tempo de execução do algoritmo. Fizemos a paralelização utilizando duas linguagens de programação diferentes, C e Python, nos baseando em códigos disponíveis [aqui (em C)](https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/) e [aqui (em Python)](https://github.com/TamaWilson/floyd_python/blob/master/floyd.py). 

Em C optamos por utilizar a API para programação paralela **OpenMP**, enquanto que em Python utilizamos as bibliotecas **multiprocessing** e **functools**.

<br>

## Resultados
### _Linguagem de programação C_
Em C fizemos testes inserindo grafos de tamanho 5000 x 5000. 
<br>
O **código serial levou 82 segundos** para executar, enquanto que o **código com 8 threads demorou 21 segundos** para ser executado. 
<br><br>

### _Linguagem de programação Python_
Em python fizemos testes inserindo grafos de tamanho 400 x 400.
<br>
O **código serial levou 44,48 segundos** para executar, enquanto que o **código com 4 threads demorou 21,74 segundos** para ser executado. 
<br><br>

### _Gráficos_
Foram montados gráficos para melhor visualização dos resultados obtidos e com outros testes. Os mesmos estão disponíveis [aqui](https://docs.google.com/spreadsheets/d/1H5-Em80YQwA0ypmRPsdF6hyoEcKSBcKjR6gqlPUFNW8/edit?usp=sharing). 

<br>

## Conclusão
Os resultados obtidos foram extremamente satisfatórios, tendo em vista que em C foi possível obter uma execução quatro vezes mais rápida e em python conseguimos reduzir o tempo de execução pela metade. 

<br><br>

# Para compilar

### 1) Código em C que utiliza OpenMP
<br>

``` 
$ gcc -O3 -fopenmp -o \<executável> \<nome do arquivo>.c
$ time ./\<executável>
```
<br>

- O parâmetro -O3 presente na primeira linha é uma das flags que o compilador GCC possui. Ela serve para deixar o executável mais rápido, fazendo com que seja possível ocupar melhor os recursos do processador (paralelismo no nível de instruções).

- O _time_, presente na segunda linha, opcional. Ele serve para mostrar mais detalhadamente o tempo de execução do programa).

<br> 

### 2) Código em C serial
<br>

``` 
$ gcc -O3 \<nome do arquivo>.c -o \<executável>
$ time ./\<executável>
```

<br>

#

<br>

## Referências
- Aulas disponíveis no classroom da matéria.
- [Algoritmo de Floyd-Warshall](https://pt.wikipedia.org/wiki/Algoritmo_de_Floyd-Warshall)
- [Um estudo sobre algoritmos para roteirização](https://periodicos.utfpr.edu.br/recit/article/download/e-5122/pdf_1)
- [Teoria dos Grafos](http://www.decom.ufop.br/marco/site_media/uploads/bcc204/07_aula_07.pdf)
- [Documentação de Python](https://docs.python.org/dev/library/multiprocessing.html)
- [Uma pequena introdução a programação paralela e multiprocessamento com python - Adson Rodrigues](https://medium.com/@adson.develop/uma-pequena-introdu%C3%A7%C3%A3o-a-programa%C3%A7%C3%A3o-paralela-e-multiprocessamento-com-python-232bbf72a8f7#:~:text=Aqui%2C%20veremos%20o%20m%C3%B3dulo%20multiprocessing,Python%20possui%20muitos%20recursos%20poderosos.)
