/*

Lab2
CS3353
Nicholas Crothers

*/

#include "Search.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	int start, dest;
	start = std::stoi(argv[1]);
	dest = std::stoi(argv[2]);

	Search search;
	search.Load("data100/");
	for (int i = 0; i < 2; i++) {
		for (int algo = Algorithm::SearchAlgos::BFS; algo < Algorithm::END; algo++) {
			search.Select(i);
			search.Execute(static_cast<Algorithm::SearchAlgos>(algo), start, dest);
			search.Stats(static_cast<Algorithm::SearchAlgos>(algo), i);
		}
	}

	std::string stuff;
	std::getline(std::cin, stuff);

	return 0;
}