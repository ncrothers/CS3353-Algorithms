
// This file contains all of the selection, crossover, and mutation methods used by
// the Genetic algorithm class

#ifndef GENETICOPERATORS_H
#define GENETICOPERATORS_H

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

	static void select(int** population, int* p1, int* p2, Selection op);
	static void crossover(int* p1, int* p2, int* c1, int* c2, Crossover op);
	static void mutate(int* gene, Mutation op);

private:
	static void selectRoulette(int** population, int* p1, int* p2);
	static void selectElitism(int** population, int* p1, int* p2);

	static void crossoverPartiallyMapped(int* p1, int* p2, int* c1, int* c2);
	static void crossoverOrder(int* p1, int* p2, int* c1, int* c2);

	static void mutateSwap(int* gene);
	static void mutateInvert(int* gene);
};

#endif