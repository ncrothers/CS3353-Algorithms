#ifndef TSPALGO_H
#define TSPALGO_H

#include "FileHandler.h"

#include <vector>
#include <unordered_map>
#include <chrono>
#include <iostream>

class TSPAlgorithm {
public:
	virtual void startAlgo(int _start, int _N) = 0;
	// Two configure options based on what is passed in
	virtual void configure(int opType1, int opType2, int opType3 = -1, int populationSize = -1) = 0;

	virtual void initDistanceMatrix(std::vector<std::vector<float>> input) {
		distance = input;
	}

	virtual float getBestDistance() const {
		return bestTourDist;
	}

	virtual std::vector<int>& getBestTour() {
		return bestTour;
	}

	virtual void setBestTour(std::vector<int>& tour) {
		bestTour = tour;
		timeSinceNewBest = 0;
	}

	virtual void reset() {
		bestTour.clear();
		bestTourDist = INT32_MAX;
	}

	virtual std::string getTypeName() = 0;
	std::vector<float> bestDistances;

protected:
	std::vector<std::vector<float>> distance;

	int allVisited = 0;
	int N = 0;
	std::vector<int> bestTour;
	float bestTourDist = INT32_MAX;
	int start = 0;
	int timeSinceNewBest = 0;
};

#endif
