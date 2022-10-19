#include "../include/utils.h"
#include <stdlib.h>

#define SEED 10

PArray init_clusters(int k) {
    // TODO: This function inits the clusters by random, I don't if this is the intended action
    srand(SEED);

    PArray clusters = malloc(sizeof(Point) * k);

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

inline void static compute_centroid(Point cluster, PArray clusterPoints, int clusterPointsSize) {
    float sumX = 0;
    float sumY = 0;

    for (int i = 0; i < clusterPointsSize; ++i) {
        Point point = clusterPoints[i];

        sumX += point->x;
        sumY += point->y;
    }

    cluster->x = sumX / clusterPointsSize;
    cluster->y = sumY / clusterPointsSize;
}

void compute_centroids(
        PArray clusters,
        int numberOfClusters,
        PArray *clustersPoints,
        int *clustersPointsSizes
) {
    for (int i = 0; i < numberOfClusters; ++i) {
        compute_centroid(clusters[i], clustersPoints[i], clustersPointsSizes[i]);
    }
}
