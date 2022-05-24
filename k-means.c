#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include "k-means.h"

static int data_rows;				// Quantidade de linhas em data_array.
static int data_cols;				// Quantidade de colunas em data_array.
static int data_k;				// Quantidade de agrupamentos.
static float *data_array;			// Pontos a serem agrupados.
static float **centroids_array;			// Centroides.
static int *clusters_array;			// Guarda o indice de cluster para cada ponto em data_array.
static int first_step = 1;

void set_kmeans(float *data, int rows, int cols, int k) {
	// Inicializa variaveis globais.
	data_array = data;
	data_rows = rows;
	data_cols = cols;
	data_k = k;
	centroids_array = (float **) malloc(sizeof(float *) * data_k);
	for (int x = 0; x < data_k; x++) {
		centroids_array[x] = (float *) malloc(sizeof(float) * data_cols);
		for (int y = 0; y < data_cols; y++) {
			centroids_array[x][y] = 0.0;
		}
	}
	// Escolher alguns pontos como os centroides inicias.
	set_rnd_centroids();
	clusters_array = (int *) malloc(sizeof(int) * data_rows);
	for (int x = 0; x < data_k; x++) {
		clusters_array[x] = 0;
	}
}

int *kmeans_step() {
	float sum;
	double euclidian;
	float point[data_cols];

	if (first_step == 0){
		// Recalcula os centroides.
		// Não é executado no primeiro passo, pois os centroides iniciais
		// escolhidos aleatoriamente.
		for (int cluster = 0; cluster < data_k; cluster++) {
			for (int col = 0; col < data_cols; col++) {
				// Calcula a media das coordenadas dos clusters correntes
				// para obter os novos centroides.
				float sum = 0.0;
				float number = 0.0;
				for (int row = 0; row < data_rows; row++) {
					if (clusters_array[row] == cluster) {
						sum = sum + *((data_array + row * data_cols) + col);
						number += 1;
					}
				}
				float average = sum / number;
				centroids_array[cluster][col] = average;
			}
		}
	}
	// Calcula as distancias dos pontos para cada centroide.
	for (int row = 0; row < data_rows; row++) {
		for (int col = 0; col < data_cols; col++) {
			//Ponto para mediar a distancia.
			point[col] = *((data_array + row * data_cols) + col);
		}
		euclidian = 1000;
		// calcula a distancia do ponto ate cada um dos centroides.
		for (int k = 0; k < data_k; k++) {
			sum = 0;
			for (int col = 0; col < data_cols; col++) {
				sum = sum + (point[col] - centroids_array[k][col]) * (point[col] - centroids_array[k][col]);
			}
			if (sqrt(sum) < euclidian){
				euclidian = sqrt(sum);
				// O ponto referente a 'row' é colocado no cluster 'k'.
				clusters_array[row] = k;
			}
		}
	}
	first_step = 0;
	return clusters_array;
}

int *kmeans() {
	int *clusters_list;
	int clusters_list_copy[data_rows];
	int update;
	for (int row = 0; row < data_rows; row++) {
		clusters_list_copy[row] = 0.0;
	}

	do {
		update = 0;
		clusters_list = kmeans_step();
		for (int row = 0; row < data_rows; row++) {
			if (clusters_list_copy[row] != clusters_list[row]) {
				update = 1;
			}
			clusters_list_copy[row] = clusters_list[row];
		}
	} while (update != 0);
	return clusters_array;
}

void set_rnd_centroids() {
	// Escolhe alguns pontos de data_array para serem os centróides iniciais.
	int rnd_x;
	int repeated_flag;
	int loop = 0;
	srand(time(0));
	do {
		rnd_x = rand() % data_rows;
		repeated_flag = 0;
		for (int i = 0; i < data_k; i++) {
			for (int y = 0; y < data_cols; y++) {
				// Percorre centroids_array para verificar se ponto escolhido
				// já foi escolhido anteriormente.
				if (centroids_array[i][y] == *((data_array + rnd_x * data_cols) + y)) {
					repeated_flag += 1;
				}
			}
		}
		// Se repeated_flag = 2 significa que as duas coordenadas do novo ponto
		// escolhido de data_array já estão em centroids_array.
		if (repeated_flag != 2) {
			for (int y = 0; y < data_cols; y++) {
				// Coloca o ponto escolhido em centroids_array.
				centroids_array[loop][y] = *((data_array + rnd_x * data_cols) + y);
			}
			loop += 1;
		}
	} while (loop < data_k);
}
