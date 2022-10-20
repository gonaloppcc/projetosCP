#ifndef UTILS
#define UTILS

/* ------------------------------------------------ Type Definitions ------------------------------------------------ */

struct point {
    float x;
    float y;
    int cluster;
};

typedef struct point *Point;

typedef Point *PArray;


/* --------------------------------------------- Functions declarations --------------------------------------------- */

PArray init_vector(int n);

PArray init_clusters(int k);

void assign_clusters(PArray vector, int n, PArray clusters, int k);

void compute_centroids();

#endif