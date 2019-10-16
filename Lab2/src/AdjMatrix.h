#ifndef ADJMATRIX_H
#define ADJMATRIX_H

#include "graph.h"

class AdjMatrix : public graph {
public:
	AdjMatrix();
	AdjMatrix(size_t size);

	void reserve(size_t size);

	void insert(size_t insert_location, size_t value);
	void setWeight(size_t insert_location, size_t value, float weight);
	std::vector<graph::Node*> getChildren(size_t parent) const;
	float getWeight(size_t start, size_t end) const;

private:
	std::vector<std::vector<Node*>> data;
};

#endif ADJMATRIX_H