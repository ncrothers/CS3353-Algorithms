#ifndef TSPALGO_H
#define TSPALGO_H

#include "FileHandler.h"

#include <vector>
#include <unordered_map>
#include <chrono>

class TSPAlgorithm {
public:
  enum class Crossover {
    PARTIALLY_MAPPED,
    ORDER
  };

  enum class Mutation {
    SWAP,
    INVERSION
  };
	
	virtual void startAlgo(int _start, int _N, int _populationSize, Crossover coType, Mutation mutType) = 0;

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
