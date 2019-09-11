// Class that includes all of the sorting algorithms used in the program

#ifndef SORTALGORITHMS_H
#define SORTALGORITHMS_H

#include "Algorithm.h"

#include <vector>

class SortAlgorithms {
public:
	// Runs the sorting algorithm based on what enum value was passed in
	static void runSort(enum Algorithm::SortAlgos, std::vector<int>&);
    static void bubbleSort(std::vector<int> &);
    static void insertionSort(std::vector<int> &);
    static void mergeSort(std::vector<int> &, int, int);
};

#endif SORTALGORITHMS_H