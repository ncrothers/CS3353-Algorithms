#ifndef TSP_H
#define TSP_H

#include "Factory.h"
#include "NaiveBF.h"
#include "DynamicP.h"
#include "Parser.h"

class TSP {
public:
	TSP(Factory::TSPAlgos algo);

	int Load(const char* filePath);
	void Execute(int start, int size);
	void Select(int type);
	void Display(Factory::TSPAlgos);
	void Stats(Factory::TSPAlgos algo, int type);
	void Save(Factory::TSPAlgos, int, int, int);

private:
	TSPAlgorithm* algoObj;
};

#endif