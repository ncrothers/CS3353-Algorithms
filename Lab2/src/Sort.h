// Class that handles any call to a sort

#ifndef SORT_H
#define SORT_H

#include "Algorithm.h"

#include <string>
#include <vector>
#include <chrono>

class Sort : public Algorithm {
public:

	Sort();

	virtual void Load(const char[]);
	virtual void Execute();
	virtual void Display(SortAlgos, int);
	virtual void Save(SortAlgos, int);

private:
	void clearData();
	// Copies the source vectors into the vectors that will be operated on
	void copyData();

	// Stores which type of data is currently loaded
	std::string curFile;
	// Stores the unsorted data
	std::vector<std::vector<int>> data;
	// Stores the sorted data from the previous vector
	std::vector<std::vector<int>> sortedData;

	// Stores the four dataset sizes for looping
	int counts[4] = { 10, 1000, 10000, 100000 };

	// Start and end points for the timer
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
};

#endif SORT_H