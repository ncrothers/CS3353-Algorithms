#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMs_H

#include "Algorithm.h"
#include "graph.h"
#include "tree.h"

class SearchAlgorithms {
public:
	// Runs the sorting algorithm based on what enum value was passed in
	static tree<int> runSearch(enum Algorithm::SearchAlgos algo, graph<int>& data, int start, int dest);
	static tree<int> BFS(graph<int>& data, int start, int dest);
	static tree<int> DFS(graph<int>& data, int start, int dest);
	static tree<int> dijkstra(graph<int>& data, int start, int dest);
	static tree<int> aStar(graph<int>& data, int start, int dest);

private:
	static tree<int> path;
};

#endif SEARCHALGORITHMS_H