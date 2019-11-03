#ifndef TSPALGO_H
#define TSPALGO_H

#include "Parser.h"

#include <vector>
#include <unordered_map>

class TSPAlgorithm {
public:
	virtual void startAlgo(int _start, int _N) = 0;

	virtual void initDistanceMatrix(std::vector<std::vector<float>> input) {
		distance = input;
	}
protected:
	std::vector<std::vector<float>> distance;

	int allVisited = 0;
	int N = 0;
	std::vector<int> bestPath;
	float bestPathDist = INT32_MAX;
	int start = 0;
};

#endif