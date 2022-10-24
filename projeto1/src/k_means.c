#include "../include/utils.h"
#include <stdio.h>

#define N 10000000 // Number of samples
#define K 4 // Number of clusters

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
        changed = assign_clusters(samples, N, clusters, K);
        compute_centroids(samples, N, clusters, K);

        iterations += changed; // If the algorithm has not converged we increment, otherwise iterations stays the same
    }

    // Program Output
    printf("N = %d, K = %d\n", N, K);
    for (int i = 0; i < K; ++i) {
        printf("Center: (%f, %f) : Size: %d\n", clusters[i]->x, clusters[i]->y, clusters[i]->samples_size);
    }
    printf("Iterations: %d\n", iterations);

    return 0;
}
