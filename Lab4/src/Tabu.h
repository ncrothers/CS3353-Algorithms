
#ifndef TABU_H
#define TABU_H

#include "TSPAlgorithm.h"
class Tabu : public TSPAlgorithm {
	void startAlgo(int _start, int _N, int _populationSize, Crossover coType, Mutation mutType);
	std::string getTypeName();
};

#endif