#include "FileHandler.h"
#include <fstream>
#include <string>

int FileHandler::loadGraph(std::unordered_map<int, Position>& positions, const char* filePath) {
	std::ifstream file(filePath);

	std::string line;
	int count = 0;
	while (file >> line)
		count++;

	file.clear();
	file.seekg(0);

	// Loads in position information from the file
	while (file >> line) {
		std::vector<int> nodes = splitNodes(line);

		positions.emplace(nodes[0], Position(nodes[1], nodes[2], nodes[3]));
	}

	return count;
}

void FileHandler::saveData(const char* filePath, std::vector<float>& distances, std::vector<float>& times, int sizeStart) {
	std::ofstream file(filePath);

	for (int i = 0; i < distances.size(); i++) {
		file << sizeStart + i << "," << distances[i] << "," << times[i] << std::endl;
	}
}

std::vector<int> FileHandler::splitNodes(std::string& str) {
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