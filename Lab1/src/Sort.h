// Class that handles any call to a sort

#ifndef SORT_H
#define SORT_H

#include "Algorithm.h"

#include <string>
#include <vector>

class Sort : public Algorithm{
public:

	Sort();

	virtual void Load(const char[]);
	virtual void Execute();
	virtual void Display();
	virtual void Stats();
	virtual void Select();
	virtual void Save();
	virtual void Configure();

private:
	void clearData();

	std::string curFile;
	std::vector<std::vector<int>> data;
	std::vector<std::vector<int>> sortedData;
	int counts[4] = { 10, 1000, 10000, 100000 };
};

#endif SORT_H