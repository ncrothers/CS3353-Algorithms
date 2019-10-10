#include "AdjList.h"

AdjList::AdjList(size_t size) {
	data.reserve(size);
}

void AdjList::insert(size_t insert_location, size_t value, float weight) {
	if (insert_location > data.size())
		return;

	Node* newNode = new Node(value, weight);
	data[insert_location - 1].neighbors.push_back(newNode);
}

std::vector<int> AdjList::getChildren(size_t parent) const {
	std::vector<int> children;
	for (auto child : data[parent - 1].neighbors)
		children.push_back(child->data);
	return children;
}

float AdjList::getWeight(size_t start, size_t end) const {
	if (start > data.size())
		return -1;

	for (auto node : data[start - 1].neighbors)
		if (node->data == end)
			return node->weight;

	return -1;
}