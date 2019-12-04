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
	case TabuOperators::Neighborhood::INVERSION:
		selectInversion(source, neighborhood);
		break;
	}
}

std::string TabuOperators::getNeighborhoodName(int type) {
	switch (type) {
	case 0:
		return std::string("swap");
	case 1:
		return std::string("inversion");
	default:
		return std::string("unknown");
	}
}

void TabuOperators::selectSwap(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood) {

	//for (int node = 1; node < N - 1; node++) {
	//	neighborhood.push_back(std::vector<int>());
	//	swap(source, neighborhood.back(), findNode(source, node), findNode(source, node + 1));
	//}

	for (int swap1 = 1; swap1 < N - 1; swap1++) {
		for (int swap2 = swap1 + 1; swap2 < N; swap2++) {
			neighborhood.push_back(std::vector<int>());
			swap(source, neighborhood.back(), swap1, swap2);
		}
	}

	//for (int i = 1; i < N - 1; i++) {
	//	neighborhood.push_back(std::vector<int>());
	//	swap(source, neighborhood.back(), i, i + 1);
	//}
}

void TabuOperators::selectInversion(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood) {
	
	// Creates a neighbor for all tour with inverted subtours of all lengths anywhere in the tour
	for (int i = 1; i < N - 2; i++) {
		for (int j = i + 2; j < N; j++) {
			neighborhood.push_back(std::vector<int>());
			invert(source, neighborhood.back(), i, j);
		}
	}

	//for (int i = 1, j = N - 1; i < j; i++, j--) {
	//	neighborhood.push_back(std::vector<int>());
	//	invert(source, neighborhood[i - 1], i, j);
	//}
}

int TabuOperators::findNode(std::vector<int>& source, int node) {
	for (int i = 1; i < source.size(); i++) {
		if (source[i] == node)
			return i;
	}
}

void TabuOperators::swap(std::vector<int>& source, std::vector<int>& dest, int swap1, int swap2) {
	for (int i = 0; i < swap1; i++) {
		dest.push_back(source[i]);
	}

	dest.push_back(source[swap2]);

	for (int i = swap1 + 1; i < swap2; i++) {
		dest.push_back(source[i]);
	}

	dest.push_back(source[swap1]);

	for (int i = swap2 + 1; i < source.size(); i++) {
		dest.push_back(source[i]);
	}
}

void TabuOperators::invert(std::vector<int>& source, std::vector<int>& dest, int start, int end) {
	// Copies all before inversion point
	for (int i = 0; i < start; i++) {
		dest.push_back(source[i]);
	}

	// Copies inverted values
	for (int i = end; i >= start; i--) {
		dest.push_back(source[i]);
	}

	// Copies all after inversion point
	for (int i = end + 1; i < N; i++) {
		dest.push_back(source[i]);
	}
}