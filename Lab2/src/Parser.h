#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

#include "graph.h"

class Parser {
public:
	static int loadGraph(graph& graph, const char* filePath);
	static void loadPositions(graph& graph, const char* filePath);
	static void loadWeights(graph& graph, const char* filePath);

private:
	static std::vector<int> splitNodes(std::string& str);
	static std::vector<float> splitPos(std::string& str);
};

#endif PARSER_H