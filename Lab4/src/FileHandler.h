#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <unordered_map>
#include <vector>

class FileHandler {
public:
	struct Position {
		Position(float x, float y, float z)
			: x(x), y(y), z(z) {}

		float x, y, z;
	};

	static int loadGraph(std::unordered_map<int, Position>& positions, const char* filePath);
	static void saveData(const char* filePath, std::vector<float>& distances, std::vector<float>& times, int sizeStart);
	static void loadBestDistances(const char* filePath, std::vector<float>& distances);

private:
	static std::vector<int> splitNodes(std::string& str);
	static float getDistance(std::string& line);
};

#endif
