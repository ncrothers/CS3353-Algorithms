#ifndef GRAPH_H
#define GRAPH_H

/* ========================================= */
/*                  Graph                    */
/* ========================================= */

#include "linked_list.h"
#include <vector>
#include <unordered_map>

template <class T>
class graph {
public:
	// Type represents which data structure the graph uses.
	// 0 = adjacency list
	// 1 = adjacency matrix
	graph(size_t type, size_t size);
	graph(const graph&);

	void insert(const T& insert_location, const T& value);
	std::vector<T> getChildren(const T&);

private:
	std::vector<linked_list<T>> adj_list;
	std::vector<std::vector<T>> adj_matrix;
	std::unordered_map<std::pair<T, T>, std::vector<int>> path_weights;
	std::unordered_map<T, int*> vertex_pos;
	size_t graphType;
};

template <class T>
graph<T>::graph(size_t type, size_t size) {
	if (type == 0) {
		graphType = 0;
		for (int i = 0; i < size; i++)
			adj_list.insertBack(linked_list<T>);

	}
	else if (type == 1) {
		graphType = 1;
		adj_matrix.reserve(size);
		for (auto vec : adj_matrix)
			vec.reserve(size);
	}
	else {
		throw "Invalid type for graph";
	}
}

template <class T>
graph<T>::graph(const graph& input) {

}

template <class T>
void graph<T>::insert(const T& insert_location, const T& value) {
	
}

template <class T>
std::vector<T> graph<T>::getChildren(const T& node) {

}

#endif GRAPH_H