#include "../include/utils.h"
#include <stdio.h>

#define N 10000000 // Number of samples
#define K 4 // Number of clusters

/*
 // TODO: APAGAR ISTO DEPOIS!
 [ ] 1. [Criar as amostras e] iniciar os “clusters”
     [ ] a. [Iniciar um vetor com valores aleatórios (N amostras no espaço (x,y) )]
     [ ] b. Iniciar os K clusters com as coordenadas das primeiras K amostras
     [ ] c. Atribuir cada amostra ao cluster mais próximo usando a distância euclidiana

 [ ] 2. Calcular o centroide de cada “cluster” (também conhecido como centro geométrico)
 [ ] 3. Atribuir cada amostra ao “cluster” mais próximo usando a distância euclidiana
 [ ] 4. Repetir os passos 2 e 3 até não existirem pontos que mudem de “cluster”
 */


int main() {
    printf("Hello from main function!\n");

    init_vector();
    PArray clusters = init_clusters(K);

    // Define the flux of the program here


    // Program Output
    printf("N = %d, K = %d\n", N, K);
    for (int i = 0; i < K; ++i) {
        printf("Center: (%f, %f) : Size: Undefined\n", clusters[i]->x, clusters[i]->y);
    }
    printf("Iterations: Undefined\n");

    return 0;
}
