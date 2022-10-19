#ifndef UTILS
#define UTILS

/* ------------------------------------------------ Type Definitions ------------------------------------------------ */

struct point {
    float x;
    float y;
};

typedef struct point *Point;

typedef Point *Array;


/* --------------------------------------------- Functions declarations --------------------------------------------- */

void init_vector();

Array init_clusters(int k);

void assign_clusters();

void compute_centroids();

#endif