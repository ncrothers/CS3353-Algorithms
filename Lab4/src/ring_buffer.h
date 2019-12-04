
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <vector>

template <typename T>
class ring_buffer {
public:
	ring_buffer(int _size);

	void push(const T& input);
	void clear();
	bool contains(const T& input) const;
	std::size_t size() const;

private:
	int head;
	std::size_t _size;
	std::vector<T> data;
};

template <typename T>
ring_buffer<T>::ring_buffer(int _size) : _size(_size), head(0) {
}

template <typename T>
void ring_buffer<T>::push(const T& input) {
	if (data.size() < _size)
		data.push_back(input);
	else
		data[head] = input;
	
	head = (head == _size - 1 ? 0 : head + 1);
}

template <typename T>
void ring_buffer<T>::clear() {
	data.clear();
}

template <typename T>
bool ring_buffer<T>::contains(const T& input) const {
	int iter;
	if (data.size() < _size) {
		iter = 0;
		while (iter < data.size()) {
			if (data[iter] == input)
				return true;
			iter++;
		}
	}
	else {
		iter = head;
		while (iter != head) {
			if (data[iter] == input)
				return true;

			iter = (iter == _size - 1 ? 0 : iter + 1);
		}
	}
	return false;
}

template <typename T>
std::size_t ring_buffer<T>::size() const {
	return _size;
}

#endif