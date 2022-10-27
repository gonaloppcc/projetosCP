#include "../include/utils.h"
#include <stdlib.h>
#include <math.h>

#define SEED 10

/**
 * @brief Initializes the clusters with the respective first samples
 *
 * @param samples Array of samples
 * @param k Number of clusters to create
 * @return CArray with all the generated clusters
 */
CArray init_clusters(PArray samples, int k) {
    CArray clusters = malloc(sizeof(Cluster) * k);

    for (int i = 0; i < k; ++i) {
        clusters[i] = (Cluster) malloc(sizeof(struct cluster));

        clusters[i]->x = samples[i]->x;
        clusters[i]->y = samples[i]->y;
        clusters[i]->samples_size = 0;
    }

    return clusters;
}

/**
 * @brief Initializes the samples randomly
 * 
 * @param n Number of samples to create
 * @return PArray with all the generated samples
*/
PArray init_samples(int n) {
    srand(SEED);

    PArray samples = malloc(sizeof(Point) * n);

    for (int i = 0; i < n; i++) {
        samples[i] = (Point) malloc(sizeof(struct point));

        samples[i]->x = (float) rand() / RAND_MAX;
        samples[i]->y = (float) rand() / RAND_MAX;
        samples[i]->cluster = -1;
    }

    return samples;
}

inline static float euclidean_distance(Cluster cluster, Point point) {
    return powf(cluster->x - point->x, 2) + (powf(cluster->y - point->y, 2));
}

/**
 * @brief Assigns the closest centroid to each sample
 * 
 * @param samples Array of samples
 * @param n Number of samples
 * @param clusters Array of centroids
 * @param k Number of clusters
*/
int assign_clusters(PArray samples, int n, CArray clusters, int k) {
    int cluster_changed = 0;

    for (int i = 0; i < k; ++i) { // Reset samples_size field in all clusters
        clusters[i]->samples_size = 0;
    }

    for (int i = 0; i < n; i++) {
        int closest = samples[i]->cluster; // Set the previous assigned cluster as the closest one
        float shortest_dist = __FLT_MAX__; // Set maximum possible distance

        for (int o = 0; o < k; o++) {
            // Euclidean distance: dist = sqrt( (x1-x2)^2 + (y1-y2)^2 )
            float dist = euclidean_distance(clusters[o], samples[i]);
            if (dist < shortest_dist) {
                shortest_dist = dist;
                closest = o;
            }
        }

        if (samples[i]->cluster != closest) {
            samples[i]->cluster = closest;
            cluster_changed = 1;
        }
        clusters[closest]->samples_size++;
    }

    return cluster_changed;
}

/**
 * @brief Computes the centroids, assigning a new position for each cluster
 *
 * @param samples Array of samples
 * @param n Number of samples
 * @param clusters Array of centroids
 * @param k Number of clusters
 */
void compute_centroids(
        PArray samples,
        int n,
        CArray clusters,
        int k
) {
    float *sum_clusters_samples = (float *) calloc(k * 2, sizeof(float));

    for (int i = 0; i < n; ++i) {
        Point point = samples[i];

        sum_clusters_samples[point->cluster * 2] += point->x;
        sum_clusters_samples[point->cluster * 2 + 1] += point->y;
    }

    for (int i = 0; i < k; ++i) {
        Cluster cluster = clusters[i];

        cluster->x = sum_clusters_samples[i * 2] / cluster->samples_size;
        cluster->y = sum_clusters_samples[i * 2 + 1] / cluster->samples_size;
    }

    free(sum_clusters_samples);
}
