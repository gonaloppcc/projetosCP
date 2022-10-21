#include "../include/utils.h"
#include <stdlib.h>
#include <math.h>

#define SEED 10

/**
 * @brief Initializes the clusters with the respective first samples
 *
 * @param k Number of clusters to create
 * @return CArray with all the generated clusters
 */
CArray init_clusters(int k) {
    // TODO: This function inits the clusters by random, I don't if this is the intended action
    srand(SEED);

    CArray clusters = malloc(sizeof(Cluster) * k);

    for (int i = 0; i < k; ++i) {
        clusters[i] = (Cluster) malloc(sizeof(struct cluster));

        clusters[i]->x = (float) rand() / RAND_MAX;
        clusters[i]->y = (float) rand() / RAND_MAX;
        clusters[i]->points_size = 0;
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

inline static float euclidean_distance(Cluster cluster, Point point) {
    return sqrtf(powf(cluster->x - point->x, 2) + (powf(cluster->y - point->y, 2)));
}

/**
 * @brief Assigns the closest centroid to each sample
 * 
 * @param points Array of samples
 * @param n Number of samples
 * @param clusters Array of centroids
 * @param k Number of clusters
*/
void assign_clusters(PArray points, int n, CArray clusters, int k) {
    for (int i = 0; i < n; i++) {
        int closest = 0;
        float shortest_dist = __FLT_MAX__; // Set maximum possible distance

        for (int o = 0; o < k; o++) {
            // Euclidean distance: dist = sqrt( (x1-x2)^2 + (y1-y2)^2 )
            float dist = euclidean_distance(clusters[o], points[i]);
            if (dist < shortest_dist) {
                shortest_dist = dist;
                closest = o;
            }
        }

        points[i]->cluster = closest;
        clusters[closest]->points_size++;
    }
}

void compute_centroids(
        PArray points,
        int n,
        CArray clusters,
        int k
) {
    float *sum_clusters_points = (float *) calloc(k * 2, sizeof(float));

    for (int i = 0; i < n; ++i) {
        Point point = points[i];

        sum_clusters_points[point->cluster * 2] += point->x;
        sum_clusters_points[point->cluster * 2 + 1] += point->y;
    }

    for (int i = 0; i < k; ++i) {
        Cluster cluster = clusters[i];

        cluster->x = sum_clusters_points[i * 2] / cluster->points_size;
        cluster->y = sum_clusters_points[i * 2 + 1] / cluster->points_size;

        // Reset points_size field
        cluster->points_size = 0;
    }

    free(sum_clusters_points);
}
