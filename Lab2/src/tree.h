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

	Node<T>* root;

public:

	tree();
	tree(const tree&);
	~tree();

	T& getElement(const T&);
	bool isEmpty();
	void makeEmpty();
	void addChild
};

#endif TREE_H