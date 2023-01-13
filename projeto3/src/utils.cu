#include "../include/utils.h"
#include "../include/cp-utils.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cuda.h>

#define SEED 10
#define BLOCK_SIZE 1024

using namespace std;

float *gpu_samples_x, *gpu_samples_y;
float *gpu_clusters_x, *gpu_clusters_y;
int *closest_cluster;
int *changed_gpu;

int samples_bytes; // = n * sizeof(float);
int cluster_bytes; //= k * sizeof(float);
int closest_cluster_bytes; // = n * sizeof(int);
int changed_gpu_bytes; // = BLOCK_SIZE * sizeof(int);


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
        int *closest_array,
        int *changed
) {
    int gid = blockIdx.x * blockDim.x + threadIdx.x;
    __shared__ int sharedArray[BLOCK_SIZE];

    if (gid >= n)
        return;

    int closest = -1;
    float shortest_dist = __FLT_MAX__;
    for (int i = 0; i < k; i++) {
        float dist = distance(clusters_x[i], clusters_y[i], samples_x[gid], samples_y[gid]);
        if (dist < shortest_dist) {
            shortest_dist = dist;
            closest = i;
        }
    }
    sharedArray[threadIdx.x] = closest_array[gid] != closest;
    closest_array[gid] = closest;
    __syncthreads();
    if (threadIdx.x != 0)
        return;

    for (int i = 0; i < blockDim.x; i++) {
        changed[blockIdx.x] = 0;
        changed[blockIdx.x] += sharedArray[i];
    }
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

    cluster_bytes = k * sizeof(float);
    changed_gpu_bytes = BLOCK_SIZE * sizeof(int);

    cudaMalloc((void **) &gpu_clusters_x, cluster_bytes);
    cudaMalloc((void **) &gpu_clusters_y, cluster_bytes);
    cudaMalloc((void **) &changed_gpu, changed_gpu_bytes);

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

    samples_bytes = n * sizeof(float);
    closest_cluster_bytes = n * sizeof(int);

    cudaMalloc((void **) &gpu_samples_x, samples_bytes);
    cudaMalloc((void **) &gpu_samples_y, samples_bytes);
    cudaMalloc((void **) &closest_cluster, closest_cluster_bytes);

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

    int changed_cpu[BLOCK_SIZE];

    int num_blocks = n / BLOCK_SIZE;

    startKernelTime();

    cudaMemcpy(gpu_samples_x, samples->x, samples_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_samples_y, samples->y, samples_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_clusters_x, clusters->x, cluster_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(gpu_clusters_y, clusters->y, cluster_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(closest_cluster, samples->cluster, closest_cluster_bytes, cudaMemcpyHostToDevice);


    calc_closest <<< num_blocks, BLOCK_SIZE >>>(gpu_samples_x, gpu_samples_y, n, gpu_clusters_x, gpu_clusters_y, k,
                                                closest_cluster, changed_gpu);

    cudaDeviceSynchronize();
    cudaMemcpy(samples->cluster, closest_cluster, closest_cluster_bytes, cudaMemcpyDeviceToHost);
    cudaMemcpy(changed_cpu, changed_gpu, changed_gpu_bytes, cudaMemcpyDeviceToHost);

    stopKernelTime();

    for (int i = 0; i < BLOCK_SIZE; i++) {
        cluster_changed += changed_cpu[i];
    }

    for (int i = 0; i < n; i++) { // Complexity: N
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

    return cluster_changed > 0;
}