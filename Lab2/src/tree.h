#ifndef TREE_H
#define TREE_H

#include <vector>

template <class T>
class tree {
private:
	template <class U>
	struct Node {
		Node();
		Node(const U& input) : data(input) {}

		Node(const Node<U>& input) : data(input) {
			for (int i = 0; i < input.children.size(); i++)
				children.push_back(input.children[i]);
			depth = input.depth;
		}

		void addChild(const U& child) {
			children.push_back(child);
		}

		U data;
		size_t depth;
		std::vector<Node*> children;
	};

public:

	tree();
	~tree();

	bool isEmpty();
	void insert(const T& location, const T& child);
	void insert(const T& location, const std::vector<T>& children);

private:
	Node<T>* root;

	void makeEmpty(Node<T>* node);
	void setRoot(const T& location);
	Node<T>* findNode(const Node<T>* iter, const T& location);
};

template <class T>
tree<T>::tree() {
	root = nullptr;
}

template <class T>
tree<T>::~tree() {
	makeEmpty(root);
}

template <class T>
bool tree<T>::isEmpty() {
	return root == nullptr;
}

template <class T>
void tree<T>::makeEmpty(Node<T>* node) {
	if (node->children.empty())
		return delete node;
	for (auto child : node->children)
		makeEmpty(child);
}

template <class T>
void tree<T>::insert(const T& location, const T& child) {
	if (isEmpty()) {
		setRoot(location);
	}

	Node<T>* parent = findNode(root, location);
	if (parent != nullptr) {
		parent->addChild(child);
	}
	else {
		throw "Parent node not found";
	}
}

template <class T>
void tree<T>::insert(const T& location, const std::vector<T>& children) {
	if (isEmpty()) {
		setRoot(location);
	}

	Node<T>* parent = findNode(root, location);
	if (parent != nullptr) {
		parent->children = children;
	}
	else {
		throw "Parent node not found";
	}
}

template <class T>
void tree<T>::setRoot(const T& location) {
	root = new Node<T>(location);
}

template <class T>
tree<T>::Node<T>* tree<T>::findNode(const Node<T>* iter, const T& location) {
	if (iter->data != location) {
		for (auto node : iter->children)
			findNode(node, location);
	}
	else {
		return iter;
	}
	return nullptr;
}

#endif TREE_H