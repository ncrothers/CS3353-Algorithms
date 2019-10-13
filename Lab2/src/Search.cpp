#include "Search.h"
#include "SearchAlgorithms.h"
#include "Parser.h"

#include <iostream>

Search::Search() {

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

void Search::Execute() {
	for (int i = Algorithm::SearchAlgos::BFS; i < Algorithm::SearchAlgos::END; i++) {
		SearchAlgorithms::runSearch(static_cast<Algorithm::SearchAlgos>(i), adjlist, 1, 5);
	}
}

void Search::Display(Algorithm::SearchAlgos algo) {
	switch (algo) {
	case BFS:
		for (int i = 1; i <= 16; i++) {
			std::cout << i << ":";
			for (auto val : adjmatrix.getChildren(i)) {
				std::cout << val << ",";
			}
			std::cout << std::endl;
		}
		break;
	case DFS:
		break;
	case DIJKSTRA:
		break;
	case ASTAR:
		break;
	}
}

void Search::Save(Algorithm::SearchAlgos, int) {

}