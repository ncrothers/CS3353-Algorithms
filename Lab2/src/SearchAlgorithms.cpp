#include "SearchAlgorithms.h"

#include <stack>
#include <iostream>
#include <math.h>

tree<int>* SearchAlgorithms::path = new tree<int>();
size_t SearchAlgorithms::nodesExplored = 0;
std::vector<bool> SearchAlgorithms::visited;
std::vector<bool> SearchAlgorithms::onTree;

void SearchAlgorithms::reset(size_t size) {
	nodesExplored = 0;
	visited.clear();
	onTree.clear();
	visited.reserve(size);
	onTree.reserve(size);
	for (int i = 0; i <= size; i++) {
		onTree.push_back(false);
		visited.push_back(false);
	}
	path->clear();
}

SearchAlgorithms::Result SearchAlgorithms::runSearch(enum Algorithm::SearchAlgos algo,
									graph& data, int start, int dest) {
	reset(data.getSize());

	switch (algo) {
	case Algorithm::BFS:
		return BFS(data, start, dest);
	case Algorithm::DFS:
		return DFS(data, start, dest);
	case Algorithm::RECURBFS:
		return recurBFS(data, start, dest);
	case Algorithm::RECURDFS:
		return recurDFS(data, start, dest);
	case Algorithm::DIJKSTRA:
		return dijkstra(data, start, dest);
	case Algorithm::ASTAR:
		return aStar(data, start, dest);
	}
}

// Iterative
SearchAlgorithms::Result SearchAlgorithms::BFS(graph& data, int start, int dest) {
	std::queue<int> nodes;
	for (int i = 0; i <= data.getSize(); i++)
		visited[i] = false;

	nodes.push(start);
	while (!nodes.empty()) {
		int curNode = nodes.front();
		nodes.pop();
		visited[curNode] = true;
		nodesExplored++;

		if (curNode == dest) {
			std::vector<int> finalPath = path->pathToRoot(curNode);
			return Result(finalPath, 0, getTotalDistance(data, finalPath), nodesExplored);
		}

		std::vector<graph::Node*> childrenNodes = data.getChildren(curNode);

		std::vector<int> children;
		for (auto node : childrenNodes) {
			if (!visited[node->data]) {
				children.push_back(node->data);
				onTree[node->data] = true;
			}
		}

		path->insert(curNode, children);

		for (auto child : children) {
			nodes.push(child);
			visited[child] = true;
		}
	}
	return Result();
}

SearchAlgorithms::Result SearchAlgorithms::recurBFS(graph& data, int start, int dest) {
	std::queue<int> nodes;
	for (int i = 0; i <= data.getSize(); i++)
		visited.push_back(false);
	nodes.push(start);

	if (recurBFS(data, dest, nodes)) {
		std::vector<int> finalPath = path->pathToRoot(dest);
		return Result(finalPath, 0, getTotalDistance(data, finalPath), nodesExplored);
	}
	return Result();
}

bool SearchAlgorithms::recurBFS(graph& data, int dest, std::queue<int>& nodes) {
	if (nodes.empty())
		return false;
	int cur = nodes.front();
	nodes.pop();
	visited[cur] = true;
	nodesExplored++;

	if (cur == dest) {
		visited[0] = true;
		return true;
	}
	std::vector<graph::Node*> childrenNodes = data.getChildren(cur);

	std::vector<int> children;
	for (auto node : childrenNodes) {
		if (!visited[node->data]) {
			children.push_back(node->data);
			onTree[node->data] = true;
			visited[node->data] = true;
			nodes.push(node->data);
		}
	}
	path->insert(cur, children);

	for (auto node : children) {
		recurBFS(data, dest, nodes);
		if (visited[0])
			return true;
	}
	return false;
}

