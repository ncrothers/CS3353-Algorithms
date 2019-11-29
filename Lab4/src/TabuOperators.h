#ifndef TABUOPS_H
#define TABUOPS_H

#include <vector>

class TabuOperators {
public:
	enum class Neighborhood {
		SWAP
	};

	static void configure(int _N);
	static void selectNeighborhood(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood, Neighborhood op);

private:
	static int N;
	static void selectSwap(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood);
	static void swap(std::vector<int>& source, std::vector<int>& dest, int index);
};

#endif