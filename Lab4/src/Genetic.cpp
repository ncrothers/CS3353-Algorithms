#include "Genetic.h"

#include <iostream>
#include <random>
#include <ctime>
#include <vector>

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
	GeneticOperators::configure(populationSize, N);

	std::vector<std::vector<int>> population(populationSize);
	std::vector<float> popFitness(populationSize);
	// Pointers for the selected parents used for crossover each iteration
	std::vector<int> parent1(N);
	std::vector<int> parent2(N);

	// Generates initial population
	generatePopulation(population);

	for (int count = 0; count < stopAmount; count++) {
		calculateFitness(population, popFitness);
		updateBest(population, popFitness);

		selection(population, popFitness, parent1, parent2);

		// New children memory allocated
		std::vector<int> child1(N);
		std::vector<int> child2(N);

		crossover(parent1, parent2, child1, child2);
		mutate(child1);
		mutate(child2);
		insert(population, popFitness, child1, child2);
	}
	int i = 0;
}

void Genetic::updateBest(std::vector<std::vector<int>>& population, std::vector<float>& popFitness) {
	float best = popFitness[0];
	int bestIndex = 0;

	for (int i = 1; i < populationSize; i++) {
		if (popFitness[i] < best) {
			best = popFitness[i];
			bestIndex = i;
		}
	}
	if (best < bestTourDist) {
		setBestTour(population[bestIndex]);
		bestTourDist = best;
	}
}

// Generates a random population to begin the algorithm
void Genetic::generatePopulation(std::vector<std::vector<int>>& population) {

	std::srand(time(0));

	for (int i = 0; i < populationSize; i++) {
		// Stores which nodes have been used for the current gene
		int used = 1 << (start - 1);
		population[i] = std::vector<int>(N);
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

	for (int j = 0; j < populationSize; j++) {
		for (int i = 0; i < N; i++) {
			std::cout << population[j][i] << (i == N - 1 ? "\n" : ", ");
		}
	}
}

// Calculates the fitness of the entire population
void Genetic::calculateFitness(std::vector<std::vector<int>>& population, std::vector<float>& fitness) {
	for (int i = 0; i < populationSize; i++) {
		float geneFitness = 0;
		for (int j = 0; j < N - 1; j++) {
			geneFitness += distance[population[i][j]][population[i][j + 1]];
		}
		geneFitness += distance[population[i][N - 1]][start - 1];
		fitness[i] = geneFitness;
	}
}

void Genetic::selection(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2) {
	GeneticOperators::select(population, popFitness, p1, p2, selectionType);
}

void Genetic::crossover(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2) {
	GeneticOperators::crossover(p1, p2, c1, c2, crossoverType);
}

void Genetic::mutate(std::vector<int>& gene) {
	GeneticOperators::mutate(gene, mutationRate, mutationType);
}

void Genetic::insert(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& c1, std::vector<int>& c2) {
	float worst, secondWorst;
	worst = secondWorst = 0;
	int worstIndex, secondWorstIndex;
	worstIndex = secondWorstIndex = 0;

	for (int i = 0; i < populationSize; i++) {
		if (popFitness[i] > worst) {
			worst = popFitness[i];
			worstIndex = i;
		}
		else if (popFitness[i] > secondWorst) {
			secondWorst = popFitness[i];
			secondWorstIndex = i;
		}
	}

	// Adds children into population
	population[worstIndex] = c1;
	population[secondWorstIndex] = c2;
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

