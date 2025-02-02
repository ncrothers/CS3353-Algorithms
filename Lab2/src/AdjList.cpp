#include "AdjList.h"

AdjList::AdjList() {

}

AdjList::AdjList(size_t size) {
	reserve(size);
}

AdjList::~AdjList() {

}

void AdjList::reserve(size_t size) {
	if (data.size() == 0) {
		data.reserve(size);
		for (int i = 0; i < size; i++)
			data.push_back(Node(i + 1));
	}
	graphSize = size;
}

void AdjList::insert(size_t insert_location, size_t value) {
	if (insert_location > data.size())
		return;

	Node* newNode = new Node(value);
	data[insert_location - 1].neighbors.push_back(newNode);
}

void AdjList::setWeight(size_t start, size_t end, float weight) {
	if (start > data.size())
		return;
	// Checks if the end node is a neighbor of the start point
	int index = -1;
	for (int i = 0; i < data[start - 1].neighbors.size(); i++) {
		if (data[start - 1].neighbors[i]->data == end) {
			index = i;
			break;
		}
	}
	if (index == -1)
		return;
	
	data[start - 1].neighbors[index]->weight = weight;
}

std::vector<graph::Node*> AdjList::getChildren(size_t parent) const {
	std::vector<Node*> children;
	for (auto child : data[parent - 1].neighbors)
		children.push_back(child);
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