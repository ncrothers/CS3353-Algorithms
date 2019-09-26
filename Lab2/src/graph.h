/* ========================================= */
/*                   Node                    */
/* ========================================= */

#include <vector>

/*
#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
public:
	Node();
	Node(const T&);
	Node(const Node<T>&);
	T& getData();

private:
	template <class U> friend class graph;
	T data;
	vector<Node<T>*> children;
};

template <class T>
Node<T>::Node() {
	next = prev = nullptr;
}

template <class T>
Node<T>::Node(const T& val) : data(val) {
	next = prev = nullptr;
}

template <class T>
T& Node<T>::getData() {
	return data;
}

template <class T>
Node<T>::Node(const Node<T>& node) :
	children(node.children),
	data(node.data) {
}

#endif NODE_H

*/

template <class T>
struct Node {

};

struct Edge {
	float weight;

};

#ifndef GRAPH_H
#define GRAPH_H

/* ========================================= */
/*                  Graph                    */
/* ========================================= */

template <class T>
class graph {
public:
	graph();
	graph(const graph&);

private:

};

template <class T>
graph<T>::graph() {

}

template <class T>
graph<T>::graph(const graph& input) {

}

#endif GRAPH_H