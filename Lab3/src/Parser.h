#ifndef PARSER_H
#define PARSER_H

#include <unordered_map>
#include <vector>

#include "TSPAlgorithm.h"

class Parser {
public:
	struct Position {
		Position(float x, float y, float z)
			: x(x), y(y), z(z) {}

		float x, y, z;
	};

	static int loadGraph(std::unordered_map<int, Position>& positions, const char* filePath);
	static std::vector<int> splitNodes(std::string& str);

};

#endif