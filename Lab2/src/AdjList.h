#ifndef ADJLIST_H
#define ADJLIST_H

#include "graph.h"

class AdjList : public graph {
public:
	AdjList();
	AdjList(size_t size);
	~AdjList();

	void reserve(size_t size);

	void insert(size_t insert_location, size_t value);
	void setWeight(size_t insert_location, size_t value, float weight);
	std::vector<Node*> getChildren(size_t parent) const;
	// Returns -1 if either start or end is invalid
	float getWeight(size_t start, size_t end) const;

private:
	std::vector<Node> data;
};

#endif ADJLIST_H