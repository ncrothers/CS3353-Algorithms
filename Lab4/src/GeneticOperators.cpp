#include "GeneticOperators.h"

#include <limits.h>
#include <math.h>
#include <ctime>

int GeneticOperators::populationSize = 0;
int GeneticOperators::N = 0;
std::default_random_engine GeneticOperators::generator;

void GeneticOperators::configure(int _populationSize, int _N) {
	populationSize = _populationSize;
	N = _N;
	generator.seed(time(0));
}

// Utility function for getting random values
float GeneticOperators::getRandomFloat(float lowerBound, float upperBound) {
	std::uniform_real_distribution<float> distribution(lowerBound, upperBound);
	return distribution(generator);
}

int GeneticOperators::getRandomInt(int lowerBound, int upperBound) {
	// Don't want inclusive upper bound
	std::uniform_int_distribution<int> distribution(lowerBound, upperBound - 1);
	return distribution(generator);
}

void GeneticOperators::select(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2, Selection op) {
	switch (op) {
	case Selection::ROULETTE:
		selectRoulette(population, popFitness, p1, p2);
		break;
	case Selection::ELITISM:
		selectElitism(population, popFitness, p1, p2);
		break;
	case Selection::TOURNAMENT:
		selectTournament(population, popFitness, p1, p2);
	}
}

void GeneticOperators::crossover(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& c1, std::vector<int>& c2, float crossoverRate, Crossover op) {
	
	if (getRandomFloat(0.0, 1.0) > crossoverRate) {
		c1 = p1;
		c2 = p2;
		return;
	}

	switch (op) {
	case Crossover::PARTIALLY_MAPPED:
		crossoverPartiallyMapped(p1, p2, c1);
		crossoverPartiallyMapped(p2, p1, c2);
		break;
	case Crossover::ORDER:
		crossoverOrder(p1, p2, c1);
		crossoverOrder(p2, p1, c2);
		break;
	}
}

void GeneticOperators::mutate(std::vector<int>& gene, float mutationRate, Mutation op) {

	if (getRandomFloat(0.0, 1.0) > mutationRate)
		return;

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

void GeneticOperators::selectRoulette(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2) {
	std::vector<float> probabilities;

	float sumFitness = 0;

	for (int i = 0; i < populationSize; i++) {
		sumFitness += popFitness[i];
	}

	float spin = getRandomFloat(0.0, sumFitness);
	int i = 0;

	while (spin < sumFitness) {
		spin += popFitness[i];
		i++;
	}
	
	p1 = population[i - 1];

	spin = getRandomFloat(0.0, sumFitness);
	i = 0;

	while (spin < sumFitness) {
		spin += popFitness[i];
		i++;
	}

	p2 = population[i - 1];
}

void GeneticOperators::selectElitism(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2) {
	float best, secondBest;
	best = secondBest = 0;
	int bestIndex, secondBestIndex;
	bestIndex = secondBestIndex = 0;

	for (int i = 0; i < populationSize; i++) {
		if (popFitness[i] > best) {
			best = popFitness[i];
			bestIndex = i;
		}
		else if (popFitness[i] > secondBest) {
			secondBest = popFitness[i];
			secondBestIndex = i;
		}
	}

	p1 = population[bestIndex];
	p2 = population[secondBestIndex];
}

void GeneticOperators::selectTournament(std::vector<std::vector<int>>& population, std::vector<float>& popFitness, std::vector<int>& p1, std::vector<int>& p2) {
	int numOpponents = 3;
	std::vector<int> opponents;

	for (int i = 0; i < numOpponents; i++) {
		opponents.push_back(getRandomInt(0, populationSize));
	}

	int best, secondBest, bestIndex, secondBestIndex;
	best = secondBest = 0;
	bestIndex = secondBestIndex = 0;

	for (auto opponent : opponents) {
		if (popFitness[opponent] > best) {
			best = popFitness[opponent];
			bestIndex = opponent;
		}
		else if (popFitness[opponent] > secondBest) {
			secondBest = popFitness[opponent];
			secondBestIndex = opponent;
		}
	}

	p1 = population[bestIndex];
	p2 = population[secondBestIndex];
}

// Crossover Functions

void GeneticOperators::crossoverPartiallyMapped(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& child) {

	int visited = 0;
	int subpathVisited = 0;

	// Selects random bounds for the subpath
	int start = getRandomInt(1, N / 3);
	int end = getRandomInt(N / 2, (3 * N) / 4);

	// Transfers the randomly selected subpath over from the opposite parent
	for (int i = start; i <= end; i++) {
		child[i] = p1[i];
		visited |= 1 << p1[i];
	}

	// Mapping process for values in subpath

	for (int cur = start; cur <= end; cur++) {
		// Skips if already in child
		if ((visited & (1 << p2[cur])) != 0)
			continue;

		for (int i = start; i <= end; i++) {

			if ((subpathVisited & (1 << i)) != 0)
				continue;

			int matchIndex = -1;
			int curNode = p1[i];

			// Finds matching value in parent2, -1 if within the subpath
			for (int j = 1; j < N; j++) {
				// Only checks values outside of subpath
				if (j < start || j > end) {
					if (p2[j] == curNode) {
						matchIndex = j;
						break;
					}
				}
			}

			// Move on if not matched
			if (matchIndex == -1)
				continue;

			child[matchIndex] = p2[cur];
			visited |= 1 << p2[cur];
			subpathVisited |= 1 << i;
			break;
		}
	}

	// Fills in remaining values
	for (int i = 1; i < N; i++) {

		if (visited == (1 << N) - 2)
			break;

		if ((visited & (1 << p2[i])) == 0) {
			child[i] = p2[i];
			visited |= 1 << p2[i];
		}
	}
}

void GeneticOperators::crossoverOrder(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& child) {

}

// Mutation Functions

void GeneticOperators::mutateSwap(std::vector<int>& gene) {
	int index1 = getRandomInt(1, N);
	int index2 = getRandomInt(1, N);

	int temp = gene[index1];
	gene[index1] = gene[index2];
	gene[index2] = temp;
}

void GeneticOperators::mutateInvert(std::vector<int>& gene) {
	int start	= getRandomInt(1, N / 2);
	int end		= getRandomInt(N / 2, N);

	for (int i = start, j = end; i < j; i++, j--) {
		int temp = gene[i];
		gene[i] = gene[j];
		gene[j] = temp;
	}
}