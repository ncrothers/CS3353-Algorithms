
#ifndef TABU_H
#define TABU_H

#include "TSPAlgorithm.h"

class Tabu : public TSPAlgorithm {
	void startAlgo(int _start, int _N);
	void configure(int opType1, int opType2, int opType3 = -1, int populationSize = -1);
	std::string getTypeName();
};

#endif