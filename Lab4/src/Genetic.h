
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
  void generatePopulation(std::vector<std::vector<int>>& population);
  bool calculateFitness(std::vector<std::vector<int>>& population, std::vector<float>& popDistances, std::vector<float>& fitness);
  void selection(std::vector<std::vector<int>>& population, 
	  std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2);

  void crossover(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2);
  void mutate(std::vector<int>& gene);
  void insert(std::vector<std::vector<int>>& population, 
	  std::vector<float>& popFitness, std::vector<int>& c1, std::vector<int>& c2);

  void updateBest(std::vector<std::vector<int>>& population, std::vector<float>& popFitness);

  size_t stopAmount = 1000;
  size_t populationSize;
  float mutationRate = 0.10;
  float crossoverRate = 0.8;

  GeneticOperators::Selection selectionType;
  GeneticOperators::Mutation mutationType;
  GeneticOperators::Crossover crossoverType;
};

#endif