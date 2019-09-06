// Implementation of the Sort.h class

#include "Sort.h"
#include "SortAlgorithms.h"

#include <iostream>

void Sort::testSort() {
	std::vector<int> arr;
    for (int i = 9; i >= 0; i--)
        arr.push_back(i);

    SortAlgorithms::mergeSort(arr, 0, arr.size() - 1);

	for (int i = 0; i < 10; i++)
		std::cout << arr[i];
}