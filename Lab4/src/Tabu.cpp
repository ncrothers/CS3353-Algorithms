#include "Tabu.h"

#include <ctime>
#include <sstream>
#include <fstream>

Tabu::~Tabu() {
	delete buffer;
}

void Tabu::configure(int opType1, int bufferSize, int opType3, int populationSize) {
	buffer = new ring_buffer<std::vector<int>>(bufferSize);
	hoodOp = static_cast<TabuOperators::Neighborhood>(opType1);
	generator.seed(time(0));
}

void Tabu::startAlgo(int _start, int _N) {

	start = _start;
	N = _N;

	TabuOperators::configure(N);
	buffer->clear();

	std::vector<int> currentNode(N);
	float currentFitness;
	generateStart(currentNode);

	int maxIterations = 1000;

	float bestDistance = ceil(bestDistances[N] * 10) / 10;

	while (bestTourDist > bestDistance) {

		currentFitness = calculateDistance(currentNode);
		updateBest(currentNode, currentFitness);

		count++;

		if (timeSinceNewBest > maxIterations) {
			generateStart(currentNode);
			timeSinceNewBest = 0;
			continue;
		}

		timeSinceNewBest++;

		std::vector<std::vector<int>> neighborhood;
		selectNeighborhood(currentNode, neighborhood);

		std::vector<float> fitness;
		calculateNeighborhoodFitness(neighborhood, fitness);

		float best = INT32_MAX;
		int bestIndex = 0;

		for (int i = 0; i < neighborhood.size(); i++) {
			if (buffer->contains(neighborhood[i]))
				continue;

			if (fitness[i] < best) {
				best = fitness[i];
				bestIndex = i;
			}
		}

		currentNode = neighborhood[bestIndex];
		buffer->push(currentNode);
	}
}

// Generates a random solution to begin the algorithm
void Tabu::generateStart(std::vector<int>& node) {

	std::uniform_int_distribution<int> distribution(0, N - 1);

	int poolSize = 100;

	std::vector<std::vector<int>> selectionPool(poolSize);
	std::vector<float> poolFitness;

	for (int i = 0; i < poolSize; i++) {
		// Stores which nodes have been used
		uint64_t used = 1 << (start - 1);
		uint64_t one = 1;
		// Sets first node to the start node
		selectionPool[i].push_back(start - 1);

		int index = 1;
		// While not all nodes have been used
		while (used != (one << N) - 1) {
			// Current randomly generated node
			int cur = distribution(generator);

			if (used & (one << cur))
				continue;

			selectionPool[i].push_back(cur);
			used ^= one << cur;
			index++;
		}
	}

	calculateNeighborhoodFitness(selectionPool, poolFitness);

	float best = poolFitness[0];
	int bestIndex = 0;

	for (int i = 1; i < poolSize; i++) {
		if (poolFitness[i] < best) {
			best = poolFitness[i];
			bestIndex = i;
		}
	}
	
	node = selectionPool[bestIndex];

}

// Calculates the fitness of the entire neighborhood
void Tabu::calculateNeighborhoodFitness(std::vector<std::vector<int>>& neighborhood, std::vector<float>& fitness) {

	for (int i = 0; i < neighborhood.size(); i++) {
		fitness.push_back(calculateDistance(neighborhood[i]));
	}
}

float Tabu::calculateDistance(std::vector<int>& node) {

	float sumDistance = 0;

	for (int i = 0; i < node.size() - 1; i++) {
		sumDistance += distance[node[i]][node[i + 1]];
	}
	sumDistance += distance[node[node.size() - 1]][start - 1];

	return sumDistance;
}

void Tabu::updateBest(std::vector<int>& tour, float distance) {

	if (distance < bestTourDist) {
		setBestTour(tour);
		bestTourDist = distance;
	}
}

void Tabu::selectNeighborhood(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood) {
	TabuOperators::selectNeighborhood(source, neighborhood, hoodOp);
}

std::string Tabu::getTypeName() {
	std::string algoName = "Tabu Search";
	std::string neighborhoodName;
	switch (hoodOp) {
	case TabuOperators::Neighborhood::SWAP:
		neighborhoodName = "Swap";
		break;
	case TabuOperators::Neighborhood::INVERSION:
		neighborhoodName = "Inversion";
		break;
	}

	std::stringstream output;

	output << algoName << std::endl << neighborhoodName << std::endl << "Tabu List Size - " << buffer->size();

	return output.str();
}