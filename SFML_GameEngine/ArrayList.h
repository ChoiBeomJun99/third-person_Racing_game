#pragma once

#define INITSIZE 5


template <typename T>
class ArrayList {
private:
	T** array;
	int size;
	int currentIndex;

	void extend() {
		T** newArray = (T**)malloc(sizeof(T*) * (size * 2));
		for (int i = 0; i < size; i++) {
			newArray[i] = array[i];
		}
		this->size *= 2;
		this->array = newArray;
	}

public:
	ArrayList() {
		this->currentIndex = 0;
		this->array = (T**)malloc(sizeof(T*) * INITSIZE);
		this->size = INITSIZE;
	}

	ArrayList(int size) {
		this->currentIndex = 0;
		this->array = (T**)malloc(sizeof(T*) * size);
		this->size = size;
	}

	~ArrayList() {
		this->removeAll();
	}


	void add(T * data) {
		if (size == currentIndex) {
			extend();
		}
		array[currentIndex] = data;
		currentIndex++;
	}

	void add(T * data, int index) {
		if (size == currentIndex) {
			extend();
		}
		if (index <= currentIndex) {
			for (int i = currentIndex; i > index; i--) {
				this->array[i] = this->array[i - 1];
			}
			array[index] = data;
		}
		else {
			array[currentIndex] = data;
		}
		currentIndex++;
	}

	T* get(int index) {
		if (index >= currentIndex) {
			return nullptr;
		}
		return array[index];
	}

	void remove(int index) {
		if (index >= currentIndex) {
			return;
		}
		for (int i = index; i < currentIndex - 1; i++) {
			this->array[i] = this->array[i + 1];
		}
		currentIndex--;
	}

	void removeAll() {
		free(array);
		this->currentIndex = 0;
		this->array = (T**)malloc(sizeof(T*) * INITSIZE);
		this->size = INITSIZE;
	}

	int getSize() {
		return this->currentIndex;
	}

	int totalMemory() {
		return this->size;
	}

	bool isEmpty() {
		return currentIndex == 0 ? true : false;
	}

};