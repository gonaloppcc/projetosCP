#include "../include/utils.h"
#include <stdio.h>

#define N 10000000 // Number of samples
#define K 4 // Number of clusters

/*
 // TODO: APAGAR ISTO DEPOIS!
 [ ] 1. [Criar as amostras e] iniciar os “clusters”
     [ ] a. [Iniciar um vetor com valores aleatórios (N amostras no espaço (x,y) )]
     [ ] b. Iniciar os K clusters com as coordenadas das primeiras K amostras

 [ ] 2. Atribuir cada amostra ao cluster mais próximo usando a distância euclidiana
 [ ] 3. Calcular o centroide de cada “cluster” (também conhecido como centro geométrico)
 [ ] 4. Repetir os passos 2 e 3 até não existirem pontos que mudem de “cluster”
 */


int main() {
    printf("Hello from main function!\n");

    PArray samples = init_samples(N);
    CArray clusters = init_clusters(samples, K);

    assign_clusters(samples, N, clusters, K);

    // TODO: Define the flux of the program here


    // Program Output
    printf("N = %d, K = %d\n", N, K);
    for (int i = 0; i < K; ++i) {
        printf("Center: (%f, %f) : Size: %d\n", clusters[i]->x, clusters[i]->y, clusters[i]->samples_size);
    }
    printf("Iterations: Undefined\n");

    /* This print is just for debugging, enabling it will flood the console with garbage...
       TODO: Delete this
    
    printf("Printing samples...\n");
    for (int i = 0; i < N; ++i) {
        printf("(%f,%f) : Cluster: %d\n", samples[i]->x, samples[i]->y, samples[i]->cluster);
    }
    
    */
    return 0;
}
