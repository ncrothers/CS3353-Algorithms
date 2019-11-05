#include "Factory.h"
#include "TSP.h"

int main(int argc, char** argv) {
	int start = 1;
	int size = 11;

	TSP* naive = Factory::Create(Factory::NAIVEBF);
	TSP* dynam = Factory::Create(Factory::DP);

	naive->Load("data/graph.txt");
	naive->Execute(start, size);

	dynam->Load("data/graph.txt");
	dynam->Execute(start, size);

	return 0;
}