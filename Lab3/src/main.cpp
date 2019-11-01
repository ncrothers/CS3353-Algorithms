#include "Factory.h"
#include "TSP.h"

int main(int argc, char** argv) {
	int start = 1;
	int size = 11;

	TSP* tsp = Factory::Create(Factory::NAIVEBF);

	tsp->Load("data/graph.txt");
	tsp->Execute(start, size);

	return 0;
}