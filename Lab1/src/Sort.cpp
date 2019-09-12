// Implementation of the Sort.h class

#include "Sort.h"
#include "SortAlgorithms.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

#define DISPLAY_AMOUNT 10

Sort::Sort() {
}

// Clears out the data before loading in new values
void Sort::clearData() {
	sortedData.clear();
	std::vector<int> temp;
	for (int i = 0; i < 4; i++) {
		sortedData.push_back(temp);
	}
}

// Copies the source data into the vectors that will store the sorted values
void Sort::copyData() {
	std::copy(data.begin(), data.end(), sortedData.begin());
}

void Sort::Load(const char filename[]) {
	curFile = filename;
	data.clear();
	std::vector<int> temp;
	for (int i = 0; i < 4; i++) {
		data.push_back(temp);
	}
	clearData();

	for (int i = 0; i < 4; i++) {
		std::ifstream file("files/" + curFile + "-" + std::to_string(counts[i]) + ".csv");
		std::string line;
		for (int j = 0; j < counts[i]; j++) {
			std::getline(file, line);
			data[i].push_back(std::stoi(line));
		}
	}

	copyData();
}

void Sort::Execute() {
	// Loops through each of the 4 dataset sizes
	for (int i = 0; i < 4; i++) {
		// Loops through each of the sorting algorithm types
		for (int j = SortAlgos::BUBBLE; j != SortAlgos::LAST; j++) {
			start = std::chrono::high_resolution_clock::now();
			SortAlgorithms::runSort(static_cast<SortAlgos>(j), sortedData[i]);
			end = std::chrono::high_resolution_clock::now();

			Display(static_cast<SortAlgos>(j), i);
			Save(static_cast<SortAlgos>(j), i);
			clearData();
			copyData();
		}
	}
}

void Sort::Display(SortAlgos algo, int size) {
	switch (algo) {
	case BUBBLE:
		std::cout << "Bubble Sort:" << std::endl;
		break;
	case INSERTION:
		std::cout << "Insertion Sort:" << std::endl;
		break;
	case MERGE:
		std::cout << "Merge Sort:" << std::endl;
		break;
	}

	std::cout << counts[size] << " values arranged as " << curFile << std::endl;

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

	std::cout	<< std::fixed << std::setprecision(10)
				<< "Time elapsed: " << time_span.count() << " seconds." << std::endl << std::endl;

}

void Sort::Save(SortAlgos algo, int size) {
	std::string sortAlgo;
	switch (algo) {
	case BUBBLE:
		sortAlgo = "bubble";
		break;
	case INSERTION:
		sortAlgo = "insertion";
		break;
	case MERGE:
		sortAlgo = "merge";
		break;
	}

	std::ofstream file("sorted_files/" + sortAlgo + "-sorted-" + curFile + "-" + std::to_string(counts[size]) + ".csv");
	for (int j = 0; j < sortedData[size].size(); j++)
		file << sortedData[size][j] << std::endl;
}