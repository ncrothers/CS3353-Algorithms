/*

Lab2
CS3353
Nicholas Crothers

*/

#include "Algorithm.h"
#include "Search.h"

#include <iostream>

int main(int argc, char* argv[]) {

	Search search;
	search.Load("data16/");
	search.Display(Algorithm::SearchAlgos::BFS);

	std::string stuff;
	std::getline(std::cin, stuff);

	return 0;
}