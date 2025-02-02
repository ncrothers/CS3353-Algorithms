#ifndef GRAPH_H
#define GRAPH_H

/* ========================================= */
/*                  Graph                    */
/* ========================================= */

#include <vector>
#include <unordered_map>
#include <algorithm>

class graph {
public:
	struct Node {
		Node(size_t _data) {
			data = _data;
		}

		~Node() {
			for (auto node : neighbors)
				delete node;
		}

		size_t data;
		float weight = 0;
		std::vector<Node*> neighbors;
	};

	struct Position {
		Position(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}

		Position(const Position& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

		float x, y, z;
	};

	virtual void reserve(size_t size) = 0;
	virtual void insert(size_t insert_location, size_t value) = 0;
	virtual void setWeight(size_t insert_location, size_t value, float weight) = 0;
	virtual std::vector<Node*> getChildren(size_t parent) const = 0;
	virtual float getWeight(size_t start, size_t end) const = 0;
	void setPos(size_t node, float x, float y, float z);
	size_t getSize() const;

	// Returns the node's position values as a Position
	// Returns a Position with x = INint32_MAX if not found
	Position getPos(int node) const;

protected:
	std::unordered_map<int, Position> vertexPos;
	size_t graphSize;
};

#endif GRAPH_H