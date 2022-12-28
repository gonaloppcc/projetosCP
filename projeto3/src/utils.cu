#include "../include/utils.h"
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

#define SEED 10


__device__
inline static float distance(float cluster_x, float cluster_y, float sample_x, float sample_y) {
    return powf(cluster_x - sample_x, 2) + (powf(cluster_y - sample_y, 2));
}

__global__
void calc_closest(
    float *samples_x,
    float *samples_y,
    int n,
    float *clusters_x,
    float *clusters_y,
    int k,
    int *closest_array
) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;

    int closest = -1;
    float shortest_dist = __FLT_MAX__;
    for (int i = 0; i < k; i++) {
        float dist = distance(clusters_x[i], clusters_y[i], samples_x[id], samples_y[id]);
        if (dist < shortest_dist) {
            shortest_dist = dist;
            closest = i;
        }
    }
    closest_array[id] = closest;
}

/**
 * @brief Initializes the clusters with the respective first samples
 *
 * @param samples Array of samples
 * @param k Number of clusters to create
 * @return CArray with all the generated clusters
 */
CArray init_clusters(SArray samples, int k) {
    CArray clusters = (CArray) malloc(sizeof(Clusters));

    clusters->x = (float *) malloc(k * sizeof(float));
    clusters->y = (float *) malloc(k * sizeof(float));
    clusters->samples_size = (int *) malloc(k * sizeof(int));

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

    SArray samples = (SArray) malloc(sizeof(Samples));

    samples->x = (float *) malloc(n * sizeof(float));
    samples->y = (float *) malloc(n * sizeof(float));
    samples->cluster = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) { // Complexity: N
        samples->x[i] = (float) rand() / RAND_MAX;
        samples->y[i] = (float) rand() / RAND_MAX;
        samples->cluster[i] = -1;
    }

    return samples;
}

/**
 * @brief Assigns the closest centroid to each sample and computes the new centroids
 *
 * @param samples Array of samples
 * @param n Number of samples
 * @param clusters Array of centroids
 * @param k Number of clusters
*/
int compute_samples(SArray samples, int n, CArray clusters, int k) {
    int cluster_changed = 0;
    int sample_sizes[k];
    float clusters_x[k];
    float clusters_y[k];

    for (int i = 0; i < k; ++i) { // Reset samples_size field in all clusters
        sample_sizes[i] = 0;
        clusters_x[i] = 0;
        clusters_y[i] = 0;
    } // Complexity: K

    float *gpu_samples_x, *gpu_samples_y;
    float *gpu_clusters_x, *gpu_clusters_y;
    int *new_closest;
    int samples_bytes = n * sizeof(float);
    int cluster_bytes = k * sizeof(float);
    int out_bytes = n * sizeof(int);

    cudaMalloc((void**) &gpu_samples_x, samples_bytes);
    cudaMalloc((void**) &gpu_samples_y, samples_bytes);
    cudaMalloc((void**) &gpu_clusters_x, cluster_bytes);
    cudaMalloc((void**) &gpu_clusters_y, cluster_bytes);
    cudaMalloc((void**) &new_closest, out_bytes);

    cudaMemcpy(gpu_samples_x, samples->x, samples_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_samples_y, samples->y, samples_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_clusters_x, clusters->x, cluster_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_clusters_y, clusters->y, cluster_bytes, cudaMemcpyHostToDevice);
    
    int num_blocks = n / 1000;
    
    calc_closest <<< 1000, num_blocks >>> (gpu_samples_x, gpu_samples_y, n, gpu_clusters_x, gpu_clusters_y, k, new_closest);

    cudaMemcpy(samples->cluster, new_closest, out_bytes, cudaMemcpyDeviceToHost);

//#pragma omp parallel for reduction(+:sample_sizes, clusters_x, clusters_y) schedule(static)
    for (int i = 0; i < n; i++) { // Complexity: N
/*

        if (samples->cluster[i] != closest) {
            samples->cluster[i] = closest;
            cluster_changed = 1;
        }
*/       
        int closest = samples->cluster[i];
        sample_sizes[closest]++;
        clusters_x[closest] += samples->x[i];
        clusters_y[closest] += samples->y[i];
    }

    for (int i = 0; i < k; i++) {
        clusters->samples_size[i] = sample_sizes[i];

        // Computing the centroids, assigning a new position for each cluster
        clusters->x[i] = clusters_x[i] / sample_sizes[i];
        clusters->y[i] = clusters_y[i] / sample_sizes[i];
    }

    return ++cluster_changed;
}