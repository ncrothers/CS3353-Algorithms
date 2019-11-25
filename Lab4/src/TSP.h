#ifndef TSP_H
#define TSP_H

#include "Factory.h"
#include "FileHandler.h"
#include "TSPAlgorithm.h"

#include <vector>
#include <chrono>

class TSP {
public:
	TSP(Factory::TSPAlgos algo);

	int Load(const char* filePath);
	// set up this way to allow the same Configure function for both Tabu and Genetic
	void Configure(int opType1, int opType2, int opType3 = -1, int populationSize = -1);
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