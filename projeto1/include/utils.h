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

    int points_size;
};

typedef struct point *Point;

typedef Point *PArray;

typedef struct cluster *Cluster;

typedef Cluster *CArray;

/* --------------------------------------------- Functions declarations --------------------------------------------- */

PArray init_vector(int n);

CArray init_clusters(int k);

void assign_clusters(PArray points, int n, CArray clusters, int k);

void compute_centroids(PArray points, int n, CArray clusters, int k);

#endif