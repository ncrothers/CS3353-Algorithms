#include "DynamicP.h"

#include <string>

std::string DynamicP::getTypeName() {
	return std::string("Dynamic Programming - Tabulation");
}

void DynamicP::startAlgo(int _start, int _N) {
	N = _N;
	// Converts startnode to one less for indexing
	start = _start - 1;

	allVisited = (1 << N) - 1;
	bestTourDist = INT32_MAX;

	if (bestTour.size() != 0) 
		bestTour.clear();

	// Creates table
	double** table = new double*[N];
	for (int i = 0; i < N; i++) {
		table[i] = new double[1 << N];
	}

	for (int next = 0; next < N; next++) {
		if (next == start) continue;
		// Adds all next subpaths to the starting node
		table[next][(1 << start) | (1 << next)] = distance[start][next];
	}

	for (int r = 3; r <= N; r++) {
		for (int subset : combinations(r)) {
			if (notIn(start, subset)) continue;

			for (int next = 0; next < N; next++) {
				// Skips current node if it is the same as the start or if not in the current path
				if (next == start || notIn(next, subset)) continue;

				int subsetWithoutNext = subset ^ (1 << next);
				float bestDist = INT32_MAX;

				// This for loop and the subsequent statement builds the table table with adding distances
				// together and inserting them into the table as appropriate
				for (int end = 0; end < N; end++) {
					if (end == start || end == next || notIn(end, subset)) continue;
					double newDistance = table[end][subsetWithoutNext] + distance[end][next];
					if (newDistance < bestDist) {
						bestDist = newDistance;
					}
				}
				table[next][subset] = bestDist;
			}
		}
	}

	// Connect tour back to starting node and minimize cost
	for (int i = 0; i < N; i++) {
		if (i == start) continue;
		double tourCost = table[i][allVisited] + distance[i][start];
		if (tourCost < bestTourDist) {
			bestTourDist = tourCost;
		}
	}

	int lastIndex = start;
	int state = allVisited;
	bestTour.push_back(start + 1);

	// Follow path from table
	for (int i = 1; i < N; i++) {

		int index = -1;
		for (int j = 0; j < N; j++) {
			if (j == start || notIn(j, state)) continue;
			if (index == -1) index = j;
			double prevDist = table[index][state] + distance[index][lastIndex];
			double newDist = table[j][state] + distance[j][lastIndex];
			if (newDist < prevDist) {
				index = j;
			}
		}
		bestTour.push_back(index + 1);
		state ^= (1 << index);
		lastIndex = index;
	}

	bestTour.push_back(start + 1);

	// Frees the memory used by the table
	for (int i = 0; i < N; i++) {
		delete[] table[i];
	}
	delete[] table;
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
	int elemRemain = N - cur;
	if (elemRemain < r) return;

	if (r == 0) {
		subsets.push_back(set);
	}
	else {
		for (int i = cur; i < N; i++) {
			// Use set with the current node visited
			set ^= 1 << i;

			combinations(set, i + 1, r - 1, subsets);

			// Backtrack with current node not visited
			set ^= 1 << i;
		}
	}
}