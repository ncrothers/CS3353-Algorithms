#ifndef SEARCH_H
#define SEARCH_H
#include "Algorithm.h"
#include "AdjList.h"
#include "AdjMatrix.h"

#include <string>
#include <vector>
#include <chrono>

class Search : public Algorithm {
public:

	Search();

	void Load(const char*);
	void Execute();
	void Display(SearchAlgos);
	void Save(SearchAlgos, int);

private:

	// Stores which type of data is currently loaded
	std::string curFile;

	AdjList adjlist;
	AdjMatrix adjmatrix;

	// Stores the four dataset sizes for looping
	int counts[4] = { 10, 1000, 10000, 100000 };

	// Start and end points for the timer
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
};

#endif SEARCH_H
