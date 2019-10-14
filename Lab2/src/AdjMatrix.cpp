#include "AdjMatrix.h"

AdjMatrix::AdjMatrix() {

}

AdjMatrix::AdjMatrix(size_t size) {
	this->data.reserve(size);
	
	for (auto row : this->data) {
		row.reserve(size);
	}
}

void AdjMatrix::reserve(size_t size) {
	if (this->data.size() == 0) {
		data.reserve(size);

		for (auto row : this->data) {
			row.reserve(size);
		}
	}
	for (int i = 0; i < size; i++) {
		data.push_back(std::vector<Node>());
		for (int y = 0; y < size; y++)
			data[i].push_back(Node(0));
	}
}

void AdjMatrix::insert(size_t insert_location, size_t value) {
	if (insert_location > data.size())
		return;
	if (value > data[insert_location - 1].size())
		return;

	data[insert_location - 1][value - 1].data = value;
}

void AdjMatrix::setWeight(size_t insert_location, size_t value, float weight) {
	if (insert_location > data.size())
		return;
	if (value > data[insert_location - 1].size())
		return;

	data[insert_location - 1][value - 1].weight = weight;
}

std::vector<graph::Node> AdjMatrix::getChildren(size_t parent) const {
	std::vector<Node> children;
	
	for (auto child : this->data[parent - 1])
		if (child.data != 0)
			children.push_back(child);

	return children;
}

float AdjMatrix::getWeight(size_t start, size_t end) const {
	if (start > data.size() || 
		end > data[start - 1].size())
		return -1;
	
	return data[start][end].weight;
}