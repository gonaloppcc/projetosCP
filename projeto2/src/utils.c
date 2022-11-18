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
CArray init_clusters(SArray samples, int k) {
    CArray clusters = (CArray) malloc(sizeof(Clusters));

    clusters->x = malloc(k * sizeof(float));
    clusters->y = malloc(k * sizeof(float));
    clusters->samples_size = malloc(k * sizeof(int));

    for (int i = 0; i < k; ++i) { // Complexity: K
        clusters->x[i] = samples->x[i];
        clusters->y[i] = samples->y[i];
        clusters->samples_size[i] = 0;
    }

    return clusters;
}

/**
 * @brief Initializes the samples randomly
 * 
 * @param n Number of samples to create
 * @return SArray with all the generated samples
*/
SArray init_samples(int n) {
    srand(SEED);

    SArray samples = malloc(sizeof(Samples));

    samples->x = malloc(n * sizeof(float));
    samples->y = malloc(n * sizeof(float));
    samples->cluster = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) { // Complexity: N
        samples->x[i] = (float) rand() / RAND_MAX;
        samples->y[i] = (float) rand() / RAND_MAX;
        samples->cluster[i] = -1;
    }

    return samples;
}

inline static float distance(float cluster_x, float cluster_y, float sample_x, float sample_y) {
    return powf(cluster_x - sample_x, 2) + (powf(cluster_y - sample_y, 2));
}

/**
 * @brief Assigns the closest centroid to each sample
 *
 * @param samples Array of samples
 * @param n Number of samples
 * @param clusters Array of centroids
 * @param k Number of clusters
*/
int assign_clusters(SArray samples, int n, CArray clusters, int k) {
    int cluster_changed = 0;
    int sample_sizes[k];
    float clusters_x[k];
    float clusters_y[k];


    for (int i = 0; i < k; ++i) { // Reset samples_size field in all clusters
        sample_sizes[i] = 0;
        clusters_x[i] = 0;
        clusters_y[i] = 0;
    } // Complexity: K

#pragma omp parallel for reduction(+:sample_sizes, clusters_x, clusters_y)
    for (int i = 0; i < n; i++) { // Complexity: N
        int closest = samples->cluster[i]; // Set the previous assigned cluster as the closest one
        float shortest_dist = __FLT_MAX__; // Set maximum possible distance

        for (int o = 0; o < k; o++) { // Complexity: K
            // Euclidean distance: dist = sqrt( (x1-x2)^2 + (y1-y2)^2 )
            float dist = distance(clusters->x[o], clusters->y[o], samples->x[i], samples->y[i]);
            if (dist < shortest_dist) {
                shortest_dist = dist;
                closest = o;
            }
        }

        if (samples->cluster[i] != closest) {
            samples->cluster[i] = closest;
            cluster_changed = 1;
        }
        sample_sizes[closest]++;
        clusters_x[closest] += samples[i].x;
        clusters_y[closest] += samples[i].y;
    }

    for (int i = 0; i < k; i++) {
        clusters->samples_size[i] = sample_sizes[i];
        clusters[i].samples_size = sample_sizes[i];
        clusters[i].x = clusters_x[i] / sample_sizes[i];
        clusters[i].y = clusters_y[i] / sample_sizes[i];
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
        SArray samples,
        int n,
        CArray clusters,
        int k
) {
    for (int i = 0; i < k; ++i) { // Complexity: K
        clusters->x[i] /= clusters->samples_size[i];
        clusters->y[i] /= clusters->samples_size[i];
    }
}
