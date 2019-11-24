
#ifndef GENETIC_H
#define GENETIC_H

#include "TSPAlgorithm.h"

class Genetic : public TSPAlgorithm {
public:

  Genetic();

  void startAlgo(int _start, int _N, int _populationSize, Crossover coType, Mutation mutType);
  void loadConfig();
  std::string getTypeName();

private:
  // Functions used by the genetic algorithm directly
  void generatePopulation(int** population);
  void selection();
  void crossover();
  void mutate();

  // Different crossover functions
  void crossoverPartialMap();
  void crossoverOrder();

  // Different mutate functions
  void mutateSwap();
  void mutateInvert();

  size_t stopAmount = 1000;
  size_t populationSize;
  float mutationRate;

  Mutation mutationType;
  Crossover crossoverType;
};

#endif