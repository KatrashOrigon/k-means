#ifndef K_MEANS_H_
#define K_MEANS_H_

typedef struct Point {
	float x;
	float y;
} point;

void set_kmeans(float *data, int rows, int cols, int k);
int *kmeans_step();
int *kmeans();
void set_rnd_centroids();
float euclidian(point *p1, point *p2);

#endif
