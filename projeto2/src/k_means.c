#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_ITERATIONS 20

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Use: kmeans [SAMPLE_NUM] [CLUSTER_NUM] [THREAD_NUM]\n");
        return 1;
    }

    int sample_num = atoi(argv[1]);
    int cluster_num = atoi(argv[2]);
    int thread_num = atoi(argv[3]);

    omp_set_num_threads(thread_num);

    SArray samples = init_samples(sample_num);
    CArray clusters = init_clusters(samples, cluster_num);

    /*
     * Main loop of the program
     * We assign a cluster to each sample and then calculate the new centroid of the cluster
     * Once no sample changes cluster we found the solution and exit the loop
    */
    int changed = 1;
    int iterations = 0;

    while (iterations < MAX_ITERATIONS && changed) {
        changed = compute_samples(samples, sample_num, clusters, cluster_num);

        iterations += changed; // If the algorithm has not converged we increment, otherwise iterations stays the same
    }

    // Program Output
    printf("N = %d, K = %d\n", sample_num, cluster_num);
    for (int i = 0; i < cluster_num; ++i) {
        printf("Center: (%.3f, %.3f) : Size: %d\n", clusters->x[i], clusters->y[i], clusters->samples_size[i]);
    }
    printf("Iterations: %d\n", iterations);

    return 0;
}
