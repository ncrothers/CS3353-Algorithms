#ifndef ADJLIST_H
#define ADJLIST_H

#include "graph.h"

template <class T>
class AdjList : public graph<T> {
public:
	AdjList(size_t size);

	virtual void insert(const T& insert_location, const T& value);
	virtual std::vector<T> getChildren(const T& parent) const;
};

#endif ADJLIST_H