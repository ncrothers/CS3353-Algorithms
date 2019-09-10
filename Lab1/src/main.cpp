/*

Lab1
CS3353
Nicholas Crothers

*/

#include "Sort.h"
#include <iostream>

int main() {
	char* files[4] = { "random", "reversed", "semi-random", "semi-unique" };

	Sort sorter;
	for (int i = 0; i < 4; i++) {
		sorter.Load(files[i]);
		sorter.Execute();
	}

	std::string bla;
	std::cin >> bla;

    return 0;
}