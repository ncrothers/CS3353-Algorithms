#ifndef TSPALGO_H
#define TSPALGO_H

#include "Parser.h"

#include <vector>
#include <unordered_map>

class TSPAlgorithm {
public:
	virtual void start(int start, int size) = 0;

	virtual void initDistanceMatrix(std::vector<std::vector<float>> input) {
		distance = input;
	}
protected:
	std::vector<std::vector<float>> distance;

	int numCities = 0;
	std::vector<int> bestPath;
	float bestPathDist = INT32_MAX;
	int startNode = 0;
};

#endif