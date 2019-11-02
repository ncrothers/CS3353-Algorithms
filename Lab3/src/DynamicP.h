#ifndef DYNAMICP_H
#define DYNAMICP_H

#include "TSPAlgorithm.h"

class DynamicP : public TSPAlgorithm {
public:
	void start(int start, int size);

private:
	std::vector<int> combinations(int r);
	void combinations(int set, int cur, int r, std::vector<int>& subsets);
	bool notIn(int node, int subset);

};

#endif