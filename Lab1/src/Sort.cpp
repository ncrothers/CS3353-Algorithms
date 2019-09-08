// Implementation of the Sort.h class

#include "Sort.h"
#include "SortAlgorithms.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

Sort::Sort() {
}

void Sort::clearData() {
	data.clear();
	std::vector<int> temp;
	for (int i = 0; i < 4; i++)
		data.push_back(temp);
}

void Sort::Load(const char filename[]) {
	curFile = filename;

	clearData();

	for (int i = 0; i < 4; i++) {
		std::ifstream file("files/" + curFile + "-" + std::to_string(counts[i]) + ".csv");
		std::string line;
		for (int j = 0; j < counts[i]; j++) {
			std::getline(file, line);
			data[i].push_back(std::stoi(line));
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++)
			std::cout << data[i][j] << ",";
		std::cout << std::endl << std::endl;
	}
}

void Sort::Execute() {
	// Loops through each of the 4 dataset sizes
	for (int i = 0; i < 4; i++)
		// Loops through each of the sorting algorithm types
		for (int j = SortAlgos::BUBBLE; j != SortAlgos::LAST; j++)
			SortAlgorithms::runSort(static_cast<SortAlgos>(j), data[i]);
}

void Sort::Display() {

}

void Sort::Stats() {

}

void Sort::Select() {

}

void Sort::Save() {

}

void Sort::Configure() {

}