/***************************************************
* FILE: omp_hello.c
* DESCRIPTION:
*   OpenMP Example - Hello World - C/C++ Version
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 04/06/05
* Midificado MM
***************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  int nthreads, tid;

  #pragma omp parallel private(nthreads, tid)
  {
    tid = omp_get_thread_num();
    printf("Hello World from thread = %d\n", tid);
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      printf("Number of threads = %d\n", nthreads);

    }
  printf("All done!\n");
  }  /* All threads join master thread and disband */
}
