#include "Factory.h"

#include "TSP.h"

TSP* Factory::Create(TSPAlgos algo) {
	return new TSP(algo);
}