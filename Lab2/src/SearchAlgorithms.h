#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMs_H

#include "Algorithm.h"
#include "graph.h"
#include "tree.h"

class SearchAlgorithms {
public:
	// Runs the sorting algorithm based on what enum value was passed in
	static tree<int> runSearch(enum Algorithm::SearchAlgos algo, graph& data, int start, int dest);
	static tree<int> BFS(graph& data, int start, int dest);
	static tree<int> DFS(graph& data, int start, int dest);
	static tree<int> dijkstra(graph& data, int start, int dest);
	static tree<int> aStar(graph& data, int start, int dest);

private:
	static tree<int> path;
};

#endif SEARCHALGORITHMS_H