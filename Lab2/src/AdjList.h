#ifndef ADJLIST_H
#define ADJLIST_H

#include "graph.h"

class AdjList : public graph {
public:
	AdjList(size_t size);

	virtual void insert(size_t insert_location, size_t value);
	virtual void setWeight(size_t insert_location, size_t value, float weight);
	virtual std::vector<int> getChildren(size_t parent) const;
	// Returns -1 if either start or end is invalid
	virtual float getWeight(size_t start, size_t end) const;

private:
	std::vector<Node> data;
};

#endif ADJLIST_H