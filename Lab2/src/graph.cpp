#include "graph.h"

graph::Position graph::getPos(int node) const {
	try {
		return vertexPos.at(node);
	}
	catch (std::exception e) {
		return graph::Position(INT32_MAX, 0, 0);
	}
}

void graph::setPos(size_t node, float x, float y, float z) {
	vertexPos.try_emplace(node, graph::Position(x, y, z));
}