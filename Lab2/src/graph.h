#ifndef GRAPH_H
#define GRAPH_H

/* ========================================= */
/*                  Graph                    */
/* ========================================= */

#include "linked_list.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

class graph {
public:
	struct Position {
		Position(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}
		float x, y, z;
	};

	virtual void insert(int insert_location, int value, float weight) = 0;
	virtual std::vector<int> getChildren(const int parent) const = 0;

	// Returns the node's position values as a Position
	// Returns a Position with x = INint32_MAX if not found
	virtual Position getPos(int node) const;

protected:
	std::unordered_map<int, Position> vertex_pos;
};

#endif GRAPH_H