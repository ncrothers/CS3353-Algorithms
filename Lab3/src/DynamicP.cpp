#include "DynamicP.h"

void DynamicP::start(int start, int size) {
	numCities = size;
	startNode = start;

	// Creates memo table
	double** memo = new double*[size];
	for (int i = 0; i < size; i++) {
		memo[i] = new double[1 << size];
	}

	int allVisited = (1 << size) - 1;

	for (int next = 0; next < size; next++) {
		if (next == start) continue;
		// Adds all next subpaths to the starting node
		memo[next][(1 << start) | (1 << next)] = distance[start][next];
	}

	for (int r = 3; r <= numCities; r++) {
		for (int subset : combinations(r)) {
			if (notIn(start, subset)) continue;

			for (int next = 0; next < numCities; next++) {
				// Skips current node if it is the same as the start or if not in the current path
				if (next == start || notIn(next, subset)) continue;

				int subsetWithoutNext = subset ^ (1 << next);

				// This for loop and the subsequent statement builds the memo table with adding distances
				// together and inserting them into the table as appropriate
				for (int end = 0; end < numCities; end++) {
					if (end == start || end == next || notIn(end, subset)) continue;
					double newDistance = memo[end][subsetWithoutNext] + distance[end][next];
					if (newDistance < bestPathDist) {
						bestPathDist = newDistance;
					}
				}
				memo[next][subset] = bestPathDist;
			}
		}
	}

	// Connect tour back to starting node and minimize cost
	for (int i = 0; i < numCities; i++) {
		if (i == start) continue;
		double tourCost = memo[i][allVisited] + distance[i][start];
		if (tourCost < bestPathDist) {
			bestPathDist = tourCost;
		}
	}

	int lastIndex = start;
	int state = allVisited;
	bestPath.push_back(start);

	// Follow path from memo table
	for (int i = 1; i < numCities; i++) {

		int index = -1;
		for (int j = 0; j < numCities; j++) {
			if (j == start || notIn(j, state)) continue;
			if (index == -1) index = j;
			double prevDist = memo[index][state] + distance[index][lastIndex];
			double newDist = memo[j][state] + distance[j][lastIndex];
			if (newDist < prevDist) {
				index = j;
			}
		}

		bestPath.push_back(index);
		state = state ^ (1 << index);
		lastIndex = index;
	}

	bestPath.push_back(start);

	// Frees the memory used by the memo table
	for (int i = 0; i < size; i++) {
		delete[] memo[i];
	}
	delete[] memo;
}

bool DynamicP::notIn(int node, int subset) {
	return ((1 << node) & subset) == 0;
}

std::vector<int> DynamicP::combinations(int r) {
	std::vector<int> subsets;

	combinations(0, 0, r, subsets);
	return subsets;
}

void DynamicP::combinations(int set, int cur, int r, std::vector<int>& subsets) {
	int elemRemain = numCities - 1;
	if (elemRemain < r) return;

	if (r == 0) {
		subsets.push_back(set);
	}
	else {
		for (int i = cur; i < numCities; i++) {
			// Use set with the current node visited
			set &= 1 << i;

			combinations(set, cur + 1, r + 1, subsets);

			// Backtrack with current node not visited
			set &= 0 << i;
		}
	}
}