SearchAlgorithms::Result SearchAlgorithms::DFS(graph& data, int start, int dest) {
	std::stack<int> nodes;
	nodes.push(start);
	while (!nodes.empty()) {
		int curNode = nodes.top();
		nodes.pop();
		visited[curNode] = true;
		nodesExplored++;
		if (curNode == dest) {
			std::vector<int> finalPath = path->pathToRoot(curNode);
			return Result(finalPath, 0, getTotalDistance(data, finalPath), nodesExplored);
		}

		std::vector<graph::Node*> childrenNodes = data.getChildren(curNode);

		std::vector<int> children;
		for (auto node : childrenNodes) {
			if (!visited[node->data] && !onTree[node->data]) {
				children.push_back(node->data);
				onTree[node->data] = true;
			}
		}

		try {
			path->insert(curNode, children);
		}
		catch (std::exception e) {
			
		}

		for (auto child : children) {
			nodes.push(child);
			visited[child] = true;
		}
	}
	return Result();
}

SearchAlgorithms::Result SearchAlgorithms::recurDFS(graph& data, int start, int dest) {
	for (int i = 0; i <= data.getSize(); i++)
		visited.push_back(false);
	if (recurDFS(data, start, dest, visited)) {
		std::vector<int> finalPath = path->pathToRoot(dest);
		return Result(finalPath, 0, getTotalDistance(data, finalPath), nodesExplored);
	}
	return Result();
}

bool SearchAlgorithms::recurDFS(graph& data, int cur, int dest, std::vector<bool>& visited) {
	visited[cur] = true;
	nodesExplored++;
	if (cur == dest) {
		visited[0] = true;
		return true;
	}
	std::vector<graph::Node*> childrenNodes = data.getChildren(cur);

	std::vector<int> children;
	for (auto node : childrenNodes) {
		if (!onTree[node->data]) {
			children.push_back(node->data);
			onTree[node->data] = true;
		}
	}
	path->insert(cur, children);

	for (int i = children.size() - 1; i >= 0; i--) {
		if (!visited[children[i]]) {
			visited[children[i]] = true;
			recurDFS(data, children[i], dest, visited);
			if (visited[0])
				return true;
		}
}
	return false;
}

SearchAlgorithms::Result SearchAlgorithms::dijkstra(graph& data, int start, int dest) {
	size_t nodesExplored = 0;

	// Stores all dynamically allocated nodes so they can be deleted later
	std::vector<SearchNode*> nodes;
	for (int i = 0; i <= data.getSize(); i++)
		nodes.push_back(nullptr);

	// Stores the current leaves to search, with the lowest weight at the top
	std::priority_queue<SearchNode*, std::vector<SearchNode*>, WeightComp> leaves;

	// Stores the visited nodes
	std::vector<bool> visited;
	for (int i = 0; i <= data.getSize(); i++) {
		visited.push_back(false);
	}

	leaves.push(new SearchNode(start, 0, nullptr, 0));
	nodes[leaves.top()->data] = leaves.top();
	int time = 0;
	while (!leaves.empty()) {
		SearchNode* curNode = leaves.top();
		leaves.pop();
		// Skips the previously invalidated pointers
		if (!validPtr(data, curNode))
			continue;

		if (curNode->data == dest) {
			Result result(path->pathToRoot(curNode->data, curNode ? curNode->parent->data : 1), 
						  curNode->totalWeight, getTotalDistance(data, curNode), nodesExplored);
			for (auto node : nodes)
				delete node;
			return result;
		}

		if (visited[curNode->data]) {
			// If existing node has a lower weight, skip this node
			if (nodes[curNode->data]->totalWeight <= curNode->totalWeight)
				continue;

			SearchNode* temp = nodes[curNode->data];
			nodes[curNode->data] = curNode;
			delete temp;
		}

		visited[curNode->data] = true;
		nodesExplored++;

		std::vector<graph::Node*> childrenNodes = data.getChildren(curNode->data);
		// Converts graph::Node to SearchNode
		std::vector<SearchNode*> children;
		for (auto node : childrenNodes) {
			if (curNode->parent == nullptr || node->data != curNode->parent->data) {
				if (!onTree[node->data]) {
					onTree[node->data] = true;
					children.push_back(new SearchNode(node->data, node->weight + curNode->totalWeight, curNode, time));
					nodes[children.back()->data] = children.back();
					time++;
				}
			}
		}

		// Transfers all nodes' int values into childrenInts.
		// When a duplicate it reached, it only keeps the SearchNode with the lower weight
		std::vector<int> childrenInts;
		for (auto node : children) {
			childrenInts.push_back(node->data);
		}

		// Adds the children of the current node to the tree
		path->insert(curNode->data, childrenInts);

		for (int i = 0; i < children.size(); i++) {
			leaves.push(children[i]);
		}
	}

	for (auto node : nodes) {
		if (node)
			delete node;
	}
	return Result();
}

