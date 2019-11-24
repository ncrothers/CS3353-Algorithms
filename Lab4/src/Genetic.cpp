#include "Genetic.h"

#include <iostream>
#include <random>
#include <ctime>

Genetic::Genetic() {

}

void Genetic::startAlgo(int _start, int _N, int _populationSize, Crossover coType, Mutation mutType) {
  start = _start;
  N = _N;
  populationSize = _populationSize;
  crossoverType = coType;
  mutationType = mutType;

  int** population = new int*[populationSize];
  generatePopulation(population);

  for (int count = 0; count < stopAmount; count++) {
    
  }
}

void Genetic::generatePopulation(int** population) {
  std::srand(time(0));
  for (int i = 0; i < populationSize; i++) {
    // Stores which nodes have been used for the current gene
    int used = 1 << (start - 1);
    population[i] = new int[N];
    // Sets first node to the start node
    population[i][0] = start - 1;
    
    int index = 1;
    // While not all nodes have been added to the current gene
    while (used != (1 << N) - 1) {
      // Current randomly generated node
      int cur = std::rand() % N;

      if (used & (1 << cur))
        continue;

      population[i][index] = cur;
      used ^= 1 << cur;
      index++;
    }
  }

  for (int j = 0; j < 10; j++) {
	  for (int i = 0; i < N; i++) {
		  std::cout << population[j][i] << (i == N - 1 ? "\n" : ", ");
	  }
  }
}

std::string Genetic::getTypeName() {
  std::string algoName = "Genetic Algorithm";
  std::string crossoverName;
  std::string mutationName;
  switch (crossoverType) {
    case Genetic::Crossover::PARTIALLY_MAPPED:
    crossoverName = "Partially Mapped Crossover (PMX)";
    break;
    case Genetic::Crossover::ORDER:
    crossoverName = "Order Crossover (OX)";
    break;
  }

  switch (mutationType) {
    case Genetic::Mutation::INVERSION:
    mutationName = "Inversion Mutation";
    break;
    case Genetic::Mutation::SWAP:
    mutationName = "Swap Mutation";
    break;
  }

  return algoName + '\n' + crossoverName + '\n' + mutationName;
}

