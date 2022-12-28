#ifndef UTILS
#define UTILS

/* ------------------------------------------------ Type Definitions ------------------------------------------------ */

struct samples {
    float *x;
    float *y;
    int *cluster;
};

struct clusters {
    float *x;
    float *y;
    int *samples_size; // Number of samples associated with this cluster
};

typedef struct samples Samples;

typedef Samples *SArray;

typedef struct clusters Clusters;

typedef Clusters *CArray;

/* --------------------------------------------- Functions declarations --------------------------------------------- */

SArray init_samples(int n);

CArray init_clusters(SArray samples, int k);

int compute_samples(SArray samples, int n, CArray clusters, int k);

#endif