bool SearchAlgorithms::validPtr(graph& data, SearchNode* ptr) {
	if (ptr->data > data.getSize())
		return false;
	try {
		ptr->parent->data;
		return true;
	}
	catch (std::exception e) {
		return false;
	}
}

SearchAlgorithms::Result SearchAlgorithms::aStar(graph& data, int start, int dest) {
	size_t nodesExplored = 0;
	// Stores all dynamically allocated nodes so they can be deleted later
	std::vector<SearchNode*> nodes;
	for (int i = 0; i <= data.getSize(); i++)
		nodes.push_back(nullptr);

	// Stores the current leaves to search, with the lowest weight at the top
	std::priority_queue<SearchNode*, std::vector<SearchNode*>, WeightComp> leaves;

	// Stores the visited nodes
	std::vector<bool> visited;
	for (int i = 0; i <= data.getSize(); i++) {
		visited.push_back(false);
	}

	leaves.push(new SearchNode(start, 0, nullptr, 0));
	nodes[leaves.top()->data] = leaves.top();
	int time = 0;
	while (!leaves.empty()) {
		SearchNode* curNode = leaves.top();
		leaves.pop();
		// Skips the previously invalidated pointers
		if (!validPtr(data, curNode))
			continue;

		if (visited[curNode->data]) {
			// If existing node has a lower weight, skip this node
			if (nodes[curNode->data]->totalWeight <= curNode->totalWeight)
				continue;

			SearchNode* temp = nodes[curNode->data];
			nodes[curNode->data] = curNode;
			delete temp;
		}

		visited[curNode->data] = true;
		nodesExplored++;

		std::vector<graph::Node*> childrenNodes = data.getChildren(curNode->data);
		// Converts graph::Node to SearchNode
		std::vector<SearchNode*> children;
		for (auto node : childrenNodes) {
			if (curNode->parent == nullptr || node->data != curNode->parent->data) {
				if (!onTree[node->data]) {
					onTree[node->data] = true;
					children.push_back(new SearchNode(node->data, node->weight + curNode->totalWeight,
						curNode, time, getHeuristic(data, node->data, dest)));
					nodes[children.back()->data] = children.back();
					time++;
				}
			}
		}

		// Transfers all nodes' int values into childrenInts.
		// When a duplicate it reached, it only keeps the SearchNode with the lower weight
		std::vector<int> childrenInts;
		for (auto node : children) {
			if (node->data != -1)
				childrenInts.push_back(node->data);
		}

		// Adds the children of the current node to the tree
		path->insert(curNode->data, childrenInts);

		for (int i = 0; i < children.size(); i++) {
			leaves.push(children[i]);
		}

		if (curNode->data == dest) {
			Result result(path->pathToRoot(curNode->data, curNode->parent ? curNode->parent->data : 1), 
						  curNode->totalWeight, getTotalDistance(data, curNode), nodesExplored);
			for (auto node : nodes)
				delete node;
			return result;
		}
	}
	for (auto node : nodes) {
		if (node)
			delete node;
	}
	return Result();
}

float SearchAlgorithms::getTotalDistance(graph& data, SearchNode* end) {
	float totalDistance = 0;
	while (end->parent) {
		totalDistance += getHeuristic(data, end->parent->data, end->data);
		end = end->parent;
	}
	return totalDistance;
}

float SearchAlgorithms::getTotalDistance(graph& data, std::vector<int>& path) {
	float totalDistance = 0;
	for (int i = path.size() - 1; i > 0; i--) {
		totalDistance += getHeuristic(data, path[i - 1], path[i]);
	}
	return totalDistance;
}

float SearchAlgorithms::getHeuristic(graph& data, int cur, int dest) {
	graph::Position curPos = data.getPos(cur);
	graph::Position destPos = data.getPos(dest);

	return (pow(destPos.x - curPos.x, 2) + pow(destPos.y - curPos.y, 2) + pow(destPos.z - curPos.z, 2));
}