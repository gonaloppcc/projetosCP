#include "../include/utils.h"
#include <stdlib.h>
#include <math.h>

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

/**
 * @brief Initializes the vector of samples randomly
 * 
 * @param n Number of samples to create
 * @return PArray with all the generated samples
*/
PArray init_vector(int n) {
    srand(SEED);

    PArray vector = malloc(sizeof(Point) * n);

    for (int i = 0; i < n; i++) {
        vector[i] = (Point) malloc(sizeof(struct point));

        vector[i]->x = (float) rand() / RAND_MAX;
        vector[i]->y = (float) rand() / RAND_MAX;
        vector[i]->cluster = -1;
    }

    return vector;
}

/**
 * @brief Assigns the closest centroid to each sample
 * 
 * @param vector Array of samples
 * @param n Number of samples
 * @param clusters Array of centroids
 * @param k Number of clusters
*/
void assign_clusters(PArray vector, int n, PArray clusters, int k) {
    for (int i = 0; i < n; i++) {
        int closest = 0;
        float shortest_dist = __FLT_MAX__; // Set maximum possible distance
        
        for (int o = 0; o < k; o++) {
            // Euclidean distance: dist = sqrt( (x1-x2)^2 + (y1-y2)^2 )
            float dist = sqrtf(powf( vector[i]->x-clusters[o]->x, 2) + (powf( vector[i]->y-clusters[o]->y, 2)));
            if (dist < shortest_dist) {
                shortest_dist = dist;
                closest = o;
            }
        }

        vector[i]->cluster = closest;
    }
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
