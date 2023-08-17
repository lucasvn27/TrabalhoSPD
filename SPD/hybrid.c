#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
#include <omp.h>

double dtw(double *X, double *Y, int n, int m, int num_threads) {
    double *dist = (double *)malloc((n+1) * (m+1) * sizeof(double));// allocate memory for 1D array

    dist[0] = 0;
    // preencher a 1 linha
    double soma = 0;
    double soma2 = 0;
    for (size_t j = 1; j <= n; j++) {
        dist[j] = abs(X[j-1] - Y[0]) + soma;
        soma += abs(X[j-1] - Y[0]);
    }

    // preencher a 1 coluna    
    for (size_t i = 1; i <= m; i++) {
        dist[i * (n+1)] = abs(X[0] - Y[i-1]) + soma2;
        soma2 += abs(X[0] - Y[i-1]);
    }
   
    // fazer o resto
    #pragma omp parallel num_threads(num_threads)
    {
               for (size_t i = 1; i <= m; i++) {
            for (size_t j = 1; j <= n; j++) {
                double custo = abs(X[j-1] - Y[i-1]);
                int index = i * (n+1) + j;
                dist[index] = custo + fmin(dist[index-1], fmin(dist[index-(n+1)], dist[index-(n+2)]));
            }
        }
    }
    
    double smallestDist = dist[(m+1)*(n+1)-1];

    free(dist);
    return smallestDist;
}

int main(int argc, char *argv[]) {

    int my_rank, num_procs, root_process = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    if(argc < 4){
        if (my_rank == root_process) {
            printf("Usage: %s x_file y_file output_file num_threads\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    FILE *x, *y, *output;;  // ponteiro para o arquivo
    double *X = NULL, *Y = NULL;  // array para armazenar os nÃƒÂºmeros lidos
    int Len1 = 0;
    int Len2 = 0;

    if (my_rank == root_process) {
        // abrir o arquivo x_file
        x = fopen(argv[1], "r");
        if (x == NULL) {
            printf("Error: could not open file %s\n", argv[1]);
            MPI_Finalize();
            return 1;
        }
        // abrir o arquivo y_file
        y = fopen(argv[2], "r");
        if (y == NULL) {
            printf("Error: could not open file %s\n", argv[2]);
            MPI_Finalize();
            return 1;
        }
        // abrir o arquivo output_file
        output = fopen(argv[3], "w");
        if (output == NULL) {
            printf("Error: could not open file %s\n", argv[3]);
            MPI_Finalize();
            return 1;
        }

        // ler a primeira linha de x_file
        
         double num;
    while (fscanf(x, "%lf", &num) == 1) {
        Len1++;
        X = (double *)realloc(X, Len1 * sizeof(double)); // dynamically allocate memory
        X[Len1-1] = num;
    }

    while (fscanf(y, "%lf", &num) == 1) {
        Len2++;
        Y = (double *)realloc(Y, Len2 * sizeof(double)); // dynamically allocate memory
        Y[Len2-1] = num;
    }

    fclose(x);
    fclose(y);

}
      
    MPI_Bcast(&Len1, 1, MPI_INT, root_process, MPI_COMM_WORLD);
    MPI_Bcast(&Len2, 1, MPI_INT, root_process, MPI_COMM_WORLD);

    if (my_rank != 0) {
        X = (double *)malloc(Len1 * sizeof(double));
        Y = (double *)malloc(Len2 * sizeof(double));
    }

    MPI_Bcast(X, Len1, MPI_DOUBLE, root_process, MPI_COMM_WORLD);
    MPI_Bcast(Y, Len2, MPI_DOUBLE, root_process, MPI_COMM_WORLD);
    int num_threads = atoi(argv[4]);

    clock_t start_time, end_time;
    double total_time = 0.0;
    start_time = clock();
    double distance = dtw(X, Y, Len1, Len2, num_threads);
    end_time = clock();
    total_time += ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

       
    if(my_rank == root_process){
        printf("DTW distance: %lf\n", distance);
        printf("Tempo total de execucaoo: %lf segundos\n", total_time);
        fclose(output);
    }


    MPI_Finalize();
    return 0;
}