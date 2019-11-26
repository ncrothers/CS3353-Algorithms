
// This file contains all of the selection, crossover, and mutation methods used by
// the Genetic algorithm class

#ifndef GENETICOPERATORS_H
#define GENETICOPERATORS_H

#include <vector>

class GeneticOperators {
public:
	enum class Selection {
		ROULETTE = 0,
		ELITISM,
		LAST
	};

	enum class Crossover {
		PARTIALLY_MAPPED = 0,
		ORDER,
		LAST
	};

	enum class Mutation {
		SWAP = 0,
		INVERSION,
		LAST
	};

	static void configure(int _populationSize, int _N);

	static void select(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2, Selection op);
	static void crossover(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2, Crossover op);
	static void mutate(std::vector<int>& gene, float mutationRate, Mutation op);

private:
	static void selectRoulette(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2);
	static void selectElitism(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2);

	static void crossoverPartiallyMapped(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2);
	static void crossoverOrder(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2);

	static void mutateSwap(std::vector<int>& gene, float mutationRate);
	static void mutateInvert(std::vector<int>& gene, float mutationRate);

	static int N;
	static int populationSize;
};

#endif