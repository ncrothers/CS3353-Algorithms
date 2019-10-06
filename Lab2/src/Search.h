#ifndef SEARCH_H
#define SEARCH_H
#include "Algorithm.h"

#include <string>
#include <vector>
#include <chrono>

class Search : public Algorithm {
public:

	Search();

	virtual void Load(const char[]);
	virtual void Execute();
	virtual void Display(SearchAlgos, int);
	virtual void Save(SearchAlgos, int);

private:

	// Stores which type of data is currently loaded
	std::string curFile;

	// Stores the four dataset sizes for looping
	int counts[4] = { 10, 1000, 10000, 100000 };

	// Start and end points for the timer
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
};

#endif SEARCH_H
