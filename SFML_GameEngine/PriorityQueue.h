#pragma once
#include "ArrayList.h"
#include "Entry.h"

template <typename T>
class PriorityQueue {
private:
	ArrayList<Entry<T>> * dataList;
	int findIndex(int key) {
		int i = 0;
		int size = dataList->getSize();
		for (i = 0; i < size; i++) {
			Entry<T> * entry = dataList->get(i);
			if (entry->key == key) {
				return i + 1;
			}
			else {
				if (entry->key > key) {
					return i;
				}
			}
		}
		return i;
	}
public:
	PriorityQueue() {
		dataList = new ArrayList<Entry<T>>();
	}

	PriorityQueue(int length) {
		dataList = new ArrayList<Entry<T>>(length);
	}

	~PriorityQueue() {
		delete dataList;
	}

	void removeAt(T data) {
		int i = 0;
		int size = dataList->getSize();
		for (i = 0; i < size; i++) {
			Entry<T> * entry = dataList->get(i);
			if (entry->data == data) {
				dataList->remove(i);
			}
		}
	}

	void push(T data, int key) {
		int inputTarget = findIndex(key);
		dataList->add(new Entry<T>(data, key), inputTarget);
	}

	T pop() {
		if (dataList->isEmpty()) {
			return nullptr;
		}
		Entry<T> entry = *(dataList->get(0));
		dataList->remove(0);
		return entry.data;
	}
	bool isEmpty() {
		return dataList->isEmpty();
	}
};