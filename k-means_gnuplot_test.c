#include <stdio.h>
#include "k-means.h"

int main() {
	int rows = 10;
	int cols = 2;
	int k = 3;
	int *clusters;
	int cmd_number = 2;
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
	clusters = kmeans_step();
	//GNUPlot Commands.
	FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
	FILE *data_txt = fopen("data.txt", "w");
	char *gnuplot_commands[] = {"set title \"k-mneas\"", "plot 'data.txt' using 1:2:3 with points pointtype 5 palette"};
    for (int row = 0; row < rows; row++) {
    	fprintf(data_txt, "%lf %lf %d \n", data[row][0], data[row][1], clusters[row]);
    }
    for (int cmd = 0; cmd < cmd_number; cmd++) {
    	fprintf(gnuplot_pipe, "%s \n", gnuplot_commands[cmd]);
    }
	return 0;
}
