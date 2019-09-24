#ifndef NODE_H
#define NODE_H

/* ========================================= */
/*                   Node                    */
/* ========================================= */

template <class T>
class Node {
private:
	template <class U> friend class linked_list;
	T data;
	Node<T>* next, prev;

public:
	Node();
	Node(const T&);
	Node(const Node<T>&);
	T& getData();
};

template <class T>
Node<T>::Node() {
	next = prev = nullptr;
}

template <class T>
Node<T>::Node(const T& val) : data(val){
	next = prev = nullptr;
}

template <class T>
T& Node<T>::getData() {
	return data; 
}

template <class T>
Node<T>::Node(const Node<T>& node) : 
	next(node.next), 
	prev(node.prev), 
	data(node.data) {
}

#endif NODE_H

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* ========================================= */
/*               Linked List                 */
/* ========================================= */

template <class T>
class linked_list {

};

#endif LINKED_LIST_H