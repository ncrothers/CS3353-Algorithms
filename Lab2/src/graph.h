#ifndef GRAPH_H
#define GRAPH_H

/* ========================================= */
/*                  Graph                    */
/* ========================================= */

#include "linked_list.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Position {
	Position(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	float x, y, z;
};

template <class T>
class graph {
public:
	virtual void insert(const T& insert_location, const T& value) = 0;
	virtual std::vector<T> getChildren(const T& parent) const = 0;

	// Returns the path weight between the two given values
	// Returns -1 if not found
	virtual float getWeight(const T& start, const T& end) const;

	// Returns the node's position values as a Position
	// Returns a Position with x = INT32_MAX if not found
	virtual Position& getPos(const T& node) const;

protected:
	std::vector<std::vector<T>> data;
	std::unordered_map<std::pair<T, T>, float> path_weights;
	std::unordered_map<T, Position> vertex_pos;
};

template <class T>
float graph<T>::getWeight(const T& start, const T& end) const {
	try {
		return path_weights.at(std::make_pair<T, T>(start, end));
	}
	catch (std::exception e) {
		return -1;
	}
}

template <class T>
Position& graph<T>::getPos(const T& node) const {
	try {
		return vertex_pos.at(node);
	}
	catch (std::exception e) {
		return graph<T>::Position(INT32_MAX, 0, 0);
	}
}

#endif GRAPH_H