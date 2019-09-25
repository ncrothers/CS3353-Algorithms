#ifndef NODE_H
#define NODE_H

/* ========================================= */
/*                   Node                    */
/* ========================================= */

template <class T>
class Node {
public:
	Node();
	Node(const T&);
	Node(const Node<T>&);
	T& getData();

private:
	template <class U> friend class linked_list;
	T data;
	Node<T>* next, prev;
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
public:
	linked_list();
	linked_list(const linked_list<T>&);

	// Inserts at the back of the list
	void insertBack(const T&);
	// Inserts before the index given
	void insertBefore(const T&, const size_t);
	// Inserts after the index given
	void insertAfter(const T&, const size_t);
	// Returns the element at the end of the list
	T& last() const;
	size_t size() const;
	bool empty() const;

private:
	size_t _size = 0;
	Node<T>* head = nullptr; 
	Node<T>* tail = nullptr;
	Node<T>* iter = nullptr;

	void setIter(size_t);
	void resetIter();
	void stepIter();
	bool validIter() const;
};

template <class T>
linked_list<T>::linked_list() {}

template <class T>
linked_list<T>::linked_list(const linked_list<T>& list) {
	iter = head = new Node<T>(list.head->data);
	
	resetIter();
	list.resetIter();

	while (list.validIter()) {
		iter->next = new Node<T>(list.iter->data);
		iter->next->prev = iter;
		stepIter();
		list.stepIter();
	}

	_size = list._size;
	resetIter();
	list.resetIter();
}

template <class T>
void linked_list<T>::insertBack(const T& data) {
	Node<T>* newNode = new Node<T>(data);

	if (tail != nullptr) {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	else {
		head = tail = iter = new Node<T>(data);
	}
}

template <class T>
void linked_list<T>::setIter(size_t index) {
	// If index is at the first half of the list
	if (_size / 2 > index) {
		resetIter();
		for (int i = 0; i != index; i++)
			stepIter();
	}
	else {
		iter = tail;
		for (int i = _size - 1; i != index; i--)
			iter = iter->prev;
	}
}

template <class T>
void linked_list<T>::insertBefore(const T& data, const size_t index) {
	if (index >= _size)
		throw "out-of-bounds list index";

	Node<T>* newNode = new Node<T>(data);

	if (empty()) {
		head = tail = iter = newNode;
		_size++;
		return;
	}
	
	setIter(index);

	if (iter->prev == nullptr) {
		iter->prev = newNode;
		newNode->next = iter;
		head = iter = newNode;
	}
	else {
		iter->prev->next = newNode;
		newNode->prev = iter->prev;
		newNode->next = iter;
		iter->prev = newNode;
	}

	_size++;
}

template <class T>
void linked_list<T>::insertAfter(const T& data, const size_t index) {
	if (index >= _size)
		throw "out-of-bounds list index";

	Node<T>* newNode = new Node<T>(data);

	if (empty()) {
		head = tail = iter = newNode;
		_size++;
		return;
	}

	setIter(index);

	if (iter->next == nullptr) {
		iter->next = newNode;
		newNode->prev = iter;
		tail = iter = newNode;
	}
	else {
		iter->next->prev = newNode;
		newNode->prev = iter->next;
		newNode->prev = iter;
		iter->prev = newNode;
	}

	_size++;
}

template <class T>
T& linked_list<T>::last() const {
	return tail->data;
}

template <class T>
size_t linked_list<T>::size() const {
	return _size;
}

template <class T>
bool linked_list<T>::empty() const {
	return _size == 0;
}

template <class T>
void linked_list<T>::resetIter() {
	iter = head;
}

template <class T>
void linked_list<T>::stepIter() {
	iter = iter->next;
}

template <class T>
bool linked_list<T>::validIter() const {
	return iter != nullptr;
}

#endif LINKED_LIST_H