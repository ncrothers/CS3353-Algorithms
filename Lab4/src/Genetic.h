
#ifndef GENETIC_H
#define GENETIC_H

#include "TSPAlgorithm.h"
#include "GeneticOperators.h"

class Genetic : public TSPAlgorithm {
public:

  Genetic();

  void startAlgo(int _start, int _N);
  void configure(int selectionType, int coType, int mutType, int _populationSize);
  std::string getTypeName();

private:
  // Functions used by the genetic algorithm directly
  void generatePopulation(int** population);
  void calculateFitness(int** population, float* fitness);
  void selection(int** population, int* p1, int* p2);
  void crossover(int* p1, int* p2, int* c1, int* c2);
  void mutate(int* gene);

  size_t stopAmount = 1000;
  size_t populationSize;
  float mutationRate;

  GeneticOperators::Selection selectionType;
  GeneticOperators::Mutation mutationType;
  GeneticOperators::Crossover crossoverType;
};

#endif