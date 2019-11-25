#include "Genetic.h"

#include <iostream>
#include <random>
#include <ctime>

Genetic::Genetic() {

}

void Genetic::configure(int selType, int coType, int mutType, int _populationSize) {

	populationSize = _populationSize;
	selectionType = static_cast<GeneticOperators::Selection>(selType);
	crossoverType = static_cast<GeneticOperators::Crossover>(coType);
	mutationType = static_cast<GeneticOperators::Mutation>(mutType);
}

void Genetic::startAlgo(int _start, int _N) {

	start = _start;
	N = _N;

	int** population = new int* [populationSize];
	float* popFitness = new float[N];
	generatePopulation(population);

	for (int count = 0; count < stopAmount; count++) {
		calculateFitness(population, popFitness);
	}

	for (int i = 0; i < populationSize; i++) {
		delete[] population[i];
	}

	delete[] population;
	delete[] popFitness;
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

void Genetic::calculateFitness(int** population, float* fitness) {
	for (int i = 0; i < populationSize; i++) {
		float geneFitness = 0;
		for (int j = 0; j < N - 1; j++) {
			geneFitness += distance[population[i][j]][population[i][j + 1]];
		}
		fitness[i] = geneFitness;
	}
}

void Genetic::selection(int** population, int* p1, int* p2) {
	GeneticOperators::select(population, p1, p2, selectionType);
}

void Genetic::crossover(int* p1, int* p2, int* c1, int* c2) {
	GeneticOperators::crossover(p1, p2, c1, c2, crossoverType);
}

void Genetic::mutate(int* gene) {
	GeneticOperators::mutate(gene, mutationType);
}

std::string Genetic::getTypeName() {
	std::string algoName = "Genetic Algorithm";
	std::string crossoverName;
	std::string mutationName;
	switch (crossoverType) {
	case GeneticOperators::Crossover::PARTIALLY_MAPPED:
		crossoverName = "Partially Mapped Crossover (PMX)";
		break;
	case GeneticOperators::Crossover::ORDER:
		crossoverName = "Order Crossover (OX)";
		break;
	}

	switch (mutationType) {
	case GeneticOperators::Mutation::INVERSION:
		mutationName = "Inversion Mutation";
		break;
	case GeneticOperators::Mutation::SWAP:
		mutationName = "Swap Mutation";
		break;
	}

	return algoName + '\n' + crossoverName + '\n' + mutationName;
}

