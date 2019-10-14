#include "SearchAlgorithms.h"

#include <stack>
#include <queue>
#include <set>
#include <map>

tree<int>* SearchAlgorithms::path = new tree<int>();

std::vector<int> SearchAlgorithms::runSearch(enum Algorithm::SearchAlgos algo,
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
std::vector<int> SearchAlgorithms::BFS(graph& data, int start, int dest) {
	std::queue<int> nodes;
	std::set<int> visited;
	nodes.push(start);
	while (!nodes.empty()) {
		int curNode = nodes.front();
		while (visited.count(curNode) != 0) {
			nodes.pop();
			curNode = nodes.front();
		}
		visited.insert(curNode);

		std::vector<graph::Node> childrenNodes = data.getChildren(curNode);

		std::vector<int> children;
		for (auto node : childrenNodes) {
			if (visited.count(node.data) == 0)
				children.push_back(node.data);
		}

		path->insert(curNode, children);

		for (auto child : childrenNodes)
			nodes.push(child.data);

		if (curNode == dest) {
			std::vector<int> finalPath = path->pathToRoot(curNode);
			path->clear();
			return finalPath;
		}
	}
	return std::vector<int>();
}

std::vector<int> SearchAlgorithms::DFS(graph& data, int start, int dest) {
	std::stack<int> nodes;
	std::set<int> visited;
	nodes.push(start);
	while (!nodes.empty()) {
		int curNode = nodes.top();
		while (visited.count(curNode) != 0) {
			nodes.pop();
			curNode = nodes.top();
		}
		visited.insert(curNode);

		std::vector<graph::Node> childrenNodes = data.getChildren(curNode);

		std::vector<int> children;
		for (auto node : childrenNodes) {
			if (visited.count(node.data) == 0)
				children.push_back(node.data);
		}

		try {
			path->insert(curNode, children);
		}
		catch (std::exception e) {
			
		}

		for (auto child : childrenNodes)
			nodes.push(child.data);

		if (curNode == dest) {
			std::vector<int> finalPath = path->pathToRoot(curNode);
			path->clear();
			return finalPath;
		}
	}
	return std::vector<int>();
}

std::vector<int> SearchAlgorithms::dijkstra(graph& data, int start, int dest) {
	// Stores all dynamically allocated nodes so they can be deleted later
	std::set<SearchNode*, NodeComp> nodes;

	// Stores the current leaves to search, with the lowest weight at the top
	std::priority_queue<SearchNode*, std::vector<SearchNode*>, WeightComp> leaves;

	// Stores the visited nodes
	std::map<int, SearchNode*> visited;

	leaves.push(new SearchNode(start, 0, nullptr));
	nodes.insert(leaves.top());
	int count = 0;
	while (!leaves.empty()) {
		count++;
		SearchNode* curNode = leaves.top();
		while (visited.count(curNode->data) != 0) {
			leaves.pop();
			curNode = leaves.top();
		}
		visited.try_emplace(curNode->data, curNode);

		std::vector<graph::Node> childrenNodes = data.getChildren(curNode->data);
		// Converts graph::Node to SearchNode
		std::vector<SearchNode*> children;
		for (auto node : childrenNodes) {
			children.push_back(new SearchNode(node.data, node.weight + curNode->totalWeight, curNode));
			nodes.insert(children.back());
		}

		// Transfers all nodes' int values into childrenInts.
		// When a duplicate it reached, it only keeps the SearchNode with the lower weight
		std::vector<int> childrenInts;
		for (auto node : children) {
			auto iter = visited.find(node->data);
			if (iter != visited.end()) {
				// If the previously visited node has a lower weight, indicate the child node is to be ignored
				if (iter->second->totalWeight < node->totalWeight) {
					node->setWeight(INT32_MAX);
					continue;
				}
				// Otherwise, remove the old node
				else {
					visited.erase(node->data);
				}
			}
			// Doesn't add nodes that have already been reached with a lower weight than this one's
			if (node->data != -1)
				childrenInts.push_back(node->data);
		}

		// Adds the children of the current node to the tree
		path->insert(curNode->data, childrenInts);

		for (auto child : children)
			leaves.push(child);

		if (curNode->data == dest) {
			std::vector<int> finalPath = path->pathToRoot(curNode->data);
			path->clear();
			for (auto node : nodes)
				delete node;
			return finalPath;
		}
	}
	for (auto node : nodes)
		delete node;
	return std::vector<int>();
}

std::vector<int> SearchAlgorithms::aStar(graph& data, int start, int dest) {
	return std::vector<int>();
}