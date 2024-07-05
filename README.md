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

Cada diretório contém o código fonte e instruções específicas para compilar e executar os projetos em diferentes ambientes. 

Para mais detalhes sobre cada projeto, por favor, consulte os README individuais dentro de cada diretório.
