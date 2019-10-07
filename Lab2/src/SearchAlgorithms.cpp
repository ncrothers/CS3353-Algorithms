#include "SearchAlgorithms.h"

#include <stack>
#include <queue>

tree<int> SearchAlgorithms::runSearch(enum Algorithm::SearchAlgos algo, 
									graph<int>& data, int start, int dest) {
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
tree<int> SearchAlgorithms::BFS(graph<int>& data, int start, int dest) {
	std::queue<int> nodes;
	nodes.push(start);
	while (!nodes.empty()) {
		int curNode = nodes.front();
		nodes.pop();

		path.insert(curNode, data.getChildren(curNode));

		std::vector<int> children = data.getChildren(curNode);
		for (auto child : children)
			nodes.push(child);

		if (curNode == dest) {
			return path;
		}
	}
	tree<int> emptyPath;
	return emptyPath;
}

tree<int> SearchAlgorithms::DFS(graph<int>& data, int start, int dest) {
	std::stack<int> nodes;
	nodes.push(start);
	while (!nodes.empty()) {
		int curNode = nodes.top();
		nodes.pop();

		path.insert(curNode, data.getChildren(curNode));

		std::vector<int> children = data.getChildren(curNode);
		for (auto child : children)
			nodes.push(child);

		if (curNode == dest) {
			return path;
		}
	}
	tree<int> emptyPath;
	return emptyPath;
}

tree<int> SearchAlgorithms::dijkstra(graph<int>& data, int start, int dest) {

}

tree<int> SearchAlgorithms::aStar(graph<int>& data, int start, int dest) {

}