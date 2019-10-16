#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMs_H

#include "Algorithm.h"
#include "graph.h"
#include "tree.h"

#include <queue>
#include <set>

class SearchAlgorithms {
public:
	struct SearchNode {
		SearchNode(size_t data, float totalWeight, SearchNode* parent, size_t time, float heuristic = 0) 
			: data(data), totalWeight(totalWeight), parent(parent), time(time), heuristic(heuristic) {}

		SearchNode(const SearchNode& rhs) 
			: data(rhs.data), totalWeight(rhs.totalWeight), parent(rhs.parent), 
			  time(rhs.time), heuristic(rhs.heuristic) {}

		float getTotalCost() const {
			return totalWeight + heuristic;
		}

		bool operator< (const SearchNode& rhs) {
			return data < rhs.data;
		}

		bool operator== (const SearchNode& rhs) {
			return data == rhs.data;
		}

		size_t data;
		size_t time;
		SearchNode* parent;
		float totalWeight;
		float heuristic;
	};
	// Stores all relevant information for the resulting path
	struct Result {
		// Case when a path isn't found
		Result() {
			totalCost = 0;
			totalDistance = 0;
			nodesExplored = 0;
		}

		Result(std::vector<int> path, float totalCost, float totalDistance, size_t nodesExplored) 
			: path(path), totalCost(totalCost), totalDistance(totalDistance), nodesExplored(nodesExplored) {}

		std::vector<int> path;
		float totalCost;
		float totalDistance;
		size_t nodesExplored;
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
			if (lhs->getTotalCost() == rhs->getTotalCost()) {
				return lhs->time > rhs->time;
			}
			return lhs->getTotalCost() > rhs->getTotalCost();
		}
	};
	// Runs the sorting algorithm based on what enum value was passed in
	static Result runSearch(enum Algorithm::SearchAlgos algo, graph& data, int start, int dest);
	static Result BFS(graph& data, int start, int dest);
	static Result DFS(graph& data, int start, int dest);
	static Result recurBFS(graph& data, int start, int dest);
	static Result recurDFS(graph& data, int start, int dest);
	static Result dijkstra(graph& data, int start, int dest);
	static Result aStar(graph& data, int start, int dest);

private:
	static bool recurBFS(graph& data, int dest, std::queue<int>& nodes);
	static bool recurDFS(graph& data, int cur, int dest, std::vector<bool>& visited);
	static bool validPtr(graph& data, SearchNode* ptr);
	static float getHeuristic(graph& data, int cur, int dest);
	static float getTotalDistance(graph& data, SearchNode* end);
	static float getTotalDistance(graph& data, std::vector<int>& end);
	static void reset(size_t size);

	static std::vector<bool> visited;
	static std::vector<bool> onTree;
	static size_t nodesExplored;
	static tree<int>* path;
};

#endif SEARCHALGORITHMS_H