#ifndef NAIVEBF_H
#define NAIVEBF_H

#include "TSPAlgorithm.h"

#include <set>
#include <vector>

class NaiveBF : public TSPAlgorithm {
public:
	NaiveBF();
	void start(int start, int size);

	void branch(std::vector<int> path, int visited, int next);

private:
	// Keeps track of the total number of times the algorithm branches
	int branchCount = 0;
	float getPathDistance(std::vector<int>& path);
	bool allVisited(int visited);
};

#endif