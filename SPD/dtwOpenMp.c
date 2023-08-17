#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MAX_SIZE 1000
int i=0;
int j=0;


double total_time(struct timeval start_time, struct timeval end_time){
    double start_sec = (double)start_time.tv_sec*1000000.0 + (double)start_time.tv_usec;
    double end_sec = (double)end_time.tv_sec*1000000.0 + (double)end_time.tv_usec;
    return (end_sec - start_sec) / 1000000.0;
}


double dtw(double *X, double *Y, int n, int m, int num_threads){
    double *dist = (double *)malloc((n+1) * sizeof(double)); //allocate memory for 1D array

    //Inicializar a matriz de distancias com os valores dos arrays X e Y
    dist[0] = 0;
    for(int j = 1; j <= n; j++) {
        dist[j] = X[j-1] + dist[j-1];
    }

    // Calcular as distÃ¢ncias
    #pragma omp parallel for num_threads(num_threads)
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
    //Libertar memoria
    free(dist);
    return smallestDist;
}

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Usage: %s x_file y_file output_file num_threads\n", argv[0]);
        return 1;
    }

    FILE *fp1, *fp2, *output;  
    double *num1 = NULL, *num2 = NULL;  
    int len1 = 0;
    int len2 = 0;

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");
    output = fopen(argv[3], "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
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

    int num_threads = atoi(argv[4]);

    struct timeval i_current_time;
    struct timeval end_current_time;

    double cpu_time_used;
    gettimeofday(&i_current_time, NULL);
    fprintf(output, "Distancia maxima usando DTW: %lf\n", dtw(num1,num2,len1,len2,num_threads));
    gettimeofday(&end_current_time,NULL);
    cpu_time_used = total_time(i_current_time, end_current_time);
    fprintf(output, "Execution time: %lf seconds.\n", cpu_time_used);
    printf("Execution time: %lf seconds.\n", cpu_time_used);
    printf("Numero de threads: %d .\n", num_threads);

    free(num1);
    free(num2);
    fclose(output);

    return 0;
}