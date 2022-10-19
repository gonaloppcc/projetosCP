#include "../include/utils.h"
#include <stdlib.h>

#define SEED 10

Array init_clusters(int k) {
    // TODO: This function inits the clusters by random, I don't if this is the intended action
    srand(SEED);

    Array clusters = malloc(sizeof(Point) * k);

    for (int i = 0; i < k; ++i) {
        clusters[i] = (Point) malloc(sizeof(struct point));

        clusters[i]->x = (float) rand() / RAND_MAX;
        clusters[i]->y = (float) rand() / RAND_MAX;
    }

    return clusters;
}

void init_vector() {

}

void assign_clusters() {

}

void compute_centroids() {

}
