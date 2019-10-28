/*

Abstract Algorithm class

*/

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Factory.h"

class Algorithm {
public:

    virtual int Load(const char* filePath) = 0;
    virtual void Execute(Factory::TSPAlgos algo, int start, int dest) = 0;
	virtual void Select(int type) = 0;
    virtual void Display(Factory::TSPAlgos) = 0;
	virtual void Stats(Factory::TSPAlgos algo, int type) = 0;
    virtual void Save(Factory::TSPAlgos, int, int, int) = 0;
};

#endif ALGORITHM_H