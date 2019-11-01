#include "NaiveBF.h"

#include <math.h>

NaiveBF::NaiveBF() {
}

void NaiveBF::start(int start, int size) {
	numCities = size;
	startNode = start;
	std::vector<int> path;
	
	branch(path, 0, startNode);
}

void NaiveBF::branch(std::vector<int> path, int visited, int next) {
	branchCount++;
	path.push_back(next);
	// Marks the current node as visited
	visited = visited | (1 << (next - 1));

	if (next == startNode && allVisited(visited)) {
		float pathDist = getPathDistance(path);
		if (pathDist < bestPathDist) {
			bestPath = path;
			bestPathDist = pathDist;
		}
	}
	else {
		if (allVisited(visited)) {
			branch(path, visited, 1);
		}
		for (int i = 1; i <= numCities; i++) {
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
		totalDist += getDistance(path[i], path[i + 1]);
	}
	return totalDist;
}

// Function that checks if all nodes have been visited
bool NaiveBF::allVisited(int visited) {
	for (int i = 0; i < numCities; i++) {
		if ((visited & 1) != 1)
			return false;
		visited = visited >> 1;
	}
	return true;
}

float NaiveBF::getDistance(int first, int second) {
	Parser::Position& fPos = positions.at(first);
	Parser::Position& sPos = positions.at(second);

	return (sqrt(pow(sPos.x - fPos.x, 2) + pow(sPos.y - fPos.y, 2) + pow(sPos.z - fPos.z, 2)));
}