#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

    if(argc  < 3){
        printf("Usage: %s x_file y_file output_file\n", argv[0]);
        return 1;
    }

    FILE *fp1, *fp2, *output;  // ponteiro para o arquivo
    double *num1 = NULL, *num2 = NULL;  // array para armazenar os números lidos
    int len1 = 0;
    int len2 = 0;

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");
    output = fopen(argv[3], "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    } 

    // lê o arquivo e armazena os números no array
    double size;
    while(fscanf(fp1, "%lf", &size) == 1){
        len1++;
        num1 = (double *)realloc(num1, len1 * sizeof(double)); //dynamically allocate memory
        num1[len1-1] = size;
    }

    while(fscanf(fp2, "%lf", &size) == 1){
        len2++;
        num2 = (double *)realloc(num2, len2 * sizeof(double)); //dynamically allocate memory
        num2[len2-1] = size;
    }

    fclose(fp1);
    fclose(fp2); // fecha o arquivo

    fprintf(output, "Distância mínima usando DTW: %lf\n", dtw(num1,num2,len1,len2));

    //Libertar memória
    free(num1);
    free(num2);
    fclose(output);

    return 0;
}
