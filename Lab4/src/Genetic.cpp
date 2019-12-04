#include "Genetic.h"

#include <iostream>
#include <ctime>
#include <vector>

Genetic::Genetic() {

}

void Genetic::configure(int selType, int coType, int mutType, int _populationSize) {

	populationSize = _populationSize;
	selectionType = static_cast<GeneticOperators::Selection>(selType);
	crossoverType = static_cast<GeneticOperators::Crossover>(coType);
	mutationType = static_cast<GeneticOperators::Mutation>(mutType);

	generator.seed(time(0));
}

void Genetic::startAlgo(int _start, int _N) {

	start = _start;
	N = _N;

	GeneticOperators::configure(populationSize, N, distance);

	std::vector<std::vector<int>> population(populationSize);
	std::vector<float> popFitness(populationSize);
	std::vector<float> popDistances(populationSize);
	// Pointers for the selected parents used for crossover each iteration
	std::vector<std::vector<int>> parents;
	int numParents = 4;

	int maxIterations = 500;

	for (int i = 0; i < numParents; i++)
		parents.push_back(std::vector<int>(N));

	// Generates initial population
	generatePopulation(population);

	float bestDistance = ceil(bestDistances[N] * 10) / 10;

	while (bestTourDist > bestDistance) {
		if (!calculateFitness(population, popDistances, popFitness)) {
			timeSinceNewBest = 0;
			return;
		}

		timeSinceNewBest++;

		updateBest(population, popDistances);

		for (int i = 0; i < numParents - 1; i += 2) {
			selection(population, popFitness, parents[i], parents[i+1]);
		}

		std::vector<std::vector<int>> children;
		for (int i = 0; i < numParents; i++)
			children.push_back(std::vector<int>(N));

		for (int i = 0; i < numParents - 1; i += 2) {
			crossover(parents[i], parents[i+1], children[i], children[i+1]);
			mutate(children[i]);
			mutate(children[i+1]);
			insert(population, popFitness, children[i], children[i+1]);
		}
	}
}

void Genetic::updateBest(std::vector<std::vector<int>>& population, std::vector<float>& popDistances) {
	float best = popDistances[0];
	int bestIndex = 0;

	for (int i = 1; i < populationSize; i++) {
		if (popDistances[i] < best) {
			best = popDistances[i];
			bestIndex = i;
		}
	}
	if (best < bestTourDist) {
		setBestTour(population[bestIndex]);
		bestTourDist = ceil(best * 10) / 10;
	}
}

// Generates a random population to begin the algorithm
void Genetic::generatePopulation(std::vector<std::vector<int>>& population) {

	std::uniform_int_distribution<int> distribution(0, N - 1);

	if (bestTour.size() > 0) {
		std::vector<int> next = bestTour;
		mutate(next);
		population[0] = bestTour;
		population[1] = next;
	}

	for (int i = bestTour.size() > 0 ? 2 : 0; i < populationSize; i++) {
		// Stores which nodes have been used for the current gene
		int used = 1 << (start - 1);
		population[i] = std::vector<int>(N);
		// Sets first node to the start node
		population[i][0] = start - 1;

		int index = 1;
		// While not all nodes have been added to the current gene
		while (used != (1 << N) - 1) {
			// Current randomly generated node
			int cur = distribution(generator);

			if (used & (1 << cur))
				continue;

			population[i][index] = cur;
			used ^= 1 << cur;
			index++;
		}
	}
}

// Calculates the fitness of the entire population
bool Genetic::calculateFitness(std::vector<std::vector<int>>& population, std::vector<float>& popDistances, std::vector<float>& fitness) {
	for (int i = 0; i < population.size(); i++) {
		float geneDistance = 0;
		for (int j = 0; j < N - 1; j++) {
			geneDistance += distance[population[i][j]][population[i][j + 1]];
		}
		geneDistance += distance[population[i][N - 1]][start - 1];
		popDistances[i] = geneDistance;
	}

	// Normalizes fitness using min-max and inverts values so shortest distance is highest fitness
	for (int i = 0; i < population.size(); i++) {
		fitness[i] = (227 / popDistances[i]);
	}
	return true;
}

void Genetic::selection(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2) {
	GeneticOperators::select(population, popFitness, p1, p2, selectionType);
}

void Genetic::crossover(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2) {
	GeneticOperators::crossover(p1, p2, c1, c2, crossoverRate, crossoverType);
}

void Genetic::mutate(std::vector<int>& gene) {
	GeneticOperators::mutate(gene, mutationRate, mutationType);
}

void Genetic::insert(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& c1, std::vector<int>& c2) {
	std::vector<float> similar{ (float)INT32_MAX, (float)INT32_MAX };
	std::vector<int> similarIndex{ -1, -1 };

	std::vector<std::vector<int>> children{ c1, c2 };
	std::vector<float> distance(2);
	std::vector<float> fitness(2);

	calculateFitness(children, distance, fitness);

	// Finds the most similar fitness gene in the pool
	for (int c = 0; c < 2; c++) {
		for (int i = 0; i < populationSize; i++) {
			if (similarIndex[0] == i)
				continue;
			if (abs(popFitness[i] - fitness[c]) < similar[c]) {
				similar[c] = popFitness[i] - fitness[c];
				similarIndex[c] = i;
			}
		}
	}

	// Only replaces it if the child is more fit
	for (int c = 0; c < 2; c++) {
		if (popFitness[similarIndex[c]] < fitness[c]) {
			population[similarIndex[c]] = children[c];
		}
	}
}

std::string Genetic::getTypeName() {
	std::string algoName = "Genetic Algorithm";
	std::string selectionName;
	std::string crossoverName;
	std::string mutationName;

	switch (selectionType) {
	case GeneticOperators::Selection::ROULETTE:
		selectionName = "Roulette Selection";
		break;
	case GeneticOperators::Selection::ELITISM:
		selectionName = "Elitism Selection";
		break;
	case GeneticOperators::Selection::TOURNAMENT:
		selectionName = "Tournament Selection";
		break;
	}

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

	return algoName + '\n' + selectionName + '\n' + crossoverName + '\n' + mutationName;
}
