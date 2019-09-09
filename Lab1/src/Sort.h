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
	virtual void Stats();
	virtual void Select();
	virtual void Save();
	virtual void Configure();

private:
	void clearData();
	// Copies the source vectors into the vectors that will be operated on
	void copyData();

	std::string curFile;
	std::vector<std::vector<int>> data;
	std::vector<std::vector<int>> sortedData;
	int counts[4] = { 10, 1000, 10000, 100000 };

	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
};

#endif SORT_H