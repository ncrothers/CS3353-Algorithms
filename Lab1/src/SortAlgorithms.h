// Class that includes all of the sorting algorithms used in the program

#ifndef SORTALGORITHMS_H
#define SORTALGORITHMS_H

#include "Algorithm.h"

#include <vector>

class SortAlgorithms {
public:
	static void runSort(enum Algorithm::SortAlgos, std::vector<int>&);
    static void bubbleSort(std::vector<int> &);
    static void insertionSort(std::vector<int> &);
    static void mergeSort(std::vector<int> &, int, int);

private:
    static unsigned int getLength(int* &);

};

#endif SORTALGORITHMS_H