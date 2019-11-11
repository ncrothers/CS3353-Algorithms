#include "NaiveBF.h"

#include <math.h>
#include <string>

NaiveBF::NaiveBF() {
}

std::string NaiveBF::getTypeName() {
	return std::string("Naive Brute Force");
}

void NaiveBF::startAlgo(int _start, int _N) {
	N = _N;
	start = _start;
	allVisited = (1 << N) - 1;
	bestTourDist = INT32_MAX;
	std::vector<int> path;
	
	branch(path, 0, start);
	std::reverse(bestTour.begin(), bestTour.end());
}

void NaiveBF::branch(std::vector<int> path, int visited, int next) {
	branchCount++;
	path.push_back(next);
	// Marks the current node as visited
	visited |= (1 << (next - 1));

	if (next == start && visited == allVisited) {
		float pathDist = getTourDistance(path);
		if (pathDist < bestTourDist) {
			bestTour = path;
			bestTourDist = pathDist;
		}
	}
	else {
		if (visited == allVisited) {
			branch(path, visited, 1);
		}
		for (int i = 1; i <= N; i++) {
			// Checks if the node has been visited
			if ((visited & (1 << (i - 1))) == 0) {
				branch(path, visited, i);
			}
		}
	}

}

float NaiveBF::getTourDistance(std::vector<int>& path) {
	float totalDist = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		totalDist += distance[path[i] - 1][path[i + 1] - 1];
	}
	return totalDist;
}
