#ifndef TSPALGO_H
#define TSPALGO_H

#include "Parser.h"

#include <vector>
#include <unordered_map>

class TSPAlgorithm {
public:
	virtual void start(int start, int size) = 0;

	virtual std::unordered_map<int, Parser::Position>& getPositions() {
		return positions;
	}
protected:
	std::unordered_map<int, Parser::Position> positions;

	int numCities = 0;
	std::vector<int> bestPath;
	float bestPathDist = INT32_MAX;
	int startNode = 0;
};

#endif