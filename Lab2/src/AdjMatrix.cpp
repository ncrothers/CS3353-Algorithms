#include "AdjMatrix.h"

template <class T>
AdjMatrix<T>::AdjMatrix(size_t size) {
	this->data.reserve(size);
	
	for (auto row : this->data) {
		row.reserve(size);
	}
}

template <class T>
void AdjMatrix<T>::insert(const T& insert_location, const T& value) {

}

template <class T>
const std::vector<T> AdjMatrix<T>::getChildren(const T& parent) const {
	std::vector<T> children;
	
	for (auto child : this->data[parent - 1])
		if (child != 0)
			children.push_back(child);
}