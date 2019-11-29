
#ifndef TABU_H
#define TABU_H

#include "TSPAlgorithm.h"
#include "TabuOperators.h"
#include "ring_buffer.h"

class Tabu : public TSPAlgorithm {
public:
	~Tabu();
	void configure(int opType1, int bufferSize, int opType3 = -1, int populationSize = -1);
	void startAlgo(int _start, int _N);
	void generateStart(std::vector<int>& node);

	void calculateNeighborhoodFitness(std::vector<std::vector<int>>& neighborhood, std::vector<float>& fitness);
	float calculateDistance(std::vector<int>& node);
	void updateBest(std::vector<int>& tour, float distance);

	void selectNeighborhood(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood);
	std::string getTypeName();

private:
	int tabuListSize;
	int iterationCount = 100;
	TabuOperators::Neighborhood hoodOp;
	ring_buffer<std::vector<int>>* buffer = nullptr;

};

#endif