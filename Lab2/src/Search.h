#ifndef SEARCH_H
#define SEARCH_H
#include "Algorithm.h"
#include "AdjList.h"
#include "AdjMatrix.h"
#include "SearchAlgorithms.h"

#include <string>
#include <vector>
#include <chrono>
#include <fstream>

class Search : public Algorithm {
public:

	Search();

	int Load(const char*);
	void Execute(SearchAlgos algo, int start, int dest);
	// 0 = adjlist
	// 1 = adjmatrix
	void Select(int type);
	void Display(SearchAlgos);
	void Stats(SearchAlgos algo, int type);
	void Save(SearchAlgos, int);

private:
	std::ofstream outputFile;

	AdjList adjlist;
	AdjMatrix adjmatrix;
	graph* graphType;
	SearchAlgorithms::Result curResult;

	// Start and end points for the timer
	std::chrono::high_resolution_clock::time_point begin;
	std::chrono::high_resolution_clock::time_point end;
	std::chrono::duration<double> time_span;
};

#endif SEARCH_H
