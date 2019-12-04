#ifndef TABUOPS_H
#define TABUOPS_H

#include <vector>
#include <string>

class TabuOperators {
public:
	enum Neighborhood {
		SWAP = 0,
		INVERSION,
		LAST
	};

	static void configure(int _N);
	static void selectNeighborhood(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood, Neighborhood op);
	static std::string getNeighborhoodName(int type);

private:
	static int N;
	static void selectSwap(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood);
	static void selectInversion(std::vector<int>& source, std::vector<std::vector<int>>& neighborhood);

	// Helper functions
	static void swap(std::vector<int>& source, std::vector<int>& dest, int swap1, int swap2);
	static void invert(std::vector<int>& source, std::vector<int>& dest, int start, int end);
	static int findNode(std::vector<int>& source, int node);
};

#endif