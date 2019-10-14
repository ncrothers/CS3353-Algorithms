#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMs_H

#include "Algorithm.h"
#include "graph.h"
#include "tree.h"

class SearchAlgorithms {
public:
	struct SearchNode {
		SearchNode(size_t data, size_t totalWeight, SearchNode* parent) 
			: data(data), totalWeight(totalWeight), parent(parent) {}

		SearchNode(const SearchNode& rhs) 
			: data(rhs.data), totalWeight(rhs.totalWeight), parent(rhs.parent) {}

		void setWeight(size_t _weight) {
			totalWeight = _weight;
		}

		bool operator< (const SearchNode& rhs) {
			return data < rhs.data;
		}

		bool operator== (const SearchNode& rhs) {
			return data == rhs.data;
		}

		size_t data;
		SearchNode* parent;
		size_t totalWeight;
	};
	// Used for storage in a container sorted by data, like a set.
	struct NodeComp {
		bool operator() (const SearchNode* lhs, const SearchNode* rhs) const {
			return lhs->data < rhs->data;
		}
	};
	// Used for storage in the priority queue, allows sorting by weight
	struct WeightComp {
		bool operator() (const SearchNode* lhs, const SearchNode* rhs) const {
			return lhs->totalWeight < rhs->totalWeight;
		}
	};
	// Runs the sorting algorithm based on what enum value was passed in
	static std::vector<int> runSearch(enum Algorithm::SearchAlgos algo, graph& data, int start, int dest);
	static std::vector<int> BFS(graph& data, int start, int dest);
	static std::vector<int> DFS(graph& data, int start, int dest);
	static std::vector<int> dijkstra(graph& data, int start, int dest);
	static std::vector<int> aStar(graph& data, int start, int dest);

private:
	static tree<int>* path;
};

#endif SEARCHALGORITHMS_H