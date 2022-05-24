//#include <assert.h>
#include <stdio.h>
#include "k-means.h"

//static void free_pointer(void **pointer) {
//	assert(pointer);
//	free(*pointer);
//	*pointer = NULL;
//}

int main() {
	int rows = 10;
	int cols = 2;
	int k = 3;
	int *clusters;
	float data[10][2] = {{0.90,2.90},
						{0.00,1.00},
						{1.50,1.50},
						{1.50,0.00},
						{2.90,1.70},
						{2.00,1.90},
						{3.00,3.00},
						{3.00,9.00},
						{6.00,2.60},
						{2.10,2.80}};
	set_kmeans((float *)data, rows, cols, k);
	clusters = kmeans();
	for (int row = 0; row < rows; row++) {
		printf("point %d -> %d\n", row, clusters[row]);
	}
	kmeans_free_pointers();
	return 0;
}
