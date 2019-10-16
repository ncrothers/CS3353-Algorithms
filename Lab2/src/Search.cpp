#include "Search.h"
#include "Parser.h"

#include <iostream>
#include <iomanip>

Search::Search() {
	graphType = nullptr;
}

void Search::Load(const char* path) {
	std::string folder(path);
	Parser::loadGraph(adjlist, (folder + "graph.txt").c_str());
	Parser::loadGraph(adjmatrix, (folder + "graph.txt").c_str());

	Parser::loadPositions(adjlist, (folder + "positions.txt").c_str());
	Parser::loadPositions(adjmatrix, (folder + "positions.txt").c_str());

	Parser::loadWeights(adjlist, (folder + "weights.txt").c_str());
	Parser::loadWeights(adjmatrix, (folder + "weights.txt").c_str());
}

void Search::Execute(Algorithm::SearchAlgos algo, int start, int dest) {
	begin = std::chrono::high_resolution_clock::now();
	curResult = SearchAlgorithms::runSearch(algo, *graphType, start, dest);
	end = std::chrono::high_resolution_clock::now();
}

void Search::Select(int type) {
	if (type == 0)
		graphType = &adjlist;
	else
		graphType = &adjmatrix;
}

void Search::Display(Algorithm::SearchAlgos algo) {
	switch (algo) {
	case BFS:
		break;
	case DFS:
		break;
	case DIJKSTRA:
		break;
	case ASTAR:
		break;
	}
}

void Search::Stats(Algorithm::SearchAlgos algo, int type) {
	std::cout << "Algorithm: ";
	std::string algoStr;
	switch (algo) {
	case BFS:
		algoStr = "Iterative BFS";
		break;
	case RECURBFS:
		algoStr = "Recursive BFS";
		break;
	case DFS:
		algoStr = "Iterative DFS";
		break;
	case RECURDFS:
		algoStr = "Recursive DFS";
		break;
	case DIJKSTRA:
		algoStr = "Dijkstra";
		break;
	case ASTAR:
		algoStr = "A* (A star)";
		break;
	}
	std::cout << algoStr << std::endl

		<< "Graph Type: " << (type == 0 ? "Adjacency List" : "Adjacency Matrix") << std::endl
		<< "Path: ";

	for (int i = curResult.path.size() - 1; i >= 0; i--) {
		std::cout << curResult.path[i] << (i != 0 ? " -> " : "");
	}

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);

	std::cout << std::endl
		<< "Nodes in Path: " << curResult.path.size() << std::endl
		<< "Path Cost: " << curResult.totalCost << std::endl
		<< "Path Distance: " << curResult.totalDistance << std::endl
		<< "Nodes Explored: " << curResult.nodesExplored << std::endl
		<< "Time elapsed: " << std::fixed << std::setprecision(7) << time_span.count() << " seconds"
		<< std::endl << std::endl;
}

void Search::Save(Algorithm::SearchAlgos, int) {

}