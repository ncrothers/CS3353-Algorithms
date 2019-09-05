// Implementation of the SortAlgorithms class

#include "SortAlgorithms.h"

void SortAlgorithms::bubbleSort(int* &arr) {
    unsigned int len = getLength(arr);

    for (int i = 0; i < len; i++)
        for (int j = i; j < len - 1; j++) {
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

void SortAlgorithms::insertionSort(int* &arr) {
    unsigned int len = getLength(arr);

    unsigned int minIndex = 0;

    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void SortAlgorithms::mergeSort(int* &arr) {

}

unsigned int SortAlgorithms::getLength(int* &arr) {
    return sizeof(arr) / sizeof(arr[0]);
}