#ifndef UTILS
#define UTILS

/* ------------------------------------------------ Type Definitions ------------------------------------------------ */

struct point {
    float x;
    float y;
    int cluster;
};

struct cluster {
    float x;
    float y;

    int samples_size; // Number of samples associated with this cluster
};

typedef struct point *Point;

typedef Point *PArray;

typedef struct cluster *Cluster;

typedef Cluster *CArray;

/* --------------------------------------------- Functions declarations --------------------------------------------- */

PArray init_samples(int n);

CArray init_clusters(PArray samples, int k);

void assign_clusters(PArray samples, int n, CArray clusters, int k);

void compute_centroids(PArray samples, int n, CArray clusters, int k);

#endif