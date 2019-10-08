#ifndef ADJMATRIX_H
#define ADJMATRIX_H

#include "graph.h"

class AdjMatrix : public graph {
public:
	AdjMatrix(size_t size);

	virtual void insert(size_t insert_location, size_t value, float weight);
	virtual std::vector<int> getChildren(size_t parent) const;

private:
	std::vector<std::vector<int>> data;
};

#endif ADJMATRIX_H