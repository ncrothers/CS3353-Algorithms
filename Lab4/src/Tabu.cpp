#include "Tabu.h"

#include <random>
#include <ctime>
#include <sstream>

Tabu::~Tabu() {
	delete buffer;
}

void Tabu::configure(int opType1, int bufferSize, int opType3, int populationSize) {
	buffer = new ring_buffer<std::vector<int>>(bufferSize);
	hoodOp = static_cast<TabuOperators::Neighborhood>(opType1);
}

void Tabu::startAlgo(int _start, int _N) {

	start = _start;
	N = _N;

	TabuOperators::configure(N);

	std::vector<int> currentNode(N);
	float currentFitness;
	generateStart(currentNode);

	for (int i = 0; i < iterationCount; i++) {

		currentFitness = calculateDistance(currentNode);
		updateBest(currentNode, currentFitness);

		std::vector<std::vector<int>> neighborhood;
		selectNeighborhood(currentNode, neighborhood);

		std::vector<float> fitness;
		calculateNeighborhoodFitness(neighborhood, fitness);

		float best = INT_MAX;
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

// Generates a random population to begin the algorithm
void Tabu::generateStart(std::vector<int>& node) {

	std::default_random_engine generator;
	generator.seed(time(0));
	std::uniform_int_distribution<int> distribution(0, N - 1);

	// Stores which nodes have been used
	int used = 1 << (start - 1);
	// Sets first node to the start node
	node[0] = start - 1;

	int index = 1;
	// While not all nodes have been added to the current gene
	while (used != (1 << N) - 1) {
		// Current randomly generated node
		int cur = distribution(generator);

		if (used & (1 << cur))
			continue;

		node[index] = cur;
		used ^= 1 << cur;
		index++;
	}
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
	}

	std::stringstream output;

	output << algoName << std::endl << neighborhoodName << std::endl << "Tabu List Size: " << buffer->size();

	return output.str();
}