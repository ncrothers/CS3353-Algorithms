#include "Factory.h"

#include"TSP.h"

Algorithm* Factory::Create(Factory::TSPAlgos algo) {
	return new TSP(algo);
}