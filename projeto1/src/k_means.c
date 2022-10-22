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
    PArray samples = init_samples(N);
    CArray clusters = init_clusters(samples, K);

    /*
     * Main loop of the program
     * We assign a cluster to each sample and then calculate the new centroid of the cluster
     * Once no sample changes cluster we found the solution and exit the loop
    */
    int changed = 1;
    int iterations = 0;

    while (changed) {
        iterations++;

        changed = assign_clusters(samples, N, clusters, K);
        compute_centroids(samples, N, clusters, K);

        // printf("Iteration %d done\n", iterations);
        //fflush(stdout);
    }

    // Program Output
    printf("N = %d, K = %d\n", N, K);
    for (int i = 0; i < K; ++i) {
        printf("Center: (%f, %f) : Size: %d\n", clusters[i]->x, clusters[i]->y, clusters[i]->samples_size);
    }
    printf("Iterations: %d\n", iterations);

    /* This print is just for debugging, enabling it will flood the console with garbage...
       TODO: Delete this
    
    printf("Printing samples...\n");
    for (int i = 0; i < N; ++i) {
        printf("(%f,%f) : Cluster: %d\n", samples[i]->x, samples[i]->y, samples[i]->cluster);
    }
    
    */
    return 0;
}
