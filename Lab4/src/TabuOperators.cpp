#include "TabuOperators.h"

int TabuOperators::N;

void TabuOperators::configure(int _N) {
	N = _N;
}

void TabuOperators::selectNeighborhood(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood, TabuOperators::Neighborhood op) {
	switch (op) {
	case TabuOperators::Neighborhood::SWAP:
		selectSwap(source, neighborhood);
		break;
	}
}

void TabuOperators::selectSwap(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood) {
	int swapIndex = 1;

	while (swapIndex < N - 1) {
		neighborhood.push_back(std::vector<int>());
		swap(source, neighborhood[swapIndex - 1], swapIndex);
		swapIndex++;
	}
}

void TabuOperators::swap(std::vector<int>& source, std::vector<int>& dest, int index) {
	for (int i = 0; i < index; i++) {
		dest.push_back(source[i]);
	}

	dest.push_back(source[index + 1]);
	dest.push_back(source[index]);
	
	for (int i = index + 2; i < source.size(); i++) {
		dest.push_back(source[i]);
	}
}