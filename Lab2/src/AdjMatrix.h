#ifndef ADJMATRIX_H
#define ADJMATRIX_H

#include "graph.h"

template <class T>
class AdjMatrix : public graph<T> {
public:
	AdjMatrix(size_t size);

	virtual void insert(const T& insert_location, const T& value);
	virtual const std::vector<T> getChildren(const T& parent) const;
};

#endif ADJMATRIX_H