/*

Lab1
CS3353
Nicholas Crothers

*/

#include "Sort.h"

#include <iostream>

int main() {
	// Stores the different data type identifier for the input files to loop through
	char const* files[4] = { "random", "reversed", "semi-random", "semi-unique" };

	Sort sorter;
	for (int i = 1; i < 4; i++) {
		sorter.Load(files[i]);
		sorter.Execute();
	}

    return 0;
}