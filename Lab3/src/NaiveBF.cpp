#include "NaiveBF.h"

#include <math.h>

NaiveBF::NaiveBF() {
}

void NaiveBF::startAlgo(int _start, int _N) {
	N = _N;
	start = _start;
	allVisited = (1 << N) - 1;
	std::vector<int> path;
	
	branch(path, 0, start);
}

void NaiveBF::branch(std::vector<int> path, int visited, int next) {
	branchCount++;
	path.push_back(next);
	// Marks the current node as visited
	visited |= (1 << (next - 1));

	if (next == start && visited == allVisited) {
		float pathDist = getPathDistance(path);
		if (pathDist < bestPathDist) {
			bestPath = path;
			bestPathDist = pathDist;
		}
	}
	else {
		if (visited == allVisited) {
			branch(path, visited, 1);
		}
		for (int i = 1; i <= N; i++) {
			// Checks if the node has been visited
			if ((visited & (1 << i - 1)) == 0) {
				branch(path, visited, i);
			}
		}
	}

}

float NaiveBF::getPathDistance(std::vector<int>& path) {
	float totalDist = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		totalDist += distance[path[i] - 1][path[i + 1] - 1];
	}
	return totalDist;
}
