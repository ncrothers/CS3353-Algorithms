#ifndef TSP_H
#define TSP_H

#include "Algorithm.h"
#include "NaiveBF.h"
#include "DynamicP.h"

class TSP : public Algorithm {
public:
	TSP(Factory::TSPAlgos algo);

	int Load(const char* filePath);
	void Execute(Factory::TSPAlgos algo, int start, int dest);
	void Select(int type);
	void Display(Factory::TSPAlgos);
	void Stats(Factory::TSPAlgos algo, int type);
	void Save(Factory::TSPAlgos, int, int, int);

private:
	
};

#endif