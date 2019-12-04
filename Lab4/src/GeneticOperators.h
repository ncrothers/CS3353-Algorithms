
// This file contains all of the selection, crossover, and mutation methods used by
// the Genetic algorithm class

#ifndef GENETICOPERATORS_H
#define GENETICOPERATORS_H

#include <vector>
#include <random>

class GeneticOperators {
public:
	enum Selection {
		ROULETTE = 0,
		ELITISM,
		TOURNAMENT,
		LASTSEL
	};

	enum Crossover {
		PARTIALLY_MAPPED = 0,
		ORDER,
		LASTCRO
	};

	enum Mutation {
		SWAP = 0,
		INVERSION,
		LASTMUT
	};

	static void configure(int _populationSize, int _N, std::vector<std::vector<float>>& _distances);
	static float getRandomFloat(float lowerBound, float upperBound);
	static int getRandomInt(int lowerBound, int upperBound);

	static std::string getSelectionName(int type);
	static std::string getCrossoverName(int type);
	static std::string getMutationName(int type);

	static void select(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2, Selection op);
	static void crossover(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2, float crossoverRate, Crossover op);
	static void mutate(std::vector<int>& gene, float mutationRate, Mutation op);

private:
	static void selectRoulette(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2);
	static void selectElitism(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2);
	static void selectTournament(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2);

	static void crossoverPartiallyMapped(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& child);
	static void crossoverOrder(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& child);

	static void mutateSwap(std::vector<int>& gene);
	static void mutateInvert(std::vector<int>& gene);

	static int keepValue(std::vector<int>& gene);

	static int N;
	static int populationSize;
	static std::default_random_engine generator;
	static std::vector<std::vector<float>>* distances;
};

#endif