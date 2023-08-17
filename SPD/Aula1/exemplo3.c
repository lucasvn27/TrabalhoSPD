#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/* SOMATÓRIO
Somatório de um intervalo
Teste os seus conmhecimentos, conclua o exemplo
*/
int sum_interval(int min, int max)
{
    int result = 0;
    for (int i = min; i <= max; i++)
	     result += i;
    return result;
}

int somatorio(double n)
{
// Cria uma região paralela que será percorrida por
// N threads
#pragma omp parallel num_threads(N)
    {				// Inicializa a variável id, que representa o número do thread
	int id = omp_get_thread_num();
// Inicializa o mínimo e o máximo que o thread vai contar
	int min = id * n / N + 1;
	int max = (id + 1) * n / N;
	printf("[%d] min = %d ; max = %d\n", id, min, max);
// Como a obtenção do resultado é uma "mini" secção crítica,
// foi declarada uma zona atómica, onde o resultado irá ser incrementado
	int sum = sum_interval(min, max);
#pragma omp atomic
	result = result + sum;
    }
    return result;

}

int main(int argc, char **argv)
{
    int n = 0;
    printf("Valor: ");
    scanf("%d", &n);
    printf(“%d \n, somatorio(n));
    return 0;
}
