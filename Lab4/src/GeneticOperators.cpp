#include "GeneticOperators.h"

#include <limits.h>
#include <math.h>
#include <random>
#include <ctime>

int GeneticOperators::populationSize = 0;
int GeneticOperators::N = 0;

void GeneticOperators::configure(int _populationSize, int _N) {
	populationSize = _populationSize;
	N = _N;
}

void GeneticOperators::select(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2, Selection op) {
	switch (op) {
	case Selection::ROULETTE:
		selectRoulette(population, popFitness, p1, p2);
		break;
	case Selection::ELITISM:
		selectElitism(population, popFitness, p1, p2);
		break;
	}
}

void GeneticOperators::crossover(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2, Crossover op) {
	switch (op) {
	case Crossover::PARTIALLY_MAPPED:
		crossoverPartiallyMapped(p1, p2, c1, c2);
		break;
	case Crossover::ORDER:
		crossoverOrder(p1, p2, c1, c2);
		break;
	}
}

void GeneticOperators::mutate(std::vector<int>& gene, float mutationRate, Mutation op) {
	switch (op) {
	case Mutation::SWAP:
		mutateSwap(gene, mutationRate);
		break;
	case Mutation::INVERSION:
		mutateInvert(gene, mutationRate);
		break;
	}
}

// Selection Functions

void GeneticOperators::selectRoulette(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2) {
	std::vector<float> probabilities;

	float sumFitness = 0;

	for (int i = 0; i < populationSize; i++) {
		sumFitness += popFitness[i];
	}

	std::srand(time(0));

	float spin = rand() % static_cast<int>(sumFitness);
	int i = 0;

	while (spin < sumFitness) {
		spin += popFitness[i];
		i++;
	}
	
	p1 = population[i - 1];

	spin = rand() % static_cast<int>(sumFitness);
	i = 0;

	while (spin < sumFitness) {
		spin += popFitness[i];
		i++;
	}

	p2 = population[i - 1];
}

void GeneticOperators::selectElitism(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2) {
	float best, secondBest;
	best = secondBest = INT_MAX;
	int bestIndex, secondBestIndex;
	bestIndex = secondBestIndex = 0;

	for (int i = 0; i < populationSize; i++) {
		if (popFitness[i] < best) {
			best = popFitness[i];
			bestIndex = i;
		}
		else if (popFitness[i] < secondBest) {
			secondBest = popFitness[i];
			secondBestIndex = i;
		}
	}

	p1 = population[bestIndex];
	p2 = population[secondBestIndex];
}

// Crossover Functions

void GeneticOperators::crossoverPartiallyMapped(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2) {
	std::srand(time(0));

	int c1Visited = 0;
	int c2Visited = 0;

	// Selects random bounds for the subpath
	int start	= std::rand() % (N / 3);
	int end		= std::rand() % (N / 3) + (N / 2);

	// Transfers the randomly selected subpath over from the opposite parent (c1 with p2, c2 with p1)
	for (int i = start; i <= end; i++) {
		c2[i] = p1[i];
		c2Visited ^= 1 << p1[i];
		c1[i] = p2[i];
		c1Visited ^= 1 << p2[i];
	}

	// Fills in any nonconflicting values from the corresponding parent (c1 with p1, c2 with p2)
	for (int i = 0; i < N; i++) {
		// Skips existing middle values
		if (i >= start & i <= end)
			continue;
		if ((c1Visited & 1 << p1[i]) == 0) {
			c1[i] = p1[i];
			c1Visited ^= 1 << p1[i];
		}
		else {
			// Go through the middle section and emplace nonconflicting values
			for (int j = start; j <= end; j++) {
				if ((c1Visited & 1 << p1[j]) == 0) {
					c1[i] = p1[j];
					c1Visited ^= 1 << p1[j];
					break;
				}
			}
		}
		
		if ((c2Visited & 1 << p2[i]) == 0) {
			c2[i] = p2[i];
			c2Visited ^= 1 << p2[i];
		}
		else {
			// Go through the middle section and emplace nonconflicting values
			for (int j = start; j <= end; j++) {
				if ((c2Visited & 1 << p2[j]) == 0) {
					c2[i] = p2[j];
					c2Visited ^= 1 << p2[j];
					break;
				}
			}
		}
	}
}

void GeneticOperators::crossoverOrder(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2) {

}

// Mutation Functions

void GeneticOperators::mutateSwap(std::vector<int>& gene, float mutationRate) {
	std::srand(time(0));

	// Mutation probability calculation
	if (std::rand() > mutationRate)
		return;

	int index1 = std::rand() % N;
	int index2 = std::rand() % N;

	int temp = gene[index1];
	gene[index1] = gene[index2];
	gene[index2] = temp;
}

void GeneticOperators::mutateInvert(std::vector<int>& gene, float mutationRate) {

}