#ifndef ADJMATRIX_H
#define ADJMATRIX_H

#include "graph.h"

class AdjMatrix : public graph {
public:
	AdjMatrix(size_t size);

	virtual void insert(size_t insert_location, size_t value, float weight);
	virtual std::vector<int> getChildren(size_t parent) const;
	virtual float getWeight(size_t start, size_t end) const;

private:
	std::vector<std::vector<int>> data;
	std::vector<std::vector<float>> weights;
};

#endif ADJMATRIX_H