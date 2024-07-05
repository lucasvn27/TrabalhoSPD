# Projetos de Sistemas Paralelos e Distribuídos

Este repositório contém projetos desenvolvidos no âmbito da cadeira de Sistemas Paralelos e Distribuídos da minha licenciatura em Engenharia Informática pela Universidade do Algarve. Os projetos foram focados na implementação do algoritmo DTW (Dynamic Time Warping) utilizando diferentes abordagens para paralelização.

## Descrição dos Projetos

- **DTW Sequencial:** Implementação do algoritmo DTW utilizando uma abordagem sequencial para comparação de séries temporais.

- **DTW com OpenMP:** Utilização da API OpenMP para paralelizar o algoritmo DTW, explorando threads para melhorar o desempenho em sistemas multiprocessador.

- **DTW com MPI:** Implementação do algoritmo DTW com o uso do MPI (Message Passing Interface) para distribuir o trabalho entre processos em um ambiente de computação distribuída.
  
- **DTW Híbrido (MPI + OpenMP):** Projeto que combina MPI e OpenMP para implementar o algoritmo DTW de forma híbrida, aproveitando tanto a distribuição entre processos quanto a paralelização em múltiplas threads.

## Tecnologias Utilizadas

- Linguagens: C/C++
- Ferramentas: OpenMP, MPI

## Como Utilizar

Dentro deste repositório, você encontrará os seguintes arquivos:

- **dtwSequencial.c:** Implementação do algoritmo DTW utilizando uma abordagem sequencial.
- **dtwOpenMp.c:** Implementação do algoritmo DTW utilizando OpenMP para paralelização.
- **mpi.c:** Implementação do algoritmo DTW utilizando MPI para computação distribuída.
- **hybrid.c:** Implementação do algoritmo DTW de forma híbrida, combinando MPI e OpenMP.

Além dos arquivos de código fonte, há também uma série de testes com números randômicos disponíveis para a realização de testes empíricos e avaliação de desempenho.
