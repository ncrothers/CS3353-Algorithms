#include "GeneticOperators.h"

void GeneticOperators::select(int** population, int* p1, int* p2, Selection op) {
	switch (op) {
	case Selection::ROULETTE:
		selectRoulette(population, p1, p2);
		break;
	case Selection::ELITISM:
		selectElitism(population, p1, p2);
		break;
	}
}

void GeneticOperators::crossover(int* p1, int* p2, int* c1, int* c2, Crossover op) {
	switch (op) {
	case Crossover::PARTIALLY_MAPPED:
		crossoverPartiallyMapped(p1, p2, c1, c2);
		break;
	case Crossover::ORDER:
		crossoverOrder(p1, p2, c1, c2);
		break;
	}
}

void GeneticOperators::mutate(int* gene, Mutation op) {
	switch (op) {
	case Mutation::SWAP:
		mutateSwap(gene);
		break;
	case Mutation::INVERSION:
		mutateInvert(gene);
		break;
	}
}

// Selection Functions

void GeneticOperators::selectRoulette(int** population, int* p1, int* p2) {

}

void GeneticOperators::selectElitism(int** population, int* p1, int* p2) {

}

// Crossover Functions

void GeneticOperators::crossoverPartiallyMapped(int* p1, int* p2, int* c1, int* c2) {

}

void GeneticOperators::crossoverOrder(int* p1, int* p2, int* c1, int* c2) {

}

// Mutation Functions

void GeneticOperators::mutateSwap(int* gene) {

}

void GeneticOperators::mutateInvert(int* gene) {

}