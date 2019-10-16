#ifndef TREE_H
#define TREE_H

#include <vector>

template <class T>
class tree {
private:
	template <class U>
	struct Node {
		Node();
		Node(const U& input, Node<U>* parent) : data(input), parent(parent) {}

		Node(const Node<U>& input) : data(input) {
			for (int i = 0; i < input.children.size(); i++) {
				children.push_back(input.children[i]);
			}
			depth = input.depth;
		}

		void addChild(const U& child) {
			children.push_back(new Node<U>(child));
			children.back().parent = this;
		}

		U data;
		Node* parent = nullptr;
		size_t depth;
		std::vector<Node*> children;
	};

public:

	tree();
	~tree();

	void clear();

	bool isEmpty();
	void insert(const T& location, const T& child);
	void insert(const T& location, const std::vector<T>& children);

	std::vector<T> pathToRoot(const T& end);
	std::vector<T> pathToRoot(const T& end, const T& parent);

private:
	Node<T>* root;

	void makeEmpty(Node<T>* node);
	void setRoot(const T& location);
	Node<T>* findNode(Node<T>* iter, const T& location);
	Node<T>* findNode(Node<T>* iter, const T& location, const T& parent);
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
void tree<T>::clear() {
	makeEmpty(root);
	root = nullptr;
}

template <class T>
bool tree<T>::isEmpty() {
	return root == nullptr;
}

template <class T>
void tree<T>::makeEmpty(Node<T>* node) {
	if (node == nullptr)
		return;
	if (node->children.empty()) {
		delete node;
		return;
	}
	for (auto child : node->children)
		makeEmpty(child);
	delete node;
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
		for (int i = 0; i < children.size(); i++) {
			parent->children.push_back(new Node<T>(children[i], parent));
		}
	}
	else {
		throw "Parent node not found";
	}
}

template <class T>
std::vector<T> tree<T>::pathToRoot(const T& end) {
	std::vector<T> path;
	Node<T>* iter = findNode(root, end);
	while (iter != nullptr) {
		path.push_back(iter->data);
		iter = iter->parent;
	}
	return path;
}

template <class T>
std::vector<T> tree<T>::pathToRoot(const T& end, const T& parent) {
	std::vector<T> path;
	Node<T>* iter = findNode(root, end, parent);
	while (iter != nullptr) {
		path.push_back(iter->data);
		iter = iter->parent;
	}
	return path;
}

template <class T>
void tree<T>::setRoot(const T& location) {
	root = new Node<T>(location, nullptr);
}

template <class T>
tree<T>::Node<T>* tree<T>::findNode(Node<T>* iter, const T& location) {
	Node<T>* result;
	if (iter->data != location) {
		for (auto node : iter->children) {
			result = findNode(node, location);
			if (result != nullptr)
				return result;
		}
	}
	else {
		return iter;
	}
	return nullptr;
}

template <class T>
tree<T>::Node<T>* tree<T>::findNode(Node<T>* iter, const T& location, const T& parent) {
	Node<T>* result;
	if (iter->data != location) {
		for (auto node : iter->children) {
			result = findNode(node, location, parent);
			if (result != nullptr && result->parent->data == parent)
				return result;
		}
	}
	else {
		return iter;
	}
	return nullptr;
}

#endif TREE_H