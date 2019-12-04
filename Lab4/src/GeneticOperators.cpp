#include "GeneticOperators.h"

#include <limits.h>
#include <math.h>
#include <ctime>

int GeneticOperators::populationSize = 0;
int GeneticOperators::N = 0;
std::default_random_engine GeneticOperators::generator;
std::vector<std::vector<float>>* GeneticOperators::distances = nullptr;

void GeneticOperators::configure(int _populationSize, int _N, std::vector<std::vector<float>>& _distances) {
	populationSize = _populationSize;
	N = _N;
	generator.seed(time(0));
	distances = &_distances;
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

std::string GeneticOperators::getSelectionName(int type) {
	switch (type) {
	case 0:
		return std::string("roulette");
	case 1:
		return std::string("elitism");
	case 2:
		return std::string("tourney");
	default:
		return std::string("unknown");
	}
}

std::string GeneticOperators::getCrossoverName(int type) {
	switch (type) {
	case 0:
		return std::string("pmapped");
	case 1:
		return std::string("order");
	default:
		return std::string("unknown");
	}
}

std::string GeneticOperators::getMutationName(int type) {
	switch (type) {
	case 0:
		return std::string("swap");
	case 1:
		return std::string("inversion");
	default:
		return std::string("unknown");
	}
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

	// Prevents floating-point rounding errors where spin == sumFitness
	float spin = getRandomFloat(0.0, sumFitness - 0.1);
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
	int numOpponents = 10;
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

	int keepIndex = keepValue(p1);

	// Selects random bounds for the subpath
	int start = getRandomInt(1, ceil((float)N / 2));
	int end = getRandomInt(ceil((float)N / 2), N);

	if (N > 8) {
		while (keepIndex < start)
			start--;
		while (keepIndex > start)
			start++;
		while (keepIndex + 2 > end)
			end++;
	}

	// Transfers the randomly selected subpath over from the first parent
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

		// If all have been visited, stop the loop
		if (visited == (1 << N) - 2)
			break;

		if ((visited & (1 << p2[i])) == 0) {
			child[i] = p2[i];
			visited |= 1 << p2[i];
		}
	}
}

void GeneticOperators::crossoverOrder(std::vector<int>& p1, std::vector<int>& p2, std::vector<int>& child) {
	int visited = 0;

	int keepIndex = keepValue(p1);

	// Selects random bounds for the subpath
	int start = getRandomInt(1, ceil((float)N / 2));
	int end = getRandomInt(ceil((float)N / 2), N);

	if (N > 8) {
		while (keepIndex < start)
			start--;
		while (keepIndex > start)
			start++;
		while (keepIndex + 2 > end)
			end++;
	}

	// Transfers the randomly selected subpath over from the first parent
	for (int i = start; i <= end; i++) {
		child[i] = p1[i];
		visited |= 1 << p1[i];
	}

	int pIndex = end;
	int cIndex = (pIndex == N - 1 ? 1 : end + 1);

	if (start == 2)
		pIndex += 0;

	while (cIndex != start) {
		// If already in tour, skip and increment/wrap to the beginning
		if ((visited & (1 << p2[pIndex])) != 0) {
			pIndex = (pIndex == N - 1 ? 1 : pIndex + 1);
			continue;
		}

		child[cIndex] = p2[pIndex];
		visited |= 1 << p2[pIndex];
		// Either increments index or wraps to the beginning
		pIndex = (pIndex == N - 1 ? 1 : pIndex + 1);
		cIndex = (cIndex == N - 1 ? 1 : cIndex + 1);
	}
}

// Mutation Functions

void GeneticOperators::mutateSwap(std::vector<int>& gene) {
	int index1 = getRandomInt(1, N);
	int index2 = getRandomInt(1, N);
	int index3 = getRandomInt(1, N);

	while (index2 == index1)
		index2 = getRandomInt(1, N);
	while (index3 == index2 || index3 == index1)
		index3 = getRandomInt(1, N);


	int temp1 = gene[index3];
	int temp2 = gene[index1];
	gene[index1] = gene[index2];
	gene[index2] = temp1;
	gene[index3] = temp2;
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

int GeneticOperators::keepValue(std::vector<int>& gene) {
	float best = INT32_MAX;
	int bestIndex = 0;
	for (int i = 0; i < gene.size() - 1; i++) {
		float cur = distances->at(i).at(i + 1) + distances->at(i + 1).at(i + 2);
		if (cur < best) {
			best = cur;
			bestIndex = i;
		}
	}

	return bestIndex;
}