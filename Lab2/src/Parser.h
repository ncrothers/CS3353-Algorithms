#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

#include "graph.h"

class Parser {
public:
	static void loadGraph(graph& graph, char* filePath);
	static void loadPositions(std::unordered_map<int, graph::Position>& vertex_pos, char* filePath);
	static void loadWeights(graph& graph, char* filePath);

private:
	static std::vector<int> splitNodes(std::string& str);
	static std::vector<float> splitPos(std::string& str);
};

#endif PARSER_H