#include "Factory.h"
#include "TSP.h"

#include <iostream>

int main(int argc, char** argv) {
	int start = 1;
	int sizeStart = 6;
	int sizeEnd = 8;

	TSP* naive = Factory::Create(Factory::NAIVEBF);
	TSP* dynam = Factory::Create(Factory::DP);

	naive->Load("data/graph.txt");
	dynam->Load("data/graph.txt");

	for (int size = 9; size <= 9; size++) {
		std::cout << size << "..." << std::endl;
		//naive->Execute(start, size);
		//naive->Stats();
		dynam->Execute(start, size);
		dynam->Stats();
	}
	//naive->Save("data/naive.csv", sizeStart);
	dynam->Save("data/dynamicp.csv", sizeStart);

	return 0;
}