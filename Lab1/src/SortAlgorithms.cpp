// Implementation of the SortAlgorithms class

#include "SortAlgorithms.h"

#include <list>

void merge(std::vector<int>&, int, int, int);

void SortAlgorithms::runSort(enum Algorithm::SortAlgos algo, std::vector<int> &arr) {
	switch (algo) {
	case Algorithm::BUBBLE:
		bubbleSort(arr);
		break;
	case Algorithm::INSERTION:
		insertionSort(arr);
		break;
	case Algorithm::MERGE:
		mergeSort(arr, 0, arr.size() - 1);
		break;
	default:
		break;
	}
}

void SortAlgorithms::bubbleSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++)
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
            else {
                continue;
            }
        }
}

void SortAlgorithms::insertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (arr[j] < arr[i] || j == 0) {
				int temp = arr[i];
				// Shifts all of the displaced values down
				for (int k = i; k > j; k--) {
					arr[k] = arr[k - 1];
				}
				arr[j] = temp;
			}
        }
    }
}

void SortAlgorithms::mergeSort(std::vector<int> &arr, int l, int r) {
	// Splits the vectors until they're at length 1
	if (l < r) {
		int m = (l + r) / 2;
		// Left half
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

void merge(std::vector<int>& arr, int l, int m, int r) {
	int lsize = m - l + 1;
	int rsize = r - m;

	int* left = new int[lsize];
	int* right = new int[rsize];

	for (int i = 0; i < lsize; i++)
		left[i] = arr[l + i];
	for (int i = 0; i < rsize; i++)
		right[i] = arr[m + i + 1];

	int lindex = 0;
	int rindex = 0;
	int arrindex = l;

	// Loop while both left and right arrays have values to check
	while (lindex < lsize && rindex < rsize) {
		if (left[lindex] < right[rindex])
			arr[arrindex++] = left[lindex++];
		else
			arr[arrindex++] = right[rindex++];
	}

	while (lindex < lsize)
		arr[arrindex++] = left[lindex++];

	while (rindex < rsize)
		arr[arrindex++] = right[rindex++];

	delete left, right;
}