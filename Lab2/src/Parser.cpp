#include "Parser.h"

int Parser::loadGraph(graph& graph, const char* filePath) {
	std::ifstream file(filePath);

	std::string line;
	int count = 0;
	while (file >> line)
		count++;

	file.clear();
	file.seekg(0);
	graph.reserve(count);

	while (file >> line) {
		std::vector<int> nodes = splitNodes(line);
		for (int i = 1; i < nodes.size(); i++) {
			graph.insert(nodes[0], nodes[i]);
		}
	}
	return count;
}

void Parser::loadPositions(graph& graph, const char* filePath) {
	std::ifstream file(filePath);

	std::string line;
	while (file >> line) {
		std::vector<float> pos = splitPos(line);
		graph.setPos(pos[0], pos[1], pos[2], pos[3]);
	}
}

void Parser::loadWeights(graph& graph, const char* filePath) {
	std::ifstream file(filePath);

	std::string line;
	while (file >> line) {
		std::vector<float> weights = splitPos(line);
		graph.setWeight(weights[0], weights[1], weights[2]);
	}
}

std::vector<int> Parser::splitNodes(std::string& str) {
	std::vector<int> nodes;
	size_t index1 = 0;
	size_t index0 = 0;
	while (index1 < str.size()) {
		if (str[index1] == ',') {
			nodes.push_back(std::stoi(str.substr(index0, index1 - index0)));
			index0 = index1 + 1;
		}
		index1++;
	}
	nodes.push_back(std::stoi(str.substr(index0, index1 - index0)));

	return nodes;
}

std::vector<float> Parser::splitPos(std::string& str) {
	std::vector<float> nodes;
	size_t index1 = 0;
	size_t index0 = 0;
	while (index1 < str.size()) {
		if (str[index1] == ',') {
			nodes.push_back(std::stof(str.substr(index0, index1 - index0)));
			index0 = index1 + 1;
		}
		index1++;
	}
	nodes.push_back(std::stof(str.substr(index0, index1 - index0)));

	return nodes;
}