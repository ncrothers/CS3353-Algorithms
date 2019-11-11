#ifndef TSP_H
#define TSP_H

#include "Factory.h"
#include "NaiveBF.h"
#include "DynamicP.h"
#include "FileHandler.h"

#include <vector>

class TSP {
public:
	TSP(Factory::TSPAlgos algo);

	int Load(const char* filePath);
	void Execute(int start, int size);
	void Stats();
	void Save(const char* filePath, int sizeStart);

private:
	TSPAlgorithm* algoObj;
	std::chrono::high_resolution_clock::time_point begin;
	std::chrono::high_resolution_clock::time_point end;
	std::vector<float> execTimes;
	std::vector<float> tourDistances;
};

#endif