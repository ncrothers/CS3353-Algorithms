// Implementation of the Sort.h class

#include "Sort.h"
#include "SortAlgorithms.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

Sort::Sort() {
	
}

void Sort::Load(const char filename[]) {
	curFile = filename;
	data.clear();

	std::vector<int> temp;
	for (int i = 0; i < 4; i++)
		data.push_back(temp);

	for (int i = 0; i < 4; i++) {
		std::ifstream file("files/random-" + std::to_string(counts[i]) + ".csv");
		std::string line;
		for (int j = 0; j < counts[i]; j++) {
			std::getline(file, line);
			data[i].push_back(std::stoi(line));
		}
	}

	for (int i = 0; i < counts[1]; i++)
		std::cout << data[1][i] << std::endl;
}

void Sort::Execute() {

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