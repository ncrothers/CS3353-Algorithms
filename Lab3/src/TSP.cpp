#include "TSP.h"

#include <math.h>

float getDistance(Parser::Position&, Parser::Position&);

TSP::TSP(Factory::TSPAlgos algo) {
	switch (algo) {
	case Factory::NAIVEBF:
		algoObj = new NaiveBF();
		break;
	case Factory::DP:
		algoObj = new DynamicP();
		break;
	}
}

int TSP::Load(const char* filePath) {
	std::unordered_map<int, Parser::Position> positions;

	int size = Parser::loadGraph(positions, filePath);
	std::vector<std::vector<float>> distance(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			distance[i].push_back(0);
		}
	}

	// Loads in all distances so they don't have to be calculated during the algorithm
	for (int i = 1; i < size; i++) {
		for (int j = 1; j < size; j++) {
			// This distance is 0 as well as irrelevant
			if (i == j) continue;
			// All distances will be calculated twice if this isn't checked
			if (distance[i][j] != 0) continue;
			// Sets both directions to the same distance
			float dist = getDistance(positions.at(i), positions.at(j));
			distance[i][j] = dist;
			distance[j][i] = dist;
		}
	}

	// Sends the distance matrix ptr to the algorithm
	algoObj->initDistanceMatrix(distance);

	return 0;
}

float getDistance(Parser::Position& start, Parser::Position& end) {
	return (sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2) + pow(start.z - end.z, 2)));
}

void TSP::Execute(int start, int size) {
	algoObj->start(start, size);
}

void TSP::Select(int type) {

}

void TSP::Display(Factory::TSPAlgos) {

}

void TSP::Stats(Factory::TSPAlgos algo, int type) {

}

void TSP::Save(Factory::TSPAlgos, int, int, int) {

}