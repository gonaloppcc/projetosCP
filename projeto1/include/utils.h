#ifndef UTILS
#define UTILS

/* ------------------------------------------------ Type Definitions ------------------------------------------------ */

struct point {
    float x;
    float y;
};

typedef struct point *Point;

typedef Point *PArray;


/* --------------------------------------------- Functions declarations --------------------------------------------- */

void init_vector();

PArray init_clusters(int k);

void assign_clusters();

void compute_centroids(PArray clusters, int numberOfClusters, PArray *clustersPoints, int *clustersPointsSizes);

#endif