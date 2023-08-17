#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>

#define MAX_SIZE 1000

double dtw(double *X, double *Y, int n, int m){
    double *dist = (double *)malloc((n+1) * sizeof(double)); //allocate memory for 1D array

    //Inicializar a matriz de distancias com os valores dos arrays X e Y
    dist[0] = 0;
    for(int j = 1; j <= n; j++) {
        dist[j] = X[j-1] + dist[j-1];
    }

    // Calcular as distâncias
    for(int i = 1; i <= m; i++) {
        double prevDist = dist[0];
        dist[0] = Y[i-1] + prevDist;
        for(int j = 1; j <= n; j++) {
            double cost = fabs(X[j-1] - Y[i-1]);
            double minDist = fmin(prevDist, fmin(dist[j], dist[j-1]));
            prevDist = dist[j];
            dist[j] = cost + minDist;
        }
    }

    double smallestDist = dist[n];
    //Libertar memória
    free(dist);
    return smallestDist;
}

int main(int argc, char *argv[]){
    int my_rank, num_procs, root_process = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if(argc < 3){
        if (my_rank == root_process) {
            printf("Usage: %s x_file y_file output_file\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    FILE *fp1, *fp2, *output;  // ponteiro para o arquivo
    double *num1 = NULL, *num2 = NULL;  // array para armazenar os números lidos
    int len1 = 0;
    int len2 = 0;

    if (my_rank == root_process) {
        fp1 = fopen(argv[1], "r");
        fp2 = fopen(argv[2], "r");
        output = fopen(argv[3], "w");

        if (fp1 == NULL || fp2 == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            MPI_Finalize();
            return 1;
        } 
        double size;
        while(fscanf(fp1, "%lf", &size) == 1){
            len1++;
            num1 = (double *)realloc(num1, len1 * sizeof(double));
            num1[len1-1] = size;
        }

        while(fscanf(fp2, "%lf", &size) == 1){
            len2++;
            num2 = (double *)realloc(num2, len2 * sizeof(double));
            num2[len2-1] = size;
        }

        fclose(fp1);
        fclose(fp2);
    }

    MPI_Bcast(&len1, 1, MPI_INT, root_process, MPI_COMM_WORLD);
    MPI_Bcast(&len2, 1, MPI_INT, root_process, MPI_COMM_WORLD);

    if (my_rank != root_process) {
        num1 = (double *)malloc(len1 * sizeof(double));
        num2 = (double *)malloc(len2 * sizeof(double));
    }

    MPI_Bcast(num1, len1, MPI_DOUBLE, root_process, MPI_COMM_WORLD);
    MPI_Bcast(num2, len2, MPI_DOUBLE, root_process, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();
    double result = dtw(num1, num2, len1, len2);
    double end_time = MPI_Wtime();

    if (my_rank == root_process) {
        fprintf(output, "Distancia minima usando DTW: %lf\n", result);
	    fprintf(output, "Tempo de execucao: %lf\n", end_time - start_time);
        fclose(output);
    }

    MPI_Finalize();

    return 0;
}
