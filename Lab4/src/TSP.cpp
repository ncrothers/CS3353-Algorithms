#include "TSP.h"
#include "Genetic.h"
#include "Tabu.h"

#include <math.h>
#include <iostream>

float getDistance(FileHandler::Position&, FileHandler::Position&);

TSP::TSP(Factory::TSPAlgos algo) {
	switch (algo) {
	case Factory::TSPAlgos::GENETIC:
		algoObj = new Genetic();
		break;
	case Factory::TSPAlgos::TABU:
		algoObj = new Tabu();
		break;
	case Factory::TSPAlgos::LAST:
		break;
	default:
		break;
	}
}

int TSP::Load(const char* filePath) {
	std::unordered_map<int, FileHandler::Position> positions;

	int size = FileHandler::loadGraph(positions, filePath);
	std::vector<std::vector<float>> distance(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			distance[i].push_back(0);
		}
	}

	// Loads in all distances so they don't have to be calculated during the algorithm
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// This distance is 0 as well as irrelevant
			if (i == j) continue;
			// All distances will be calculated twice if this isn't checked
			if (distance[i][j] != 0) continue;
			// Sets both directions to the same distance
			float dist = getDistance(positions.at(i + 1), positions.at(j + 1));
			distance[i][j] = dist;
			distance[j][i] = dist;
		}
	}

	// Sends the distance matrix ptr to the algorithm
	algoObj->initDistanceMatrix(distance);

	FileHandler::loadBestDistances("results/dynamicp.csv", algoObj->bestDistances);

	return 0;
}

float getDistance(FileHandler::Position& start, FileHandler::Position& end) {
	return (sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2) + pow(start.z - end.z, 2)));
}

void TSP::Configure(int opType1, int opType2, int opType3, int populationSize) {
	if (populationSize == -1 || opType3 == -1)
		algoObj->configure(opType1, opType2);
	else
		algoObj->configure(opType1, opType2, opType3, populationSize);
}

void TSP::Execute(int start, int size) {
	algoObj->reset();
	begin = std::chrono::high_resolution_clock::now();
	algoObj->startAlgo(start, size);
	end = std::chrono::high_resolution_clock::now();

	auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);
	execTimes.push_back(elapsedTime.count());
	tourDistances.push_back(algoObj->getBestDistance());
}

void TSP::Stats() {
	std::vector<int>& tour = algoObj->getBestTour();

	std::cout << algoObj->getTypeName() << ":" << std::endl
		<< "Number of nodes: " << tour.size() << std::endl
		<< "Starting node: " << tour[0] << std::endl
		<< "Shortest tour: ";

	for (int i = 0; i < tour.size(); i++) {
		std::cout << tour[i] + 1 << (i == tour.size() - 1 ? "" : "->");
	}
	std::cout << std::endl
		<< "Tour distance: " << algoObj->getBestDistance() << std::endl
		<< "Time elapsed: " << execTimes.back() << " seconds" << std::endl << std::endl;

}

void TSP::Save(const char* filePath, int sizeStart) {
	FileHandler::saveData(filePath, tourDistances, execTimes, sizeStart);
	tourDistances.clear();
	execTimes.clear();
}