#ifndef ADJLIST_H
#define ADJLIST_H

#include "graph.h"

class AdjList : public graph {
public:
	struct Node {
		Node(size_t _data, float _weight) {
			data = _data;
			weight = _weight;
		}

		~Node() {
			for (auto node : neighbors)
				delete node;
		}

		size_t data;
		float weight;
		std::vector<Node*> neighbors;
	};

	AdjList(size_t size);

	virtual void insert(size_t insert_location, size_t value, float weight);
	virtual std::vector<int> getChildren(size_t parent) const;

private:
	std::vector<Node> data;
};

#endif ADJLIST_H