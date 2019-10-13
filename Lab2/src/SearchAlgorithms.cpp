#include "SearchAlgorithms.h"

#include <stack>
#include <queue>

tree<int>* SearchAlgorithms::path = new tree<int>();

tree<int>* SearchAlgorithms::runSearch(enum Algorithm::SearchAlgos algo, 
									graph& data, int start, int dest) {
	switch (algo) {
	case Algorithm::BFS:
		return BFS(data, start, dest);
	case Algorithm::DFS:
		return DFS(data, start, dest);
	case Algorithm::DIJKSTRA:
		return dijkstra(data, start, dest);
	case Algorithm::ASTAR:
		return aStar(data, start, dest);
	}
}

// Iterative
tree<int>* SearchAlgorithms::BFS(graph& data, int start, int dest) {
	std::queue<int> nodes;
	nodes.push(start);
	while (!nodes.empty()) {
		int curNode = nodes.front();
		nodes.pop();

		path->insert(curNode, data.getChildren(curNode));

		std::vector<int> children = data.getChildren(curNode);
		for (auto child : children)
			nodes.push(child);

		if (curNode == dest) {
			return path;
		}
	}
	return nullptr;
}

tree<int>* SearchAlgorithms::DFS(graph& data, int start, int dest) {
	std::stack<int> nodes;
	nodes.push(start);
	while (!nodes.empty()) {
		int curNode = nodes.top();
		nodes.pop();

		path->insert(curNode, data.getChildren(curNode));

		std::vector<int> children = data.getChildren(curNode);
		for (auto child : children)
			nodes.push(child);

		if (curNode == dest) {
			return path;
		}
	}
	return nullptr;
}

tree<int>* SearchAlgorithms::dijkstra(graph& data, int start, int dest) {
	return nullptr;
}

tree<int>* SearchAlgorithms::aStar(graph& data, int start, int dest) {
	return nullptr;
}