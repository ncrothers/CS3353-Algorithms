#include "graph.h"

graph::Position graph::getPos(int node) const {
	try {
		return vertex_pos.at(node);
	}
	catch (std::exception e) {
		return graph::Position(INT32_MAX, 0, 0);
	}
}