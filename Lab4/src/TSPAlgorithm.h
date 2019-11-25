#ifndef TSPALGO_H
#define TSPALGO_H

#include "FileHandler.h"

#include <vector>
#include <unordered_map>
#include <chrono>

class TSPAlgorithm {
public:
	virtual void startAlgo(int _start, int _N) = 0;
	// Two configure options based on what is passed in
	virtual void configure(int opType1, int opType2, int opType3, int populationSize);
	virtual void configure(int opType1, int opType2);

	virtual void initDistanceMatrix(std::vector<std::vector<float>> input) {
		distance = input;
	}

	virtual float getBestDistance() const {
		return bestTourDist;
	}

	virtual std::vector<int>& getBestTour() {
		return bestTour;
	}

	virtual std::string getTypeName() = 0;
protected:
	std::vector<std::vector<float>> distance;

	int allVisited = 0;
	int N = 0;
	std::vector<int> bestTour;
	float bestTourDist = INT32_MAX;
	int start = 0;
};

#endif
