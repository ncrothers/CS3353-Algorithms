#include "AdjMatrix.h"

AdjMatrix::AdjMatrix(size_t size) {
	this->data.reserve(size);
	
	for (auto row : this->data) {
		row.reserve(size);
	}
}

void AdjMatrix::insert(size_t insert_location, size_t value, float weight) {
	if (insert_location > data.size())
		return;
	if (value > data[insert_location - 1].size())
		return;

	data[insert_location - 1][value - 1] = value;
}

std::vector<int> AdjMatrix::getChildren(size_t parent) const {
	std::vector<int> children;
	
	for (auto child : this->data[parent - 1])
		if (child != 0)
			children.push_back(child);

	return children;
}

float AdjMatrix::getWeight(size_t start, size_t end) const {
	if (start > data.size() || 
		end > data[start - 1].size())
		return -1;
	
	return data[start][end];
}