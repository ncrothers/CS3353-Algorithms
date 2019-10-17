/*

Lab2
CS3353
Nicholas Crothers

*/

#include "Search.h"

#include <iostream>
#include <string>
#include <random>
#include <time.h>

std::vector<std::pair<int, int>> getRandomPoints(int bound);

int main(int argc, char* argv[]) {
	Search search;
	int bound = search.Load("data16/");
	std::vector<std::pair<int, int>> testPoints;
	if (argc == 3) {
		testPoints.push_back(std::make_pair<int, int>(std::stoi(argv[1]), std::stoi(argv[2])));
	}
	else {
		testPoints = getRandomPoints(bound);
	}

	for (int num = 0; num < testPoints.size(); num++) {
		num = num;
		for (int graphType = 0; graphType < 2; graphType++) {
			for (int algo = Algorithm::SearchAlgos::BFS; algo < Algorithm::END; algo++) {
				search.Select(graphType);
				search.Execute(static_cast<Algorithm::SearchAlgos>(algo), testPoints[num].first, testPoints[num].second);
				search.Stats(static_cast<Algorithm::SearchAlgos>(algo), graphType);
				search.Save(static_cast<Algorithm::SearchAlgos>(algo), graphType, testPoints[num].first, testPoints[num].second);
			}
		}
	}
	
	std::string stuff;
	std::getline(std::cin, stuff);

	return 0;
}

std::vector<std::pair<int, int>> getRandomPoints(int bound) {
	std::default_random_engine gen(time(nullptr));
	std::uniform_int_distribution<int> distribution(1, bound);
	std::vector<std::pair<int, int>> values;
	for (int i = 0; i < 100; i++) {
		values.push_back(std::make_pair<int, int>(distribution(gen), distribution(gen)));
	}
	return values;
}